// SubRoomDetailInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailCFG.h"
#include "SubRoomDetailInfoDlg.h"

#include "SubRoomDetailDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
CSubRoomDetailDlg* m_Dlg = NULL;	
// CSubRoomDetailInfoDlg dialog


CSubRoomDetailInfoDlg::CSubRoomDetailInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubRoomDetailInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubRoomDetailInfoDlg)
	//}}AFX_DATA_INIT
	m_Dlg = (CSubRoomDetailDlg*)pParent;
	m_pCurEntryInfo = NULL;
}


void CSubRoomDetailInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubRoomDetailInfoDlg)
	DDX_Control(pDX, IDC_COMBO_ROOM_TYPE, m_RoomType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubRoomDetailInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CSubRoomDetailInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubRoomDetailInfoDlg message handlers

BOOL CSubRoomDetailInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here
	InitRoomType();

	InitContext();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSubRoomDetailInfoDlg::SetRelationData(PVOID lParam)
{
	CString str;
	PROOM_DETAIL_ENTRY pTempRoom = (PROOM_DETAIL_ENTRY)lParam;
	if(pTempRoom == NULL)
	{	
		return;
	}
////////////////////////////////////////////////////////////////////////////////
	str.Format("BuildingID=%d AND FloorNum=%d AND DoorNum=%d",pTempRoom->bBuildingNum,pTempRoom->bFloorNum,pTempRoom->bRoomNum);	
	GetRoomRecord(&m_pCurEntryInfo,str);
}

void CSubRoomDetailInfoDlg::InitRoomType()
{
	int Index,EntryNum;
	CString str;
	CComboBox* m_pCombo = (CComboBox*)m_Dlg->GetDlgItem(IDC_COMBO_ROOMTYPE);
	EntryNum = m_pCombo->GetCount();
	for(Index=0;Index<EntryNum;Index++)
	{
		m_pCombo->GetLBText(Index,str);
		m_RoomType.InsertString(Index,str);
		m_RoomType.SetItemData(Index,m_pCombo->GetItemData(Index));
	}
}

void CSubRoomDetailInfoDlg::InitContext()
{
	int i = 0;
	if(m_pCurEntryInfo == NULL)
		return;
	//楼座信息
	SetDlgItemText(IDC_BUILDING,m_Dlg->m_pBuildingInfo->cName);
	//楼层信息 
	SetDlgItemInt(IDC_EDIT_FLOOR,m_pCurEntryInfo->bFloorNum);
	//房间信息 
	SetDlgItemInt(IDC_EDIT_ROOM,m_pCurEntryInfo->bRoomNum);
	//房类
	for(i=0;i<m_RoomType.GetCount();i++)
	{
	  if((DWORD)m_RoomType.GetItemData(i) == m_pCurEntryInfo->dwRoomTypeID)
		break;
	}
    m_RoomType.SetCurSel(i);
	//IP
	SetDlgItemText(IDC_IPADDRESS,m_pCurEntryInfo->sIpAddress);
	//端口
	SetDlgItemInt(IDC_EDIT_PORT,m_pCurEntryInfo->dwPort);
}

void CSubRoomDetailInfoDlg::OnOK() 
{
	// TODO: Add extra validation here
	//楼层信息 
	m_pCurEntryInfo->bFloorNum = GetDlgItemInt(IDC_EDIT_FLOOR);
	//房间信息 
	m_pCurEntryInfo->bRoomNum = GetDlgItemInt(IDC_EDIT_ROOM);
	//房类
	m_pCurEntryInfo->dwRoomTypeID = (DWORD)m_RoomType.GetItemData(m_RoomType.GetCurSel());
	//IP
	memset(m_pCurEntryInfo->sIpAddress,'\0',32);
	GetDlgItemText(IDC_IPADDRESS,m_pCurEntryInfo->sIpAddress,32);
	//端口
	m_pCurEntryInfo->dwPort = GetDlgItemInt(IDC_EDIT_PORT);	

	CDialog::OnOK();
}

PVOID CSubRoomDetailInfoDlg::GetRelationData()
{
	return m_pCurEntryInfo;
}
