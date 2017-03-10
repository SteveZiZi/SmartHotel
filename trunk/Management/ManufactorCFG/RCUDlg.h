#if !defined(AFX_RCUDLG_H__F084E646_F3FD_41EA_89D8_2535CE12F84B__INCLUDED_)
#define AFX_RCUDLG_H__F084E646_F3FD_41EA_89D8_2535CE12F84B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RCUDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
#include "SubRCUBaseInfoDlg.h"
//#include "SubRCUDevicePortsDlg.h"
//#include "SubRCURoomPortsDlg.h"
#include "SubDeviceCfgMethodDlg.h"
// CRCUDlg dialog

class CRCUDlg : public CDialog
{
public:
	//HTREEITEM hItem;
	//DWORD LastRCUID;
	//PRCUTYPE pSelectRCU; 
    //子对话框之基本信息
	CSubRCUBaseInfoDlg			*m_pBaseInfoDlg;
	CSubDeviceCfgMethodDlg		*m_pSubDeviceMethodDlg;
	//CSubRCUDevicePortsDlg	*m_pDevicePortsDlg;
	//CSubRCURoomPortsDlg		*m_pRoomPortsDlg;
// Construction
public:
	DWORD GetNextEntry(HTREEITEM hItem);
	void DeleteTreeContext(HTREEITEM hItem);
	void UpDataAllSubDlg(HTREEITEM wParam,PVOID lParam);
	void EnumAllTableRecord();
	void SetTableEntryFocus(UINT nTableEntry);
	void InitRCUTableEntry();






	BOOL SearchEntryExist(HTREEITEM hItem,const char* KeyString);
	CRCUDlg(CWnd* pParent = NULL);   // standard constructor
    ~CRCUDlg();
// Dialog Data
	//{{AFX_DATA(CRCUDlg)
	enum { IDD = IDD_RCU_DIALOG };
	CTabCtrl	m_TableEntry;
	CTreeCtrl	m_RCUEntryTree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRCUDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRCUDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTreeRcu(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeTabRcuSetting(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT DoAddOpt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT DoDeleteOpt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT DoModifyOpt(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RCUDLG_H__F084E646_F3FD_41EA_89D8_2535CE12F84B__INCLUDED_)
