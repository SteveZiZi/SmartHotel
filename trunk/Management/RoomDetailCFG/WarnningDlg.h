#if !defined(AFX_WARNNINGDLG_H__5EBE733B_4C37_4738_ADDC_56E3A7A2EA3E__INCLUDED_)
#define AFX_WARNNINGDLG_H__5EBE733B_4C37_4738_ADDC_56E3A7A2EA3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WarnningDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWarnningDlg dialog

class CWarnningDlg : public CDialog
{
// Construction
public:
	void InitWarn();
	CWarnningDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWarnningDlg)
	enum { IDD = IDD_WARNNING_DIALOG };
	CTabCtrl	m_WarnEntry;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWarnningDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWarnningDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WARNNINGDLG_H__5EBE733B_4C37_4738_ADDC_56E3A7A2EA3E__INCLUDED_)
