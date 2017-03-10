#include "stdafx.h"
#include "DataManage.h"
#include "..\\CommSource\\Project\\TransDataType.h"
#include "..\\CommSource\\Project\\DataTransferLay.h"
//=====================================================================================


CDataManage::CDataManage(void)
{
	pRoomUnit = NULL;
	LoadSpecialLinkList();
}

CDataManage::~CDataManage(void)
{
	LoadSpecialLinkList(FALSE);
	pModuleLinkList.RemoveAll();
}


//设置房型结构
void CDataManage::SetRoomContainer(LPVOID lParam)
{
	pRoomUnit = reinterpret_cast<PROOM>(lParam);

}



PMODULE_ENTRY CDataManage::SearchModuleExit(DWORD dwAddress)
{
	int Index = 0;
	BOOL bFindEmpty = FALSE;
	if (pRoomUnit == NULL)	{	return NULL;	}
	PMODULE_ENTRY pModuleArray	= reinterpret_cast<PMODULE_ENTRY>(pRoomUnit->mModuleEntry);	
	while (Index < MAX_MODULE_NUMBER)
	{	
		Index++;
		if ((pModuleArray->dwModuleAddress == dwAddress) && (pModuleArray->bEntry))	{	
			bFindEmpty = TRUE;
			break;	
		}
		pModuleArray++;
	}
	if (bFindEmpty == FALSE)	{	pModuleArray = NULL;	}
	return pModuleArray;
}




int	CDataManage::LoadSpecialLinkList(BOOL Flag)
{
	PCHAR pName = NULL;
	int Index = 0;
	for (Index =0;Index < pSepeciallLinkList.GetSize();Index++)
	{
		pName = (PCHAR)pSepeciallLinkList.GetAt(Index);
		if (pName != NULL)	{	delete pName;	}
	}
	
	if (pSepeciallLinkList.GetSize())	{	pSepeciallLinkList.RemoveAll();	}
	if (Flag == FALSE)	{	return 0;	}
//=============================================================================
	CStdioFile m_File;
	CString str;
	int nFind;
	if(!m_File.Open("SpecilFunDefine.dat",CFile::modeRead,NULL))
	{		return 0;	}
	//=================================================================
	while(1)
	{
		if(m_File.ReadString(str) == NULL)
			break;
		nFind = str.Find(',',0);
		if(nFind >0)
		{
			pName = new char[nFind+1];
			ZeroMemory(pName,nFind+1);

			strcpy(pName,str.Left(nFind));
			pSepeciallLinkList.Add(pName);
		}
	}
	m_File.Close();

	return pSepeciallLinkList.GetSize();
}



PMODULE_ENTRY CDataManage::InsertModule(int nItem,int nSubItem,int nDeviceType,DWORD dwAddress)
{
//查找模块是否存在
	if (SearchModuleExit(dwAddress) != NULL)	{	return NULL;	}
	int Index = 0;
	BOOL bFindEmpty = FALSE;
	if (pRoomUnit == NULL)	{	return NULL;	}
	PMODULE_ENTRY pModuleArray	= reinterpret_cast<PMODULE_ENTRY>(pRoomUnit->mModuleEntry);	
	while (Index < MAX_MODULE_NUMBER)
	{	
		Index++;
		if (pModuleArray->bEntry == 0)	{	
			bFindEmpty = TRUE;
			break;	
		}
		pModuleArray++;
	}
	if (bFindEmpty == FALSE)	{	return NULL;	}
//=======================================================================================================================
	ZeroMemory(pModuleArray,sizeof(MODULE_ENTRY));

	pModuleArray->bEntry = Index;
	pModuleArray->bModuleType = nItem;
	pModuleArray->bModuleName = nSubItem;
	pModuleArray->dwModuleAddress = dwAddress;
	pModuleArray->bDeviceType = nDeviceType;
//=======================================================================================================================
//模块的内容不能全为空








	return pModuleArray;
}

