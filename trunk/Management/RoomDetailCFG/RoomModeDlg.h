#if !defined(AFX_ROOMMODEDLG_H__98AF86C6_F6CE_4B15_A733_EE4F00501765__INCLUDED_)
#define AFX_ROOMMODEDLG_H__98AF86C6_F6CE_4B15_A733_EE4F00501765__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RoomModeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRoomModeDlg dialog

class CRoomModeDlg : public CDialog
{
// Construction
public:
	void InitRoomMode();
	CRoomModeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRoomModeDlg)
	enum { IDD = IDD_ROOMMODE_DIALOG };
	CTabCtrl	m_RoomMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomModeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRoomModeDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMMODEDLG_H__98AF86C6_F6CE_4B15_A733_EE4F00501765__INCLUDED_)
