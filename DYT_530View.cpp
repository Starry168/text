// DYT_530View.cpp : implementation of the CDYT_530View class
//

#include "stdafx.h"
#include "DYT_530.h"

#include "DYT_530Doc.h"
#include "DYT_530View.h"
#include "DialogHistergram.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDYT_530View

IMPLEMENT_DYNCREATE(CDYT_530View, CScrollView)

BEGIN_MESSAGE_MAP(CDYT_530View, CScrollView)
	//{{AFX_MSG_MAP(CDYT_530View)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(GRAY, OnGRAY)
	ON_UPDATE_COMMAND_UI(GRAY, OnUpdateGRAY)
	ON_UPDATE_COMMAND_UI(ID_Histogram, OnUpdateHistogram)
	ON_COMMAND(ID_Histogram, OnHistogram)
	ON_COMMAND(ID_LINEAR, OnLinear)
	ON_UPDATE_COMMAND_UI(ID_LINEAR, OnUpdateLinear)
	ON_COMMAND(ID_EQUALIZE, OnEqualize)
	ON_UPDATE_COMMAND_UI(ID_EQUALIZE, OnUpdateEqualize)
	ON_COMMAND(ID_Fourier, OnFourier)
	ON_UPDATE_COMMAND_UI(ID_Fourier, OnUpdateFourier)
	ON_COMMAND(ID_Ifourier, OnIfourier)
	ON_UPDATE_COMMAND_UI(ID_Ifourier, OnUpdateIfourier)
	ON_COMMAND(ID_Fft, OnFft)
	ON_UPDATE_COMMAND_UI(ID_Fft, OnUpdateFft)
	ON_COMMAND(ID_Ifft, OnIfft)
	ON_UPDATE_COMMAND_UI(ID_Ifft, OnUpdateIfft)
	ON_COMMAND(ID_AverageFilter, OnAverageFilter)
	ON_UPDATE_COMMAND_UI(ID_AverageFilter, OnUpdateAverageFilter)
	ON_COMMAND(ID_MediumFilter, OnMediumFilter)
	ON_UPDATE_COMMAND_UI(ID_MediumFilter, OnUpdateMediumFilter)
	ON_COMMAND(ID_GradSharp, OnGradSharp)
	ON_UPDATE_COMMAND_UI(ID_GradSharp, OnUpdateGradSharp)
	ON_COMMAND(ID_RaplasSharp, OnRaplasSharp)
	ON_UPDATE_COMMAND_UI(ID_RaplasSharp, OnUpdateRaplasSharp)
	ON_COMMAND(ID_D, OnD)
	ON_UPDATE_COMMAND_UI(ID_D, OnUpdateD)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDYT_530View construction/destruction

CDYT_530View::CDYT_530View()
{
	// TODO: add construction code here

}

CDYT_530View::~CDYT_530View()
{
}

BOOL CDYT_530View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDYT_530View drawing
extern BITMAPINFO *lpBitsInfo;
extern BITMAPINFO *lpDIB_FFT;
extern BITMAPINFO *lpDIB_IFFT;
void CDYT_530View::OnDraw(CDC* pDC)
{
	CDYT_530Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

    if(NULL==lpBitsInfo)
		return;

	LPVOID lpBits = 
(LPVOID)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	RGBQUAD pal[2];
	pal[0].rgbRed=255;
	pal[0].rgbGreen=0;
	pal[0].rgbBlue=0;
	pal[0].rgbReserved=0;
	pal[1].rgbRed=0;
	pal[1].rgbGreen=0;
	pal[1].rgbBlue=0;
	pal[1].rgbReserved=0;


	StretchDIBits(
	pDC->GetSafeHdc(),
	0,0,
	lpBitsInfo->bmiHeader.biWidth,
	lpBitsInfo->bmiHeader.biHeight,
	0,0,
	lpBitsInfo->bmiHeader.biWidth,
	lpBitsInfo->bmiHeader.biHeight,
	lpBits,
	lpBitsInfo,
	DIB_RGB_COLORS,
	SRCCOPY);

		if (lpDIB_FFT)
	{
		lpBits = (LPVOID)&lpDIB_FFT->bmiColors[lpDIB_FFT->bmiHeader.biClrUsed];
		StretchDIBits( 
			pDC->GetSafeHdc(),
			600,0,
			lpDIB_FFT->bmiHeader.biWidth,
			lpDIB_FFT->bmiHeader.biHeight,
			0,0,
			lpDIB_FFT->bmiHeader.biWidth,
			lpDIB_FFT->bmiHeader.biHeight,
			lpBits,
			lpDIB_FFT, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY);
	}

	if (lpDIB_IFFT)
	{
		lpBits = (LPVOID)&lpDIB_IFFT->bmiColors[lpDIB_IFFT->bmiHeader.biClrUsed];
		StretchDIBits( 
			pDC->GetSafeHdc(),
			0,600,
			lpDIB_IFFT->bmiHeader.biWidth,
			lpDIB_IFFT->bmiHeader.biHeight,
			0,0,
			lpDIB_IFFT->bmiHeader.biWidth,
			lpDIB_IFFT->bmiHeader.biHeight,
			lpBits,
			lpDIB_IFFT, // bitmap data 
			DIB_RGB_COLORS,
			SRCCOPY);
	}

}

