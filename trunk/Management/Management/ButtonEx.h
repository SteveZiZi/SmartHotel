#if !defined(AFX_BUTTONEX_H__F7448DAC_19B2_490B_BA49_0BD8C4F29769__INCLUDED_)
#define AFX_BUTTONEX_H__F7448DAC_19B2_490B_BA49_0BD8C4F29769__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonEx.h : header file
//背景显示的样式
#define ENABLE_EDGE        0x01    //显示边框
#define ENABLE_BK_COLOR    0x10    //允许显示背景色



















//对齐的方式
#define TEXT_LEFT    0x01
#define TEXT_TOP     0x02
#define TEXT_BUTTON  0x04
#define TEXT_RIGHT   0x08
//手标当前在的状态
#define MOUSE_NORMAL  0x00
#define MOUSE_FOCUS   0x01
#define MOUSE_LEAVE   MOUSE_NORMAL
//边界
#define BORDER_VALUE_X  10
#define BORDER_VALUE_Y  5
//图片的显示状态
#define PIC_NORMAL     0        //正常大小(左上角显示)
#define PIC_ZOOM       1        //放大适应控件
#define PIC_MIN        2        //缩小适应控件
#define PIC_FULL       3        //填满控件
/////////////////////////////////////////////////////////////////////////////
const CPoint sPoint(15,15);




// VC6
//#if defined(_MSC_VER) && _MSC_VER == 1200
#ifndef ULONG_PTR
  #define ULONG_PTR unsigned long*
#endif
//#include "GDIPlus\\include\\specstrings.h"
#include "..\\CommSource\\include\\gdiplus.h"
#pragma comment(lib, "..\\CommSource\\lib\\gdiplus.lib")
using namespace Gdiplus;
// CButtonEx window






class CButtonEx : public CButton
{
// Construction
public:
	CButtonEx();

// Attributes
public:
   GdiplusStartupInput m_gdiplusStartupInput; 
   ULONG_PTR m_gdiplusToken;
   CDC			m_dcBk;
   CBitmap		m_bmpBk;
   CBitmap*	m_pbmpOldBk;




   CRect Rect;                   //控件的尺寸
//按钮的形态显示
   BYTE dStyleFlag;              //控件的样式(4 BYTE)
   CPoint rPt;                   //圆角的大小
   COLORREF BkColor;             //控制件的背景色
   COLORREF EdgeColor;           //边框颜色




















   CToolTipCtrl	m_ToolTip;     //手标放上去时显示
   //全局变量
   BOOL bIsMouseMoved;
   int MouseStatus;              //手标当前状态
   int PicShowMode;              //图片的显示模式

   //文本相关的
   CString sContent;      //文本的内容
   COLORREF TextColor;    //控件的文本色
   BYTE AlignFlag;        //文本的对齐方式
   CFont m_Font;
   int tHight;            //字体高

   //图片相关的
   CSize pSize;                  //图片的大小
   CRect pRect;                  //图片显示的Rect
   Gdiplus::Image *m_pImage;     //显示的图片
   Gdiplus::Image *m_fImage;     //焦点时显示的图片
// Operations
protected:
  	BOOL		m_bIsFlat;			// Is a flat button?
	BOOL		m_bMouseOnButton;	// Is mouse over the button?
	BOOL		m_bDrawTransparent;	// Draw transparent?
	BOOL		m_bIsPressed;		// Is button pressed?
	BOOL		m_bIsFocused;		// Is button focused?
	BOOL		m_bIsDisabled;		// Is button disabled?
	BOOL		m_bIsDefault;		// Is default button?
	BOOL		m_bIsCheckBox;		// Is the button a checkbox?
	BYTE		m_byAlign;			// Align mode
	BOOL		m_bDrawBorder;		// Draw border?
	BOOL		m_bDrawFlatFocus;	// Draw focus rectangle for flat button? 

















public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawBackground(CDC* pDC, LPCRECT aRect);
	void PaintBk(CDC* pDC);
	void PaintFram(CDC *pDC,BOOL Flag = FALSE);
	void DrawActivePicture(CDC *pDC);
	void DrawBkEdge(CDC *pDC);
	void SetBtnBkColor(COLORREF cbk,COLORREF cedge = NULL);
	void SetButtonBkStyle(BYTE nMode,CPoint ePt = sPoint);
	void SetShowMode(int Mode);
	void SetControlSource(PWCHAR lPath,PWCHAR lFocusPath,float Flag =1.0);
	void ShowControlText(CDC *pDC);
	void SetTextStyle(COLORREF tColor,int nHight,CString character);
	virtual ~CButtonEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonEx)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam = 0);
    afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam = 0);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONEX_H__F7448DAC_19B2_490B_BA49_0BD8C4F29769__INCLUDED_)
