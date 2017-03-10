// SystemSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoCFG.h"
#include "SystemSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSystemSettingDlg dialog


CSystemSettingDlg::CSystemSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemSettingDlg::IDD, pParent)
{
	nSelect = 0;
	pSystemInfoDlg = NULL;
	pRoomStyleDlg = NULL;
	//{{AFX_DATA_INIT(CSystemSettingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSystemSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSystemSettingDlg)
	DDX_Control(pDX, IDD_TAB_SYSTEM_SETTING, m_SystemNenu);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSystemSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CSystemSettingDlg)
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDD_TAB_SYSTEM_SETTING, &CSystemSettingDlg::OnTcnSelchangeMainTab)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSystemSettingDlg message handlers
BOOL CSystemSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitAllSubDlg();
	InitSystemSettingMenu();




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSystemSettingDlg::OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int nEntry = m_SystemNenu.GetCurSel();
	if (nEntry == -1)	{	return;	}
	ShowSelectEntry(nEntry);

	*pResult = 0;
}

void CSystemSettingDlg::InitSystemSettingMenu()
{//m_SystemNenu
	m_SystemNenu.InsertItem(0,"系统设置");
    m_SystemNenu.InsertItem(1,"客房样式");
	
	m_SystemNenu.SetCurSel(nSelect);

	//nSelect = m_SystemNenu.GetCurSel();
	ShowSelectEntry(nSelect);
}

void CSystemSettingDlg::InitAllSubDlg()
{
	if (pSystemInfoDlg == NULL){
		pSystemInfoDlg = new CSystemInfoDlg;
		pSystemInfoDlg->Create(IDD_SYSTEMINFODLG,GetDlgItem(IDC_SYSTEM_SETTING_DIALOG));
		pSystemInfoDlg->ShowWindow(SW_HIDE);
	}

	if (pRoomStyleDlg == NULL){
		pRoomStyleDlg = new CRoomStyleDlg;
		pRoomStyleDlg->Create(IDD_ROOMSTYLEDLG,GetDlgItem(IDC_SYSTEM_SETTING_DIALOG));
		pRoomStyleDlg->ShowWindow(SW_HIDE);
	}
	else{
	if (pSystemInfoDlg != NULL)	{	delete pSystemInfoDlg;	pSystemInfoDlg = NULL;	}
	if (pRoomStyleDlg != NULL)	{	delete pRoomStyleDlg;	pRoomStyleDlg = NULL;	}
	}
}

void CSystemSettingDlg::ShowSelectEntry(int nEntry)
{
	if(nEntry == 0){
		pSystemInfoDlg->ShowWindow(SW_SHOWNORMAL);
		pRoomStyleDlg->ShowWindow(SW_HIDE);
	}else if(nEntry == 1){
		pSystemInfoDlg->ShowWindow(SW_HIDE);
		pRoomStyleDlg->ShowWindow(SW_SHOWNORMAL);
	}
	else{
		pSystemInfoDlg->ShowWindow(SW_HIDE);
		pRoomStyleDlg->ShowWindow(SW_HIDE);
	}
}

void CSystemSettingDlg::OnOK()
{

}