#ifndef TRANS_DATA_TYPE_H
#define  TRANS_DATA_TYPE_H
//*****************************************************************************************
#define FRAME_START_FLAG	0x68			//֡��ʼ�ַ�
#define FRAME_END_FLAG		0x16			//֡�����ַ�
//=================================================================================
static char ErrString[][64] = {"��ȷ���޴���","����û�з���","�������ݷǷ�",\
"����Ȩ�޲���","�޴�������","����ʱ��ʧЧ","Ŀ���ַ������","����ʧ��","����Ϣ̫֡��"};

enum _MODULE_TYPE_DEF
{
	MODULE_RESERVED = 0,		//����
	MODULE_KEY_BOEAD,			//����
	MODULE_OUTPUT,				//����ͼ̵���
	MODULE_IO_REGISTER,			//��������ͼ̵���
	MODULE_DOOR,				//�ſ�
	MODULE_AIRCONDITION			//�յ�
};

enum COMMAND_DESCRIPTION_BLOCK
{
//�������ָ��
	CMD_QUEST_SET_DEVICE_NODE = 0x08,		//��/ɾ/���豸�ڵ�(����������)


	CMD_QUEST_ALL_STATUS_INFO = 0x2F,	//�������еķ�̬��Ϣ
	CMD_QUEST_ALL_DEVICE_INFO = 0x1F,	//�������е��豸��Ϣ	
	CMD_QUEST_ALL_INFO = 0x7F			//�������е���Ϣ
};
//==================================================================================
//**********************************************************************************
#pragma pack(push,1)
//֡ͷ��һ���ֽ�
typedef struct _DATA_TRANS_PRE		//[11] BYTES
{
	UCHAR	bStartFrame;			//[00]֡��ʼ						//��ֵ0x68
	ULONG	dwRtua;					//[01-04]RCU���߼���ַ			
	USHORT	wMstaAndSeq;			//[05-06]��վ��ַ���������
	UCHAR	bFrameFlag;				//[07]֡��ʶ��						//��ֵ0x68
	UCHAR	bCtrlCode;				//[08]������
	USHORT	wTransLength;			//[09-0A]���ݳ���
	USHORT	wTestNodeIndex;			//[0B-0C]�豸�ڵ��
	ULONG	uLevel:8;				//[0D]Ȩ�޵ȼ�
	ULONG	uPasswords:24;			//[0E-10]����
}DATA_TRANS_PRE,*PDATA_TRANS_PRE;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct _DATA_TRANS_OP		//[2] BYTES
{
	#ifdef cdebug
	UCHAR	btestflag[2];		//for debug 0x2211;
#endif
	USHORT  wDataCoding;
	UCHAR	bOPType;			//�������ͣ�0 ���� ��1 �޸ģ�2 ɾ����
	UCHAR	bDeviceNum;	  //�豸���� ɾ��RCUȫ������ �� 0x00��
}DATA_TRANS_OP,*PDATA_TRANS_OP;

typedef struct _DATA_TRANS_HEAD  //[11] BYTES
{
	#ifdef cdebug
	UCHAR	btestflag[2];  // for debug 0x4433
#endif
	UCHAR	bNodeIndex;	//�豸�ڵ��ţ�
	ULONG	dwNodeAddr_L; //�豸�ڵ��ַ? low 4bytes  <- ���õõ�
	USHORT	wNodeAddr_H; //�豸�ڵ��ַ��  hight 2bytes <-����
	UCHAR	bFuncType;	//��������
	UCHAR	bDevType;	 // �豸����
	UCHAR	bTranParam;	//ͨѶ������
	UCHAR	bDevListNum;	//�����豸����
}DATA_TRANS_HEAD,*PDATA_TRANS_HEAD;

