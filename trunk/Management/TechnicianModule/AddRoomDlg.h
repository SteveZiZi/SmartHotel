#if !defined(AFX_ADDROOMDLG_H__4D0F71B8_1B69_4E5E_9534_E01E2333AFCF__INCLUDED_)
#define AFX_ADDROOMDLG_H__4D0F71B8_1B69_4E5E_9534_E01E2333AFCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddRoomDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddRoomDlg dialog

class CAddRoomDlg : public CDialog
{
public:
	int	nMethod;
// Construction
public:
	CAddRoomDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddRoomDlg)
	enum { IDD = IDD_ADD_ROOM_DIALOG };
	CComboBox	m_ConMethod;
	CString		m_RoomName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddRoomDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddRoomDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDROOMDLG_H__4D0F71B8_1B69_4E5E_9534_E01E2333AFCF__INCLUDED_)
