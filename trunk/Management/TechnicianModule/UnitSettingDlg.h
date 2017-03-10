#if !defined(AFX_UNITSETTINGDLG_H__3E19F347_A918_4EC3_A9DE_886BD96DE761__INCLUDED_)
#define AFX_UNITSETTINGDLG_H__3E19F347_A918_4EC3_A9DE_886BD96DE761__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UnitSettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUnitSettingDlg dialog

class CUnitSettingDlg : public CDialog
{
public:
	LPVOID	lpRoom;
// Construction
public:
	CUnitSettingDlg(CWnd* pParent = NULL);   // standard constructor
	~CUnitSettingDlg();

public:
	DWORD GetRtuaValue(CString str);
	int GetConfigData(LPVOID lParam,PBYTE pBuf,int NodeNum); 
	void SetCfgDataBuffer(LPVOID lParam)	{ lpRoom = lParam;}
	void SetListFocus(int nSelect,BOOL Flag=TRUE);
	void InitAllItem();
	
// Dialog Data
	//{{AFX_DATA(CUnitSettingDlg)
	enum { IDD = IDD_UNIT_SETTING_DIALOG };
	CListCtrl	m_ModuleList;
	long			m_PortNumberValue;
	CString			m_Rcua;
	DWORD 			m_TargetIpAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnitSettingDlg)
	public:	
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUnitSettingDlg)
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnModify();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnAddAll();
	afx_msg void OnBtnDeleteAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnAddStage();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNITSETTINGDLG_H__3E19F347_A918_4EC3_A9DE_886BD96DE761__INCLUDED_)


