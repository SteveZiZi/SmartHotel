// MyListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
//#include "clistctrlreportstyledemo.h"
#include "MyListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
GdiplusStartupInput m_gdiplusStartupInput; 
ULONG_PTR m_gdiplusToken;
// CMyListCtrlEx

CMyListCtrlEx::CMyListCtrlEx()
{
	m_crWindow = ::GetSysColor(COLOR_WINDOW);;
	m_crWindowText = ::GetSysColor(COLOR_WINDOWTEXT);
	m_crGrayText = ::GetSysColor(COLOR_GRAYTEXT);


	m_ItemHight = 0;


	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
}

CMyListCtrlEx::~CMyListCtrlEx()
{
////////////////////////////////////////////////////////////////////////////
	int i = 0;
	LIST_DATA_INFO *m_pListItem;
	while(1)
	{
	   m_pListItem = (LIST_DATA_INFO *)CListCtrl::GetItemData(i);
	   if(m_pListItem == NULL)
		 break;
	   delete[] (LIST_DATA_INFO *)m_pListItem;
	   i++;
	}
	GdiplusShutdown(m_gdiplusToken);
}


BEGIN_MESSAGE_MAP(CMyListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrlEx)
	ON_WM_MEASUREITEM_REFLECT()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrlEx message handlers

void CMyListCtrlEx::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

//设定为自绘风格
	CListCtrl::ModifyStyle(0,LVS_OWNERDRAWFIXED);  //默认的是列表风格
    CListCtrl::ModifyStyle(0,LVS_REPORT);   //0x50010004
	//如果是列表框的话设定一些风格
	DWORD mExStyle;
    mExStyle = GetExtendedStyle();
    mExStyle |= LVS_EX_FULLROWSELECT;      //全行选中
    mExStyle |= LVS_EX_GRIDLINES;          //显示网格
    //|LVS_REPORT
	CListCtrl::SetExtendedStyle(mExStyle);
	//m_pFont = CListCtrl::GetFont();
	
	CListCtrl::PreSubclassWindow();
}



void CMyListCtrlEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
   if(m_ItemHight)
      lpMeasureItemStruct->itemHeight = m_ItemHight;
}




void CMyListCtrlEx::SetItemHigh(int nHigh)
{
	if(!nHigh)
	  return;

    m_ItemHight = nHigh;
	CRect rcWin;
	WINDOWPOS wp;

	GetWindowRect(&rcWin);
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;

	SendMessage(WM_WINDOWPOSCHANGED,0,(LPARAM)&wp);
}



void CMyListCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
//第一步：确定这是一个列表控件
   if(lpDrawItemStruct->CtlType != ODT_LISTVIEW)
   {
 //     TRACE("CtlType:%d\n",lpDrawItemStruct->CtlType);
      return;
   } 
   //单纯只是显示下ID号
//   TRACE("CtrlID:%d\n",lpDrawItemStruct->CtlID);
//   TRACE("ItemID:%d\n",lpDrawItemStruct->itemID);
//   TRACE("Rect:%d,%d,%d,%d\n",lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.top,lpDrawItemStruct->rcItem.right,lpDrawItemStruct->rcItem.bottom);
   //第二步：画边框
   CDC *pDC;
   pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
   /////////////////////////////////////////////////////////////////////
   //是否绘制每个对像的矩形区
   //DrawAllItemFrame(pDC,&lpDrawItemStruct->rcItem);
   //第三步：绘制选中状态
	if((lpDrawItemStruct->itemState & ODS_SELECTED) == ODS_SELECTED)
	{
		 pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_HIGHLIGHT)) ;
		 pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	//Case2:未选中
	else
	{
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem,GetBkColor());
		pDC->SetTextColor(GetTextColor());	
	}




