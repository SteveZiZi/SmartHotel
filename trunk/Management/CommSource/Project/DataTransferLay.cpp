#include "StdAfx.h"
#include <afxmt.h>
#include <Winsock2.h>
#include "DataTransferLay.h"
#include "channel.h"
//#include <mstcpip.h>
#pragma comment(lib,"ws2_32.lib")				//���ؼ�;
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
static int nNetTimeout = 1000;				//�շ���ʱֵ[1��]
////////////////////////////////////////////////////////////////////////////
//TCP/IPЭ��
//***************************************************************************
//***************************************************************************
//Function:Use for init Socket 
//====================================
//input: ReqVersion����İ汾��
//Output:
//			[Success] TRUE		[Fail] FALSE
BOOL InitSocket(UINT ReqVersion)
{
	WSADATA wsaData;
	int Result;
//1����ʼ���׽���
	Result = WSAStartup(ReqVersion,&wsaData);//MAKEWORD(2,2)
	if(Result)
	{
		#ifdef TRANSLATE_LOG_NAME
			
			FILE *fp;
			fp = fopen(TRANSLATE_LOG_NAME,"wt");
			if(fp != NULL)
			{
	  			fprintf(fp,"��ʼ�׽���ʧ��%lu\n",WSAGetLastError());
				fclose(fp);
			}
		#endif;
		return FALSE;
	}
	//********************************************************
	#ifdef TRANSLATE_LOG_NAME
		FILE *fp;
		fp = fopen(TRANSLATE_LOG_NAME,"wt");
		if(fp != NULL)
		{
			fprintf(fp,"��ʼ���ɹ�\n����İ汾Ϊ:V%d.%d\nʵ�ʰ汾Ϊ:V%d.%d\n",HIBYTE(ReqVersion),LOBYTE(ReqVersion),
				HIBYTE(wsaData.wVersion),LOBYTE(wsaData.wVersion));
			fclose(fp);
		}
	#endif;
    //���汾�Ƿ��������wsaData.wVersion
    ////if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion ) != 2 )
	//if(ReqVersion != wsaData.wVersion)
	//{
    //   WSACleanup();
	//   return FALSE;
	//}
	return TRUE;
}

void UnInitSocket()
{
	#ifdef TRANSLATE_LOG_NAME
		FILE *fp;
		fp = fopen(TRANSLATE_LOG_NAME,"a+");
		if(fp != NULL)
		{
			fprintf(fp,"Close Socket Module");
			fclose(fp);
		}
	#endif;		
//*******************************************************************************
	WSACleanup();
}
//==========================================================================
//***************************************************************************
//Function:�õ�������
//====================================
//input:
//Output:
BOOL GetHostName(char *Name,int Length)
{
   int Result;
   memset(Name,'\0',Length);
   DWORD ErrorValue = 0;
   //�õ�������
   Result = gethostname(Name,Length);
   if(Result)
   {
	 ErrorValue= WSAGetLastError();
	 #ifdef TRANSLATE_LOG_NAME
	    FILE *fp;
		fp = fopen(TRANSLATE_LOG_NAME,"a+");
		if(fp != NULL)
		{
			fprintf(fp,"��ȡ������ʧ��[%lu]\n",ErrorValue);
			fclose(fp);
		}
	 #endif;	 
	 return FALSE;
   }
   else
   {
	#ifdef TRANSLATE_LOG_NAME
	    FILE *fp;
		fp = fopen(TRANSLATE_LOG_NAME,"a+");
		if(fp != NULL)
		{
			fprintf(fp,"������Ϊ��%s\n",Name);
			fclose(fp);
		}
	#endif;	 
	return TRUE;
   }
}
//Function:�õ�����IP,
//====================================
//input:IP������������������Է�����������������ṩ����������Ĭ�������Ϊ0
//Output:
//			[Success] IP		[Fail] 0
DWORD GetLocalIp(int Index)
{
   hostent* phostent;
   char HostName[MAX_PATH];
   BOOL Result;
   DWORD ip = 0;
   DWORD ErrorValue = 0;

   //�õ�������
   Result = GetHostName(HostName,MAX_PATH);
   if(Result == FALSE)
	 return 0;

   //�õ�����IP
   phostent =  gethostbyname(HostName);
   if(phostent == NULL)
   {
 	 ErrorValue= WSAGetLastError();
	 #ifdef TRANSLATE_LOG_NAME
	    FILE *fp;
		fp = fopen(TRANSLATE_LOG_NAME,"a+");
		if(fp != NULL)
		{
			fprintf(fp,"��ȡ����IPʧ��[%lu]\n",ErrorValue);
			fclose(fp);
		}
	 #endif;	 
	 return 0;  
   }
   //�ɹ���
   ip = inet_addr(inet_ntoa(*(in_addr*)phostent->h_addr_list[Index]));
   //*******************************************************************
   #ifdef TRANSLATE_LOG_NAME
		FILE *fp;
		fp = fopen(TRANSLATE_LOG_NAME,"a+");
		if(fp != NULL)
		{
			//fprintf(fp,"����IPΪ[%08X]\n",ip);
			fprintf(fp,"����IPΪ[%s]\n",inet_ntoa(*(in_addr*)phostent->h_addr_list[Index]));
			fclose(fp);
		}
   #endif;	 
   return ip;
}

