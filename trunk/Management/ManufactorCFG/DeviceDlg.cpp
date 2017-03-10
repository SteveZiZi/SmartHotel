// DeviceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManufactorCFG.h"
#include "DeviceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg dialog


CDeviceDlg::CDeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeviceDlg)
	//}}AFX_DATA_INIT

}

CDeviceDlg::~CDeviceDlg()
{
   DeleteAllListContext();


   if(pEdit != NULL)
	 delete[] pEdit;
}

void CDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeviceDlg)
	DDX_Control(pDX, IDC_LIST_DEVICE, m_DeviceList);
	DDX_Control(pDX, IDC_TAB_DEVICECLASS, m_DeviceEntry);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeviceDlg, CDialog)
	//{{AFX_MSG_MAP(CDeviceDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_DEVICECLASS, OnSelchangeTabDeviceclass)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DEVICE, OnClickListDevice)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DEVICE, OnDblclkListDevice)
	ON_MESSAGE(BM_ADD_DB_ENTRY,DoAddOpt)
	ON_MESSAGE(BM_MODIFY_DB_ENTRY,DoModifyOpt)
	ON_MESSAGE(BM_DELETE_DB_ENTRY,DoDeleteOpt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg message handlers

BOOL CDeviceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
//新建一个可编辑框
	pEdit = new CEdit;
	if(pEdit == NULL)
      exit(0);
	pEdit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,CRect(10, 10, 100, 40),(CWnd *)FromHandle(m_DeviceList.m_hWnd), 1);
	pEdit->ShowWindow(SW_HIDE);
	m_PreItem.Flag = FALSE;
	m_PreItem.Item = -1;
	m_PreItem.SubItem = -1;

    //Step 1: 设置好列表控件外观
	InitDeviceListCtrl();
	//Step 2: 再初始化好选项
	InitDeviceClass();        //初始化选项

	//得到表中所有的记录
	EnumAllTableRecord(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDeviceDlg::InitDeviceClass()
{
//索引0：设备
    m_DeviceEntry.InsertItem(0,"空调设备");
    m_DeviceEntry.InsertItem(1,"调光设备");
    m_DeviceEntry.InsertItem(2,"开关设备");
    m_DeviceEntry.InsertItem(3,"节电开关");

	//设置默认的为
	m_DeviceEntry.SetCurSel(0);
}

void CDeviceDlg::OnSelchangeTabDeviceclass(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelectEntry;
	nSelectEntry = m_DeviceEntry.GetCurSel();
	EnumAllTableRecord(nSelectEntry);

	*pResult = 0;
}
void CDeviceDlg::InitDeviceListCtrl()
{
	CRect Rt; 
	int Width;
	DWORD dwStyleEx;
	int Order[12]={1,2,0,3,4,5,6,7,8,9,10,11};

	::GetClientRect(m_DeviceList.GetSafeHwnd(),&Rt);
	//改变显示模式为报表
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	dwStyleEx = LVS_EX_FULLROWSELECT |  LVS_EX_CHECKBOXES | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES;  //LVS_EX_FULLROWSELECT |  
    m_DeviceList.SetExtendedStyle(dwStyleEx);
	//m_DeviceList.SetItemHigh(150);
    //m_DeviceList.SetTextAttr(25,"宋体",RGB(0,0,255));

	Width = GetSystemMetrics(SM_CYVSCROLL);
	Width = Rt.Width() - Width;
    ////////////////////////////////////////////////////////
    m_DeviceList.InsertColumn( 0, "DualPort", LVCFMT_CENTER, Width/5 );//插入列
    m_DeviceList.InsertColumn( 1, "Name", LVCFMT_CENTER, Width/5);//插入列
    m_DeviceList.InsertColumn( 2, "Timing", LVCFMT_CENTER, Width/5);
    m_DeviceList.InsertColumn( 3, "View", LVCFMT_CENTER, Width/5 );
    m_DeviceList.InsertColumn( 4, "Btn", LVCFMT_CENTER, Width/5);
  
    m_DeviceList.SetColumnOrderArray(5,Order);
}

BOOL CDeviceDlg::PreTranslateMessage(MSG* pMsg) 
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
		  if(::GetDlgCtrlID(::GetFocus()) != IDC_LIST_ROOMSTATE)
	        return TRUE;
	  }
	}
	return CDialog::PreTranslateMessage(pMsg);
}


