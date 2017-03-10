// SystemInfoCFG.h : main header file for the SystemInfoCFG DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CSystemInfoCFGApp
// See SystemInfoCFG.cpp for the implementation of this class
//

class CSystemInfoCFGApp : public CWinApp
{
public:
	CSystemInfoCFGApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