void CDataManage::DeleteModule(int Entry)
{
	PMODULE_ENTRY pModuleArray	= reinterpret_cast<PMODULE_ENTRY>(pRoomUnit->mModuleEntry);	
	for (int Index = 0;Index < MAX_MODULE_NUMBER;Index++)
	{
		if (Entry == pModuleArray->bEntry)	
		{	
			break;	
		}
		pModuleArray++;
	}
	
	pModuleArray->bEntry = 0;
	pModuleArray->bModuleType = 0;
	pModuleArray->bModuleName = 0;
	pModuleArray->dwModuleAddress = 0;
	pModuleArray->bDeviceType = 0;
}

PCHAR CDataManage::GetModuleKeyEntry(int nModule,int nSubKey)
{
	static char pContext[MAX_PATH];
	ZeroMemory(pContext,MAX_PATH);
//===============================================================================
	if (pRoomUnit == NULL)		{	return NULL;	}
	PMODULE_KEY_UNIT	pModuleKeyUnit = &(pRoomUnit->mModuleEntry[nModule].mKeyUnit[nSubKey]);


	if (pModuleKeyUnit->bKeyAttribute == ATTRIBUTE_INPUT)	{	sprintf(pContext,"[%s]子路%d",sKeyAttribute[pModuleKeyUnit->bKeyAttribute],pModuleKeyUnit->bEntry);	}
	else if (pModuleKeyUnit->bKeyAttribute == ATTRIBUTE_OUTPUT)	{	sprintf(pContext,"[%s]%s",sKeyAttribute[pModuleKeyUnit->bKeyAttribute],pModuleKeyUnit->mContent.pName);	}
	//else { sprintf(pContext,"[%s]%s未配置",sKeyAttribute[pModuleKeyUnit->bKeyAttribute],pModuleKeyUnit->bEntry);		}
	else {	return NULL;	}


	return pContext;
}


PCHAR CDataManage::GetSpecialFunName(int nValue)
{
	if (nValue < pSepeciallLinkList.GetSize())	{	return (PCHAR)pSepeciallLinkList.GetAt(nValue);	}
	else {	return NULL;	}
}



PCHAR CDataManage::GetSubModuleName(int nModule)
{
	PCHAR pSubName = NULL;
	if (pRoomUnit == NULL)	{	return NULL;	}
//=======================================================================
	if (pRoomUnit->mModuleEntry[nModule].bEntry == 0)	{	return NULL;	}

	int iEntry = pRoomUnit->mModuleEntry[nModule].bModuleType;
	int iSunEntry = pRoomUnit->mModuleEntry[nModule].bModuleName;

	if (iEntry < pModuleLinkList.GetCount()){
		CWnd *pWnd = (CWnd *)pModuleLinkList.GetAt(iEntry);
		if (pWnd == NULL)	{	return NULL;	}
		pWnd->SendMessage(WM_GET_SUB_MODULE_NAME,(WPARAM)&pSubName,iSunEntry);
	}
	return pSubName;
}
//获取配置模块的内容
//===============================================================================================
//得到由iEntry配置好的信息的配置数据
DWORD CDataManage::GetAppointedModuleCfgData(PBYTE &pBuf,int iEntry)
{
	DWORD dwTotalBytes = 0;
//===========================================================================================================
	if (pBuf == NULL)		{	pBuf = new BYTE[8192];	}
	if (pBuf == NULL)		{	return 0;	}			
	ZeroMemory(pBuf,8192);




















	return dwTotalBytes;
}

