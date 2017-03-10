//该文件用来定义客房的结构和表名
#ifndef ROOM_DETAIL_H	//宏定义避免重复定义
#define ROOM_DETAIL_H
//===============================================================================
//客房数据表名
#define RoomSetTableName   (TEXT("RoomSet"))
//楼座数据表
#define	BuildingTableName	(TEXT("BuildingSet"))

//////////////////////////////////////////////////////////////////////////////////
#define SHOW_STYLE_TYPE_A	0
#define SHOW_STYLE_TYPE_B	1
#define SHOW_STYLE_TYPE_C	2
#define SHOW_STYLE_TYPE_D	3




//表的结构定如下
typedef struct _ROOM_DETAIL_ENTRY
{
	unsigned long	dwEntryIndex;			//记录索引
	unsigned long	bRoomNum;				//房号
	unsigned long   bFloorNum;				//楼层号
	unsigned long	bBuildingNum;			//楼座号

	unsigned long	dwRoomTypeID;			//房类号


	char			sIpAddress[32];			//IP地址
	unsigned long	dwPort;					//通信端口号

	unsigned char	*pBuffer;

	unsigned char	*pEquipBlock;
	unsigned char   *pStatusBlock;
	struct _ROOM_DETAIL_ENTRY  *pNext;
}ROOM_DETAIL_ENTRY,*PROOM_DETAIL_ENTRY;




typedef struct _BUILDING_ENTRY
{
	unsigned long	dwEntryIndex;					//记录索引
	char			cName[ENTRY_NAME_BUF_SIZE];		//楼座名
	unsigned long	dwFloorNum;						//楼层数量
	unsigned long	dwExtend;						//显示的风格
	struct _BUILDING_ENTRY *pNext;
}BUILDING_ENTRY,*PBUILDING_ENTRY;

//============================================================================================
//建表字符串
/*
CREATE TABLE `RoomSet` (
`RoomID` int(4) not null primary key auto_increment, 
`DoorNum` int(4) not null, 
`FloorNum` int(4) not null ,
`BuildingID` Int(4) not null,
`RoomtypeID` int(4) not null, 
`IPaddress` VARCHAR(25) not null,
`PortValue` int(4) unsigned not null,
 EquipBlock  blob,
 StatusBlock  blob,
 FOREIGN KEY(BuildingID) references `BuildingSet`(BuildingID) on delete cascade on update cascade,
 FOREIGN KEY(RoomtypeID) references `RoomTypeSet`(ID) on delete cascade on update cascade
 )ENGINE=MyISAM DEFAULT CHARSET=gbk


*/
/*
CREATE TABLE `BuildingSet` (
`BuildingID` int(4) not null primary key auto_increment, 
`BuildingName` VARCHAR(64) not null, 
`FloorNum`  int(4) not null,
`Extender`  int(4) unsigned)ENGINE=MyISAM DEFAULT CHARSET=gbk
*/
//=============================================================================================
//增加记录
//INSERT INTO `RoomSet`	VALUE(0,15,10,65,1,'192.168.1.122',8000)
//#pragma once

#endif