#if !defined(AFX_KEYDEFINEDLG_H__17F7A200_57C2_4D65_A61A_8E75155FF799__INCLUDED_)
#define AFX_KEYDEFINEDLG_H__17F7A200_57C2_4D65_A61A_8E75155FF799__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KeyDefineDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKeyDefineDlg dialog

class CKeyDefineDlg : public CDialog
{
// Construction
public:
	void InitKeyEntry();
	CKeyDefineDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKeyDefineDlg)
	enum { IDD = IDD_KEYDEF_DIALOG };
	CTabCtrl	m_KeyEntry;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyDefineDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKeyDefineDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYDEFINEDLG_H__17F7A200_57C2_4D65_A61A_8E75155FF799__INCLUDED_)
