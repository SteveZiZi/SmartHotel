//���ļ����������û���Ľṹ�ͱ���
#ifndef USER_H	//�궨������ظ�����
#define USER_H
//===============================================================================

//User���ͱ�
#define UserTableName		   (TEXT("user"))
//===============================================================================
typedef struct _USER_INFORMATION	//�û����ݽṹ
{
	char	sName[MAX_PATH];
	char	sPasswords[MAX_PATH];
	int		nDepartment;
	DWORD	dwPermission;
}USER_INFORMATION,*PUSER_INFORMATION;
//============================================================================================
/*CREATE TABLE `user` (
	`userID` varchar(25) NOT NULL,
	`password` varchar(25) NOT NULL,
	`groupsID` int(4) NOT NULL,
	`Permission` int(4) NOT NULL,
	PRIMARY KEY  (`userID`),
	KEY `groupsID` (`groupsID`),
	CONSTRAINT `user_ibfk_1` FOREIGN KEY (`groupsID`) REFERENCES `departments` (`groupsID`) ON DELETE CASCADE ON UPDATE CASCADE
	) ENGINE=InnoDB DEFAULT CHARSET=gbk |
*/
//============================================================================================


// INSERT INTO User VALUES('Admin','admin',2,65535);
//=============================================================================================
//#pragma once

#endif