//获取所有模块的内容
//===============================================================================================
//得到由配置好的信息的全配置数据
DWORD CDataManage::GetTotalModuleCfgData(LPVOID lParam,PBYTE &pBuf)						
{
	DWORD dwTotalBytes = 0;
	PBYTE pBaseBuf = NULL;
	PBYTE pDeviceNum;		//设备总数
//===============================================================
	if (pBuf == NULL)		{	pBuf = new BYTE[8192];	}
	if (pBuf == NULL) {	return 0;	}			
	ZeroMemory(pBuf,8192);
//*********************************************************************
//895D的内容
	pBaseBuf = pBuf + sizeof(DATA_TRANS_PRE);
	*(pBaseBuf++) = 0x5D;			//标示编码
	*(pBaseBuf++) = 0x89;			
	*(pBaseBuf++) = 0x00;			//表示新增
	pDeviceNum = pBaseBuf++;		//设备总数(如果是删除就填0x00)
//======================================================================
	int nModule,nKey,nReleation;
	for (nModule = 0;nModule < MAX_MODULE_NUMBER;nModule++)
	{
		//模块层
		PMODULE_ENTRY pModule = (PMODULE_ENTRY)&(pRoomUnit->mModuleEntry[nModule]);
		if (pModule->bEntry == 0)			{	continue;	}
		if (pModule->bModuleType > 5)		{	continue;	}
		*pDeviceNum += 1;

	//*(pBaseBuf++) = 0x55;
		*(pBaseBuf++) = pModule->bEntry;			//设备节点编号
		DWORD dwAddress = DWORD2_BCD(pModule->dwModuleAddress);
		memcpy(pBaseBuf,(PBYTE)(DWORD *)(&dwAddress),sizeof(DWORD));
		pBaseBuf += 6;							    //设备地址
		*(pBaseBuf++) = 0x00;						//功能类型(无用)
		//*(pBaseBuf++) = pModule->bModuleType+1;		//设备类型
		*(pBaseBuf++) = pModule->bDeviceType;		//设备类型
		*(pBaseBuf++) = 0x04;						//通讯参数(9600)
		PBYTE pReleation = pBaseBuf++;				//关联设备数N
	//*(pBaseBuf++) = 0x00AA;

		for (nKey=0;nKey<MAX_MODULE_KEY_NUMBER;nKey++)
		{
			PMODULE_KEY_UNIT pKey = (PMODULE_KEY_UNIT)&(pModule->mKeyUnit[nKey]);
			if (pKey->bEntry == 0)	{	continue;	}

			if (pKey->bKeyAttribute == ATTRIBUTE_OUTPUT)	{	continue;	}
			for (nReleation = 0;nReleation < MAX_CTRL_MODULE_NUMBER;nReleation++)
			{
				PCONTROL_DEVICE_UNIT pCtrlDevice = (PCONTROL_DEVICE_UNIT)&(pKey->mContent.mCtrlDeviceList.mCtrlDev[nReleation]);
				if (pCtrlDevice->bModuleEntry == 0)	{	continue;	}
				//*(pBaseBuf++) = 0x55;
				*pReleation += 1;
				*(pBaseBuf++) = pKey->bEntry;
				*(pBaseBuf++) = pCtrlDevice->bSpecialFundef;
				*(pBaseBuf++) = pCtrlDevice->bModuleEntry;
				*((DWORD *)pBaseBuf) = GetDataPos(pCtrlDevice->bSubModuleItem-1);
				pBaseBuf += 4;
				//*(pBaseBuf++) = 0xAA;
			}
//*(pBaseBuf++) = 0xAA;
		}
	}
	//dwTotalBytes = pBaseBuf - pBuf-2;
	dwTotalBytes = pBaseBuf - pBuf;
	return dwTotalBytes;
}


