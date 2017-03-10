// RoomStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailModule.h"
#include "RoomStatusDlg.h"
#include <Winsock2.h>


// CRoomStatusDlg dialog

IMPLEMENT_DYNAMIC(CRoomStatusDlg, CDialog)

CRoomStatusDlg::CRoomStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomStatusDlg::IDD, pParent)
{

}

CRoomStatusDlg::~CRoomStatusDlg()
{
}

void CRoomStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRoomStatusDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CRoomStatusDlg::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_TIMING, &CRoomStatusDlg::OnBnClickedBtnTiming)
	ON_BN_CLICKED(IDC_BTN_GET, &CRoomStatusDlg::OnBnClickedBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, &CRoomStatusDlg::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CRoomStatusDlg message handlers

BOOL CRoomStatusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRoomStatusDlg::UpDataRoomInfo(PVOID lParam)
{
	PBUILDING_ENTRY  m_pEntryInfo = NULL;		//楼座链表
	PROMM_INFO_TRANSFER pRoomInfo = (PROMM_INFO_TRANSFER)lParam;
	lpRoomDetail = NULL;
	if (pRoomInfo == NULL)	{	return;	}
	lpRoomDetail = (PROOM_DETAIL_ENTRY)pRoomInfo->pRoomEntry;
	if (lpRoomDetail == NULL)	{	return;	}
	////////////////////////////////////////////////////////////////////////////
	//显示IP地址
	//SetDlgItemText(IDC_IPADDRESS,lpRoomDetail->sIpAddress);
	//UpdataAllItems(NULL,false);
}

//更新所有的参数信息
//如果lParam 为空则恢复默认的
//Flag为TRUE  往控件上填		FALSE往结构中填
void CRoomStatusDlg::UpdataAllItems(LPVOID lParam, BOOL Flag)
{
	DWORD iValue,iTemp;
	CTime mt(2014,5,20,18,00,00);
	if(lParam == NULL)
	{//时间设置
		mt = CTime::CTime(2014,4,16,18,00,00);
		((CDateTimeCtrl *)GetDlgItem(IDC_DATETIME_BEGIN))->SetTime(&mt);
		mt = CTime::CTime(2014,4,16,07,00,00);
		((CDateTimeCtrl *)GetDlgItem(IDC_DATETIME_END))->SetTime(&mt);
		//灯渐变百分比
		SetDlgItemInt(IDC_LIGHT_GRADUAL_PERCENT,20);
		//电机运行时间
		SetDlgItemInt(IDC_CURTAIN_MOTORS_RUN_TIMES,20);
		////季节模式
		//((CComboBox *)GetDlgItem(IDC_SEASON_MODE))->SetCurSel(0);
		//SetDlgItemInt(IDC_SUMMER_WORK_TEMPERATURE,25);
		//SetDlgItemInt(IDC_WINTER_WORK_TEMPERATURE,20);
		//门卡类型
		((CComboBox *)GetDlgItem(IDC_ELECTRONIC_BADGE))->SetCurSel(0);
		((CComboBox *)GetDlgItem(IDC_COM_DOOR_CARD))->SetCurSel(0);
		((CComboBox *)GetDlgItem(IDC_COM_AIR_PROTOCOL))->SetCurSel(0);
		//人体红外
		SetDlgItemInt(IDC_EDIT_IR_TIME,10);
		return;
	}
	//=======================================================
	if(Flag == TRUE)
	{
		PRCU_ARG_GET_RES_PACK pPack = reinterpret_cast<PRCU_ARG_GET_RES_PACK>(lParam);
		iValue = pPack->dwTime & 0x000000FF;
		iValue = BCD2_DWORD(iValue);
		iTemp = (pPack->dwTime >> 8) & 0x000000FF;
		iTemp = BCD2_DWORD(iTemp);
		mt = CTime::CTime(2013,07,15,iTemp,iValue,00);
		((CDateTimeCtrl *)GetDlgItem(IDC_DATETIME_END))->SetTime(&mt);
		iValue = (pPack->dwTime >> 16) & 0x000000FF;
		iValue = BCD2_DWORD(iValue);
		iTemp = (pPack->dwTime >> 24) & 0x000000FF;
		iTemp = BCD2_DWORD(iTemp);
		mt = CTime::CTime(2013,07,15,iTemp,iValue,00);
		((CDateTimeCtrl *)GetDlgItem(IDC_DATETIME_BEGIN))->SetTime(&mt);
		//灯渐变百分比
		iValue = BCD2_DWORD(pPack->bLightPercent);
		SetDlgItemInt(IDC_LIGHT_GRADUAL_PERCENT,iValue);
		//电机运行时间
		iValue = BCD2_DWORD(pPack->bMotorRumTimes);
		SetDlgItemInt(IDC_CURTAIN_MOTORS_RUN_TIMES,iValue);
		////季节模式
		//((CComboBox *)GetDlgItem(IDC_SEASON_MODE))->SetCurSel(pPack->bSeasonKeyword-1);
		//iValue = pPack->wTemerature & 0x000000FF;
		//iTemp = BCD2_DWORD(iValue);
		//SetDlgItemInt(IDC_SUMMER_WORK_TEMPERATURE,iTemp);
		//iValue = (pPack->wTemerature>>8) & 0x000000FF;
		//iTemp = BCD2_DWORD(iValue);
		//SetDlgItemInt(IDC_WINTER_WORK_TEMPERATURE,iTemp);
		//门卡类型
		((CComboBox *)GetDlgItem(IDC_ELECTRONIC_BADGE))->SetCurSel((pPack->bAccessCard)&0x01);
		((CComboBox *)GetDlgItem(IDC_COM_DOOR_CARD))->SetCurSel((pPack->bAccessCard) >> 1);	
		((CComboBox *)GetDlgItem(IDC_COM_AIR_PROTOCOL))->SetCurSel((pPack->bAccessCard) >> 2);	
		//人体红外
		iValue = BCD2_DWORD(pPack->bIrTime);
		SetDlgItemInt(IDC_EDIT_IR_TIME,iValue);
	}
	else
	{
		PRCU_ARG_SET_REQ_PACK pPack = (PRCU_ARG_SET_REQ_PACK)lParam;

		((CDateTimeCtrl *)GetDlgItem(IDC_DATETIME_END))->GetTime(mt);
		iValue = mt.GetMinute();
		iTemp = DWORD2_BCD(iValue);
		pPack->dwTime = iTemp;
		//==========================
		iValue = mt.GetHour();
		iTemp = DWORD2_BCD(iValue);
		pPack->dwTime |= iTemp << 8;
		((CDateTimeCtrl *)GetDlgItem(IDC_DATETIME_BEGIN))->GetTime(mt);
		iValue = mt.GetMinute();
		iTemp = DWORD2_BCD(iValue);
		pPack->dwTime |= iTemp << 16;
		iValue = mt.GetHour();
		iTemp = DWORD2_BCD(iValue);
		pPack->dwTime |= iTemp << 24;
		//灯渐变百分比
		iValue = GetDlgItemInt(IDC_LIGHT_GRADUAL_PERCENT);
		pPack->bLightPercent = DWORD2_BCD(iValue);
		//电机运行时间
		iValue = GetDlgItemInt(IDC_CURTAIN_MOTORS_RUN_TIMES);
		pPack->bMotorRumTimes = DWORD2_BCD(iValue);
		////季节模式
		/*pPack->bSeasonKeyword = ((CComboBox *)GetDlgItem(IDC_SEASON_MODE))->GetCurSel()+1;
		iValue = GetDlgItemInt(IDC_SUMMER_WORK_TEMPERATURE);
		iTemp = DWORD2_BCD(iValue);
		pPack->wTemerature = iTemp;
		iValue = GetDlgItemInt(IDC_WINTER_WORK_TEMPERATURE);
		iTemp = DWORD2_BCD(iValue);
		pPack->wTemerature |= iTemp << 8;*/
		//门卡类型
		UCHAR temp1,temp2,temp3;
		temp1 = ((CComboBox *)GetDlgItem(IDC_ELECTRONIC_BADGE))->GetCurSel();
		temp2 = ((CComboBox *)GetDlgItem(IDC_COM_DOOR_CARD))->GetCurSel();
		temp3 = ((CComboBox *)GetDlgItem(IDC_COM_AIR_PROTOCOL))->GetCurSel();
		temp2 = temp2 << 1;
		temp3 = temp3 << 2;
		pPack->bAccessCard = temp1 | temp2 ;
		pPack->bAccessCard |= temp3;
		//红外检测
		pPack->bIrTime = GetDlgItemInt(IDC_EDIT_IR_TIME);
	}
}

void CRoomStatusDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
	if(bShow == TRUE)
	{
		UpdataAllItems(NULL,TRUE);

	}
}

