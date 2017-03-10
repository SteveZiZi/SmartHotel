// MainRoomInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailModule.h"
#include "MainRoomInfoDlg.h"


// CMainRoomInfoDlg dialog

IMPLEMENT_DYNAMIC(CMainRoomInfoDlg, CDialog)

CMainRoomInfoDlg::CMainRoomInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainRoomInfoDlg::IDD, pParent)
{
	pRoomStatusDlg = NULL;
	pDeviceInfoDlg = NULL;
	pAirConditionDlg = NULL;
	pRealStatuDlg = NULL;
	lParamBuf = NULL;

	nSelect = 0;
}

CMainRoomInfoDlg::~CMainRoomInfoDlg()
{
}

void CMainRoomInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainRoomInfoDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MAIN_TAB, &CMainRoomInfoDlg::OnTcnSelchangeMainTab)
END_MESSAGE_MAP()


// CMainRoomInfoDlg message handlers

BOOL CMainRoomInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	
	//InitSocket(MAKEWORD(1,1));	
	InitGolabVariant();
	InitAllSubDlg(TRUE);
	InitTabCtrl();




	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMainRoomInfoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

void CMainRoomInfoDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

void CMainRoomInfoDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

BOOL CMainRoomInfoDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}



void CMainRoomInfoDlg::SetDataBuffer(LPVOID lParam)
{
	lParamBuf = lParam;
}

void CMainRoomInfoDlg::InitGolabVariant()
{
	CString str;
	ULONG   RecordNum = 0;		//查表的结果
	PBUILDING_ENTRY  m_pEntryInfo = NULL;		//楼座链表
	PROMM_INFO_TRANSFER pRoomInfo = (PROMM_INFO_TRANSFER)lParamBuf;
	PROOM_DETAIL_ENTRY m_pRoomEntry = NULL;
	if (pRoomInfo == NULL)	{	return;	}
	m_pRoomEntry = (PROOM_DETAIL_ENTRY)pRoomInfo->pRoomEntry;
	if (m_pRoomEntry == NULL)	{	return;	}
//======================================================================================
	str.Format("F-%02d",m_pRoomEntry->bFloorNum);
	SetDlgItemText(IDC_FLOOR_NUM,str);

	str.Format("R-%02d",m_pRoomEntry->bRoomNum);
	SetDlgItemText(IDC_ROOM_NUM,str);

	//链接所有的记录到链表
	str.Format("BuildingID=%d",m_pRoomEntry->bBuildingNum);
	RecordNum = (ULONG)GetBuildingRecord(&m_pEntryInfo,(LPSTR)(LPCSTR)str);
	SetDlgItemText(IDC_BUILDING,m_pEntryInfo->cName);
	
	/*SetDlgItemText(IDC_IPADDRESS,m_pRoomEntry->sIpAddress);
	delete m_pEntryInfo;*/
	m_pEntryInfo = NULL;
}


void CMainRoomInfoDlg::InitTabCtrl()
{
	int nEntry = 0;
	CTabCtrl* pTab = (CTabCtrl*)GetDlgItem(IDC_MAIN_TAB);
	//pTab->ModifyStyle(0,TCS_VERTICAL);

	pTab->InsertItem(nEntry++,_T("设备参数"));
	pTab->InsertItem(nEntry++,_T("设备状态"));
	pTab->InsertItem(nEntry++,_T("空调状态"));
	pTab->InsertItem(nEntry++,_T("房态信息"));

	pTab->SetCurSel(nSelect);
	ShowSelectEntry(nSelect);
}
void CMainRoomInfoDlg::OnTcnSelchangeMainTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CTabCtrl* pTab = (CTabCtrl*)GetDlgItem(IDC_MAIN_TAB);
	int nEntry = pTab->GetCurSel();
	if (nEntry == -1)	{	return;	}
	ShowSelectEntry(nEntry);

	*pResult = 0;
}

