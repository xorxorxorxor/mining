#if !defined(AFX_injection_H_INCLUDED)
#define AFX_injection_H_INCLUDED
#include <Windows.h>
#include <shlobj.h>
#include <psapi.h>
#pragma comment (lib, "psapi.lib")
DWORD WINAPI remote(LPVOID pvparam);
DWORD processtopid(char *processname);
BOOL EnablePriv();
HANDLE CreateRemoteThreadProc(char* ProcessName);
#endif // !defined(AFX_injection_H_INCLUDED)