//执行要删除的信息
LRESULT CDeviceDlg::DoDeleteOpt(WPARAM wParam, LPARAM lParam)
{
	PEQUIPMENT_ENTRY m_pEntryInfo = (PEQUIPMENT_ENTRY)lParam;
	int TableIndex = m_DeviceEntry.GetCurSel();
	int TotalListNum = m_DeviceList.GetItemCount();
	CString str;
	int status;
	str.Format("是否确认要【删除】 设备(%s)",m_pEntryInfo->cName);
	if(MessageBox(str,"警告",MB_OKCANCEL) == IDCANCEL)
	{
	   return FALSE;
	}
	if(m_pEntryInfo == NULL)
	{
		MessageBox("增加项为空,请重新选择！");
		return 0;
	}
//=========================================================================================
	str.Format("DELETE FROM %s WHERE ID=%d",sEquipmentTbName[TableIndex],m_pEntryInfo->dwEntryIndex);
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  return	FALSE;
	}

	SetDlgItemInt(IDC_ENTRYNUM,TotalListNum-1);
	//查找到要删除的项目
	while(TotalListNum)
	{
		TotalListNum--;
		if((PEQUIPMENT_ENTRY)m_DeviceList.GetItemData(TotalListNum) == m_pEntryInfo)
			break;
	}

	m_DeviceList.DeleteItem(TotalListNum);
	delete[] (PEQUIPMENT_ENTRY)m_pEntryInfo;
	return TRUE;
}

//执行要增加的房态信息
LRESULT CDeviceDlg::DoAddOpt(WPARAM wParam, LPARAM lParam)
{
	PEQUIPMENT_ENTRY m_pEntryInfo = (PEQUIPMENT_ENTRY)lParam;
	int TableIndex = m_DeviceEntry.GetCurSel();
	int TotalListNum = m_DeviceList.GetItemCount();
	//DWORD LastEntry = ((PEQUIPMENT_ENTRY)(m_DeviceList.GetItemData(TotalListNum-1)))->dwEntryIndex+1;
	CString str;
	int status;
	str.Format("是否确认要【增加】 设备(%s)",m_pEntryInfo->cName);
	if(MessageBox(str,"警告",MB_OKCANCEL) == IDCANCEL)
	{
	   delete[] (PEQUIPMENT_ENTRY)m_pEntryInfo;
	   return FALSE;
	}
	if(m_pEntryInfo == NULL)
	{
		MessageBox("增加项为空,请重新选择！");
		return 0;
	}
//=========================================================================================
//举例
//INSERT INTO cctv value(0,5,'8265')
	str.Format("INSERT INTO %s VALUE(%d,'%s',%d,%d,%d,'%s')",sEquipmentTbName[TableIndex],
			    m_pEntryInfo->dwEntryIndex,m_pEntryInfo->cName,m_pEntryInfo->bEnDualPort,
				m_pEntryInfo->wType,m_pEntryInfo->dwExtend,m_pEntryInfo->vSharpPath);

	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  delete[] (PROOMSTATUS_ENTRY)m_pEntryInfo;
	  return	FALSE;
	}

	InertOneRow(TotalListNum,m_pEntryInfo);
	
	SetDlgItemInt(IDC_ENTRYNUM,TotalListNum+1);
	return TRUE;
}



//执行要修改的信息
LRESULT CDeviceDlg::DoModifyOpt(WPARAM wParam, LPARAM lParam)
{
	PEQUIPMENT_ENTRY m_pEntryInfo = (PEQUIPMENT_ENTRY)lParam;
	int TableIndex = m_DeviceEntry.GetCurSel();
	PUINT	Item = (PUINT)wParam;
	if(m_pEntryInfo == NULL)
	{
		MessageBox("修改项为空,请重新选择");
		return 0;
	}
	CString str;
	int status;
	str.Format("是否确认要【修改】 设备(%s)",m_pEntryInfo->cName);
	if(MessageBox(str,"警告",MB_OKCANCEL) == IDCANCEL)
	{
	   return FALSE;
	}
//=========================================================================================
//举例
//UPDATE roomstate_base SET roomstate_base.baseType = '??' where roomstate_base.baseType = '??'
	//str.Format("UPDATE %s SET TypeName='%s' IsDualDirection=%d Shape='%s' WHERE ID=%d",
	//	sRoomStatusName[TableIndex],m_pRoomState->cName,m_pRoomState->bEnDualPort,
	//	m_pRoomState->vSharpPath,m_pRoomState->dwEntryIndex);
	str.Format("UPDATE %s SET cName='%s',IsDualDirection=%d,EquType=%d,Shape='%s' WHERE ID=%d",sEquipmentTbName[TableIndex],
		m_pEntryInfo->cName,m_pEntryInfo->bEnDualPort,m_pEntryInfo->wType,m_pEntryInfo->vSharpPath,m_pEntryInfo->dwEntryIndex);

	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  return	FALSE;
	}	
	/////////////////////////////////////////////////////////////////////
	if(Item != NULL)
	  m_DeviceList.SetCheck(*Item,m_pEntryInfo->bEnDualPort);
	return TRUE;
}

