//该文件用来定义部门表的结构和表名
#ifndef DEPARTMENT_H	//宏定义避免重复定义
#define DEPARTMENT_H
//===============================================================================

//User类型表
#define DepartmentTableName		   (TEXT("departments"))
//===============================================================================
typedef struct _DEPARTMENT_INFORMATION	//用户数据结构
{
	DWORD	dwID;
	char	sName[32];
	DWORD	dwPermission;
}DEPARTMENT_INFORMATION,*PDEPARTMENT_INFORMATION;
//============================================================================================
/*CREATE TABLE Departments(
	groupsID int(4) not null primary key auto_increment,
	groupsName VARCHAR(25) not null, 
	authority int(8) unsigned not null
	) ENGINE=InnoDB DEFAULT CHARSET=gbk
*/
//============================================================================================


// INSERT INTO Departments VALUE(1,'总经理',65535);
//=============================================================================================
//#pragma once

#endif