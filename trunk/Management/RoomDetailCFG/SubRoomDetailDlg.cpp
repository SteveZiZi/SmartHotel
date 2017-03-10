// SubRoomDetailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailCFG.h"
#include "SubRoomDetailDlg.h"

#include "SubRoomDetailInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//右键单击弹出菜单项
#define  IDM_POPMENU_BASE     10
// CSubRoomDetailDlg dialog
CSubRoomDetailDlg::CSubRoomDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubRoomDetailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubRoomDetailDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pBuildingInfo = NULL;
	m_pMenu = NULL;
	CurSelRoomDetail = NULL;
	CurSelRoomEntry = -1;
}

CSubRoomDetailDlg::~CSubRoomDetailDlg()
{


}



void CSubRoomDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubRoomDetailDlg)
	DDX_Control(pDX, IDC_COMBO_ROOMTYPE, m_RoomType);
	DDX_Control(pDX, IDC_LIST_ROOM, m_RoomList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubRoomDetailDlg, CDialog)
	//{{AFX_MSG_MAP(CSubRoomDetailDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ROOM, OnItemchangedListRoom)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ROOM, OnRclickListRoom)
	ON_MESSAGE(BM_ADD_DB_ENTRY,DoAddOpt)
	ON_MESSAGE(BM_MODIFY_DB_ENTRY,DoModifyOpt)
	ON_MESSAGE(BM_DELETE_DB_ENTRY,DoDeleteOpt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
LRESULT CSubRoomDetailDlg::DoAddOpt(WPARAM wParam, LPARAM lParam)
{
	PROOM_DETAIL_ENTRY	m_pEntryInfo = (PROOM_DETAIL_ENTRY)lParam;
	CString str;
	int status;
	if(CheckRoomExist(m_pEntryInfo) == TRUE)
	{
		MessageBox("客房已存在");
		delete[] m_pEntryInfo;
		return FALSE;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////
 	str.Format("INSERT INTO %s VALUE(%d,%d,%d,%d,%d,'%s',%d,'','')",RoomSetTableName,
				m_pEntryInfo->dwEntryIndex,m_pEntryInfo->bRoomNum,
				m_pEntryInfo->bFloorNum,m_pEntryInfo->bBuildingNum,
				m_pEntryInfo->dwRoomTypeID,m_pEntryInfo->sIpAddress,
				m_pEntryInfo->dwPort);
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  delete[] (PROOM_DETAIL_ENTRY)m_pEntryInfo;
	  return FALSE;
	}
   //==================================================================
   InsertOneRow(m_RoomList.GetItemCount(),m_pEntryInfo);
	return TRUE;
}

LRESULT CSubRoomDetailDlg::DoModifyOpt(WPARAM wParam, LPARAM lParam)
{
	PROOM_DETAIL_ENTRY	m_pEntryInfo = (PROOM_DETAIL_ENTRY)lParam;
	CString str,temp,Context;
	BOOL status = FALSE;
/////////////////////////////////////////////////////////////////////////////////
	str.Format("UPDATE %s SET ",RoomSetTableName);
	if(m_pEntryInfo->bFloorNum != CurSelRoomDetail->bFloorNum)
	{
		temp.Format("FloorNum=%d",m_pEntryInfo->bFloorNum);
		str = str + temp;
		status = TRUE;
	}	

	if(m_pEntryInfo->bRoomNum != CurSelRoomDetail->bRoomNum)
	{
		if(status == TRUE)
			temp.Format(",DoorNum=%d",m_pEntryInfo->bRoomNum);
		else
			temp.Format("DoorNum=%d",m_pEntryInfo->bRoomNum);
		str = str + temp;
		status = TRUE;
	}	
	
	if(m_pEntryInfo->dwRoomTypeID != CurSelRoomDetail->dwRoomTypeID)
	{
		if(status == TRUE)
			temp.Format(",RoomtypeID=%d",m_pEntryInfo->dwRoomTypeID);
		else
			temp.Format("RoomtypeID=%d",m_pEntryInfo->dwRoomTypeID);
		str = str + temp;
		status = TRUE;
	}		
	
	if(strcmp(m_pEntryInfo->sIpAddress,CurSelRoomDetail->sIpAddress) != 0)
	{
		if(status == TRUE)
			temp.Format(",IPAddress='%s'",m_pEntryInfo->sIpAddress);
		else
			temp.Format("IPAddress='%s'",m_pEntryInfo->sIpAddress);
		str = str + temp;
		status = TRUE;
	}

	if(m_pEntryInfo->dwPort != CurSelRoomDetail->dwPort)
	{
		if(status == TRUE)
			temp.Format(",PortValue=%d",m_pEntryInfo->dwPort);
		else
			temp.Format("PortValue=%d",m_pEntryInfo->dwPort);
		str = str + temp;
		status = TRUE;
	}		
//**********************************************************************************************
	if(status == FALSE)
	{
		//MessageBox("不需要修改");
		return TRUE;
	}
	temp.Format(" WHERE RoomID=%d",m_pEntryInfo->dwEntryIndex);
	str = str + temp;
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);  
	  return	FALSE;
	}
