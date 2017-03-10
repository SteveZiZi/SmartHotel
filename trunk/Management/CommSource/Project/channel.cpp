#include "channel.h"
#include "StdAfx.h"
/*
brief: ����SOCKET���ӣ�������ͨѶ��
param [in]void
return bool:true,�����ɹ���false������ʧ�ܡ�
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
		if((DataSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) //����ʧ��
		{
			m_bOpened = false;
			return false;
		}
		TIMEVAL tv_out;
		tv_out.tv_sec = 1;
		tv_out.tv_usec = 0;
		nRet = setsockopt(DataSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv_out, sizeof(tv_out));
		ConnectTimes = 1;
		while (ConnectTimes < 3)//�������Դ���3��
		{
			nRet = connect(DataSocket,(PSOCKADDR)&inetAddr,sizeof(inetAddr));//����
			if (nRet == SOCKET_ERROR)//����ʧ��
			{
				ConnectTimes++;
				Sleep(100);
			}
			else//�����ɹ�
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
brief: socket�������ݽӿ�
param [in]char* sData:�������ݻ�����ָ��
param [in]long sLength:���������ݳ���
return bool:true,�ɹ���false��ʧ�ܡ�
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
			if(SendLength == SOCKET_ERROR ) //���ʹ���
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
			else//���ͳɹ�
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
brief: socket�������ݽӿ�
param [in]char* sData:�������ݻ�����ָ��
param [in]long MaxLength:���ջ�������󳤶�
return long:ʵ�ʽ����ֽ���
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
brief: �жϸ�IP�Ͷ˿�һ�µ�ͨ�������Ƿ����
param [in]unsigned long IpAddress:IP��ַ
param [in]INT NetPort:�˿ں�
return bool:true,һ�¡�false����һ�¡�
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
brief: �ر�����ͨ��
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
brief: ��������ͨѶ����
param [in]unsigned long IpAddress:�����ַ
param [in]int NetPort:�˿ں�
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
brief: ����IP�Ͷ˿ڻ�ȡ����ͨ�����
param [in]unsigned long IpAddress:�����ַ
param [in]int NetPort:�˿ں�
return C_Channel* ����ͨ�����
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
	/* ͨ����ͨ���б���û�ҵ����贴���������б�*/
	if (CreateChannel(IpAddress,NetPort) == true)
	{
		return m_Channel[m_ChNum-1];
	}
	return NULL;
}

/*
brief: ����IP�Ͷ˿�ʵ����һ��ͨ�����������������
param [in]unsigned long IpAddress:�����ַ
param [in]int NetPort:�˿ں�
return bool:true,�ɹ���false,ʧ��
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
brief: �ر�����ͨ��ͨ��
param [in]��
param [in]��
return void:��
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










