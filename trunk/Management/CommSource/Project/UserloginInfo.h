//���ļ����������û���½��Ľṹ�ͱ���
#ifndef USERLOGIN_H	//�궨������ظ�����
#define USERLOGIN_H
//===============================================================================

//User���ͱ�
#define UserLoginInfoTableName		   (TEXT("UserLoginInfo"))
//===============================================================================
typedef struct _USER_LOGIN_INFORMATION	//�û����ݽṹ
{
	DWORD	dwID;
	char	sName[MAX_PATH];
	CTime	mtLogin;
	CTime   mtExit;
}USER_LOGIN_INFORMATION,*PUSER_LOGIN_INFORMATION;
//============================================================================================
/*CREATE TABLE `UserLoginInfo` (
	`ID` int(4) not null primary key auto_increment, 
	`UserName` varchar(25) NOT NULL,
	`LoginIn`  DATETIME  NOT NULL,
	`LoginOut` DATETIME  NOT NULL
	) ENGINE=InnoDB DEFAULT CHARSET=gbk |
*/
//============================================================================================


// INSERT INTO User VALUES('Admin','admin',2,65535);
//=============================================================================================
//#pragma once

#endif