void CDeviceDlg::EnumAllTableRecord(int TableIndex)
{
	CString str;
	ULONG	Result;
	ULONG   RecordNum = 0;
	PEQUIPMENT_ENTRY m_pEntryInfo = NULL;	
	//先清空列表框及参数
	DeleteAllListContext();
	//链接所有的记录到链表
	Result = (ULONG)GetEquipmentRecord(TableIndex,&m_pEntryInfo,NULL);
	//增加到列表框中去
	while(RecordNum<Result)
	{
		InertOneRow(RecordNum,m_pEntryInfo);
		m_pEntryInfo = m_pEntryInfo->pNext;
		RecordNum++;
	}
	SetDlgItemInt(IDC_ENTRYNUM,RecordNum);
}

void CDeviceDlg::DeleteAllListContext()
{
	int RecordNum;
	PEQUIPMENT_ENTRY m_pEntryInfo = NULL;	
	RecordNum = m_DeviceList.GetItemCount();
	while(RecordNum)
	{
		RecordNum--;
		m_pEntryInfo = (PEQUIPMENT_ENTRY)m_DeviceList.GetItemData(RecordNum);
		if(m_pEntryInfo != NULL)
			delete[] (PEQUIPMENT_ENTRY)m_pEntryInfo;
		m_DeviceList.DeleteItem(RecordNum);
	}
}

int CDeviceDlg::InertOneRow(int Index, LPVOID lParam)
{
	CString str;
	PEQUIPMENT_ENTRY m_pEntryInfo = (PEQUIPMENT_ENTRY)lParam;
/////////////////////////////////////////////////////////////////////////////////
	m_DeviceList.InsertItem(Index,"是否双向");
	m_DeviceList.SetItemText(Index,1,m_pEntryInfo->cName);
	m_DeviceList.SetItemText(Index,2,"是否定时");
	m_DeviceList.SetItemText(Index,3,m_pEntryInfo->vSharpPath);
	m_DeviceList.SetItemText(Index,4,"删除");
	if(m_pEntryInfo->bEnDualPort)		//双向打勾
	   m_DeviceList.SetCheck(Index);
/////////////////////////////////////////////////////////////////////////////////
	m_DeviceList.SetItemData(Index,(DWORD_PTR)lParam);
	return Index+1;
}


void CDeviceDlg::OnClickListDevice(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	LVHITTESTINFO lvhti;
	PEQUIPMENT_ENTRY m_pEntryInfo;

	lvhti.pt = pNMLV->ptAction;//point;
	
	int nItem = m_DeviceList.SubItemHitTest(&lvhti);	
	
	if((lvhti.iSubItem == 0) && (lvhti.iItem != -1))
	{
		m_pEntryInfo = (PEQUIPMENT_ENTRY)m_DeviceList.GetItemData(lvhti.iItem);
		//m_pRoomStateEntry->bEnDualPort = m_RoomStateList.GetItemState(lvhti.iItem,LVIF_STATE);
		m_pEntryInfo->bEnDualPort = !m_DeviceList.GetCheck(lvhti.iItem);
		if(lvhti.flags == LVHT_ABOVE)
			SendMessage(BM_MODIFY_DB_ENTRY,NULL,(LPARAM)m_pEntryInfo);
		else
			SendMessage(BM_MODIFY_DB_ENTRY,(WPARAM)&lvhti.iItem,(LPARAM)m_pEntryInfo);
	}

	if(m_PreItem.Flag == TRUE)			//??????(????)
	{
		UpdataItemStringFromEdit(m_PreItem.Item,m_PreItem.SubItem);
	}	
	*pResult = 0;
}

