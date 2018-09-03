// Éú³ÉÆ÷Dlg.h : header file
//

#if !defined(AFX_DLG_H__3C799092_552D_4EE6_9F1A_AEC8E0D9CF57__INCLUDED_)
#define AFX_DLG_H__3C799092_552D_4EE6_9F1A_AEC8E0D9CF57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog
void update();
void Deletecaching();
class CMyDlg : public CDialog
{
// Construction
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CString	m_IP;
	int		m_Port;
	CString	m_serdis;
	CString	filename;
	CString	m_sername;
	CString	m_sershow;
	CString	Thisversion;
	BOOL    UPX ;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void Onxxs();
	afx_msg void OnChangeEdit3();
	afx_msg void OnButton1();
	afx_msg void OnOk2();
	afx_msg void OnChangeSetDis3();
	afx_msg void OnChangeSetDis4();
	afx_msg void OnChangeSetDis();
	afx_msg void OnOk3();
	afx_msg void OnChangeSetDis2();
	afx_msg void build(CString file);
	afx_msg void OnOk4();
	afx_msg void OnOk5();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__3C799092_552D_4EE6_9F1A_AEC8E0D9CF57__INCLUDED_)
