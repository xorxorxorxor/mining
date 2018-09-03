// WK2017Doc.h : interface of the CWK2017Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WK2017DOC_H__B0D7EFBF_9428_449F_BF40_29B29A12AA1A__INCLUDED_)
#define AFX_WK2017DOC_H__B0D7EFBF_9428_449F_BF40_29B29A12AA1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWK2017Doc : public CDocument
{
protected: // create from serialization only
	CWK2017Doc();
	DECLARE_DYNCREATE(CWK2017Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWK2017Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWK2017Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWK2017Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WK2017DOC_H__B0D7EFBF_9428_449F_BF40_29B29A12AA1A__INCLUDED_)
