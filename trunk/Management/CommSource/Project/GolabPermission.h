//该文件用来定义全局权限结构
#ifndef GOLAB_PERMISSION_H	//宏定义避免重复定义
#define GOLAB_PERMISSION_H
//===============================================================================
#pragma pack(push,1)
//==========================================================================================
typedef struct _USER_PERMISSION    //用户权限结构
{
////////////////////////////////////////////////////////
//BYTE[0] 主权限字节
	union
	{
		BYTE Value;
		struct _MAIN_PERMISSION
		{
		BYTE bActiveRSEn:1;          //实时房态权限[0]
		BYTE bControlPanelEn:1 ;     //控制面板权限[1]
		BYTE bCensusEn:1 ;           //统计查询权限[2]
		BYTE bLogViewEn:1 ;          //统计查询权限[3]
		BYTE bReservedEn:1 ;         //实时房态权限[4]
		BYTE bExitEn:1 ;             //实时房态权限[5]
		BYTE bReserved0:2 ;          //保留权限[6-7]
		}bValue;
	}PermissionMain;
////////////////////////////////////////////////////////    
	//常规设置中的
	BYTE bSystemSet:1 ;       //系统设置权限[8]
	BYTE bUser:1 ;            //用户帐户权限[9]
	BYTE bNoticeSet:1 ;       //公告设置权限[10]
	BYTE bKeyDefine:1 ;       //题牌定义权限[11] 
	BYTE bDailyUphold:1 ;      //日常维护权限[12]
	//工程设置
	BYTE bRoomStyleSet:1 ;    //房类设置权限[13]
	BYTE bRoomSet:1 ;         //客房设置权限[14]
	BYTE bRoomMode:1 ;        //客房模式权限[15]
	BYTE bAutoMessage:1 ;     //自动事件权限[16]
	BYTE bPictureChange:1 ;   //图片变更权限[17]
    //出厂设置
	BYTE bRoomStateSet:1 ;    //房态设置权限[18]
	BYTE bDeviceConfig:1 ;    //设备配置权限[19]
	BYTE bRCUType:1 ;         //RCU类型权限[20]
	BYTE bCommunicationSet:1 ;     //通讯设置权限[21]
	BYTE bWarningDefine:1 ;    //告警定义权限[22]
	BYTE bReserved1:1 ;       //保留权限[23]
////////////////////////////////////////////////////////////
	BYTE bRoomAdjust:1 ;      //房态调整权限[24]
	BYTE bDeviceAdjust:1 ;    //设备调整权限[25]
	BYTE bDeviceTimer:1 ;         //设备定时权限[26]
	BYTE bLCDNotice:1 ;     //LCD公告权限[27]
	BYTE bSetTemperature:1 ;    //预设温度权限[28]
	BYTE bPermissionSet:1 ;    //预设温度权限[29]
	BYTE bReserved2:1 ;    //保留权限[30]

	
	BYTE bOperationFunction:1 ;    //技术员配置[31]
}USER_PERMISSION,*PUSER_PERMISSION;
#pragma pack(pop)






















typedef struct _GOLAB_PERMISSION
{
//第一部分：软件主界面功能
	union	{
		DWORD	dwMainValue;
		struct MAIN_DETAIl
		{
			DWORD Reserved:31;
			DWORD bEnOperateCfg:1;		//是否允许技术员操作
		}MainDetail;
	}MainPermission;	//主功能权限
//绺二部分：
	DWORD Resv;
}GOLAB_PERMISSION,*PGOLAB_PERMISSION;















#endif