void CDYT_530View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CDYT_530View printing

BOOL CDYT_530View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDYT_530View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDYT_530View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDYT_530View diagnostics

#ifdef _DEBUG
void CDYT_530View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDYT_530View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDYT_530Doc* CDYT_530View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDYT_530Doc)));
	return (CDYT_530Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDYT_530View message handlers

void gray();

//显示位图像素点的RGB值
void CDYT_530View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		void pixel(int i,int j);
	// TODO: Add your message handler code here and/or call default
	pixel(point.y,point.x);
	CScrollView::OnLButtonDown(nFlags, point);

}

void CDYT_530View::OnGRAY() 
{
	// TODO: Add your command handler code here
		 gray();
	 Invalidate();
}



void CDYT_530View::OnUpdateGRAY(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount ==24);

}
//直方图
void CDYT_530View::OnHistogram() 
{
	// TODO: Add your command handler code here
	CDialogHistergram dlg;
	dlg.DoModal();
}
void CDYT_530View::OnUpdateHistogram(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount ==8);
}

void LinerTrans(float,float);
//线性
void CDYT_530View::OnLinear() 
{
	// TODO: Add your command handler code here
	LinerTrans(2,-100);
	Invalidate();
	
}

void CDYT_530View::OnUpdateLinear(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount ==8);
	
}
//均衡化
void Equalize();
void CDYT_530View::OnEqualize() 
{
	// TODO: Add your command handler code here
	Equalize();
	Invalidate();
	
}

void CDYT_530View::OnUpdateEqualize(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount ==8);
	
}

//傅里叶变换
void Fourier();
void CDYT_530View::OnFourier() 
{
	// TODO: Add your command handler code here
	Fourier();
	Invalidate();
}

void CDYT_530View::OnUpdateFourier(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount == 8);
}

//I
void IFourier();
void CDYT_530View::OnIfourier() 
{
	// TODO: Add your command handler code here
	IFourier();
	Invalidate();
}

void CDYT_530View::OnUpdateIfourier(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount == 8);
}

//FF
void FFourier();
void CDYT_530View::OnFft() 
{
	// TODO: Add your command handler code here
		if (lpDIB_FFT)
     	free(lpDIB_FFT);
 
	FFourier();
	Invalidate();

}

void CDYT_530View::OnUpdateFft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && lpBitsInfo->bmiHeader.biBitCount == 8);
}

//IFF
void IFFourier();
void CDYT_530View::OnIfft() 
{
	// TODO: Add your command handler code here
	if (lpDIB_IFFT)
		free(lpDIB_IFFT);

	IFFourier();
	Invalidate();
}

void CDYT_530View::OnUpdateIfft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpDIB_FFT != NULL);
}

//均值变换
void AverageFilter();
void CDYT_530View::OnAverageFilter() 
{
	// TODO: Add your command handler code here
	AverageFilter();
	Invalidate();
}

void CDYT_530View::OnUpdateAverageFilter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

//中值变换
void MediumFilter(); 

void CDYT_530View::OnMediumFilter() 
{
	// TODO: Add your command handler code here
	MediumFilter();
	Invalidate();
}

void CDYT_530View::OnUpdateMediumFilter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

//梯度变换
void GradSharp();
void CDYT_530View::OnGradSharp() 
{
	// TODO: Add your command handler code here
	GradSharp();
	Invalidate();
}

void CDYT_530View::OnUpdateGradSharp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

//拉普拉斯变换
void RaplasSharp();
void CDYT_530View::OnRaplasSharp() 
{
	// TODO: Add your command handler code here
	RaplasSharp();
	Invalidate();
}

void CDYT_530View::OnUpdateRaplasSharp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}

//理想低-高通滤波
void Ideal_Filter_FFT(int D);
void CDYT_530View::OnD() 
{
	// TODO: Add your command handler code here
	Ideal_Filter_FFT(10);
	Invalidate();
}

void CDYT_530View::OnUpdateD(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL);
}
