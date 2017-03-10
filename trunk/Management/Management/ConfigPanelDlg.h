#if !defined(AFX_CONFIGPANELDLG_H__928535B9_434F_4864_B27E_55202119E72A__INCLUDED_)
#define AFX_CONFIGPANELDLG_H__928535B9_434F_4864_B27E_55202119E72A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigPanelDlg.h : header file
//
#include "ButtonEx.h"
/////////////////////////////////////////////////////////////////////////////
#include "ManufactorClass.h"
#include "RoomDetailClass.h"
#include "SystemInfoClass.h"
// CConfigPanelDlg dialog

class CConfigPanelDlg : public CDialog
{
public:
    
// Construction
public:
	void SetBtnView();
	CConfigPanelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigPanelDlg)
	enum { IDD = IDD_CONFIG_DIALOG };
	CButtonEx	m_Manage_Setting;
	CButtonEx	m_Warnning_Setting;
	CButtonEx	m_Key_Define;
	CButtonEx	m_Notice_Setting;
	CButtonEx	m_Picture_Change;
	CButtonEx	m_Communication_Config;
	CButtonEx	m_RCU_Config;
	CButtonEx	m_AutoEvent_Setting;
	CButtonEx	m_Device_Setting;
	CButtonEx	m_RoomStatus_Setting;
	CButtonEx	m_RoomMode_Setting;
	CButtonEx	m_Room_Setting;
	CButtonEx	m_RoomType_Setting;
	CButtonEx	m_Use_Manage;
	CButtonEx	m_System_Setting;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigPanelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigPanelDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnRoomstatus();
	afx_msg void OnBtnDevice();
	afx_msg void OnBtnCommunation();
	afx_msg void OnBtnRcu();
	afx_msg void OnBtnRoomtype();
	afx_msg void OnBtnRoom();
	afx_msg void OnBtnRoommode();
	afx_msg void OnBtnSystem();
	afx_msg void OnBtnUseinfo();
	afx_msg void OnBtnManage();
	afx_msg void OnBtnPicture();
	afx_msg void OnBtnAutoevent();
	afx_msg void OnBtnAttention();
	afx_msg void OnBtnKey();
	afx_msg void OnBtnWarnning();
public:
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGPANELDLG_H__928535B9_434F_4864_B27E_55202119E72A__INCLUDED_)
