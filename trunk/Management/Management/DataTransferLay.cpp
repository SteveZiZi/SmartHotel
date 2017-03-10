#include "StdAfx.h"
#include <afxmt.h>
//#include <Winsock2.h>
#include "DataTransferLay.h"
//#include <mstcpip.h>
#pragma comment(lib,"ws2_32.lib")//这句关键;

////////////////////////////////////////////////////////////////////////////
//============================================================================
CMutex hQueueMutex(FALSE,NULL,NULL);								//互斥变量
CEvent hCmdCompleteEvent(FALSE,FALSE,NULL,NULL);		//查询结束的事件

REQUEST_QUEUE_ENTRY  m_pRequestQueue[MAX_REQUEST_QUEUE_NUM];
ULONG	LocalIpAddress = 0x0100007F;		//本机默认的IP
USHORT	ReqVersion = MAKEWORD(1,1);			//请求通信的版本
int		nNetTimeout = 1000;					//收发超时值[1秒]
////////////////////////////////////////////////////////////////////////////
//==========================================================================
//***************************************************************************
//Function:得到主机名
//====================================
//input:
//Output:
BOOL GetHostName(char *Name,int Length)
{
   int Result;
   memset(Name,'\0',Length);
   DWORD ErrorValue = 0;
   //得到主机名
   Result = gethostname(Name,Length);
   if(Result)
   {
	 ErrorValue= WSAGetLastError();
	 #ifdef PRINT_LOG
	    FILE *fp;
		fp = fopen(sLogName,"a+");
		if(fp != NULL)
		{
			fprintf(fp,"获取主机名失败[%lu]\n",ErrorValue);
			fclose(fp);
		}
	 #endif;	 
	 return FALSE;
   }
   else
   {
	#ifdef PRINT_LOG
	    FILE *fp;
		fp = fopen(sLogName,"a+");
		if(fp != NULL)
		{
			fprintf(fp,"主机名为：%s\n",Name);
			fclose(fp);
		}
	#endif;	 
	return TRUE;
   }
}
/////////////////////////////////////////////////////////////////////////////
//***************************************************************************
//Function:得到本机IP,
//====================================
//input:IP链的索引，输入的是以防多网卡的情况必须提供网卡索引，默认情况下为0
//Output:
//			[Success] IP		[Fail] 0
DWORD GetLocalIp(int Index)
{
   hostent* phostent;
   char HostName[MAX_PATH];
   BOOL Result;
   DWORD ip = 0;
   DWORD ErrorValue = 0;

   //得到主机名
   Result = GetHostName(HostName,MAX_PATH);
   if(Result == FALSE)
	 return 0;

   //得到主机IP
   phostent =  gethostbyname(HostName);
   if(phostent == NULL)
   {
 	 ErrorValue= WSAGetLastError();
	 #ifdef PRINT_LOG
	    FILE *fp;
		fp = fopen(sLogName,"a+");
		if(fp != NULL)
		{
			fprintf(fp,"获取本机IP失败[%lu]\n",ErrorValue);
			fclose(fp);
		}
	 #endif;	 
	 return 0;  
   }
   //成功后
   ip = inet_addr(inet_ntoa(*(in_addr*)phostent->h_addr_list[Index]));
   //*******************************************************************
   #ifdef PRINT_LOG
		FILE *fp;
		fp = fopen(sLogName,"a+");
		if(fp != NULL)
		{
			//fprintf(fp,"本机IP为[%08X]\n",ip);
			fprintf(fp,"本机IP为[%s]\n",inet_ntoa(*(in_addr*)phostent->h_addr_list[Index]));
			fclose(fp);
		}
   #endif;	 
   return ip;
}
/////////////////////////////////////////////////////////////////////////////////////
BOOL InitDataTransferLay()
{
	int Index;
	for(Index=0;Index<MAX_REQUEST_QUEUE_NUM;Index++)
		ZeroMemory(&m_pRequestQueue[Index],sizeof(REQUEST_QUEUE_ENTRY));

	#ifdef PRINT_LOG
		FILE *fp;
		fp = fopen(sLogName,"wt");
		if(fp != NULL)
			fclose(fp);
	#endif;	 

	//////////////////////////////////////////////////////////////////////////////
	InitSocket();
	LocalIpAddress = GetLocalIp(0);
	return TRUE;
}

//
void UnInitDataTransferLay()
{
	WSACleanup();
}

////////////////////////////////////////////////////////////////////////////
int GetValidQueueEntry()			//得到一个有效的队列结构
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