DWORD CDataManage::GetStageDataContext(LPVOID lParam,PBYTE pBuf)
{
	DWORD dwTotalBytes = 0;
	int i,j,k;
	PBYTE pLengthValue;
//=====================================================================
//*********************************************************************
	
	//2.填充场景数据
	for (k=0;k<MAX_MODULE_NUMBER;k++)
	{

		//PMODULE_ENTRY pModule = (PMODULE_ENTRY)&(pRoomUnit->mModuleEntry[nModule]);
		//if (pModule->bEntry == 0)			{	continue;	}
		//if (pModule->bModuleType > 5)		{	continue;	}
		//*pDeviceNum += 1;
		if (pRoomUnit->mModuleEntry[k].bModuleType != 0x06){
			continue;
		}
	
		/*if (pRoomUnit->mModuleEntry[k].bModuleName != 0x02){
			pBuf[dwTotalBytes++] = 0x11;
			pBuf[dwTotalBytes++] = 0x01;
		}
		else{
			pBuf[dwTotalBytes++] = 0x40;
			pBuf[dwTotalBytes++] = 0x01;
		}*/
		switch (pRoomUnit->mModuleEntry[k].bModuleName)
		{
		case SCENEONE:
			pBuf[dwTotalBytes++] = 0x11;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		case SCENETWO:
			pBuf[dwTotalBytes++] = 0x12;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		case SCENETHREE:
			pBuf[dwTotalBytes++] = 0x13;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		case SCENEFOUR:
			pBuf[dwTotalBytes++] = 0x14;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		case SCENEFIVE:
			pBuf[dwTotalBytes++] = 0x15;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		case SCENESIX:
			pBuf[dwTotalBytes++] = 0x16;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		case SCENESEVEN:
			pBuf[dwTotalBytes++] = 0x17;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		case SCENECARDIN:
			pBuf[dwTotalBytes++] = 0x42;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		case SCENECARDOUT:
			pBuf[dwTotalBytes++] = 0x43;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		case SCENEINFRAREDON:
			pBuf[dwTotalBytes++] = 0x45;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		case SCENEINFRAREDOFF:
			pBuf[dwTotalBytes++] = 0x46;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		case SCENESUPPLY:
			pBuf[dwTotalBytes++] = 0x40;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		case SCENEDOOR:
			pBuf[dwTotalBytes++] = 0x44;
			pBuf[dwTotalBytes++] = 0x01;
			break;
		default:
			break;
		}
		pLengthValue = pBuf+dwTotalBytes;
		dwTotalBytes++;

		for (i=0;i<MAX_MODULE_KEY_NUMBER;i++)
		{
			for (j=0;j<MAX_CTRL_MODULE_NUMBER;j++)
			{
				if ((pRoomUnit->mModuleEntry[k].mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].bModuleEntry != 0) && (\
					pRoomUnit->mModuleEntry[k].mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].bSubModuleItem != 0))
				{
					(*pLengthValue)++;
					pBuf[dwTotalBytes++] = pRoomUnit->mModuleEntry[k].mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].bModuleEntry;
					pBuf[dwTotalBytes++] = pRoomUnit->mModuleEntry[k].mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].bSubModuleItem;
					pBuf[dwTotalBytes++] = pRoomUnit->mModuleEntry[k].mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].bSpecialFundef;
					
					pBuf[dwTotalBytes++] = (BYTE)(pRoomUnit->mModuleEntry[k].mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].dwArgument) & 0x000000FF;;
					pBuf[dwTotalBytes++] = (BYTE)((pRoomUnit->mModuleEntry[k].mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].dwArgument)>>8) & 0x000000FF;
					pBuf[dwTotalBytes++] = (BYTE)((pRoomUnit->mModuleEntry[k].mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].dwArgument)>>16) & 0x000000FF;
					pBuf[dwTotalBytes++] = (BYTE)((pRoomUnit->mModuleEntry[k].mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].dwArgument)>>24)  & 0x000000FF;
				}
				
				
				
				
				
				
				
				
				
				
				
	/*			
				
				
				
				if ((p->mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].bModuleEntry == pCtrlUnit->bModuleEntry) && \
					(m_pModule->mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].bSubModuleItem == pCtrlUnit->bSubModuleItem))
				{
					pDeviceUnit = &(m_pModule->mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j]);
					break;
				}
			}
			if (pDeviceUnit != NULL){	break;	}*/
			}
		}
	}















	return dwTotalBytes;
}



DWORD CDataManage::GetDataPos(BYTE bValue)
{
	DWORD dwResult = 0;
	dwResult = 0x00000001 << (bValue%32);
	return dwResult;
}
