// RoomTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailCFG.h"
#include "RoomTypeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomTypeDlg dialog


CRoomTypeDlg::CRoomTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomTypeDlg)
		// NOTE: the ClassWizard will add member initialization here

	//}}AFX_DATA_INIT
}

CRoomTypeDlg::~CRoomTypeDlg()
{

}

void CRoomTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomTypeDlg)
	DDX_Control(pDX, IDC_COMBO_RCU_TYPE, m_RcuType);
	DDX_Control(pDX, IDD_TAB_ROOMTYPE, m_tRoomType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRoomTypeDlg, CDialog)
	//{{AFX_MSG_MAP(CRoomTypeDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDD_TAB_ROOMTYPE, OnSelchangeTabRoomtype)
	ON_MESSAGE(BM_ADD_DB_ENTRY,DoAddOpt)
	ON_MESSAGE(BM_MODIFY_DB_ENTRY,DoModifyOpt)
	ON_MESSAGE(BM_DELETE_DB_ENTRY,DoDeleteOpt)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MODIFY, OnBtnModify)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomTypeDlg message handlers

BOOL CRoomTypeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

//先列出所有的RCU
	EnumAllRCU();

//列出所有的房类
	EnumAllRoomType();


	if(m_tRoomType.GetItemCount())
	{
		m_tRoomType.SetCurSel(0);
		UpDataEntry(0);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CRoomTypeDlg::OnSelchangeTabRoomtype(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int Index; 	
	Index = m_tRoomType.GetCurSel();

	UpDataEntry(Index);
	*pResult = 0;
}


BOOL CRoomTypeDlg::CheckTypeExist(PCHAR pTempRt)
{
   int i = 0;
   int Result = 1;

   char szBuf[256];
   TCITEM tci;   

   tci.mask =   TCIF_TEXT;   
   tci.pszText =   szBuf;   
   tci.cchTextMax =   sizeof(szBuf)/sizeof(TCHAR);   
   //PROOMTYPE m_pRoomType;
   while(Result)
   {
     memset(szBuf,'\0',256); 
	 Result = m_tRoomType.GetItem(i,&tci);
     if(strcmp(szBuf,pTempRt) == 0)
	   return TRUE;
     i++;
   }
   return FALSE;
}

void CRoomTypeDlg::EnumAllRoomType()
{
	ULONG	Result;
	ULONG   RecordNum = 0;
	PROOM_TYPE_ENTRY	m_pEntryInfo = NULL;	
	//链接所有的记录到链表
	Result = (ULONG)GetRoomTypeRecord(&m_pEntryInfo,NULL);
	//增加到列表框中去		
	while(RecordNum<Result)
	{
		m_tRoomType.InsertItem(RecordNum,m_pEntryInfo->cName);
		m_TypeList.Add(m_pEntryInfo);
		
		m_pEntryInfo = m_pEntryInfo->pNext;
		RecordNum++;
	}
}

void CRoomTypeDlg::EnumAllRCU()
{
	ULONG	Result;
	ULONG   RecordNum = 0;
	PRCU_TYPE_ENTRY	m_pEntryInfo = NULL;	
	PRCU_TYPE_ENTRY	m_pNextEntry = NULL;

	m_RcuType.InsertString(0,"未定义");
	//链接所有的记录到链表
	Result = (ULONG)GetRCUTypeRecord(&m_pEntryInfo,NULL);
	//增加到列表框中去		m_RcuType
	while(RecordNum<Result)
	{
		RecordNum++;
		m_RcuType.InsertString(RecordNum,m_pEntryInfo->RCUName);
		m_RcuType.SetItemData(RecordNum,m_pEntryInfo->RCUId);
		m_pNextEntry = m_pEntryInfo->pNext;
		//==========================================================
		if(m_pEntryInfo->pEquipDetail != NULL)
			delete[] m_pEntryInfo->pEquipDetail;
		if(m_pEntryInfo->pStatusDetail != NULL)
			delete[] m_pEntryInfo->pStatusDetail;
		delete[] m_pEntryInfo; 
		//==========================================================
		m_pEntryInfo = m_pNextEntry;
		//RecordNum++;
	}
}

BOOL CRoomTypeDlg::PreTranslateMessage(MSG* pMsg) 
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

BOOL CRoomTypeDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
   INT_PTR i,itemNum;
   PROOM_TYPE_ENTRY	m_pEntryInfo = NULL;	
   itemNum = m_TypeList.GetSize();
   for(i=0;i<itemNum;i++)
   {
       m_pEntryInfo = (PROOM_TYPE_ENTRY)m_TypeList.GetAt(i);
       delete[] (PROOM_TYPE_ENTRY)m_pEntryInfo;
   }
   m_TypeList.RemoveAll();
	return CDialog::DestroyWindow();
}

