#pragma once


// CRoomStyleDlg dialog

class CRoomStyleDlg : public CDialog
{
	DECLARE_DYNAMIC(CRoomStyleDlg)

public:
	CRoomStyleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRoomStyleDlg();

// Dialog Data
	enum { IDD = IDD_ROOMSTYLEDLG };
public:
	BOOL m_CheckEmergency;
	BOOL m_CheckDoorStatus;
	BOOL m_CheckmMagnetmis;
	BOOL m_CheckSupply;
	BOOL m_CheckClean;
	BOOL m_CheckWash;
	BOOL m_CheckNoDistruct;
	BOOL m_CheckWait;

	BOOL m_CheckInfrared;
	BOOL m_CheckServer;
	BOOL m_CheckBalconyMagnetmis;
	BOOL m_CheckBed;
	BOOL m_CheckSafe;
	BOOL m_CheckCheckOut;
	BOOL m_CheckAccount;
	BOOL m_CheckRepair;

	void InitAllItems();

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
	afx_msg void OnBnClickedBtnSave();
};
