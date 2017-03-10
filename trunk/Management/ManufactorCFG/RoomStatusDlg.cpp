// RoomStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManufactorCFG.h"
#include "RoomStatusDlg.h"

//#include "DbAccess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoomStatusDlg dialog


CRoomStatusDlg::CRoomStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomStatusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomStatusDlg)
	//}}AFX_DATA_INIT

}

CRoomStatusDlg::~CRoomStatusDlg()
{
   //CSubBaseRoomStatusDlg *m_pBaseDlg;
   DeleteAllListContext();


   if(pEdit != NULL)
	 delete[] pEdit;
}


void CRoomStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomStatusDlg)
	DDX_Control(pDX, IDC_TAB_ROOM_STATUS, m_RoomStateEntry);
	DDX_Control(pDX, IDC_LIST_ROOMSTATE, m_RoomStateList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRoomStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CRoomStatusDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_ROOM_STATUS, OnSelchangeTabRoomStatus)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ROOMSTATE, OnItemchangedListRoomstate)
	ON_MESSAGE(WM_EX_DELETE,DoDeleteOpt)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ROOMSTATE, OnClickListRoomstate)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ROOMSTATE, OnDblclkListRoomstate)

	ON_MESSAGE(BM_ADD_DB_ENTRY,DoAddOpt)
	ON_MESSAGE(BM_MODIFY_DB_ENTRY,DoModifyOpt)
	ON_MESSAGE(BM_DELETE_DB_ENTRY,DoDeleteOpt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomStatusDlg message handlers

BOOL CRoomStatusDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
//�½�һ���ɱ༭��
	pEdit = new CEdit;
	if(pEdit == NULL)
      exit(0);
	pEdit->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,CRect(10, 10, 100, 40),(CWnd *)FromHandle(m_RoomStateList.m_hWnd), 1);
	pEdit->ShowWindow(SW_HIDE);
	m_PreItem.Flag = FALSE;
	m_PreItem.Item = -1;
	m_PreItem.SubItem = -1;

    //Step 1: ���ú��б�ؼ����
	InitRoomstateListCtrl();
	//Step 2: �ٳ�ʼ����ѡ��
	InitRoomStatus();        //��ʼ��ѡ��

	//�õ��������еļ�¼
	EnumAllTableRecord(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRoomStatusDlg::InitRoomStatus()
{
//����0��������̬
    m_RoomStateEntry.InsertItem(0,"������̬");
    m_RoomStateEntry.InsertItem(1,"��ʱ��̬");
    m_RoomStateEntry.InsertItem(2,"����̬");
	m_RoomStateEntry.InsertItem(3,"������̬");
 
	//����Ĭ�ϵ�Ϊ
	m_RoomStateEntry.SetCurSel(0);
}

void CRoomStatusDlg::OnSelchangeTabRoomStatus(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nSelectEntry;
	nSelectEntry = m_RoomStateEntry.GetCurSel();
	EnumAllTableRecord(nSelectEntry);

	*pResult = 0;
}

//��ʼ���б�ؼ���һЩ�������
void CRoomStatusDlg::InitRoomstateListCtrl()
{
	CRect Rt; 
	int Width;
	DWORD dwStyleEx;
	int Order[12]={1,0,2,3,4,5,6,7,8,9,10,11};
	::GetClientRect(m_RoomStateList.GetSafeHwnd(),&Rt);
	//�ı���ʾģʽΪ����
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	dwStyleEx = LVS_EX_FULLROWSELECT |  LVS_EX_CHECKBOXES | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES;  //LVS_EX_FULLROWSELECT |  
    m_RoomStateList.SetExtendedStyle(dwStyleEx);
	//m_RoomStateList.SetItemHigh(120);
    //m_RoomStateList.SetTextAttr(25,"����",RGB(0,0,255));

	Width = GetSystemMetrics(SM_CYVSCROLL);
	Width = Rt.Width() - Width;
    ////////////////////////////////////////////////////////
    m_RoomStateList.InsertColumn( 0, "DualPort", LVCFMT_CENTER, Width*3/10);//������
    m_RoomStateList.InsertColumn( 1, "Name", LVCFMT_CENTER, Width*3/10 );//������
    m_RoomStateList.InsertColumn( 2, "View", LVCFMT_CENTER, Width/5 );
    m_RoomStateList.InsertColumn( 3, "Btn", LVCFMT_CENTER, Width/5 );
    m_RoomStateList.SetColumnOrderArray(4,Order);
}




BOOL CRoomStatusDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
      //��Ҫ�˳�
	  if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT)
	    return TRUE;
	  //��������
	  if(pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN)
	  {
		  if(::GetDlgCtrlID(::GetFocus()) != IDC_LIST_ROOMSTATE)
	        return TRUE;
	  }
	}
	return CDialog::PreTranslateMessage(pMsg);
}


