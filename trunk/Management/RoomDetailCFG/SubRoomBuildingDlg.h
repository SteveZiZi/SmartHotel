#if !defined(AFX_SUBROOMBUILDINGDLG_H__AC7E2997_8880_4E53_B528_13A43414F78B__INCLUDED_)
#define AFX_SUBROOMBUILDINGDLG_H__AC7E2997_8880_4E53_B528_13A43414F78B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubRoomBuildingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
#define WM_ROOM_BUILDING_SETTING   WM_USER+20
enum 
{
   BTN_ADD,
   BTN_MODIFY,
   BTN_DELETE
};
// CSubRoomBuildingDlg dialog

class CSubRoomBuildingDlg : public CDialog
{
public:
    PBUILDING_ENTRY m_pEntry;
	HTREEITEM		hItem;
// Construction
public:
	void UpdataBuilding(PVOID lParam);				
	void SetRelationItem(PVOID pItem);
	void InitRoomViewStyle();
	
	



	

	CSubRoomBuildingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubRoomBuildingDlg)
	enum { IDD = IDD_SUB_ROOM_BUILD_DIALOG };
	CComboBox	m_ShowStyle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubRoomBuildingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubRoomBuildingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnModify();
	afx_msg void OnBtnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBROOMBUILDINGDLG_H__AC7E2997_8880_4E53_B528_13A43414F78B__INCLUDED_)
