#if !defined(AFX_AUTOEVENTDLG_H__968FD2DB_45A8_47A9_A8D8_0ABABABB5CBD__INCLUDED_)
#define AFX_AUTOEVENTDLG_H__968FD2DB_45A8_47A9_A8D8_0ABABABB5CBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AutoEventDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAutoEventDlg dialog

class CAutoEventDlg : public CDialog
{
// Construction
public:
	void InitEvent();
	CAutoEventDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAutoEventDlg)
	enum { IDD = IDD_AUTOEVENT_DIALOG };
	CTabCtrl	m_Event;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoEventDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAutoEventDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOEVENTDLG_H__968FD2DB_45A8_47A9_A8D8_0ABABABB5CBD__INCLUDED_)
