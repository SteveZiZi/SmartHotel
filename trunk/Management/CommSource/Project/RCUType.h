//该文件用来定义RCU的结构和表名
#ifndef RCU_H	//宏定义避免重复定义
#define RCU_H
//===============================================================================

//RCU类型表
#define RCUTypeTableName		   (TEXT("RCUInfo"))
#define DeviceCfgMethodTableName   (TEXT("DeviceCfgMethod"))
//===============================================================================
typedef struct _DEVICE_CFG_METHOD	//设备配置方案的数据结构
{
	DWORD dwID;					//子方案索引号
	DWORD dwMethodID;			//方案号(对应的为RCUId)
//========================================================
	BYTE bEntry;			//设备序号
	BYTE bType;				//设备类型
	BYTE bSublun;			//子路号
	BYTE bResv;				//保留

	char sLun[64];			//设备名
	char LunView[64];		//设备显示
}DEVICE_CFG_METHOD,*PDEVICE_CFG_METHOD;




typedef struct _RCU_PORT_UNIT
{
	//unsigned long	PortNum;			//端口号
	unsigned long	ObjectEntryIdx;		//对象的索引号
}RCU_PORT_UNIT,*PRCU_PORT_UNIT;
//================================================================================

typedef struct _RCU_TYPE_ENTRY    //基本房态结构
{
	unsigned long		RCUId;										//RCU索引号
	char				RCUName[ENTRY_NAME_BUF_SIZE];				//RCU名称
	unsigned long		wEquipPortNum;								//设备端口数
	unsigned long		wStatusPortNum;								//房态端口数

	RCU_PORT_UNIT		*pEquipDetail;								//设备端口详细
	RCU_PORT_UNIT		*pStatusDetail;								//房态端口详细
	struct _RCU_TYPE_ENTRY *pNext;
}RCU_TYPE_ENTRY,*PRCU_TYPE_ENTRY;

//#define  RCUDevicePortConfigName   (TEXT("RCUDevicePortCFG"))           //设备端口配置表
//#define  RCURoomStatePortConfigName  (TEXT("RCURoomStatePortCFG"))     //房态端口配置表
//============================================================================================
//CREATE TABLE `devicecfgmethod` (
//  `ID` int(4) NOT NULL auto_increment,
//  `RCUID` int(4) NOT NULL,
//  `DeviceEntry` int(4) NOT NULL,
//  `DeviceType` int(4) NOT NULL,
//  `LunIndex` int(4) NOT NULL,
//  `LunString` varchar(25) NOT NULL,
//  `DeviceView` varchar(32) NOT NULL,
//  PRIMARY KEY  (`ID`),
//  KEY `RCUID` (`RCUID`),
//  CONSTRAINT `devicecfgmethod_ibfk_1` FOREIGN KEY (`RCUID`) REFERENCES `rcuinfo` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE
//) ENGINE=InnoDB DEFAULT CHARSET=gbk;
//============================================================================================
//建表字符串
/*CREATE TABLE RCUInfo(ID int(4) not null primary key auto_increment,
cName varchar(25) not null,
equipPortNum int(4) not null,
statePortNum int(4) not null,
EquipDetail blob,
pStatusDetail blob) ENGINE = MYISAM*/

//insert into tmp values('1',load_file('c:/cloud.gif'));
//=============================================================================================
//#pragma once

#endif