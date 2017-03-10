// ManufactorClass.cpp: implementation of the CManufactorClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ManufactorCFG.h"
#include "ManufactorClass.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
#include "RoomStatusDlg.h"
#include "DeviceDlg.h"
#include "CommunicationDlg.h"
#include "RCUDlg.h"
//////////////////////////////////////////////////////////////////////

CManufactorClass::CManufactorClass()
{

}

CManufactorClass::~CManufactorClass()
{

}


//
void CManufactorClass::LoadRoomStatusDlg()
{ 
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	CRoomStatusDlg *m_pDlg;;
	m_pDlg = new CRoomStatusDlg();
	if (m_pDlg == NULL)	{	return;	}
	m_pDlg->DoModal();
	delete (CRoomStatusDlg *)m_pDlg;
}
//
void CManufactorClass::LoadDeviceDlg()
{
   CDeviceDlg *m_pDlg;
   m_pDlg = new CDeviceDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CDeviceDlg *)m_pDlg;
}
//
void CManufactorClass::LoadCommunicationDlg()
{
  //CCommunicationDlg
   CCommunicationDlg *m_pDlg;
   m_pDlg = new CCommunicationDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CCommunicationDlg *)m_pDlg;
}

void CManufactorClass::LoadRCUDlg()
{
   CRCUDlg *m_pDlg;
   m_pDlg = new CRCUDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CRCUDlg *)m_pDlg;
}

void CManufactorClass::SetDBHandle(LPVOID lParam)
{
   m_mysql = (CMySQL_API *)lParam;

}