/*
   if((lpDrawItemStruct->itemAction  & ODA_DRAWENTIRE) == ODA_DRAWENTIRE)
     TRACE("Redraw All\n");
   else if((lpDrawItemStruct->itemAction  & ODA_FOCUS) == ODA_FOCUS)
	   TRACE("FOCUS \n");
	   else 
		   TRACE("Redraw All\n");
*/








	//最后绘制内容
	if(lpDrawItemStruct->itemID != -1)
	  DrawSubItem(pDC,&lpDrawItemStruct->rcItem,lpDrawItemStruct->itemID);
}

void CMyListCtrlEx::DrawAllItemFrame(CDC *pDC,CRect rt)
{
//////////////////////////////////////////////////////////
	int i,Num;
	int Width;
	CRect tempRect;

	tempRect = rt;
	Num = CListCtrl::GetHeaderCtrl()->GetItemCount();
	for(i=0;i<Num;i++)
	{
	    Width = CListCtrl::GetColumnWidth(i);
		if(Width)
		{
			tempRect.right = tempRect.left + Width;
			pDC->FrameRect(tempRect,CBrush::FromHandle(CreateSolidBrush(RGB(255,0,0))));
			tempRect.left = tempRect.right;
		}
	}
}

void CMyListCtrlEx::SetTextAttr(int nHigh,const LPCSTR Shape, COLORREF cText)
{
   m_Font.DeleteObject();
   m_crWindowText = cText;
   //====================================
   LOGFONT logFont;
   CListCtrl::GetFont()->GetLogFont(&logFont);
///////////////////////////////////////////////////////////
   strcpy(logFont.lfFaceName,Shape);
   //logFont.lfUnderline = 1;
   logFont.lfHeight = nHigh;


///////////////////////////////////////////////////////////
   m_Font.CreateFontIndirect(&logFont);
   //m_pFont->CreateFont(nHigh,0,0,0,0,FALSE,FALSE,0,0,0,0,0,0,Shape);//创建字体 
   CListCtrl::SetFont(&m_Font);
}

void CMyListCtrlEx::DrawSubItem(CDC *pDC, CRect rt, int Item)
{
    char lpBuffer[MAX_PATH];
	CRect iRect;
	int Result;  
	LIST_DATA_INFO *m_pListInfo;
/////////////////////////////////////////////////////////////////////////
	m_pListInfo = (LIST_DATA_INFO *)CListCtrl::GetItemData(Item);
    if(m_pListInfo == NULL)
	  return;
	//===================================================================
	LVCOLUMN  lvc;     //列信息的结构
	ZeroMemory(&lvc,sizeof(LVCOLUMN));
	lvc.mask = LVCF_WIDTH | LVCF_FMT; //|LVCF_SUBITEM |LVCF_TEXT;
	/////////////////////////////////////////////////////////////////
	LVITEM lvi;        //对象信息的结构
    ZeroMemory(&lvi,sizeof(LVITEM));
    lvi.iItem = Item;
    lvi.mask = LVIF_TEXT | LVIF_PARAM;
    lvi.iSubItem = 0;
    lvi.pszText = lpBuffer;
    lvi.cchTextMax = sizeof(lpBuffer);

	while(CListCtrl::GetColumn(lvi.iSubItem,&lvc))
	{
		memset(lpBuffer,'\0',MAX_PATH);
        if(lvc.cx)    //lvc.fmt
		{
          GetSubItemRect(Item,lvi.iSubItem,LVIR_LABEL,iRect);
          Result = GetItem(&lvi);
		  //////////////////////////////////////////////////////////////////
		  if(m_pListInfo[lvi.iSubItem].dItemType == OSB_CHECKBUTTON)//Check BTN
			 DrawCheckBtn(pDC,iRect,lpBuffer,&m_pListInfo[lvi.iSubItem]);
		  else if(m_pListInfo[lvi.iSubItem].dItemType == OSB_BUTTON)//BTN
		     DrawItemButton(pDC,iRect,lpBuffer,&m_pListInfo[lvi.iSubItem]);
		  else if(m_pListInfo[lvi.iSubItem].dItemType == OSB_PICTURE)//BTN
		     DrawItemPicture(pDC,lpBuffer,iRect);
		  else
			DrawItemText(pDC,lpBuffer,iRect,lvc.fmt);    //绘制文本信息
		}
		lvi.iSubItem++;
	}
}