//***************************************************************************
//Function:Use for init Socket 
//====================================
//input:
//Output:
//			[Success] TRUE		[Fail] FALSE
BOOL InitSocket()
{
	WSADATA wsaData;
	int Result;
//1、初始化套接字
	Result = WSAStartup(ReqVersion,&wsaData);//MAKEWORD(2,2)
	if(Result)
	{
		#ifdef PRINT_LOG
			FILE *fp;
			fp = fopen(sLogName,"a+");
			if(fp != NULL)
			{
	  			fprintf(fp,"初始套接字失败%lu\n",WSAGetLastError());
				fclose(fp);
			}
		#endif;
		return FALSE;
	}
	//********************************************************
	#ifdef PRINT_LOG
		FILE *fp;
		fp = fopen(sLogName,"a+");
		if(fp != NULL)
		{
			fprintf(fp,"初始化成功\n请求的版本为:V%d.%d\n实际版本为:V%d.%d\n",HIBYTE(ReqVersion),LOBYTE(ReqVersion),
				HIBYTE(wsaData.wVersion),LOBYTE(wsaData.wVersion));
			fclose(fp);
		}
	#endif;
    //检查版本是否是请求的wsaData.wVersion
    ////if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion ) != 2 )
	//if(ReqVersion != wsaData.wVersion)
	//{
    //   WSACleanup();
	//   return FALSE;
	//}
	return TRUE;
}

//=========================================================================================================
//客户端操作事项
//*******************************************************************************************
//连接客户端程序
int ConnectTargetIP_Address(SOCKET  &ClientSocket,ULONG address,USHORT Port)
{
	int Result;
	u_long  EnUnBlockMode = 0;		//0:  禁止非阻塞		X:允许非阻塞
//1:创建监察套接字
	//struct protoent *ppe; 
	//ppe=getprotobyname("tcp"); 
	//SOCKET ClientSocket;
	//两种套接字
	//A:流式Socket(SOCK_STREAM)		面向连接的TCP服务应用
	ClientSocket = socket(AF_INET,SOCK_STREAM,0);
	//ClientSocket = socket(AF_INET,SOCK_STREAM,0);//ppe->p_proto);	  //AF_INET是基于IPV4		PF_INET是基于IPV6
	//B:数据报式Socket(SOCK_DGRAM)	无连接的UDP服务应用
	//ClientSocket = socket(PF_INET,SOCK_DGRAM,0);	
	//C:原始Socket					允许程序使用低层协议
	//ClientSocket = socket(PF_INET,SOCK_RAW,0);	
//2:设定套接字的访问模式
  //异步的设置方法
	//WSAAsynSelect(ListenSocket,hWnd,WM_SOCKET,FD_READ|FD_CLOSE|FD_CONNECT);
	//允许或禁止套接口s的非阻塞模式	
	Result = ioctlsocket(ClientSocket,FIONBIO,&EnUnBlockMode);
	if(Result != NO_ERROR)//== SOCKET_ERROR)
	{
		#ifdef PRINT_LOG
			FILE *fp;
			fp = fopen(sLogName,"a+");
			if(fp != NULL)
			{
				fprintf(fp,"套接字的模式设定失败[%ld]\n",WSAGetLastError());
				fclose(fp);
			}
		#endif;	
		return	1;			//套接字的模式设定失败
	}
//3:设定收发超时值
	setsockopt(ClientSocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&nNetTimeout,sizeof(int));		//发送时限
	setsockopt(ClientSocket,SOL_SOCKET,SO_RCVTIMEO,(char *)&nNetTimeout,sizeof(int));		//接收时限
//4:绑定在地址上
	sockaddr_in  addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(Port);
	addr.sin_addr.S_un.S_addr = htonl(address);
	//=====================================================================
	Result = connect(ClientSocket,(sockaddr*)&addr,sizeof(sockaddr));
	//Result = SOCKET_ERROR;
	if(Result == SOCKET_ERROR)   //访问出错
	{
		#ifdef PRINT_LOG
			FILE *fp;
			fp = fopen(sLogName,"a+");
			if(fp != NULL)
			{
				fprintf(fp,"链接Ip:%s Port:%d失败[%ld](%lX)\n",inet_ntoa(addr.sin_addr),Port,WSAGetLastError(),address);
				fclose(fp);
			}
		#endif;		
		return 2;
	}
//连接超时
   //select 模型，即设置超时
   struct timeval timeout ;
   fd_set r;
   FD_ZERO(&r);
   FD_SET(ClientSocket, &r);
   timeout.tv_sec = 0; //连接超时15秒
   timeout.tv_usec =100;
   Result = select(0, 0, &r, 0, &timeout);
   if ( Result <= 0 )
   {
     closesocket(ClientSocket);
     return 4;
   }
////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
//一般非锁定模式套接比较难控制，可以根据实际情况考虑 再设回阻塞模式
	EnUnBlockMode = 0;
	Result = ioctlsocket(ClientSocket,FIONBIO,&EnUnBlockMode);
	if(Result != NO_ERROR)//== SOCKET_ERROR)
	{
		#ifdef PRINT_LOG
			FILE *fp;
			fp = fopen(sLogName,"a+");
			if(fp != NULL)
			{
				fprintf(fp,"套接字的模式设定失败[%ld]\n",WSAGetLastError());
				fclose(fp);
			}
		#endif;	
		return	1;			//套接字的模式设定失败
	}
*/
	//closesocket(ClientSocket);
	return 0;
}
//==============================================================
//往目标Ip发送数据报
//**************************************************
//参数1：目标机连接的套接字
//参数2：指令代码
//参数3：发送Buffer
//参数4：发送长度
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
				fprintf(fp,"发送数据Buffer 错误[%ld]  [%lx]\n",dwSendLength,pSendBuf);
				fclose(fp);
			}
		#endif;				
		return 0;
	}
	//========================================================================================================================================
