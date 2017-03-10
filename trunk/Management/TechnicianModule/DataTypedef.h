#pragma once
//==================================================================================
#define		MAX_MODULE_NUMBER				32				//最大模块个数
#define		MAX_MODULE_KEY_NUMBER			32				//模块最大的按键数目
#define		MAX_CTRL_MODULE_NUMBER			16				//最大受控模块个数
//**********************************************************************************
enum _KEY_ATTRIBUTE_VALUE
{
	ATTRIBUTE_UNDEFINE,				//未定义
	ATTRIBUTE_INPUT,				//输入
	ATTRIBUTE_OUTPUT				//输出
};

const char sKeyAttribute[][12] = {"N","I","O",""};







//==================================================================================
//受控设备的结构类型
//表示的是设备中的输入端控制的设备结构(最小单元)
#pragma pack(push,1)
typedef struct _CONTROL_DEVICE_UNIT
{
	BYTE bModuleEntry;			//模块编号(1-255)````0:表示无效
	BYTE bSubModuleItem;		//模块的子路

	BYTE bSpecialFundef;		//特殊功能定义
	BYTE bReserved;				//保留

	DWORD dwArgument;			//参数
}CONTROL_DEVICE_UNIT,*PCONTROL_DEVICE_UNIT;
#pragma pack(pop)

//模块的子键定义结构部分
#pragma pack(push,1)
typedef struct _CTRL_DEVICE_LIST
{
	BYTE	bNumber;		//有效个数
	CONTROL_DEVICE_UNIT		mCtrlDev[MAX_CTRL_MODULE_NUMBER];
}CTRL_DEVICE_LIST,*PCTRL_DEVICE_LIST;

#pragma pack(pop)



#pragma pack(push,1)
typedef struct _MODULE_KEY_UNIT
{
	BYTE bEntry;				//按键编号(1-MAX_MODULE_KEY_NUMBER)````0:表示无效
	BYTE bKeyAttribute;			//按键属性	_KEY_ATTRIBUTE_VALUE
	union _CONTENT{
		char pName[];
		CTRL_DEVICE_LIST mCtrlDeviceList;
		//struct _CTRL_DEVICE_LIST
		//{
		//	BYTE	bNumber;		//有效个数
		//	CONTROL_DEVICE_UNIT		mCtrlDev[MAX_CTRL_MODULE_NUMBER];
		//}mCtrlDeviceList;
	}mContent;
}MODULE_KEY_UNIT,*PMODULE_KEY_UNIT;
#pragma pack(pop)
//====================================================================================================
//模块的结构的定义部分
#pragma pack(push,1)
typedef struct _MODULE_ENTRY
{
	BYTE	bEntry;					//模块编号(1-MAX_MODULE_KEY_NUMBER)````0:表示无效
	BYTE	bModuleType;
	BYTE	bModuleName;
	BYTE	bDeviceType;
	//BYTE	bValidKeyNumber;		//有效按键个数
	DWORD	dwModuleAddress;		//模块地址

	MODULE_KEY_UNIT mKeyUnit[MAX_MODULE_KEY_NUMBER];
}MODULE_ENTRY,*PMODULE_ENTRY;
#pragma pack(pop)




//客房总类型()
#pragma pack(push,1)
typedef struct _ROOM
{
	UCHAR		sRoomName[64];			//客房名称
	ULONG		ulConnectType;			//通信方式
	UCHAR		bResv[4];				//保留字段
	
	MODULE_ENTRY	mModuleEntry[MAX_MODULE_NUMBER];		//模块定义的结构
	HTREEITEM	hItem;					//树节点
}ROOM,*PROOM;
#pragma pack(pop)






//消息定义的全局信息在这里
#define		WM_UPDATE_SELECT_CFG		(WM_USER+1)
#define		WM_ENABLE_CTRL_ITEM			(WM_UPDATE_SELECT_CFG+1)
#define		WM_GET_SUB_MODULE_NAME		(WM_ENABLE_CTRL_ITEM+1)


