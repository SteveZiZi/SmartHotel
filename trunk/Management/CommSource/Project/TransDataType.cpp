#include "stdafx.h"
//#include "..\\..\\TechnicianModule\\TechnicianDataType.h"
#include "TransDataType.h"
///////////////////////////////////////////////////////////////////////////////////////////
//==============================================================
//����RCU���ò�����������ݿ�ת��
//**************************************************
//����1���������͵�Buffer����
//����2��ָ�����
//����3������Buffer
//����4�����ͳ���
//**************************************************
DWORD SetRCUargPacket(LPVOID lParam)
{
	PRCU_ARG_SET_REQ_PACK pTemp = (PRCU_ARG_SET_REQ_PACK)lParam;
	if(pTemp == NULL)
		return 0;
//======================================================
	memset(pTemp,0,sizeof(RCU_ARG_SET_REQ_PACK));
//֡ͷ
	pTemp->sPreFrame.bStartFrame = 0x68;
	pTemp->sPreFrame.dwRtua = 0x00000000;
	pTemp->sPreFrame.wMstaAndSeq = 0x0000;
	pTemp->sPreFrame.bFrameFlag = 0x68;
	pTemp->sPreFrame.bCtrlCode = 0x08;
	pTemp->sPreFrame.wTransLength = 0x0018;
	pTemp->sPreFrame.wTestNodeIndex = 0x0000;
	pTemp->sPreFrame.uLevel = 0x11;
	pTemp->sPreFrame.uPasswords = 0x111111;

	//֡��
	pTemp->uEntryA = 0x0101;
	pTemp->uEntryB = 0x0102;
	pTemp->uEntryC = 0x0103;
	/*pTemp->uEntryD = 0x0104;
	pTemp->uEntryE = 0x0105;*/
	pTemp->uEntryF = 0x0108;
	pTemp->uEntryG = 0x0109;


//֡β
	pTemp->sPostFrame.bEndFrame = 0x16;
	return sizeof(RCU_ARG_SET_REQ_PACK);
}


DWORD GetRCUargPacket(LPVOID lParam)
{
	PRCU_ARG_GET_REQ_PACK pTemp = (PRCU_ARG_GET_REQ_PACK)lParam;
	if(pTemp == NULL)
		return 0;
//======================================================
	memset(pTemp,0,sizeof(RCU_ARG_GET_REQ_PACK));
//֡ͷ
	pTemp->bStartFrame = 0x68;
	pTemp->dwRtua = 0x00000000;
	pTemp->wMstaAndSeq = 0x0000;
	pTemp->bFrameFlag = 0x68;
	pTemp->bCtrlCode = 0x01;
	pTemp->wTransLength = 0x0012;
	pTemp->lwTnm = 0x01;

	//֡��
	pTemp->uEntryA = 0x0101;
	pTemp->uEntryB = 0x0102;
	pTemp->uEntryC = 0x0103;
	/*pTemp->uEntryD = 0x0104;
	pTemp->uEntryE = 0x0105;*/
	pTemp->uEntryF = 0x0108;
	pTemp->uEntryG = 0x0109;


//֡β
	pTemp->sPostFrame.bEndFrame = 0x16;
	return sizeof(RCU_ARG_GET_REQ_PACK);
}

//��ȡ0202��Լ�ĸ����豸״̬
DWORD GetRCUargPacket0202(LPVOID lParam)
{
	PRCU_ARG_GET_REQ_PACK_0202 pTemp = (PRCU_ARG_GET_REQ_PACK_0202)lParam;
	if(pTemp == NULL)
		return 0;
//======================================================
	memset(pTemp,0,sizeof(RCU_ARG_GET_REQ_PACK_0202));
//֡ͷ
	pTemp->bStartFrame = 0x68;
	pTemp->dwRtua = 0x00000000;
	pTemp->wMstaAndSeq = 0x0000;
	pTemp->bFrameFlag = 0x68;
	pTemp->bCtrlCode = 0x01;
	pTemp->wTransLength = 0x000A;
	pTemp->lwTnm = 0x01;

	//֡��
	pTemp->uEntryA = 0x0202;

	//֡β
	pTemp->sPostFrame.bEndFrame = 0x16;
	return sizeof(RCU_ARG_GET_REQ_PACK_0202);
}

