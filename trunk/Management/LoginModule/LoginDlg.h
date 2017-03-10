#if !defined(AFX_LOGINDLG_H__B3F07FEC_CEE3_4AE0_8DBF_E92EC849D3F1__INCLUDED_)
#define AFX_LOGINDLG_H__B3F07FEC_CEE3_4AE0_8DBF_E92EC849D3F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

class CLoginDlg : public CDialog
{
// Construction
public:
	CRect Rect;
	char CurrentPath[MAX_PATH];
	CString CurrentName;
	CString sConfigFile;
public:
	void InitDepartMent();
	void DrawPicture(CDC *pDC,PCHAR Path,CPoint lt,CSize area,bool Flag);
	CLoginDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_LOGIN_DIALOG };
	CComboBox	m_Departament;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg void OnSelchangeComboDepartment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int		nDepartment;
	CString m_UserName;
	CString m_Passwords;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__B3F07FEC_CEE3_4AE0_8DBF_E92EC849D3F1__INCLUDED_)
