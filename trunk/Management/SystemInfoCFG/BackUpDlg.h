#if !defined(AFX_BACKUPDLG_H__7986286E_A416_46A3_8D4C_240EEB309987__INCLUDED_)
#define AFX_BACKUPDLG_H__7986286E_A416_46A3_8D4C_240EEB309987__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackUpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackUpDlg dialog

class CBackUpDlg : public CDialog
{
// Construction
public:
	CBackUpDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBackUpDlg)
	enum { IDD = IDD_BACKUP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
private:
	CListCtrl m_FileList;
	CString	m_FileName;
	CString m_PathName;

	void InitList();
	void UpdataList(BOOL flag);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackUpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	virtual BOOL OnInitDialog();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnDestroy();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBackUpDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnBackup();
	afx_msg void OnBnClickedBtnImport();
	afx_msg void OnLvnItemchangedListFile(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnOK();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKUPDLG_H__7986286E_A416_46A3_8D4C_240EEB309987__INCLUDED_)
