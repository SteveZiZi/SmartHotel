// AirConditionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailModule.h"
#include "AirConditionDlg.h"
#include <Winsock2.h>

// CAirConditionDlg dialog

IMPLEMENT_DYNAMIC(CAirConditionDlg, CDialog)

CAirConditionDlg::CAirConditionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAirConditionDlg::IDD, pParent)
{

}

CAirConditionDlg::~CAirConditionDlg()
{
}

void CAirConditionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_SEASON_MODE,m_CobSeaonMode);
	DDX_Control(pDX,IDC_WORK_MODE,m_CobWorkMode);
	DDX_Control(pDX,IDC_FAN_SPEED,m_CobFanSpeed);
	DDX_Control(pDX,IDC_AIR_NUM,m_CobAirNum);
	DDX_Control(pDX,IDC_SET_TEMPERATURE,m_EditSetTempl);
	DDX_Control(pDX,IDC_ENV_TEMPERATURE,m_EditEnvTempl);
}


BEGIN_MESSAGE_MAP(CAirConditionDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_GET, &CAirConditionDlg::OnBnClickedBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, &CAirConditionDlg::OnBnClickedBtnSet)
	ON_BN_CLICKED(IDC_BTN_FLUSH, &CAirConditionDlg::OnBnClickedBtnFlush)
END_MESSAGE_MAP()


// CAirConditionDlg message handlers

//void CAirConditionDlg::PreInitDialog()
//{
//	// TODO: Add your specialized code here and/or call the base class
//
//	CDialog::PreInitDialog();
//}

BOOL CAirConditionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_CobSeaonMode.SetCurSel(0);
	m_CobWorkMode.SetCurSel(0);
	m_CobFanSpeed.SetCurSel(0);
	m_EditSetTempl.SetWindowText("0");
	m_EditEnvTempl.SetWindowText("0");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CAirConditionDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

void CAirConditionDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CAirConditionDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}

HBRUSH CAirConditionDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CAirConditionDlg::UpDataRoomInfo(PVOID lParam)
{
	PBUILDING_ENTRY  m_pEntryInfo = NULL;		//楼座链表
	PROMM_INFO_TRANSFER pRoomInfo = (PROMM_INFO_TRANSFER)lParam;
	lpRoomDetail = NULL;
	if (pRoomInfo == NULL)	{	return;	}
	lpRoomDetail = (PROOM_DETAIL_ENTRY)pRoomInfo->pRoomEntry;
	if (lpRoomDetail == NULL)	{	return;	}	
}

void CAirConditionDlg::initAirCondition()
{
	DWORD nBytes,nRevLength;
	DWORD IpAddress;
	PBYTE pBuf = NULL;
	DWORD dwRtua = 10550;
	WORD  wMstaAndSeq = 0x005E;
	PRCU_ARG_GET_REQ_PACK_0202 pPack = NULL;
	pPack = new RCU_ARG_GET_REQ_PACK_0202;
	memset(pPack,0,sizeof(RCU_ARG_GET_REQ_PACK_0202));

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
	nBytes = GetRCUargPacket0202(pPack);
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
	UpdataAirNum(pBuf);	
	
	delete pPack;
	delete[] pBuf;
}

