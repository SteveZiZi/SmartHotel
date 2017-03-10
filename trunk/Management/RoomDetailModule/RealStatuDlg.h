#pragma once


// CRealStatuDlg dialog

class CRealStatuDlg : public CDialog
{
	DECLARE_DYNAMIC(CRealStatuDlg)

public:
	CRealStatuDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRealStatuDlg();

// Dialog Data
	enum { IDD = IDD_REAL_STATU_DLG };
	PROOM_DETAIL_ENTRY lpRoomDetail;

private:
	CComboBox m_ComEmergency;
	CComboBox m_ComCardStatus;
	CComboBox m_ComMagnetism;
	CComboBox m_ComSupply;
	CComboBox m_ComClean;
	CComboBox m_ComWash;
	CComboBox m_ComNoDistruct;
	CComboBox m_ComWait;
	CComboBox m_ComInfrared;
	CComboBox m_ComServce;
	CComboBox m_ComMagnetismBalcony;
	CComboBox m_ComBed;
	CComboBox m_ComSafe;
	CComboBox m_ComCheckOut;
	CComboBox m_ComAccount;
	CComboBox m_ComRepair;

	void UpdataRoomStatus(LPVOID lParam);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
public:
	virtual BOOL OnInitDialog();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnOK();
	afx_msg void OnDestroy();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnGet();
public:
	void UpDataRoomInfo(PVOID lParam);
};
