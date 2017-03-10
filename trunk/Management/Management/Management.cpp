// Management.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Management.h"
#include "ManagementDlg.h"


#include "WelcomDlg.h"
//#include "TechnicianClass.h"
typedef int (*ModulePtr)(unsigned long *);
//////////////////////////////////////////////////////////////////////////////
#include "..\\LoginModule\\LoginFunction.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CManagementApp

BEGIN_MESSAGE_MAP(CManagementApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CManagementApp construction

CManagementApp::CManagementApp()
{
	// TODO: add construction code here,
	mLoginOK = FALSE;
	// Place all significant initialization in InitInstance
}


// The one and only CManagementApp object

CManagementApp theApp;
CMySQL_API *m_mysql=NULL;


PUSER_PERMISSION  GolabPermission;      //权限值
// CManagementApp initialization

BOOL CManagementApp::InitInstance()
{
	INT_PTR Result=S_OK;
	int nEntry = 0;
	CString str;
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.

	

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	skinppLoadSkin(_T("avfone.ssk"));/////////////
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	InitMysql();

//增加登陆框
	USER_LOGIN_INFO mUserInfo;
	USER_LOGIN_INFORMATION mUserLoginInfo;
	ZeroMemory(&mUserLoginInfo,sizeof(USER_LOGIN_INFORMATION));
	CLoginFunction *m_pLogin = NULL;
	m_pLogin = new CLoginFunction();
	
	for (nEntry=0;nEntry<3;nEntry++)
	{
		ZeroMemory(&mUserInfo,sizeof(USER_LOGIN_INFO));
		Result = m_pLogin->LoadLoginModule(&mUserInfo);	
		m_Permission = CheckLoginPermission(&mUserInfo);
		if(Result == IDCANCEL)	
		{	
			exit(1);	
		}
		if (mLoginOK == FALSE)	{	
			str.Format("用户名或密码错 [%d次]\n超过3次自动退出",nEntry+1);
			AfxMessageBox(str);	
		}else{
			break;
		}
	}
	if (mLoginOK == FALSE)	
	{	
		exit(1);	
	}
	if (m_pLogin != NULL)	
	{	
		delete (CLoginFunction *)m_pLogin;	
	}
	m_pLogin = NULL;
	
//获取权限值
	//m_Permission = 0x8000003F;
	//登陆记录
	CTime mtLgoin;
	mtLgoin = CTime::GetCurrentTime();
	strcpy(mUserLoginInfo.sName,mUserInfo.pUserName);
	//mUserLoginInfo.dwID = mUserInfo.nDepartment;
	mUserLoginInfo.mtLogin = mtLgoin;

////////////////////////////////////////////////////////////
//权限指派结构
	GolabPermission = reinterpret_cast<PUSER_PERMISSION>(&m_Permission);
	//******************************************************************
	if(GolabPermission->bOperationFunction == 1)		//允许技术员配置
	{
		CWelcomDlg *m_pWelcom = NULL;
		int SelectMode;
		m_pWelcom = new CWelcomDlg;

		Result = m_pWelcom->DoModal();
		SelectMode = m_pWelcom->GetSelectMode();

		if (m_pWelcom != NULL)	{	delete (CWelcomDlg *)m_pWelcom;	}
		m_pWelcom = NULL;
		if(Result == IDOK)
		{
			if(SelectMode == 0)
			{
				Result = CallTechCfgFrame(NULL);
				if(Result == IDCANCEL)
				{
					//退出时记录登陆记录
					CTime mtLgoout;
					mtLgoout = CTime::GetCurrentTime();
					mUserLoginInfo.mtExit = mtLgoout;
					InsertLoginInfoRecord(&mUserLoginInfo);
					exit(1);
				}
			}
		}
		else
		{
			//退出时记录登陆记录
			CTime mtLgoout;
			mtLgoout = CTime::GetCurrentTime();
			mUserLoginInfo.mtExit = mtLgoout;
			InsertLoginInfoRecord(&mUserLoginInfo);
			exit(1);
		}
   }

	CManagementDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		//退出时记录登陆记录
		CTime mtLgoout;
		mtLgoout = CTime::GetCurrentTime();
		mUserLoginInfo.mtExit = mtLgoout;
		InsertLoginInfoRecord(&mUserLoginInfo);
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	skinppExitSkin();
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
BOOL CManagementApp::InitMysql()
{
	char FileName[MAX_PATH];			//配置文件名
	char CurrentFullPath[MAX_PATH];		//运行全路径
	BOOL bFound;
	memset(FileName,'\0',MAX_PATH);
//得到全运行路径
	memset(CurrentFullPath,'\0',MAX_PATH);
	::GetCurrentDirectory(MAX_PATH,CurrentFullPath);



	strcpy(FileName,CurrentFullPath);
	strcat(FileName,"\\");
	strcat(FileName,DBFileName);

	ZeroMemory(&m_MysqlCfg,sizeof(m_MysqlCfg));
/////////////////////////////////////////////////////////////////////////////
	GetPrivateProfileString("MYSQL","HostName","localhost",m_MysqlCfg.HostName,MAX_PATH,FileName);
	GetPrivateProfileString("MYSQL","User","root",m_MysqlCfg.UserName,MAX_PATH,FileName);
	GetPrivateProfileString("MYSQL","PassWord","",m_MysqlCfg.PassWord,MAX_PATH,FileName);
	m_MysqlCfg.Port = GetPrivateProfileInt("MYSQL","Port",3306,FileName);
	GetPrivateProfileString("MYSQL","DBName","HotelDB",m_MysqlCfg.DBName,MAX_PATH,FileName);
   
   //
	m_mysql = new CMySQL_API(m_MysqlCfg.HostName,m_MysqlCfg.UserName,m_MysqlCfg.PassWord,m_MysqlCfg.Port);
   //初始化数据库并链接
	bFound = m_mysql->ConnectMySQL(m_MysqlCfg.DBName);
	if(bFound == FALSE)  //失败
	{
	//GolabRecordLastMysqlError();
	  AfxMessageBox("Connect DB Fail");
	  return FALSE;
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////////
//功能说明：调用技术员配置模块
//=====================================
//动态调用
int CManagementApp::CallTechCfgFrame(PVOID lParam)
{
	int Result = IDCANCEL;
	
	HINSTANCE hInst;
	hInst = LoadLibrary("TechnicianModule.dll"); 
	if(hInst == NULL)
		return Result;
	ModulePtr TechnicianModule=(ModulePtr)GetProcAddress(hInst,"WakeUpTechnicianModule");//获取Dll的导出函数
	if(TechnicianModule)
		Result = TechnicianModule(NULL);
	FreeLibrary(hInst);//释放Dll函数
	/*CTechnicianClass *m_pTechnician;
	m_pTechnician = new CTechnicianClass();
	Result = m_pTechnician->LoadMainFrame();
	delete[] (CTechnicianClass *)m_pTechnician;
	*/
	return Result;
}



DWORD	CManagementApp::CheckLoginPermission(LPVOID lParam)
{
	PUSER_LOGIN_INFO mUserInfo = (PUSER_LOGIN_INFO)lParam;
	PUSER_INFORMATION	pDbUser = NULL;
	CString str;
	CPtrArray	pRecordArray;
	int nEntry ;
	DWORD dwPermission = 0;
//========================================================================
	str.Format("userID ='%s' AND groupsID =%d",mUserInfo->pUserName,mUserInfo->nDepartment);
	nEntry = GetUserInfoRecord(pRecordArray,str);
	if (nEntry != 1)	{	return 0;	}
	pDbUser = (PUSER_INFORMATION)pRecordArray.GetAt(0);
	if (pDbUser != NULL)	{
		if (strcmp(pDbUser->sPasswords,mUserInfo->pPasswords) == 0){
			mLoginOK = TRUE;
			dwPermission = pDbUser->dwPermission;
		}
	}
	ReleaseUserInfoRecord(pRecordArray);
	return dwPermission;
}