//================================================================================
	delete[] (PROOM_DETAIL_ENTRY)CurSelRoomDetail;
	UpdataListRow(CurSelRoomEntry,m_pEntryInfo);

	return TRUE;
}
LRESULT CSubRoomDetailDlg::DoDeleteOpt(WPARAM wParam, LPARAM lParam)
{
	PROOM_DETAIL_ENTRY	m_pEntryInfo = (PROOM_DETAIL_ENTRY)lParam;
	int EntryIndex = (int)wParam;
	CString str;
	int status;
	if(m_pEntryInfo == NULL)
		return FALSE;
//////////////////////////////////////////////////////////////////////////////////////
	if(m_pEntryInfo->dwEntryIndex != 0)
	{
		str.Format("DELETE FROM %s WHERE RoomID=%d",RoomSetTableName,m_pEntryInfo->dwEntryIndex);
	}
	else
	{
		//str.Format("DELETE FROM %s WHERE IPaddress=%s",RoomSetTableName,m_pEntryInfo->sIpAddress);	
		str.Format("DELETE FROM %s WHERE BuildingID=%d AND FloorNum=%d AND DoorNum=%d",RoomSetTableName,
		m_pEntryInfo->bBuildingNum,m_pEntryInfo->bFloorNum,m_pEntryInfo->bRoomNum);	
	}

	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  return	FALSE;
	}
//////////////////////////////////////////////////////////////////////////////////////////////////
	delete[] (PROOM_DETAIL_ENTRY)m_pEntryInfo;
	m_RoomList.DeleteItem(EntryIndex);

	CurSelRoomEntry = -1;
	CurSelRoomDetail = NULL;
	return TRUE;
}

// CSubRoomDetailDlg message handlers

BOOL CSubRoomDetailDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here
//初始化列表控件
	InitListCtrlView();    //初始化控件的外观

//枚举得到所有的房类信息
	EnumAllRoomType();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubRoomDetailDlg::EnumAllRoomType()
{
	ULONG	Result;
	ULONG   RecordNum = 0;
	PROOM_TYPE_ENTRY	m_pEntryInfo = NULL;
	PROOM_TYPE_ENTRY	m_pTempEntryInfo;
	//链接所有的记录到链表
	Result = (ULONG)GetRoomTypeRecord(&m_pEntryInfo,NULL);
	//增加到列表框中去		
	while(RecordNum<Result)
	{
		m_pTempEntryInfo = m_pEntryInfo->pNext;
		m_RoomType.InsertString(RecordNum,m_pEntryInfo->cName);
		m_RoomType.SetItemData(RecordNum,m_pEntryInfo->dwEntryIndex);

		delete[] (PROOM_TYPE_ENTRY)m_pEntryInfo;
		m_pEntryInfo = m_pTempEntryInfo;
		RecordNum++;
	}
	if(Result)
		m_RoomType.SetCurSel(0);
}


