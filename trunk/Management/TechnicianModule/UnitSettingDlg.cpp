// UnitSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "technicianmodule.h"
#include "UnitSettingDlg.h"
#include "..\\CommSource\\Project\\DataTransferLay.h"
#include "..\\CommSource\\Project\\TransDataType.h"
#include <Winsock2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnitSettingDlg dialog


CUnitSettingDlg::CUnitSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitSettingDlg::IDD, pParent),lpRoom(NULL)
{
	//{{AFX_DATA_INIT(CUnitSettingDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_TargetIpAddress = 0xC0A80164;
	m_PortNumberValue = 10000;
	m_Rcua = _T("50050001");
	//}}AFX_DATA_INIT
	//InitSocket();
}

CUnitSettingDlg::~CUnitSettingDlg()
{

	//UnInitSocket();
}


void CUnitSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnitSettingDlg)
	DDX_Control(pDX, IDC_MODULE_LIST, m_ModuleList);
	DDX_Text(pDX, IDC_EDIT_PORTNUM, m_PortNumberValue);
	DDX_Text(pDX, IDC_EDIT_RCUA, m_Rcua);
	DDX_IPAddress(pDX, IDC_IPADDRESS, m_TargetIpAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUnitSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CUnitSettingDlg)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MODIFY, OnBtnModify)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_BN_CLICKED(IDC_BTN_ADD_ALL, OnBtnAddAll)
	ON_BN_CLICKED(IDC_BTN_DELETE_ALL, OnBtnDeleteAll)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_ADD_STAGE, &CUnitSettingDlg::OnBnClickedBtnAddStage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnitSettingDlg message handlers

BOOL CUnitSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
//配置模块的列表显示
	CRect rt;
	::GetClientRect(GetDlgItem(IDC_MODULE_LIST)->GetSafeHwnd(),&rt);
	/////////////////////////////////////////////////////////////////////////////
	m_ModuleList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP);
	m_ModuleList.InsertColumn(0,"",LVCFMT_LEFT,0);
	m_ModuleList.InsertColumn(1,"编号",LVCFMT_CENTER,60);
	m_ModuleList.InsertColumn(2,"地址",LVCFMT_CENTER,60);
	m_ModuleList.InsertColumn(3,"名称",LVCFMT_CENTER,rt.Width()-120);
	//=====================================================================
	//SetDlgItemInt(IDC_EDIT_PORTNUM,10000);
	//SetDlgItemText(IDC_IPADDRESS,"192.168.1.22");
	//SetDlgItemText(IDC_EDIT_RCUA,"50050001");
	InitAllItem();



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CUnitSettingDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		//屏掉回车和退出键
		if(pMsg->wParam == VK_RETURN  || pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void CUnitSettingDlg::InitAllItem()
{
	int Index = 0,nEntry=0;
	CString str;
	PCHAR pName;
	PMODULE_ENTRY pModuleUnit = m_DataManage.pRoomUnit->mModuleEntry;
	for (Index=0;Index<MAX_MODULE_NUMBER;Index++,pModuleUnit++)
	{
		if (pModuleUnit->bEntry == 0){	continue;	}
		m_ModuleList.InsertItem(nEntry,NULL);

		pName = m_DataManage.GetSubModuleName(Index);
		str.Format("%d",pModuleUnit->bEntry);
		m_ModuleList.SetItemText(nEntry,1,str);
		str.Format("%d",pModuleUnit->dwModuleAddress);
		m_ModuleList.SetItemText(nEntry,2,str);
		m_ModuleList.SetItemText(nEntry,3,pName);

		m_ModuleList.SetItemData(nEntry,Index);
		nEntry++;
	}
}

void CUnitSettingDlg::OnBtnAdd() 
{
	//// TODO: Add your control notification handler code here
	//POSITION pos = m_ModuleList.GetFirstSelectedItemPosition();
	//int Index = m_ModuleList.GetNextSelectedItem(pos);
	//BYTE pSentBuf[512];
	//ZeroMemory(pSentBuf,512);
	////=========================================================
	////InitSocket();
	//SendDataWithResponse(pSentBuf,512);
	////UnInitSocket();
	////=========================================================
	//SetListFocus(Index);
}

void CUnitSettingDlg::OnBtnModify() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_ModuleList.GetFirstSelectedItemPosition();
	int Index = m_ModuleList.GetNextSelectedItem(pos);
	//=========================================================
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//=========================================================	
	SetListFocus(Index);	
}

