// ButtonEx.cpp : implementation file
//

#include "stdafx.h"
#include "ButtonEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonEx

CButtonEx::CButtonEx():BkColor(NULL),pSize(0,0)
{
	m_bIsPressed		= FALSE;
	m_bIsFocused		= FALSE;
	m_bIsDisabled		= FALSE;
	m_bMouseOnButton	= FALSE;
////////////////////////////////////////////////
//	FreeResources(FALSE);
	// Default type is "flat" button
	m_bIsFlat = TRUE;
	// Button will be tracked also if when the window is inactive (like Internet Explorer)
	//m_bAlwaysTrack = TRUE;

	// By default draw border in "flat" button 
	m_bDrawBorder = TRUE; 

	// By default icon is aligned horizontally
	//m_byAlign = ST_ALIGN_HORIZ; 

	// By default, for "flat" button, don't draw the focus rect
	m_bDrawFlatFocus = FALSE;

	// By default the button is not the default button
	m_bIsDefault = FALSE;
	// By default the button is not a checkbox
	m_bIsCheckBox = FALSE;

	// Do not draw as a transparent button
	m_bDrawTransparent = FALSE;









}

CButtonEx::~CButtonEx()
{
   

  // if(m_pFont)
  //   delete[] m_pFont;
   
   
   GdiplusShutdown(m_gdiplusToken);
}


BEGIN_MESSAGE_MAP(CButtonEx, CButton)
	//{{AFX_MSG_MAP(CButtonEx)
	ON_WM_MOUSEMOVE()
    ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
    ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover) 
	ON_WM_ERASEBKGND()
	ON_WM_DRAWITEM()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonEx message handlers

void CButtonEx::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
	ModifyStyle(0, BS_OWNERDRAW);

    ///////////////////////////////////////////////////////////////////////
    dStyleFlag = 0;
	rPt = sPoint;
	//dStyleFlag = ENABLE_EDGE;//;                                              //基本样式
	//dStyleFlag = ENABLE_BK_COLOR;
	//dStyleFlag = ENABLE_BK_COLOR | ENABLE_EDGE; 
	BkColor = GetSysColor(COLOR_WINDOW);
	EdgeColor = GetSysColor(COLOR_HIGHLIGHT);














    //
	MouseStatus = MOUSE_NORMAL;
	bIsMouseMoved = FALSE;
	//图片的显示模式
	PicShowMode = PIC_NORMAL;
	//得到控件的尺寸
    GetClientRect(&Rect);
	//ScreenToClient(Rect);
	CButton::GetWindowText(sContent);
	//显示的文本
    m_ToolTip.Create(this,TTS_ALWAYSTIP);
    m_ToolTip.AddTool(this,sContent);
 
    //显示的正常和焦点状态的图片
    m_pImage = NULL;
	m_fImage = NULL;
	//颜色初始化
	TextColor = GetSysColor(COLOR_BTNTEXT);






















	CButton::PreSubclassWindow();
}


void CButtonEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
   CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
   CRect itemRect;

////////////////////////////////////////////////////////////////////////
   // Normal button OR other button style ...
   m_bIsPressed = (lpDrawItemStruct->itemState & ODS_SELECTED);
   m_bIsFocused  = (lpDrawItemStruct->itemState & ODS_FOCUS);
   m_bIsDisabled = (lpDrawItemStruct->itemState & ODS_DISABLED);

   itemRect = lpDrawItemStruct->rcItem;
   pDC->SetBkMode(TRANSPARENT);
   

   ///////////////////////////////////////////////////////
   //绘背景
   PaintBk(pDC);
















	// Draw transparent
	if(m_bDrawTransparent)
	  PaintBk(pDC);
    else
	  DrawBkEdge(pDC);





   //if (m_bIsFlat == FALSE)
   {
		//if (m_bIsFocused || m_bIsDefault)
		{
           //画边
		   //DrawBkEdge(pDC);


			//CBrush br(EdgeColor);  
			//pDC->FrameRect(&itemRect, &br);
			//itemRect.DeflateRect(1, 1);
		} // if
	} // if



		//OnDrawBackground(pDC, &itemRect);
































   //先画背景
   //DrawBkEdge(pDC);
   //再画图片
   DrawActivePicture(pDC);
   //显示文本
   ShowControlText(pDC);
}