DWORD GetAirRCUargPacket(LPVOID lParam)
{
	PRCU_ARG_AIR_GET_REQ_PACK pTemp = (PRCU_ARG_AIR_GET_REQ_PACK)lParam;
	if(pTemp == NULL)
		return 0;
	//======================================================
	memset(pTemp,0,sizeof(RCU_ARG_AIR_GET_REQ_PACK));
	//֡ͷ
	pTemp->bStartFrame = 0x68;
	pTemp->dwRtua = 0x00000000;
	pTemp->wMstaAndSeq = 0x0000;
	pTemp->bFrameFlag = 0x68;
	pTemp->bCtrlCode = 0x01;
	pTemp->wTransLength = 0x000C;
	pTemp->lwTnm = 0x01;

	//֡��
	pTemp->uEntryA = 0x0104;
	pTemp->uEntryB = 0x0107;
	//֡β
	pTemp->sPostFrame.bEndFrame = 0x16;
	return sizeof(RCU_ARG_AIR_GET_REQ_PACK);
}

DWORD GetAirConditionPacket(LPVOID lParam,int airNum)
{
	PRCU_ARG_AIR_GET_REQ_PACK_021X pTemp = (PRCU_ARG_AIR_GET_REQ_PACK_021X)lParam;
	if(pTemp == NULL)
		return 0;
	//======================================================
	memset(pTemp,0,sizeof(RCU_ARG_AIR_GET_REQ_PACK_021X));
	//֡ͷ
	pTemp->bStartFrame = 0x68;
	pTemp->dwRtua = 0x00000000;
	pTemp->wMstaAndSeq = 0x0000;
	pTemp->bFrameFlag = 0x68;
	pTemp->bCtrlCode = 0x01;
	pTemp->wTransLength = 0x000A;
	pTemp->lwTnm = 0x01;

	//֡��
	pTemp->bCodeA = 0x10;
	pTemp->bCodeA = pTemp->bCodeA| airNum;
	pTemp->bCodeB = 0x02;
	//֡β
	pTemp->sPostFrame.bEndFrame = 0x16;
	return sizeof(RCU_ARG_AIR_GET_REQ_PACK_021X);
}

DWORD SetAirConditionPacket(LPVOID lParam,int airNum)
{
	PRCU_ARG_AIR_SET_REQ_PACK_021X pTemp = (PRCU_ARG_AIR_SET_REQ_PACK_021X)lParam;
	if(pTemp == NULL)
		return 0;
	//======================================================
	memset(pTemp,0,sizeof(RCU_ARG_AIR_SET_REQ_PACK_021X));
	//֡ͷ
	pTemp->sPreFrame.bStartFrame = 0x68;
	pTemp->sPreFrame.dwRtua = 0x00000000;
	pTemp->sPreFrame.wMstaAndSeq = 0x0000;
	pTemp->sPreFrame.bFrameFlag = 0x68;
	pTemp->sPreFrame.bCtrlCode = 0x08;
	pTemp->sPreFrame.wTransLength = 0x0011;
	pTemp->sPreFrame.wTestNodeIndex = 0x0000;
	pTemp->sPreFrame.uLevel = 0x11;
	pTemp->sPreFrame.uPasswords = 0x111111;

	//֡��
	pTemp->bCodeA = 0x10;
	pTemp->bCodeA = pTemp->bCodeA| airNum;
	pTemp->bCodeB = 0x02;
	pTemp->bType = 0x01;

	memset(pTemp->bContent,0,8);
	//֡β
	pTemp->sPostFrame.bEndFrame = 0x16;
	return sizeof(RCU_ARG_AIR_SET_REQ_PACK_021X);
}

