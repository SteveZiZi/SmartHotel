// WelcomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "WelcomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWelcomDlg dialog


CWelcomDlg::CWelcomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWelcomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWelcomDlg)
	m_Mode = 1;
	//}}AFX_DATA_INIT
}


void CWelcomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcomDlg)
	DDX_Radio(pDX, IDC_RADIO_OPERATOR, m_Mode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWelcomDlg, CDialog)
	//{{AFX_MSG_MAP(CWelcomDlg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CWelcomDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcomDlg message handlers

BOOL CWelcomDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CWelcomDlg::GetSelectMode()
{
   return m_Mode;
}

void CWelcomDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
