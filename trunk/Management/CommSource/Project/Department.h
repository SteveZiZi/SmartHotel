//���ļ��������岿�ű�Ľṹ�ͱ���
#ifndef DEPARTMENT_H	//�궨������ظ�����
#define DEPARTMENT_H
//===============================================================================

//User���ͱ�
#define DepartmentTableName		   (TEXT("departments"))
//===============================================================================
typedef struct _DEPARTMENT_INFORMATION	//�û����ݽṹ
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


// INSERT INTO Departments VALUE(1,'�ܾ���',65535);
//=============================================================================================
//#pragma once

#endif