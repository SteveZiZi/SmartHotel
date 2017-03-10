// KeyDefineDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailCFG.h"
#include "KeyDefineDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeyDefineDlg dialog


CKeyDefineDlg::CKeyDefineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyDefineDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyDefineDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CKeyDefineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyDefineDlg)
	DDX_Control(pDX, IDD_TAB_KEY_DEFINE, m_KeyEntry);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKeyDefineDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyDefineDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyDefineDlg message handlers

BOOL CKeyDefineDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitKeyEntry();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CKeyDefineDlg::InitKeyEntry()
{
   m_KeyEntry.InsertItem(0,"客人卡");
   m_KeyEntry.InsertItem(1,"清洁卡");
   m_KeyEntry.InsertItem(2,"会员卡");
}
