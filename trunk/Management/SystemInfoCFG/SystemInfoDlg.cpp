// SystemInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoCFG.h"
#include "SystemInfoDlg.h"


// CSystemInfoDlg dialog

IMPLEMENT_DYNAMIC(CSystemInfoDlg, CDialog)

CSystemInfoDlg::CSystemInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemInfoDlg::IDD, pParent)
{

}

CSystemInfoDlg::~CSystemInfoDlg()
{
}

void CSystemInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_EDIT_HOTEL_NAME,m_EditHotelName);
	DDX_Control(pDX,IDC_COM_LANGUAGE,m_ComLanguage);
	DDX_Control(pDX,IDC_COM_STYLE,m_ComStyle);
	DDX_Control(pDX,IDC_COM_ROOM_STATUS,m_ComRoomStatus);
	DDX_Control(pDX,IDC_COM_DOOR_SWITCH,m_ComDoorSwitch);
}


BEGIN_MESSAGE_MAP(CSystemInfoDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CSystemInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	SetDlgItemText(IDC_EDIT_HOTEL_NAME,"°ÙÄÁ¾Æµê");
	m_ComLanguage.SetCurSel(0);
	m_ComStyle.SetCurSel(0);
	m_ComRoomStatus.SetCurSel(0);
	m_ComDoorSwitch.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSystemInfoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

void CSystemInfoDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CSystemInfoDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}

void CSystemInfoDlg::OnOK()
{

}

// CSystemInfoDlg message handlers
