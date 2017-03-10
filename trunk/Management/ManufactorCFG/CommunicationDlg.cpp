// CommunicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManufactorCFG.h"
#include "CommunicationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommunicationDlg dialog


CCommunicationDlg::CCommunicationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommunicationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommunicationDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCommunicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommunicationDlg)
	DDX_Control(pDX, IDC_TAB_METHOD, m_tMethod);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommunicationDlg, CDialog)
	//{{AFX_MSG_MAP(CCommunicationDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommunicationDlg message handlers

BOOL CCommunicationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitCommunicationMethod();



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCommunicationDlg::InitCommunicationMethod()
{
    m_tMethod.InsertItem(0,"串口");
    m_tMethod.InsertItem(1,"TCP/IP");
    m_tMethod.InsertItem(2,"CAN");
//    m_tDevice.InsertItem(3,"节电开关"); 
}
