// LoginModule.h : main header file for the LoginModule DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CLoginModuleApp
// See LoginModule.cpp for the implementation of this class
//

class CLoginModuleApp : public CWinApp
{
public:
	CLoginModuleApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
