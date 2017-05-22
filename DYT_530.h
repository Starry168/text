// DYT_530.h : main header file for the DYT_530 application
//

#if !defined(AFX_DYT_530_H__D2275F02_BFC3_46F1_B1E0_F0ABAD9573B4__INCLUDED_)
#define AFX_DYT_530_H__D2275F02_BFC3_46F1_B1E0_F0ABAD9573B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDYT_530App:
// See DYT_530.cpp for the implementation of this class
//

class CDYT_530App : public CWinApp
{
public:
	CDYT_530App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDYT_530App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDYT_530App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYT_530_H__D2275F02_BFC3_46F1_B1E0_F0ABAD9573B4__INCLUDED_)
