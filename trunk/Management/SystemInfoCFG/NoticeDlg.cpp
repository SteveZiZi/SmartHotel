// NoticeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoCFG.h"
#include "NoticeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoticeDlg dialog


CNoticeDlg::CNoticeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNoticeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNoticeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNoticeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNoticeDlg)
	DDX_Control(pDX, IDD_TAB_NOTICE_SETTING, m_NoticeEntry);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNoticeDlg, CDialog)
	//{{AFX_MSG_MAP(CNoticeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoticeDlg message handlers

BOOL CNoticeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitNotice();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNoticeDlg::InitNotice()
{
  m_NoticeEntry.InsertItem(0,"欢迎词");
  m_NoticeEntry.InsertItem(1,"天气预报");
  m_NoticeEntry.InsertItem(2,"紧急情况");
  m_NoticeEntry.InsertItem(3,"新闻时事");
}
