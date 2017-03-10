// SubCardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TechnicianModule.h"
#include "SubCardDlg.h"

#define MAX_SUB_CARD_MODULE_NUM 2
const char pSubCardName[][32] = {"�ſ�ģ��",""};
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
	str = _T("�ſ�����������\n\n");
	str += _T("�忨ȡ����������ʶ��:\n");
	str += _T("1�� ����\n");
	str += _T("2�� ����Ա\n");
	str += _T("3�� ������Ա\n");
	str += _T("���ݲ���Ĳ�ͬ�׿�ʶ����忨�˵����,�����罫��Ϣ������¥�㼰ǰ̨�����,");
	str += _T("��ʾ������/�׳���ͼ�겢��ʱ���¼,����Ƶ����ձ�Ҫ��Ϣ,");
	str += _T("������Ч�׿�(ָ���׿�����κ����),ϵͳ����Ӧ\n");

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