// RoomDetailClass.h: interface for the CRoomDetailClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROOMDETAILCLASS_H__2C234B38_05F9_4979_91BC_05755787A229__INCLUDED_)
#define AFX_ROOMDETAILCLASS_H__2C234B38_05F9_4979_91BC_05755787A229__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define ROOMDETAIL_API __declspec(dllexport)


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

#endif // !defined(AFX_ROOMDETAILCLASS_H__2C234B38_05F9_4979_91BC_05755787A229__INCLUDED_)
