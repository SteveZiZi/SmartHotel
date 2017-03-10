// SubCardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TechnicianModule.h"
#include "SubCardDlg.h"

#define MAX_SUB_CARD_MODULE_NUM 2
const char pSubCardName[][32] = {"门卡模块",""};
// CSubCardDlg dialog

IMPLEMENT_DYNAMIC(CSubCardDlg, CDialog)

CSubCardDlg::CSubCardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubCardDlg::IDD, pParent)
{

}

CSubCardDlg::~CSubCardDlg()
{
}

void CSubCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubCardDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_GET_SUB_MODULE_NAME,&CSubCardDlg::Msg_GetSubModuleName)
	ON_MESSAGE(WM_ENABLE_CTRL_ITEM,&CSubCardDlg::Msg_EnableCtrlItem)
	//ON_MESSAGE(WM_ENABLE_CTRL_ITEM,,&CSubCardDlg::Msg_EnableCtrlItem)
END_MESSAGE_MAP()


// CSubCardDlg message handlers

BOOL CSubCardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSubCardDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}

LRESULT CSubCardDlg::Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam)
{
	CString str;
	str = _T("门卡配置无内容\n\n");
	str += _T("插卡取电带三种身份识别:\n");
	str += _T("1、 客人\n");
	str += _T("2、 服务员\n");
	str += _T("3、 管理人员\n");
	str += _T("根据插入的不同匙卡识别出插卡人的身份,由网络将信息传送至楼层及前台计算机,");
	str += _T("显示“匙入/匙出”图标并有时间记录,方便酒店掌握必要信息,");
	str += _T("插入无效匙卡(指定匙卡外的任何物件),系统不响应\n");

	SetDlgItemText(IDC_STATIC_ENTRY,str);
	return S_OK;
}
LRESULT CSubCardDlg::Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam)
{
	int nEntry = (int)lParam;
	PCHAR *pSubName = (PCHAR *)wParam;

	(*pSubName) =  NULL;
	if (nEntry < MAX_SUB_CARD_MODULE_NUM)	{	(*pSubName) = (PCHAR)pSubCardName[nEntry];	}
	if (strcmp((*pSubName),"") == 0)	{	(*pSubName) =  NULL;	}

	return S_OK;
}