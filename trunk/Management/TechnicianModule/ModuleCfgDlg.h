#pragma once
#include "afxwin.h"
#include "afxcmn.h"
//=======================================================================================================
#include "SubOutPutModuleDlg.h"				//输出模块
#include "SubButtonModuleDlg.h"				//按键模块
#include "SubAirConditionModuleDlg.h"		//空调模块
#include "SubIoModuleDlg.h"					//输入输出模块
#include "SubCardDlg.h"						//门卡模块
#include "SubNumberDlg.h"					//门牌模块
#include "SubStageModuleDlg.h"				//情景模块
#include "SubStageDlg.h"

// CModuleCfgDlg dialog

class CModuleCfgDlg : public CDialog
{
	DECLARE_DYNAMIC(CModuleCfgDlg)

public:
	CModuleCfgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModuleCfgDlg();

// Dialog Data
	enum { IDD = IDD_MODULE_CFG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCbnSelchangeComboModuleType();
	afx_msg void OnCbnSelchangeComboModuleName();
	afx_msg LRESULT Msg_UpdataSelectRoomCfg(WPARAM wParam,LPARAM lParam);

public:
	CComboBox	m_ConMethod;
	CComboBox m_ComModuleName;
	CComboBox m_ComModuleType;
	CListCtrl m_ModuleList;
	DWORD m_ModuleAddress;
	//=============================================================================
	CWnd		*pSelModuleWnd;
	CSubOutPutModuleDlg				*pSubOutModuleDlg;
	CSubButtonModuleDlg				*pSubButtonModuleDlg;
	CSubAirConditionModuleDlg		*pSubAirConditionModuleDlg;
	CSubIoModuleDlg					*pSubIoModuleDlg;
//	CSubStageModuleDlg				*pSubStageModuleDlg;
	CSubCardDlg						*pSubCardDlg;
	CSubNumberDlg					*pSubNumberDlg;

	CSubStageDlg					*pSubStageDlg;
public:
	void    InitDeviceTypeKey();
	void	InitListCtrl();
	void	InitAllSubModule();
	void	ActiveSelModule(CWnd *pWnd,UINT nSubItem,PVOID lParam);
	void	InsertOneModuleToList(PMODULE_ENTRY pModule);
public:
	afx_msg void OnBnClickedBtnAdd();
public:
	afx_msg void OnLvnItemchangedModuleList(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CComboBox m_DeviceTypeKey;
	afx_msg void OnBnClickedBtnDelete();
};