BOOL CRoomStatusDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

void CRoomStatusDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CRoomStatusDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}

HBRUSH CRoomStatusDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CRoomStatusDlg::OnBnClickedBtnRefresh()
{
	// TODO: Add your control notification handler code here
	CTime mt;
	mt = CTime::GetCurrentTime();
	//======================================================
	CDateTimeCtrl *m_Date = (CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_DATE);
	CDateTimeCtrl *m_Time = (CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_TIME);



	m_Date->SetTime(&mt);
	m_Time->SetTime(&mt);
}

void CRoomStatusDlg::OnBnClickedBtnTiming()
{
	// TODO: Add your control notification handler code here
	CTime mt;
	DWORD IpAddress;
	PBYTE pBuf = NULL;
	PBYTE pRevBuf = NULL;
	DWORD nBytes,nRevLength;
	DWORD dwRtua = 10550;
	WORD  wMstaAndSeq = 0x005E;
	PRCU_SET_TIMIMG_PACK pPack = NULL;
	nRevLength = 256;
	pRevBuf = new BYTE[nRevLength];
	memset(pRevBuf,0,nRevLength);
	PROOM_DETAIL_ENTRY m_pRoomEntry = lpRoomDetail;

	CDateTimeCtrl *m_Date = (CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_DATE);
	CDateTimeCtrl *m_Time = (CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER_TIME);
	//m_Date->GetTime(mt);
	m_Time->GetTime(mt);	
	//=================================================================================
	nBytes = SetRCUtimingPacket(NULL,mt);
	pBuf = new BYTE[nBytes];
	if(pBuf == NULL)
	{
		delete pPack;
		delete[] pRevBuf;
		return;
	}
	memset(pBuf,0,nBytes);
	SetRCUtimingPacket(pBuf,mt);
	pPack = reinterpret_cast<PRCU_SET_TIMIMG_PACK>(pBuf);
	pPack->sPreFrame.dwRtua = DWORD2_BCD(dwRtua);
	pPack->sPreFrame.wMstaAndSeq = 0x005E;
	//========================================================================			
	pPack->sPostFrame.bCS = Crc8((PBYTE)pPack,nBytes-1);
	//============================================================
	IpAddress = inet_addr(m_pRoomEntry->sIpAddress);
	IpAddress = ToLittleEndian(IpAddress);

	nRevLength = SendDataWithResponse((PBYTE)pPack,nBytes,\
		pRevBuf,nRevLength,\
		IpAddress,m_pRoomEntry->dwPort);

	//	nBytes = offset(RCU_ARG_GET_RES_UNIT,lwTnm);
	PRCU_ARG_SET_RES_UNIT pUnit = reinterpret_cast<PRCU_ARG_SET_RES_UNIT>(pRevBuf+13);
	if(pUnit->bResult != 0x00)
	{
		CString str;
		str.Format("数据项编号:%04X 设置失败[%s]",pUnit->uEntry,ErrString[pUnit->bResult]);
		MessageBox(str);
	}
	delete pPack;
	delete[] pRevBuf;
}

