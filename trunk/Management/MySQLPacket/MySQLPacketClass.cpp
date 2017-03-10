// MySQLPacket.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "MySQLPacketClass.h"
#include ".\include\\mysql.h"
#pragma comment(lib,"libmysql.lib")

//////////////////////////////////////////////////////////////////////
//����ȫ�ֱ���
my_ulonglong ResordNum = 0;
MYSQL* mydata = NULL;
MYSQL_RES* m_Res = NULL;
MYSQL_ROW  m_Row;

//�����ַ���


/////////////////////////////////////////////////////////////
//����CMD(DOS) ����
/////////////////////////////////////////////////////////////
MYSQLPACKET_API UINT ExeSystemCmd(PCHAR Cmdstr,BOOL ShowFlag,BOOL ExitFlag)
{
   char Cmd[MAX_PATH];
   UINT Result;
   memset(Cmd,'\0',MAX_PATH);

   //����ָ��
   strcpy(Cmd,"cmd /k ");    //����CMD
   //���������ַ���
   strcat(Cmd,Cmdstr);       //ָ���ַ���

/* strcat(Cmd,"cmd /k ");    //CMD.exe");
   //����·��
   strcat(Cmd,"cd ");        //CMD
   strcat(Cmd,MysqlPath);   //Path

   strcat(Cmd," && ");   //����

   //������ָ��
   strcat(Cmd,Cmdstr);   //ָ���ַ���
*/

   //�Ƿ��˳�
   if(ExitFlag)
   {
     strcat(Cmd," && ");   //����
     strcat(Cmd,"exit");   //����
   }


   //�Ƿ���ʾ
   if(ShowFlag)
	 Result = WinExec(Cmd, SW_SHOW);
   else
     Result = WinExec(Cmd, SW_HIDE);

   return Result;
}

























/////////////////////////////////////////////////////////////////////////////////////////
//���캯��
CMySQL_API::CMySQL_API(PCHAR host,PCHAR user,PCHAR password,int port)
{
   InitMySQLAPI();
   //��ֵ
   strcpy(m_HostName,host);   //����Host��
   strcpy(m_UserName,user);   //�����û���
   strcpy(m_Passwords,password);  //��������
   
   /*strcpy(m_HostName,"localhost");
   strcpy(m_UserName,"root");
   strcpy(m_Passwords,"123456");
  */ m_Port = port;       //�˿�

}

//��������
CMySQL_API::~CMySQL_API()
{
  // CloseMySQL();
  mysql_library_end(); 
}


/////////////////////////////////////////////////////////////////////////////////////////
//��Ա����
/////////////////////////////////////////////////////////////////////////////////////////
//��ʼ��һЩ����
void CMySQL_API::InitMySQLAPI()
{
   mydata = NULL;
   mysql_library_init(0,NULL,NULL);    //��ʼ��MYSQL ��C  API��
}

//���״̬�Ƿ���ȷ
BOOL CMySQL_API::CheckReady()
{
   //�����Ч��
  if(mydata == NULL)    //�����Ч���ؼ�
     return FALSE;


  return TRUE;
}

//����ִ�е�SQL���
BOOL CMySQL_API::ExecuteSQLCmd(PCHAR sqlCMD,BOOL Request)
{
   int Result;
   //��ռ�¼ֵ
   if(m_Res != NULL)
     mysql_free_result(m_Res);
 
   m_Res = NULL;
   ResordNum = 0;
   m_Row = NULL;

   //�ȼ�����Ƿ���Ч
   if(!CheckReady())
	 return 0;

   //ִ��SQL���
   //Result = mysql_query(mydata,sqlCMD);
   Result = mysql_real_query(mydata,sqlCMD,(DWORD)strlen(sqlCMD));
   if(Result)   //�д�ͷ���
     return FALSE;
 
   //����ֵ������
   //0:��ʾ�ɹ�
   //CR_COMMANDS_OUT_OF_SYNC        �Բ�ǡ����˳��ִ��������
   //CR_SERVER_GONE_ERROR           MySQL������������
   //CR_SERVER_LOST                 �ڲ�ѯ�����У�������������Ӷ�ʧ
   //CR_UNKNOWN_ERROR               ����δ֪����
/////////////////////////////////////////////////////////////////////////////////////////////////
   if(Request)
   {
     //�õ�һ���洢��¼���Ŀռ�
     m_Res = mysql_store_result(mydata);   //�ڴ�Ҫ�㹻��
     //m_Res = mysql_use_result(mydata);       //����ͨ��fetch�ſ��Եõ�
	 if(m_Res == NULL)
		 return FALSE;
     //�õ���¼�����ж��ٸ�����
     ResordNum = mysql_num_rows(m_Res);    
     if(!ResordNum)
		return FALSE;
   }


   return TRUE;
}


