//该文件用来定义用户登陆表的结构和表名
#ifndef USERLOGIN_H	//宏定义避免重复定义
#define USERLOGIN_H
//===============================================================================

//User类型表
#define UserLoginInfoTableName		   (TEXT("UserLoginInfo"))
//===============================================================================
typedef struct _USER_LOGIN_INFORMATION	//用户数据结构
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