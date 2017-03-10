//该文件用来定义房态的结构和表名
#ifndef ROOMSTATUS_H	//宏定义避免重复定义
#define ROOMSTATUS_H
//===============================================================================
#define		MAX_ROOMSTATUS_TABLE_NUM	4			//房态类表的数量
//总共有4种房态对应的为房态表的表名
const char sRoomStatusName[][32] = {"RoomState_Base",		//基本房态表名
									"RoomState_Temp",		//临时房态表名
									"RoomState_Service",	//服务房态表名
									"RoomState_Other",		//其它房态表名
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
	char			cName[MAX_PATH];		//房态名
	unsigned char	bEnDualPort;			//是否双向
	
	
	unsigned short	wType;					//房态的类型
	unsigned long	dwExtern;				//扩展参数


	unsigned long   vSharp;					//外观索引
}ROOMSTATUS_ENTRY,*PROOMSTATUS_ENTRY;
//============================================================================================
//BOOL CreateRoomStatusTable(int TableName);












//=============================================================================================
//#pragma once
//#include "RoomStatus.c"
#endif