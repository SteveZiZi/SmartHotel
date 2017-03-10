
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MYSQLPACKET_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MYSQLPACKET_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef MYSQLPACKET_EXPORTS
#define MYSQLPACKET_API __declspec(dllexport)
#else
#define MYSQLPACKET_API __declspec(dllimport)
#endif


//////////////////////////////////////////////////////////////////////////////////
//全局功能函数
MYSQLPACKET_API UINT ExeSystemCmd(PCHAR Cmdstr,BOOL ShowFlag = TRUE,BOOL ExitFlag = FALSE);






///////////////////////////////////////////////////////////////////////////////////
//MYSQL API的类
class MYSQLPACKET_API CMySQL_API
{
  public:     //成员变量
     char m_HostName[64];
     char m_UserName[64];
     char m_Passwords[64];
     int m_Port;
  public:     //成员函数
    void InitMySQLAPI();   //初始化API
	BOOL CheckReady();     //检查数据库句柄是否有效
	BOOL ConnectMySQL(const char *DBName);   //连接数据库
	void CloseMySQL();     //关闭数据库
    BOOL ExecuteSQLCmd(PCHAR sqlCMD,BOOL Request=FALSE);   //执行SQL语句
    

	//得到相关的信息
    DWORD GetMySQLError(char* eDesc);    //得到出错信息
    unsigned long GetClientVersion();
	unsigned long GetServiceVersion();
	unsigned int GetConnectProtocolVersion();
	//字符形
	const char* GetHostInfo();
	const char*  GetClientInfo();
	const char* GetServiceInfo();
	//设置相关的信息


	//Create函数
	BOOL CreateDatabase(const char *DBName);
	BOOL DeleteDatabase(const char *DBName);
	BOOL CreateTable(const char *tbName,PCHAR *Field=NULL,int Num=0);
	BOOL DeleteTable(const char *tbName);
	//得到记录集
	unsigned __int64 QuestRecorderSet();
	unsigned __int64 GetRecordNum();
	char ** GetRowString(int rIndex=-1);

	char *GetCurrentColString(int Row,int Col);
    long int GetCurrentColValue(int Row,int Col);
    //删除指定的行
	BOOL DeleteSpecifyRow(const char *TableName,const char *Condition);
    //增加一行
	BOOL InsertRow(const char *TableName,const char *ValueStr);
    //修改指定的行
	BOOL ModifySpecifyValue(const char *TableName,const char *Sector,const char *NewValueStr,const char *Condition);
    BOOL ModifyRecord(const char *TableName,const char *ValueStr,const char *Condition);   









  public:     //构造析构函数

	CMySQL_API(PCHAR host = NULL,PCHAR user = NULL,PCHAR password = NULL,int port = 3306);
	~CMySQL_API();
};















extern MYSQLPACKET_API int nMySQLPacket;










#ifndef MYSQLPACKET_EXPORTS
#pragma comment(lib,"MySQLPacket.lib")
#endif