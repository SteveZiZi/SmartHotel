// SubNumberDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TechnicianModule.h"
#include "SubNumberDlg.h"

#define MAX_SUB_NUMBER_MODULE_NUM 2
const char pSubNumberName[][32] = {"门牌模块",""};
// CSubNumberDlg dialog

IMPLEMENT_DYNAMIC(CSubNumberDlg, CDialog)

CSubNumberDlg::CSubNumberDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubNumberDlg::IDD, pParent)
{

}

CSubNumberDlg::~CSubNumberDlg()
{
}

void CSubNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubNumberDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_GET_SUB_MODULE_NAME,&CSubNumberDlg::Msg_GetSubModuleName)
	ON_MESSAGE(WM_ENABLE_CTRL_ITEM,&CSubNumberDlg::Msg_EnableCtrlItem)
END_MESSAGE_MAP()


// CSubNumberDlg message handlers

BOOL CSubNumberDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSubNumberDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}


LRESULT CSubNumberDlg::Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam)
{
	CString str;

	str = _T("门牌配置无内容\n\n");
	str += _T("门牌显示房间的信息:\n");
	str += _T("1、 清理\n");
	str += _T("2、 勿扰\n");
	str += _T("3、 门铃\n");
	str += _T("相应的亮起表示当前的状态");
	SetDlgItemText(IDC_STATIC_ENTRY,str);
	return S_OK;
}


LRESULT CSubNumberDlg::Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam)
{
	int nEntry = (int)lParam;
	PCHAR *pSubName = (PCHAR *)wParam;

	(*pSubName) =  NULL;
	if (nEntry < MAX_SUB_NUMBER_MODULE_NUM)	{	(*pSubName) = (PCHAR)pSubNumberName[nEntry];	}
	if (strcmp((*pSubName),"") == 0)	{	(*pSubName) =  NULL;	}

	return S_OK;
}