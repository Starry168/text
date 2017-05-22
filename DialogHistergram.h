#if !defined(AFX_DIALOGHISTERGRAM_H__79AA72A6_518B_47C9_9CFA_C971AC38EB4B__INCLUDED_)
#define AFX_DIALOGHISTERGRAM_H__79AA72A6_518B_47C9_9CFA_C971AC38EB4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogHistergram.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogHistergram dialog

class CDialogHistergram : public CDialog
{
// Construction
public:
	CDialogHistergram(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogHistergram)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogHistergram)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogHistergram)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGHISTERGRAM_H__79AA72A6_518B_47C9_9CFA_C971AC38EB4B__INCLUDED_)
