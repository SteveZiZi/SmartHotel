// SystemInfoClass.cpp: implementation of the CSystemInfoClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemInfoCFG.h"
#include "SystemInfoClass.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
#include "SystemSettingDlg.h"
#include "GuestDlg.h"
#include "BackUpDlg.h"
#include "PictureChangeDlg.h"
#include "NoticeDlg.h"
//////////////////////////////////////////////////////////////////////

CSystemInfoClass::CSystemInfoClass()
{

}

CSystemInfoClass::~CSystemInfoClass()
{

}

void CSystemInfoClass::LoadSystemDlg()
{
   CSystemSettingDlg *m_pDlg;
   m_pDlg = new CSystemSettingDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CSystemSettingDlg *)m_pDlg;
}

void CSystemInfoClass::LoadGuestInfoDlg()
{
   CGuestDlg *m_pDlg;
   m_pDlg = new CGuestDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CGuestDlg *)m_pDlg;
}

void CSystemInfoClass::LoadBackUpDlg()
{
   CBackUpDlg *m_pDlg;
   m_pDlg = new CBackUpDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CBackUpDlg *)m_pDlg;
}

void CSystemInfoClass::LoadPictureChangeDlg()
{//CPictureChangeDlg
   CPictureChangeDlg *m_pDlg;
   m_pDlg = new CPictureChangeDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 


   m_pDlg->DoModal();
   delete (CPictureChangeDlg *)m_pDlg;
}

void CSystemInfoClass::LoadNoticeDlg()
{//CNoticeDlg
   CNoticeDlg *m_pDlg;
   m_pDlg = new CNoticeDlg();

   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 



   m_pDlg->DoModal();
   delete (CNoticeDlg *)m_pDlg;
}

void CSystemInfoClass::SetDBHandle(LPVOID lParam)
{
   m_mysql = (CMySQL_API *)lParam;
}
