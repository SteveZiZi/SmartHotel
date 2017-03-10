// MyPictureEx.cpp : implementation file
//

#include "stdafx.h"
#include "MyPictureEx.h"


// CMyPictureEx

//IMPLEMENT_DYNAMIC(CMyPictureEx, CWnd)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
GdiplusStartupInput m_gdiplusStartupInput; 
ULONG_PTR m_gdiplusToken;
// CMyPictureEx
CMyPictureEx::CMyPictureEx()
{
	//边框的一些初始化
	FrameEnable = FALSE;
	nRound = 0;
	FrameSize = 1;
	m_cFrame = GetSysColor(COLOR_WINDOWFRAME);
	//背景色
	m_cBkgd = NULL;

	//图片
	m_pImage = NULL;
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
}

CMyPictureEx::~CMyPictureEx()
{
	GdiplusShutdown(m_gdiplusToken);
}


BEGIN_MESSAGE_MAP(CMyPictureEx, CWnd)
	//{{AFX_MSG_MAP(CMyPictureEx)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPictureEx message handlers

void CMyPictureEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	//首先获取画框
	GetClientRect(m_rcWnd);
	//第一步：画边框+背景
	DrawFrame(&dc);
	//第二步：绘图从这里开始
	DrawSourceImage(&dc);

	// Do not call CStatic::OnPaint() for painting messages
	//  dc.BitBlt(-10,-10,m_rcWnd.Width(),m_rcWnd.Height(),&MemDC,0,0,SRCCOPY);
}

BOOL CMyPictureEx::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class



	return CWnd::PreCreateWindow(cs);
}


void CMyPictureEx::SetFrameEnable(int nSize, COLORREF nColor,int Mode, BOOL Flag)
{
	FrameEnable = Flag;
	FrameSize = nSize;
	//=============================
	if(nColor != NULL)
		m_cFrame = nColor;
	//=============================
	nRound = Mode;

	Invalidate();
}



void CMyPictureEx::DrawFrame(CDC *pDC)
{
	CPen *m_Pen;
	CBrush *bh;
	//如果要画边框
	if(FrameEnable == TRUE)
		m_Pen = new CPen(PS_SOLID,FrameSize,m_cFrame);
	else
		m_Pen = new CPen(PS_NULL,FrameSize,m_cFrame);
	//========================================================
	//创建好画笔
	CPen *OldPen = pDC->SelectObject(m_Pen);

	//画背景
	if(m_cBkgd == NULL)
		bh = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	else
		bh = CBrush::FromHandle(::CreateSolidBrush(m_cBkgd));

	CBrush *OldBh = pDC->SelectObject(bh);
	//画边框
	if(!nRound)
		pDC->Rectangle(m_rcWnd);
	else
		pDC->RoundRect(m_rcWnd,CPoint(nRound,nRound));

	//pDC->FrameRect(m_rcWnd,CBrush::FromHandle(CreateSolidBrush(m_cFrame)));//绘制边框
	//==========================================
	pDC->SelectObject(OldPen);
	pDC->SelectObject(OldBh);
	m_Pen->DeleteObject();
	bh->DeleteObject();
}



void CMyPictureEx::SetBkColor(COLORREF nColor,BOOL Flag)
{
	m_cBkgd = nColor;
	if(Flag == TRUE)
		Invalidate();
}

void CMyPictureEx::SetImage(LPCSTR FileName,BOOL Flag)
{
	wchar_t wFileName[MAX_PATH];
	ZeroMemory(wFileName,sizeof(wchar_t)*MAX_PATH);
	MultiByteToWideChar(CP_ACP,0,FileName,-1,wFileName,MAX_PATH);
	Gdiplus::Image *mTempImage = Gdiplus::Image::FromFile(wFileName);
	if (m_pImage != NULL)	
	{	delete m_pImage;	m_pImage = NULL;	}
	//////////////////////////////////////////////////////////////
	m_pImage =  mTempImage;
	if(Flag == TRUE)
		Invalidate();

}


void CMyPictureEx::DrawSourceImage(CDC *pDC)
{
	CRect rt;
	Gdiplus::Graphics graphics(pDC->m_hDC);
	rt.left = m_rcWnd.left + FrameSize + nRound/2;
	rt.top = m_rcWnd.top + FrameSize + nRound/2;
	rt.right = m_rcWnd.right - FrameSize - nRound/2;
	rt.bottom = m_rcWnd.bottom - FrameSize - nRound/2;

	graphics.DrawImage(m_pImage,rt.left,rt.top,rt.Width(),rt.Height());
}