void CUnitSettingDlg::OnBtnDelete() 
{
	PBYTE pSendBuf = NULL;
	DWORD dwSendLen = 0;

	PBYTE pRecvBuf = NULL;	
	DWORD dwRecvLen = 0;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	pSendBuf = new BYTE[8192];
	if (pSendBuf == NULL)	{	MessageBox("申请发送缓冲区失败");	delete[] pSendBuf;		return;		}
	ZeroMemory(pSendBuf,8192);

	pRecvBuf = new BYTE[256];
	if (pRecvBuf == NULL)	{	MessageBox("申请接收缓冲区失败");	delete[] pRecvBuf;		return;		}
	ZeroMemory(pRecvBuf,256);
//=======================================================================================================================





















//=====================================================================================================================
	if (pSendBuf != NULL)	{	delete[] pSendBuf;		pSendBuf = NULL;	}
	if (pRecvBuf != NULL)	{	delete[] pRecvBuf;		pRecvBuf = NULL;	}
}

void CUnitSettingDlg::OnBtnAddAll() 
{
	PBYTE pSendBuf = NULL;
	DWORD dwSendLen = 0;

	PBYTE pRecvBuf = NULL;	
	DWORD dwRecvLen = 128;
	CString str;
// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD	dwRtua = GetRtuaValue(m_Rcua);
	WORD	Msta = 0x5E00;
	
	pSendBuf = new BYTE[8192];
	if (pSendBuf == NULL)	{	MessageBox("申请发送缓冲区失败");	delete[] pSendBuf;		return;		}
	ZeroMemory(pSendBuf,8192);

	pRecvBuf = new BYTE[256];
	if (pRecvBuf == NULL)	{	MessageBox("申请接收缓冲区失败");	delete[] pRecvBuf;		return;		}
	ZeroMemory(pRecvBuf,256);
//=====================================================================================================================
//先配置所有的配置模式的数据
	dwSendLen = m_DataManage.GetTotalModuleCfgData(NULL,pSendBuf);
	PDATA_TRANS_PRE pPreBuf = reinterpret_cast<PDATA_TRANS_PRE>(pSendBuf);
	//CString str;
	//DWORD	IpAddress;			//Ip地址
	//USHORT	nPort = GetDlgItemInt(IDC_EDIT_PORTNUM);
	//GetDlgItemText(IDC_IPADDRESS,str);
	//IpAddress = inet_addr(str);
	//IpAddress = ToLittleEndian(IpAddress);
	INPUT_DATA Input;
	//1.=====设置临时值=======================================
	Input.bCode = 0x08;
	Input.wFloor = (WORD)(dwRtua>>16)&0x0000FFFF;
	Input.wRoom = (WORD)dwRtua&0x0000FFFF;
	Input.bMSTA = (Msta>>8)&0x00FF;
	Input.bSEQ = Msta&0x00FF;
	Input.bOPType = 0x00;
	Input.bFuncType= 0x01;
	Input.bTranParam =4;
	FillPreBuffer(&Input,pPreBuf);
	pPreBuf->wTransLength = dwSendLen-sizeof(DATA_TRANS_PRE)+6;
	//FillPreBuffer(pPreBuf,0x08,(WORD)(dwRtua>>16)&0x0000FFFF),(WORD)(dwRtua&0x0000FFFF),(Msta>>8)&0x00FF,Msta&0x00FF);
	PDATA_TRANS_POST pPostBuf = reinterpret_cast<PDATA_TRANS_POST>(pSendBuf+dwSendLen);
	dwSendLen += sizeof(DATA_TRANS_POST);
	FillPostBuffer(pSendBuf,dwSendLen);
//======================================================================================================================
	dwRecvLen = SendDataWithResponse(pSendBuf,dwSendLen,\
		pRecvBuf,dwRecvLen,\
		m_TargetIpAddress,(USHORT)m_PortNumberValue);
	
	RecordBuffer("SetAll_Request.txt",pSendBuf,dwSendLen);
	RecordBuffer("SetAll_Response.txt",pRecvBuf,dwRecvLen);
	//4.返回状态
	if(pRecvBuf[dwRecvLen-3] == 0)		{	str = _T("配置RCU成功");	}
	else	{	str.Format("配置RCU失败 [%s]",ErrString[*(pRecvBuf+dwRecvLen-3)]);	}
	MessageBox(str);


	if (pSendBuf != NULL)	{	delete[] pSendBuf;		pSendBuf = NULL;	}
	if (pRecvBuf != NULL)	{	delete[] pRecvBuf;		pRecvBuf = NULL;	}
}

void CUnitSettingDlg::SetListFocus(int nSelect,BOOL Flag)
{
	DWORD dwStytle = 0;
	::SetFocus(((CListCtrl *)GetDlgItem(IDC_MODULE_LIST))->GetSafeHwnd());

	if(Flag == TRUE) {	dwStytle = LVIS_SELECTED|LVIS_FOCUSED;	}
	m_ModuleList.SetItemState(nSelect,dwStytle,LVIS_SELECTED | LVIS_FOCUSED);
}