typedef struct _DEV_INFO	//[7]  BYTES
{
#ifdef cdebug
	UCHAR	btestflag[2];  // for debug 0x6655
#endif
	UCHAR	bDevNodeID; //�豸��·�ţ�1-32����
	UCHAR	bSpeFunc;	//���⹦�ܶ��壻
	UCHAR	bLinkDevID;	//��·�������豸�ڵ��ţ�1-16����
	ULONG	dwLinkDevLink; //��·�������豸��·�ţ�	
}DEV_INFO, *PDEV_INFO;
#pragma pack(pop)

//֡β�������ֽ�
#pragma pack(push,1)
typedef struct _DATA_TRANS_POST		//[2]	BYTES
{
	UCHAR	bCS;
	UCHAR	bEndFrame;				//��ֵ0x16
}DATA_TRANS_POST,*PDATA_TRANS_POST;
#pragma pack(pop)
//=====================================================================
//�����ѯ���ݵ�֡
//=====================================================================
#pragma pack(push,1)
typedef struct _QUERY_RCU_FRAM		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]֡��ʼ						//��ֵ0x68
	ULONG	dwRtua;					//[01-04]RCU���߼���ַ			
	USHORT	wMstaAndSeq;			//[05-06]��վ��ַ���������
	UCHAR	bFrameFlag;				//[07]֡��ʶ��						//��ֵ0x68
	UCHAR	bCtrlCode;				//[08]������
	USHORT	wTransLength;			//[09-0A]���ݳ���
	__int64 lwTnm;					//[0B-12]�������־

	USHORT	uEntry[255];		//��������

	DATA_TRANS_POST sPostFrame;			//֡β	
}QUERY_RCU_FRAM,*PQUERY_RCU_FRAM;
#pragma pack(pop)
//=====================================================================
//���ýڵ��ķ���֡
//=====================================================================
#pragma pack(push,1)
typedef struct _RESPONSE_FRAM		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]֡��ʼ
	ULONG	dwRtua;					//[01-04]RCU���߼���ַ	
	USHORT	wMstaAndSeq;			//[05-06]��վ��ַ���������
	UCHAR	bFrameFlag;				//[07]֡��ʶ��						//��ֵ0x68
	UCHAR	bCtrlCode;				//[08]������
	USHORT	wTransLength;			//[09-0A]���ݳ���
//	UCHAR	pData[];
}RESPONSE_FRAM,*PRESPONSE_FRAM;
#pragma pack(pop)

//=====================================================================
//��ȡRCU�����Ľṹ
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_GET_REQ_PACK		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]֡��ʼ						//��ֵ0x68
	ULONG	dwRtua;					//[01-04]RCU���߼���ַ			
	USHORT	wMstaAndSeq;			//[05-06]��վ��ַ���������
	UCHAR	bFrameFlag;				//[07]֡��ʶ��						//��ֵ0x68
	UCHAR	bCtrlCode;				//[08]������
	USHORT	wTransLength;			//[09-0A]���ݳ���
	__int64 lwTnm;					//[0B-12]�������־

	USHORT	uEntryA;					//��������0101
	USHORT	uEntryB;					//��������0102
	USHORT	uEntryC;					//��������0103
	//USHORT	uEntryD;					//��������0104
	//USHORT	uEntryE;					//��������0105
	USHORT	uEntryF;					//��������0108
	USHORT	uEntryG;					//��������0109
	DATA_TRANS_POST sPostFrame;			//��β	
}RCU_ARG_GET_REQ_PACK,*PRCU_ARG_GET_REQ_PACK;
#pragma pack(pop)
//*******************************************************
//��ȡ�����ĵķ��ؽṹ
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_GET_RES_PACK		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]֡��ʼ						//��ֵ0x68
	ULONG	dwRtua;					//[01-04]RCU���߼���ַ			
	USHORT	wMstaAndSeq;			//[05-06]��վ��ַ���������
	UCHAR	bFrameFlag;				//[07]֡��ʶ��						//��ֵ0x68
	UCHAR	bCtrlCode;				//[08]������
	USHORT	wTransLength;			//[09-0A]���ݳ���
	__int64 lwTnm;					//[0B-12]�������־

	USHORT	uEntryA;					//��������0101
	DWORD	dwTime;						//ҹ��ʱ��
	USHORT	uEntryB;					//��������0102
	UCHAR	bLightPercent;				//�ưٷֱ�
	USHORT	uEntryC;					//��������0103
	UCHAR	bMotorRumTimes;				//�������ʱ��
	//USHORT	uEntryD;					//��������0104
	//UCHAR	bSeasonKeyword;				//ʱ����
	//USHORT	uEntryE;					//��������0105
	//USHORT	wTemerature;				//�¶�
	USHORT	uEntryF;					//��������0108
	UCHAR	bAccessCard;				//�ſ�
	USHORT  uEntryG;					//��������0109
	UCHAR	bIrTime;					//������������ж�ʱ��

	DATA_TRANS_POST sPostFrame;			//��β	
}RCU_ARG_GET_RES_PACK,*PRCU_ARG_GET_RES_PACK;
#pragma pack(pop)