//设置文本的颜色
void CButtonEx::SetTextStyle(COLORREF tColor,int nHight,CString character)
{
   LOGFONT ft;
   CFont *pfont;

   if(tColor != NULL)
      TextColor = tColor;

   m_Font.DeleteObject();
/////////////////////////////////////////
   pfont = GetFont();
   pfont->GetLogFont(&ft);
////////////////////////////////////
   ft.lfHeight = nHight;
   memcpy(ft.lfFaceName,(LPSTR)(LPCSTR)character,sizeof(ft.lfFaceName));

   m_Font.CreateFontIndirect(&ft);

   tHight = nHight;
}

//显示文本
void CButtonEx::ShowControlText(CDC *pDC)
{
	COLORREF oldColor;
	int oldMode;
	CSize tSize;
	CRect tRect;
	//设置文本色
    oldColor = pDC->SetTextColor(TextColor);
    //选择文本字体	
    //m_font.CreatePointFont(TextSize,sCharacter);

    CFont *oldFont = pDC->SelectObject(&m_Font);
    //设置文本模式(透明)
	oldMode = pDC->SetBkMode(TRANSPARENT);
	
	//AlignFlag = TEXT_LEFT;
    //AlignFlag = TEXT_TOP;
    //AlignFlag = TEXT_RIGHT;
    //AlignFlag = TEXT_BUTTON;
//////////////////////////////////////////////////////
	GetTextExtentPoint32(pDC->GetSafeHdc(),sContent,sContent.GetLength(),&tSize);   
	//根据不同的选择来分配区间给文本
	switch(AlignFlag)
	{
	   case TEXT_LEFT:	   //左
		    tRect.top = (Rect.Height()-tSize.cy)/2;
			tRect.left = BORDER_VALUE_X;//(Rect.Width()-tSize.cx)/2;

			tRect.right = tRect.left + tSize.cx;
			tRect.bottom = tRect.top + tSize.cy;
		    break;
	   case TEXT_TOP:	   //上
		    tRect.top = Rect.top + BORDER_VALUE_Y;
			tRect.left = (Rect.Width()-tSize.cx)/2;

			tRect.right = tRect.left + tSize.cx;
			tRect.bottom = tRect.top + tSize.cy;		    
		    break;	
	   case TEXT_RIGHT:	   //右
		    tRect.top = (Rect.Height()-tSize.cy)/2;
			tRect.left = BORDER_VALUE_X + pSize.cx + BORDER_VALUE_X;

			tRect.right = tRect.right - tSize.cx;
			tRect.bottom = tRect.top + tSize.cy;		    
		    break;	
	
	   default:            //默认在下面

		   tRect.bottom = Rect.bottom - tHight/2;
		   tRect.left =  pRect.left + (pRect.Width()-tSize.cx)/2;

           tRect.top = tRect.bottom - tHight;
           tRect.right = Rect.right;
		    //tRect.top = pRect.bottom + tHight/2;
			//tRect.left = pRect.left + (pRect.Width()-tSize.cx)/2;

			//tRect.right = tRect.left + tSize.cx;
			//tRect.bottom = tRect.top + tSize.cy;

	}
////////////////////////////////////////////////////////////////////////////////
	pDC->DrawText(sContent,tRect,0);

    //还原颜色
	pDC->SetBkMode(oldMode);
	pDC->SetTextColor(oldColor);
    pDC->SelectObject(oldFont);
}


//手标移动时触发
void CButtonEx::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = m_hWnd;
	tme.dwFlags = TME_LEAVE|TME_HOVER;
	tme.dwHoverTime = 5;
	_TrackMouseEvent(&tme);


	CButton::OnMouseMove(nFlags, point);
}


//手标离开窗口时
LRESULT CButtonEx::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
   if(bIsMouseMoved == FALSE)
      return TRUE;

   bIsMouseMoved = FALSE;
   MouseStatus = MOUSE_LEAVE;


   dStyleFlag &= ~ENABLE_EDGE;


   Invalidate();

   return 1;
}

//手标在窗口上停留
LRESULT CButtonEx::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
  if(bIsMouseMoved == TRUE)
    return TRUE;

  bIsMouseMoved = TRUE;
  MouseStatus = MOUSE_FOCUS;
/////////////////////////////////////////
  dStyleFlag |= ENABLE_EDGE; //| ENABLE_BK_COLOR;

  //PaintFram(GetDC(),TRUE);
  Invalidate();

  return TRUE;
}











