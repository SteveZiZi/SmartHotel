// ManufactorClass.h: interface for the CManufactorClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANUFACTORCLASS_H__5B71658B_D9D8_4DF5_A8F5_967F311B4F8A__INCLUDED_)
#define AFX_MANUFACTORCLASS_H__5B71658B_D9D8_4DF5_A8F5_967F311B4F8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
////////////////////////////////////////////////////////////////////////////////////////////
#define MANUFACTORCFG_API __declspec(dllexport)

/////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////
class MANUFACTORCFG_API CManufactorClass  
{
public:
	CManufactorClass();
	virtual ~CManufactorClass();
public:
	void SetDBHandle(LPVOID lParam);
	void LoadRCUDlg();
	void LoadCommunicationDlg();
	void LoadDeviceDlg();
	void LoadRoomStatusDlg();


};

#endif // !defined(AFX_MANUFACTORCLASS_H__5B71658B_D9D8_4DF5_A8F5_967F311B4F8A__INCLUDED_)