void CMyListCtrlEx::DrawItemText(CDC *pDC, LPCSTR iString, CRect iRect, int iFmt)
{
	DWORD nTextFmt;
	CRect rt;
	const int Gap = 2;
	rt = iRect;
    nTextFmt = DT_SINGLELINE | DT_VCENTER;
	if((iFmt & LVCFMT_CENTER) == LVCFMT_CENTER)
       nTextFmt |= DT_CENTER;
	else if((iFmt & LVCFMT_RIGHT) == LVCFMT_RIGHT)
	{
       nTextFmt |= DT_RIGHT;
	   rt.right -= Gap;
	}
	else
	{
       nTextFmt |= DT_LEFT;
	   rt.left += Gap;
	}
	pDC->DrawText(iString,rt,nTextFmt);
}



int CMyListCtrlEx::InsertItem( int nItem, LPCTSTR lpszItem, int nImage )
{
	LIST_DATA_INFO *m_ItemInfo;
	int ColNum;
	int ReturnValue;
	////////////////////////////////////////////////
    ColNum = CListCtrl::GetHeaderCtrl()->GetItemCount();    //得到列数
	if(!ColNum)
      return -1;
    m_ItemInfo = new LIST_DATA_INFO[ColNum];
	while(ColNum)
	{
	    ColNum--;
	    ZeroMemory(&m_ItemInfo[ColNum],sizeof(LIST_DATA_INFO));	
        //=====================================================

	}
    //*********************************************************
	m_ItemInfo[0].nImaegIndex = nImage;
	m_ItemInfo[0].dItemType = OSB_DEFAULT;
//    strcpy(m_ItemInfo[0].SubItemName,lpszItem);


	ReturnValue = CListCtrl::InsertItem(nItem,lpszItem,nImage);

	CListCtrl::SetItemData(nItem,(DWORD)m_ItemInfo);
	return ReturnValue;
}

BOOL CMyListCtrlEx::SetItemText(int nItem, int nSubItem, LPTSTR lpszText)
{
	int ReturnValue;
	LIST_DATA_INFO *m_pListInfo;
	/////////////////////////////////////////////////////////////////////////
	m_pListInfo = (LIST_DATA_INFO *)CListCtrl::GetItemData(nItem);
    if(m_pListInfo == NULL)
	  return FALSE;
	/////////////////////////////////////////////////////////////////////////
	//传入子Item名
//    memset(m_pListInfo[nSubItem].SubItemName,'\0',sizeof(m_pListInfo[nSubItem].SubItemName));
//    strcpy(m_pListInfo[nSubItem].SubItemName,lpszText);

	switch(nSubItem)
	{
		case 0:
				m_pListInfo[nSubItem].dItemType = OSB_DEFAULT;
				break;
		case 1:
		//case 2:
				m_pListInfo[nSubItem].dItemType = OSB_CHECKBUTTON;
				break;
		case 2:
				m_pListInfo[nSubItem].dItemType = OSB_PICTURE;
				break;
		case 3:
				m_pListInfo[nSubItem].dItemType = OSB_BUTTON;
				break;
		case 4:
				m_pListInfo[nSubItem].dItemType = OSB_BUTTON;
				break;
		case 5:
				m_pListInfo[nSubItem].dItemType = OSB_DEFAULT;
				break;
		case 6:
				m_pListInfo[nSubItem].dItemType = OSB_DEFAULT;
				break;
		default:
				m_pListInfo[nSubItem].dItemType = OSB_DEFAULT;
				break;
	}

	ReturnValue = CListCtrl::SetItemText(nItem,nSubItem,lpszText);
	CListCtrl::SetItemData(nItem,(DWORD)m_pListInfo);

	return ReturnValue;
}




