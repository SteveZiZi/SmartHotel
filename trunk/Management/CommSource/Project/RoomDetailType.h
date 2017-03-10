//���ļ���������ͷ��Ľṹ�ͱ���
#ifndef ROOM_DETAIL_H	//�궨������ظ�����
#define ROOM_DETAIL_H
//===============================================================================
//�ͷ����ݱ���
#define RoomSetTableName   (TEXT("RoomSet"))
//¥�����ݱ�
#define	BuildingTableName	(TEXT("BuildingSet"))

//////////////////////////////////////////////////////////////////////////////////
#define SHOW_STYLE_TYPE_A	0
#define SHOW_STYLE_TYPE_B	1
#define SHOW_STYLE_TYPE_C	2
#define SHOW_STYLE_TYPE_D	3




//��Ľṹ������
typedef struct _ROOM_DETAIL_ENTRY
{
	unsigned long	dwEntryIndex;			//��¼����
	unsigned long	bRoomNum;				//����
	unsigned long   bFloorNum;				//¥���
	unsigned long	bBuildingNum;			//¥����

	unsigned long	dwRoomTypeID;			//�����


	char			sIpAddress[32];			//IP��ַ
	unsigned long	dwPort;					//ͨ�Ŷ˿ں�

	unsigned char	*pBuffer;

	unsigned char	*pEquipBlock;
	unsigned char   *pStatusBlock;
	struct _ROOM_DETAIL_ENTRY  *pNext;
}ROOM_DETAIL_ENTRY,*PROOM_DETAIL_ENTRY;




typedef struct _BUILDING_ENTRY
{
	unsigned long	dwEntryIndex;					//��¼����
	char			cName[ENTRY_NAME_BUF_SIZE];		//¥����
	unsigned long	dwFloorNum;						//¥������
	unsigned long	dwExtend;						//��ʾ�ķ��
	struct _BUILDING_ENTRY *pNext;
}BUILDING_ENTRY,*PBUILDING_ENTRY;

//============================================================================================
//�����ַ���
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
//���Ӽ�¼
//INSERT INTO `RoomSet`	VALUE(0,15,10,65,1,'192.168.1.122',8000)
//#pragma once

#endif