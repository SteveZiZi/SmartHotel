#pragma once


// CRoomStatusDlg dialog

class CRoomStatusDlg : public CDialog
{
	DECLARE_DYNAMIC(CRoomStatusDlg)

public:
	CRoomStatusDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRoomStatusDlg();

// Dialog Data
	enum { IDD = IDD_ROOM_STATUS_DIALOG };
	PROOM_DETAIL_ENTRY lpRoomDetail;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnDestroy();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnBnClickedBtnTiming();
	afx_msg void OnBnClickedBtnGet();
	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnOK();

public:
	void UpDataRoomInfo(PVOID lParam);
	void UpdataAllItems(LPVOID lParam, BOOL Flag);
};