//############################################################################################
//Function:���Ͳ��õ�����֡
//====================================
//input:���ͻ����������ͻ���������
//		���ջ����������ջ���������
//		Ŀ��IP���˿�
//Output:
//			���յĳ���
unsigned long SendDataWithResponse(unsigned char* pSendBuf,unsigned long ulSendLength,
									unsigned char* pRevBuf,unsigned long ulRevLength,
									unsigned long TargetIp,unsigned short ulPort)
{
	C_Channel* pChannel = NULL;
	
	pChannel = C_ChannelFactory ::GetChannel(TargetIp,ulPort);

       if (pChannel == NULL)
       {
		return 0;	
       }

	if (pChannel->IsConnected() == true)
	{
		pChannel->SendData((char*)pSendBuf, (long)ulSendLength);
	}
	else
	{
		pChannel->Open();
		if (pChannel->IsConnected() == true)
		{
			pChannel->SendData((char*)pSendBuf, (long)ulSendLength);
		}
		else
		{
			return 0;
		}
	}

	return pChannel->ReceiveData((char*)pRevBuf, (long)ulRevLength);
}











#if 0
//============================================================================
CMutex hQueueMutex(FALSE,NULL,NULL);								//�������
CEvent hCmdCompleteEvent(FALSE,FALSE,NULL,NULL);		//��ѯ�������¼�

REQUEST_QUEUE_ENTRY  m_pRequestQueue[MAX_REQUEST_QUEUE_NUM];
ULONG	LocalIpAddress = 0x0100007F;		//����Ĭ�ϵ�IP
USHORT	ReqVersion = MAKEWORD(1,1);			//����ͨ�ŵİ汾
int		nNetTimeout = 1000;					//�շ���ʱֵ[1��]
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
int GetValidQueueEntry()			//�õ�һ����Ч�Ķ��нṹ
{
	int Result = -1;
	hQueueMutex.Lock();
	for(int Index=0;Index<MAX_REQUEST_QUEUE_NUM;Index++)
	{
		if(m_pRequestQueue[Index].bStatus == 0)
		{
			Result = Index;
			break;
		}
	}
	hQueueMutex.Unlock();
	return Result;
}
//==============================================================
//��Ŀ��Ip�������ݱ�
//**************************************************
//����1��Ŀ������ӵ��׽���
//����2��ָ�����
//����3������Buffer
//����4�����ͳ���
//**************************************************
ULONG SendDataToTargetIp(SOCKET	sTarget,PVOID pPreFrame,PUCHAR pInBuf,ULONG uInLength)
{
	ULONG dwSendLength = 0;	
	PBYTE pSendBuf = NULL;
	int Result = 0;
	dwSendLength = ConvertInputDataToSendBuf(pSendBuf,(PDATA_TRANS_PRE)pPreFrame,pInBuf,uInLength);
	if((dwSendLength == 0) || (pSendBuf == NULL))
	{//Allocate Send Buffer Fail
		#ifdef PRINT_LOG
			FILE *fp;
			fp = fopen(sLogName,"a+");
			if(fp != NULL)
			{
				fprintf(fp,"��������Buffer ����[%ld]  [%lx]\n",dwSendLength,pSendBuf);
				fclose(fp);
			}
		#endif;				
		return 0;
	}
	//========================================================================================================================================
//Johnson Debug 
	RecordBuffer("SendBuf.v",pSendBuf,dwSendLength);
	
	Result = send(sTarget,(const char*)pSendBuf,dwSendLength,0);
	if(Result == SOCKET_ERROR)   //���ʳ���
	{
		#ifdef PRINT_LOG
			FILE *fp;
			fp = fopen(sLogName,"a+");
			if(fp != NULL)
			{
				fprintf(fp,"��������ʧ��(%lX)\n",WSAGetLastError());
				fclose(fp);
			}
		#endif;		
		return 0;
	}	

	//============================================================================================================================================================
	#ifdef PRINT_LOG
		FILE *fp;
		fp = fopen(sLogName,"a+");
		if(fp != NULL)
		{
			fprintf(fp,"�������ݵ��ɹ� %ld\n",Result);
			fclose(fp);
		}
	#endif;		
	return Result;
}