void CRoomStatusDlg::OnBnClickedBtnGet()
{
	// TODO: Add your control notification handler code here
	DWORD nBytes,nRevLength;
	DWORD IpAddress;
	PBYTE pBuf = NULL;
	DWORD dwRtua = 10550;
	WORD  wMstaAndSeq = 0x005E;
	PRCU_ARG_GET_REQ_PACK pPack = NULL;
	pPack = new RCU_ARG_GET_REQ_PACK;
	memset(pPack,0,sizeof(RCU_ARG_GET_REQ_PACK));

	nRevLength = 256;
	pBuf = new BYTE[nRevLength];
	memset(pBuf,0,nRevLength);
	PROOM_DETAIL_ENTRY m_pRoomEntry = lpRoomDetail;
	// TODO: Add your control notification handler code here
	if((pPack == NULL) || (m_pRoomEntry == NULL))
	{
		delete pPack;
		delete[] pBuf;
		return;
	}
	nBytes = GetRCUargPacket(pPack);
	//RTUA
	pPack->dwRtua = DWORD2_BCD(dwRtua);
	pPack->wMstaAndSeq = 0x005E;
	//========================================================================			
	pPack->sPostFrame.bCS = Crc8((PBYTE)pPack,nBytes-1);
	//====================================================================
	IpAddress = inet_addr(m_pRoomEntry->sIpAddress);
	IpAddress = ToLittleEndian(IpAddress);

	nRevLength = SendDataWithResponse((PBYTE)pPack,nBytes,\
		pBuf,nRevLength,\
		IpAddress,m_pRoomEntry->dwPort);
	//=======================================================
	//pRevPack = reinterpret_cast<RCU_ARG_SET_PACK *>(pBuf);
	UpdataAllItems(pBuf,TRUE);	
	//RecordBuffer("Johnson_Arg_Read.v",(PBYTE)pPack,nBytes);
	//RecordBuffer("Johnson_Arg_Write.v",pBuf,nRevLength);	
	delete pPack;
	delete[] pBuf;
}

