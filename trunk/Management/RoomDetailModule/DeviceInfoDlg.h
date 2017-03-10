#pragma once


// CDeviceInfoDlg dialog

class CDeviceInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeviceInfoDlg)

public:
	CDeviceInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDeviceInfoDlg();
	CListCtrl m_DeviceList;

// Dialog Data
	enum { IDD = IDD_DEVICE_INFO_DIALOG };
	PROOM_DETAIL_ENTRY lpRoomDetail;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnOK();
public:
	afx_msg void OnDestroy();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMClickListDevicedata(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnKillfocusEdit();//��̬���ɱ༭��ʧȥ������Ӧ����
	afx_msg void OnKillfocusCcomboBox();//��̬���������б��ʧȥ������Ӧ����

	void UpDataRoomInfo(PVOID lParam);
	void InitDeviceInfo();

private:
	enum DeviceType
	{
		RELAY_EIGHT = 2,
		LIGHT_FOUR,
		RELAY_TWO,
		LIGHT_THREE
	};

	int e_Item;    //�ձ༭����  
	int e_SubItem; //�ձ༭���� 
	CComboBox m_comBox; //������Ԫ�������б����
	bool haveccomboboxcreate;//��־�����б���Ѿ�������
	void createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccomboboxobj, int &Item, int &SubItem, bool &havecreat);//������Ԫ�������б����
	void distroyCcombobox(CListCtrl *list, CComboBox* distroyccomboboxobj, int &Item, int &SubItem);//���ٵ�Ԫ�������б��
	
	void UpdataList(PVOID lParam);
	void WriteDataToPack(PVOID lParam);
	void InitDataList();
	void InsertOneRow(int Entry,LPVOID lParam);
public:
	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnBnClickedButGet();
};
