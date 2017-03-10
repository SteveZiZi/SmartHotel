#pragma once
#include "afxwin.h"
// CSubOutPutModuleDlg dialog
class CSubOutPutModuleDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubOutPutModuleDlg)
public:
	enum _OUT_PUT_MODULE
	{
		MODULE_SINGLE,
		MODULE_TWO,
		MODULE_FOUR,
		MODULE_SIX,
		MODULE_EIGHT
	};
public:
	CSubOutPutModuleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubOutPutModuleDlg();

// Dialog Data
	enum { IDD = IDD_SUB_OUTPUT_MODULE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	void  InitAllDlgItemCtrl();
	PCHAR GetModuleName()	{		return _T("输出型继电器模块");		}		//模块名称
	void  SetModuleMemory(USHORT usSubName,LPVOID lParam)	{	nSubNameEntry = usSubName;	
						  pModule = (PMODULE_ENTRY)lParam;	}
public:
	USHORT			nSubNameEntry;
	PMODULE_ENTRY	pModule;
	CComboBox		m_ComboEntryName[8];
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam);


public:

public:
	afx_msg void OnBnClickedBtnSave();
public:
	afx_msg void OnBnClickedBtnClear();
};