void CButtonEx::SetControlSource(PWCHAR lPath, PWCHAR lFocusPath, int Flag)
{
   //先加载正常的图片
   m_pImage = Gdiplus::Image::FromFile(lPath);        //也可以用此方法: Gdiplus::Image m_Image(DrawPic);
   //
   if(lFocusPath == NULL)
	 m_fImage = Gdiplus::Image::FromFile(lPath);
   else
	 m_fImage = Gdiplus::Image::FromFile(lFocusPath);


   if(m_pImage == NULL)//不能为空
	 return;

   pSize.cy = m_pImage->GetHeight();
   pSize.cx = m_pImage->GetWidth();

}

void CButtonEx::SetShowMode(int Mode)
{
   if((Mode >0 ) && (Mode < 4)) 
      PicShowMode = Mode;
}

BOOL CButtonEx::OnEraseBkgnd(CDC* pDC) 
{  
  	// Draw transparent
	//if(m_bDrawTransparent)
	//  PaintBk(pDC);
    //else
	//  DrawBkEdge(pDC);
   return TRUE;
   //return CButton::OnEraseBkgnd(pDC);
}

BOOL CButtonEx::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message== WM_LBUTTONDOWN ||pMsg->message== WM_LBUTTONUP ||pMsg->message== WM_MOUSEMOVE)
        m_ToolTip.RelayEvent(pMsg);

	return CButton::PreTranslateMessage(pMsg);
}

//设置控钮的背景模式
void CButtonEx::SetButtonBkStyle(BYTE nMode,CPoint ePt)
{
    dStyleFlag = nMode;

	rPt = ePt;
}

//设置背景色
void CButtonEx::SetBtnBkColor(COLORREF cbk, COLORREF cedge)
{
    if(cbk != NULL)
      BkColor = cbk;


	if(cedge != NULL)
      EdgeColor = cedge;
}


//画背景和边框的信息
void CButtonEx::DrawBkEdge(CDC *pDC)
{
  CBrush *oldBrush;
  CPen *oldPen;
  CPen m_Pen;
  CBrush m_Brush;
  CRect rt;

  rt = Rect;
  //rt.InflateRect(-10,-1);
//画刷部分显示
  if(dStyleFlag & ENABLE_BK_COLOR)    //如果选中有画背景的
  {
     m_Brush.CreateSolidBrush(BkColor);
     oldBrush = pDC->SelectObject(&m_Brush);    
  }
  else
  {
	pDC->SelectStockObject(NULL_BRUSH); 
	pDC->SetBkMode(TRANSPARENT);
  }
//画笔部分显示 
  if(dStyleFlag & ENABLE_EDGE)    //如果选中有画边框
    m_Pen.CreatePen(PS_SOLID,1,EdgeColor);
  else
    m_Pen.CreatePen(PS_NULL,0,EdgeColor); ;
  oldPen = pDC->SelectObject(&m_Pen);
  //
///////////////////////////////////////////////////////////////////////////////////////////////
//画一个圆角的短形

  pDC->RoundRect(rt,rPt);

///////////////////////////////////////////////////////////////////////////////////////////////
//完了退出前的动作
  pDC->SelectObject(oldPen);  //还原画笔
  m_Pen.DeleteObject();
  //还原画刷
  if(dStyleFlag & ENABLE_BK_COLOR)
  {
    pDC->SelectObject(oldBrush);
	m_Brush.DeleteObject();
  }
}