void CMyListCtrlEx::DrawItemPicture(CDC *pDC, LPCSTR imageName, CRect iRect)
{
	wchar_t wFileName[MAX_PATH];
	CRect rt;
	int Width,Height,iWidth,iHeight;
	MultiByteToWideChar(CP_ACP,0,imageName,-1,wFileName,MAX_PATH); 
	//*************************************************************************
	Gdiplus::Image *m_pImage;     //显示的图片
	m_pImage = Gdiplus::Image::FromFile(wFileName);
	Gdiplus::Graphics graphics(pDC->m_hDC);
    //*************************************************************************
    Width = iRect.Width();
	Height = iRect.Height();

	iWidth = m_pImage->GetWidth();
    iHeight = m_pImage->GetHeight();
///////////////////////////////////////////////////////////////////
	rt = iRect;
	//计算水平方向上的大小
    if(Width > iWidth)
	{
	  rt.left = iRect.left + (Width-iWidth)/2;
	  rt.right = rt.left + iWidth;
	}
    //计算垂直
	if(Height > iHeight)
	{
	  rt.top = iRect.top + (Height-iHeight)/2;
	  rt.bottom = rt.top + iHeight;	
	}
///////////////////////////////////////////////////////////////////////////////
	graphics.DrawImage(m_pImage,rt.left,rt.top,rt.Width(),rt.Height());

	//rt.InflateRect(4,4,4,4);
	//pDC->FrameRect(rt,CBrush::FromHandle(CreateSolidBrush(RGB(0,0,0))));
}

void CMyListCtrlEx::DrawCheckBtn(CDC *pDC, CRect iRect, LPCSTR lpString,LPVOID lParam)
{
    CRect rt;
    int Width,Height,tempSize;;
	LOGFONT logFont;
	PLIST_DATA_INFO m_pListItem;
    if(lParam == NULL)
	  return;
    m_pListItem = (PLIST_DATA_INFO)lParam;

    Width = iRect.Width();
	Height = iRect.Height();
 
	rt = iRect;
    CListCtrl::GetFont()->GetLogFont(&logFont);
    tempSize = (logFont.lfHeight > 0)?logFont.lfHeight:(-logFont.lfHeight);

    rt.left += 10;
	rt.right = rt.left + tempSize;

	rt.top += (Height - tempSize)/2;
	rt.bottom = rt.top + tempSize;

/////////////////////////////////////////////////////////////////////////////////////////
	pDC->FrameRect(rt,CBrush::FromHandle(CreateSolidBrush(RGB(51,102,153))));
	rt.DeflateRect(1,1,1,1);
	//pDC->Rectangle(rt);
    //=======================================================================
	if(m_pListItem->bSubItemStatus == 1)   //选中的
	  pDC->FillSolidRect(rt, RGB(255,0,0));
    else
	  pDC->FillSolidRect(rt, m_crWindow);
/////////////////////////////////////////////////////////////////////////////////////
/*	{
	    CPen *pOldPen = NULL;
		CPen graypen(PS_SOLID, 2, m_crGrayText);
		CPen blackpen(PS_SOLID, 2, RGB(0,0,0));
		//if(m_pListItem->EnableItem)
		   pOldPen = pDC->SelectObject(&blackpen);
		//else
		//   pOldPen = pDC->SelectObject(&graypen);



		pDC->MoveTo(rt.left+3,rt.top+rt.Height()/3);
		pDC->LineTo(rt.left + rt.Width()*2/5,rt.bottom-3);

		pDC->MoveTo(rt.left + rt.Width()*2/5,rt.bottom-3);
		pDC->LineTo(rt.right - 3,rt.top+3);
		int x = rt.right - tempSize/4;
		int y = rt.top + 3;
        //对勾函数：y = ax + b/x
		int i;
////////////////////////////////////////////////////////////////////////
	    for (i = 0; i < tempSize/4; i++)
		{
			pDC->MoveTo(x, y);
			pDC->LineTo(x, y+3);
			x--;
			y++;
		}
		for (i = 0; i < tempSize/4; i++)
		{
			pDC->MoveTo(x, y);
			pDC->LineTo(x, y+3);
			x--;
			y--;
		}

        ///////////////////////////////////////////////////////////////
		if (pOldPen)
			pDC->SelectObject(pOldPen);
	}
*/

	//==================================================================
	rt.left = rt.right + 5;
	rt.right = iRect.right;
	rt.top = iRect.top;
	rt.bottom = iRect.bottom;
    pDC->DrawText(lpString,rt,DT_SINGLELINE | DT_VCENTER | DT_LEFT);
}

