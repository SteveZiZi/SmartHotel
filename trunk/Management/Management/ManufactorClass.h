// ManufactorClass.h: interface for the CManufactorClass class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////
#define MANUFACTORCFG_API __declspec(dllimport)

/////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
class MANUFACTORCFG_API CManufactorClass  
{
public:
	void LoadRCUDlg();
	void LoadCommunicationDlg();
	void LoadDeviceDlg();
	void LoadRoomStatusDlg();	
public:
	void SetDBHandle(LPVOID lParam);

	CManufactorClass();
	virtual ~CManufactorClass();

};













#pragma comment(lib,"ManufactorCFG.lib")