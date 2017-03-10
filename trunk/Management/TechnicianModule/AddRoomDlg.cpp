// AddRoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TechnicianModule.h"
#include "AddRoomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddRoomDlg dialog


CAddRoomDlg::CAddRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddRoomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddRoomDlg)
	m_RoomName = _T("");
	nMethod = 0;
	//}}AFX_DATA_INIT
}


void CAddRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddRoomDlg)
	DDX_Control(pDX, IDC_COMBO_CON_METHOD, m_ConMethod);
	DDX_Text(pDX, IDC_EDIT_ROOM_NAME, m_RoomName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddRoomDlg, CDialog)
	//{{AFX_MSG_MAP(CAddRoomDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddRoomDlg message handlers

BOOL CAddRoomDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_ConMethod.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CAddRoomDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		//屏掉回车和退出键
		if(pMsg->wParam == VK_RETURN  || pMsg->wParam == VK_ESCAPE)
		  return TRUE;

		if(pMsg->wParam == VK_UP  || pMsg->wParam == VK_DOWN)
		  return TRUE;

		if(pMsg->wParam == VK_LEFT  || pMsg->wParam == VK_RIGHT)
		  return TRUE;

	}		
	return CDialog::PreTranslateMessage(pMsg);
}

void CAddRoomDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
//==============================================================================
	m_RoomName.TrimLeft();
	m_RoomName.TrimRight();
	if (m_RoomName.IsEmpty())	{	MessageBox("客房名不能为空");	return;	}
	nMethod = m_ConMethod.GetCurSel();
	if (nMethod == -1)	{	MessageBox("请先选择通信方式");	return;	}

	CDialog::OnOK();
}

void CAddRoomDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
