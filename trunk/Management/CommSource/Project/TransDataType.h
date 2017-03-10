#ifndef TRANS_DATA_TYPE_H
#define  TRANS_DATA_TYPE_H
//*****************************************************************************************
#define FRAME_START_FLAG	0x68			//帧起始字符
#define FRAME_END_FLAG		0x16			//帧结束字符
//=================================================================================
static char ErrString[][64] = {"正确，无错误","命令没有返回","设置内容非法",\
"密码权限不足","无此项数据","命令时间失效","目标地址不存在","发送失败","短消息帧太长"};

enum _MODULE_TYPE_DEF
{
	MODULE_RESERVED = 0,		//保留
	MODULE_KEY_BOEAD,			//键盘
	MODULE_OUTPUT,				//输出型继电器
	MODULE_IO_REGISTER,			//输入输出型继电器
	MODULE_DOOR,				//门卡
	MODULE_AIRCONDITION			//空调
};

enum COMMAND_DESCRIPTION_BLOCK
{
//设置类的指令
	CMD_QUEST_SET_DEVICE_NODE = 0x08,		//增/删/改设备节点(单个和批量)


	CMD_QUEST_ALL_STATUS_INFO = 0x2F,	//请求所有的房态信息
	CMD_QUEST_ALL_DEVICE_INFO = 0x1F,	//请求所有的设备信息	
	CMD_QUEST_ALL_INFO = 0x7F			//请求所有的信息
};
//==================================================================================
//**********************************************************************************
#pragma pack(push,1)
//帧头的一堆字节
typedef struct _DATA_TRANS_PRE		//[11] BYTES
{
	UCHAR	bStartFrame;			//[00]帧起始						//定值0x68
	ULONG	dwRtua;					//[01-04]RCU的逻辑地址			
	USHORT	wMstaAndSeq;			//[05-06]主站地址与命令序号
	UCHAR	bFrameFlag;				//[07]帧标识符						//定值0x68
	UCHAR	bCtrlCode;				//[08]控制码
	USHORT	wTransLength;			//[09-0A]数据长度
	USHORT	wTestNodeIndex;			//[0B-0C]设备节点号
	ULONG	uLevel:8;				//[0D]权限等级
	ULONG	uPasswords:24;			//[0E-10]密码
}DATA_TRANS_PRE,*PDATA_TRANS_PRE;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct _DATA_TRANS_OP		//[2] BYTES
{
	#ifdef cdebug
	UCHAR	btestflag[2];		//for debug 0x2211;
#endif
	USHORT  wDataCoding;
	UCHAR	bOPType;			//操作类型：0 新增 ；1 修改；2 删除；
	UCHAR	bDeviceNum;	  //设备数； 删除RCU全部档案 ＝ 0x00；
}DATA_TRANS_OP,*PDATA_TRANS_OP;

typedef struct _DATA_TRANS_HEAD  //[11] BYTES
{
	#ifdef cdebug
	UCHAR	btestflag[2];  // for debug 0x4433
#endif
	UCHAR	bNodeIndex;	//设备节点编号；
	ULONG	dwNodeAddr_L; //设备节点地址? low 4bytes  <- 配置得到
	USHORT	wNodeAddr_H; //设备节点地址；  hight 2bytes <-补零
	UCHAR	bFuncType;	//功能类型
	UCHAR	bDevType;	 // 设备类型
	UCHAR	bTranParam;	//通讯参数；
	UCHAR	bDevListNum;	//关联设备数；
}DATA_TRANS_HEAD,*PDATA_TRANS_HEAD;

typedef struct _DEV_INFO	//[7]  BYTES
{
#ifdef cdebug
	UCHAR	btestflag[2];  // for debug 0x6655
#endif
	UCHAR	bDevNodeID; //设备子路号（1-32）；
	UCHAR	bSpeFunc;	//特殊功能定义；
	UCHAR	bLinkDevID;	//子路关联的设备节点编号（1-16）；
	ULONG	dwLinkDevLink; //子路关联的设备子路号；	
}DEV_INFO, *PDEV_INFO;
#pragma pack(pop)

