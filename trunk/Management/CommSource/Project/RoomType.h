//该文件用来定义房类的结构和表名
#ifndef ROOMTYPE_H	//宏定义避免重复定义
#define ROOMTYPE_H
//===============================================================================
//房类配置表相关的信息
#define roomTypeSettingTableName   (TEXT("RoomTypeSet"))


//表的结构定如下
typedef struct _ROOM_TYPE_ENTRY
{
	unsigned long	dwEntryIndex;					//记录索引
	char			cName[ENTRY_NAME_BUF_SIZE];		//房类名
	unsigned long	dwExRCU;						//外键RCU索引
	struct _ROOM_TYPE_ENTRY *pNext;
}ROOM_TYPE_ENTRY,*PROOM_TYPE_ENTRY;
//============================================================================================
//建表字符串
/*
CREATE TABLE RoomTypeSet (ID int(4) not null primary key auto_increment,
roomtypeName VARCHAR(64) not null, 
RCUID int(4) not null , 
FOREIGN KEY(RCUID) references RCUInfo(ID) on delete cascade on update cascade) ENGINE = MYISAM
*/
//=============================================================================================
//#pragma once
#endif