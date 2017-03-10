// RoomModeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailCFG.h"
#include "RoomModeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomModeDlg dialog


CRoomModeDlg::CRoomModeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomModeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomModeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRoomModeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomModeDlg)
	DDX_Control(pDX, IDD_TAB_ROOMMODE, m_RoomMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRoomModeDlg, CDialog)
	//{{AFX_MSG_MAP(CRoomModeDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomModeDlg message handlers

BOOL CRoomModeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitRoomMode();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRoomModeDlg::InitRoomMode()
{
    m_RoomMode.InsertItem(0,"入住模式");
    m_RoomMode.InsertItem(1,"待住模式");
    m_RoomMode.InsertItem(2,"退房模式");
    m_RoomMode.InsertItem(3,"待住模式");
}
