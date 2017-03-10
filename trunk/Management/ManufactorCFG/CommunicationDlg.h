#if !defined(AFX_COMMUNICATIONDLG_H__2BAAEAC9_DBB8_4368_800B_4024100ABDC0__INCLUDED_)
#define AFX_COMMUNICATIONDLG_H__2BAAEAC9_DBB8_4368_800B_4024100ABDC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommunicationDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommunicationDlg dialog

class CCommunicationDlg : public CDialog
{
// Construction
public:
	void InitCommunicationMethod();
	CCommunicationDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCommunicationDlg)
	enum { IDD = IDD_COMMUNICATION_DIALOG };
	CTabCtrl	m_tMethod;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommunicationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommunicationDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMUNICATIONDLG_H__2BAAEAC9_DBB8_4368_800B_4024100ABDC0__INCLUDED_)