//帧尾的两个字节
#pragma pack(push,1)
typedef struct _DATA_TRANS_POST		//[2]	BYTES
{
	UCHAR	bCS;
	UCHAR	bEndFrame;				//定值0x16
}DATA_TRANS_POST,*PDATA_TRANS_POST;
#pragma pack(pop)
//=====================================================================
//请求查询数据的帧
//=====================================================================
#pragma pack(push,1)
typedef struct _QUERY_RCU_FRAM		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]帧起始						//定值0x68
	ULONG	dwRtua;					//[01-04]RCU的逻辑地址			
	USHORT	wMstaAndSeq;			//[05-06]主站地址与命令序号
	UCHAR	bFrameFlag;				//[07]帧标识符						//定值0x68
	UCHAR	bCtrlCode;				//[08]控制码
	USHORT	wTransLength;			//[09-0A]数据长度
	__int64 lwTnm;					//[0B-12]测量点标志

	USHORT	uEntry[255];		//数据项编号

	DATA_TRANS_POST sPostFrame;			//帧尾	
}QUERY_RCU_FRAM,*PQUERY_RCU_FRAM;
#pragma pack(pop)
//=====================================================================
//设置节点后的返回帧
//=====================================================================
#pragma pack(push,1)
typedef struct _RESPONSE_FRAM		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]帧起始
	ULONG	dwRtua;					//[01-04]RCU的逻辑地址	
	USHORT	wMstaAndSeq;			//[05-06]主站地址与命令序号
	UCHAR	bFrameFlag;				//[07]帧标识符						//定值0x68
	UCHAR	bCtrlCode;				//[08]控制码
	USHORT	wTransLength;			//[09-0A]数据长度
//	UCHAR	pData[];
}RESPONSE_FRAM,*PRESPONSE_FRAM;
#pragma pack(pop)

//=====================================================================
//读取RCU参数的结构
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_GET_REQ_PACK		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]帧起始						//定值0x68
	ULONG	dwRtua;					//[01-04]RCU的逻辑地址			
	USHORT	wMstaAndSeq;			//[05-06]主站地址与命令序号
	UCHAR	bFrameFlag;				//[07]帧标识符						//定值0x68
	UCHAR	bCtrlCode;				//[08]控制码
	USHORT	wTransLength;			//[09-0A]数据长度
	__int64 lwTnm;					//[0B-12]测量点标志

	USHORT	uEntryA;					//数据项编号0101
	USHORT	uEntryB;					//数据项编号0102
	USHORT	uEntryC;					//数据项编号0103
	//USHORT	uEntryD;					//数据项编号0104
	//USHORT	uEntryE;					//数据项编号0105
	USHORT	uEntryF;					//数据项编号0108
	USHORT	uEntryG;					//数据项编号0109
	DATA_TRANS_POST sPostFrame;			//帖尾	
}RCU_ARG_GET_REQ_PACK,*PRCU_ARG_GET_REQ_PACK;
#pragma pack(pop)
//*******************************************************
//读取参数的的返回结构
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_GET_RES_PACK		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]帧起始						//定值0x68
	ULONG	dwRtua;					//[01-04]RCU的逻辑地址			
	USHORT	wMstaAndSeq;			//[05-06]主站地址与命令序号
	UCHAR	bFrameFlag;				//[07]帧标识符						//定值0x68
	UCHAR	bCtrlCode;				//[08]控制码
	USHORT	wTransLength;			//[09-0A]数据长度
	__int64 lwTnm;					//[0B-12]测量点标志

	USHORT	uEntryA;					//数据项编号0101
	DWORD	dwTime;						//夜间时段
	USHORT	uEntryB;					//数据项编号0102
	UCHAR	bLightPercent;				//灯百分比
	USHORT	uEntryC;					//数据项编号0103
	UCHAR	bMotorRumTimes;				//电机动行时间
	//USHORT	uEntryD;					//数据项编号0104
	//UCHAR	bSeasonKeyword;				//时令字
	//USHORT	uEntryE;					//数据项编号0105
	//USHORT	wTemerature;				//温度
	USHORT	uEntryF;					//数据项编号0108
	UCHAR	bAccessCard;				//门卡
	USHORT  uEntryG;					//数据项编号0109
	UCHAR	bIrTime;					//人体红外无人判断时间

	DATA_TRANS_POST sPostFrame;			//帖尾	
}RCU_ARG_GET_RES_PACK,*PRCU_ARG_GET_RES_PACK;
#pragma pack(pop)

//=====================================================================
//读取RCU所有设备的结构规约 0202
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_GET_REQ_PACK_0202		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]帧起始						//定值0x68
	ULONG	dwRtua;					//[01-04]RCU的逻辑地址			
	USHORT	wMstaAndSeq;			//[05-06]主站地址与命令序号
	UCHAR	bFrameFlag;				//[07]帧标识符						//定值0x68
	UCHAR	bCtrlCode;				//[08]控制码
	USHORT	wTransLength;			//[09-0A]数据长度
	__int64 lwTnm;					//[0B-12]测量点标志

	USHORT	uEntryA;					//数据项编号0202
	DATA_TRANS_POST sPostFrame;			//帖尾	
}RCU_ARG_GET_REQ_PACK_0202,*PRCU_ARG_GET_REQ_PACK_0202;
#pragma pack(pop)
//*******************************************************
//读取0202规约的返回结构
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_GET_RES_PACK_0202		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]帧起始						//定值0x68
	ULONG	dwRtua;					//[01-04]RCU的逻辑地址			
	USHORT	wMstaAndSeq;			//[05-06]主站地址与命令序号
	UCHAR	bFrameFlag;				//[07]帧标识符						//定值0x68
	UCHAR	bCtrlCode;				//[08]控制码
	USHORT	wTransLength;			//[09-0A]数据长度
	__int64 lwTnm;					//[0B-12]测量点标志

	USHORT	uEntryA;				//数据项编号0202
	UCHAR   bCount;					//设备个数 最大为15
	UCHAR	bContent[150];			//设备状态内容

	DATA_TRANS_POST sPostFrame;		//帖尾	
}RCU_ARG_GET_RES_PACK_0202,*PRCU_ARG_GET_RES_PACK_0202;
#pragma pack(pop)

//=====================================================================
//读取空调参数的结构  旧版规约
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_AIR_GET_REQ_PACK		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]帧起始						//定值0x68
	ULONG	dwRtua;					//[01-04]RCU的逻辑地址			
	USHORT	wMstaAndSeq;			//[05-06]主站地址与命令序号
	UCHAR	bFrameFlag;				//[07]帧标识符						//定值0x68
	UCHAR	bCtrlCode;				//[08]控制码
	USHORT	wTransLength;			//[09-0A]数据长度
	__int64 lwTnm;					//[0B-12]测量点标志

	USHORT	uEntryA;					//数据项编号0104
	USHORT  uEntryB;					//数据项编号0107
	DATA_TRANS_POST sPostFrame;			//帖尾	
}RCU_ARG_AIR_GET_REQ_PACK,*PRCU_ARG_AIR_GET_REQ_PACK;
#pragma pack(pop)

//*******************************************************
//读取空调参数的返回结构   旧版规约
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_AIR_GET_RES_PACK		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]帧起始						//定值0x68
	ULONG	dwRtua;					//[01-04]RCU的逻辑地址			
	USHORT	wMstaAndSeq;			//[05-06]主站地址与命令序号
	UCHAR	bFrameFlag;				//[07]帧标识符						//定值0x68
	UCHAR	bCtrlCode;				//[08]控制码
	USHORT	wTransLength;			//[09-0A]数据长度
	__int64 lwTnm;					//[0B-12]测量点标志

	USHORT	uEntryA;					//数据项编号0104
	UCHAR	ucSeason;					//季节模式
	USHORT	uEntryB;					//数据项编号0104
	UCHAR	ucSettingTempl;				//空调设置温度
	UCHAR	ucTempl;					//房间温度
	UCHAR	ucFanSpeed;					//空调风速
	DATA_TRANS_POST sPostFrame;			//帖尾	
}RCU_ARG_AIR_GET_RES_PACK,*PRCU_ARG_AIR_GET_RES_PACK;
#pragma pack(pop)

//=====================================================================
//读取空调参数的结构  新版规约
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_AIR_GET_REQ_PACK_021X		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]帧起始						//定值0x68
	ULONG	dwRtua;					//[01-04]RCU的逻辑地址			
	USHORT	wMstaAndSeq;			//[05-06]主站地址与命令序号
	UCHAR	bFrameFlag;				//[07]帧标识符						//定值0x68
	UCHAR	bCtrlCode;				//[08]控制码
	USHORT	wTransLength;			//[09-0A]数据长度
	__int64 lwTnm;					//[0B-12]测量点标志

	UCHAR	bCodeA;					//编码021X
	UCHAR	bCodeB;					
	DATA_TRANS_POST sPostFrame;			//帖尾	
}RCU_ARG_AIR_GET_REQ_PACK_021X,*PRCU_ARG_AIR_GET_REQ_PACK_021X;
#pragma pack(pop)

