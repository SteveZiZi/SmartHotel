#pragma once

#ifndef ULONG_PTR
#define ULONG_PTR unsigned long*
#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")
#endif

// CMyPictureEx

class CMyPictureEx : public CWnd
{
	//DECLARE_DYNAMIC(CMyPictureEx)

public:
	BOOL FrameEnable;
	int FrameSize;
	COLORREF m_cFrame;     //±ß¿òÑÕÉ«
	COLORREF m_cBkgd;      //±³¾°É«
private:
	Gdiplus::Image *m_pImage;     //ÏÔÊ¾µÄÍ¼Æ¬
	CRect m_rcWnd;
	int nRound;
	// Construction
public:
	CMyPictureEx();

	// Attributes
public:

	// Operations
public:

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Implementation
public:
	void DrawSourceImage(CDC *pDC);
	void SetImage(LPCSTR FileName,BOOL Flag=FALSE);
	void SetBkColor(COLORREF nColor,BOOL Flag=FALSE);
	void DrawFrame(CDC *pDC);
	void SetFrameEnable(int nSize, COLORREF nColor,int Mode = 0, BOOL Flag=FALSE);
	virtual ~CMyPictureEx();

	// Generated message map functions
public:
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};


