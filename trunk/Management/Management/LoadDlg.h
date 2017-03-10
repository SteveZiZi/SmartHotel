#if !defined(AFX_LOADDLG_H__512B6FA0_753F_4812_B797_45C0F4A9F101__INCLUDED_)
#define AFX_LOADDLG_H__512B6FA0_753F_4812_B797_45C0F4A9F101__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoadDlg.h : header file
//
#include "PictureEx.h"
/////////////////////////////////////////////////////////////////////////////
#define DEFAULT_TIMEOUT_VALUE	15
// CLoadDlg dialog

class CLoadDlg : public CDialog
{
public:
	ULONG	uCostTimes;
	ULONG	uTimeOutValue;
	LPCTSTR	lpPicName;

// Construction
public:
	void SetCurrentStatus(BOOL Status){IsReady = Status;};
	void SetViewName(LPCTSTR lpName){lpPicName = lpName;};			//设置图片的路径
	void SetTimeOutValue(ULONG uValue){uTimeOutValue = uValue;};		//超时退出值
	void ReSetItemSize();
	CLoadDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoadDlg)
	enum { IDD = IDD_LOAD_DIALOG };
	CPictureEx	m_GifPic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLoadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL	IsReady;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADDLG_H__E63C0011_77E5_491E_9210_8D83E1A28447__INCLUDED_)
