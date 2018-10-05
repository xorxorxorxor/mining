// WK2017View.cpp : implementation of the CWK2017View class
//

#include "stdafx.h"
#include "WK2017.h"

#include "WK2017Doc.h"
#include "WK2017View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWK2017View

IMPLEMENT_DYNCREATE(CWK2017View, CView)

BEGIN_MESSAGE_MAP(CWK2017View, CView)
	//{{AFX_MSG_MAP(CWK2017View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWK2017View construction/destruction

CWK2017View::CWK2017View()
{
	// TODO: add construction code here

}

CWK2017View::~CWK2017View()
{
}

BOOL CWK2017View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWK2017View drawing

void CWK2017View::OnDraw(CDC* pDC)
{
	CWK2017Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CWK2017View printing

BOOL CWK2017View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWK2017View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWK2017View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWK2017View diagnostics

#ifdef _DEBUG
void CWK2017View::AssertValid() const
{
	CView::AssertValid();
}

void CWK2017View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWK2017Doc* CWK2017View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWK2017Doc)));
	return (CWK2017Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWK2017View message handlers
