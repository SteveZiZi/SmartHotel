//该文件用来定义房态的结构和表名
#ifndef ROOMSTATUS_H	//宏定义避免重复定义
#define ROOMSTATUS_H
//===============================================================================
#define		MAX_ROOMSTATUS_TABLE_NUM	4			//房态类表的数量
//总共有4种房态对应的为房态表的表名
const char sRoomStatusName[][64] = {"RoomState_Base",		//基本房态表名
									"RoomState_Temp",		//临时房态表名
									"RoomState_Service",	//服务房态表名
									"RoomState_Others",		//其它房态表名
									"RoomState_Test"};
//对应的关系为枚举类型sRoomStatusName[x]表示的为表名
enum _ROOMSTATUS_INDEX
{
	RS_BASE = 0,
	RS_TEMP,
	RS_SERVICE,
	RS_OTHER,
	RS_TEST
};


//表的结构定如下
typedef struct _ROOMSTATUS_ENTRY
{
	unsigned long	dwEntryIndex;			//记录索引
	char			cName[ENTRY_NAME_BUF_SIZE];				//房态名
	unsigned char	bEnDualPort;			//是否双向
	
	unsigned long	dwExtend;				//扩展参数
	char			vSharpPath[ENTRY_NAME_BUF_SIZE];					//外观索引

	//定义一下锭表的指针
	struct _ROOMSTATUS_ENTRY *pNext;
}ROOMSTATUS_ENTRY,*PROOMSTATUS_ENTRY;
//============================================================================================
//建表字符串
/*CREATE TABLE RoomState_Others(ID int(4) not null primary key auto_increment,
TypeName varchar(32) not null,
IsDualDirection TINYINT(1) not null,
ExtendValue  TINYINT(4) not null,
Shape	varchar(64) not null) ENGINE = MYISAM
*/
//如果是带有外键的话就用
//ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=gbk
//增加记录
/*
INSERT INTO RoomState_Base VALUE(0,'入住',1,0,'8742.jpg');
*/








//=============================================================================================
//#pragma once
//#include "RoomStatus.c"
#endif