void CSubRoomDetailDlg::InitListCtrlView()
{
	CRect Rt; 
	DWORD dwStyleEx;
//	int Order[12]={1,0,2,3,4,5,6,7,8,9.10,11};
	::GetClientRect(m_RoomList.GetSafeHwnd(),&Rt);
	//改变显示模式为报表
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	dwStyleEx = LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES;  //  
    m_RoomList.SetExtendedStyle(dwStyleEx);
    ////////////////////////////////////////////////////////
	m_RoomList.InsertColumn( 0, NULL, LVCFMT_CENTER, 0);//插入列
    m_RoomList.InsertColumn( 1, "楼幢楼层", LVCFMT_CENTER, Rt.Width()/5);//插入列
    m_RoomList.InsertColumn( 2, "门牌号", LVCFMT_CENTER, Rt.Width()/5 );//插入列
    m_RoomList.InsertColumn( 3, "房类", LVCFMT_CENTER, Rt.Width()/5 );
    m_RoomList.InsertColumn( 4, "IP地址", LVCFMT_CENTER, Rt.Width()*3/10 );
	m_RoomList.InsertColumn( 5, "端口", LVCFMT_CENTER, Rt.Width()/10 );
//    m_RoomList.SetColumnOrderArray(4,Order);
//===============================================================================================
//Init Menu Item
	m_pMenu = new CMenu();       //m_pMenu->CreateMenu();
	m_pMenu->CreatePopupMenu();
	//显示外观模式显示切换菜单
	m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE,"增加");//添加菜单项(Offset 0x00)
	m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE+1,"修改");//添加菜单项(Offset 0x00)
	//m_pMenu->AppendMenu(MF_SEPARATOR);//添加分隔线
	//先中房间的操作界面
	m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE+2,"删除");
}





void CSubRoomDetailDlg::InsertOneRow(int Entry, LPVOID lParam)
{
	PROOM_DETAIL_ENTRY	m_pEntryInfo = (PROOM_DETAIL_ENTRY)lParam;
	CString str;
	int i=0;
//行第一列为空
	m_RoomList.InsertItem(Entry,NULL);

  //第一栏
	if(m_pBuildingInfo->dwExtend == SHOW_STYLE_TYPE_A)
	{
		str.Format("%s-%02d",m_pBuildingInfo->cName,m_pEntryInfo->bFloorNum);  
		m_RoomList.SetItemText(Entry,1,str);
		str.Format("%02d%02d",m_pEntryInfo->bFloorNum,m_pEntryInfo->bRoomNum);  
		m_RoomList.SetItemText(Entry,2,str);
	}

	if(m_pBuildingInfo->dwExtend == SHOW_STYLE_TYPE_B)
	{
		str.Format("%s-%02d",m_pBuildingInfo->cName,m_pEntryInfo->bFloorNum);  
		m_RoomList.SetItemText(Entry,1,str);
		str.Format("%02d%03d",m_pEntryInfo->bFloorNum,m_pEntryInfo->bRoomNum);  
		m_RoomList.SetItemText(Entry,2,str);
	}

	if(m_pBuildingInfo->dwExtend == SHOW_STYLE_TYPE_C)
	{
		str.Format("%s-%03d",m_pBuildingInfo->cName,m_pEntryInfo->bFloorNum);  
		m_RoomList.SetItemText(Entry,1,str);
		str.Format("%03d%03d",m_pEntryInfo->bFloorNum,m_pEntryInfo->bRoomNum);  
		m_RoomList.SetItemText(Entry,2,str);
	}
///////////////////////////////////////////////////////////////////////////////////////
//显示房类信息
    for(i=0;i<m_RoomType.GetCount();i++)
	{
	   if(m_RoomType.GetItemData(i) == m_pEntryInfo->dwRoomTypeID)
		 break;
	}
	if(i>=m_RoomType.GetCount())
       str.Format("房类【%d】",m_pEntryInfo->dwRoomTypeID);
	else
	   m_RoomType.GetLBText(i,str);
    m_RoomList.SetItemText(Entry,3,str);
	
	//显示地址信息
    str.Format("%s",m_pEntryInfo->sIpAddress);
    m_RoomList.SetItemText(Entry,4,str);


	str.Format("%d",m_pEntryInfo->dwPort);
    m_RoomList.SetItemText(Entry,5,str);
    
    //关联结构体
	m_RoomList.SetItemData(Entry,(DWORD_PTR)m_pEntryInfo);
}


