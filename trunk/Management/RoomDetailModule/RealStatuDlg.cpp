// RealStatuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailModule.h"
#include "RealStatuDlg.h"
#include <Winsock2.h>


// CRealStatuDlg dialog

IMPLEMENT_DYNAMIC(CRealStatuDlg, CDialog)

CRealStatuDlg::CRealStatuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRealStatuDlg::IDD, pParent)
{

}

CRealStatuDlg::~CRealStatuDlg()
{
}

void CRealStatuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_COM_EMERGENCY,m_ComEmergency);
	DDX_Control(pDX,IDC_COM_CARD_STATUS,m_ComCardStatus);
	DDX_Control(pDX,IDC_COM_MAGNETIC,m_ComMagnetism);
	DDX_Control(pDX,IDC_COM_SUPPLY,m_ComSupply);
	DDX_Control(pDX,IDC_COM_CLEAN,m_ComClean);
	DDX_Control(pDX,IDC_COM_WASH,m_ComWash);
	DDX_Control(pDX,IDC_COM_NODISTURB,m_ComNoDistruct);
	DDX_Control(pDX,IDC_COM_WAIT,m_ComWait);

	DDX_Control(pDX,IDC_COM_INFRARED,m_ComInfrared);
	DDX_Control(pDX,IDC_COM_SERVE,m_ComServce);
	DDX_Control(pDX,IDC_COM_MAGNETISM_BALCONY,m_ComMagnetismBalcony);
	DDX_Control(pDX,IDC_COM_BED,m_ComBed);
	DDX_Control(pDX,IDC_COM_SAFE,m_ComSafe);
	DDX_Control(pDX,IDC_COM_CHECKOUT,m_ComCheckOut);
	DDX_Control(pDX,IDC_COM_ACCOUNT,m_ComAccount);
	DDX_Control(pDX,IDC_COM_REPAIR,m_ComRepair);
}


BEGIN_MESSAGE_MAP(CRealStatuDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_GET, &CRealStatuDlg::OnBnClickedBtnGet)
END_MESSAGE_MAP()

BOOL CRealStatuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_ComEmergency.SetCurSel(0);
	m_ComCardStatus.SetCurSel(0);
	m_ComMagnetism.SetCurSel(0);
	m_ComSupply.SetCurSel(0);
	m_ComClean.SetCurSel(0);
	m_ComWash.SetCurSel(0);
	m_ComNoDistruct.SetCurSel(0);
	m_ComWait.SetCurSel(0);

	m_ComInfrared.SetCurSel(0);
	m_ComServce.SetCurSel(0);
	m_ComMagnetismBalcony.SetCurSel(0);
	m_ComBed.SetCurSel(0);
	m_ComSafe.SetCurSel(0);
	m_ComCheckOut.SetCurSel(0);
	m_ComAccount.SetCurSel(0);
	m_ComRepair.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CRealStatuDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

void CRealStatuDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CRealStatuDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}

void CRealStatuDlg::UpDataRoomInfo(PVOID lParam)
{
	PBUILDING_ENTRY  m_pEntryInfo = NULL;		//Â¥×ùÁ´±í
	PROMM_INFO_TRANSFER pRoomInfo = (PROMM_INFO_TRANSFER)lParam;
	lpRoomDetail = NULL;
	if (pRoomInfo == NULL)	{	return;	}
	lpRoomDetail = (PROOM_DETAIL_ENTRY)pRoomInfo->pRoomEntry;
	if (lpRoomDetail == NULL)	{	return;	}	
}

// CRealStatuDlg message handlers

void CRealStatuDlg::OnBnClickedBtnGet()
{
	// TODO: Add your control notification handler code here
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
	UpdataRoomStatus(pBuf);	

	delete pPack;
	delete[] pBuf;
}


void CRealStatuDlg::UpdataRoomStatus(LPVOID lParam)
{
	PRCU_ARG_GET_RES_PACK_0202 pPack = reinterpret_cast<PRCU_ARG_GET_RES_PACK_0202>(lParam);

	if (pPack->bContent[2] & 0x01)
	{
		m_ComEmergency.SetCurSel(1);
	}
	else
	{
		m_ComEmergency.SetCurSel(0);
	}

	if (pPack->bContent[2] & (0x01 << 1))
	{
		m_ComCardStatus.SetCurSel(1);
	}
	else
	{
		m_ComCardStatus.SetCurSel(0);
	}

	if (pPack->bContent[2] & (0x01 << 2))
	{
		m_ComMagnetism.SetCurSel(1);
	} 
	else
	{
		m_ComMagnetism.SetCurSel(0);
	}

	if (pPack->bContent[2] & (0x01 << 3))
	{
		m_ComSupply.SetCurSel(1);
	} 
	else
	{
		m_ComSupply.SetCurSel(0);
	}

	if (pPack->bContent[2] & (0x01 << 4))
	{
		m_ComClean.SetCurSel(1);
	} 
	else
	{
		m_ComClean.SetCurSel(0);
	}

	if (pPack->bContent[2] & (0x01 << 5))
	{
		m_ComWash.SetCurSel(1);
	} 
	else
	{
		m_ComWash.SetCurSel(0);
	}

	if (pPack->bContent[2] & (0x01 << 6))
	{
		m_ComNoDistruct.SetCurSel(1);
	} 
	else
	{
		m_ComNoDistruct.SetCurSel(0);
	}

	if (pPack->bContent[2] & (0x01 << 7))
	{
		m_ComWait.SetCurSel(1);
	} 
	else
	{
		m_ComWait.SetCurSel(0);
	}

	if (pPack->bContent[3] & 0x01)
	{
		m_ComInfrared.SetCurSel(1);
	} 
	else
	{
		m_ComInfrared.SetCurSel(0);
	}

	if (pPack->bContent[3] & (0x01 << 1))
	{
		m_ComServce.SetCurSel(1);
	} 
	else
	{
		m_ComServce.SetCurSel(0);
	}

	if (pPack->bContent[3] & (0x01 << 2))
	{
		m_ComMagnetismBalcony.SetCurSel(1);
	} 
	else
	{
		m_ComMagnetismBalcony.SetCurSel(0);
	}

	if (pPack->bContent[3] & (0x01 << 3))
	{
		m_ComBed.SetCurSel(1);
	} 
	else
	{
		m_ComBed.SetCurSel(0);
	}

	if (pPack->bContent[3] & (0x01 << 4))
	{
		m_ComSafe.SetCurSel(1);
	} 
	else
	{
		m_ComSafe.SetCurSel(0);
	}

	if (pPack->bContent[3] & (0x01 << 5))
	{
		m_ComCheckOut.SetCurSel(1);
	} 
	else
	{
		m_ComCheckOut.SetCurSel(0);
	}

	if (pPack->bContent[3] & (0x01 << 6))
	{
		m_ComAccount.SetCurSel(1);
	} 
	else
	{
		m_ComAccount.SetCurSel(0);
	}

	if (pPack->bContent[3] & (0x01 << 7))
	{
		m_ComRepair.SetCurSel(1);
	} 
	else
	{
		m_ComRepair.SetCurSel(0);
	}
}

void CRealStatuDlg::OnOK()
{

}