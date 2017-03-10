// Management.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "stdafx.h"


// CManagementApp:
// See Management.cpp for the implementation of this class
//

class CManagementApp : public CWinApp
{
public:
	MYSQL_CONFIG m_MysqlCfg;
	CString UseName;							//用户名
	unsigned __int64  m_Permission;       //权限值
	BOOL	mLoginOK;
public:
	int CallTechCfgFrame(PVOID lParam);
	BOOL InitMysql();
	DWORD	CheckLoginPermission(LPVOID lParam);
	CManagementApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CManagementApp theApp;