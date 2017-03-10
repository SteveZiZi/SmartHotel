//���ļ���������RCU�Ľṹ�ͱ���
#ifndef RCU_H	//�궨������ظ�����
#define RCU_H
//===============================================================================

//RCU���ͱ�
#define RCUTypeTableName		   (TEXT("RCUInfo"))
#define DeviceCfgMethodTableName   (TEXT("DeviceCfgMethod"))
//===============================================================================
typedef struct _DEVICE_CFG_METHOD	//�豸���÷��������ݽṹ
{
	DWORD dwID;					//�ӷ���������
	DWORD dwMethodID;			//������(��Ӧ��ΪRCUId)
//========================================================
	BYTE bEntry;			//�豸���
	BYTE bType;				//�豸����
	BYTE bSublun;			//��·��
	BYTE bResv;				//����

	char sLun[64];			//�豸��
	char LunView[64];		//�豸��ʾ
}DEVICE_CFG_METHOD,*PDEVICE_CFG_METHOD;




typedef struct _RCU_PORT_UNIT
{
	//unsigned long	PortNum;			//�˿ں�
	unsigned long	ObjectEntryIdx;		//�����������
}RCU_PORT_UNIT,*PRCU_PORT_UNIT;
//================================================================================

typedef struct _RCU_TYPE_ENTRY    //������̬�ṹ
{
	unsigned long		RCUId;										//RCU������
	char				RCUName[ENTRY_NAME_BUF_SIZE];				//RCU����
	unsigned long		wEquipPortNum;								//�豸�˿���
	unsigned long		wStatusPortNum;								//��̬�˿���

	RCU_PORT_UNIT		*pEquipDetail;								//�豸�˿���ϸ
	RCU_PORT_UNIT		*pStatusDetail;								//��̬�˿���ϸ
	struct _RCU_TYPE_ENTRY *pNext;
}RCU_TYPE_ENTRY,*PRCU_TYPE_ENTRY;

//#define  RCUDevicePortConfigName   (TEXT("RCUDevicePortCFG"))           //�豸�˿����ñ�
//#define  RCURoomStatePortConfigName  (TEXT("RCURoomStatePortCFG"))     //��̬�˿����ñ�
//============================================================================================
//CREATE TABLE `devicecfgmethod` (
//  `ID` int(4) NOT NULL auto_increment,
//  `RCUID` int(4) NOT NULL,
//  `DeviceEntry` int(4) NOT NULL,
//  `DeviceType` int(4) NOT NULL,
//  `LunIndex` int(4) NOT NULL,
//  `LunString` varchar(25) NOT NULL,
//  `DeviceView` varchar(32) NOT NULL,
//  PRIMARY KEY  (`ID`),
//  KEY `RCUID` (`RCUID`),
//  CONSTRAINT `devicecfgmethod_ibfk_1` FOREIGN KEY (`RCUID`) REFERENCES `rcuinfo` (`ID`) ON DELETE CASCADE ON UPDATE CASCADE
//) ENGINE=InnoDB DEFAULT CHARSET=gbk;
//============================================================================================
//�����ַ���
/*CREATE TABLE RCUInfo(ID int(4) not null primary key auto_increment,
cName varchar(25) not null,
equipPortNum int(4) not null,
statePortNum int(4) not null,
EquipDetail blob,
pStatusDetail blob) ENGINE = MYISAM*/

//insert into tmp values('1',load_file('c:/cloud.gif'));
//=============================================================================================
//#pragma once

#endif