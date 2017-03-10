#pragma once
#include "afxcmn.h"
#include "AirConditionDlg.h"
#include "DeviceInfoDlg.h"
#include "RoomStatusDlg.h"
#include "RealStatuDlg.h"
// CMainRoomInfoDlg dialog

class CMainRoomInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainRoomInfoDlg)

public:
	CMainRoomInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMainRoomInfoDlg();

// Dialog Data
	enum { IDD = IDD_ROOMINFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	LPVOID lParamBuf;
	int		nSelect;
	CRoomStatusDlg		*pRoomStatusDlg;
	CDeviceInfoDlg		*pDeviceInfoDlg;
	CAirConditionDlg	*pAirConditionDlg;
	CRealStatuDlg		*pRealStatuDlg;

public:
	void SetDataBuffer(LPVOID lParam);
	void InitGolabVariant();




	void InitTabCtrl();
	void InitAllSubDlg(BOOL bFlag=FALSE);
	void ShowSelectEntry(int nEntry);
public:
	afx_msg void OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult);
};
