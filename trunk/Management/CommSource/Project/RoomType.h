//���ļ��������巿��Ľṹ�ͱ���
#ifndef ROOMTYPE_H	//�궨������ظ�����
#define ROOMTYPE_H
//===============================================================================
//�������ñ���ص���Ϣ
#define roomTypeSettingTableName   (TEXT("RoomTypeSet"))


//��Ľṹ������
typedef struct _ROOM_TYPE_ENTRY
{
	unsigned long	dwEntryIndex;					//��¼����
	char			cName[ENTRY_NAME_BUF_SIZE];		//������
	unsigned long	dwExRCU;						//���RCU����
	struct _ROOM_TYPE_ENTRY *pNext;
}ROOM_TYPE_ENTRY,*PROOM_TYPE_ENTRY;
//============================================================================================
//�����ַ���
/*
CREATE TABLE RoomTypeSet (ID int(4) not null primary key auto_increment,
roomtypeName VARCHAR(64) not null, 
RCUID int(4) not null , 
FOREIGN KEY(RCUID) references RCUInfo(ID) on delete cascade on update cascade) ENGINE = MYISAM
*/
//=============================================================================================
//#pragma once
#endif