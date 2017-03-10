// RoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailCFG.h"
#include "RoomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomDlg dialog


CRoomDlg::CRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pRoomDetail = NULL;
    m_pBuilding = NULL;
}

CRoomDlg::~CRoomDlg()
{
    if(m_pBuilding != NULL)
	  delete[] (CSubRoomBuildingDlg *)m_pBuilding;
	if(m_pRoomDetail != NULL)
	  delete[] (CSubRoomDetailDlg *)m_pRoomDetail;
}



void CRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomDlg)
	DDX_Control(pDX, IDC_TREE_BUILDING, m_Building);
	DDX_Control(pDX, IDD_TAB_ROOM, m_RoomMenu);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRoomDlg, CDialog)
	//{{AFX_MSG_MAP(CRoomDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_BUILDING, OnSelchangedTreeBuilding)
	ON_NOTIFY(TCN_SELCHANGE, IDD_TAB_ROOM, OnSelchangeTabRoom)
	ON_MESSAGE(BM_ADD_DB_ENTRY,DoAddOpt)
	ON_MESSAGE(BM_DELETE_DB_ENTRY,DoDeleteOpt)
	ON_MESSAGE(BM_MODIFY_DB_ENTRY,DoModifyOpt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomDlg message handlers
BOOL CRoomDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitRoomTableMenu();		//客房的标签菜单添加
    //加载楼座信息
    EnumAllBuilding();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CRoomDlg::InitRoomTableMenu()
{
    m_RoomMenu.InsertItem(0,"楼座信息");
//CSubRoomBuildingDlg *m_pBuilding;
    m_pBuilding = new CSubRoomBuildingDlg();
    m_pBuilding->Create(IDD_SUB_ROOM_BUILD_DIALOG,GetDlgItem(IDC_ROOM_CUSTOM));
	m_pBuilding->ShowWindow(SW_SHOWNORMAL);


    m_RoomMenu.InsertItem(1,"客房详细");
//CSubRoomDetailDlg *m_pRoomDetail;
    m_pRoomDetail = new CSubRoomDetailDlg();
    m_pRoomDetail->Create(IDD_SUB_ROOM_DETAIL_DIALOG,GetDlgItem(IDC_ROOM_CUSTOM));
	m_pRoomDetail->ShowWindow(SW_HIDE);
}


LRESULT CRoomDlg::DoAddOpt(WPARAM wParam,LPARAM lParam)
{
	HTREEITEM hItem = NULL;
	PBUILDING_ENTRY	m_pEntryInfo = (PBUILDING_ENTRY)lParam;	
	CString str;
	int status;
	if(SearchEntryExist(m_Building.GetRootItem(),m_pEntryInfo->cName) == TRUE)
	{
		str.Format("楼座名称[%s]重复,请重试",m_pEntryInfo->cName);
		MessageBox(str);
		delete[] (PBUILDING_ENTRY)m_pEntryInfo;
		return FALSE;
	}

	str.Format("是否确认要【增加】 楼座(%s)",m_pEntryInfo->cName);
	if(MessageBox(str,"警告",MB_OKCANCEL) == IDCANCEL)
	{
	   return FALSE;
	}
	/*m_pEntryInfo->pEquipDetail = new RCU_PORT_UNIT[m_pEntryInfo->wEquipPortNum];
	m_pEntryInfo->pStatusDetail = new RCU_PORT_UNIT[m_pEntryInfo->wStatusPortNum];
	if(m_pEntryInfo->pEquipDetail != NULL)
	{
		ZeroMemory(m_pEntryInfo->pEquipDetail,sizeof(RCU_PORT_UNIT)*m_pEntryInfo->wEquipPortNum);
	}
	if(m_pEntryInfo->pStatusDetail != NULL)
	{
		ZeroMemory(m_pEntryInfo->pStatusDetail,sizeof(RCU_PORT_UNIT)*m_pEntryInfo->wStatusPortNum);
	}*/
//1：加入数据库
	m_pEntryInfo->dwEntryIndex = GetNextEntry(m_Building.GetRootItem())+1;
	str.Format("INSERT INTO %s VALUE(%d,'%s',%d,%d)",BuildingTableName,
			    m_pEntryInfo->dwEntryIndex,m_pEntryInfo->cName,m_pEntryInfo->dwFloorNum,
				m_pEntryInfo->dwExtend);

	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
	  return	FALSE;
	}
//2：加入树控件
	hItem = m_Building.InsertItem(m_pEntryInfo->cName);
	m_Building.SetItemData(hItem,(DWORD_PTR)m_pEntryInfo);
	//m_Building.SetSelectedItem(hItem);
	//UpDataAllSubDlg(hItem,m_pEntryInfo);
	//DeleteTreeItem(m_RCUEntryTree.GetRootItem());	
	return TRUE;
}
LRESULT CRoomDlg::DoDeleteOpt(WPARAM wParam,LPARAM lParam)
{
	HTREEITEM hItem = (HTREEITEM)wParam;
	PBUILDING_ENTRY	m_pEntryInfo = (PBUILDING_ENTRY)lParam;	
	CString str;
	int status;
	str.Format("是否确认要【删除】 楼名(%s)",m_pEntryInfo->cName);
	if(MessageBox(str,"警告",MB_OKCANCEL) == IDCANCEL)
	{
	   return FALSE;
	}	
//1：删除数据库
	str.Format("DELETE FROM %s WHERE BuildingID=%d",BuildingTableName,m_pEntryInfo->dwEntryIndex);

	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  return	FALSE;
	}
