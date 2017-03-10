// GuestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoCFG.h"
#include "GuestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGuestDlg dialog


CGuestDlg::CGuestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGuestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGuestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CGuestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGuestDlg)
	DDX_Control(pDX, IDD_TAB_GUEST, m_GuestMenu);
	DDX_Control(pDX, IDC_TREE_DEPARTMENT,m_Department);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGuestDlg, CDialog)
	//{{AFX_MSG_MAP(CGuestDlg)
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDD_TAB_GUEST, &CGuestDlg::OnTcnSelchangeTabGuest)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DEPARTMENT, &CGuestDlg::OnTvnSelchangedTreeDepartment)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGuestDlg message handlers

BOOL CGuestDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitGuestMenu();

	InitDepartmentTree();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGuestDlg::InitGuestMenu()
{
	m_GuestMenu.InsertItem(0,"帐户管理");
	m_paccountManagement = new CAccountManagement();
	m_paccountManagement->Create(IDD_ACCOUNT_MANAGEMENT,GetDlgItem(IDC_STATIC_GUEST));
	m_paccountManagement->ShowWindow(SW_SHOWNORMAL);

    m_GuestMenu.InsertItem(1,"权限设置");
	m_prightManagement = new CRightManagement();
	m_prightManagement->Create(IDD_RIGHT_MANAGEMENT,GetDlgItem(IDC_STATIC_GUEST));
	m_prightManagement->ShowWindow(SW_HIDE);

	m_GuestMenu.InsertItem(2,"登陆记录");
	m_plandRecord = new CLandRecord();
	m_plandRecord->Create(IDD_LAND_RECORD,GetDlgItem(IDC_STATIC_GUEST));
	m_plandRecord->ShowWindow(SW_HIDE);
}

void CGuestDlg::InitDepartmentTree()
{
	m_Department.InsertItem("前台部");
	m_Department.InsertItem("工程部");
	m_Department.InsertItem("总经办");
	m_Department.InsertItem("服务部");
	m_Department.InsertItem("管理员");
}

void CGuestDlg::OnTcnSelchangeTabGuest(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int Index;
	Index = m_GuestMenu.GetCurSel();
	if(Index == 0)
	{
		m_paccountManagement->ShowWindow(SW_SHOWNORMAL);
		m_prightManagement->ShowWindow(SW_HIDE);
		m_plandRecord->ShowWindow(SW_HIDE);
	}
	else if (Index == 1)
	{
		m_paccountManagement->ShowWindow(SW_HIDE);
		m_prightManagement->ShowWindow(SW_SHOWNORMAL);	
		m_plandRecord->ShowWindow(SW_HIDE);
	}
	else
	{
		m_paccountManagement->ShowWindow(SW_HIDE);
		m_prightManagement->ShowWindow(SW_HIDE);	
		m_plandRecord->ShowWindow(SW_SHOWNORMAL);
	}
	*pResult = 0;
}

void CGuestDlg::OnTvnSelchangedTreeDepartment(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem;
	CString	result;
	hItem = m_Department.GetSelectedItem();	//pNMTreeView->itemNew.hItem;
	result = m_Department.GetItemText(hItem);
	/////////////////////////////////////////////////////////////////////////////
	UpDataAllSubDlg(hItem,result);
	*pResult = 0;
}

void CGuestDlg::UpDataAllSubDlg(HTREEITEM wParam,CString result)
{
	m_paccountManagement->SetRelationItem(wParam);
	m_paccountManagement->UpdataDLG(result);

	m_prightManagement->SetRelationItem(wParam);
	m_prightManagement->UpdataDLG(result);

	m_plandRecord->SetRelationItem(wParam);
	m_plandRecord->UpdataDLG(result);
}

void CGuestDlg::OnOK()
{

}