void CSubRoomDetailDlg::DeleteAllData()
{
   PROOM_DETAIL_ENTRY m_pRoom;
   while(m_RoomList.GetItemCount())
   {
     m_pRoom = (PROOM_DETAIL_ENTRY)m_RoomList.GetItemData(0);
	 if(m_pRoom)
	   delete[] (PROOM_DETAIL_ENTRY)m_pRoom;
     m_RoomList.DeleteItem(0);
   }
}

void CSubRoomDetailDlg::OnItemchangedListRoom(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMListView->iItem == -1)
	  return;

	PROOM_DETAIL_ENTRY m_pRoom = (PROOM_DETAIL_ENTRY)m_RoomList.GetItemData(pNMListView->iItem);
	if(m_pRoom == NULL)
	  return;
	//=========================================================================
    SetDlgItemInt(IDC_EDIT_FLOOR,m_pRoom->bFloorNum);
	SetDlgItemInt(IDC_EDIT_ROOM_MIN,m_pRoom->bRoomNum);
	SetDlgItemText(IDC_EDIT_ROOM_MAX,NULL);
    //房类信息
    int i;
	for(i=0;i<m_RoomType.GetCount();i++)
	{
	  if((DWORD)m_RoomType.GetItemData(i) == m_pRoom->dwRoomTypeID)
		break;
	}
    m_RoomType.SetCurSel(i);
	SetDlgItemInt(IDC_EDIT_PORT_NUM,m_pRoom->dwPort);

	*pResult = 0;
}

void CSubRoomDetailDlg::OnBtnAdd() 
{
   // TODO: Add your control notification handler code here
	UINT	MinNum,MaxNum;
	PROOM_DETAIL_ENTRY	m_pEntryInfo = NULL;
	if(m_pBuildingInfo == NULL)
		return;
	//===========================================================================
	MaxNum = GetDlgItemInt(IDC_EDIT_ROOM_MAX);		//最大的
	MinNum = GetDlgItemInt(IDC_EDIT_ROOM_MIN);		//最小的
	do
	{
		m_pEntryInfo = new ROOM_DETAIL_ENTRY;
		if(m_pEntryInfo == NULL)
			return;
		ZeroMemory(m_pEntryInfo,sizeof(ROOM_DETAIL_ENTRY));
	////////////////////////////////////////////////////////////////////////
		UpDataItemContext(m_pEntryInfo,FALSE);
		m_pEntryInfo->bRoomNum = MinNum;
		memset(m_pEntryInfo->sIpAddress,'\0',32);
		sprintf(m_pEntryInfo->sIpAddress,"192.168.%d.%d",m_pEntryInfo->bFloorNum,m_pEntryInfo->bRoomNum);
		DoAddOpt(NULL,(LPARAM)m_pEntryInfo);
		MinNum++;
	}while(MinNum<=MaxNum);
}

BOOL CSubRoomDetailDlg::CheckRoomExist(LPVOID lParam)
{
	DWORD Index,ItemNum;
	PROOM_DETAIL_ENTRY m_pRoom;
	PROOM_DETAIL_ENTRY m_pCurRoom = (PROOM_DETAIL_ENTRY)lParam;

	ItemNum = m_RoomList.GetItemCount();
	for(Index=0;Index<ItemNum;Index++)
	{
		m_pRoom = (PROOM_DETAIL_ENTRY)m_RoomList.GetItemData(Index);
		if((m_pCurRoom->bFloorNum == m_pRoom->bFloorNum) && (m_pCurRoom->bRoomNum == m_pRoom->bRoomNum))
			return TRUE;
	}
	return FALSE;	
}

