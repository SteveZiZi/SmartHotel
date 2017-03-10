//***************************************************************************
//=======     主要用于数据传输的操作	=====================================
//***************************************************************************
#ifndef DATA_TRANSFERLAY_H
#define DATA_TRANSFERLAY_H
//***************************************************************************
#include <Winsock2.h>
//////////////////////////////////////////////////////////////////////////
#define	MAX_REQUEST_QUEUE_NUM		6

#define	PRINT_LOG			//打印Log
#define	sLogName	(TEXT("Net.Log")) 
//******************************************************
#define	BIG_ENDIAN_DWORD(X)	(((X & 0x000000FF) << 24) | ((X & 0x0000FF00) << 8) | ((X & 0x00FF0000) >> 8) | ((X & 0xFF000000) >> 24))

//IP数据队列的结构=====================================
typedef struct _REQUEST_QUEUE_ENTRY
{
	UCHAR	bStatus;			//当前对象是否有效
	UCHAR	Code;				//指令代码字

	USHORT	uPort;				//通信端口

	ULONG	IpAddress;			//IP地址

	PUCHAR	pInBuf;
	ULONG	InputLength;

	PUCHAR	pOutBuf;
	ULONG	OutputLength;

	SOCKET  ClientSocket;		//套接字
}REQUEST_QUEUE_ENTRY,*PREQUEST_QUEUE_ENTRY;
//======================================================
//////////////////////////////////////////////////////////////
BOOL InitSocket();
BOOL InitDataTransferLay();			//初始化工作
void UnInitDataTransferLay();
//链接
BOOL InsertIntoQueueList(UCHAR CmdCode,const char* sIpAddress,USHORT wPort,PUCHAR	pInBuf,PUCHAR pOutBuf);



int ConnectTargetIP_Address(SOCKET  &ClientSocket,ULONG address,USHORT Port);		//链接
ULONG SendDataToTargetIp(SOCKET	sTarget,PVOID pPreFrame,PUCHAR pInBuf,ULONG uInLength);
void RecvDataFromTargetIp(SOCKET	sTarget,PUCHAR pOutBuf,ULONG &uOutLength);




int	QuiryHostInNet(PVOID pPreFrame,DWORD TargetIp,USHORT sPort,PUCHAR pInBuf,ULONG InLength,PUCHAR pOutBuf,ULONG &OutLength);
#endif
