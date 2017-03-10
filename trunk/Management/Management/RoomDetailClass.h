// RoomDetailClass.h: interface for the CRoomDetailClass class.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#define ROOMDETAIL_API __declspec(dllimport)




class ROOMDETAIL_API CRoomDetailClass  
{
public:
	void LoadWarnningDlg();
	void LoadKeyDefineDlg();
	void LoadAutoEventDlg();
	void LoadRoomModeDlg();
	void LoadRoomDlg();
	void LoadRoomTypeDlg();
public:
	void SetDBHandle(LPVOID lParam);

	CRoomDetailClass();
	virtual ~CRoomDetailClass();

};


#pragma comment(lib,"RoomDetailCFG.lib")