// RCUDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManufactorCFG.h"
#include "RCUDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRCUDlg dialog
CRCUDlg::CRCUDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRCUDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRCUDlg)
	m_pSubDeviceMethodDlg = NULL;
	//}}AFX_DATA_INIT
}

CRCUDlg::~CRCUDlg()
{
	//CSubRCUBaseInfoDlg *m_pBaseInfoDlg;
	if(m_pBaseInfoDlg != NULL)
		delete[] (CSubRCUBaseInfoDlg *)m_pBaseInfoDlg;
	if (m_pSubDeviceMethodDlg != NULL)
		delete m_pSubDeviceMethodDlg;

	m_pSubDeviceMethodDlg = NULL;
	//CSubRCURoomPortsDlg *m_pRoomPortsDlg;
	/*if(m_pRoomPortsDlg != NULL)
	delete[] (CSubRCURoomPortsDlg *)m_pRoomPortsDlg;

	//CSubRCUDevicePortsDlg *m_pDevicePortsDlg;
	if(m_pDevicePortsDlg != NULL)
	delete[] (CSubRCUDevicePortsDlg *)m_pDevicePortsDlg;
	*/
}

void CRCUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRCUDlg)
	DDX_Control(pDX, IDC_TAB_RCU_SETTING, m_TableEntry);
	DDX_Control(pDX, IDC_TREE_RCU, m_RCUEntryTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRCUDlg, CDialog)
	//{{AFX_MSG_MAP(CRCUDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_RCU, OnSelchangedTreeRcu)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_RCU_SETTING, OnSelchangeTabRcuSetting)
	ON_MESSAGE(BM_ADD_DB_ENTRY,DoAddOpt)
	ON_MESSAGE(BM_DELETE_DB_ENTRY,DoDeleteOpt)
	ON_MESSAGE(BM_MODIFY_DB_ENTRY,DoModifyOpt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRCUDlg message handlers

BOOL CRCUDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
// TODO: Add extra initialization here
//先初始化标签控件
	InitRCUTableEntry();
//加载所有的RCU
	EnumAllTableRecord();
//选定一个初值
	SetTableEntryFocus(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRCUDlg::OnSelchangedTreeRcu(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem;
	PVOID	lparam;
	hItem = m_RCUEntryTree.GetSelectedItem();	//pNMTreeView->itemNew.hItem;
	lparam = (PVOID)m_RCUEntryTree.GetItemData(hItem);
/////////////////////////////////////////////////////////////////////////////
	UpDataAllSubDlg(hItem,lparam);
	*pResult = 0;
}

void CRCUDlg::OnSelchangeTabRcuSetting(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelect;
	nSelect = m_TableEntry.GetCurSel();
	SetTableEntryFocus(nSelect);

	*pResult = 0;
}




LRESULT CRCUDlg::DoAddOpt(WPARAM wParam,LPARAM lParam)
{
	HTREEITEM hItem = NULL;
	PRCU_TYPE_ENTRY	m_pEntryInfo = (PRCU_TYPE_ENTRY)lParam;	
	CString str;
	int status;

	if(SearchEntryExist(m_RCUEntryTree.GetRootItem(),m_pEntryInfo->RCUName) == TRUE)
	{
		str.Format("RCU名称[%s]重复,请重试",m_pEntryInfo->RCUName);
		MessageBox(str);
		delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return FALSE;
	}

	str.Format("是否确认要【增加】 RCU(%s)",m_pEntryInfo->RCUName);
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
	m_pEntryInfo->RCUId = GetNextEntry(m_RCUEntryTree.GetRootItem())+1;
	str.Format("INSERT INTO %s VALUE(%d,'%s',%d,%d,'','')",RCUTypeTableName,
			    m_pEntryInfo->RCUId,m_pEntryInfo->RCUName,m_pEntryInfo->wEquipPortNum,
				m_pEntryInfo->wStatusPortNum);

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
	hItem = m_RCUEntryTree.InsertItem(m_pEntryInfo->RCUName);
	m_RCUEntryTree.SetItemData(hItem,(DWORD_PTR)m_pEntryInfo);

	UpDataAllSubDlg(hItem,m_pEntryInfo);
	return TRUE;
}


LRESULT CRCUDlg::DoDeleteOpt(WPARAM wParam,LPARAM lParam)
{
	HTREEITEM hItem = (HTREEITEM)wParam;
	PRCU_TYPE_ENTRY	m_pEntryInfo = (PRCU_TYPE_ENTRY)lParam;	
	CString str;
	int status;
	str.Format("是否确认要【删除】 RCU(%s)",m_pEntryInfo->RCUName);
	if(MessageBox(str,"警告",MB_OKCANCEL) == IDCANCEL)
	{
	   return FALSE;
	}	
//1：删除数据库
	str.Format("DELETE FROM %s WHERE ID=%d",RCUTypeTableName,m_pEntryInfo->RCUId);

	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  return	FALSE;
	}
//2：删除树控件
	m_RCUEntryTree.DeleteItem(hItem);
	if(m_pEntryInfo->pEquipDetail != NULL)
	  delete[] m_pEntryInfo->pEquipDetail;
	if(m_pEntryInfo->pStatusDetail != NULL)
	  delete[] m_pEntryInfo->pStatusDetail;
	delete[]m_pEntryInfo; 

	return TRUE;
}


LRESULT CRCUDlg::DoModifyOpt(WPARAM wParam,LPARAM lParam)
{
	HTREEITEM hItem = (HTREEITEM)wParam;
	PRCU_TYPE_ENTRY	m_pNewEntryInfo = (PRCU_TYPE_ENTRY)lParam;	
	PRCU_TYPE_ENTRY m_OldEntry = (PRCU_TYPE_ENTRY)m_RCUEntryTree.GetItemData(hItem);
	CString str,temp;
	BOOL status = FALSE;

	/*if(SearchEntryExist(m_RCUEntryTree.GetRootItem(),m_pNewEntryInfo->RCUName) == TRUE)
	{
		str.Format("RCU名称[%s]重复,请重试",m_pNewEntryInfo->RCUName);
		MessageBox(str);
		return FALSE;
	}*/
	str.Format("是否确认要【修改】 RCU(%s)",m_pNewEntryInfo->RCUName);
	if(MessageBox(str,"警告",MB_OKCANCEL) == IDCANCEL)
	{
		delete[] (PRCU_TYPE_ENTRY)m_pNewEntryInfo;
		return FALSE;
	}	
	str.Format("UPDATE %s SET ",RCUTypeTableName);
	if(strcmp(m_pNewEntryInfo->RCUName,m_OldEntry->RCUName) != 0)
	{
		temp.Format("cName='%s'",m_pNewEntryInfo->RCUName);
		str = str + temp;
		status = TRUE;
	}
	if(m_pNewEntryInfo->wEquipPortNum != m_OldEntry->wEquipPortNum)
	{
		if(status == TRUE)
			temp.Format(",equipPortNum=%d",m_pNewEntryInfo->wEquipPortNum);
		else
			temp.Format("equipPortNum=%d",m_pNewEntryInfo->wEquipPortNum);
		str = str + temp;
		status = TRUE;
	
	}
	if(m_pNewEntryInfo->wStatusPortNum != m_OldEntry->wStatusPortNum)
	{
		if(status == TRUE)
			temp.Format(",statePortNum=%d",m_pNewEntryInfo->wStatusPortNum);
		else
			temp.Format("statePortNum=%d",m_pNewEntryInfo->wStatusPortNum);
		str = str + temp;
		status = TRUE;
	}
	if(status == FALSE)
	{
		delete[] m_pNewEntryInfo; 
		return FALSE;
	}
	temp.Format(" WHERE ID=%d",m_pNewEntryInfo->RCUId);
	str = str + temp;
//////////////////////////////////////////////////////////////////////////////////
	/*if(m_pNewEntryInfo->wEquipPortNum == m_OldEntry->wEquipPortNum)
	{
		m_pNewEntryInfo->pEquipDetail = m_OldEntry->pEquipDetail;
		m_OldEntry->pEquipDetail = NULL;
	}
	else
	{
		m_pNewEntryInfo->pEquipDetail = new RCU_PORT_UNIT[m_pNewEntryInfo->wEquipPortNum];
		if(m_pNewEntryInfo->pEquipDetail != NULL)
		{
			ZeroMemory(m_pNewEntryInfo->pEquipDetail,sizeof(RCU_PORT_UNIT)*m_pNewEntryInfo->wEquipPortNum);
			if(m_pNewEntryInfo->wEquipPortNum < m_OldEntry->wEquipPortNum)	  
				memcpy(m_pNewEntryInfo->pEquipDetail,m_OldEntry->pEquipDetail,sizeof(RCU_PORT_UNIT)*m_pNewEntryInfo->wEquipPortNum);
			else
				memcpy(m_pNewEntryInfo->pEquipDetail,m_OldEntry->pEquipDetail,sizeof(RCU_PORT_UNIT)*m_OldEntry->wEquipPortNum);
		}	
	}
	if(m_pNewEntryInfo->wStatusPortNum == m_OldEntry->wStatusPortNum)
	{
		m_pNewEntryInfo->pStatusDetail = m_OldEntry->pStatusDetail;
		m_OldEntry->pStatusDetail = NULL;
	}
	else
	{
		m_pNewEntryInfo->pStatusDetail = new RCU_PORT_UNIT[m_pNewEntryInfo->wStatusPortNum];
		if(m_pNewEntryInfo->pStatusDetail != NULL)
		{
			ZeroMemory(m_pNewEntryInfo->pStatusDetail,sizeof(RCU_PORT_UNIT)*m_pNewEntryInfo->wStatusPortNum);
			if(m_pNewEntryInfo->wStatusPortNum < m_OldEntry->wStatusPortNum)	  
				memcpy(m_pNewEntryInfo->pStatusDetail,m_OldEntry->pStatusDetail,sizeof(RCU_PORT_UNIT)*m_pNewEntryInfo->wStatusPortNum);
			else
				memcpy(m_pNewEntryInfo->pStatusDetail,m_OldEntry->pStatusDetail,sizeof(RCU_PORT_UNIT)*m_OldEntry->wStatusPortNum);
		}
	}*/
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
	m_RCUEntryTree.SetItemText(hItem,m_pNewEntryInfo->RCUName);
	m_RCUEntryTree.SetItemData(hItem,(DWORD_PTR)m_pNewEntryInfo);
	if(m_OldEntry->pEquipDetail != NULL)
		delete[] m_OldEntry->pEquipDetail;
	if(m_OldEntry->pStatusDetail != NULL)
		delete[] m_OldEntry->pStatusDetail;
	delete[] m_OldEntry; 

	UpDataAllSubDlg(hItem,m_pNewEntryInfo);
	return TRUE;
/*   CString strCmd,temp;
   BOOL status;
   PRCUTYPE ItemData;
   DWORD RCUId;
   ItemData = (PRCUTYPE)m_MCUEntry.GetItemData(hItem);
   RCUId = ItemData->RCUId;
   if(lParam == NULL)
	 return;

   //============================================================
   ZeroMemory(ItemData,sizeof(RCUTYPE));
   memcpy(ItemData,(PRCUTYPE)lParam,sizeof(RCUTYPE));
   ItemData->RCUId = RCUId;
   //==========================================================================
   strCmd.Format("UPDATE %s SET %s='%s',%s=%d,%s=%d where %s = %d",RCUTypeTableName,RCUColumn[1],ItemData->RCUName,\
	   RCUColumn[2],ItemData->wEquipPortNum,RCUColumn[3],ItemData->wStatePortNum,RCUColumn[0],ItemData->RCUId);

   //strCmd.Format("UPDATE %s SET %s='%s' ,%s=%d WHERE %s = %d",RCUTypeTableName,RCUColumn[1],ItemData->RCUName,\
   //   RCUColumn[2],ItemData->wEquipPortNum,RCUColumn[3],ItemData->wStatePortNum,RCUColumn[0],ItemData->RCUId);
   status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)strCmd);  
   if(!status)
   {
     m_mysql->GetMySQLError((LPSTR)(LPCSTR)temp);
	 MessageBox(temp);
   }
   /////////////////////////////////////////////////////////////////////////////////////////	
   m_MCUEntry.SetItemText(hItem,ItemData->RCUName);*/
	return TRUE;
}



BOOL CRCUDlg::SearchEntryExist(HTREEITEM hItem,const char *KeyString)
{
	HTREEITEM hCurItem;
	PRCU_TYPE_ENTRY	m_pEntryInfo;
	if(hItem == NULL)
	  return FALSE;

	m_pEntryInfo = (PRCU_TYPE_ENTRY)m_RCUEntryTree.GetItemData(hItem);
	if(strcmp(m_pEntryInfo->RCUName,KeyString) == 0)
		return TRUE;
///////////////////////////////////////////////////////////
	hCurItem = m_RCUEntryTree.GetNextItem(hItem,TVGN_NEXT);
	return SearchEntryExist(hCurItem,KeyString);
}

void CRCUDlg::InitRCUTableEntry()
{
	m_TableEntry.InsertItem(0,"基本信息");
//CSubRCUBaseInfoDlg *m_pBaseInfoDlg;
    m_pBaseInfoDlg = new CSubRCUBaseInfoDlg();
    m_pBaseInfoDlg->Create(IDD_SUB_RCU_BASEINFO_DIALOG,GetDlgItem(IDC_RCU_CUSTOMER));
	m_pBaseInfoDlg->ShowWindow(SW_HIDE);
//设备/房态端口   
	m_TableEntry.InsertItem(1,"配置方案");

	//CSubDeviceMethodDlg		*m_pSubDeviceMethodDlg;
	m_pSubDeviceMethodDlg = new CSubDeviceCfgMethodDlg;
	m_pSubDeviceMethodDlg->Create(IDD_SUB_DEVICE_METHOD_DIALOG,GetDlgItem(IDC_RCU_CUSTOMER));
	m_pSubDeviceMethodDlg->ShowWindow(SW_HIDE);	





//CSubRCURoomPortsDlg *m_pRoomPortsDlg;
    //m_pRoomPortsDlg = new CSubRCURoomPortsDlg();
    //m_pRoomPortsDlg->Create(IDD_SUB_RCU_ROOMPORTS_DIALOG,GetDlgItem(IDC_RCU_CUSTOMER));
	//m_pRoomPortsDlg->ShowWindow(SW_HIDE);	
//CSubRCUDevicePortsDlg *m_pDevicePortsDlg;
 //   m_TableEntry.InsertItem(2,"设备端口");
 //   m_pDevicePortsDlg = new CSubRCUDevicePortsDlg();
 //   m_pDevicePortsDlg->Create(IDD_SUB_RCU_DEVICEPORTS_DIALOG,GetDlgItem(IDC_RCU_CUSTOMER));
//m_pDevicePortsDlg->ShowWindow(SW_HIDE);	
}

void CRCUDlg::SetTableEntryFocus(UINT nTableEntry)
{
	//m_pBaseInfoDlg->ShowWindow(SW_HIDE);
	//m_pSubDeviceMethodDlg->ShowWindow(SW_HIDE);
	//m_pRoomPortsDlg->ShowWindow(SW_HIDE);
	//m_pDevicePortsDlg->ShowWindow(SW_HIDE);	
	
	switch(nTableEntry)
	{
		case 0:	m_pBaseInfoDlg->ShowWindow(SW_SHOWNORMAL);	
			    m_pSubDeviceMethodDlg->ShowWindow(SW_HIDE);
				break;
		case 1: m_pSubDeviceMethodDlg->ShowWindow(SW_SHOWNORMAL);	
			    m_pBaseInfoDlg->ShowWindow(SW_HIDE);
				break;
		//case 2: m_pDevicePortsDlg->ShowWindow(SW_SHOWNORMAL);		
		//		break;
		default:
				m_pBaseInfoDlg->ShowWindow(SW_HIDE);
				m_pSubDeviceMethodDlg->ShowWindow(SW_HIDE);
			    break;
	}
}

void CRCUDlg::EnumAllTableRecord()
{
	ULONG	Result;
	ULONG   RecordNum = 0;
	HTREEITEM tItem;
	PRCU_TYPE_ENTRY	m_pEntryInfo = NULL;	
	//链接所有的记录到链表
	Result = (ULONG)GetRCUTypeRecord(&m_pEntryInfo,NULL);
	//增加到列表框中去
	while(RecordNum<Result)
	{
		tItem = m_RCUEntryTree.InsertItem(m_pEntryInfo->RCUName);
		m_RCUEntryTree.SetItemData(tItem,(DWORD_PTR)m_pEntryInfo);
		m_pEntryInfo = m_pEntryInfo->pNext;
		RecordNum++;
	}
}

void CRCUDlg::UpDataAllSubDlg(HTREEITEM wParam,PVOID lParam)
{
	//PRCU_TYPE_ENTRY	m_pEntryInfo = (PRCU_TYPE_ENTRY)lParam;	
//基本信息	//CSubRCUBaseInfoDlg		*m_pBaseInfoDlg;
	m_pBaseInfoDlg->SetRelationItem(wParam);
	m_pBaseInfoDlg->UpdataRCU(lParam);

	m_pSubDeviceMethodDlg->SetRelationItem(wParam);
	m_pSubDeviceMethodDlg->UpdataRCU(lParam);
//设备端口	//CSubRCUDevicePortsDlg	*m_pDevicePortsDlg;
	//m_pDevicePortsDlg->SetPortNum(m_pEntryInfo->wEquipPortNum);
	//m_pDevicePortsDlg->SetRelationItem(lParam);
//房态端口	//CSubRCURoomPortsDlg		*m_pRoomPortsDlg;
	//m_pRoomPortsDlg->SetPortNum(m_pEntryInfo->wStatusPortNum);
	//m_pRoomPortsDlg->SetRelationItem(lParam);
}

BOOL CRCUDlg::PreTranslateMessage(MSG* pMsg) 
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

BOOL CRCUDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	//DeleteTreeContext(m_RCUEntryTree.GetRootItem());
	return CDialog::DestroyWindow();
}

