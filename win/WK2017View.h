// WK2017View.h : interface of the CWK2017View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WK2017VIEW_H__178896E5_EB0F_4A80_8DCB_E9029C44A0EE__INCLUDED_)
#define AFX_WK2017VIEW_H__178896E5_EB0F_4A80_8DCB_E9029C44A0EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWK2017View : public CView
{
protected: // create from serialization only
	CWK2017View();
	DECLARE_DYNCREATE(CWK2017View)

// Attributes
public:
	CWK2017Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWK2017View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWK2017View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWK2017View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WK2017View.cpp
inline CWK2017Doc* CWK2017View::GetDocument()
   { return (CWK2017Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WK2017VIEW_H__178896E5_EB0F_4A80_8DCB_E9029C44A0EE__INCLUDED_)