void CButtonEx::DrawActivePicture(CDC *pDC)
{
   Image *m_Image = NULL;
   //显示的图片的路径
   if(MouseStatus == MOUSE_FOCUS)
      m_Image = m_fImage;
   else
      m_Image = m_pImage;

   //加载要画的图片
   //   m_pImage = Gdiplus::Image::FromFile(DrawPic);        //也可以用此方法: Gdiplus::Image m_Image(DrawPic);
   if(m_pImage == NULL)//不能为空
	  return;

   ////////////////////////////////////////////////////////

   //得到GDI的绘图DC
   Gdiplus::Graphics graphics(pDC->m_hDC);
   PicShowMode = PIC_ZOOM;//
   //PicShowMode = PIC_FULL;
   //根据不同的值来画图片
   switch(PicShowMode)
   {
      case PIC_ZOOM:        //放大
           pRect.left = rPt.x/2;
		   pRect.top = rPt.y/2;
           ////
		   if((Rect.Width()-rPt.x) > (Rect.Height() - rPt.y))  //长比宽长
		   {
              pRect.bottom = Rect.bottom - rPt.y - tHight*2;
			  pRect.right = pRect.bottom;
		   }
		   else
		   {
			  pRect.right = Rect.right - rPt.x;
			  pRect.bottom = pRect.right;
		   }
		   break;
 	   case PIC_MIN:	   //缩小
	   case PIC_FULL:	   //全部
		   pRect = Rect;
		   break;	
	   default:            //默认
		   pRect.left = rPt.x/2;
		   pRect.top = rPt.y/2;
	
		   pRect.right = pRect.left + pSize.cx;
		   pRect.bottom = pRect.top + pSize.cy;
   }
   //从左上角画图标
   //graphics.DrawImage(&m_Image,Rect.top+BORDER_VALUE_Y,Rect.left+BORDER_VALUE_X);

   //图片自动缩放画
   graphics.DrawImage(m_Image,pRect.left,pRect.top,pRect.right,pRect.bottom);
   //m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, rectS.left, rectS.top, SRCCOPY);
}

HBRUSH CButtonEx::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here

	return (HBRUSH)::GetStockObject(NULL_BRUSH); 
}

//画框架
void CButtonEx::PaintFram(CDC *pDC, BOOL Flag)
{
  CBrush *oldBrush;
  CPen *oldPen;
  CPen m_Pen;
  CBrush m_Brush;
//画刷部分显示
  pDC->SelectStockObject(NULL_BRUSH); 
  pDC->SetBkMode(TRANSPARENT);
//画笔部分显示 
  if(Flag)    //如果选中有画边框
    m_Pen.CreatePen(PS_SOLID,1,EdgeColor);
  else
    m_Pen.CreatePen(PS_NULL,0,EdgeColor); ;
  oldPen = pDC->SelectObject(&m_Pen);
  //
///////////////////////////////////////////////////////////////////////////////////////////////
//画一个圆角的短形
  pDC->RoundRect(Rect,rPt);

///////////////////////////////////////////////////////////////////////////////////////////////
//完了退出前的动作
  pDC->SelectObject(oldPen);  //还原画笔
  m_Pen.DeleteObject();
  //还原画刷
  if(dStyleFlag & ENABLE_BK_COLOR)
  {
    pDC->SelectObject(oldBrush);
	m_Brush.DeleteObject();
  }

}

void CButtonEx::PaintBk(CDC *pDC)
{
	CClientDC clDC(GetParent());
	CRect rect;
	CRect rect1;

	GetClientRect(rect);

	GetWindowRect(rect1);
	GetParent()->ScreenToClient(rect1);
	if (m_dcBk.m_hDC == NULL)
	{
		m_dcBk.CreateCompatibleDC(&clDC);
		m_bmpBk.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
		m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
		m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
	} // if

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
}

//如果不是迤明背景就要画背景
void CButtonEx::DrawBackground(CDC *pDC, LPCRECT aRect)
{
  CBrush *oldBrush;
  CPen *oldPen;
  CPen m_Pen;
  CBrush m_Brush;
//画刷部分显示
  m_Brush.CreateSolidBrush(BkColor);
  oldBrush = pDC->SelectObject(&m_Brush);    

//画笔部分显示 
  m_Pen.CreatePen(PS_NULL,0,EdgeColor); ;
  oldPen = pDC->SelectObject(&m_Pen);
  //
///////////////////////////////////////////////////////////////////////////////////////////////
//画一个圆角的短形

  pDC->RoundRect(aRect,rPt);

///////////////////////////////////////////////////////////////////////////////////////////////
//完了退出前的动作
  pDC->SelectObject(oldPen);  //还原画笔
  m_Pen.DeleteObject();
  //还原画刷
  if(dStyleFlag & ENABLE_BK_COLOR)
  {
    pDC->SelectObject(oldBrush);
	m_Brush.DeleteObject();
  }
/*	COLORREF	crColor;

	if (m_bMouseOnButton || m_bIsPressed)
		crColor = m_crColors[BTNST_COLOR_BK_IN];
	else
	{
		if (m_bIsFocused)
			crColor = m_crColors[BTNST_COLOR_BK_FOCUS];
		else
			crColor = m_crColors[BTNST_COLOR_BK_OUT];
	} // else

	CBrush		brBackground(crColor);

	pDC->FillRect(pRect, &brBackground);
*/
}

