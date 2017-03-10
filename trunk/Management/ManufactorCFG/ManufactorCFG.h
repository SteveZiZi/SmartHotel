// ManufactorCFG.h : main header file for the ManufactorCFG DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CManufactorCFGApp
// See ManufactorCFG.cpp for the implementation of this class
//

class CManufactorCFGApp : public CWinApp
{
public:
	CManufactorCFGApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
