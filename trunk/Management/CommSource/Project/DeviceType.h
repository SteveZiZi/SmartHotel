//该文件用来定义设备的结构和表名
#ifndef DEVICE_H	//宏定义避免重复定义
#define DEVICE_H
//===============================================================================
#define		MAX_EQUIPMENT_TABLE_NUM	4			//设备类表的数量
//总共有4种设备对应的为设备表的表名
const char sEquipmentTbName[][64] = {"Equipment_Air",					//空调设备表名
									"Equipment_Light",					//调光设备表名
									"Equipment_Switch",					//开关设备表名
									"Equipment_PowerSaveSwitch",		//节电开关设备表名
									"Equipment_Test"};
//对应的关系为枚举类型sEquipmentTbName[x]表示的为表名
enum _EQUIPMENT_INDEX
{
	EP_AIR = 0,
	EP_LIGHT,
	EP_SWITCH,
	EP_POWERSAVESWITCH,
	EP_TEST
};


//表的结构定如下
typedef struct _EQUIPMENT_ENTRY
{
	unsigned long	dwEntryIndex;					//记录索引
	char			cName[ENTRY_NAME_BUF_SIZE];		//设备名
	unsigned char	bEnDualPort;					//是否双向
	unsigned short	wType;							//设备的类型
	unsigned long	dwExtend;						//扩展参数
	char			vSharpPath[ENTRY_NAME_BUF_SIZE];//外观索引
	struct _EQUIPMENT_ENTRY *pNext;
}EQUIPMENT_ENTRY,*PEQUIPMENT_ENTRY;
//============================================================================================
//建表字符串
/*CREATE TABLE Equipment_PowerSaveSwitch(ID int(4) not null primary key auto_increment,
cName varchar(25) not null,
IsDualDirection TINYINT(1) not null,
EquType TINYINT(2) not null,
ExtendValue  TINYINT(4) not null,
Shape	varchar(64) not null) ENGINE = MYISAM
//如果是带有外键的话就用
/ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=gbk
*/
//=============================================================================================
//#pragma once

#endif
