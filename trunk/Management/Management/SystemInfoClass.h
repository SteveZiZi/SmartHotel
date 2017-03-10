// SystemInfoClass.h: interface for the CSystemInfoClass class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#define ROOMDETAIL_API __declspec(dllimport)



class ROOMDETAIL_API CSystemInfoClass  
{
public:
	void LoadNoticeDlg();
	void LoadPictureChangeDlg();
	void LoadBackUpDlg();
	void LoadGuestInfoDlg();
	void LoadSystemDlg();
public:
	void SetDBHandle(LPVOID lParam);

	CSystemInfoClass();
	virtual ~CSystemInfoClass();

};


#pragma comment(lib,"SystemInfoCFG.lib")