void CSubRoomDetailDlg::UpDataRoomInfo(PVOID lParam)
{
	ULONG	Result;
	ULONG   RecordNum = 0;
	CString str;
	PROOM_DETAIL_ENTRY	m_pEntryInfo = NULL;
	m_pBuildingInfo = (PBUILDING_ENTRY)lParam;

//先将列表控件的内容全删掉
	DeleteAllData();
	//楼层信息为空
	if(m_pBuildingInfo == NULL)
	{
		((CButton *)GetDlgItem(IDC_BTN_ADD))->EnableWindow(FALSE);
		return;
	}
	///////////////////////////////////////////////////////////
	((CButton *)GetDlgItem(IDC_BTN_ADD))->EnableWindow(TRUE);
	str.Format("BuildingID=%d",m_pBuildingInfo->dwEntryIndex);
	//链接所有的记录到链表
	Result = (ULONG)GetRoomRecord(&m_pEntryInfo,str);
	//增加到列表框中去		
	while(RecordNum<Result)
	{
		InsertOneRow(RecordNum,m_pEntryInfo);
		m_pEntryInfo = m_pEntryInfo->pNext;;
		RecordNum++;
	}
	//////////////
	//if(!Result)		//要将内容清空
	//{}
}

DWORD CSubRoomDetailDlg::GetNextEntryIndex()
{
	DWORD MaxEntry = 0;
	DWORD Index,ItemNum;
	PROOM_DETAIL_ENTRY m_pRoom;

	ItemNum = m_RoomList.GetItemCount();
	for(Index=0;Index<ItemNum;Index++)
	{
		m_pRoom = (PROOM_DETAIL_ENTRY)m_RoomList.GetItemData(Index);
		if(MaxEntry < m_pRoom->dwEntryIndex)
			MaxEntry = m_pRoom->dwEntryIndex;
	}
	return MaxEntry;
}

void CSubRoomDetailDlg::OnRclickListRoom(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem == -1)
	  return;

	CurSelRoomEntry = pNMListView->iItem;
	CurSelRoomDetail = (PROOM_DETAIL_ENTRY)m_RoomList.GetItemData(pNMListView->iItem);
	//if(m_RoomList.GetItemCount())
	{
	  CPoint pt;
      GetCursorPos(&pt);
  	  m_pMenu->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);	
	}	
	*pResult = 0;
}

BOOL CSubRoomDetailDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	UINT uMsg=LOWORD(wParam);
	PROOM_DETAIL_ENTRY	m_pEntryInfo = NULL;
	INT_PTR Result;
	switch(uMsg)
	{
		case  IDM_POPMENU_BASE:
				if(m_pBuildingInfo == NULL)
					break;
				m_pEntryInfo = new ROOM_DETAIL_ENTRY;
				if(m_pEntryInfo == NULL)
					break;
				ZeroMemory(m_pEntryInfo,sizeof(ROOM_DETAIL_ENTRY));
				////////////////////////////////////////////////////////////////////////
				UpDataItemContext(m_pEntryInfo,FALSE);
				DoAddOpt(NULL,(LPARAM)m_pEntryInfo);
				break;
		case  IDM_POPMENU_BASE+1:			//修改客房信息
				CSubRoomDetailInfoDlg *m_DetailModifyDlg;
				m_DetailModifyDlg = new CSubRoomDetailInfoDlg(this);
				m_DetailModifyDlg->SetRelationData(CurSelRoomDetail);
				Result = m_DetailModifyDlg->DoModal();
				m_pEntryInfo = (PROOM_DETAIL_ENTRY)m_DetailModifyDlg->GetRelationData();
				if(Result == IDOK)
				{
					DoModifyOpt((WPARAM)CurSelRoomDetail,(LPARAM)m_pEntryInfo);
				}
				else
				{
					delete m_pEntryInfo;
				}
				delete m_DetailModifyDlg;
				break;
		case  IDM_POPMENU_BASE+2:		//删除客房信息
				DoDeleteOpt((WPARAM)CurSelRoomEntry,(LPARAM)CurSelRoomDetail);
				break;
		default:
			 ;
	}
	return CDialog::OnCommand(wParam, lParam);
}

