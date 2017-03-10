#if !defined(AFX_SUBRCUBASEINFODLG_H__E56B285A_61D9_46EC_8212_1D71A3DF02BE__INCLUDED_)
#define AFX_SUBRCUBASEINFODLG_H__E56B285A_61D9_46EC_8212_1D71A3DF02BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubRCUBaseInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
#define WM_RCU_ADD      WM_USER+91
#define WM_RCU_DELETE   WM_USER+92
#define WM_RCU_MODIFY   WM_USER+93
// CSubRCUBaseInfoDlg dialog

class CSubRCUBaseInfoDlg : public CDialog
{
// Construction
public:
    PRCU_TYPE_ENTRY m_pRCUEntry;
	HTREEITEM		hItem;
public:
	void SetRelationItem(PVOID pItem);
	void UpdataRCU(PVOID lParam);
	CSubRCUBaseInfoDlg(CWnd* pParent = NULL);   // standard constructor
    ~CSubRCUBaseInfoDlg();
// Dialog Data
	//{{AFX_DATA(CSubRCUBaseInfoDlg)
	enum { IDD = IDD_SUB_RCU_BASEINFO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubRCUBaseInfoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubRCUBaseInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnModify();
	afx_msg void OnBtnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBRCUBASEINFODLG_H__E56B285A_61D9_46EC_8212_1D71A3DF02BE__INCLUDED_)
