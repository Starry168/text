// DYT_530View.h : interface of the CDYT_530View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYT_530VIEW_H__C2F1759A_2CB6_424D_87CF_94F00C6CFFE2__INCLUDED_)
#define AFX_DYT_530VIEW_H__C2F1759A_2CB6_424D_87CF_94F00C6CFFE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDYT_530View : public CScrollView
{
protected: // create from serialization only
	CDYT_530View();
	DECLARE_DYNCREATE(CDYT_530View)

// Attributes
public:
	CDYT_530Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDYT_530View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDYT_530View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDYT_530View)
	afx_msg void Ongray();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGRAY();
	afx_msg void OnUpdateH(CCmdUI* pCmdUI);
	afx_msg void OnUpdateE(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGRAY(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHistogram(CCmdUI* pCmdUI);
	afx_msg void OnHistogram();
	afx_msg void OnLinear();
	afx_msg void OnUpdateLinear(CCmdUI* pCmdUI);
	afx_msg void OnEqualize();
	afx_msg void OnUpdateEqualize(CCmdUI* pCmdUI);
	afx_msg void OnFourier();
	afx_msg void OnUpdateFourier(CCmdUI* pCmdUI);
	afx_msg void OnIfourier();
	afx_msg void OnUpdateIfourier(CCmdUI* pCmdUI);
	afx_msg void OnFft();
	afx_msg void OnUpdateFft(CCmdUI* pCmdUI);
	afx_msg void OnIfft();
	afx_msg void OnUpdateIfft(CCmdUI* pCmdUI);
	afx_msg void OnAverageFilter();
	afx_msg void OnUpdateAverageFilter(CCmdUI* pCmdUI);
	afx_msg void OnMediumFilter();
	afx_msg void OnUpdateMediumFilter(CCmdUI* pCmdUI);
	afx_msg void OnGradSharp();
	afx_msg void OnUpdateGradSharp(CCmdUI* pCmdUI);
	afx_msg void OnRaplasSharp();
	afx_msg void OnUpdateRaplasSharp(CCmdUI* pCmdUI);
	afx_msg void OnD();
	afx_msg void OnUpdateD(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DYT_530View.cpp
inline CDYT_530Doc* CDYT_530View::GetDocument()
   { return (CDYT_530Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYT_530VIEW_H__C2F1759A_2CB6_424D_87CF_94F00C6CFFE2__INCLUDED_)