void CSubRoomDetailDlg::UpDataItemContext(PVOID pContext, BOOL Flag)
{
	PROOM_DETAIL_ENTRY m_pEntryInfo = (PROOM_DETAIL_ENTRY)pContext;
	if(m_pEntryInfo == NULL)
		return;
//////////////////////////////////////////////////////////////////////////////////////////
	//m_pEntryInfo->dwEntryIndex = GetNextEntryIndex()+1;
	m_pEntryInfo->bBuildingNum = m_pBuildingInfo->dwEntryIndex;
	m_pEntryInfo->bFloorNum = GetDlgItemInt(IDC_EDIT_FLOOR);
	m_pEntryInfo->bRoomNum = GetDlgItemInt(IDC_EDIT_ROOM_MIN);;

	m_pEntryInfo->dwPort = GetDlgItemInt(IDC_EDIT_PORT_NUM);
	m_pEntryInfo->dwRoomTypeID = (DWORD)m_RoomType.GetItemData(m_RoomType.GetCurSel());
	sprintf(m_pEntryInfo->sIpAddress,"192.168.%d.%d",m_pEntryInfo->bFloorNum,m_pEntryInfo->bRoomNum);
	
	m_pEntryInfo->pEquipBlock = NULL;
	m_pEntryInfo->pStatusBlock = NULL;
	m_pEntryInfo->pNext = NULL;
}

void CSubRoomDetailDlg::UpdataListRow(int RowIndex, PVOID lParam)
{
	PROOM_DETAIL_ENTRY	m_pEntryInfo = (PROOM_DETAIL_ENTRY)lParam;
	CString str;
	int i=0;
	//////////////////////////////////////////////////////////////////////
 //第一栏
	if(m_pBuildingInfo->dwExtend == SHOW_STYLE_TYPE_A)
	{
		str.Format("%s-%02d",m_pBuildingInfo->cName,m_pEntryInfo->bFloorNum);  
		m_RoomList.SetItemText(RowIndex,1,str);
		str.Format("%02d%02d",m_pEntryInfo->bFloorNum,m_pEntryInfo->bRoomNum);  
		m_RoomList.SetItemText(RowIndex,2,str);
	}

	if(m_pBuildingInfo->dwExtend == SHOW_STYLE_TYPE_B)
	{
		str.Format("%s-%02d",m_pBuildingInfo->cName,m_pEntryInfo->bFloorNum);  
		m_RoomList.SetItemText(RowIndex,1,str);
		str.Format("%02d%03d",m_pEntryInfo->bFloorNum,m_pEntryInfo->bRoomNum);  
		m_RoomList.SetItemText(RowIndex,2,str);
	}

	if(m_pBuildingInfo->dwExtend == SHOW_STYLE_TYPE_C)
	{
		str.Format("%s-%03d",m_pBuildingInfo->cName,m_pEntryInfo->bFloorNum);  
		m_RoomList.SetItemText(RowIndex,1,str);
		str.Format("%03d%03d",m_pEntryInfo->bFloorNum,m_pEntryInfo->bRoomNum);  
		m_RoomList.SetItemText(RowIndex,2,str);
	}
///////////////////////////////////////////////////////////////////////////////////////
//显示房类信息
    for(i=0;i<m_RoomType.GetCount();i++)
	{
	   if(m_RoomType.GetItemData(i) == m_pEntryInfo->dwRoomTypeID)
		 break;
	}
	if(i>=m_RoomType.GetCount())
       str.Format("房类【%d】",m_pEntryInfo->dwRoomTypeID);
	else
	   m_RoomType.GetLBText(i,str);
    m_RoomList.SetItemText(RowIndex,3,str);
	
	//显示地址信息
    str.Format("%s",m_pEntryInfo->sIpAddress);
    m_RoomList.SetItemText(RowIndex,4,str);


	str.Format("%d",m_pEntryInfo->dwPort);
    m_RoomList.SetItemText(RowIndex,5,str);

	CurSelRoomDetail = m_pEntryInfo;
	m_RoomList.SetItemData(RowIndex,(DWORD_PTR)CurSelRoomDetail);
}

void CSubRoomDetailDlg::OnOK()
{

}