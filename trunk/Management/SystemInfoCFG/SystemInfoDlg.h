#pragma once


// CSystemInfoDlg dialog

class CSystemInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemInfoDlg)

public:
	CSystemInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSystemInfoDlg();

// Dialog Data
	enum { IDD = IDD_SYSTEMINFODLG };
private:
	CEdit	m_EditHotelName;
	CComboBox	m_ComLanguage;
	CComboBox	m_ComStyle;
	CComboBox	m_ComRoomStatus;
	CComboBox	m_ComDoorSwitch;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
public:
	virtual BOOL OnInitDialog();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnDestroy();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnOK();
	DECLARE_MESSAGE_MAP()
};