void CMyListCtrlEx::SetItemStatus(int nItem, int nSubItem, int nStatus)
{
	LIST_DATA_INFO *m_pListInfo;
	/////////////////////////////////////////////////////////////////////////
	m_pListInfo = (LIST_DATA_INFO *)CListCtrl::GetItemData(nItem);
    if(m_pListInfo == NULL)
	  return;
    /////////////////////////////////////////////////////////////////////////
    m_pListInfo[nSubItem].bSubItemStatus = nStatus;


}

void CMyListCtrlEx::DrawItemButton(CDC *pDC, CRect iRect, LPCSTR lString, LPVOID lParam)
{
    CRect rt;
    int Width,Height,tempSize;;
	LOGFONT logFont;
	PLIST_DATA_INFO m_pListItem;
    if(lParam == NULL)
	  return;
    m_pListItem = (PLIST_DATA_INFO)lParam;

    Width = iRect.Width();
	Height = iRect.Height();

	rt = iRect;
    CListCtrl::GetFont()->GetLogFont(&logFont);
    tempSize = (logFont.lfHeight > 0)?logFont.lfHeight:(-logFont.lfHeight);
	///////////////////////////////////////////////////////////////////////////////////
    rt.top +=  ((rt.Height() - tempSize)/2) - 5;
	rt.bottom = rt.top + tempSize + 5;
    
	rt.left += 20;
	rt.right -= 20;
    //先画个文本
	DrawItemPicture(pDC,"Source\\2222.png",iRect);
    //再画边框
	//if(m_pListItem->bSubItemStatus)
	rt.InflateRect(5,5,5,5);
	pDC->FrameRect(rt,CBrush::FromHandle(CreateSolidBrush(m_crGrayText)));
	
    pDC->DrawText(lString,rt,DT_SINGLELINE | DT_VCENTER | DT_CENTER);
 
}

void CMyListCtrlEx::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//=========================================================================
    CRect rt;

    int nItem = pNMIA->iItem;
	int nSubItem = pNMIA->iSubItem;
    if((nItem == -1) || (nSubItem == -1))
	   return;
    LIST_DATA_INFO *m_ListItemInfo;
    m_ListItemInfo = (LIST_DATA_INFO *)CListCtrl::GetItemData(nItem);
	if(m_ListItemInfo == NULL)
	  return;

	GetSubItemRect(nItem,nSubItem,LVIR_LABEL,rt);
    //============================================================================
	switch(m_ListItemInfo[nSubItem].dItemType)
	{
		case OSB_DEFAULT:
							break;
		case OSB_CHECKBUTTON:
			                m_ListItemInfo[nSubItem].bSubItemStatus = !m_ListItemInfo[nSubItem].bSubItemStatus;
							m_ListItemInfo[nSubItem].bUpdate = !m_ListItemInfo[nSubItem].bUpdate;
							break;
		case OSB_BUTTON:
			                m_ListItemInfo[nSubItem].bSubItemStatus = !m_ListItemInfo[nSubItem].bSubItemStatus;
							break;
		default:
							break;
	}

    //往上发送消息删除
	if(nSubItem == 3)
	  ::SendMessage(GetParent()->GetSafeHwnd(),WM_EX_DELETE,(WPARAM)&nItem,NULL);



	InvalidateRect(rt);
	*pResult = 0;
}
