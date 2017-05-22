// DYT_530Doc.h : interface of the CDYT_530Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYT_530DOC_H__E5A88978_A4ED_41B2_B2CB_671C8ADA2539__INCLUDED_)
#define AFX_DYT_530DOC_H__E5A88978_A4ED_41B2_B2CB_671C8ADA2539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDYT_530Doc : public CDocument
{
protected: // create from serialization only
	CDYT_530Doc();
	DECLARE_DYNCREATE(CDYT_530Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDYT_530Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDYT_530Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDYT_530Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYT_530DOC_H__E5A88978_A4ED_41B2_B2CB_671C8ADA2539__INCLUDED_)
