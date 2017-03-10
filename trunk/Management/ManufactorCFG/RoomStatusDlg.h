#if !defined(AFX_ROOMSTATUSDLG_H__9ACC9DC0_04DF_4BFA_80C4_DB7081FE2D8A__INCLUDED_)
#define AFX_ROOMSTATUSDLG_H__9ACC9DC0_04DF_4BFA_80C4_DB7081FE2D8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RoomStatusDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
//#include "SubBaseRoomStatusDlg.h"
#define MAX_ENTRY_NUMBER      5
// CRoomStatusDlg dialog
//#include "MyListCtrlEx.h"


class CRoomStatusDlg : public CDialog
{
public:
	ITEM_ENTRTY m_PreItem;		
	CEdit		*pEdit;
public:
	afx_msg LRESULT DoAddOpt(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT DoModifyOpt(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT DoDeleteOpt(WPARAM wParam, LPARAM lParam);
public:
	ULONG GetNextDbIndex();
	void UpdataItemStringFromEdit(unsigned int nItem, unsigned int nSubItem);
	void SetEditStringFromItem(unsigned int nItem, unsigned int nSubItem);
	int InertOneRow(int Index,LPVOID lParam);
	void DeleteAllListContext();
	void EnumAllTableRecord(int TableIndex);

	void InitRoomstateListCtrl();
	void InitRoomStatus();
	CRoomStatusDlg(CWnd* pParent = NULL);   // standard constructor
    ~CRoomStatusDlg();
// Dialog Data
	//{{AFX_DATA(CRoomStatusDlg)
	enum { IDD = IDD_ROOMSTATUE_DIALOG };
	CTabCtrl	m_RoomStateEntry;
	//CMyListCtrlEx	m_RoomStateList;		//带外观的
	CListCtrl m_RoomStateList;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomStatusDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRoomStatusDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabRoomStatus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListRoomstate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListRoomstate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListRoomstate(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMSTATUSDLG_H__9ACC9DC0_04DF_4BFA_80C4_DB7081FE2D8A__INCLUDED_)
