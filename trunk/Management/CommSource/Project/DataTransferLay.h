//***************************************************************************
//=======     主要用于数据传输的操作	=====================================
//***************************************************************************
#ifndef DATA_TRANSFERLAY_H
#define DATA_TRANSFERLAY_H
//***************************************************************************
//////////////////////////////////////////////////////////////////////////
#define		TRANSLATE_LOG_NAME		_T("LogFile\\Net.Log")	//网络记录文件
#define		BIG_ENDIAN_DWORD(X)	(((X & 0x000000FF) << 24) | ((X & 0x0000FF00) << 8) | ((X & 0x00FF0000) >> 8) | ((X & 0xFF000000) >> 24))
/*#define		BIG_ENDIAN_DWORD(X)		(((X & 0x000000FF) << 24) | ((X & 0x0000FF00) << 8) | ((X & 0x00FF0000) >> 8) | ((X & 0xFF000000) >> 24))

#define		BYTE2_BCD(x)	(((x/10)<<4)|(x%10))			//字节转8421 BCD码
#define		SHORT2_BCD(x)	(((x/1000)<< 12) | (((x%1000)/100)<<8) | (((x%100)/10)<<4) | (x%10))
#define		DWORD2_BCD(x)	(((x/10000000)<< 28) | (((x%10000000)/1000000)<<24) | \
							(((x%1000000)/100000)<<20) | (((x%100000)/10000)<<16) | (((x%10000)/1000)<<12) | (((x%1000)/100)<<8) | \
							(((x%100)/10)<<4) | (x%10))
#define		BCD2_BYTE(x)	((((x >> 4)&0x0F)*10)+(x&0x0F)) 
#define		BCD2_SHORT(x)	((((x>>12)&0x000F)*1000)+(((x>>8)&0x000F)*100)+(((x>>8)&0x000F)*10)+(x&0x000F))
*/
//=====================================================================
//TCP/IP部分
//*********************************************************************
//函数声明部分如下
BOOL InitSocket(UINT ReqVersion=MAKEWORD(1,1));		//初始化套接字
void UnInitSocket();								//结束套接字
//BOOL	GetHostName(char *Name,int Length);				//得到主机名
//DWORD	GetLocalIp(int Index);							//得到网卡IP

//发送数据并接收状态
unsigned long SendDataWithResponse(unsigned char* pSendBuf,unsigned long ulSendLength,
									unsigned char* pRevBuf=NULL,unsigned long ulRevLength=0,
									unsigned long TargetIp=0x7F000001,unsigned short ulPort=80);



//BOOL	SocketInit(SOCKET* pClientSocket,unsigned long TargetIp,unsigned short ulPort);












#if 0
#define	MAX_REQUEST_QUEUE_NUM		6

#define	PRINT_LOG			//打印Log
#define	sLogName	(TEXT("Net.Log")) 
//******************************************************

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

BOOL InitDataTransferLay();			//初始化工作
void UnInitDataTransferLay();
//链接
BOOL InsertIntoQueueList(UCHAR CmdCode,const char* sIpAddress,USHORT wPort,PUCHAR	pInBuf,PUCHAR pOutBuf);



int ConnectTargetIP_Address(SOCKET  &ClientSocket,ULONG address,USHORT Port);		//链接
ULONG SendDataToTargetIp(SOCKET	sTarget,PVOID pPreFrame,PUCHAR pInBuf,ULONG uInLength);
void RecvDataFromTargetIp(SOCKET	sTarget,PUCHAR pOutBuf,ULONG &uOutLength);




int	QuiryHostInNet(PVOID pPreFrame,DWORD TargetIp,USHORT sPort,PUCHAR pInBuf,ULONG InLength,PUCHAR pOutBuf,ULONG &OutLength);
#endif
#endif