DWORD SetDeviceSwitchStatusPacket(LPVOID lParam,int deviceCount)
{
	PRCU_ARG_SET_REQ_PACK_0201 pTemp = (PRCU_ARG_SET_REQ_PACK_0201)lParam;
	if(pTemp == NULL)
		return 0;
	//======================================================
	memset(pTemp,0,sizeof(RCU_ARG_SET_REQ_PACK_0201));
	//֡ͷ
	pTemp->sPreFrame.bStartFrame = 0x68;
	pTemp->sPreFrame.dwRtua = 0x00000000;
	pTemp->sPreFrame.wMstaAndSeq = 0x0000;
	pTemp->sPreFrame.bFrameFlag = 0x68;
	pTemp->sPreFrame.bCtrlCode = 0x08;
	pTemp->sPreFrame.wTransLength = 0x0072;
	pTemp->sPreFrame.wTestNodeIndex = 0x0000;
	pTemp->sPreFrame.uLevel = 0x11;
	pTemp->sPreFrame.uPasswords = 0x111111;

	//֡��
	pTemp->bCodeA = 0x01;
	pTemp->bCodeB = 0x02;
	pTemp->bCount = 15;

	memset(pTemp->bContent,0,105);
	//֡β
	pTemp->sPostFrame.bEndFrame = 0x16;
	return sizeof(RCU_ARG_SET_REQ_PACK_0201);
}

DWORD GetDeviceStatusPacket(LPVOID lParam,int deviceNum)
{
	PRCU_ARG_AIR_GET_REQ_PACK_021X pTemp = (PRCU_ARG_AIR_GET_REQ_PACK_021X)lParam;
	if(pTemp == NULL)
		return 0;
	//======================================================
	memset(pTemp,0,sizeof(RCU_ARG_AIR_GET_REQ_PACK_021X));
	//֡ͷ
	pTemp->bStartFrame = 0x68;
	pTemp->dwRtua = 0x00000000;
	pTemp->wMstaAndSeq = 0x0000;
	pTemp->bFrameFlag = 0x68;
	pTemp->bCtrlCode = 0x01;
	pTemp->wTransLength = 0x000A;
	pTemp->lwTnm = 0x01;

	//֡��
	pTemp->bCodeA = 0x10;
	pTemp->bCodeA = pTemp->bCodeA| deviceNum;
	pTemp->bCodeB = 0x02;
	//֡β
	pTemp->sPostFrame.bEndFrame = 0x16;
	return sizeof(RCU_ARG_AIR_GET_REQ_PACK_021X);
}

DWORD SetRCUtimingPacket(PBYTE pBuf,CTime mt)
{
	DWORD nBytes = sizeof(RCU_SET_TIMIMG_PACK);
	PRCU_SET_TIMIMG_PACK pPack = NULL;
	if(pBuf == NULL)
		return nBytes;
	pPack = reinterpret_cast<PRCU_SET_TIMIMG_PACK>(pBuf);
//=============================================================================
	pPack->sPreFrame.bStartFrame = 0x68;
	pPack->sPreFrame.dwRtua = 0x00000000;
	pPack->sPreFrame.wMstaAndSeq = 0x0000;
	pPack->sPreFrame.bFrameFlag = 0x68;
	pPack->sPreFrame.bCtrlCode = 0x08;
	pPack->sPreFrame.wTransLength = 0x000E;
	pPack->sPreFrame.wTestNodeIndex = 0x0000;
	pPack->sPreFrame.uLevel = 0x11;
	pPack->sPreFrame.uPasswords = 0x111111;

	//֡��
	pPack->wDataEntry = 0x8030;
	pPack->bYear = (BYTE)DWORD2_BCD(mt.GetYear());
	pPack->bMonth = (BYTE)DWORD2_BCD(mt.GetMonth());
	pPack->bDay = (BYTE)DWORD2_BCD(mt.GetDay());

	pPack->bHour = (BYTE)DWORD2_BCD(mt.GetHour());
	pPack->bMinute = (BYTE)DWORD2_BCD(mt.GetMinute());
	pPack->bSecond = (BYTE)DWORD2_BCD(mt.GetSecond());
//֡β
	pPack->sPostFrame.bEndFrame = 0x16;

	return nBytes;
}


