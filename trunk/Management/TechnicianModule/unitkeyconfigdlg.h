#if !defined(AFX_UNITKEYCONFIGDLG_H__417C5723_0DB6_4DB5_AE9E_5A662B27E1EF__INCLUDED_)
#define AFX_UNITKEYCONFIGDLG_H__417C5723_0DB6_4DB5_AE9E_5A662B27E1EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UnitKeyConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUnitKeyConfigDlg dialog

class CUnitKeyConfigDlg : public CDialog
{
// Construction
public:
	CUnitKeyConfigDlg(CWnd* pParent = NULL);   // standard constructor
	CUnitKeyConfigDlg(int nEntry,CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CUnitKeyConfigDlg)
	enum { IDD = IDD_CONFIG_KEY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnitKeyConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUnitKeyConfigDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	afx_msg void OnCmdCleanAll();
	afx_msg void OnCmdAddReleasion();
	afx_msg void OnCmdModifyReleasion();
	afx_msg void OnCmdDeleteReleasion();
public:
	void InitSpecialFunCombo();
	void InitListCtrlStyle();
	void InitListMenu();
	//===============================================================================
	void FillListCtrl();
	void FillModuleCtrl();

	void SetParamValidFlag(BOOL bFlag)	{	bParamFlag = bFlag;	}
	void SetKeyMemory(LPVOID lParam)	{	pKeyUnit = (PMODULE_KEY_UNIT)lParam;	}

	int  SearchExistCtrlDevice(UINT nModule,UINT nSubItem);
	BOOL InsertOneRow(LPVOID lParam,BOOL bFlag=FALSE);
	void UpDateListRowContext(int nRow,LPVOID lParam);
	PCONTROL_DEVICE_UNIT GetEmptyCtrlDeviceUnit(int nModuleEntry,int nKeyEntry,BOOL bFlag=TRUE);
public:
	BOOL		bParamFlag;
	CListCtrl	m_ReleasionList;
	CComboBox	m_ComboSpecialFun;
	CComboBox   m_ComboModuleName;
	CComboBox   m_ComboSubKey;
	int			mAdditionalParam;
	int			m_Entry;

	CMenu				mRmenu;
	PMODULE_KEY_UNIT	pKeyUnit;
public:
	afx_msg void OnCbnSelchangeValidModuleName();
public:
	afx_msg void OnNMRclickReleasionList(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnLvnItemchangedReleasionList(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNITKEYCONFIGDLG_H__417C5723_0DB6_4DB5_AE9E_5A662B27E1EF__INCLUDED_)


