#pragma once
#include "afxcmn.h"


// CSubIoModuleDlg dialog

class CSubIoModuleDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubIoModuleDlg)

public:
	CSubIoModuleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubIoModuleDlg();

// Dialog Data
	enum { IDD = IDD_SUB_IO_MODULE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	void  InitAllDlgItemCtrl();
	PCHAR GetModuleName()	{		return _T("输入输出模块");		}		//模块名称
	void  SetModuleMemory(USHORT usSubName,LPVOID lParam)	{	nSubNameEntry = usSubName;	
						  pModule = (PMODULE_ENTRY)lParam;	}
	

	
	
	void  CleanSubItem(HTREEITEM hParent);
	void  FillModuleKeyReleasion(int nOffset,BOOL bFlag=FALSE);
	void  SetCfgModuleKey(UINT nOffset);
public:
	USHORT			nSubNameEntry;
	PMODULE_ENTRY	pModule;
	CComboBox		m_ComboEntryName[8];
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam);
	//afx_msg void OnViewConfigInfo();
	//afx_msg void OnSetConfigInfo();
public:
	CTreeCtrl m_KeyItemTree;
public:
	afx_msg void OnNMDblclkTreeItem(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnBnClickedBtnSave();
public:
	afx_msg void OnBnClickedBtnClear();
};
