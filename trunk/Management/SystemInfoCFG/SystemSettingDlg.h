#if !defined(AFX_SYSTEMSETTINGDLG_H__E84B6BD8_6EE5_4513_9EEF_A919E475D913__INCLUDED_)
#define AFX_SYSTEMSETTINGDLG_H__E84B6BD8_6EE5_4513_9EEF_A919E475D913__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SystemSettingDlg.h : header file
//
#include "RoomStyleDlg.h"
#include "SystemInfoDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CSystemSettingDlg dialog

class CSystemSettingDlg : public CDialog
{
// Construction
public:
	void InitSystemSettingMenu();
	CSystemSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSystemSettingDlg)
	enum { IDD = IDD_SYSTEM_DIALOG };
	int		nSelect;
	CTabCtrl	m_SystemNenu;
	CSystemInfoDlg *pSystemInfoDlg;
	CRoomStyleDlg *pRoomStyleDlg;
	//}}AFX_DATA
public:
	void ShowSelectEntry(int nEntry);
	void InitAllSubDlg();
public:
	afx_msg void OnOK();
	afx_msg void OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSystemSettingDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMSETTINGDLG_H__E84B6BD8_6EE5_4513_9EEF_A919E475D913__INCLUDED_)
