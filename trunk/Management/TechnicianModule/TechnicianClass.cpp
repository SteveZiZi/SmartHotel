// TechnicianClass.cpp: implementation of the CTechnicianClass class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "TechnicianModule.h"
#include "TechnicianClass.h"
#include "TechnicianDlg.h"
//============================================================
TECHNICIAN_API(int) WakeUpTechnicianModule(unsigned long * lParam)
{
   int Result = IDOK;
   AFX_MANAGE_STATE(AfxGetStaticModuleState()); 

   CTechnicianDlg *m_pDlg;
   m_pDlg = new CTechnicianDlg();
   Result = m_pDlg->DoModal();

   delete (CTechnicianDlg *)m_pDlg;
   return Result;
}
