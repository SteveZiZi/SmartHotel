#if !defined(AFX_TECHNICIANDLG_H__BC7715CB_EB56_45F9_99C7_B83B78BD8DD4__INCLUDED_)
#define AFX_TECHNICIANDLG_H__BC7715CB_EB56_45F9_99C7_B83B78BD8DD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TechnicianDlg.h : header file
//
#include "ModuleCfgDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CTechnicianDlg dialog

class CTechnicianDlg : public CDialog
{
// Construction
public:
	CTechnicianDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTechnicianDlg)
	enum { IDD = IDD_MAIN_DIALOG };
	CTreeCtrl	m_RoomTree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTechnicianDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTechnicianDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg void OnBtnAddRt();
	afx_msg void OnSelchangedTreeRoomname(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetting();
	afx_msg void OnImport();
	afx_msg void OnExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CModuleCfgDlg *pModuleStage;
	BOOL		bFirstTimeFlag;
public:
	HTREEITEM	hFindRoomPos(PCHAR pRoomName);
	void SaveTreeItem(HTREEITEM hItem);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TECHNICIANDLG_H__BC7715CB_EB56_45F9_99C7_B83B78BD8DD4__INCLUDED_)

