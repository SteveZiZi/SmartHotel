// SubRoomBuildingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailCFG.h"
#include "SubRoomBuildingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubRoomBuildingDlg dialog


CSubRoomBuildingDlg::CSubRoomBuildingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubRoomBuildingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubRoomBuildingDlg)
	//}}AFX_DATA_INIT
	hItem = NULL;
	m_pEntry = NULL;
}


void CSubRoomBuildingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubRoomBuildingDlg)
	DDX_Control(pDX, IDC_COMBO_ROOM_SHOW, m_ShowStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubRoomBuildingDlg, CDialog)
	//{{AFX_MSG_MAP(CSubRoomBuildingDlg)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MODIFY, OnBtnModify)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubRoomBuildingDlg message handlers

BOOL CSubRoomBuildingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	//======================================
	InitRoomViewStyle();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSubRoomBuildingDlg::InitRoomViewStyle()
{
	m_ShowStyle.InsertString(0,"#FFRR");
    m_ShowStyle.InsertString(1,"#FFRRR");
    m_ShowStyle.InsertString(2,"#FFFRRR");


}

void CSubRoomBuildingDlg::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_BUILDING_NAME,str);
	str.TrimLeft();
	str.TrimRight();

	if(str.IsEmpty())
	{
		MessageBox("增加的楼座名为空，请重试");
		return;
	}
	m_pEntry = new BUILDING_ENTRY;
	ZeroMemory(m_pEntry,sizeof(BUILDING_ENTRY));
	strcpy(m_pEntry->cName,(LPSTR)(LPCSTR)str);

	m_pEntry->dwExtend = m_ShowStyle.GetCurSel();
	::SendMessage(::GetParent(GetParent()->GetSafeHwnd()),BM_ADD_DB_ENTRY,NULL,(LPARAM)m_pEntry);
}

void CSubRoomBuildingDlg::OnBtnModify() 
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_BUILDING_NAME,str);
	str.TrimLeft();
	str.TrimRight();

	if(str.IsEmpty())
	{
		MessageBox("修改的楼座名为空，请重试");
		return;
	}
	PBUILDING_ENTRY NewEntry;
	NewEntry = new BUILDING_ENTRY;
	ZeroMemory(NewEntry,sizeof(BUILDING_ENTRY));
	
	NewEntry->dwEntryIndex = m_pEntry->dwEntryIndex;
	strcpy(NewEntry->cName,(LPSTR)(LPCSTR)str);
	NewEntry->dwExtend = m_ShowStyle.GetCurSel();

	::SendMessage(::GetParent(GetParent()->GetSafeHwnd()),BM_MODIFY_DB_ENTRY,(WPARAM)hItem,(LPARAM)NewEntry);
}

void CSubRoomBuildingDlg::OnBtnDelete() 
{
	// TODO: Add your control notification handler code here
	::SendMessage(::GetParent(GetParent()->GetSafeHwnd()),BM_DELETE_DB_ENTRY,(WPARAM)hItem,(LPARAM)m_pEntry);	

}

void CSubRoomBuildingDlg::SetRelationItem(PVOID pItem)
{
	if(pItem != NULL)
      hItem = (HTREEITEM)pItem;
}

void CSubRoomBuildingDlg::UpdataBuilding(PVOID lParam)
{
	m_pEntry = (PBUILDING_ENTRY)lParam;
	if(m_pEntry != NULL)
	{
		SetDlgItemText(IDC_BUILDING_NAME,m_pEntry->cName);

		((CButton *)GetDlgItem(IDC_BTN_MODIFY))->EnableWindow(TRUE);
		((CButton *)GetDlgItem(IDC_BTN_DELETE))->EnableWindow(TRUE);
	}
	else
	{
		SetDlgItemText(IDC_BUILDING_NAME,NULL);

		((CButton *)GetDlgItem(IDC_BTN_MODIFY))->EnableWindow(FALSE);
		((CButton *)GetDlgItem(IDC_BTN_DELETE))->EnableWindow(FALSE);
	}
	m_ShowStyle.SetCurSel(0);
}
