#if !defined(AFX_WELCOMDLG_H__86F73EF9_A4D4_48DE_A562_962769D545C7__INCLUDED_)
#define AFX_WELCOMDLG_H__86F73EF9_A4D4_48DE_A562_962769D545C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WelcomDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWelcomDlg dialog

class CWelcomDlg : public CDialog
{
// Construction
public:
	int GetSelectMode();
	CWelcomDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWelcomDlg)
	enum { IDD = IDD_WELCOME_DIALOG };
	int		m_Mode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWelcomDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWelcomDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOMDLG_H__86F73EF9_A4D4_48DE_A562_962769D545C7__INCLUDED_)
