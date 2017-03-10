//***************************************************************************
//=======     ��Ҫ�������ݴ���Ĳ���	=====================================
//***************************************************************************
#ifndef DATA_TRANSFERLAY_H
#define DATA_TRANSFERLAY_H
//***************************************************************************
#include <Winsock2.h>
//////////////////////////////////////////////////////////////////////////
#define	MAX_REQUEST_QUEUE_NUM		6

#define	PRINT_LOG			//��ӡLog
#define	sLogName	(TEXT("Net.Log")) 
//******************************************************
#define	BIG_ENDIAN_DWORD(X)	(((X & 0x000000FF) << 24) | ((X & 0x0000FF00) << 8) | ((X & 0x00FF0000) >> 8) | ((X & 0xFF000000) >> 24))

//IP���ݶ��еĽṹ=====================================
typedef struct _REQUEST_QUEUE_ENTRY
{
	UCHAR	bStatus;			//��ǰ�����Ƿ���Ч
	UCHAR	Code;				//ָ�������

	USHORT	uPort;				//ͨ�Ŷ˿�

	ULONG	IpAddress;			//IP��ַ

	PUCHAR	pInBuf;
	ULONG	InputLength;

	PUCHAR	pOutBuf;
	ULONG	OutputLength;

	SOCKET  ClientSocket;		//�׽���
}REQUEST_QUEUE_ENTRY,*PREQUEST_QUEUE_ENTRY;
//======================================================
//////////////////////////////////////////////////////////////
BOOL InitSocket();
BOOL InitDataTransferLay();			//��ʼ������
void UnInitDataTransferLay();
//����
BOOL InsertIntoQueueList(UCHAR CmdCode,const char* sIpAddress,USHORT wPort,PUCHAR	pInBuf,PUCHAR pOutBuf);



int ConnectTargetIP_Address(SOCKET  &ClientSocket,ULONG address,USHORT Port);		//����
ULONG SendDataToTargetIp(SOCKET	sTarget,PVOID pPreFrame,PUCHAR pInBuf,ULONG uInLength);
void RecvDataFromTargetIp(SOCKET	sTarget,PUCHAR pOutBuf,ULONG &uOutLength);




int	QuiryHostInNet(PVOID pPreFrame,DWORD TargetIp,USHORT sPort,PUCHAR pInBuf,ULONG InLength,PUCHAR pOutBuf,ULONG &OutLength);
#endif
