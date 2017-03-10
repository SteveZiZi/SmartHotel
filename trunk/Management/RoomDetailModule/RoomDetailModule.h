// RoomDetailModule.h : main header file for the RoomDetailModule DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRoomDetailModuleApp
// See RoomDetailModule.cpp for the implementation of this class
//

class CRoomDetailModuleApp : public CWinApp
{
public:
	CRoomDetailModuleApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
