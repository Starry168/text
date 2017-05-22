// DYT_530Doc.cpp : implementation of the CDYT_530Doc class
//

#include "stdafx.h"
#include "DYT_530.h"

#include "DYT_530Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDYT_530Doc

IMPLEMENT_DYNCREATE(CDYT_530Doc, CDocument)

BEGIN_MESSAGE_MAP(CDYT_530Doc, CDocument)
	//{{AFX_MSG_MAP(CDYT_530Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDYT_530Doc construction/destruction

CDYT_530Doc::CDYT_530Doc()
{
	// TODO: add one-time construction code here

}

CDYT_530Doc::~CDYT_530Doc()
{
}

BOOL CDYT_530Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDYT_530Doc serialization

void CDYT_530Doc::Serialize(CArchive& ar)
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
// CDYT_530Doc diagnostics

#ifdef _DEBUG
void CDYT_530Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDYT_530Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDYT_530Doc commands
BOOL LoadBmpFile(char*BmpFileName);
BOOL CDYT_530Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	LoadBmpFile((char*)lpszPathName);
	return TRUE;
}