void CRoomTypeDlg::UpDataEntry(int nSel)
{
	BOOL	IsValid = FALSE;
	int Index = 0;
	PROOM_TYPE_ENTRY	m_pEntryInfo = NULL;
	if(nSel == -1)
	{
		SetDlgItemText(IDC_EDIT_ROOMTYPE_NAME,NULL);

	}

	m_pEntryInfo = (PROOM_TYPE_ENTRY)m_TypeList.GetAt(nSel);
	SetDlgItemText(IDC_EDIT_ROOMTYPE_NAME,m_pEntryInfo->cName);
	for(Index = 0;Index<m_RcuType.GetCount();Index++)
	{
		if(m_RcuType.GetItemData(Index) == m_pEntryInfo->dwExRCU)
		{
			IsValid = TRUE;
			break;
		}
	}

	if(IsValid == FALSE)
	  Index = -1;
	m_RcuType.SetCurSel(Index);
}


//执行要增加的房态信息
LRESULT CRoomTypeDlg::DoAddOpt(WPARAM wParam, LPARAM lParam)
{
	PROOM_TYPE_ENTRY	m_pEntryInfo = (PROOM_TYPE_ENTRY)lParam;
	CString str;
	int status;
	str.Format("是否确认要【增加】 设备(%s)",m_pEntryInfo->cName);
	if(MessageBox(str,"警告",MB_OKCANCEL) == IDCANCEL)
	{
	   delete[] (PROOM_TYPE_ENTRY)m_pEntryInfo;
	   return FALSE;
	}
//判断不为空
	if(m_pEntryInfo == NULL)
	{
		MessageBox("增加项为空,请重新选择！");
		delete[] (PROOM_TYPE_ENTRY)m_pEntryInfo;
		return FALSE;
	}
	m_pEntryInfo->dwEntryIndex = GetLastEntryNum();	
//=========================================================================================
//举例
//INSERT INTO cctv value(0,5,'8265')
	str.Format("INSERT INTO %s VALUE(%d,'%s',%d)",roomTypeSettingTableName,
			    m_pEntryInfo->dwEntryIndex,m_pEntryInfo->cName,m_pEntryInfo->dwExRCU);
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  delete[] (PROOM_TYPE_ENTRY)m_pEntryInfo;
	  return	FALSE;
	}

	m_tRoomType.InsertItem(m_tRoomType.GetItemCount(),m_pEntryInfo->cName);
	m_TypeList.Add(m_pEntryInfo);


//UpDataEntry(m_tRoomType.GetItemCount()-1);
	return TRUE;
}



