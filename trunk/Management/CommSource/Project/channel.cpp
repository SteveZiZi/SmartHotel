#include "channel.h"
#include "StdAfx.h"
/*
brief: 建立SOCKET链接，打开网络通讯口
param [in]void
return bool:true,建联成功。false，建联失败。
author:Steven Wan
date: 2015-05-04
*/ 
bool C_NetChannel::Open()
{
	PHOSTENT			phe;
	SOCKADDR_IN			inetAddr;
	int					nRet;
	long				ConnectTimes;
	try
	{
		inetAddr.sin_family = AF_INET;
		inetAddr.sin_port = htons((u_short)m_NetPort);
		phe = gethostbyname(m_StrIpAddress);
		if(phe == NULL) 
		{
			m_bOpened = false;
			return false;
		}
		memcpy((char FAR *)&(inetAddr.sin_addr), phe->h_addr, phe->h_length);
		if((DataSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) //建联失败
		{
			m_bOpened = false;
			return false;
		}
		TIMEVAL tv_out;
		tv_out.tv_sec = 1;
		tv_out.tv_usec = 0;
		nRet = setsockopt(DataSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv_out, sizeof(tv_out));
		ConnectTimes = 1;
		while (ConnectTimes < 3)//建联重试次数3次
		{
			nRet = connect(DataSocket,(PSOCKADDR)&inetAddr,sizeof(inetAddr));//建联
			if (nRet == SOCKET_ERROR)//建联失败
			{
				ConnectTimes++;
				Sleep(100);
			}
			else//建联成功
			{
				m_bOpened = true;
				return true;
			}
		}
		m_bOpened = false;
		return false;
	}
	catch(...)
	{
		m_bOpened = false;
		return false;
	}
	return true;
}

/*
brief: socket发送数据接口
param [in]char* sData:发送数据缓冲区指针
param [in]long sLength:待发送数据长度
return bool:true,成功。false，失败。
author:Steven Wan
date: 2015-05-04
*/ 
bool C_NetChannel::SendData(char* sData,long sLength)
{
	int				SendLength;
	int				BlockTimes;
	try
	{
		BlockTimes = 0;
		//if (mEchoTerm > 0 ) Sleep(mEchoTerm);
		while (BlockTimes < 3)
		{
			SendLength = send(DataSocket,sData,sLength,0);
			if(SendLength == SOCKET_ERROR ) //发送错误
			{	
				if(GetLastError() == WSAECONNABORTED)
				{
					Close();
				}else
				{
					BlockTimes++;
					Sleep(mDataTerm);
				}
			}
			else//发送成功
			{
				return true;
			}
		}
		return false;
	}
	catch(...)
	{
		return false;
	}	
}

/*
brief: socket接收数据接口
param [in]char* sData:接收数据缓冲区指针
param [in]long MaxLength:接收缓冲区最大长度
return long:实际接收字节数
author:Steven Wan
date: 2015-05-04
*/ 
long C_NetChannel::ReceiveData(char* sData,long MaxLength)
{
	long			GetLength;
	CString			Error;
	int				ErrNo;
	try
	{
		//if (mDataTerm > 0 ) Sleep(mDataTerm);
		GetLength=recv(DataSocket,sData,MaxLength,0);
		if(GetLength==0)
		{
			return 0;
		}
		else if(GetLength==SOCKET_ERROR) 
		{
			ErrNo = GetLastError();
			if(GetLastError() == WSAECONNABORTED)
			{
				Close();
			}
			else if (GetLastError()==WSAEWOULDBLOCK)
			{
				Sleep(mDataTerm);
			}
			return 0;
		}
		else
		{
			return GetLength;
		}
	}
	catch(...)
	{
		return 0;
	}
}

/*
brief: 判断该IP和端口一致的通道参数是否存在
param [in]unsigned long IpAddress:IP地址
param [in]INT NetPort:端口号
return bool:true,一致。false，不一致。
author:Steven Wan
date: 2015-05-04
*/ 
bool	C_NetChannel::Match(unsigned long IpAddress,INT NetPort)
{
	if (m_IpAddress == IpAddress && m_NetPort == NetPort)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
brief: 关闭网络通道
param [in]void
return void
author:Steven Wan
date: 2015-05-04
*/ 
void C_NetChannel::Close() 
{
	try
	{
		closesocket(DataSocket);
		DataSocket = NULL;
		m_bOpened = false;
	}
	catch(...)
	{
		return;
	}
}

/*
brief: 设置网络通讯参数
param [in]unsigned long IpAddress:网络地址
param [in]int NetPort:端口号
return bool
author:Steven Wan
date: 2015-05-04
*/ 
bool C_NetChannel::SetChannel(unsigned long IpAddress,int NetPort)
{
 	m_IpAddress = IpAddress;
	m_NetPort = NetPort;
	unsigned char ip[4] = {0};
	ip[0] = (unsigned char)((m_IpAddress>>24)&0xff);
	ip[1] = (unsigned char)((m_IpAddress>>16)&0xff);
	ip[2] = (unsigned char)((m_IpAddress>>8)&0xff);
	ip[3] = (unsigned char)((m_IpAddress)&0xff);	
	sprintf(m_StrIpAddress,"%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
	
	return true;
}

/******************************************************/
/*           NetChannel Factory                                                    */
/******************************************************/
int C_ChannelFactory::m_ChNum = 0;
C_Channel* 	C_ChannelFactory::m_Channel[MAX_CHANNEL_NUM];

/*
brief: 根据IP和端口获取网络通道句柄
param [in]unsigned long IpAddress:网络地址
param [in]int NetPort:端口号
return C_Channel* 网络通道句柄
author:Steven Wan
date: 2015-05-04
*/ 
C_Channel* C_ChannelFactory::GetChannel(unsigned long IpAddress,int NetPort)
{
	for (int i=0; i<m_ChNum; i++)
	{
		if (m_Channel[i]->Match(IpAddress, NetPort) == true)
		{
			return m_Channel[i];
		}
	}
	/* 通道在通道列表中没找到，需创建并存入列表*/
	if (CreateChannel(IpAddress,NetPort) == true)
	{
		return m_Channel[m_ChNum-1];
	}
	return NULL;
}

/*
brief: 根据IP和端口实例化一个通道，并设置网络参数
param [in]unsigned long IpAddress:网络地址
param [in]int NetPort:端口号
return bool:true,成功。false,失败
author:Steven Wan
date: 2015-05-04
*/ 
bool C_ChannelFactory::CreateChannel(unsigned long IpAddress,int NetPort)
{
	if (m_ChNum == MAX_CHANNEL_NUM)
	{
		return false;
	}
	m_Channel[m_ChNum] = new C_NetChannel();
	m_Channel[m_ChNum] ->SetChannel(IpAddress,NetPort);
	m_ChNum++;
	TRACE("Address %d\n",&m_Channel);
	return true;
}

/*
brief: 关闭所有通信通道
param [in]空
param [in]空
return void:空
author:Steven Wan
date: 2015-05-04
*/ 
void C_ChannelFactory::CloseAllChannels()
{
	for (int i = 0;i < m_ChNum;i++)
	{
		m_Channel[i]->Close();
	}
}