//=====================================================================
//��ȡRCU�����豸�Ľṹ��Լ 0202
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_GET_REQ_PACK_0202		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]֡��ʼ						//��ֵ0x68
	ULONG	dwRtua;					//[01-04]RCU���߼���ַ			
	USHORT	wMstaAndSeq;			//[05-06]��վ��ַ���������
	UCHAR	bFrameFlag;				//[07]֡��ʶ��						//��ֵ0x68
	UCHAR	bCtrlCode;				//[08]������
	USHORT	wTransLength;			//[09-0A]���ݳ���
	__int64 lwTnm;					//[0B-12]�������־

	USHORT	uEntryA;					//��������0202
	DATA_TRANS_POST sPostFrame;			//��β	
}RCU_ARG_GET_REQ_PACK_0202,*PRCU_ARG_GET_REQ_PACK_0202;
#pragma pack(pop)
//*******************************************************
//��ȡ0202��Լ�ķ��ؽṹ
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_GET_RES_PACK_0202		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]֡��ʼ						//��ֵ0x68
	ULONG	dwRtua;					//[01-04]RCU���߼���ַ			
	USHORT	wMstaAndSeq;			//[05-06]��վ��ַ���������
	UCHAR	bFrameFlag;				//[07]֡��ʶ��						//��ֵ0x68
	UCHAR	bCtrlCode;				//[08]������
	USHORT	wTransLength;			//[09-0A]���ݳ���
	__int64 lwTnm;					//[0B-12]�������־

	USHORT	uEntryA;				//��������0202
	UCHAR   bCount;					//�豸���� ���Ϊ15
	UCHAR	bContent[150];			//�豸״̬����

	DATA_TRANS_POST sPostFrame;		//��β	
}RCU_ARG_GET_RES_PACK_0202,*PRCU_ARG_GET_RES_PACK_0202;
#pragma pack(pop)

//=====================================================================
//��ȡ�յ������Ľṹ  �ɰ��Լ
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_AIR_GET_REQ_PACK		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]֡��ʼ						//��ֵ0x68
	ULONG	dwRtua;					//[01-04]RCU���߼���ַ			
	USHORT	wMstaAndSeq;			//[05-06]��վ��ַ���������
	UCHAR	bFrameFlag;				//[07]֡��ʶ��						//��ֵ0x68
	UCHAR	bCtrlCode;				//[08]������
	USHORT	wTransLength;			//[09-0A]���ݳ���
	__int64 lwTnm;					//[0B-12]�������־

	USHORT	uEntryA;					//��������0104
	USHORT  uEntryB;					//��������0107
	DATA_TRANS_POST sPostFrame;			//��β	
}RCU_ARG_AIR_GET_REQ_PACK,*PRCU_ARG_AIR_GET_REQ_PACK;
#pragma pack(pop)

//*******************************************************
//��ȡ�յ������ķ��ؽṹ   �ɰ��Լ
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_AIR_GET_RES_PACK		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]֡��ʼ						//��ֵ0x68
	ULONG	dwRtua;					//[01-04]RCU���߼���ַ			
	USHORT	wMstaAndSeq;			//[05-06]��վ��ַ���������
	UCHAR	bFrameFlag;				//[07]֡��ʶ��						//��ֵ0x68
	UCHAR	bCtrlCode;				//[08]������
	USHORT	wTransLength;			//[09-0A]���ݳ���
	__int64 lwTnm;					//[0B-12]�������־

	USHORT	uEntryA;					//��������0104
	UCHAR	ucSeason;					//����ģʽ
	USHORT	uEntryB;					//��������0104
	UCHAR	ucSettingTempl;				//�յ������¶�
	UCHAR	ucTempl;					//�����¶�
	UCHAR	ucFanSpeed;					//�յ�����
	DATA_TRANS_POST sPostFrame;			//��β	
}RCU_ARG_AIR_GET_RES_PACK,*PRCU_ARG_AIR_GET_RES_PACK;
#pragma pack(pop)

//=====================================================================
//��ȡ�յ������Ľṹ  �°��Լ
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_AIR_GET_REQ_PACK_021X		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]֡��ʼ						//��ֵ0x68
	ULONG	dwRtua;					//[01-04]RCU���߼���ַ			
	USHORT	wMstaAndSeq;			//[05-06]��վ��ַ���������
	UCHAR	bFrameFlag;				//[07]֡��ʶ��						//��ֵ0x68
	UCHAR	bCtrlCode;				//[08]������
	USHORT	wTransLength;			//[09-0A]���ݳ���
	__int64 lwTnm;					//[0B-12]�������־

	UCHAR	bCodeA;					//����021X
	UCHAR	bCodeB;					
	DATA_TRANS_POST sPostFrame;			//��β	
}RCU_ARG_AIR_GET_REQ_PACK_021X,*PRCU_ARG_AIR_GET_REQ_PACK_021X;
#pragma pack(pop)

//*******************************************************
//��ȡ�յ������ķ��ؽṹ   �°��Լ
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_AIR_GET_RES_PACK_021X		//[2]	BYTES
{
	UCHAR	bStartFrame;			//[00]֡��ʼ						//��ֵ0x68
	ULONG	dwRtua;					//[01-04]RCU���߼���ַ			
	USHORT	wMstaAndSeq;			//[05-06]��վ��ַ���������
	UCHAR	bFrameFlag;				//[07]֡��ʶ��						//��ֵ0x68
	UCHAR	bCtrlCode;				//[08]������
	USHORT	wTransLength;			//[09-0A]���ݳ���
	__int64 lwTnm;					//[0B-12]�������־

	UCHAR	bCodeA;					//����021X
	UCHAR	bCodeB;					
	UCHAR   bType;					//���ͱ���
	UCHAR	bContent[8];			//��ȡ��״̬

	DATA_TRANS_POST sPostFrame;			//��β	
}RCU_ARG_AIR_GET_RES_PACK_021X,*PRCU_ARG_AIR_GET_RES_PACK_021X;
#pragma pack(pop)

//*******************************************************
//���ÿյ������Ľṹ
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_AIR_SET_REQ_PACK_021X		//[2]	BYTES
{
	DATA_TRANS_PRE	sPreFrame;			//֡ͷ

	UCHAR	bCodeA;					//����021X
	UCHAR	bCodeB;					
	UCHAR	bType;
	UCHAR	bContent[8];			//Ҫд���״̬

	DATA_TRANS_POST sPostFrame;			//��β	
}RCU_ARG_AIR_SET_REQ_PACK_021X,*PRCU_ARG_AIR_SET_REQ_PACK_021X;
#pragma pack(pop)


//*******************************************************
//�����豸�����Ľṹ
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_SET_REQ_PACK_0201		//[2]	BYTES
{
	DATA_TRANS_PRE	sPreFrame;			//֡ͷ

	UCHAR	bCodeA;					//����0201
	UCHAR	bCodeB;					
	UCHAR	bCount;
	UCHAR	bContent[105];			//Ҫд���״̬

	DATA_TRANS_POST sPostFrame;			//��β	
}RCU_ARG_SET_REQ_PACK_0201,*PRCU_ARG_SET_REQ_PACK_0201;
#pragma pack(pop)

//*******************************************************
//����RCU�����Ľṹ
//*******************************************************
#pragma pack(push,1)
typedef struct _RCU_ARG_SET_REQ_PACK		//[2]	BYTES
{
	DATA_TRANS_PRE	sPreFrame;			//֡ͷ
	USHORT	uEntryA;					//��������0101
	DWORD	dwTime;						//ҹ��ʱ��
	USHORT	uEntryB;					//��������0102
	UCHAR	bLightPercent;				//�ưٷֱ�
	USHORT	uEntryC;					//��������0103
	UCHAR	bMotorRumTimes;				//�������ʱ��
	//USHORT	uEntryD;					//��������0104
	//UCHAR	bSeasonKeyword;				//ʱ����
	//USHORT	uEntryE;					//��������0105
	//USHORT	wTemerature;				//�¶�
	USHORT	uEntryF;					//��������0108
	UCHAR	bAccessCard;				//�ſ�
	USHORT  uEntryG;					//��������0109
	UCHAR	bIrTime;					//������������ж�ʱ��
	DATA_TRANS_POST sPostFrame;			//��β	
}RCU_ARG_SET_REQ_PACK,*PRCU_ARG_SET_REQ_PACK;
#pragma pack(pop)
#pragma pack(push,1)
typedef struct _RCU_ARG_SET_RES_UNIT
{
	USHORT	uEntry;
	UCHAR	bResult;
}RCU_ARG_SET_RES_UNIT,*PRCU_ARG_SET_RES_UNIT;
#pragma pack(pop)
//RCUУʱ�����
#pragma pack(push,1)
typedef struct _RCU_SET_TIMIMG_PACK
{
	DATA_TRANS_PRE sPreFrame;			//֡ͷ;
	USHORT	wDataEntry;					//��������
	UCHAR	bSecond;
	UCHAR	bMinute;
	UCHAR	bHour;
	UCHAR	bDay;
	UCHAR	bMonth;
	UCHAR	bYear;
	DATA_TRANS_POST sPostFrame;			//��β	
}RCU_SET_TIMIMG_PACK,*PRCU_SET_TIMIMG_PACK;

#pragma pack(push,1)
//===================================================
// ����ת���������ݣ�Ԥ�����ֲ������ݣ�

typedef struct _INPUT_DATA
{
	//=====Ԥ��������ʱֵ==================================
	// ǰ׺���֣�
	UCHAR bCode ;	
	USHORT wFloor;
	USHORT wRoom ;
	UCHAR bMSTA ;
	UCHAR bSEQ ;
	
	//895d���ݱ��벿�֣�
	UCHAR bOPType ;	//�������ͣ�0������1�޸ģ�2ɾ����
	UCHAR bFuncType; //�������ͣ�0 ������1�������ͣ�2�����ʾ���ͣ� 
	UCHAR bTranParam; //ͨѶ������1��1200��2-2400��3-4800��4-9600��5-19200
	UCHAR bDevId[6];
	//=================================================
	//PROOM_CONFIG_INFO  pRoomConfigInfo;
	LPVOID pRoomConfigInfo;
}INPUT_DATA, *PINPUT_DATA;
#pragma pack(pop)
//============================================================================
//****************************************************************************
//���涨��������ݵ�����
#pragma pack(push,1)
typedef struct _RCU_DATA_FORMAT_0106
{
	WORD	pEntryCode;
	DWORD	bEmergencyBtnStatus:1;				//������ť״̬��0��δ���£�1���Ѱ���
	DWORD	bCardInsertStatus:1;				//�����ſ�����״̬��0��δ�忨��1�Ѳ忨
	DWORD	bDoorContactCheck:1;				//������Ŵż�⣺0�����Źأ�1���ſ�
	DWORD	bGolabSwitch:1;						//�ܵ�Դ����״̬��0���أ�1����
	DWORD	bCorridorlampSwitch:1;				//�ȵƿ���״̬ 0���أ�1����
	DWORD	bNightlightSwitch:1;				//ҹ�ƿ���״̬ 0���أ�1����
	DWORD	bAirConditionSeasonStatus:1;		//�յ�����״̬ 0���ļ���1������
	DWORD	bClearStatus:1;						//������״̬ 0���أ�1����
	DWORD	bWashingSeviceStatus:1;				//ϴ�·���ť״̬0���أ�1����
	DWORD	bResv:13;
}RCU_DATA_FORMAT_0106,*PRCU_DATA_FORMAT_0106;


