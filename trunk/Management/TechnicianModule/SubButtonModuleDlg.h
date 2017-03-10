#pragma once


// CSubButtonModuleDlg �Ի���

class CSubButtonModuleDlg : public CDialog
{
	DECLARE_DYNAMIC(CSubButtonModuleDlg)

public:
	CSubButtonModuleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSubButtonModuleDlg();

// �Ի�������
	enum { IDD = IDD_SUB_BUTTON_MODULE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	void  InitAllDlgItemCtrl();
	PCHAR GetModuleName()	{		return _T("��·����ģ��");		}		//ģ������
	void  SetModuleMemory(USHORT usSubName,LPVOID lParam)	{	nSubNameEntry = usSubName;	
						  pModule = (PMODULE_ENTRY)lParam;	}
	void  FillModuleKeyReleasion(int nOffset);
	void  SetCfgModuleKey(UINT nOffset);
	void  InitPopMenu();
public:
	USHORT			nSubNameEntry;
	PMODULE_ENTRY	pModule;
	CListCtrl		m_ReleasionList;
	CMenu			mRmenu;
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg LRESULT Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedItemEntry();
	afx_msg void OnViewConfigInfo();
	afx_msg void OnSetConfigInfo();
public:

};




