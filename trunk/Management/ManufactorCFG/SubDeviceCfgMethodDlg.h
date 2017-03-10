#pragma once
#include "MyPictureEx.h"
#include "PictureEx.h"

// CSubDeviceCfgMethodDlg dialog

class CSubDeviceCfgMethodDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubDeviceCfgMethodDlg)

public:
	CSubDeviceCfgMethodDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDeviceCfgMethodDlg();

	void UpdataRCU(PVOID lParam);
	void SetRelationItem(PVOID pItem);
	BOOL CheckRoomExist(LPVOID lParam);

	PRCU_TYPE_ENTRY m_pRCUEntry;
	HTREEITEM		hItem;
	PDEVICE_CFG_METHOD m_pModuleEntry;

// Dialog Data
	enum { IDD = IDD_SUB_DEVICE_METHOD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnClose();
public:
	afx_msg void OnDestroy();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnBnClickedBtnAdd();
public:
	afx_msg void OnBnClickedBtnModify();
public:
	afx_msg void OnBnClickedBtnDelete();

	afx_msg void OnCbnSelchangeComboDeviceType();

	afx_msg void OnItemchangedListRoom(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnStnClickedPicture();
public:
	afx_msg void OnOK();

private:
	CComboBox m_DeviceEntry;
	CComboBox m_DeviceType;
	CComboBox m_DeviceSubNum;
	CEdit m_SubName;
	CButton m_AddBtn;
	CButton m_ModifyBtn;
	CButton m_DeleteBtn;
	CListCtrl m_DataList;
	CMyPictureEx m_Picture;
	CString m_FileName;

	void InitDataList();
	void InsertOneRow(int Entry,LPVOID lParam);
	void UpdataListRow(int Entry,LPVOID lParam);
	CString OnModifyPicture();
};
