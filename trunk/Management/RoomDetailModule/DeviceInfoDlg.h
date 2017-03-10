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
	//afx_msg void OnKillfocusEdit();//动态生成编辑框失去焦点响应函数
	afx_msg void OnKillfocusCcomboBox();//动态生成下拉列表框失去焦点响应函数

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

	int e_Item;    //刚编辑的行  
	int e_SubItem; //刚编辑的列 
	CComboBox m_comBox; //生产单元格下拉列表对象
	bool haveccomboboxcreate;//标志下拉列表框已经被创建
	void createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccomboboxobj, int &Item, int &SubItem, bool &havecreat);//创建单元格下拉列表框函数
	void distroyCcombobox(CListCtrl *list, CComboBox* distroyccomboboxobj, int &Item, int &SubItem);//销毁单元格下拉列表框
	
	void UpdataList(PVOID lParam);
	void WriteDataToPack(PVOID lParam);
	void InitDataList();
	void InsertOneRow(int Entry,LPVOID lParam);
public:
	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnBnClickedButGet();
};