///////////////////////////////////////////////////////////////////////////////////////////
//==============================================================
//���ڹ�������MCU������֡
//**************************************************
//����1�����͵�Buffer����(OUT)
//����2�����ݱ������
//����3�����ݱ�����鳤��
//����4��֡����������()
//**************************************************
//����ֵ������Buffer�ĳ���
DWORD QuiryRCUFramePack(PBYTE pBuf,unsigned short *pDataEntry,int iNum,DWORD dwRtua,WORD wMsta,__int64 lpTnm)
{
	DWORD nBytes = 0;
	PWORD pTemp = NULL;
	if((pBuf == NULL) || (pDataEntry == NULL) || (iNum < 1))
		return nBytes;
//===============================================================================
	PRCU_ARG_GET_REQ_PACK pFrame = reinterpret_cast<PRCU_ARG_GET_REQ_PACK>(pBuf);
	pFrame->bStartFrame = FRAME_START_FLAG;
	pFrame->dwRtua = DWORD2_BCD(dwRtua);
	pFrame->wMstaAndSeq = wMsta;
	pFrame->bFrameFlag = FRAME_START_FLAG;
	pFrame->bCtrlCode = 0x01;
	pFrame->wTransLength = 0x0008;
	pFrame->lwTnm = lpTnm;
	
	nBytes = 8+11;
	pTemp = (PWORD)(pBuf+nBytes);
//=============================================================	
	memcpy(pTemp,pDataEntry,iNum*sizeof(WORD));
	

	pFrame->wTransLength += iNum*((USHORT)sizeof(USHORT));
	nBytes += iNum*sizeof(WORD);

	pBuf[nBytes] = (BYTE)Crc8(pBuf,nBytes);
	pBuf[nBytes+1] = FRAME_END_FLAG;
	nBytes += 2;
	return nBytes;
}

















///////////////////////////////////////////////////////////////////////////////////////////
//==============================================================
//����ת������ṹ
//**************************************************
//����1���������͵�Buffer����
//����2��ָ�����
//����3������Buffer
//����4�����ͳ���
//**************************************************
//����ֵ������Buffer�ĳ���
/*ULONG ConvertInputDataToSendBuf(PUCHAR &pSendBuf,PDATA_TRANS_PRE pPreFrame,PUCHAR pInBuf,ULONG uInLength)
{
	ULONG nBytes = 0;
	PUCHAR	pDataBuf = NULL;

	if(pSendBuf != NULL)		//��ȷ���ǿ�ָ�봫����
		delete[] pSendBuf;

	if(pPreFrame == NULL)		//ǰ׺����Ϊ��
		return 0;

	nBytes = sizeof(DATA_TRANS_PRE)+sizeof(DATA_TRANS_POST)+uInLength;
/////////////////////////////////////////////////////////////////////////
	pSendBuf = new BYTE[nBytes];	//�ֿռ�
	if(pSendBuf == NULL)
		return 0;
	memset(pSendBuf,0xCC,nBytes);
	//ZeroMemory(pSendBuf,nBytes);	//ȫ��0
/////////////////////////////////////////////////////////////////////
	pPreFrame->wTransLength = (USHORT)uInLength;
	memcpy(pSendBuf,pPreFrame,sizeof(DATA_TRANS_PRE));
	//pPreTrans = reinterpret_cast<PDATA_TRANS_PRE>(pSendBuf);
	//pPostTrans = reinterpret_cast<PDATA_TRANS_POST>(pSendBuf+sizeof(PDATA_TRANS_PRE)+uInLength);
	if(uInLength && (pInBuf != NULL))
	{
		pDataBuf = pSendBuf+sizeof(DATA_TRANS_PRE);
		memcpy(pDataBuf,pInBuf,uInLength);
		delete[] (PUCHAR)pInBuf;
	}
////////////////////////////////////////////////////////////////////////
	FillPostBuffer(pSendBuf,nBytes);
///////////////////////////////////////////////////////////////////////
	return nBytes;
}*/