void CAirConditionDlg::OnBnClickedBtnGet()
{
	DWORD nBytes,nRevLength;
	DWORD IpAddress;
	PBYTE pBuf = NULL;
	DWORD dwRtua = 10550;
	WORD  wMstaAndSeq = 0x005E;
	PRCU_ARG_AIR_GET_REQ_PACK_021X pPack = NULL;
	pPack = new RCU_ARG_AIR_GET_REQ_PACK_021X;
	memset(pPack,0,sizeof(RCU_ARG_AIR_GET_REQ_PACK_021X));

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
	int airNum = GetDlgItemInt(IDC_AIR_NUM);
	nBytes = GetAirConditionPacket(pPack,airNum);
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

//更新所有的参数信息
//如果lParam 为空则恢复默认的
//Flag为TRUE  往控件上填		FALSE往结构中填
void CAirConditionDlg::UpdataAllItems(LPVOID lParam, BOOL Flag)
{
	int iValue,iTemp;
	if(Flag == TRUE)
	{
		PRCU_ARG_AIR_GET_RES_PACK_021X pPack = reinterpret_cast<PRCU_ARG_AIR_GET_RES_PACK_021X>(lParam);
		//季节模式
		((CComboBox *)GetDlgItem(IDC_SEASON_MODE))->SetCurSel(pPack->bContent[0] & 0x03);
		((CComboBox *)GetDlgItem(IDC_WORK_MODE))->SetCurSel(pPack->bContent[1]);
		((CComboBox *)GetDlgItem(IDC_FAN_SPEED))->SetCurSel(pPack->bContent[4]);
		iValue = pPack->bContent[2];
		//iTemp = BCD2_DWORD(iValue);
		SetDlgItemInt(IDC_SET_TEMPERATURE,iValue);
		iValue = (pPack->bContent[3]);
		//iTemp = BCD2_DWORD(iValue);
		SetDlgItemInt(IDC_ENV_TEMPERATURE,iValue);
		iValue = (pPack->bContent[0] >> 2);
		SetDlgItemInt(IDC_EDIT_SEASON_WORK_TEMP,iValue);
			
	}
	else
	{
		UCHAR temp1,temp2;
		PRCU_ARG_AIR_SET_REQ_PACK_021X pPack = (PRCU_ARG_AIR_SET_REQ_PACK_021X)lParam;
		temp1 = m_CobSeaonMode.GetCurSel();
		pPack->bContent[1] = m_CobWorkMode.GetCurSel();
		pPack->bContent[4] = m_CobFanSpeed.GetCurSel();
		UCHAR temp;
		temp2 = GetDlgItemInt(IDC_EDIT_SEASON_WORK_TEMP);
		temp2 = temp2 << 2;
		pPack->bContent[0]  = temp1 | temp2;
		temp = GetDlgItemInt(IDC_SET_TEMPERATURE);
		pPack->bContent[2] = temp;
		/*temp = GetDlgItemInt(IDC_ENV_TEMPERATURE);
		pPack->bContent[3] = temp;*/
 	}
}

void CAirConditionDlg::UpdataAirNum(LPVOID lParam)
{
	PRCU_ARG_GET_RES_PACK_0202 pPack = reinterpret_cast<PRCU_ARG_GET_RES_PACK_0202>(lParam);
	int count = 0,num;
	CString str,deviceNum;
	for (int i = 1; i < 150;i =i + 10)
	{
		if (1 == pPack->bContent[i])
		{
			count++;
			num = pPack->bContent[i - 1];
			deviceNum.Format("%d",num);
			m_CobAirNum.AddString(deviceNum);
		}
	}
	m_CobAirNum.SetCurSel(0);
}

void CAirConditionDlg::OnBnClickedBtnSet()
{
	// TODO: Add your control notification handler code here
	DWORD nBytes,nRevLength;
	DWORD IpAddress;
	PBYTE pBuf = NULL;
	DWORD dwRtua = 10550;
	WORD  wMstaAndSeq = 0x005E;
	PRCU_ARG_AIR_SET_REQ_PACK_021X pPack = NULL;

	nRevLength = 256;
	pBuf = new BYTE[nRevLength];
	memset(pBuf,0,nRevLength);
	PROOM_DETAIL_ENTRY m_pRoomEntry = lpRoomDetail;
	// TODO: Add your control notification handler code here
	pPack = new RCU_ARG_AIR_SET_REQ_PACK_021X;
	if((pPack == NULL) || (m_pRoomEntry == NULL))
	{
		delete pPack;
		delete[] pBuf;
		return;
	}
	int airNum = GetDlgItemInt(IDC_AIR_NUM);
	nBytes = SetAirConditionPacket(pPack,airNum);
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
	PRCU_ARG_SET_RES_UNIT pUnit = reinterpret_cast<PRCU_ARG_SET_RES_UNIT>(pBuf+16);
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

	delete pPack;
	delete[] pBuf;
}

void CAirConditionDlg::OnBnClickedBtnFlush()
{
	// TODO: Add your control notification handler code here
	initAirCondition();
}

void CAirConditionDlg::OnOK()
{

}