typedef struct _RCU_DATA_FORMAT_0107
{
	WORD	pEntryCode;
	UCHAR	bRoomTemperature;				//�����¶�
	UCHAR	bAirConditionTemperature;		//�յ��¶�
}RCU_DATA_FORMAT_0107,*PRCU_DATA_FORMAT_0107;
#pragma pack(pop)

//***************************************************************************************************
//����У���
BYTE Crc8(PUCHAR pBuf,ULONG uLength);	
//�ֽڱ���ת��	
BYTE atoh(char Charect);
unsigned long BCD2_DWORD(unsigned long dwValue);
unsigned long DWORD2_BCD(unsigned long dwValue);
unsigned long ToLittleEndian(DWORD dwBigEndian);

// ��ȡ�յ�����  �ɰ��Լ
DWORD GetAirRCUargPacket(LPVOID lParam);


// ��ȡ�յ�����  �°��Լ
DWORD GetAirConditionPacket(LPVOID lParam,int airNum);
DWORD SetAirConditionPacket(LPVOID lParam,int airNum);

// ��ȡ�豸״̬
DWORD GetDeviceStatusPacket(LPVOID lParam,int deviceNum);
DWORD SetDeviceStatusPacket(LPVOID lParam,int deviceNum,int deviceType);

//����ת����һ���������Ķ�ȡ������
DWORD SetRCUargPacket(LPVOID lParam);
DWORD GetRCUargPacket(LPVOID lParam);

//�����豸״̬����
DWORD SetDeviceSwitchStatusPacket(LPVOID lParam,int deviceCount);

//�����Ķ�ȡ��0202��Լ�����豸״̬�Ķ�ȡ
DWORD GetRCUargPacket0202(LPVOID lParam);

//RCUУʱ����0x8030
DWORD SetRCUtimingPacket(PBYTE pBuf,CTime mt);



//��վ����֡��ת��
DWORD QuiryRCUFramePack(PBYTE pBuf,unsigned short *pDataEntry,int iNum,DWORD dwRtua=0x00000000,WORD wMsta=0x0000,__int64 lpTnm=0x00000001);

















void RecordBuffer(char *pFileName,PUCHAR pBuf,ULONG pLength);

void FillPreBuffer(INPUT_DATA *pInput, PDATA_TRANS_PRE pPreBuf);
void FillPreBuffer(PDATA_TRANS_PRE pPreBuf,UCHAR bCode,USHORT Floor,USHORT Room,UCHAR bMSTA=0,UCHAR bSEQ=0);
void FillPostBuffer(PUCHAR pDataBuf,ULONG pLength);				//����У��ͽ���

ULONG ConvertInputDataToSendBuf(PINPUT_DATA pInput, PUCHAR pBuf, UCHAR bflag);


DWORD FillClearAllCfgPack(PINPUT_DATA pInput, PUCHAR pBuf, UCHAR bflag);
//ULONG ConvertInputDataToSendBuf(PUCHAR &pSendBuf,PDATA_TRANS_PRE pPreFrame,PUCHAR pInBuf,ULONG uInLength);
//**************************************************************************************************
#endif
