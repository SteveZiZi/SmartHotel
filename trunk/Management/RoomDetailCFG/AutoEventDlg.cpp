// AutoEventDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailCFG.h"
#include "AutoEventDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoEventDlg dialog


CAutoEventDlg::CAutoEventDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoEventDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAutoEventDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAutoEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAutoEventDlg)
	DDX_Control(pDX, IDD_TAB_AUTOEVENT, m_Event);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAutoEventDlg, CDialog)
	//{{AFX_MSG_MAP(CAutoEventDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoEventDlg message handlers

BOOL CAutoEventDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitEvent();




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAutoEventDlg::InitEvent()
{
    m_Event.InsertItem(0,"入住事件");
    m_Event.InsertItem(1,"退房事件");
    m_Event.InsertItem(2,"待住事件");
    m_Event.InsertItem(3,"预订事件");
}
