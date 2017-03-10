// LoginFunction.cpp: implementation of the CLoginFunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LoginModule.h"
#include "LoginFunction.h"

////////////////////////////////////////////////////
#include "LoginDlg.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoginFunction::CLoginFunction()
{

}

CLoginFunction::~CLoginFunction()
{

}

int CLoginFunction::LoadLoginModule(LPVOID lParam)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	PUSER_LOGIN_INFO pUserInfo = (PUSER_LOGIN_INFO)lParam;
    CLoginDlg *m_pDlg = NULL;
	int Result;
	m_pDlg = new CLoginDlg();
    Result = m_pDlg->DoModal();
//===================================================================
	pUserInfo->nDepartment = m_pDlg->nDepartment;
	strcpy(pUserInfo->pUserName,(LPSTR)(LPCSTR)m_pDlg->m_UserName);
	strcpy(pUserInfo->pPasswords,(LPSTR)(LPCSTR)m_pDlg->m_Passwords);

	if (m_pDlg != NULL)	{    delete (CLoginDlg *)m_pDlg;	}
	m_pDlg = NULL;
    return Result;
}