//2：删除树控件
	m_Building.DeleteItem(hItem);
	delete[]m_pEntryInfo; 

	return TRUE;
}
LRESULT CRoomDlg::DoModifyOpt(WPARAM wParam,LPARAM lParam)
{
	HTREEITEM hItem = (HTREEITEM)wParam;
	PBUILDING_ENTRY	m_pNewEntryInfo = (PBUILDING_ENTRY)lParam;	
	PBUILDING_ENTRY m_OldEntry = (PBUILDING_ENTRY)m_Building.GetItemData(hItem);
	CString str,temp;
	BOOL status = FALSE;

	/*if(SearchEntryExist(m_RCUEntryTree.GetRootItem(),m_pNewEntryInfo->RCUName) == TRUE)
	{
		str.Format("RCU名称[%s]重复,请重试",m_pNewEntryInfo->RCUName);
		MessageBox(str);
		return FALSE;
	}*/
	str.Format("是否确认要【修改】 楼名(%s)",m_pNewEntryInfo->cName);
	if(MessageBox(str,"警告",MB_OKCANCEL) == IDCANCEL)
	{
		delete[] (PBUILDING_ENTRY)m_pNewEntryInfo;
		return FALSE;
	}	
	str.Format("UPDATE %s SET ",BuildingTableName);
	if(strcmp(m_pNewEntryInfo->cName,m_OldEntry->cName) != 0)
	{
		temp.Format("BuildingName='%s'",m_pNewEntryInfo->cName);
		str = str + temp;
		status = TRUE;
	}

	if(status == FALSE)
	{
		delete[] m_pNewEntryInfo; 
		return FALSE;
	}
	temp.Format(" WHERE BuildingID=%d",m_OldEntry->dwEntryIndex);
	str = str + temp;
//////////////////////////////////////////////////////////////////////////////////
//1：加入数据库
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  return	FALSE;
	}	

//2：加入树控件
	m_Building.SetItemText(hItem,m_pNewEntryInfo->cName);
	m_Building.SetItemData(hItem,(DWORD_PTR)m_pNewEntryInfo);

	delete[] m_OldEntry; 
	UpDataAllSubDlg(hItem,m_pNewEntryInfo);
	return TRUE;
}

void CRoomDlg::OnSelchangedTreeBuilding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem;
	PVOID	lparam;
	hItem = m_Building.GetSelectedItem();	//pNMTreeView->itemNew.hItem;
	lparam = (PVOID)m_Building.GetItemData(hItem);
/////////////////////////////////////////////////////////////////////////////
	UpDataAllSubDlg(hItem,lparam);

	*pResult = 0;
}

void CRoomDlg::OnSelchangeTabRoom(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int Index;
	Index = m_RoomMenu.GetCurSel();
	if(Index == 0)
	{
	   	m_pBuilding->ShowWindow(SW_SHOWNORMAL);
		m_pRoomDetail->ShowWindow(SW_HIDE);
	}
	else
	{
	   	m_pBuilding->ShowWindow(SW_HIDE);
		m_pRoomDetail->ShowWindow(SW_SHOWNORMAL);	
	}
	*pResult = 0;
}

