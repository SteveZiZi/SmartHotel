// SubRCUBaseInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManufactorCFG.h"
#include "SubRCUBaseInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubRCUBaseInfoDlg dialog


CSubRCUBaseInfoDlg::CSubRCUBaseInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubRCUBaseInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubRCUBaseInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	hItem = NULL;
	m_pRCUEntry = NULL;
}

CSubRCUBaseInfoDlg::~CSubRCUBaseInfoDlg()
{
	  ::SendMessage(::GetParent(GetParent()->GetSafeHwnd()),BM_ADD_DB_ENTRY,(WPARAM)hItem,(LPARAM)m_pRCUEntry);	

	
}

void CSubRCUBaseInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubRCUBaseInfoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubRCUBaseInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CSubRCUBaseInfoDlg)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MODIFY, OnBtnModify)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubRCUBaseInfoDlg message handlers

BOOL CSubRCUBaseInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here
	//m_pRCUType = new RCUTYPE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubRCUBaseInfoDlg::UpdataRCU(PVOID lParam)
{
	//PRCU_TYPE_ENTRY m_pEntryInfo;
	m_pRCUEntry = (PRCU_TYPE_ENTRY)lParam;
	if(m_pRCUEntry != NULL)
	{
		SetDlgItemText(IDC_RCU_NAME,m_pRCUEntry->RCUName);
		SetDlgItemInt(IDC_RCU_RS_NUM,m_pRCUEntry->wStatusPortNum);
		//SetDlgItemInt(IDC_RCU_DEVICE_NUM,m_pRCUEntry->wEquipPortNum);

		((CButton *)GetDlgItem(IDC_BTN_MODIFY))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_BTN_DELETE))->EnableWindow(TRUE);
	}
	else
	{
		SetDlgItemText(IDC_RCU_NAME,NULL);
		SetDlgItemText(IDC_RCU_RS_NUM,NULL);
		//SetDlgItemText(IDC_RCU_DEVICE_NUM,NULL);

		((CButton *)GetDlgItem(IDC_BTN_MODIFY))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_BTN_DELETE))->EnableWindow(FALSE);
	}
}

void CSubRCUBaseInfoDlg::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_RCU_NAME,str);
	str.TrimLeft();
	str.TrimRight();

	if(str.IsEmpty())
	{
		MessageBox("增加的RCU名为空，请重试");
		return;
	}
	m_pRCUEntry = new RCU_TYPE_ENTRY;
	ZeroMemory(m_pRCUEntry,sizeof(RCU_TYPE_ENTRY));

	strcpy(m_pRCUEntry->RCUName,(LPSTR)(LPCSTR)str);
	m_pRCUEntry->wStatusPortNum = GetDlgItemInt(IDC_RCU_RS_NUM);
	//m_pRCUEntry->wEquipPortNum = GetDlgItemInt(IDC_RCU_DEVICE_NUM);

	::SendMessage(::GetParent(GetParent()->GetSafeHwnd()),BM_ADD_DB_ENTRY,NULL,(LPARAM)m_pRCUEntry);
}

void CSubRCUBaseInfoDlg::OnBtnModify() 
{
	// TODO: Add your control notification handler code here
	CString str;
	PRCU_TYPE_ENTRY	NewEntry = NULL;
	GetDlgItemText(IDC_RCU_NAME,str);
	str.TrimLeft();
	str.TrimRight();

	if(str.IsEmpty())
	{
		MessageBox("增加的RCU名为空，请重试");
		return;
	}
	NewEntry = new RCU_TYPE_ENTRY;
	ZeroMemory(NewEntry,sizeof(RCU_TYPE_ENTRY));
	
	NewEntry->RCUId = m_pRCUEntry->RCUId;
	strcpy(NewEntry->RCUName,(LPSTR)(LPCSTR)str);
	NewEntry->wStatusPortNum = GetDlgItemInt(IDC_RCU_RS_NUM);
	//NewEntry->wEquipPortNum = GetDlgItemInt(IDC_RCU_DEVICE_NUM);

	::SendMessage(::GetParent(GetParent()->GetSafeHwnd()),BM_MODIFY_DB_ENTRY,(WPARAM)hItem,(LPARAM)NewEntry);
}

void CSubRCUBaseInfoDlg::OnBtnDelete() 
{
  // TODO: Add your control notification handler code here
  ::SendMessage(::GetParent(GetParent()->GetSafeHwnd()),BM_DELETE_DB_ENTRY,(WPARAM)hItem,(LPARAM)m_pRCUEntry);	
}

void CSubRCUBaseInfoDlg::SetRelationItem(PVOID pItem)
{
	if(pItem != NULL)
      hItem = (HTREEITEM)pItem;
}

BOOL CSubRCUBaseInfoDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
      //不要退出
	  if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT)
	    return TRUE;
	  //上下左右
	  if(pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN)
	  {
	        return TRUE;
	  }
	}
	return CDialog::PreTranslateMessage(pMsg);
}


