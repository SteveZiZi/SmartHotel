#if !defined(AFX_GUESTDLG_H__617BFE7A_6545_4069_ADD5_2D5B7CC91091__INCLUDED_)
#define AFX_GUESTDLG_H__617BFE7A_6545_4069_ADD5_2D5B7CC91091__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GuestDlg.h : header file
//
#include "AccountManagement.h"
#include "RightManagement.h"
#include "LandRecord.h"
/////////////////////////////////////////////////////////////////////////////
// CGuestDlg dialog

class CGuestDlg : public CDialog
{
// Construction
public:
	void InitGuestMenu();
	void InitDepartmentTree();
	void UpDataAllSubDlg(HTREEITEM wParam,CString result);
	CGuestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGuestDlg)
	enum { IDD = IDD_GUEST_DIALOG };

	CTreeCtrl	m_Department;
	CTabCtrl	m_GuestMenu;
	CAccountManagement *m_paccountManagement;
	CRightManagement *m_prightManagement;
	CLandRecord	*m_plandRecord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGuestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGuestDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTabGuest(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeDepartment(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnOK();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUESTDLG_H__617BFE7A_6545_4069_ADD5_2D5B7CC91091__INCLUDED_)
