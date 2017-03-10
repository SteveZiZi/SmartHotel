// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit
#define _CRT_SECURE_NO_DEPRECATE
// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#define GOLAB_THREAD_IDLE	0
#define GOLAB_THREAD_RUN	1
#define GOLAB_THREAD_PAUSE	2
#define GOLAB_THREAD_EXIT	3
//*****************************************************************************




#include "FunLibrary.h"			//���ܺ���ͷ�ļ�
#include "..\\CommSource\\Project\\DbDefine.h"
#include "..\\CommSource\\Project\\ProjectType.h"
#include "..\\CommSource\\Project\\MySqlDBType.h"		//���ݿ�ĸ��ű�
#include "..\\CommSource\\Project\\TableAccess.h"		//���ʸ��ű�
//���ݿ�
#include "MySQLPacket.h"   //���ݿ��װ
#include "..\\CommSource\\Project\\MySqlDBType.h"
//�������������ת��
#include "..\\CommSource\\Project\\TransDataType.h"
#include "..\\CommSource\\Project\\channel.h"

//ȫ��Ȩ�����ͽ۹�
#include "..\\CommSource\\Project\\GolabPermission.h"		//���ݿ�ĸ��ű�



extern BYTE GolabRunStatus;						//��ʶȫ��ִ��״̬
extern CMySQL_API *m_mysql;
extern PUSER_PERMISSION  GolabPermission;		//Ȩ��ֵ
extern HANDLE	hInquiryThread;

#pragma comment(lib,"SkinPPWTL.lib")
#include "SkinPPWTL.h"

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif