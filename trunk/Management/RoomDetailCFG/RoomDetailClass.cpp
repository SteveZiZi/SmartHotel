// RoomDetailClass.cpp: implementation of the CRoomDetailClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RoomDetailCFG.h"
#include "RoomDetailClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
#include "RoomTypeDlg.h"
#include "RoomDlg.h"
#include "RoomModeDlg.h"
#include "AutoEventDlg.h"
#include "KeyDefineDlg.h"
#include "WarnningDlg.h"
//////////////////////////////////////////////////////////////////////

CRoomDetailClass::CRoomDetailClass()
{

}

CRoomDetailClass::~CRoomDetailClass()
{

}

void CRoomDetailClass::LoadRoomTypeDlg()
{
   CRoomTypeDlg *m_pDlg;
   m_pDlg = new CRoomTypeDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CRoomTypeDlg *)m_pDlg;
}

void CRoomDetailClass::LoadRoomDlg()
{//CRoomDlg
   CRoomDlg *m_pDlg;
   m_pDlg = new CRoomDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CRoomDlg *)m_pDlg;
}

void CRoomDetailClass::LoadRoomModeDlg()
{//CRoomModeDlg
   CRoomModeDlg *m_pDlg;
   m_pDlg = new CRoomModeDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CRoomModeDlg *)m_pDlg;
}

void CRoomDetailClass::LoadAutoEventDlg()
{//CAutoEventDlg
   CAutoEventDlg *m_pDlg;
   m_pDlg = new CAutoEventDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CAutoEventDlg *)m_pDlg;
}

void CRoomDetailClass::LoadKeyDefineDlg()
{//CKeyDefineDlg
   CKeyDefineDlg *m_pDlg;
   m_pDlg = new CKeyDefineDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CKeyDefineDlg *)m_pDlg;
}

void CRoomDetailClass::LoadWarnningDlg()
{//CWarnningDlg
   CWarnningDlg *m_pDlg;
   m_pDlg = new CWarnningDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CWarnningDlg *)m_pDlg;
}

void CRoomDetailClass::SetDBHandle(LPVOID lParam)
{
   m_mysql = (CMySQL_API *)lParam;
}