//��䷢��Buffer��ǰ׺
void FillPreBuffer(INPUT_DATA *pInput, PDATA_TRANS_PRE pPreBuf)
{
	ULONG Temp;

	if((pPreBuf == NULL)||(pInput == NULL))		//Ϊ�յĻ����˳�
		return;
	ZeroMemory(pPreBuf,sizeof(DATA_TRANS_PRE));	//ȫ��0
	pPreBuf->bStartFrame = FRAME_START_FLAG;
	//**************************************************************
	Temp = pInput->wFloor;//DWORD2_BCD(pInput->wFloor);
	Temp = (Temp << 16) | pInput->wRoom;//DWORD2_BCD(pInput->wRoom);
	//**************************************************************
	pPreBuf->dwRtua = Temp;
	pPreBuf->wMstaAndSeq = pInput->bSEQ;
	pPreBuf->wMstaAndSeq = (pPreBuf->wMstaAndSeq << 8) | pInput->bMSTA;
	pPreBuf->bFrameFlag = FRAME_START_FLAG;
	pPreBuf->bCtrlCode = pInput->bCode;
	pPreBuf->uLevel = 0x11;
	pPreBuf->uPasswords = 0x00111111;
	pPreBuf->wTransLength = 0;
}

//��䷢��Buffer��ǰ׺
void FillPreBuffer(PDATA_TRANS_PRE pPreBuf,UCHAR bCode,USHORT Floor,USHORT Room,UCHAR bMSTA,UCHAR bSEQ)
{
	ULONG Temp; 
	if(pPreBuf == NULL)		//Ϊ�յĻ����˳�
		return;
	ZeroMemory(pPreBuf,sizeof(DATA_TRANS_PRE));	//ȫ��0
	pPreBuf->bStartFrame = FRAME_START_FLAG;
	//**************************************************************
	Temp = DWORD2_BCD(Floor);
	Temp = (Temp << 16) | DWORD2_BCD(Room);
	//**************************************************************
	pPreBuf->dwRtua = Temp;
	pPreBuf->wMstaAndSeq = bSEQ;
	pPreBuf->wMstaAndSeq = (pPreBuf->wMstaAndSeq << 8) | bMSTA;
	pPreBuf->bFrameFlag = FRAME_START_FLAG;
	pPreBuf->bCtrlCode = bCode;
	pPreBuf->wTransLength = 0;
}


//��䷢��Buffer�ĺ�׺
void FillPostBuffer(PUCHAR pDataBuf,ULONG pLength)
{
	PDATA_TRANS_POST PostBuf = NULL;
	ULONG Index = 0;
	UCHAR bCS = 0;
	if((pDataBuf == NULL) || (pLength<sizeof(DATA_TRANS_POST)))
		return;
	PostBuf = reinterpret_cast<PDATA_TRANS_POST>(pDataBuf+pLength-2);
	for(Index=0;Index<pLength-2;Index++){
		bCS += pDataBuf[Index];
	}
	PostBuf->bCS = bCS;
	PostBuf->bEndFrame = FRAME_END_FLAG;
}


///////////////////////////////////////////////////////////////////////////////////////////
//==============================================================
//����ת������ṹ
//**************************************************
//����1���������͵�Buffer����
//����2��ָ�����
//����3���������ͣ� 0 ���β�����1 ����������
//**************************************************