void CMainRoomInfoDlg::InitAllSubDlg(BOOL bFlag)
{
	PROMM_INFO_TRANSFER pRoomInfo = (PROMM_INFO_TRANSFER)lParamBuf;
	if (pRoomInfo == NULL)	
	{	
		return;	
	}
	if (bFlag == TRUE)
	{
		if (pRoomStatusDlg == NULL){
			pRoomStatusDlg = new CRoomStatusDlg;
			pRoomStatusDlg->Create(IDD_ROOM_STATUS_DIALOG,GetDlgItem(IDC_STATIC_CUSTOMER));
			pRoomStatusDlg->ShowWindow(SW_HIDE);
			pRoomStatusDlg->UpDataRoomInfo(lParamBuf);
		}

		if (pDeviceInfoDlg == NULL){
			pDeviceInfoDlg = new CDeviceInfoDlg;
			pDeviceInfoDlg->Create(IDD_DEVICE_INFO_DIALOG,GetDlgItem(IDC_STATIC_CUSTOMER));
			pDeviceInfoDlg->ShowWindow(SW_HIDE);
			pDeviceInfoDlg->UpDataRoomInfo(lParamBuf);
			//pDeviceInfoDlg->InitDeviceInfo();
		}

		if (pAirConditionDlg == NULL){
			pAirConditionDlg = new CAirConditionDlg;
			pAirConditionDlg->Create(IDD_AIR_CONDITION_DIALOG,GetDlgItem(IDC_STATIC_CUSTOMER));
			pAirConditionDlg->ShowWindow(SW_HIDE);
			pAirConditionDlg->UpDataRoomInfo(lParamBuf);
			//pAirConditionDlg->initAirCondition();
		}
		if (pRealStatuDlg == NULL){
			pRealStatuDlg = new CRealStatuDlg;
			pRealStatuDlg->Create(IDD_REAL_STATU_DLG,GetDlgItem(IDC_STATIC_CUSTOMER));
			pRealStatuDlg->ShowWindow(SW_HIDE);
			pRealStatuDlg->UpDataRoomInfo(lParamBuf);
		}
	}
	else{
	if (pRoomStatusDlg != NULL)	{	delete pRoomStatusDlg;	pRoomStatusDlg = NULL;	}
	if (pDeviceInfoDlg != NULL)	{	delete pDeviceInfoDlg;	pDeviceInfoDlg = NULL;	}
	if (pAirConditionDlg != NULL){	delete pAirConditionDlg;	pAirConditionDlg = NULL;	}
	if (pRoomStatusDlg != NULL) {	delete pRealStatuDlg; pRealStatuDlg = NULL; }
	}
}



void CMainRoomInfoDlg::ShowSelectEntry(int nEntry)
{
	if(nEntry == 0){
		pRoomStatusDlg->ShowWindow(SW_SHOWNORMAL);
		pDeviceInfoDlg->ShowWindow(SW_HIDE);
		pAirConditionDlg->ShowWindow(SW_HIDE);
		pRealStatuDlg->ShowWindow(SW_HIDE);
	}else if(nEntry == 1){
		pRoomStatusDlg->ShowWindow(SW_HIDE);
		pDeviceInfoDlg->ShowWindow(SW_SHOWNORMAL);
		pAirConditionDlg->ShowWindow(SW_HIDE);
		pRealStatuDlg->ShowWindow(SW_HIDE);

	}else if(nEntry == 2)
	{
		pRoomStatusDlg->ShowWindow(SW_HIDE);
		pDeviceInfoDlg->ShowWindow(SW_HIDE);
		pAirConditionDlg->ShowWindow(SW_SHOWNORMAL);
		pRealStatuDlg->ShowWindow(SW_HIDE);
	}else if(nEntry == 3)
	{
		pRoomStatusDlg->ShowWindow(SW_HIDE);
		pDeviceInfoDlg->ShowWindow(SW_HIDE);
		pAirConditionDlg->ShowWindow(SW_HIDE);
		pRealStatuDlg->ShowWindow(SW_SHOWNORMAL);
	}
	else{
		pRoomStatusDlg->ShowWindow(SW_HIDE);
		pDeviceInfoDlg->ShowWindow(SW_HIDE);
		pAirConditionDlg->ShowWindow(SW_HIDE);
		pRealStatuDlg->ShowWindow(SW_HIDE);
	}
}

void CMainRoomInfoDlg::OnOK()
{

}