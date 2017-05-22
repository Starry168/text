#include "stdafx.h"
#include <complex>
using namespace std;
#define PI 3.1415926535

BITMAPINFO* lpDIB_FFT = NULL; 
BITMAPINFO* lpDIB_IFFT = NULL;
BITMAPINFO *lpBitsInfo=NULL;

BOOL LoadBmpFile(char*BmpFileName)
{
	FILE* fp;
	if(NULL == (fp=fopen(BmpFileName,"rb")))
		return FALSE;

	BITMAPFILEHEADER bf;//文件头
	BITMAPINFOHEADER bi;//信息头

	fread(&bf,sizeof(BITMAPFILEHEADER),1,fp);
	fread(&bi,sizeof(BITMAPINFOHEADER),1,fp);

//调色板位图
	DWORD NumColors;
if(bi.biClrUsed !=0)
NumColors=bi.biClrUsed;
else{
	switch(bi.biBitCount){
     case 1:
        NumColors=2;
		break;
     case 4:
        NumColors=16;
        break;
     case 8:
        NumColors=256;
        break;
     case 24:
        NumColors=0;
		break;
	}
}

//每一行字节数必须是4的倍数
   DWORD LineBytes=(bi.biWidth*bi.biBitCount+31)/32*4; 
   LONG size=40+4*NumColors+ LineBytes*bi.biHeight;
   if(NULL==(lpBitsInfo=(BITMAPINFO*)malloc(size)))
      return FALSE;
   fseek(fp,14,SEEK_SET);
   fread((char*)lpBitsInfo,size,1,fp);
   lpBitsInfo->bmiHeader.biClrUsed = NumColors;
   fclose(fp);

/*	LONG size = 40 +bi.biWidth * bi.biHeight * 3;
	if(NULL==(lpBitsInfo=(BITMAPINFO*)malloc(size)))
		return FALSE;

	fseek(fp,14,SEEK_SET);//从文件头往下走一个信息头的大小
	fread((char*)lpBitsInfo,size,1,fp);
	*/

	return TRUE;
}

void gray()
{
	int w = lpBitsInfo->bmiHeader.biWidth;
    int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int new_LineBytes =(w*8+31)/32*4;
	LONG size = 40 + 1024 + new_LineBytes * h;
	BITMAPINFO*new_lpBitsInfo=(BITMAPINFO*)malloc(size);

	memcpy(new_lpBitsInfo,lpBitsInfo,40);
    new_lpBitsInfo->bmiHeader.biBitCount =8;
	new_lpBitsInfo->bmiHeader.biClrUsed =256;

	int i,j;
	for(i=0;i<256;i++)
	{
		new_lpBitsInfo->bmiColors[i].rgbRed=i;
		new_lpBitsInfo->bmiColors[i].rgbGreen=i;
	    new_lpBitsInfo->bmiColors[i].rgbBlue=i;
		new_lpBitsInfo->bmiColors[i].rgbReserved=0;

	}
    
	BYTE* new_lpBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];

	BYTE *R,*G,*B,avg,*pixel;
	

	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			B=lpBits+LineBytes*(h-1 -i) + j*3;
			G=B+1;
			R=G+1;
			avg=(*R + *G + *B)/3;

			pixel = new_lpBits + new_LineBytes * (h - 1 - i) + j;
			*pixel=avg;


		}
	}

     free(lpBitsInfo);
	 lpBitsInfo=new_lpBitsInfo;

}