void CRoomStatusDlg::OnBnClickedBtnSet()
{
	// TODO: Add your control notification handler code here
	DWORD nBytes,nRevLength;
	DWORD IpAddress;
	PBYTE pBuf = NULL;
	DWORD dwRtua = 10550;
	WORD  wMstaAndSeq = 0x005E;
	PRCU_ARG_SET_REQ_PACK pPack = NULL;

	nRevLength = 256;
	pBuf = new BYTE[nRevLength];
	memset(pBuf,0,nRevLength);
	PROOM_DETAIL_ENTRY m_pRoomEntry = lpRoomDetail;
	// TODO: Add your control notification handler code here
	pPack = new RCU_ARG_SET_REQ_PACK;
	if((pPack == NULL) || (m_pRoomEntry == NULL))
	{
		delete pPack;
		delete[] pBuf;
		return;
	}
	nBytes = SetRCUargPacket(pPack);
	//RTUA
	pPack->sPreFrame.dwRtua = DWORD2_BCD(dwRtua);
	pPack->sPreFrame.wMstaAndSeq = 0x005E;
	//========================================================================		
	UpdataAllItems(pPack,FALSE);	
	pPack->sPostFrame.bCS = Crc8((PBYTE)pPack,nBytes-1);
	//====================================================================
	IpAddress = inet_addr(m_pRoomEntry->sIpAddress);
	IpAddress = ToLittleEndian(IpAddress);

	nRevLength = SendDataWithResponse((PBYTE)pPack,nBytes,\
		pBuf,nRevLength,\
		IpAddress,m_pRoomEntry->dwPort);
	//=======================================================
	PRCU_ARG_SET_RES_UNIT pUnit = reinterpret_cast<PRCU_ARG_SET_RES_UNIT>(pBuf+13);
	nBytes = 0;
	CString str;
	while(pUnit->uEntry != 0x00)
	{
		if(pUnit->bResult != 0x00)
		{
			str.Format("数据项编号:%04X 设置失败[%s]",pUnit->uEntry,ErrString[pUnit->bResult]);
			MessageBox(str);
		}
		pUnit++;
	}



	//pRevPack = reinterpret_cast<RCU_ARG_SET_PACK *>(pBuf);
	//RecordBuffer("Johnson_Arg_Write.v",(PBYTE)pPack,nBytes);
	//RecordBuffer("Johnson_Arg_Read.v",(PBYTE)pBuf,nRevLength);

	delete pPack;
	delete[] pBuf;
}

void CRoomStatusDlg::OnOK()
{

}