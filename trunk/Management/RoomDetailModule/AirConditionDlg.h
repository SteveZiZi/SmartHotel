#pragma once


// CAirConditionDlg dialog

class CAirConditionDlg : public CDialog
{
	DECLARE_DYNAMIC(CAirConditionDlg)

public:
	CAirConditionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAirConditionDlg();

// Dialog Data
	enum { IDD = IDD_AIR_CONDITION_DIALOG };
	PROOM_DETAIL_ENTRY lpRoomDetail;

private:
	CComboBox m_CobSeaonMode;
	CComboBox m_CobWorkMode;
	CComboBox m_CobFanSpeed;
	CComboBox m_CobAirNum;
	CEdit m_EditSetTempl;
	CEdit m_EditEnvTempl;

	
	void UpdataAirNum(LPVOID lParam);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
//	virtual void PreInitDialog();
public:
	virtual BOOL OnInitDialog();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnDestroy();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnGet();
	afx_msg void OnBnClickedBtnSet();
	void UpDataRoomInfo(PVOID lParam);
	void UpdataAllItems(LPVOID lParam, BOOL Flag);
	void initAirCondition();
	afx_msg void OnBnClickedBtnFlush();
	afx_msg void OnOK();
};