ULONG ConvertInputDataToSendBuf(PINPUT_DATA pInput, PUCHAR pBuf, UCHAR bflag)
{
	UINT dwLen = 0;
#if 0
	PDATA_TRANS_PRE pPreBuf;
	PDATA_TRANS_OP	pOPData;
	PDATA_TRANS_HEAD pHead;
	PDEV_INFO pDevInfo;
	UCHAR bloopa,bloopb,bloopc,bloopd,bloope;
	UCHAR bloop=0;
	CString str;
	UCHAR bMaxNum;

//=======================================
	if((pInput == NULL) || (pBuf == NULL))
		return 0;

	PROOM_CONFIG_INFO pRoomUnit = (PROOM_CONFIG_INFO)(pInput->pRoomConfigInfo);
//===================================================================
//С����Ҫ�ӵĴ����������
//===================================================================
// 1. ��䷢��Buffer��ǰ׺	
	pPreBuf = (PDATA_TRANS_PRE)pBuf;
	FillPreBuffer(pInput, pPreBuf );
#ifdef cdebug
	pPreBuf->btestflag[30] =0x5a ;
	pPreBuf->btestflag[31] =0x5a;
	RecordBuffer("Input.txt",(BYTE *)pRoomUnit,1024);

//	str.Format("ValidModeNum: %d; %x;%x",pRoomUnit->MCU[0].ValidModeNum,pRoomUnit,pInput->pRoomConfigInfo);
//	AfxMessageBox(str);
#endif

// 2. ��䷢��buffer��������Ϣ��
	pOPData = (PDATA_TRANS_OP)(pBuf+sizeof(DATA_TRANS_PRE));	//895E���ݱ���
	pOPData->bOPType = pInput->bOPType; 
#ifdef cdebug
	pOPData->btestflag[0] =0x11 ;
	pOPData->btestflag[1] =0x22;
#endif
	if(bflag) 
	{//��������ʱ��
		pOPData->wDataCoding = 0x895D;
		pHead = (PDATA_TRANS_HEAD)(pOPData + 1);
	} else {
	//���β���ʱ��
		pOPData->wDataCoding = 0x895E;
		pHead = (PDATA_TRANS_HEAD)(pBuf + sizeof(DATA_TRANS_PRE) + 1); 	
	}

	
	for(bloopa=0;bloopa<1;bloopa++) 
	{// 1).loop for MCU;

#ifdef cdebug
//	str.Format("ValidModeNum: %d",pRoomUnit->MCU[0].ValidModeNum);
//	AfxMessageBox(str);

//		pBuf[bloop++] = pRoomUnit->MCU[bloopa].ValidModeNum;
//		pBuf[bloop++] = 0x1a;
#endif
		if(bflag) // ע�⣺���ǵ��β���ʱ������ pRoomUnit->MCU[bloopa].ValidModeNum��1��
			pOPData->bDeviceNum = pRoomUnit->MCU[bloopa].ValidModeNum; // �豸����
		bloopb = 0;
		bloopc = 0;
		
		while( bloopb<pRoomUnit->MCU[bloopa].ValidModeNum )
//		while(bloopc < MAX_MODULE_NUM)
		{ //2).loop for module;
#ifdef cdebug
	pHead->btestflag[0] =0x33;
	pHead->btestflag[1] =0x44;
//	str.Format("pHead: %x", pHead);
//	AfxMessageBox(str);
#endif

			if(pRoomUnit->MCU[bloopa].Module[bloopc].bModuleValid ) 
			//����ģ����Чʱ����Ϊ����Чʱ�������£�
			{
#ifdef cdebug
//		pBuf[bloop++] = pRoomUnit->MCU[bloopa].Module[bloopc].bModuleValid;
//		pBuf[bloop++] = 0x2a;
#endif
				pHead->bNodeIndex = bloopc+1;
				pHead->dwNodeAddr_L = DWORD2_BCD(pRoomUnit->MCU[bloopa].Module[bloopc].ModuleAddress);
				pHead->wNodeAddr_H = 0 ; //??????
				pHead->bFuncType = pInput->bFuncType;
				pHead->bDevType = pRoomUnit->MCU[bloopa].Module[bloopc].ModuleClass;
				pHead->bTranParam = pInput->bTranParam ;
				pHead->bDevListNum =0;
				bMaxNum =pRoomUnit->MCU[bloopa].Module[bloopc].KeyNum + pRoomUnit->MCU[bloopa].Module[bloopc].BtnNum;
				pDevInfo = (PDEV_INFO)(pHead+1);
				
				for(bloopd=0; bloopd< bMaxNum ; bloopd++)
				{//3).loop for mLunInfo;
#ifdef cdebug1
	str.Format("bDevListNum= %d loop= %d",pHead->bDevListNum, bloopd);
	AfxMessageBox(str);

#endif
					bloope = 0;
					while(bloope<MAX_SUB_LUN_MAPPING_NUM)
					{ //4) loop for MapLunInfo;
#ifdef cdebug1
		pBuf[bloop++] = bloope;
		pBuf[bloop++] = 0x4a;
#endif
						if(pRoomUnit->MCU[bloopa].Module[bloopc].mLunInfo[bloopd].MapLunInfo[bloope].IsValid == 0)
						{
							bloope++;
						}else{

#ifdef cdebug1
	str.Format("pDevInfo= %d",pDevInfo);
	AfxMessageBox(str);

#endif
#ifdef cdebug
				pDevInfo->btestflag[0] =0x55;
				pDevInfo->btestflag[1] =0x66;
#endif
							if(pHead->bDevType==5) // �յ��豸��·��Ϊ 0��
								pDevInfo->bDevNodeID = bloopd;
							else
								pDevInfo->bDevNodeID = bloopd+1;// ���������豸��·��Ϊ ��1-32����

							pDevInfo->bSpeFunc = pRoomUnit->MCU[bloopa].Module[bloopc].mLunInfo[bloopd].MapLunInfo[bloope].SpecialFun;
							pDevInfo->bLinkDevID = pRoomUnit->MCU[bloopa].Module[bloopc].mLunInfo[bloopd].MapLunInfo[bloope].ModuleIndex;
							pDevInfo->dwLinkDevLink = pRoomUnit->MCU[bloopa].Module[bloopc].mLunInfo[bloopd].MapLunInfo[bloope].LunIndex;
							bloope++;
							pHead->bDevListNum ++;
							pDevInfo = pDevInfo + 1;
							dwLen += sizeof(DEV_INFO);
						}
					}
			

				}
				bloopb ++;
				pHead = (PDATA_TRANS_HEAD)pDevInfo;
				dwLen += sizeof(DATA_TRANS_HEAD);
#ifdef cdebug1
	str.Format("pHead= %d",pHead);
	AfxMessageBox(str);

#endif
			}
			bloopc ++ ;
		}
	}

// 3. ��䷢��buffer�����ݺ�׺
	dwLen += sizeof(DATA_TRANS_PRE) + (bflag ? sizeof(DATA_TRANS_OP):(sizeof(DATA_TRANS_OP)-1)) + sizeof(DATA_TRANS_POST);
	pPreBuf->wTransLength = dwLen - 13;

	FillPostBuffer(pBuf, dwLen);

#endif
	return dwLen ;
}


