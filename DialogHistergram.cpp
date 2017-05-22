// DialogHistergram.cpp : implementation file
//

#include "stdafx.h"
#include "DYT_530.h"
#include "DialogHistergram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogHistergram dialog


CDialogHistergram::CDialogHistergram(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogHistergram::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogHistergram)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogHistergram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogHistergram)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogHistergram, CDialog)
	//{{AFX_MSG_MAP(CDialogHistergram)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogHistergram message handlers

extern DWORD H[256];
void Histogram();//Ö±·½Í¼
BOOL CDialogHistergram::OnInitDialog() 
{
	CDialog::OnInitDialog();
	Histogram();		
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogHistergram::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	int i;
	DWORD max;
	dc.Rectangle(20, 20, 277, 221);
	max=0;
	for(i=0;i<256;i++)
	{
          if(H[i]>max)
			  max=H[i];
	}
	for(i = 0; i < 256; i ++)
	{
		dc.MoveTo(i + 20, 220);
		dc.LineTo(i + 20, 220 - (int)(H[i] * 200 / max));

	}
}
