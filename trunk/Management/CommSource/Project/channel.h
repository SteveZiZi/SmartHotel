/************************************************************************
 * Copyright (c) XT Co., Ltd. 
 * All rights reserved. 
 *  
 * File Name：channel.h
 * Function：通道类为各种通讯方式提供统一的接口声明
 
 *
 * Author：Steven Wan
 * Date：2015-05-05
 * Version：1.0         
 *
 * Reversion: 
 * Author: 
 * Date: 
**************************************************************************/
#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include <afxmt.h>
#include <Winsock2.h>
#pragma comment(lib,"ws2_32.lib")				//这句关键;

/*****************************************************************************************\
*　通道对象基本类(派生出C_NetChannel,C_SerialChannel等)，作为通道的接口
\*****************************************************************************************/
class C_Channel
{
public:
	C_Channel(){}
	~C_Channel(){}
	virtual bool	Open()=0;
	virtual void	Close()=0;
	virtual bool	IsConnected()=0;
	virtual bool	SendData(char* sData,long sLendth)=0;
	virtual long	ReceiveData(char* sData,long sLength)=0;
	virtual bool	Match(unsigned long IpAddress,int NetPort)=0;
	virtual bool	SetChannel(unsigned long IpAddress,int NetPort)=0;
};

/*       网络通道   */
class C_NetChannel:public C_Channel
{
public:
	bool Open();
	void Close();
	bool IsConnected(){return m_bOpened;}
	bool SendData(char* sData,long sLength);
	long ReceiveData(char* sData,long MaxLength);
	bool	Match(unsigned long IpAddress,int NetPort);
	bool	SetChannel(unsigned long IpAddress,int NetPort);
private:
	bool m_bOpened;
	INT	m_NetPort;
	unsigned long m_IpAddress;
	char m_StrIpAddress[32];
	int	mEchoTerm;
	int	mDataTerm;
	int	mMaxSize;
	SOCKET DataSocket;				
};

/******************************************************/
/*           Channel Factory                                                         */
/******************************************************/
#define MAX_CHANNEL_NUM	500
class C_ChannelFactory
{
public :
	static C_Channel* GetChannel(unsigned long IpAddress,int NetPort);
	static bool CreateChannel(unsigned long IpAddress,int NetPort);
	static void CloseAllChannels();

private:
	static C_Channel* 	m_Channel[MAX_CHANNEL_NUM];
	static int m_ChNum;
};



#endif


