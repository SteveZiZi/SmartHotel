#pragma once


// CSubNumberDlg dialog

class CSubNumberDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubNumberDlg)

public:
	CSubNumberDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubNumberDlg();

// Dialog Data
	enum { IDD = IDD_SUB_NUMBER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	USHORT			nSubNameEntry;
	PMODULE_ENTRY	pModule;
public:
	PCHAR GetModuleName()	{		return _T("门牌模块");		}		//模块名称
	void  SetModuleMemory(USHORT usSubName,LPVOID lParam)	{	nSubNameEntry = usSubName;	
	pModule = (PMODULE_ENTRY)lParam;	}
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam);
};