//�������ݿ�
BOOL CMySQL_API::ConnectMySQL(const char *DBName)
{
 //��������Ӿͷ�����
    if(mydata != NULL)
      return TRUE;  
 
   //�½�һ�����ݽṹ���
   mydata = new MYSQL(); 
   mysql_init(mydata);    //��ʼ��mydata�����ݽṹ��Mydata��MYSQL����


   //mysql_select_db(mydata,DBName);
   /////////////////////////////////////////////////////////////////////
   if(mysql_real_connect(mydata,m_HostName,m_UserName,m_Passwords,DBName,m_Port,NULL,0) == NULL)
     return FALSE;     //��ʾ�������ݿ��д� 
   mysql_query(mydata,"SET NAMES 'GBK'");
   return TRUE;
}


//�ر����ݿ�CMySQL_APICMySQL_API
void CMySQL_API::CloseMySQL()
{ 
   if(m_Res != NULL)
   {
     mysql_free_result(m_Res);
     m_Res = NULL;
   }
   /////////////////////////////////////////////////
   if(mydata != NULL)
   {
     mysql_close(mydata);    
     delete []mydata;
     mydata = NULL;
   }
}


///////////////////////////////////////////////////////////////////
//���صĴ������
//������eDesc ��ʾ���Ǵ������ϸ��Ϣ
///////////////////////////////////////////////////////////////////
DWORD CMySQL_API::GetMySQLError(char* eDesc)
{
   DWORD ErrorValue;
   ErrorValue = mysql_errno(mydata);   //�������

   strcpy(eDesc,mysql_error(mydata));  //������Ϣ
   return ErrorValue;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//�����ǵõ�һЩ��ص���Ϣ
///////////////////////////////////////////////////////////////////////////////////////////////////
//���ַ�����ʽ���ؿͻ��˰汾��Ϣ
const char* CMySQL_API::GetClientInfo()
{   

	return mysql_get_client_info();

}
//��������ʽ���ؿͻ��˰汾��Ϣ
unsigned long CMySQL_API::GetClientVersion()
{
   return mysql_get_client_version();
}

//�����������ӵ��ַ���
const char* CMySQL_API::GetHostInfo()
{
  if(mydata == NULL)
	return NULL;
  return mysql_get_host_info(mydata);

}

//��������ʽ���ط������İ汾��
unsigned long CMySQL_API::GetServiceVersion()
{
   if(mydata == NULL)
	  return 0;
   return mysql_get_server_version(mydata);
}

//���ط������İ汾��
const char* CMySQL_API::GetServiceInfo()
{
   if(mydata == NULL)
	  return NULL;

   return mysql_get_server_info(mydata);
}

//����������ʹ�õ�Э��汾
unsigned int CMySQL_API::GetConnectProtocolVersion()
{
   if(mydata == NULL)
	  return 0;
   
   return mysql_get_proto_info(mydata);
}


/////////////////////////////////////////////
//���ã�������ѡ�б�
//����TRUE    ��ʾ�����ɹ�
//����FALSE   ��ʾʧ��  
/////////////////////////////////////////////
BOOL CMySQL_API::CreateDatabase(const char *DBName)
{
   BOOL status;
   char szSqlText[64];

   memset(szSqlText,'\0',64);
   //������������
   status = ConnectMySQL(NULL);
   if(!status)
	 return FALSE;

   //�������ݿ�
   strcpy(szSqlText,"CREATE DATABASE ");
   if(DBName == NULL)
	  return FALSE;
   strcat(szSqlText,DBName);

   //ִ�д���
   status = ExecuteSQLCmd(szSqlText);
   if(!status)
   	 return FALSE;

   //ѡ �����ݿ�
   status = mysql_select_db(mydata,DBName);
   //����ֵ
   //0: ��ȷ
   //CR_COMMANDS_OUT_OF_SYNC           ������һ�����ʵ��Ĵ���ִ��
   //CR_SERVER_GONE_ERROR              MySQL�������ر��ˡ�
   //CR_SERVER_LOST                    �Է������������ڲ�ѯ�ڼ�ʧȥ�� 
   //CR_UNKNOWN_ERROR                  ����һ��δ֪�Ĵ��� 

   if(status)
     return FALSE;

   return TRUE;
}

BOOL CMySQL_API::DeleteDatabase(const char *DBName)
{
   char szSqlText[64];
   BOOL Result;
   memset(szSqlText,'\0',64);


   Result = ConnectMySQL(NULL);
   if(!Result)
	 return FALSE;


   strcpy(szSqlText,"DROP DATABASE ");
   if(DBName == NULL)
	  return FALSE;
   strcat(szSqlText,DBName);
  
   //ִ��
   Result = ExecuteSQLCmd(szSqlText);

   return Result;
}

/////////////////////////////////////////////
//���ã�������ѡ�б�
//����TRUE    ��ʾ�����ɹ�
//����FALSE   ��ʾʧ��  
/////////////////////////////////////////////
BOOL CMySQL_API::CreateTable(const char *tbName,PCHAR *Field,int Num)
{
   BOOL status;
   int i;
   char szSqlText[1000];

   memset(szSqlText,'\0',1000);
   //�������ݿ�
   strcpy(szSqlText,"CREATE TABLE ");
   if(tbName == NULL)
	  return FALSE;
   strcat(szSqlText,tbName);


   //�ȼ���Ҫ�ӵ��ֶ�����
   strcat(szSqlText,"(");
   //�ֶ�
   if(Field != NULL)   //ָ���ֶ�
   {
     for(i=0;i<Num;i++)
	 {
	    strcat(szSqlText,Field[i]);
		if(i<Num-1)
		  strcat(szSqlText,",");
	 }
   }
   else     //ûָ���ֶξͼ�һ������������
    strcat(szSqlText,"EntryID int not null primary key auto_increment");
   
   //��������
   strcat(szSqlText,")");


  //ִ�д���
   status = ExecuteSQLCmd(szSqlText);
   if(!status)
   	 return FALSE;

   return TRUE;
}


BOOL CMySQL_API::DeleteTable(const char *tbName)
{
   char szSqlText[64];
   BOOL Result;
   memset(szSqlText,'\0',64);

   strcpy(szSqlText,"DROP TABLE ");
   if(tbName == NULL)
	  return FALSE;
   strcat(szSqlText,tbName);
  
   //ִ��
   Result = ExecuteSQLCmd(szSqlText);

   return Result;
}

//�õ���¼�����õ���һ��
unsigned __int64 CMySQL_API::QuestRecorderSet()
{
   //�õ�һ���洢��¼���Ŀռ�
   m_Res = mysql_store_result(mydata);   //�ڴ�Ҫ�㹻��
   //m_Res = mysql_use_result(mydata);       //����ͨ��fetch�ſ��Եõ�(����ò�����¼����)
   if(m_Res == NULL)
	 return -1;
   //�õ���¼�����ж��ٸ�����
   ResordNum = mysql_num_rows(m_Res);  

   return ResordNum;
}

//
unsigned __int64 CMySQL_API::GetRecordNum()
{
   return ResordNum;
}

//�е�ָ���е��ַ�ֵ
char *CMySQL_API::GetCurrentColString(int Row,int Col)
{
  char **str; 
  str = GetRowString(Row);
  if(str == NULL)
	return NULL;
  else
	return str[Col];

}

//�õ�ָ�����е���ֵ
long int CMySQL_API::GetCurrentColValue(int Row,int Col)
{




   return 0;
}


//����һ��
BOOL CMySQL_API::InsertRow(const char *TableName,const char *ValueStr)
{
  char dstr[256];
  BOOL status;
  memset(dstr,'\0',256);
/////////////////////////////////////////////////
  strcpy(dstr,"INSERT INTO ");
  strcat(dstr,TableName);

  //Ϊ�յĻ�����ʲô
  if(ValueStr == NULL)
	  return FALSE;
  

  strcat(dstr," value ");
  strcat(dstr,ValueStr);
  
////////////////////////////////////////////////////////
  //����
  //INSERT INTO cctv value(0,5,'8265')

  //ִ��SQL
  status = ExecuteSQLCmd(dstr);

  return status;
}


//�޸�ָ������
BOOL CMySQL_API::ModifySpecifyValue(const char *TableName,const char *Sector,const char *NewValueStr,const char *Condition)
{
  char dstr[256];
  BOOL status;
  memset(dstr,'\0',256);
////////////////////////////////////////////////
  if(TableName == NULL || NewValueStr==NULL || Condition == NULL || Sector == NULL)
	 return FALSE;

  /////////////////////
  sprintf(dstr,"UPDATE %s SET %s.%s = %s where %s.%s",TableName,\
	  TableName,Sector,NewValueStr,TableName,Condition);

  //����
  //UPDATE roomstate_base SET roomstate_base.baseType = '����' where roomstate_base.baseType = 'Ĭ��'


  //ִ��SQL
  status = ExecuteSQLCmd(dstr);

  return status;
}


//�޸�ָ������
BOOL CMySQL_API::ModifyRecord(const char *TableName,const char *ValueStr,const char *Condition)
{
  char dstr[256];
  BOOL status;
  memset(dstr,'\0',256);
////////////////////////////////////////////////
  if(TableName == NULL || ValueStr==NULL || Condition == NULL)
	 return FALSE;

  /////////////////////
  sprintf(dstr,"UPDATE %s SET %s where %s",TableName,ValueStr,Condition);

  //����
  //UPDATE roomstate_base SET roomstate_base.baseType = '����' where roomstate_base.baseType = 'Ĭ��'


  //ִ��SQL
  status = ExecuteSQLCmd(dstr);

  return status;
}






















// This is an example of an exported variable
MYSQLPACKET_API int nMySQLPacket=0;


// This is an example of an exported function.
MYSQLPACKET_API int fnMySQLPacket(void)
{
	return 42;
}

char ** CMySQL_API::GetRowString(int rIndex)
{
   //��¼������Ϊ��
   if(m_Res == NULL)
	 return NULL;
   //�����˳��ȡ
   if(rIndex == -1)
      m_Row = mysql_fetch_row(m_Res);   
   else
   {
     if(rIndex < ResordNum)
	 {
	   mysql_data_seek(m_Res,rIndex);
       m_Row = mysql_fetch_row(m_Res);
	 }
   }
   return m_Row;
}


//ɾ��ָ������
BOOL CMySQL_API::DeleteSpecifyRow(const char *TableName,const char *Condition)
{
  char dstr[256];
  BOOL status;
  memset(dstr,'\0',256);

/////////////////////////////////////////////////
  strcpy(dstr,"DELETE FROM ");
  strcat(dstr,TableName);

  //Ϊ�յĻ�ȫɾ��
  if(Condition != NULL)
  {
    strcat(dstr," where ");
    strcat(dstr,Condition);
  }
////////////////////////////////////////////////////////
  //����
  //DELETE FROM cctv where ID = 5
  //DELETE FROM cctv where Name = 'Johnson'

  //ִ��SQL
  status = ExecuteSQLCmd(dstr);

  return status;
}


//////////////////////////////////////////////////////////////////
//���ݹ��ܺ���
BOOL CMySQL_API::BackUpDataBase(PCHAR DbName,PCHAR BackFileName)
{
    char CmdStr[256];
    BOOL status;
    memset(CmdStr,'\0',256); 
	/////////////////////////////////////////
    //strcpy(CmdStr,"Source d:\\0715.sql");
   
	status = ExecuteSQLCmd(CmdStr,FALSE);
    FILE *fp;
	fp = fopen("8765.txt","wt");
    if(status == FALSE)
	{
	  fprintf(fp,"Operation Fail\n\n");
      GetMySQLError(CmdStr);
	  fprintf(fp,"%s",CmdStr);
	}
    fclose(fp);
	return TRUE;
}
