void pixel(int i,int j)
{


  int w = lpBitsInfo->bmiHeader.biWidth;
  int h = lpBitsInfo->bmiHeader.biHeight;
  int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
  BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	if(i>h||j>w)
		return;
	
  BYTE* pixel,bv;
  int r,g,b;
  char str[255];


switch(lpBitsInfo->bmiHeader.biBitCount)
{ 
case 8:
	pixel = lpBits + LineBytes * (h - 1 - i) + j;
    r = lpBitsInfo->bmiColors[*pixel].rgbRed;
	g = lpBitsInfo->bmiColors[*pixel].rgbGreen;
	b = lpBitsInfo->bmiColors[*pixel].rgbBlue;
    sprintf(str,"RGB(%d,%d,%d)",r,g,b);
	break;
case 24:
	pixel = lpBits + LineBytes * (h - 1 - i) + j*3;
	b= *pixel;
	g= *(pixel+1);
	r= *(pixel+2);
    sprintf(str,"RGB(%d,%d,%d)",r,g,b);
	break;
case 1:
    bv=*(lpBits + LineBytes * (h - 1 - i) + j/8)&(1<<(7-j%8));
	
	if(0==bv)
		strcpy(str,"背景点");
	else
		strcpy(str,"前景点");
	break;
case 4:
	pixel=lpBits + LineBytes * (h - 1 - i) + j/2;
	if(0==j%2)
		*pixel=*pixel>>4;
	else
        *pixel=*pixel%15;

    r = lpBitsInfo->bmiColors[*pixel].rgbRed;
	g = lpBitsInfo->bmiColors[*pixel].rgbGreen;
	b = lpBitsInfo->bmiColors[*pixel].rgbBlue;
    sprintf(str,"RGB(%d,%d,%d)",r,g,b);
	break;
}
AfxMessageBox(str);
}

DWORD H[256];
void Histogram() //统计各灰度级的像素个数
{
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
    int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
	int i,j;
	BYTE* pixel;
	for(i=0;i<256;i++)
      H[i]=0;
	  for(i=0;i<h;i++)
	  {
		  for(j=0;j<w;j++)
		  {
			  pixel = lpBits + LineBytes * (h - 1 - i) + j;
		  	  H[*pixel] ++;
		  }
	  }

}

void LinerTrans(float a,float b)
{
	
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	int i,j;
	BYTE* pixel;
	float temp;
    for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;  // 指向像素点(i,j)的指针
			temp = a * (*pixel) + b;  // 线性变换
			if(temp>255)
			{
                *pixel=255;
			}
			else if(temp<0)
			{
				*pixel=0;
			}
			else 
			{
				*pixel=(BYTE) (temp + 0.5);
			}
		}
	}

}

void Equalize()
{
	int i,j;
	BYTE* pixel;
	DWORD temp;
    int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	BYTE Map[256];
	Histogram();
	for(i=0;i<256;i++)
	{
		temp=0;
		for(j=0;j<=i;j++)
			temp+=H[j];

        Map[i] = (BYTE) (temp * 255 / w / h);
	}
	for (i=0;i<h;i++)
	{
		for (j=0;j<w;j++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;
			// 计算新的灰度值
			*pixel = Map[*pixel];
		}
	}

}

//一维傅里叶变换
void FT(complex<double>*TD,complex<double>*FD,int m) //TD指向时域数组的指针,FD指向频域数组的指针
{
	int u,x;
	double angle;
	for(u=0;u<m;u++)
	{
		FD[u]=0;  //初始化数组值
		for(x=0;x<m;x++)
		{
			angle = -2*PI*u*x/m;// xita
			FD[u]+= TD[x]*complex<double>(cos(angle),sin(angle));

		}
        FD[u]/=m;

	}
}

void IFT(complex<double>*FD,complex<double>*TD,int m)
{
	int u,x;
	double angle;
	for(x=0;x<m;x++)
	{
		TD[x]=0;
		for(u=0;u<m;u++)
		{
	     	angle=2*PI*u*x/m;
		    TD[x]+=FD[u]*complex<double>(cos(angle),sin(angle));
	
		}
	}
}