//ִ��Ҫɾ���ķ�̬��Ϣ
LRESULT CRoomStatusDlg::DoDeleteOpt(WPARAM wParam, LPARAM lParam)
{
	PROOMSTATUS_ENTRY	m_pRoomState = (PROOMSTATUS_ENTRY)lParam;
	int TotalListNum = m_RoomStateList.GetItemCount();
	int TableIndex = m_RoomStateEntry.GetCurSel();
	CString str;
	int status;
	str.Format("�Ƿ�ȷ��Ҫ��ɾ���� ��̬(%s)",m_pRoomState->cName);
	if(MessageBox(str,"����",MB_OKCANCEL) == IDCANCEL)
	{
	  
	   return FALSE;
	}


	if(m_pRoomState == NULL)
	{
		MessageBox("ɾ����Ϊ��,������ѡ��");
		return 0;
	}
//=========================================================================================
	str.Format("DELETE FROM %s WHERE ID=%d",sRoomStatusName[TableIndex],m_pRoomState->dwEntryIndex);
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  return	FALSE;
	}
	
	SetDlgItemInt(IDC_ENTRYNUM,TotalListNum-1);
	//���ҵ�Ҫɾ������Ŀ
	while(TotalListNum)
	{
		TotalListNum--;
		if((PROOMSTATUS_ENTRY)m_RoomStateList.GetItemData(TotalListNum) == m_pRoomState)
			break;
	}

	m_RoomStateList.DeleteItem(TotalListNum);
	delete[] (PROOMSTATUS_ENTRY)m_pRoomState;
	return TRUE;
}

//ִ��Ҫ���ӵķ�̬��Ϣ
LRESULT CRoomStatusDlg::DoAddOpt(WPARAM wParam, LPARAM lParam)
{
	PROOMSTATUS_ENTRY	m_pRoomState = (PROOMSTATUS_ENTRY)lParam;
	int TableIndex = m_RoomStateEntry.GetCurSel();
	int TotalListNum = m_RoomStateList.GetItemCount();
	//DWORD LastEntry = ((PROOMSTATUS_ENTRY)(m_RoomStateList.GetItemData(TotalListNum-1)))->dwEntryIndex+1;
	CString str;
	int status;
	str.Format("�Ƿ�ȷ��Ҫ�����ӡ� ��̬(%s)",m_pRoomState->cName);
	if(MessageBox(str,"����",MB_OKCANCEL) == IDCANCEL)
	{
	   delete[] (PROOMSTATUS_ENTRY)m_pRoomState;
	   return FALSE;
	}
	if(m_pRoomState == NULL)
	{
		MessageBox("������Ϊ��,������ѡ��");
		return 0;
	}
//=========================================================================================
//����
//INSERT INTO cctv value(0,5,'8265')
	str.Format("INSERT INTO %s VALUE(%d,'%s',%d,%d,'%s')",sRoomStatusName[TableIndex],
			    m_pRoomState->dwEntryIndex,m_pRoomState->cName,m_pRoomState->bEnDualPort,
				m_pRoomState->dwExtend,m_pRoomState->vSharpPath);

	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(status == FALSE)
	{
	  char ErrInfo[MAX_PATH];
	  m_mysql->GetMySQLError(ErrInfo);
	  MessageBox(ErrInfo);
	  //MessageBox(str);
	  delete[] (PROOMSTATUS_ENTRY)m_pRoomState;
	  return	FALSE;
	}

	InertOneRow(TotalListNum,m_pRoomState);
	
	SetDlgItemInt(IDC_ENTRYNUM,TotalListNum+1);
	return TRUE;
}



