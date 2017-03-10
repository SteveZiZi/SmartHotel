#if !defined(AFX_ROOMTYPEDLG_H__F7D1A1D2_0537_4092_B8BF_E4B39836D1B7__INCLUDED_)
#define AFX_ROOMTYPEDLG_H__F7D1A1D2_0537_4092_B8BF_E4B39836D1B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RoomTypeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRoomTypeDlg dialog

class CRoomTypeDlg : public CDialog
{
public:
	CPtrArray m_TypeList;

// Construction
public:
	int CheckName(PCHAR pName);
	DWORD GetLastEntryNum();
	void UpDataEntry(int nSel);
	void EnumAllRCU();
	void EnumAllRoomType();
	BOOL CheckTypeExist(PCHAR pTempRt);
	CRoomTypeDlg(CWnd* pParent = NULL);   // standard constructor
    ~CRoomTypeDlg();
// Dialog Data
	//{{AFX_DATA(CRoomTypeDlg)
	enum { IDD = IDD_ROOMTYPE_DIALOG };
	CComboBox	m_RcuType;
	CTabCtrl	m_tRoomType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomTypeDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRoomTypeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabRoomtype(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT DoAddOpt(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT DoModifyOpt(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT DoDeleteOpt(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnModify();
	afx_msg void OnBtnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMTYPEDLG_H__F7D1A1D2_0537_4092_B8BF_E4B39836D1B7__INCLUDED_)