//执行要修改的房态信息
LRESULT CRoomTypeDlg::DoModifyOpt(WPARAM wParam, LPARAM lParam)
{
	PROOM_TYPE_ENTRY	m_pEntryInfo = (PROOM_TYPE_ENTRY)lParam;
	PROOM_TYPE_ENTRY	RealEntryInfo;
	int nSel = *(int *)wParam;
	CString str,temp;
	int status = FALSE;
	str.Format("是否确认要【修改】 设备(%s) %d",m_pEntryInfo->cName,nSel);
	if(MessageBox(str,"警告",MB_OKCANCEL) == IDCANCEL)
	{
	   return FALSE;
	}
//判断不为空
	if(m_pEntryInfo == NULL)
	{
		MessageBox("修改项为空,请重新选择！");
		delete[] (PROOM_TYPE_ENTRY)m_pEntryInfo;
		return FALSE;
	}
//==================================================================
	RealEntryInfo = (PROOM_TYPE_ENTRY)m_TypeList.GetAt(nSel);

	str.Format("UPDATE %s SET ",roomTypeSettingTableName);
	if(strcmp(m_pEntryInfo->cName,RealEntryInfo->cName) != 0)
	{
		//ZeroMemory(m_OldEntry->cName,ENTRY_NAME_BUF_SIZE);
		memcpy(RealEntryInfo->cName,m_pEntryInfo->cName,ENTRY_NAME_BUF_SIZE);
		temp.Format("roomtypeName='%s'",RealEntryInfo->cName);
		str = str + temp;
		status = TRUE;
	}
	if(m_pEntryInfo->dwExRCU != RealEntryInfo->dwExRCU)
	{
		RealEntryInfo->dwExRCU = m_pEntryInfo->dwExRCU;
		if(status == TRUE)
			temp.Format(",RCUID=%d",RealEntryInfo->dwExRCU);
		else
			temp.Format("RCUID=%d",RealEntryInfo->dwExRCU);
		str = str + temp;
		status = TRUE;
	
	}
	delete[] (PROOMSTATUS_ENTRY)m_pEntryInfo;
	if(status == FALSE)
	{
		//MessageBox("不需要修改");
		return TRUE;
	}
	temp.Format(" WHERE ID=%d",RealEntryInfo->dwEntryIndex);
	str = str + temp;


	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);


	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);  
	  return	FALSE;
	}
	return TRUE;
}



//执行要删除的房态信息
LRESULT CRoomTypeDlg::DoDeleteOpt(WPARAM wParam, LPARAM lParam)
{
	PROOM_TYPE_ENTRY	m_pEntryInfo = (PROOM_TYPE_ENTRY)lParam;
	int nSel = *(int *)wParam;
	CString str;
	int status;
	str.Format("是否确认要【增加】 设备(%s) %d",m_pEntryInfo->cName,nSel);
	if(MessageBox(str,"警告",MB_OKCANCEL) == IDCANCEL)
	{
	   return FALSE;
	}
//判断不为空
	if(m_pEntryInfo == NULL)
	{
		MessageBox("增加项为空,请重新选择！");
		delete[] (PROOM_TYPE_ENTRY)m_pEntryInfo;
		return FALSE;
	}
//=========================================================================================
//举例
	str.Format("DELETE FROM %s WHERE ID=%d",roomTypeSettingTableName,m_pEntryInfo->dwEntryIndex);
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  return	FALSE;
	}

	delete[] (PROOM_TYPE_ENTRY)m_pEntryInfo;
	m_TypeList.RemoveAt(nSel);
	m_tRoomType.DeleteItem(nSel);

	if(nSel)
	{
		m_tRoomType.SetCurSel(nSel-1);
		UpDataEntry(nSel-1);
	}
	return TRUE;
}

void CRoomTypeDlg::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	PROOM_TYPE_ENTRY	m_pEntryInfo = NULL;
	m_pEntryInfo = new ROOM_TYPE_ENTRY;
	DWORD EntryNum;
	if(m_pEntryInfo == NULL)
	{
		MessageBox("添加失败");
		return;
	}
	ZeroMemory(m_pEntryInfo,sizeof(ROOM_TYPE_ENTRY));