void CRCUDlg::DeleteTreeContext(HTREEITEM hItem)
{
	PRCU_TYPE_ENTRY	m_pEntryInfo = NULL;	
	if(hItem == NULL)
	  return ;
	m_pEntryInfo = (PRCU_TYPE_ENTRY)m_RCUEntryTree.GetItemData(hItem);
	if(m_pEntryInfo != NULL)
	{
		if(m_pEntryInfo->pEquipDetail != NULL)
			delete[] m_pEntryInfo->pEquipDetail;
		if(m_pEntryInfo->pStatusDetail != NULL)
			delete[] m_pEntryInfo->pStatusDetail;
		delete[] m_pEntryInfo; 
	}
	DeleteTreeContext(m_RCUEntryTree.GetNextItem(hItem,TVGN_NEXT));
}

DWORD CRCUDlg::GetNextEntry(HTREEITEM hItem)
{
	DWORD Value = 0;
	PRCU_TYPE_ENTRY	m_pEntryInfo = NULL;
	HTREEITEM hReItem = NULL;
	if(hItem == NULL)
	  return 0;
	////////////////////////////////////
	while(hItem != NULL)
	{
		m_pEntryInfo = (PRCU_TYPE_ENTRY)m_RCUEntryTree.GetItemData(hItem);
		if(m_pEntryInfo->RCUId > Value)
			Value = m_pEntryInfo->RCUId;
		hItem = m_RCUEntryTree.GetNextItem(hItem,TVGN_NEXT);
	}
	return Value;
}
