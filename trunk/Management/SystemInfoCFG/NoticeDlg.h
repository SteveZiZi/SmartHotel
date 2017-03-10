#if !defined(AFX_NOTICEDLG_H__2033DB31_3551_486D_97C2_6B4EE6061706__INCLUDED_)
#define AFX_NOTICEDLG_H__2033DB31_3551_486D_97C2_6B4EE6061706__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NoticeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNoticeDlg dialog

class CNoticeDlg : public CDialog
{
// Construction
public:
	void InitNotice();
	CNoticeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNoticeDlg)
	enum { IDD = IDD_NOTICE_DIALOG };
	CTabCtrl	m_NoticeEntry;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoticeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNoticeDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTICEDLG_H__2033DB31_3551_486D_97C2_6B4EE6061706__INCLUDED_)