//==============================================================
//��Ŀ��Ip��������
//**************************************************
//����1��Ŀ������ӵ��׽���
//����2��ָ�����
//����3������Buffer
//����4�����ͳ���
//**************************************************
void RecvDataFromTargetIp(SOCKET	sTarget,PUCHAR pOutBuf,ULONG &uOutLength)
{
	int Result = 0;
//���Buf�ͳ��Ȳ�ƥ�䣬����
	if((pOutBuf == NULL) || (uOutLength==0))
	{
		uOutLength = 0;
		return ;
	}
	Result = recv(sTarget,(char *)pOutBuf,uOutLength,0);//
	if(Result == SOCKET_ERROR)   //���ʳ���
	{
		#ifdef PRINT_LOG
			FILE *fp;
			fp = fopen(sLogName,"a+");
			if(fp != NULL)
			{
				fprintf(fp,"��������ʧ��(%lX)\n",WSAGetLastError());
				fclose(fp);
			}
		#endif; 	
		return ;
	}	
	uOutLength = Result;
	#ifdef PRINT_LOG
		FILE *fp;
		fp = fopen(sLogName,"a+");
		if(fp != NULL)
		{
			fprintf(fp,"[%d]�յ�����:%02X %02X %02X %02X\n",uOutLength,
				pOutBuf[0],pOutBuf[1],pOutBuf[2],pOutBuf[3]);
			fclose(fp);
		}
	#endif; 		
}
//=========================================================================================================
//�������м���һ��Ip����
//*******************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL InsertIntoQueueList(UCHAR CmdCode,const char* sIpAddress,USHORT wPort,PUCHAR	pInBuf,PUCHAR pOutBuf)
{
	int Result;
	DWORD	dwIp;
//	DWORD nBytes;
	int EntryIndex = 0;
	while(1)		//�ҵ��пյ�ָ�����
	{
		EntryIndex = GetValidQueueEntry();
		if(EntryIndex == -1)
		{
			WaitForSingleObject(hCmdCompleteEvent,INFINITE);		//�����һ��
			continue;
		}
		break;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
	dwIp = inet_addr(sIpAddress);
	m_pRequestQueue[EntryIndex].Code = CmdCode;
	m_pRequestQueue[EntryIndex].IpAddress = BIG_ENDIAN_DWORD(dwIp);
	m_pRequestQueue[EntryIndex].uPort = wPort;
	m_pRequestQueue[EntryIndex].pInBuf = pInBuf;
	m_pRequestQueue[EntryIndex].InputLength = 0;
	m_pRequestQueue[EntryIndex].pOutBuf = pOutBuf;
	m_pRequestQueue[EntryIndex].OutputLength = 10;
	////////////////////////////////////////////////////////////////////////////////
	Result = ConnectTargetIP_Address(m_pRequestQueue[EntryIndex].ClientSocket,m_pRequestQueue[EntryIndex].IpAddress,m_pRequestQueue[EntryIndex].uPort);			//����0�Ǳ�ʾû��
	/*if(!Result)		//����ʧ��
	{
		//==============================
		nBytes = SendOutData(EntryIndex);
		if(nBytes)	//��������ǳɹ���
			ReceiveData(EntryIndex);

		closesocket(m_pRequestQueue[EntryIndex].ClientSocket);			//
		return TRUE;
	}*/
	////////////////////////////////////////////////////////////////////////////////
	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////////////////////



















//////////////////////////////////////////////////////////////////////////////////////////////////////
int	QuiryHostInNet(PVOID pPreFrame,DWORD TargetIp,USHORT sPort,PUCHAR pInBuf,ULONG InLength,PUCHAR pOutBuf,ULONG &OutLength)
{//�������ӵ�ͨ������������
	SOCKET	ClientSocket;
	int Result;
//1������Ŀ��IP
	Result = ConnectTargetIP_Address(ClientSocket,TargetIp,sPort);
	//0��ʾ����			��0��ʾʧ��
	if(Result)
	{
		OutLength = 0;
		return 1;		//ʧ���˾ͷ��ط�0ֵ
	}
//2����������
	Result = SendDataToTargetIp(ClientSocket,pPreFrame,pInBuf,InLength);
	if(Result == 0)
	{
		OutLength = 0;	
		return 2;
	}
//3����������
	RecvDataFromTargetIp(ClientSocket,pOutBuf,OutLength);

	return 0;
}




#endif