//得到房类名
	GetDlgItemText(IDC_EDIT_ROOMTYPE_NAME,m_pEntryInfo->cName,ENTRY_NAME_BUF_SIZE);
	if(m_pEntryInfo->cName[0] == '\0')
	{
		MessageBox("房类名不能为空");
		delete (PROOM_TYPE_ENTRY)m_pEntryInfo;
		return;
	}
	if(CheckName(m_pEntryInfo->cName) != -1)
	{
		MessageBox("房类存在");
		delete (PROOM_TYPE_ENTRY)m_pEntryInfo;
		return;
	}
//RCU索引号
	EntryNum = m_RcuType.GetCurSel();
	m_pEntryInfo->dwExRCU = (DWORD)m_RcuType.GetItemData(EntryNum);

	SendMessage(BM_ADD_DB_ENTRY,NULL,(LPARAM)m_pEntryInfo);
}

void CRoomTypeDlg::OnBtnModify() 
{
	// TODO: Add your control notification handler code here
	int Index,Result; 	
	Index = m_tRoomType.GetCurSel();

	PROOM_TYPE_ENTRY	m_pEntryInfo = NULL;
	m_pEntryInfo = new ROOM_TYPE_ENTRY;
	DWORD EntryNum;
	if(m_pEntryInfo == NULL)
	{
		MessageBox("修改失败");
		return;
	}
	ZeroMemory(m_pEntryInfo,sizeof(ROOM_TYPE_ENTRY));
//得到房类名
	GetDlgItemText(IDC_EDIT_ROOMTYPE_NAME,m_pEntryInfo->cName,ENTRY_NAME_BUF_SIZE);
	if(m_pEntryInfo->cName[0] == '\0')
	{
		MessageBox("房类名不能为空");
		delete (PROOM_TYPE_ENTRY)m_pEntryInfo;
		return;
	}
	Result = CheckName(m_pEntryInfo->cName);
	if((Result != -1) && (Result != Index))
	{
		MessageBox("房类存在");
		delete (PROOM_TYPE_ENTRY)m_pEntryInfo;
		return;
	}
//RCU索引号
	EntryNum = m_RcuType.GetCurSel();
	m_pEntryInfo->dwExRCU = (DWORD)m_RcuType.GetItemData(EntryNum);

	SendMessage(BM_MODIFY_DB_ENTRY,(WPARAM)&Index,(LPARAM)m_pEntryInfo);
}

void CRoomTypeDlg::OnBtnDelete() 
{
	// TODO: Add your control notification handler code here
	int Index; 	
	Index = m_tRoomType.GetCurSel();
	SendMessage(BM_DELETE_DB_ENTRY,(WPARAM)&Index,(LPARAM)m_TypeList.GetAt(Index));	
}

DWORD CRoomTypeDlg::GetLastEntryNum()
{
	INT_PTR i,itemNum;
	DWORD Result = 0;
	PROOM_TYPE_ENTRY	m_pEntryInfo = NULL;	
	itemNum = m_TypeList.GetSize();
	for(i=0;i<itemNum;i++)
	{
		m_pEntryInfo = (PROOM_TYPE_ENTRY)m_TypeList.GetAt(i);
		if(Result < m_pEntryInfo->dwEntryIndex)
			Result = m_pEntryInfo->dwEntryIndex;
	}
	return Result+1;
}

int CRoomTypeDlg::CheckName(PCHAR pName)
{
   INT_PTR i,itemNum;
   int Result = -1;
   PROOM_TYPE_ENTRY	m_pEntryInfo = NULL;	
   itemNum = m_TypeList.GetSize();
   for(i=0;i<itemNum;i++)
   {
       m_pEntryInfo = (PROOM_TYPE_ENTRY)m_TypeList.GetAt(i);
       if(memcmp(m_pEntryInfo->cName,pName,ENTRY_NAME_BUF_SIZE) == 0)
	   {
			Result = (int)i;
			break;
	   }
   }
   return Result;
}