void CDeviceDlg::OnDblclkListDevice(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	PEQUIPMENT_ENTRY m_pEntryInfo;
	LVHITTESTINFO lvhti;
	lvhti.pt = pNMLV->ptAction;//point;
	int nItem = m_DeviceList.SubItemHitTest(&lvhti);	
	if(nItem == -1)			//??????(????)
	{//????
		m_pEntryInfo = (PEQUIPMENT_ENTRY)new EQUIPMENT_ENTRY;
		ZeroMemory(m_pEntryInfo,sizeof(EQUIPMENT_ENTRY));
		m_pEntryInfo->dwEntryIndex = GetNextDbIndex();
		memcpy(m_pEntryInfo->cName,(LPSTR)(LPCSTR)"未指派",sizeof("未指派"));
		m_pEntryInfo->bEnDualPort = 0;
		m_pEntryInfo->wType = 0;
		m_pEntryInfo->dwExtend = 0;
		memcpy(m_pEntryInfo->vSharpPath,(LPSTR)(LPCSTR)"ST00.jpg",sizeof("ST00.jpg"));
		SendMessage(BM_ADD_DB_ENTRY,NULL,(LPARAM)m_pEntryInfo);
	}
	else
	{
		if(lvhti.iSubItem == 1)
		   SetEditStringFromItem(lvhti.iItem,lvhti.iSubItem);
		
		if(lvhti.iSubItem == 4)
		{
			m_pEntryInfo = (PEQUIPMENT_ENTRY)m_DeviceList.GetItemData(lvhti.iItem);
			SendMessage(BM_DELETE_DB_ENTRY,NULL,(LPARAM)m_pEntryInfo);
		}
	}

	*pResult = 0;
}

void CDeviceDlg::SetEditStringFromItem(unsigned int nItem, unsigned int nSubItem)
{
	CRect rcCtrl;
	CString str;
	m_DeviceList.GetSubItemRect(nItem,nSubItem,LVIR_LABEL,rcCtrl);

	pEdit->MoveWindow(rcCtrl);
	pEdit->ShowWindow(SW_SHOWNORMAL);
	str = m_DeviceList.GetItemText(nItem,nSubItem);
	pEdit->SetWindowText(str);

	m_PreItem.Flag = TRUE;
	m_PreItem.Item = nItem;
	m_PreItem.SubItem = nSubItem;
}


void CDeviceDlg::UpdataItemStringFromEdit(unsigned int nItem, unsigned int nSubItem)
{
	CString str;
	PEQUIPMENT_ENTRY m_pEntryInfo = (PEQUIPMENT_ENTRY)m_DeviceList.GetItemData(nItem);
	if(m_pEntryInfo == NULL)
	   return;

	pEdit->GetWindowText(str);
	pEdit->ShowWindow(SW_HIDE);

	ZeroMemory(m_pEntryInfo->cName,ENTRY_NAME_BUF_SIZE);
	memcpy(m_pEntryInfo->cName,(LPSTR)(LPCSTR)str,str.GetLength());
	m_DeviceList.SetItemText(nItem,nSubItem,m_pEntryInfo->cName);
	//m_RoomStateList.SetItemText(nItem,nSubItem,str);
	m_PreItem.Flag = FALSE;
	m_PreItem.Item = -1;
	m_PreItem.SubItem = -1;
	//m_pRoomStateEntry->bEnDualPort = 25;
	//memcpy(m_pRoomStateEntry->vSharpPath,(LPSTR)(LPCSTR)"9527",sizeof("9527"));
	SendMessage(BM_MODIFY_DB_ENTRY,NULL,(LPARAM)m_pEntryInfo);
}

ULONG CDeviceDlg::GetNextDbIndex()
{
	int	EntryNum;
	PEQUIPMENT_ENTRY m_pEntryInfo = NULL;
	EntryNum = m_DeviceList.GetItemCount();
	if(!EntryNum)
	  return 1;

	m_pEntryInfo = (PEQUIPMENT_ENTRY)m_DeviceList.GetItemData(EntryNum-1);
	if(m_pEntryInfo == NULL)
	   return EntryNum;
	
	EntryNum = m_pEntryInfo->dwEntryIndex;
	return EntryNum+1;
}
