// RoomDetailCFG.h : main header file for the RoomDetailCFG DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRoomDetailCFGApp
// See RoomDetailCFG.cpp for the implementation of this class
//

class CRoomDetailCFGApp : public CWinApp
{
public:
	CRoomDetailCFGApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