complex<double>*gFD =NULL;
void Fourier()
{	
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
    
	int new_LineBytes=(w * 8 + 31)/32 * 4;
	LONG size=40+1024+new_LineBytes*h;

	complex<double>*TD= new complex<double>[w*h];
	complex<double>*FD= new complex<double>[w*h];

	int i, j;
	BYTE* pixel;
	for (i = 0; i < h; i ++)
	{
		for (j = 0; j < w; j++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;
			TD[j + w * i] = complex<double>(*pixel * pow(-1, i + j), 0);
		}
	}
	for(i=0;i<h;i++)
	    FT(&TD[w*i],&FD[w*i],w);
	
    for(i=0;i<h;i++)
		for(j=0;j<w;j++)
			TD[i+h*j]=FD[j+w*i];

	for(i=0;i<w;i++)
		FT(&TD[i*h],&FD[i*h],h);

	BITMAPINFO*lpDIB_FT=(LPBITMAPINFO)malloc(size);
	   if(NULL==lpDIB_FT)
		   return;
		   memcpy(lpDIB_FT,lpBitsInfo,size);

	   lpBits=(BYTE*)&lpDIB_FT->bmiColors[lpDIB_FT->bmiHeader.biClrUsed];

	double temp;
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;
			temp=sqrt(FD[j*h+i].real()*FD[j*h+i].real()+FD[j*h+i].imag()*FD[j*h+i].imag())*2000;
			if(temp>255)
				temp=255;
			*pixel=(BYTE)(temp);

		}
	}
	delete TD;
	gFD=FD;

	free(lpBitsInfo);
    lpBitsInfo=lpDIB_FT;    
}

void IFourier()
{	
	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];
    
	int new_LineBytes=(w * 8 + 31)/32 * 4;
	LONG size=40+1024+new_LineBytes*h;

	complex<double>*TD= new complex<double>[w*h];
	complex<double>*FD= new complex<double>[w*h];

	int i, j;
	for (i = 0; i < h; i ++)
		for (j = 0; j < w; j++)
			FD[ w * i+j] =gFD[i+h*j];

	for(i=0;i<h;i++)
	    IFT(&FD[w*i],&TD[w*i],w);
	
    for(i=0;i<h;i++)
		for(j=0;j<w;j++)
			FD[i+h*j]=TD[j+w*i];

	for(i=0;i<w;i++)
		IFT(&FD[i*h],&TD[i*h],h);

	BITMAPINFO*lpDIB_IFT=(LPBITMAPINFO)malloc(size);
	   if(NULL==lpDIB_IFT)
		   return;
		   memcpy(lpDIB_IFT,lpBitsInfo,size);

	   lpBits=(BYTE*)&lpDIB_IFT->bmiColors[lpDIB_IFT->bmiHeader.biClrUsed];

	BYTE* pixel;
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			pixel = lpBits + LineBytes * (h - 1 - i) + j;
			*pixel=(BYTE)(TD[j*h+i].real()/pow(-1,i+j));

		}
	}
	delete TD;
	delete FD;
	delete gFD;

	free(lpBitsInfo);
    lpBitsInfo=lpDIB_IFT;    
}