int CUnitSettingDlg::GetConfigData(LPVOID lParam,PBYTE pBuf,int NodeNum)
{
	int nBytes = 0;
//	PMODULE_CFG_INFO pModule = (PMODULE_CFG_INFO)lParam;
//	if((pModule == NULL) && (pModule->bModuleValid == FALSE))
//		return nBytes;
////======================================================
//	int Index;
//	PMODULE_LUN_INFO pLun = NULL;
//	//B[0]		设备节点编号[1]
//	pBuf[nBytes++] = NodeNum & 0x00FF;
//	//B[1-6]	设备节点地址[6]
//	pBuf[nBytes++] = (BYTE)(pModule->ModuleAddress & 0x000000FF);
//	pBuf[nBytes++] = (BYTE)((pModule->ModuleAddress >> 8) & 0x000000FF);
//	pBuf[nBytes++] = (BYTE)((pModule->ModuleAddress >> 16) & 0x000000FF);
//	pBuf[nBytes++] = (BYTE)((pModule->ModuleAddress >> 24) & 0x000000FF);
//	pBuf[nBytes++] = 0x00;
//	pBuf[nBytes++] = 0x00;
//	//B[7]		功能类型[1]
//	pBuf[nBytes++] = 0x001;
//	//B[8]		设备类型[1]
//	pBuf[nBytes++] = pModule->ModuleName;
//	//B[9]		通讯参数[1]
//	//pBuf[nBytes++] = 0x01;		//1200
//	//pBuf[nBytes++] = 0x02;		//2400
//	//pBuf[nBytes++] = 0x03;		//4800
//	pBuf[nBytes++] = 0x04;			//9600
//	//pBuf[nBytes++] = 0x05;		//19200
//	//关联设备数N
//
//
//
//
//
//
//
//
//
//
//
//	for(Index=0;Index<MAX_SUB_LUN_NUM;Index++)		//遍历子路
//	{
//		pLun = (PMODULE_LUN_INFO)pModule->mLunInfo;
//	
//	
//	
//	
//	}
//






	return nBytes;
}

void CUnitSettingDlg::OnBtnDeleteAll() 
{
	PBYTE pSendBuf = NULL;
	DWORD dwSendLen = 0;

	PBYTE pRecvBuf = NULL;	
	DWORD dwRecvLen = 64;

	INPUT_DATA mInputArg;
	CString str;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	pSendBuf = new BYTE[512];
	if (pSendBuf == NULL)	{	MessageBox("申请发送缓冲区失败");	delete[] pSendBuf;		return;		}
	ZeroMemory(pSendBuf,512);

	pRecvBuf = new BYTE[256];
	if (pRecvBuf == NULL)	{	MessageBox("申请接收缓冲区失败");	delete[] pRecvBuf;		return;		}
	ZeroMemory(pRecvBuf,256);

	ZeroMemory(&mInputArg,sizeof(INPUT_DATA));
//=======================================================================================================================
//填充发送数据部分
	WORD	Msta = 0x5E00;
	DWORD	dwRtua = GetRtuaValue(m_Rcua);
//1.=====设置临时值=======================================								// 批量操作；
	mInputArg.bCode = 0x08;
	mInputArg.wFloor = (WORD)(dwRtua>>16)&0x0000FFFF;
	mInputArg.wRoom = (WORD)dwRtua&0x0000FFFF;
	mInputArg.bMSTA = (Msta>>8)&0x00FF;
	mInputArg.bSEQ = Msta&0x00FF;
	mInputArg.bOPType = 0x00;
	mInputArg.bFuncType= 0x02;
	mInputArg.bTranParam =4;

//设置清空列表框的内容
	dwSendLen = FillClearAllCfgPack(&mInputArg,pSendBuf,FALSE);
//往目标IP发送数据
	dwRecvLen = SendDataWithResponse(pSendBuf,dwSendLen,\
		pRecvBuf,dwRecvLen,\
		m_TargetIpAddress,(USHORT)m_PortNumberValue);


	RecordBuffer("DeleteAll_Request.txt",pSendBuf,dwSendLen);
	RecordBuffer("DeleteAll_Response.txt",pRecvBuf,dwRecvLen);
	//4.返回状态
	if(pRecvBuf[dwRecvLen-3] == 0)		{	str = _T("清空RCU成功");	}
	else	{	str.Format("清除RCU失败 [%s]",ErrString[*(pRecvBuf+dwRecvLen-3)]);	}
	MessageBox(str);
	//=====================================================================================================================
	if (pSendBuf != NULL)	{	delete[] pSendBuf;		pSendBuf = NULL;	}
	if (pRecvBuf != NULL)	{	delete[] pRecvBuf;		pRecvBuf = NULL;	}
}

