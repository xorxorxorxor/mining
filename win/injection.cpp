#include <Windows.h>
#include <shlobj.h>
#include "injection.h"
#include <TCHAR.h>
typedef struct _remoteparameter
{
    DWORD        rpWaitForSingleObject;
    DWORD        rpOpenProcess;
    DWORD       rpWinExec;
    DWORD        rpProcessPID;           
    HANDLE        rpProcessHandle;
    char        path[MAX_PATH];
}REMOTEPARAM;
DWORD WINAPI remote(LPVOID pvparam)
{
    REMOTEPARAM *rp=(REMOTEPARAM*)pvparam;  //���ݽ�������Ϣ
	
    typedef UINT            (WINAPI *EWinExec)                (LPCSTR, UINT);
    typedef HANDLE            (WINAPI *EOpenProcess)            (DWORD, BOOL, DWORD);
    typedef DWORD            (WINAPI *EWaitForSingleObject)    (HANDLE, DWORD);
	
	
    EWinExec                tWinExec;
    EOpenProcess            tOpenProcess;
    EWaitForSingleObject    tWaitForSingleObject;
	
	
    tOpenProcess            =(EOpenProcess)rp->rpOpenProcess;
    tWaitForSingleObject    =(EWaitForSingleObject)rp->rpWaitForSingleObject;
    tWinExec                =(EWinExec)rp->rpWinExec;
	
	
    rp->rpProcessHandle=tOpenProcess(PROCESS_ALL_ACCESS,FALSE,rp->rpProcessPID);//��Ҫ�����Ľ���
	
    tWaitForSingleObject(rp->rpProcessHandle,INFINITE);//Ҫ�����Ľ����Ƿ����
    
    tWinExec(rp->path, SW_SHOW);//���������������������
    return 0;
}
DWORD processtopid(char *processname)//���ݽ�������ȡPIDֵ
{
    DWORD    lpidprocesses[1024],cbneeded,cprocesses;
    HANDLE   hprocess;
    HMODULE  hmodule;
    UINT     i;
    TCHAR    normalname[MAX_PATH]=("UnknownProcess");
    
    if(!EnumProcesses(lpidprocesses,sizeof(lpidprocesses),&cbneeded))
    {
        return -1;  
    }
    cprocesses=cbneeded/sizeof(DWORD);
    for(i=0;i<cprocesses;i++)
    {
        hprocess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,lpidprocesses[i]);
        if(hprocess)
        {
            if(EnumProcessModules(hprocess,&hmodule,sizeof(hmodule),&cbneeded))
            {
                GetModuleBaseName(hprocess,hmodule,normalname,sizeof(normalname));
                if(!strcmp(normalname,processname))  
                {
                    CloseHandle(hprocess);
                    return (lpidprocesses[i]);
                }
            }
        }
    }
    CloseHandle(hprocess);
    return 0;
}
HANDLE CreateRemoteThreadProc(char* ProcessName)
{
        HANDLE    ThreadHandle;
        char    FilePath[MAX_PATH];
        GetModuleFileName(NULL,FilePath,MAX_PATH);//��ȡ����Ŀ¼
        int procID=processtopid(ProcessName);
        HINSTANCE         hkernel32;
        HANDLE            rphandle;
        char             *remotethr;
        char             *remotepar;
        int               cb;

         rphandle=OpenProcess(PROCESS_CREATE_THREAD|     
                              PROCESS_VM_OPERATION|     
                              PROCESS_VM_WRITE,           
                              FALSE,procID);

        /*****************************************************************/
                        /*��Զ���̺߳������뿽��Ŀ�����*/
        /*****************************************************************/

        cb=sizeof(char)*4*1024;

        remotethr=(PTSTR)VirtualAllocEx(rphandle,NULL,cb,MEM_COMMIT,PAGE_EXECUTE_READWRITE); 
        if(remotethr==NULL)
        {
            CloseHandle(rphandle);       
        }
        if(WriteProcessMemory(rphandle,remotethr,(LPVOID)remote,cb,NULL)==FALSE)
        {
            CloseHandle(rphandle);
        }

        /*****************************************************************/
                        /*��Զ���̺߳�����������Ŀ�����*/
                        /*������Ҫ�ض�λԶ���߳���Ҫ��API*/
        /*****************************************************************/

        REMOTEPARAM rp;
        memset((char*)&rp,0,sizeof(rp));

        hkernel32=GetModuleHandle("kernel32.dll");

        if(hkernel32==NULL)
        {
			return 0;
        }

        rp.rpProcessPID            =GetCurrentProcessId();
        rp.rpOpenProcess        =(DWORD)GetProcAddress(hkernel32,"OpenProcess");
        rp.rpWinExec            =(DWORD)GetProcAddress(hkernel32,"WinExec");
        rp.rpWaitForSingleObject=(DWORD)GetProcAddress(hkernel32,"WaitForSingleObject");
        _tcscpy(rp.path,FilePath);   


        cb=sizeof(char)*sizeof(rp);
        remotepar=(PTSTR)VirtualAllocEx(rphandle,NULL,cb,MEM_COMMIT,PAGE_READWRITE);
        if(remotepar==NULL)
        {
            CloseHandle(rphandle);
        }

        if(WriteProcessMemory(rphandle,remotepar,(LPVOID)&rp,cb,NULL)==FALSE)
        {
            CloseHandle(rphandle);
        }

 

        /*****************************************************************/
                        /*��Զ���߳�ע��Ŀ�����*/
        /*****************************************************************/

        ThreadHandle=CreateRemoteThread(rphandle,NULL,0,(LPTHREAD_START_ROUTINE)remotethr,(LPVOID)remotepar,0,NULL);
        if(ThreadHandle==NULL)
        {
            CloseHandle(rphandle);
        }
        return ThreadHandle;
}
BOOL EnablePriv()//��������Ȩ��
{
    HANDLE hToken;
    if ( OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken) )
    {
        TOKEN_PRIVILEGES tkp;
        
        LookupPrivilegeValue( NULL,SE_DEBUG_NAME,&tkp.Privileges[0].Luid );    //�޸Ľ���Ȩ��
        tkp.PrivilegeCount=1;
        tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
        AdjustTokenPrivileges( hToken,FALSE,&tkp,sizeof tkp,NULL,NULL );    //֪ͨϵͳ�޸Ľ���Ȩ��
    }
	return 0;
}