//ִ��Ҫ�޸ĵķ�̬��Ϣ
LRESULT CRoomStatusDlg::DoModifyOpt(WPARAM wParam, LPARAM lParam)
{
	PROOMSTATUS_ENTRY	m_pRoomState = (PROOMSTATUS_ENTRY)lParam;
	int TableIndex = m_RoomStateEntry.GetCurSel();
	
	PUINT	Item = (PUINT)wParam;
	if(m_pRoomState == NULL)
	{
		MessageBox("������Ϊ��,������ѡ��");
		return 0;
	}
	CString str;
	int status;
	str.Format("�Ƿ�ȷ��Ҫ���޸ġ� ��̬(%s)",m_pRoomState->cName);
	if(MessageBox(str,"����",MB_OKCANCEL) == IDCANCEL)
	{
	   return FALSE;
	}

//=========================================================================================
//����
//UPDATE roomstate_base SET roomstate_base.baseType = '����' where roomstate_base.baseType = 'Ĭ��'
	//str.Format("UPDATE %s SET TypeName='%s' IsDualDirection=%d Shape='%s' WHERE ID=%d",
	//	sRoomStatusName[TableIndex],m_pRoomState->cName,m_pRoomState->bEnDualPort,
	//	m_pRoomState->vSharpPath,m_pRoomState->dwEntryIndex);
	str.Format("UPDATE %s SET TypeName='%s',IsDualDirection=%d,Shape='%s' WHERE ID=%d",sRoomStatusName[TableIndex],
		m_pRoomState->cName,m_pRoomState->bEnDualPort,m_pRoomState->vSharpPath,m_pRoomState->dwEntryIndex);

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
	  m_RoomStateList.SetCheck(*Item,m_pRoomState->bEnDualPort);
	return TRUE;
}

void CRoomStatusDlg::EnumAllTableRecord(int TableIndex)
{
	CString str;
	ULONG	Result;
	ULONG   RecordNum = 0;
	PROOMSTATUS_ENTRY m_pRoomStateList = NULL;	
	//������б�򼰲���
	DeleteAllListContext();
	//�������еļ�¼������
	Result = (ULONG)GetRoomStatusRecord(TableIndex,&m_pRoomStateList,NULL);
	//���ӵ��б����ȥ
	while(RecordNum<Result)
	{
		InertOneRow(RecordNum,m_pRoomStateList);
		m_pRoomStateList = m_pRoomStateList->pNext;
		RecordNum++;
	}
	SetDlgItemInt(IDC_ENTRYNUM,RecordNum);
}

void CRoomStatusDlg::DeleteAllListContext()
{
	int RecordNum;
	PROOMSTATUS_ENTRY m_pRoomStateList = NULL;	
	RecordNum = m_RoomStateList.GetItemCount();
	while(RecordNum)
	{
		RecordNum--;
		m_pRoomStateList = (PROOMSTATUS_ENTRY)m_RoomStateList.GetItemData(RecordNum);
		if(m_pRoomStateList != NULL)
			delete[] (PROOMSTATUS_ENTRY)m_pRoomStateList;
		m_RoomStateList.DeleteItem(RecordNum);
	}
}

int CRoomStatusDlg::InertOneRow(int Index, LPVOID lParam)
{
	CString str;
	PROOMSTATUS_ENTRY m_pRoomStateEntry = (PROOMSTATUS_ENTRY)lParam;
/////////////////////////////////////////////////////////////////////////////////
	m_RoomStateList.InsertItem(Index,"�Ƿ�˫��");
	m_RoomStateList.SetItemText(Index,1,m_pRoomStateEntry->cName);
	m_RoomStateList.SetItemText(Index,2,m_pRoomStateEntry->vSharpPath);
	m_RoomStateList.SetItemText(Index,3,"ɾ��");

	if(m_pRoomStateEntry->bEnDualPort)		//˫���
	   m_RoomStateList.SetCheck(Index);
/////////////////////////////////////////////////////////////////////////////////
	m_RoomStateList.SetItemData(Index,(DWORD_PTR)lParam);
	return Index+1;
}

void CRoomStatusDlg::OnItemchangedListRoomstate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
















	*pResult = 0;
}

void CRoomStatusDlg::OnClickListRoomstate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	LVHITTESTINFO lvhti;
	PROOMSTATUS_ENTRY m_pRoomStateEntry;

	lvhti.pt = pNMLV->ptAction;//point;
	
	int nItem = m_RoomStateList.SubItemHitTest(&lvhti);// ������굱ǰѡ�е�ITEM��SUBITEM	
	
	if((lvhti.iSubItem == 0) && (lvhti.iItem != -1))
	{
		m_pRoomStateEntry = (PROOMSTATUS_ENTRY)m_RoomStateList.GetItemData(lvhti.iItem);
		//m_pRoomStateEntry->bEnDualPort = m_RoomStateList.GetItemState(lvhti.iItem,LVIF_STATE);
		m_pRoomStateEntry->bEnDualPort = !m_RoomStateList.GetCheck(lvhti.iItem);
		if(lvhti.flags == LVHT_ABOVE)
			SendMessage(BM_MODIFY_DB_ENTRY,NULL,(LPARAM)m_pRoomStateEntry);
		else
			SendMessage(BM_MODIFY_DB_ENTRY,(WPARAM)&lvhti.iItem,(LPARAM)m_pRoomStateEntry);
	}

	if(m_PreItem.Flag == TRUE)			//�ڷ�Χ����(�ɵ�����)
	{
		UpdataItemStringFromEdit(m_PreItem.Item,m_PreItem.SubItem);
	}
	*pResult = 0;
}

