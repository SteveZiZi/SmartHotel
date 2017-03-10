// WarnningDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailCFG.h"
#include "WarnningDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWarnningDlg dialog


CWarnningDlg::CWarnningDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWarnningDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWarnningDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWarnningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWarnningDlg)
	DDX_Control(pDX, IDD_TAB_WARNNING, m_WarnEntry);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWarnningDlg, CDialog)
	//{{AFX_MSG_MAP(CWarnningDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWarnningDlg message handlers

BOOL CWarnningDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitWarn();




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWarnningDlg::InitWarn()
{
	m_WarnEntry.InsertItem(0,"非法入室");
    m_WarnEntry.InsertItem(1,"房门开启");
}
