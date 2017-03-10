// SystemInfoClass.h: interface for the CSystemInfoClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMINFOCLASS_H__33C91D88_4365_4F5E_AE7D_4E1C9CBC9A2C__INCLUDED_)
#define AFX_SYSTEMINFOCLASS_H__33C91D88_4365_4F5E_AE7D_4E1C9CBC9A2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define ROOMDETAIL_API __declspec(dllexport)



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

#endif // !defined(AFX_SYSTEMINFOCLASS_H__33C91D88_4365_4F5E_AE7D_4E1C9CBC9A2C__INCLUDED_)