void FFT(complex<double> * TD, complex<double> * FD, int r)  //一维傅里叶变换
{
	// 计算付立叶变换点数
	LONG count = 1 << r;
	// 计算加权系数
	int i;
	double angle;
	complex<double>* W = new complex<double>[count / 2];
	for(i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	// 将时域点写入X1
	complex<double>* X1 = new complex<double>[count];
	memcpy(X1, TD, sizeof(complex<double>) * count);
	
	// 采用蝶形算法进行快速付立叶变换，输出为频域值X2
	complex<double>* X2 = new complex<double>[count]; 

	int k,j,p,size;
	complex<double>* temp;
	for (k = 0; k < r; k++)
	{
		for (j = 0; j < 1 << k; j++)
		{
			size = 1 << (r-k);
			for (i = 0; i < size/2; i++)
			{
				p = j * size;
				X2[i + p] = X1[i + p] + X1[i + p + size/2];
				X2[i + p + size/2] = (X1[i + p] - X1[i + p + size/2]) * W[i * (1<<k)];
			}
		}
		temp  = X1;
		X1 = X2;
		X2 = temp;
	}
	
	// 重新排序（码位倒序排列）
	for (j = 0; j < count; j++)
	{
		p = 0;
		for (i = 0; i < r; i++)
		{
			if (j & (1<<i))
			{
				p += 1<<(r-i-1);
			}
		}
		FD[j]=X1[p];
		FD[j] /= count;
	}
	
	// 释放内存
	delete W;
	delete X1;
	delete X2;
}


void FFourier()
{
	
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE* lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];


	int FFT_w = 1;
	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}


	int FFT_h = 1;

	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}

	// 分配内存
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	BYTE* pixel;
	
	for(i = 0; i < FFT_h; i++)  // 行
	{
		for(j = 0; j < FFT_w; j++)  // 列
		{
			// 指向DIB第i行，第j个象素的指针
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// 给时域赋值
			TD[j + FFT_w * i] = complex<double>(*pixel* pow(-1,i+j), 0);
		}
	}
	
	for(i = 0; i < FFT_h; i++)
	{
		// 对y方向进行快速付立叶变换
		FFT(&TD[FFT_w * i], &FD[FFT_w * i], wp);
	}
	
	// 保存中间变换结果
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			TD[i + FFT_h * j] = FD[j + FFT_w * i];
		}
	}
	
	for(i = 0; i < FFT_w; i++)
	{
		// 对x方向进行快速付立叶变换
		FFT(&TD[i * FFT_h], &FD[i * FFT_h], hp);
	}

	// 删除临时变量
	delete TD;

	//生成频谱图像
	//为频域图像分配内存
	LONG size = 40 + 1024 + LineBytes * height;
	lpDIB_FFT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_FFT)
		return;
	memcpy(lpDIB_FFT, lpBitsInfo, size);

	//指向频域图像数据指针
	lpBits = (BYTE*)&lpDIB_FFT->bmiColors[lpDIB_FFT->bmiHeader.biClrUsed];

	double temp;
	for(i = 0; i < FFT_h; i++) // 行
	{
		for(j = 0; j < FFT_w; j++) // 列
		{
			// 计算频谱幅度
			temp = sqrt(FD[j * FFT_h + i].real() * FD[j * FFT_h + i].real() + 
				        FD[j * FFT_h + i].imag() * FD[j * FFT_h + i].imag()) *2000;
			
			// 判断是否超过255
			if (temp > 255)
			{
				// 对于超过的，直接设置为255
				temp = 255;
			}
			
			pixel = lpBits + LineBytes * (height - 1 - i) + j;

			// 更新源图像
			*pixel = (BYTE)(temp);
		}
	}

	gFD=FD;

}


void IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	// 付立叶变换点数
	LONG	count;
	// 计算付立叶变换点数
	count = 1 << r;

	// 分配运算所需存储器
	complex<double> * X = new complex<double>[count];
	// 将频域点写入X
	memcpy(X, FD, sizeof(complex<double>) * count);
	
	// 求共轭
	for(int i = 0; i < count; i++)
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	
	// 调用快速付立叶变换
	FFT(X, TD, r);
	
	// 求时域点的共轭
	for(i = 0; i < count; i++)
		TD[i] = complex<double> (TD[i].real() * count, -TD[i].imag() * count);
	
	// 释放内存
	delete X;
}

