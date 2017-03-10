// ManagementDlg.h : header file
#pragma once

/////////////////////////////////////////////////////////////////////////////
#include "ButtonEx.h"
//#define FULL_SCREEN_COVER_TASK
#include "MainRealStatusDlg.h"      //主实时房态
#include "ConfigPanelDlg.h"

// CManagementDlg dialog

class CManagementDlg : public CDialog
{
public:
	CRect	rcWorkArea;                   //工作的区间
	CRect	rcHeadArea;				//头部
	CRect	rcCustomerArea;			//客户区
// Construction
public:
    CMainRealStatusDlg  *m_pRealStatusDlg;
	CConfigPanelDlg  *m_pConfigPanel;



public:
	void InitSubDialog();
	void AdjustItemPosition();
	CManagementDlg(CWnd* pParent = NULL);	// standard constructor
    ~CManagementDlg();
// Dialog Data
	//{{AFX_DATA(CManagementDlg)
	enum { IDD = IDD_MANAGEMENT_DIALOG };
	CButtonEx	m_Exit;
	CButtonEx	m_Census;
	CButtonEx	m_ConfigPannel;
	CButtonEx	m_ActureRS;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManagementDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CManagementDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBtnActulRoomstate();
	afx_msg void OnBtnConfig();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

