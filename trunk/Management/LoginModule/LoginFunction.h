// LoginFunction.h: interface for the CLoginFunction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGINFUNCTION_H__66F652BB_A683_4246_A31A_E134222F0A98__INCLUDED_)
#define AFX_LOGINFUNCTION_H__66F652BB_A683_4246_A31A_E134222F0A98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//=====================================================================
typedef struct _USER_LOGIN_INFO
{
	char pUserName[MAX_PATH];
	char pPasswords[MAX_PATH];
	int  nDepartment;
}USER_LOGIN_INFO,*PUSER_LOGIN_INFO;
///////////////////////////////////////////////////////////////////////
#ifdef JOHNSON_EXPORT
    #define LOGIN_MODULE_API __declspec(dllexport)
#else
    #define LOGIN_MODULE_API __declspec(dllimport)
#endif
//====================================================================
class LOGIN_MODULE_API CLoginFunction  
{
public:
	int LoadLoginModule(LPVOID lParam);
	CLoginFunction();
	virtual ~CLoginFunction();

};

#endif // !defined(AFX_LOGINFUNCTION_H__66F652BB_A683_4246_A31A_E134222F0A98__INCLUDED_)



#ifndef JOHNSON_EXPORT
#ifdef _DEBUG
	#pragma comment(lib,"..\\Debug\\LoginModule.lib")
#else
	#pragma comment(lib,"..\\Release\\LoginModule.lib")
#endif
#endif