void IFFourier()
{
	//图像的宽度和高度
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;


	int FFT_w = 1;

	int wp = 0;
	while(FFT_w * 2 <= width)
	{
		FFT_w *= 2;
		wp ++;
	}


	int FFT_h = 1;

	int hp = 0;
	while(FFT_h * 2 <= height)
	{
		FFT_h *= 2;
		hp ++;
	}

	// 分配内存
	complex<double>* TD = new complex<double>[FFT_w * FFT_h];
	complex<double>* FD = new complex<double>[FFT_w * FFT_h];
	
	int i, j;
	for(i = 0; i < FFT_h; i++)  // 行
		for(j = 0; j < FFT_w; j++)  // 列
			FD[j + FFT_w * i] = gFD[i + FFT_h*j];
	

	for(i = 0; i < FFT_h; i++)
		IFFT(&FD[FFT_w * i], &TD[FFT_w * i], wp);
	

	for(i = 0; i < FFT_h; i++)
		for(j = 0; j < FFT_w; j++)
			FD[i + FFT_h * j] = TD[j + FFT_w * i];
	

	for(i = 0; i < FFT_w; i++)
		IFFT(&FD[i * FFT_h], &TD[i * FFT_h], hp);


	LONG size = 40 + 1024 + LineBytes * height;

	lpDIB_IFFT = (LPBITMAPINFO) malloc(size);
	if (NULL == lpDIB_IFFT)
		return;
	memcpy(lpDIB_IFFT, lpBitsInfo, size);

	BYTE* lpBits = (BYTE*)&lpDIB_IFFT->bmiColors[lpDIB_IFFT->bmiHeader.biClrUsed];
	BYTE* pixel;
	double temp;
	for(i = 0; i < FFT_h; i++) 
	{
		for(j = 0; j < FFT_w; j++) 
		{
			pixel = lpBits + LineBytes * (height - 1 - i) + j;
			temp= (TD[j*FFT_h + i].real() / pow(-1, i+j));
			if (temp < 0)
				temp = 0;
			else if (temp >255)
				temp = 255;
			*pixel = (BYTE)temp;
		}
	}


	delete FD;
	delete TD;
	//delete gFD;
}



void Template(int* Array, float coef)
{

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	BITMAPINFO* new_lpBitsInfo;
	LONG size = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + h * LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return;

	memcpy(new_lpBitsInfo, lpBitsInfo, size);

	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];

	int i, j, k, l;
	BYTE *pixel, *new_pixel;
	float result;

	for(i = 1; i < h - 1; i++)
	{

		for(j = 1; j < w - 1; j++)
		{

			new_pixel = lpNewBits + LineBytes * (h - 1 - i) + j;
			result = 0;

			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{

					pixel = lpBits + LineBytes * (h - i - k) + j - 1 + l;

					result += (*pixel) * Array[k * 3 + l];
				}
			}

			result *= coef;
			if (result < 0)
				*new_pixel = 0;
			else if(result > 255)
				*new_pixel = 255;
			else
				*new_pixel = (BYTE) (result + 0.5);
		}
	}
	free(lpBitsInfo);
	lpBitsInfo = new_lpBitsInfo;
}

void AverageFilter() 
{
	int Array[9]; 

	Array[0] = 1;	Array[1] = 1;	Array[2] = 1;
	Array[3] = 1;	Array[4] = 1;	Array[5] = 1;
	Array[6] = 1;	Array[7] = 1;	Array[8] = 1;
	Template(Array, (float)1/9);

}
BYTE WINAPI GetMedianNum(BYTE* Array)
{
	int i,j;
	BYTE temp;

	for (j = 0; j < 9 - 1; j ++)
	{
		for (i = 0; i < 9 - j - 1; i ++)
		{
			if (Array[i] > Array[i + 1])
			{
				temp = Array[i];
				Array[i] = Array[i + 1];
				Array[i + 1] = temp;
			}
		}
	}

	return Array[4];
}

void MediumFilter() 
{

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;

	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;

	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	BITMAPINFO* new_lpBitsInfo;
	LONG size = sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + h * LineBytes;
	if (NULL == (new_lpBitsInfo = (LPBITMAPINFO) malloc(size)))
		return;

	memcpy(new_lpBitsInfo, lpBitsInfo, size);

	BYTE* lpNewBits = (BYTE*)&new_lpBitsInfo->bmiColors[new_lpBitsInfo->bmiHeader.biClrUsed];

	int i, j, k, l;
	BYTE *pixel, *new_pixel;
	BYTE Value[9]; 

	for(i = 1; i < h - 1; i++)
	{

		for(j = 1; j < w - 1; j++)
		{

			new_pixel = lpNewBits + LineBytes * (h - 1 - i) + j;

			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{

					pixel = lpBits + LineBytes * (h - i - k) + j - 1 + l;
					Value[k * 3 + l] = *pixel;
				}
			}

			*new_pixel = GetMedianNum(Value);
		}
	}
	free(lpBitsInfo);
	lpBitsInfo = new_lpBitsInfo;
}

