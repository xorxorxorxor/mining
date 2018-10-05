// WK2017Doc.cpp : implementation of the CWK2017Doc class
//

#include "stdafx.h"
#include "WK2017.h"

#include "WK2017Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWK2017Doc

IMPLEMENT_DYNCREATE(CWK2017Doc, CDocument)

BEGIN_MESSAGE_MAP(CWK2017Doc, CDocument)
	//{{AFX_MSG_MAP(CWK2017Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWK2017Doc construction/destruction

CWK2017Doc::CWK2017Doc()
{
	// TODO: add one-time construction code here

}

CWK2017Doc::~CWK2017Doc()
{
}

BOOL CWK2017Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWK2017Doc serialization

void CWK2017Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWK2017Doc diagnostics

#ifdef _DEBUG
void CWK2017Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWK2017Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWK2017Doc commands
