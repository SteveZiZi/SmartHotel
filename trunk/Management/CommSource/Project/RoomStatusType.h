//���ļ��������巿̬�Ľṹ�ͱ���
#ifndef ROOMSTATUS_H	//�궨������ظ�����
#define ROOMSTATUS_H
//===============================================================================
#define		MAX_ROOMSTATUS_TABLE_NUM	4			//��̬��������
//�ܹ���4�ַ�̬��Ӧ��Ϊ��̬��ı���
const char sRoomStatusName[][64] = {"RoomState_Base",		//������̬����
									"RoomState_Temp",		//��ʱ��̬����
									"RoomState_Service",	//����̬����
									"RoomState_Others",		//������̬����
									"RoomState_Test"};
//��Ӧ�Ĺ�ϵΪö������sRoomStatusName[x]��ʾ��Ϊ����
enum _ROOMSTATUS_INDEX
{
	RS_BASE = 0,
	RS_TEMP,
	RS_SERVICE,
	RS_OTHER,
	RS_TEST
};


//��Ľṹ������
typedef struct _ROOMSTATUS_ENTRY
{
	unsigned long	dwEntryIndex;			//��¼����
	char			cName[ENTRY_NAME_BUF_SIZE];				//��̬��
	unsigned char	bEnDualPort;			//�Ƿ�˫��
	
	unsigned long	dwExtend;				//��չ����
	char			vSharpPath[ENTRY_NAME_BUF_SIZE];					//�������

	//����һ�¶����ָ��
	struct _ROOMSTATUS_ENTRY *pNext;
}ROOMSTATUS_ENTRY,*PROOMSTATUS_ENTRY;
//============================================================================================
//�����ַ���
/*CREATE TABLE RoomState_Others(ID int(4) not null primary key auto_increment,
TypeName varchar(32) not null,
IsDualDirection TINYINT(1) not null,
ExtendValue  TINYINT(4) not null,
Shape	varchar(64) not null) ENGINE = MYISAM
*/
//����Ǵ�������Ļ�����
//ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=gbk
//���Ӽ�¼
/*
INSERT INTO RoomState_Base VALUE(0,'��ס',1,0,'8742.jpg');
*/








//=============================================================================================
//#pragma once
//#include "RoomStatus.c"
#endif