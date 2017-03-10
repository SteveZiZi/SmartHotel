
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
//ȫ�ֹ��ܺ���
MYSQLPACKET_API UINT ExeSystemCmd(PCHAR Cmdstr,BOOL ShowFlag = TRUE,BOOL ExitFlag = FALSE);






///////////////////////////////////////////////////////////////////////////////////
//MYSQL API����
class MYSQLPACKET_API CMySQL_API
{
  public:     //��Ա����
     char m_HostName[64];
     char m_UserName[64];
     char m_Passwords[64];
     int m_Port;
  public:     //��Ա����
    void InitMySQLAPI();   //��ʼ��API
	BOOL CheckReady();     //������ݿ����Ƿ���Ч
	BOOL ConnectMySQL(const char *DBName);   //�������ݿ�
	void CloseMySQL();     //�ر����ݿ�
    BOOL ExecuteSQLCmd(PCHAR sqlCMD,BOOL Request=FALSE);   //ִ��SQL���
    

	//�õ���ص���Ϣ
    DWORD GetMySQLError(char* eDesc);    //�õ�������Ϣ
    unsigned long GetClientVersion();
	unsigned long GetServiceVersion();
	unsigned int GetConnectProtocolVersion();
	//�ַ���
	const char* GetHostInfo();
	const char*  GetClientInfo();
	const char* GetServiceInfo();
	//������ص���Ϣ


	//Create����
	BOOL CreateDatabase(const char *DBName);
	BOOL DeleteDatabase(const char *DBName);
	BOOL CreateTable(const char *tbName,PCHAR *Field=NULL,int Num=0);
	BOOL DeleteTable(const char *tbName);
	//�õ���¼��
	unsigned __int64 QuestRecorderSet();
	unsigned __int64 GetRecordNum();
	char ** GetRowString(int rIndex=-1);

	char *GetCurrentColString(int Row,int Col);
    long int GetCurrentColValue(int Row,int Col);
    //ɾ��ָ������
	BOOL DeleteSpecifyRow(const char *TableName,const char *Condition);
    //����һ��
	BOOL InsertRow(const char *TableName,const char *ValueStr);
    //�޸�ָ������
	BOOL ModifySpecifyValue(const char *TableName,const char *Sector,const char *NewValueStr,const char *Condition);
    BOOL ModifyRecord(const char *TableName,const char *ValueStr,const char *Condition);   









  public:     //������������

	CMySQL_API(PCHAR host = NULL,PCHAR user = NULL,PCHAR password = NULL,int port = 3306);
	~CMySQL_API();
};















extern MYSQLPACKET_API int nMySQLPacket;










#ifndef MYSQLPACKET_EXPORTS
#pragma comment(lib,"MySQLPacket.lib")
#endif