DWORD CUnitSettingDlg::GetRtuaValue(CString str)
{
	DWORD dwRtua = 0;
	//CString str;

	PBYTE pbRtua = reinterpret_cast<PBYTE>(&dwRtua);
	//GetDlgItemText(IDC_EDIT_RCUA,str);
//=============================================================
	int Index = 0;
	char CurCharect;
	//FILE *fp;
	//fp = fopen("8895.txt","wt");
	//fprintf(fp,"待转的字符串：%s\n",str);
	int strNum = str.GetLength();
	if(strNum>8)
		strNum=8;
	//int Temp = strNum-1;
	Index = strNum-1;
	while(Index>=0){
		CurCharect = str.GetAt(Index);
		//======================================================
		if((CurCharect >= '0') && (CurCharect <= '9')){ 
			CurCharect = CurCharect - '0';}
		else if((CurCharect >= 'a') && (CurCharect <= 'f')){ 
			CurCharect = CurCharect - 'a' + 10;}
		else if((CurCharect >= 'A') && (CurCharect <= 'F')){ 
			CurCharect = CurCharect - 'A' + 10;}
		else{
			CurCharect = 0;
		}
		//======================================================
		*(pbRtua+Index/2) |= CurCharect<<((1-Index%2)*4);
		Index--;
	}
	CurCharect = *(pbRtua+3);
	*(pbRtua+3) = *(pbRtua+2);
	*(pbRtua+2) = CurCharect;
	return dwRtua;
}



void CUnitSettingDlg::OnBnClickedBtnAddStage()
{
	// TODO: Add your control notification handler code here
	PBYTE pSendBuf = NULL;
	DWORD dwSendLen = 0;

	PBYTE pRecvBuf = NULL;	
	DWORD dwRecvLen = 64;
	INPUT_DATA mInputArg;
	CString str;
	DWORD pLengthValue = 0;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	pSendBuf = new BYTE[512];
	if (pSendBuf == NULL)	{	MessageBox("申请发送缓冲区失败");	delete[] pSendBuf;		return;		}
	ZeroMemory(pSendBuf,512);

	pRecvBuf = new BYTE[256];
	if (pRecvBuf == NULL)	{	MessageBox("申请接收缓冲区失败");	delete[] pRecvBuf;		return;		}
	ZeroMemory(pRecvBuf,256);

	ZeroMemory(&mInputArg,sizeof(INPUT_DATA));
	//=======================================================================================================================
	//填充发送数据部分
	WORD	Msta = 0x5E00;
	DWORD	dwRtua = GetRtuaValue(m_Rcua);
	//1.=====设置临时值=======================================								// 批量操作；
	mInputArg.bCode = 0x08;
	mInputArg.wFloor = (WORD)(dwRtua>>16)&0x0000FFFF;
	mInputArg.wRoom = (WORD)dwRtua&0x0000FFFF;
	mInputArg.bMSTA = (Msta>>8)&0x00FF;
	mInputArg.bSEQ = Msta&0x00FF;
	mInputArg.bOPType = 0x00;
	mInputArg.bFuncType= 0x02;
	mInputArg.bTranParam =4;

	//设置清空列表框的内容
	// 1. 填充发送Buffer的前缀	
	PDATA_TRANS_PRE mPreFrame = reinterpret_cast<PDATA_TRANS_PRE>(pSendBuf);
	FillPreBuffer(&mInputArg, mPreFrame);
	dwSendLen = sizeof(DATA_TRANS_PRE);
	

	pLengthValue = m_DataManage.GetStageDataContext(NULL,(pSendBuf+dwSendLen));
	dwSendLen += pLengthValue;
	mPreFrame->wTransLength = pLengthValue;


	dwSendLen += sizeof(DATA_TRANS_POST);
	//3.填充尾
	mPreFrame->wTransLength = dwSendLen -13;
	FillPostBuffer(pSendBuf, dwSendLen);
	//往目标IP发送数据
	dwRecvLen = SendDataWithResponse(pSendBuf,dwSendLen,\
		pRecvBuf,dwRecvLen,\
		m_TargetIpAddress,(USHORT)m_PortNumberValue);


	RecordBuffer("SetStage_Request.txt",pSendBuf,dwSendLen);
	RecordBuffer("SetStage_Response.txt",pRecvBuf,dwRecvLen);
	//4.返回状态
	if(pRecvBuf[dwRecvLen-3] == 0)		{	str = _T("设置场景成功");	}
	else	{	str.Format("设置场景失败 [%s]",ErrString[*(pRecvBuf+dwRecvLen-3)]);	}
	MessageBox(str);
	//=====================================================================================================================
	if (pSendBuf != NULL)	{	delete[] pSendBuf;		pSendBuf = NULL;	}
	if (pRecvBuf != NULL)	{	delete[] pRecvBuf;		pRecvBuf = NULL;	}


}