//*******************************************************
//读取空调参数的返回结构   新版规约
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_AIR_GET_RES_PACK_021X		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]帧起始						//定值0x68
	ULONG	dwRtua;					//[01-04]RCU的逻辑地址			
	USHORT	wMstaAndSeq;			//[05-06]主站地址与命令序号
	UCHAR	bFrameFlag;				//[07]帧标识符						//定值0x68
	UCHAR	bCtrlCode;				//[08]控制码
	USHORT	wTransLength;			//[09-0A]数据长度
	__int64 lwTnm;					//[0B-12]测量点标志

	UCHAR	bCodeA;					//编码021X
	UCHAR	bCodeB;					
	UCHAR   bType;					//类型编码
	UCHAR	bContent[8];			//读取的状态

	DATA_TRANS_POST sPostFrame;			//帖尾	
}RCU_ARG_AIR_GET_RES_PACK_021X,*PRCU_ARG_AIR_GET_RES_PACK_021X;
#pragma pack(pop)

//*******************************************************
//设置空调参数的结构
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_AIR_SET_REQ_PACK_021X		//[2]	BYTES
{
	DATA_TRANS_PRE	sPreFrame;			//帧头

	UCHAR	bCodeA;					//编码021X
	UCHAR	bCodeB;					
	UCHAR	bType;
	UCHAR	bContent[8];			//要写入的状态

	DATA_TRANS_POST sPostFrame;			//帖尾	
}RCU_ARG_AIR_SET_REQ_PACK_021X,*PRCU_ARG_AIR_SET_REQ_PACK_021X;
#pragma pack(pop)


//*******************************************************
//设置设备参数的结构
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_SET_REQ_PACK_0201		//[2]	BYTES
{
	DATA_TRANS_PRE	sPreFrame;			//帧头

	UCHAR	bCodeA;					//编码0201
	UCHAR	bCodeB;					
	UCHAR	bCount;
	UCHAR	bContent[105];			//要写入的状态

	DATA_TRANS_POST sPostFrame;			//帖尾	
}RCU_ARG_SET_REQ_PACK_0201,*PRCU_ARG_SET_REQ_PACK_0201;
#pragma pack(pop)

//*******************************************************
//设置RCU参数的结构
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_SET_REQ_PACK		//[2]	BYTES
{
	DATA_TRANS_PRE	sPreFrame;			//帧头
	USHORT	uEntryA;					//数据项编号0101
	DWORD	dwTime;						//夜间时段
	USHORT	uEntryB;					//数据项编号0102
	UCHAR	bLightPercent;				//灯百分比
	USHORT	uEntryC;					//数据项编号0103
	UCHAR	bMotorRumTimes;				//电机动行时间
	//USHORT	uEntryD;					//数据项编号0104
	//UCHAR	bSeasonKeyword;				//时令字
	//USHORT	uEntryE;					//数据项编号0105
	//USHORT	wTemerature;				//温度
	USHORT	uEntryF;					//数据项编号0108
	UCHAR	bAccessCard;				//门卡
	USHORT  uEntryG;					//数据项编号0109
	UCHAR	bIrTime;					//人体红外无人判断时间
	DATA_TRANS_POST sPostFrame;			//帖尾	
}RCU_ARG_SET_REQ_PACK,*PRCU_ARG_SET_REQ_PACK;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct _RCU_ARG_SET_RES_UNIT
{
	USHORT	uEntry;
	UCHAR	bResult;
}RCU_ARG_SET_RES_UNIT,*PRCU_ARG_SET_RES_UNIT;
#pragma pack(pop)
//RCU校时命令包
#pragma pack(push,1)
typedef struct _RCU_SET_TIMIMG_PACK
{
	DATA_TRANS_PRE sPreFrame;			//帧头;
	USHORT	wDataEntry;					//数据项编号
	UCHAR	bSecond;
	UCHAR	bMinute;
	UCHAR	bHour;
	UCHAR	bDay;
	UCHAR	bMonth;
	UCHAR	bYear;
	DATA_TRANS_POST sPostFrame;			//帖尾	
}RCU_SET_TIMIMG_PACK,*PRCU_SET_TIMIMG_PACK;

#pragma pack(push,1)
//===================================================
// 用于转换发送数据，预留部分参数传递；