BOOL CRoomDlg::CheckTypeExist(PCHAR pTempRt)
{
   HTREEITEM tempTree;
   CString sTempName;

   
   tempTree = m_Building.GetRootItem();
   while(tempTree != NULL)
   {
       sTempName = m_Building.GetItemText(tempTree);
       if(strcmp((LPSTR)(LPCSTR)sTempName,pTempRt) == 0)
	     return TRUE;
       tempTree = m_Building.GetNextItem(tempTree,TVGN_NEXT); 
   }
   return FALSE;
}



BOOL CRoomDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		//屏蔽几个键
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT)
			return TRUE;
		//
		if(pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN)
		{
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CRoomDlg::EnumAllBuilding()
{
	PBUILDING_ENTRY  m_pEntryInfo = NULL;		//楼座链表
	HTREEITEM tItem;							//树链
	ULONG	Result;				//查表的结果
	ULONG   RecordNum = 0;		//加入树中的索引
	//链接所有的记录到链表
	Result = (ULONG)GetBuildingRecord(&m_pEntryInfo,NULL);
	//增加到列表框中去
	while(RecordNum<Result)
	{
		tItem = m_Building.InsertItem(m_pEntryInfo->cName);
		m_Building.SetItemData(tItem,(DWORD_PTR)m_pEntryInfo);
		m_pEntryInfo = m_pEntryInfo->pNext;
		RecordNum++;
	}
}

void CRoomDlg::UpDataAllSubDlg(HTREEITEM wParam, PVOID lParam)
{
//更新楼座的信息
//CSubRoomBuildingDlg *m_pBuilding;			//楼座详细
	m_pBuilding->SetRelationItem(wParam);
	m_pBuilding->UpdataBuilding(lParam);

//更新客房的信息
//CSubRoomDetailDlg *m_pRoomDetail;			//客房详细	
	m_pRoomDetail->UpDataRoomInfo(lParam);
	
	
	

	
	
/*	
	int nSelect;
	PBUILDINGSET m_pBuild;
	hItem = m_Building.GetSelectedItem();//pNMTreeView->itemNew.hItem;
    m_pBuild = (PBUILDINGSET)m_Building.GetItemData(hItem);
    //更新子结构
	m_pBuilding->SetBuildIngInfo(m_pBuild);
    m_pRoomDetail->SetBuildingInfo(m_pBuild);
*/
}



BOOL CRoomDlg::SearchEntryExist(HTREEITEM hItem,const char *KeyString)
{
	HTREEITEM hCurItem;
	PBUILDING_ENTRY	m_pEntryInfo;
	if(hItem == NULL)
	  return FALSE;

	m_pEntryInfo = (PBUILDING_ENTRY)m_Building.GetItemData(hItem);
	if(strcmp(m_pEntryInfo->cName,KeyString) == 0)
		return TRUE;
///////////////////////////////////////////////////////////
	hCurItem = m_Building.GetNextItem(hItem,TVGN_NEXT);
	return SearchEntryExist(hCurItem,KeyString);
}


DWORD CRoomDlg::GetNextEntry(HTREEITEM hItem)
{
	DWORD Value = 0;
	PBUILDING_ENTRY	m_pEntryInfo = NULL;
	HTREEITEM hReItem = NULL;
	if(hItem == NULL)
	  return 0;
	////////////////////////////////////
	while(hItem != NULL)
	{
		m_pEntryInfo = (PBUILDING_ENTRY)m_Building.GetItemData(hItem);
		if(m_pEntryInfo->dwEntryIndex > Value)
			Value = m_pEntryInfo->dwEntryIndex;
		hItem = m_Building.GetNextItem(hItem,TVGN_NEXT);
	}
	return Value;
}

BOOL CRoomDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	DeleteTreeContext(m_Building.GetRootItem());
	return CDialog::DestroyWindow();
}


void CRoomDlg::DeleteTreeContext(HTREEITEM hItem)
{
	PBUILDING_ENTRY	m_pEntryInfo = NULL;	
	if(hItem == NULL)
	  return ;
	m_pEntryInfo = (PBUILDING_ENTRY)m_Building.GetItemData(hItem);
	if(m_pEntryInfo != NULL)
	{
		delete[] m_pEntryInfo; 
	}
	DeleteTreeContext(m_Building.GetNextItem(hItem,TVGN_NEXT));
}
