//���ļ��������巿̬�Ľṹ�ͱ���
#ifndef ROOMSTATUS_H	//�궨������ظ�����
#define ROOMSTATUS_H
//===============================================================================
#define		MAX_ROOMSTATUS_TABLE_NUM	4			//��̬��������
//�ܹ���4�ַ�̬��Ӧ��Ϊ��̬��ı���
const char sRoomStatusName[][32] = {"RoomState_Base",		//������̬����
									"RoomState_Temp",		//��ʱ��̬����
									"RoomState_Service",	//����̬����
									"RoomState_Other",		//������̬����
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
	char			cName[MAX_PATH];		//��̬��
	unsigned char	bEnDualPort;			//�Ƿ�˫��
	
	
	unsigned short	wType;					//��̬������
	unsigned long	dwExtern;				//��չ����


	unsigned long   vSharp;					//�������
}ROOMSTATUS_ENTRY,*PROOMSTATUS_ENTRY;
//============================================================================================
//BOOL CreateRoomStatusTable(int TableName);












//=============================================================================================
//#pragma once
//#include "RoomStatus.c"
#endif