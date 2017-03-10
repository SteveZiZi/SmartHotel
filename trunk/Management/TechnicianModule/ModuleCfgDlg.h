#pragma once
#include "afxwin.h"
#include "afxcmn.h"
//=======================================================================================================
#include "SubOutPutModuleDlg.h"				//���ģ��
#include "SubButtonModuleDlg.h"				//����ģ��
#include "SubAirConditionModuleDlg.h"		//�յ�ģ��
#include "SubIoModuleDlg.h"					//�������ģ��
#include "SubCardDlg.h"						//�ſ�ģ��
#include "SubNumberDlg.h"					//����ģ��
#include "SubStageModuleDlg.h"				//�龰ģ��
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

