#pragma once
#include "afxwin.h"


// CSubAirConditionModuleDlg dialog

class CSubAirConditionModuleDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubAirConditionModuleDlg)

public:
	CSubAirConditionModuleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubAirConditionModuleDlg();

// Dialog Data
	enum { IDD = IDD_SUB_AIRCONDITION_MODULE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	void  InitAllDlgItemCtrl();
	PCHAR GetModuleName()	{		return _T("空调模块");		}		//模块名称
	void  SetModuleMemory(USHORT usSubName,LPVOID lParam)	{	nSubNameEntry = usSubName;	
	pModule = (PMODULE_ENTRY)lParam;	}
	void  InitSpecialFunCombo();
	
	
	
	
	void  FillModuleKeyReleasion(int nOffset);
	void  SetCfgModuleKey(UINT nOffset);
public:
	USHORT			nSubNameEntry;
	PMODULE_ENTRY	pModule;
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam);
public:
	CComboBox m_SpecialFun[4];
	CComboBox mEntryKey[4];
	CComboBox mModuleName[4];
public:
	afx_msg void OnStnDblclickStaticEntry1();
public:
	afx_msg void OnStnDblclickStaticEntry2();
public:
	afx_msg void OnStnDblclickStaticEntry3();
public:
	afx_msg void OnStnDblclickStaticEntry4();
public:
	afx_msg void OnCbnSelchangeValidModuleName();
public:
	afx_msg void OnCbnSelchangeValidModuleName2();
public:
	afx_msg void OnCbnSelchangeValidModuleName3();
public:
	afx_msg void OnCbnSelchangeValidModuleName4();
};
