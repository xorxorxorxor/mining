// WK2017.h : main header file for the WK2017 application
//

#if !defined(AFX_WK2017_H__DB523E5A_075A_402F_A718_3C6A8BFB2DFA__INCLUDED_)
#define AFX_WK2017_H__DB523E5A_075A_402F_A718_3C6A8BFB2DFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CWK2017App:
// See WK2017.cpp for the implementation of this class
//

class CWK2017App : public CWinApp
{
public:
	CWK2017App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWK2017App)
	public:

	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWK2017App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WK2017_H__DB523E5A_075A_402F_A718_3C6A8BFB2DFA__INCLUDED_)
