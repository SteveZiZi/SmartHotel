// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__0F812DEE_F7A7_47CD_B619_BF869D6AE110__INCLUDED_)
#define AFX_STDAFX_H__0F812DEE_F7A7_47CD_B619_BF869D6AE110__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define _CRT_SECURE_NO_DEPRECATE
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//////////////////////////
#ifndef ULONG_PTR
  #define ULONG_PTR unsigned long*
#endif
//#include "GDIPlus\\include\\specstrings.h"
#include "..\\CommSource\\include\\gdiplus.h"
#pragma comment(lib, "..\\CommSource\\lib\\gdiplus.lib")
using namespace Gdiplus;

//数据库
#include "..\\MySQLPacket\\MySQLPacketClass.h"   //数据库封装
#include "..\\CommSource\\Project\\MySqlDBType.h"
#include "..\\CommSource\\Project\\DbDefine.h"
extern CMySQL_API *m_mysql;

#include "..\\CommSource\\Project\\TableAccess.h"
#include "..\\CommSource\\Project\\channel.h"
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#include "GDIPlus\\include\\specstrings.h"





#endif // !defined(AFX_STDAFX_H__0F812DEE_F7A7_47CD_B619_BF869D6AE110__INCLUDED_)
