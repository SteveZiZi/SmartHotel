#if !defined(AFX_BUTTONEX_H__F7448DAC_19B2_490B_BA49_0BD8C4F29769__INCLUDED_)
#define AFX_BUTTONEX_H__F7448DAC_19B2_490B_BA49_0BD8C4F29769__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonEx.h : header file
//������ʾ����ʽ
#define ENABLE_EDGE        0x01    //��ʾ�߿�
#define ENABLE_BK_COLOR    0x10    //������ʾ����ɫ



















//����ķ�ʽ
#define TEXT_LEFT    0x01
#define TEXT_TOP     0x02
#define TEXT_BUTTON  0x04
#define TEXT_RIGHT   0x08
//�ֱ굱ǰ�ڵ�״̬
#define MOUSE_NORMAL  0x00
#define MOUSE_FOCUS   0x01
#define MOUSE_LEAVE   MOUSE_NORMAL
//�߽�
#define BORDER_VALUE_X  10
#define BORDER_VALUE_Y  5
//ͼƬ����ʾ״̬
#define PIC_NORMAL     0        //������С(���Ͻ���ʾ)
#define PIC_ZOOM       1        //�Ŵ���Ӧ�ؼ�
#define PIC_MIN        2        //��С��Ӧ�ؼ�
#define PIC_FULL       3        //�����ؼ�
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




   CRect Rect;                   //�ؼ��ĳߴ�
//��ť����̬��ʾ
   BYTE dStyleFlag;              //�ؼ�����ʽ(4 BYTE)
   CPoint rPt;                   //Բ�ǵĴ�С
   COLORREF BkColor;             //���Ƽ��ı���ɫ
   COLORREF EdgeColor;           //�߿���ɫ




















   CToolTipCtrl	m_ToolTip;     //�ֱ����ȥʱ��ʾ
   //ȫ�ֱ���
   BOOL bIsMouseMoved;
   int MouseStatus;              //�ֱ굱ǰ״̬
   int PicShowMode;              //ͼƬ����ʾģʽ

   //�ı���ص�
   CString sContent;      //�ı�������
   COLORREF TextColor;    //�ؼ����ı�ɫ
   BYTE AlignFlag;        //�ı��Ķ��뷽ʽ
   CFont m_Font;
   int tHight;            //�����

   //ͼƬ��ص�
   CSize pSize;                  //ͼƬ�Ĵ�С
   CRect pRect;                  //ͼƬ��ʾ��Rect
   Gdiplus::Image *m_pImage;     //��ʾ��ͼƬ
   Gdiplus::Image *m_fImage;     //����ʱ��ʾ��ͼƬ
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