typedef struct _INPUT_DATA
{
	//=====预留设置临时值==================================
	// 前缀部分：
	UCHAR bCode ;	
	USHORT wFloor;
	USHORT wRoom ;
	UCHAR bMSTA ;
	UCHAR bSEQ ;
	
	//895d数据编码部分：
	UCHAR bOPType ;	//操作类型：0新增；1修改；2删除；
	UCHAR bFuncType; //功能类型：0 保留；1控制类型；2面板显示类型； 
	UCHAR bTranParam; //通讯参数：1－1200；2-2400；3-4800；4-9600；5-19200
	UCHAR bDevId[6];
	//=================================================
	//PROOM_CONFIG_INFO  pRoomConfigInfo;
	LPVOID pRoomConfigInfo;
}INPUT_DATA, *PINPUT_DATA;
#pragma pack(pop)
//============================================================================
//****************************************************************************
//下面定义的是数据的类型
#pragma pack(push,1)
typedef struct _RCU_DATA_FORMAT_0106
{
	WORD	pEntryCode;
	DWORD	bEmergencyBtnStatus:1;				//紧急按钮状态：0，未按下，1，已按下
	DWORD	bCardInsertStatus:1;				//房间门卡插入状态：0，未插卡，1已插卡
	DWORD	bDoorContactCheck:1;				//房间大门磁检测：0，大门关，1大门开
	DWORD	bGolabSwitch:1;						//总电源开关状态：0：关，1：开
	DWORD	bCorridorlampSwitch:1;				//廊灯开关状态 0：关，1：开
	DWORD	bNightlightSwitch:1;				//夜灯开关状态 0：关，1：开
	DWORD	bAirConditionSeasonStatus:1;		//空调季节状态 0：夏季，1：冬季
	DWORD	bClearStatus:1;						//清理房间状态 0：关，1：开
	DWORD	bWashingSeviceStatus:1;				//洗衣服务按钮状态0：关，1：开
	DWORD	bResv:13;
}RCU_DATA_FORMAT_0106,*PRCU_DATA_FORMAT_0106;


typedef struct _RCU_DATA_FORMAT_0107
{
	WORD	pEntryCode;
	UCHAR	bRoomTemperature;				//房间温度
	UCHAR	bAirConditionTemperature;		//空调温度
}RCU_DATA_FORMAT_0107,*PRCU_DATA_FORMAT_0107;
#pragma pack(pop)

//***************************************************************************************************
//记算校验和
BYTE Crc8(PUCHAR pBuf,ULONG uLength);	
//字节编码转换	
BYTE atoh(char Charect);
unsigned long BCD2_DWORD(unsigned long dwValue);
unsigned long DWORD2_BCD(unsigned long dwValue);
unsigned long ToLittleEndian(DWORD dwBigEndian);

// 读取空调参数  旧版规约
DWORD GetAirRCUargPacket(LPVOID lParam);


// 读取空调参数  新版规约
DWORD GetAirConditionPacket(LPVOID lParam,int airNum);
DWORD SetAirConditionPacket(LPVOID lParam,int airNum);

// 读取设备状态
DWORD GetDeviceStatusPacket(LPVOID lParam,int deviceNum);
DWORD SetDeviceStatusPacket(LPVOID lParam,int deviceNum,int deviceType);

//数据转换第一步：参数的读取和设置
DWORD SetRCUargPacket(LPVOID lParam);
DWORD GetRCUargPacket(LPVOID lParam);

//设置设备状态函数
DWORD SetDeviceSwitchStatusPacket(LPVOID lParam,int deviceCount);

//参数的读取：0202规约所有设备状态的读取
DWORD GetRCUargPacket0202(LPVOID lParam);

//RCU校时功能0x8030
DWORD SetRCUtimingPacket(PBYTE pBuf,CTime mt);



//主站请求帧的转换
DWORD QuiryRCUFramePack(PBYTE pBuf,unsigned short *pDataEntry,int iNum,DWORD dwRtua=0x00000000,WORD wMsta=0x0000,__int64 lpTnm=0x00000001);

















void RecordBuffer(char *pFileName,PUCHAR pBuf,ULONG pLength);

void FillPreBuffer(INPUT_DATA *pInput, PDATA_TRANS_PRE pPreBuf);
void FillPreBuffer(PDATA_TRANS_PRE pPreBuf,UCHAR bCode,USHORT Floor,USHORT Room,UCHAR bMSTA=0,UCHAR bSEQ=0);
void FillPostBuffer(PUCHAR pDataBuf,ULONG pLength);				//增加校验和结束

ULONG ConvertInputDataToSendBuf(PINPUT_DATA pInput, PUCHAR pBuf, UCHAR bflag);


DWORD FillClearAllCfgPack(PINPUT_DATA pInput, PUCHAR pBuf, UCHAR bflag);
//ULONG ConvertInputDataToSendBuf(PUCHAR &pSendBuf,PDATA_TRANS_PRE pPreFrame,PUCHAR pInBuf,ULONG uInLength);
//**************************************************************************************************
#endif