//===============================================================================
//������е����õ�������
/////////////////////////////////////////////////////////////////////////////////
DWORD FillClearAllCfgPack(PINPUT_DATA pInput, PUCHAR pBuf, UCHAR bflag)
{
	WORD dwLen = 0;
	PDATA_TRANS_PRE mPreFrame = NULL;			//֡ͷ
//	PDATA_TRANS_POST mPostFrame = NULL;			//֡β
//=====================================================================
// 1. ��䷢��Buffer��ǰ׺	
	mPreFrame = reinterpret_cast<PDATA_TRANS_PRE>(pBuf);
	FillPreBuffer(pInput, mPreFrame);
	
// 2.�������
	dwLen = sizeof(DATA_TRANS_PRE);
	pBuf[dwLen++] = 0x5D;
	pBuf[dwLen++] = 0x89;
	pBuf[dwLen++] = 0x02;
	pBuf[dwLen++] = 0x00;
	
	dwLen += sizeof(DATA_TRANS_POST);
//3.���β
	mPreFrame->wTransLength = dwLen - 13;
	FillPostBuffer(pBuf, dwLen);
	return dwLen;
}










void RecordBuffer(char *pFileName,PUCHAR pBuf,ULONG pLength)
{
	HANDLE	hFile = INVALID_HANDLE_VALUE;
	DWORD	nBytes;
/////////////////////////////////////////////////////////////////////////////////////////
	hFile = CreateFile(pFileName,
              GENERIC_WRITE | GENERIC_READ,               //   don 't   need   any   access   to   the   drive 
              FILE_SHARE_READ   |   FILE_SHARE_WRITE,     //   share   mode 
              NULL,         //   default   security   attributes 
              CREATE_ALWAYS,     //   disposition 
              0,		//   file   attributes               
              NULL);       //   don 't   co
	if(hFile == INVALID_HANDLE_VALUE)
	  return;
	WriteFile(hFile,pBuf,pLength,&nBytes,NULL);
	CloseHandle(hFile);
}





