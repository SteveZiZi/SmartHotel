#pragma once
//==================================================================================
#define		MAX_MODULE_NUMBER				32				//���ģ�����
#define		MAX_MODULE_KEY_NUMBER			32				//ģ�����İ�����Ŀ
#define		MAX_CTRL_MODULE_NUMBER			16				//����ܿ�ģ�����
//**********************************************************************************
enum _KEY_ATTRIBUTE_VALUE
{
	ATTRIBUTE_UNDEFINE,				//δ����
	ATTRIBUTE_INPUT,				//����
	ATTRIBUTE_OUTPUT				//���
};

const char sKeyAttribute[][12] = {"N","I","O",""};







//==================================================================================
//�ܿ��豸�Ľṹ����
//��ʾ�����豸�е�����˿��Ƶ��豸�ṹ(��С��Ԫ)
#pragma pack(push,1)
typedef struct _CONTROL_DEVICE_UNIT
{
	BYTE bModuleEntry;			//ģ����(1-255)````0:��ʾ��Ч
	BYTE bSubModuleItem;		//ģ�����·

	BYTE bSpecialFundef;		//���⹦�ܶ���
	BYTE bReserved;				//����

	DWORD dwArgument;			//����
}CONTROL_DEVICE_UNIT,*PCONTROL_DEVICE_UNIT;
#pragma pack(pop)

//ģ����Ӽ�����ṹ����
#pragma pack(push,1)
typedef struct _CTRL_DEVICE_LIST
{
	BYTE	bNumber;		//��Ч����
	CONTROL_DEVICE_UNIT		mCtrlDev[MAX_CTRL_MODULE_NUMBER];
}CTRL_DEVICE_LIST,*PCTRL_DEVICE_LIST;

#pragma pack(pop)



#pragma pack(push,1)
typedef struct _MODULE_KEY_UNIT
{
	BYTE bEntry;				//�������(1-MAX_MODULE_KEY_NUMBER)````0:��ʾ��Ч
	BYTE bKeyAttribute;			//��������	_KEY_ATTRIBUTE_VALUE
	union _CONTENT{
		char pName[];
		CTRL_DEVICE_LIST mCtrlDeviceList;
		//struct _CTRL_DEVICE_LIST
		//{
		//	BYTE	bNumber;		//��Ч����
		//	CONTROL_DEVICE_UNIT		mCtrlDev[MAX_CTRL_MODULE_NUMBER];
		//}mCtrlDeviceList;
	}mContent;
}MODULE_KEY_UNIT,*PMODULE_KEY_UNIT;
#pragma pack(pop)
//====================================================================================================
//ģ��Ľṹ�Ķ��岿��
#pragma pack(push,1)
typedef struct _MODULE_ENTRY
{
	BYTE	bEntry;					//ģ����(1-MAX_MODULE_KEY_NUMBER)````0:��ʾ��Ч
	BYTE	bModuleType;
	BYTE	bModuleName;
	BYTE	bDeviceType;
	//BYTE	bValidKeyNumber;		//��Ч��������
	DWORD	dwModuleAddress;		//ģ���ַ

	MODULE_KEY_UNIT mKeyUnit[MAX_MODULE_KEY_NUMBER];
}MODULE_ENTRY,*PMODULE_ENTRY;
#pragma pack(pop)




//�ͷ�������()
#pragma pack(push,1)
typedef struct _ROOM
{
	UCHAR		sRoomName[64];			//�ͷ�����
	ULONG		ulConnectType;			//ͨ�ŷ�ʽ
	UCHAR		bResv[4];				//�����ֶ�
	
	MODULE_ENTRY	mModuleEntry[MAX_MODULE_NUMBER];		//ģ�鶨��Ľṹ
	HTREEITEM	hItem;					//���ڵ�
}ROOM,*PROOM;
#pragma pack(pop)






//��Ϣ�����ȫ����Ϣ������
#define		WM_UPDATE_SELECT_CFG		(WM_USER+1)
#define		WM_ENABLE_CTRL_ITEM			(WM_UPDATE_SELECT_CFG+1)
#define		WM_GET_SUB_MODULE_NAME		(WM_ENABLE_CTRL_ITEM+1)