//Johnson Debug 
	RecordBuffer("SendBuf.v",pSendBuf,dwSendLength);
	
	Result = send(sTarget,(const char*)pSendBuf,dwSendLength,0);
	if(Result == SOCKET_ERROR)   //访问出错
	{
		#ifdef PRINT_LOG
			FILE *fp;
			fp = fopen(sLogName,"a+");
			if(fp != NULL)
			{
				fprintf(fp,"发送数据失败(%lX)\n",WSAGetLastError());
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
			fprintf(fp,"发送数据到成功 %ld\n",Result);
			fclose(fp);
		}
	#endif;		
	return Result;
}



//==============================================================
//从目标Ip接收数据
//**************************************************
//参数1：目标机连接的套接字
//参数2：指令代码
//参数3：发送Buffer
//参数4：发送长度
//**************************************************
void RecvDataFromTargetIp(SOCKET	sTarget,PUCHAR pOutBuf,ULONG &uOutLength)
{
	int Result = 0;
//如果Buf和长度不匹配，返回
	if((pOutBuf == NULL) || (uOutLength==0))
	{
		uOutLength = 0;
		return ;
	}
	Result = recv(sTarget,(char *)pOutBuf,uOutLength,0);//
	if(Result == SOCKET_ERROR)   //访问出错
	{
		#ifdef PRINT_LOG
			FILE *fp;
			fp = fopen(sLogName,"a+");
			if(fp != NULL)
			{
				fprintf(fp,"接收数据失败(%lX)\n",WSAGetLastError());
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
			fprintf(fp,"[%d]收到数据:%02X %02X %02X %02X\n",uOutLength,
				pOutBuf[0],pOutBuf[1],pOutBuf[2],pOutBuf[3]);
			fclose(fp);
		}
	#endif; 		
}
//=========================================================================================================
//往队列中加入一个Ip命令
//*******************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL InsertIntoQueueList(UCHAR CmdCode,const char* sIpAddress,USHORT wPort,PUCHAR	pInBuf,PUCHAR pOutBuf)
{
	int Result;
	DWORD	dwIp;
//	DWORD nBytes;
	int EntryIndex = 0;
	while(1)		//找到有空的指令对列
	{
		EntryIndex = GetValidQueueEntry();
		if(EntryIndex == -1)
		{
			WaitForSingleObject(hCmdCompleteEvent,INFINITE);		//等完成一个
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
	Result = ConnectTargetIP_Address(m_pRequestQueue[EntryIndex].ClientSocket,m_pRequestQueue[EntryIndex].IpAddress,m_pRequestQueue[EntryIndex].uPort);			//返回0是表示没错
	/*if(!Result)		//链接失败
	{
		//==============================
		nBytes = SendOutData(EntryIndex);
		if(nBytes)	//如果发送是成功的
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
{//面向连接的通信数据在这里
	SOCKET	ClientSocket;
	int Result;
//1、链接目标IP
	Result = ConnectTargetIP_Address(ClientSocket,TargetIp,sPort);
	//0表示正常			非0表示失败
	if(Result)
	{
		OutLength = 0;
		return 1;		//失败了就返回非0值
	}
//2、发送数据
	Result = SendDataToTargetIp(ClientSocket,pPreFrame,pInBuf,InLength);
	if(Result == 0)
	{
		OutLength = 0;	
		return 2;
	}
//3、接收数据
	RecvDataFromTargetIp(ClientSocket,pOutBuf,OutLength);

	return 0;
}




