///////////////////////////////////////////////////////////////////////////////////////////
//==============================================================
//����У���
//**************************************************
//����1��У���Buffer����
//����2��Buffer����
//**************************************************
//����ֵ��У����
BYTE Crc8(PUCHAR pBuf,ULONG uLength)
{
	BYTE crc = 0;
	ULONG Index;
	for(Index=0;Index<uLength;Index++)
		crc += pBuf[Index];
	return crc;
}

///////////////////////////////////////////////////////////////////////////////////////////
//==============================================================
//��DWORDת����BCD��
//**************************************************
//����1��ԭʼ����
//**************************************************
//����ֵ��BCD���
unsigned long DWORD2_BCD(unsigned long dwValue)
{
	unsigned long TempValue = 0;

	TempValue = (dwValue/10000000)<< 28;
	TempValue |= ((dwValue%10000000)/1000000)<<24;
	TempValue |= ((dwValue%1000000)/100000)<<20;
	TempValue |= ((dwValue%100000)/10000)<<16;
	TempValue |= ((dwValue%10000)/1000)<<12;
	TempValue |= ((dwValue%1000)/100)<<8;
	TempValue |= ((dwValue%100)/10)<<4;
	TempValue |= dwValue%10;
	
	return TempValue;
}

unsigned long BCD2_DWORD(unsigned long dwValue)
{
	unsigned long TempValue = 0;

	TempValue = dwValue&0x0000000F;			//��λ
	TempValue  = ((dwValue>>28)&0x0000000F)*10000000;
	TempValue += ((dwValue>>24)&0x0000000F)*1000000;
	TempValue += ((dwValue>>20)&0x0000000F)*100000;
	TempValue += ((dwValue>>16)&0x0000000F)*10000;
	TempValue += ((dwValue>>12)&0x0000000F)*1000;
	TempValue += ((dwValue>>8)&0x0000000F)*100;
	TempValue += ((dwValue>>4)&0x0000000F)*10;
	TempValue += dwValue&0x0000000F;
	
	return TempValue;
}


DWORD ToLittleEndian(DWORD dwBigEndian)
{
    BYTE* p = (BYTE*)&dwBigEndian;
    return (DWORD)(p[0] << 24) + (DWORD)(p[1] << 16) +
        (DWORD)(p[2] << 8) + (DWORD)p[3];
}


BYTE atoh(char Charect)
{
	BYTE bValue;
	//================================
	if((Charect >= '0') && (Charect <= '9')){ 
		bValue = Charect - '0';}
	else if((Charect >= 'a') && (Charect <= 'f')){ 
		bValue = Charect - 'a' + 10;}
	else if((Charect >= 'A') && (Charect <= 'F')){ 
		bValue = Charect - 'A' + 10;}
	else{
		bValue = 0;
	}
	return bValue;
}