void GradSharp() 
{

	int w = lpBitsInfo->bmiHeader.biWidth;
	int h = lpBitsInfo->bmiHeader.biHeight;
	int LineBytes = (w * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	BYTE *lpBits = (BYTE*)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	BYTE *lpSrc, *lpSrc1, *lpSrc2;
	int i, j;
	BYTE temp;

	for(i = 0; i < h-1; i++)
	{

		for(j = 0; j < w-1; j++)
		{

			lpSrc  = (unsigned char*)lpBits + LineBytes * (h - 1 - i) + j;
			lpSrc1 = (unsigned char*)lpBits + LineBytes * (h - 2 - i) + j;
			lpSrc2 = (unsigned char*)lpBits + LineBytes * (h - 1 - i) + j + 1;
			temp = abs((*lpSrc)-(*lpSrc1)) + abs((*lpSrc)-(*lpSrc2));
			if (temp > 255)
				*lpSrc = 255;
			else
				*lpSrc = temp;
		}
	}
}

void RaplasSharp() 
{
	int Array[9]; //3x3模板

	Array[0] = -1;	Array[1] = -1;	Array[2] = -1;
	Array[3] = -1;	Array[4] = 9;	Array[5] = -1;
	Array[6] = -1;	Array[7] = -1;	Array[8] = -1;
	Template(Array, (float)1);
}


//高通、低通
void Ideal_Filter_FFT(int D)
{
	//图像的宽度和高度
	int width = lpBitsInfo->bmiHeader.biWidth;
	int height = lpBitsInfo->bmiHeader.biHeight;
	int FFT_w = 1;
	while(FFT_w * 2 <= width)
		FFT_w *= 2;
	int FFT_h = 1;
	while(FFT_h * 2 <= height)
		FFT_h *= 2;

	//备份原始频域数据
	complex<double>* origin_FD = new complex<double>[FFT_w * FFT_h];
	for(int n = 0; n < FFT_w * FFT_h; n++)
		origin_FD[n] = gFD[n];

	//频率滤波（理想高/低通滤波）
	int i, j;
	double dis;
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			dis = sqrt((i - FFT_h/2) * (i - FFT_h/2) + (j - FFT_w/2)  * (j - FFT_w/2) + 1);
			if (D > 0) //低通
			{
				if (dis > D) 
					gFD[i * FFT_h + j] = 0; //理想低通，截断高频
			}
			else { //高通
				if (dis <= -D) 
					gFD[i * FFT_h + j] = 0; //理想高通，截断低频
			}
		}
	}

	//生成新的频谱图像
	int LineBytes = (width * lpBitsInfo->bmiHeader.biBitCount + 31)/32 * 4;
	LONG size = 40 + 1024 + LineBytes * height;
	BITMAPINFO* new_lpDIB_FFT = (LPBITMAPINFO) malloc(size);
	memcpy(new_lpDIB_FFT, lpDIB_FFT, size);
	BYTE* lpBits = (BYTE*)&new_lpDIB_FFT->bmiColors[new_lpDIB_FFT->bmiHeader.biClrUsed];
	double temp;
	BYTE* pixel;
	for(i = 0; i < FFT_h; i++)
	{
		for(j = 0; j < FFT_w; j++)
		{
			temp = sqrt(gFD[j * FFT_h + i].real() * gFD[j * FFT_h + i].real() + 
				        gFD[j * FFT_h + i].imag() * gFD[j * FFT_h + i].imag())*2000 ;
			if (temp > 255)
				temp = 255;
			pixel = lpBits + LineBytes * (height - 1 - i) + j;
			*pixel = (BYTE)(temp);
		}
	}
	//释放原频谱图像
	if (lpDIB_FFT)
		free(lpDIB_FFT);
	//更新新的频谱图像
	lpDIB_FFT = new_lpDIB_FFT;

	//傅里叶反变换
	IFourier();

	//恢复到原始频域数据
	delete gFD;
	gFD = origin_FD;
}
