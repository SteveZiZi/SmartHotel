#if !defined(AFX_SUBROOMDETAILDLG_H__1FD22AD9_F642_4F72_8D5C_EE3582A1E293__INCLUDED_)
#define AFX_SUBROOMDETAILDLG_H__1FD22AD9_F642_4F72_8D5C_EE3582A1E293__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubRoomDetailDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubRoomDetailDlg dialog

class CSubRoomDetailDlg : public CDialog
{
public:
	PBUILDING_ENTRY m_pBuildingInfo;
	CMenu  *m_pMenu;   
	PROOM_DETAIL_ENTRY	CurSelRoomDetail;
	int CurSelRoomEntry;
	//CPtrArray m_RoomTypeArr;
	//PBUILDINGSET m_pBuildingInfo;
// Construction
public:
	void UpdataListRow(int RowIndex,PVOID lParam);
	void UpDataItemContext(PVOID pContext,BOOL Flag);
	DWORD GetNextEntryIndex();
	void UpDataRoomInfo(PVOID lParam);
	BOOL CheckRoomExist(LPVOID lParam);
	
	void InsertOneRow(int Entry,LPVOID lParam);




	void DeleteAllData();			//删除所有的列表
	void EnumAllRoomType();			//显示所有的房类
	void InitListCtrlView();		//初始化列表控件
	CSubRoomDetailDlg(CWnd* pParent = NULL);   // standard constructor
    ~CSubRoomDetailDlg();
// Dialog Data
	//{{AFX_DATA(CSubRoomDetailDlg)
	enum { IDD = IDD_SUB_ROOM_DETAIL_DIALOG };
	CComboBox	m_RoomType;
	CListCtrl	m_RoomList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubRoomDetailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubRoomDetailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedListRoom(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnAdd();
	afx_msg void OnRclickListRoom(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT DoAddOpt(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT DoModifyOpt(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT DoDeleteOpt(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBROOMDETAILDLG_H__1FD22AD9_F642_4F72_8D5C_EE3582A1E293__INCLUDED_)
