#pragma once


// CSubStageModuleDlg dialog

class CSubStageModuleDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubStageModuleDlg)

public:
	CSubStageModuleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubStageModuleDlg();

// Dialog Data
	enum { IDD = IDD_SUB_STAGE_MODULE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	PCHAR GetModuleName()	{		return _T("场景模式");		}		//模块名称
	void  SetModuleMemory(USHORT usSubName,LPVOID lParam)	{	nSubNameEntry = usSubName;	
	pModule = (PMODULE_ENTRY)lParam;	}
	void  InitSpecialFunCombo();


	void  SetCfgModuleKey(UINT nOffset);
	void  FillModuleKeyReleasion(int nOffset);
public:
	USHORT			nSubNameEntry;
	PMODULE_ENTRY	pModule;
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam);
public:
	CComboBox m_SpecialFun[10];
	CComboBox mEntryKey[10];
	CComboBox mModuleName[10];
public:
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	afx_msg void OnCbnSelchangeValidModuleName();
	void OnSelchangeValidModuleName(int nOffset);
public:
	afx_msg void OnStnDblclickStaticEntry();
	afx_msg void OnStnDblclickStaticEntry1();
	afx_msg void OnStnDblclickStaticEntry2();
	afx_msg void OnStnDblclickStaticEntry3();
	afx_msg void OnStnDblclickStaticEntry4();
	afx_msg void OnStnDblclickStaticEntry5();
	afx_msg void OnStnDblclickStaticEntry6();
	afx_msg void OnStnDblclickStaticEntry7();
	afx_msg void OnStnDblclickStaticEntry8();
	afx_msg void OnStnDblclickStaticEntry9();
};
