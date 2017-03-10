#if !defined(AFX_ROOMDLG_H__D796172B_0074_4AFB_805C_7C4E8BEDCD30__INCLUDED_)
#define AFX_ROOMDLG_H__D796172B_0074_4AFB_805C_7C4E8BEDCD30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RoomDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
#include "SubRoomBuildingDlg.h"
#include "SubRoomDetailDlg.h"
// CRoomDlg dialog

class CRoomDlg : public CDialog
{

public:
    CSubRoomBuildingDlg *m_pBuilding;			//楼座详细
	CSubRoomDetailDlg *m_pRoomDetail;			//客房详细

	int	RoomStringMode;						//客房模式显示








	HTREEITEM hItem;
	DWORD LastIndex;
// Construction
public:
	void DeleteTreeContext(HTREEITEM hItem);
	DWORD GetNextEntry(HTREEITEM hItem);								//得到下一个索引
	BOOL SearchEntryExist(HTREEITEM hItem,const char *KeyString);		//查找同名的
	void UpDataAllSubDlg(HTREEITEM wParam,PVOID lParam);
	void EnumAllBuilding();
	BOOL CheckTypeExist(PCHAR pTempRt);
	void InitRoomTableMenu();
	CRoomDlg(CWnd* pParent = NULL);   // standard constructor
    ~CRoomDlg();
// Dialog Data
	//{{AFX_DATA(CRoomDlg)
	enum { IDD = IDD_ROOOM_DIALOG };
	CTreeCtrl	m_Building;
	CTabCtrl	m_RoomMenu;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRoomDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTreeBuilding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeTabRoom(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg LRESULT DoAddOpt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT DoDeleteOpt(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT DoModifyOpt(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMDLG_H__D796172B_0074_4AFB_805C_7C4E8BEDCD30__INCLUDED_)
