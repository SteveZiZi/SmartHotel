#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSubStageDlg dialog

class CSubStageDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubStageDlg)

public:
	CSubStageDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubStageDlg();

// Dialog Data
	enum { IDD = IDD_SUB_STAGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:

	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam);
public:
	afx_msg void OnBnClickedBtnClean();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnDelete();
	void  SetModuleMemory(USHORT usSubName,LPVOID lParam)	{	nSubNameEntry = usSubName;	
				m_pModule = (PMODULE_ENTRY)lParam;	}


public:
	CComboBox m_ComboSpecialFun;
	DWORD mArgument;
	CComboBox m_ModuleName;
	CComboBox m_SubEntry;

	USHORT			nSubNameEntry;
	PMODULE_ENTRY	m_pModule;
public:
	PCHAR GetModuleName()	{		return _T("场景模式");		}		//模块名称
	void InitSpecialFunCombo();
	void InitListCtrl();
	void InitModule();
	void InitListModule();
	//void UpdateListCtrl(LPVOID lParam);
	void UpdateListCtrl(LPVOID lParam,int n);
	int  nFindStringInList(LPVOID lParam);
public:
	PCONTROL_DEVICE_UNIT GetFreeEntryMem();
	PCONTROL_DEVICE_UNIT SearchModuleExist(PCONTROL_DEVICE_UNIT pCtrlUnit);
public:
	CListCtrl m_DataList;
public:
	afx_msg void OnCbnSelchangeComboModuleEntry();
public:
	afx_msg void OnLvnItemchangedDataList(NMHDR *pNMHDR, LRESULT *pResult);
};