void CRoomStatusDlg::OnDblclkListRoomstate(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	PROOMSTATUS_ENTRY m_pRoomStateEntry;
	LVHITTESTINFO lvhti;
	lvhti.pt = pNMLV->ptAction;//point;
	int nItem = m_RoomStateList.SubItemHitTest(&lvhti);// ������굱ǰѡ�е�ITEM��SUBITEM	
	if(nItem == -1)			//�ڷ�Χ����(�ɵ�����)
	{//����һ��
		m_pRoomStateEntry = new ROOMSTATUS_ENTRY;
		ZeroMemory(m_pRoomStateEntry,sizeof(ROOMSTATUS_ENTRY));
		m_pRoomStateEntry->dwEntryIndex = GetNextDbIndex();
		
		CString str;
		str.Format("%d",m_pRoomStateEntry->dwEntryIndex);
		MessageBox(str);



		memcpy(m_pRoomStateEntry->cName,(LPSTR)(LPCSTR)"δָ��",sizeof("δָ��"));
		m_pRoomStateEntry->bEnDualPort = 0;
		m_pRoomStateEntry->dwExtend = 0;
		memcpy(m_pRoomStateEntry->vSharpPath,(LPSTR)(LPCSTR)"ST00.jpg",sizeof("ST00.jpg"));

		SendMessage(BM_ADD_DB_ENTRY,NULL,(LPARAM)m_pRoomStateEntry);
	}
	else
	{
		if(lvhti.iSubItem == 1)
		   SetEditStringFromItem(lvhti.iItem,lvhti.iSubItem);
		
		if(lvhti.iSubItem == 3)
		{
			m_pRoomStateEntry = (PROOMSTATUS_ENTRY)m_RoomStateList.GetItemData(lvhti.iItem);
			SendMessage(BM_DELETE_DB_ENTRY,NULL,(LPARAM)m_pRoomStateEntry);
		}
	}
	*pResult = 0;
}

void CRoomStatusDlg::SetEditStringFromItem(unsigned int nItem, unsigned int nSubItem)
{
	CRect rcCtrl;
	CString str;
	m_RoomStateList.GetSubItemRect(nItem,nSubItem,LVIR_LABEL,rcCtrl);//��ȡѡ��λ�õ����� 

	pEdit->MoveWindow(rcCtrl);
	pEdit->ShowWindow(SW_SHOWNORMAL);
	str = m_RoomStateList.GetItemText(nItem,nSubItem);
	pEdit->SetWindowText(str);

	m_PreItem.Flag = TRUE;
	m_PreItem.Item = nItem;
	m_PreItem.SubItem = nSubItem;
}


void CRoomStatusDlg::UpdataItemStringFromEdit(unsigned int nItem, unsigned int nSubItem)
{
	CString str;
	PROOMSTATUS_ENTRY m_pRoomStateEntry = (PROOMSTATUS_ENTRY)m_RoomStateList.GetItemData(nItem);
	if(m_pRoomStateEntry == NULL)
	   return;

	pEdit->GetWindowText(str);
	pEdit->ShowWindow(SW_HIDE);

	ZeroMemory(m_pRoomStateEntry->cName,ENTRY_NAME_BUF_SIZE);
	memcpy(m_pRoomStateEntry->cName,(LPSTR)(LPCSTR)str,str.GetLength());
	m_RoomStateList.SetItemText(nItem,nSubItem,m_pRoomStateEntry->cName);
	//m_RoomStateList.SetItemText(nItem,nSubItem,str);
	m_PreItem.Flag = FALSE;
	m_PreItem.Item = -1;
	m_PreItem.SubItem = -1;
	//m_pRoomStateEntry->bEnDualPort = 25;
	//memcpy(m_pRoomStateEntry->vSharpPath,(LPSTR)(LPCSTR)"9527",sizeof("9527"));
	SendMessage(BM_MODIFY_DB_ENTRY,NULL,(LPARAM)m_pRoomStateEntry);
}

ULONG CRoomStatusDlg::GetNextDbIndex()
{
	int	EntryNum;
	PROOMSTATUS_ENTRY m_pRoomStateEntry = NULL;
	EntryNum = m_RoomStateList.GetItemCount();
	if(!EntryNum)
	  return 1;

	m_pRoomStateEntry = (PROOMSTATUS_ENTRY)m_RoomStateList.GetItemData(EntryNum-1);
	if(m_pRoomStateEntry == NULL)
	   return EntryNum;
	
	EntryNum = m_pRoomStateEntry->dwEntryIndex;
	return EntryNum+1;
}
