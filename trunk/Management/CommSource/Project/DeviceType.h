//���ļ����������豸�Ľṹ�ͱ���
#ifndef DEVICE_H	//�궨������ظ�����
#define DEVICE_H
//===============================================================================
#define		MAX_EQUIPMENT_TABLE_NUM	4			//�豸��������
//�ܹ���4���豸��Ӧ��Ϊ�豸��ı���
const char sEquipmentTbName[][64] = {"Equipment_Air",					//�յ��豸����
									"Equipment_Light",					//�����豸����
									"Equipment_Switch",					//�����豸����
									"Equipment_PowerSaveSwitch",		//�ڵ翪���豸����
									"Equipment_Test"};
//��Ӧ�Ĺ�ϵΪö������sEquipmentTbName[x]��ʾ��Ϊ����
enum _EQUIPMENT_INDEX
{
	EP_AIR = 0,
	EP_LIGHT,
	EP_SWITCH,
	EP_POWERSAVESWITCH,
	EP_TEST
};


//��Ľṹ������
typedef struct _EQUIPMENT_ENTRY
{
	unsigned long	dwEntryIndex;					//��¼����
	char			cName[ENTRY_NAME_BUF_SIZE];		//�豸��
	unsigned char	bEnDualPort;					//�Ƿ�˫��
	unsigned short	wType;							//�豸������
	unsigned long	dwExtend;						//��չ����
	char			vSharpPath[ENTRY_NAME_BUF_SIZE];//�������
	struct _EQUIPMENT_ENTRY *pNext;
}EQUIPMENT_ENTRY,*PEQUIPMENT_ENTRY;
//============================================================================================
//�����ַ���
/*CREATE TABLE Equipment_PowerSaveSwitch(ID int(4) not null primary key auto_increment,
cName varchar(25) not null,
IsDualDirection TINYINT(1) not null,
EquType TINYINT(2) not null,
ExtendValue  TINYINT(4) not null,
Shape	varchar(64) not null) ENGINE = MYISAM
//����Ǵ�������Ļ�����
/ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=gbk
*/
//=============================================================================================
//#pragma once

#endif
