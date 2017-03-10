// MySQLPacket.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "MySQLPacketClass.h"
#include ".\include\\mysql.h"
#pragma comment(lib,"libmysql.lib")

//////////////////////////////////////////////////////////////////////
//定义全局变量
my_ulonglong ResordNum = 0;
MYSQL* mydata = NULL;
MYSQL_RES* m_Res = NULL;
MYSQL_ROW  m_Row;

//连接字符串


/////////////////////////////////////////////////////////////
//调用CMD(DOS) 窗体
/////////////////////////////////////////////////////////////
MYSQLPACKET_API UINT ExeSystemCmd(PCHAR Cmdstr,BOOL ShowFlag,BOOL ExitFlag)
{
   char Cmd[MAX_PATH];
   UINT Result;
   memset(Cmd,'\0',MAX_PATH);

   //构建指令
   strcpy(Cmd,"cmd /k ");    //调用CMD
   //增加命令字符集
   strcat(Cmd,Cmdstr);       //指令字符串

/* strcat(Cmd,"cmd /k ");    //CMD.exe");
   //数据路径
   strcat(Cmd,"cd ");        //CMD
   strcat(Cmd,MysqlPath);   //Path

   strcat(Cmd," && ");   //连接

   //真正的指令
   strcat(Cmd,Cmdstr);   //指令字符串
*/

   //是否退出
   if(ExitFlag)
   {
     strcat(Cmd," && ");   //连接
     strcat(Cmd,"exit");   //连接
   }


   //是否显示
   if(ShowFlag)
	 Result = WinExec(Cmd, SW_SHOW);
   else
     Result = WinExec(Cmd, SW_HIDE);

   return Result;
}

























/////////////////////////////////////////////////////////////////////////////////////////
//构造函数
CMySQL_API::CMySQL_API(PCHAR host,PCHAR user,PCHAR password,int port)
{
   InitMySQLAPI();
   //赋值
   strcpy(m_HostName,host);   //分配Host名
   strcpy(m_UserName,user);   //分配用户名
   strcpy(m_Passwords,password);  //分配密码
   
   /*strcpy(m_HostName,"localhost");
   strcpy(m_UserName,"root");
   strcpy(m_Passwords,"123456");
  */ m_Port = port;       //端口

}

//析构函数
CMySQL_API::~CMySQL_API()
{
  // CloseMySQL();
  mysql_library_end(); 
}


/////////////////////////////////////////////////////////////////////////////////////////
//成员函数
/////////////////////////////////////////////////////////////////////////////////////////
//初始化一些变量
void CMySQL_API::InitMySQLAPI()
{
   mydata = NULL;
   mysql_library_init(0,NULL,NULL);    //初始化MYSQL 的C  API库
}

//检查状态是否正确
BOOL CMySQL_API::CheckReady()
{
   //句柄有效否
  if(mydata == NULL)    //句柄无效返回假
     return FALSE;


  return TRUE;
}

//万能执行的SQL语句
BOOL CMySQL_API::ExecuteSQLCmd(PCHAR sqlCMD,BOOL Request)
{
   int Result;
   //清空记录值
   if(m_Res != NULL)
     mysql_free_result(m_Res);
 
   m_Res = NULL;
   ResordNum = 0;
   m_Row = NULL;

   //先检查句柄是否有效
   if(!CheckReady())
	 return 0;

   //执行SQL语句
   //Result = mysql_query(mydata,sqlCMD);
   Result = mysql_real_query(mydata,sqlCMD,(DWORD)strlen(sqlCMD));
   if(Result)   //有错就返回
     return FALSE;
 
   //返回值的类型
   //0:表示成功
   //CR_COMMANDS_OUT_OF_SYNC        以不恰当的顺序执行了命令
   //CR_SERVER_GONE_ERROR           MySQL服务器不可用
   //CR_SERVER_LOST                 在查询过程中，与服务器的连接丢失
   //CR_UNKNOWN_ERROR               出现未知错误
/////////////////////////////////////////////////////////////////////////////////////////////////
   if(Request)
   {
     //得到一个存储记录集的空间
     m_Res = mysql_store_result(mydata);   //内存要足够大
     //m_Res = mysql_use_result(mydata);       //必须通过fetch才可以得到
	 if(m_Res == NULL)
		 return FALSE;
     //得到记录集中有多少个对象
     ResordNum = mysql_num_rows(m_Res);    
     if(!ResordNum)
		return FALSE;
   }


   return TRUE;
}


//链接数据库
BOOL CMySQL_API::ConnectMySQL(const char *DBName)
{
 //如果有连接就返回真
    if(mydata != NULL)
      return TRUE;  
 
   //新建一个数据结构句柄
   mydata = new MYSQL(); 
   mysql_init(mydata);    //初始化mydata的数据结构，Mydata是MYSQL对象


   //mysql_select_db(mydata,DBName);
   /////////////////////////////////////////////////////////////////////
   if(mysql_real_connect(mydata,m_HostName,m_UserName,m_Passwords,DBName,m_Port,NULL,0) == NULL)
     return FALSE;     //表示链接数据库有错 
   mysql_query(mydata,"SET NAMES 'GBK'");
   return TRUE;
}


//关闭数据库CMySQL_APICMySQL_API
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
//返回的错误代码
//参数：eDesc 表示的是错误的详细信息
///////////////////////////////////////////////////////////////////
DWORD CMySQL_API::GetMySQLError(char* eDesc)
{
   DWORD ErrorValue;
   ErrorValue = mysql_errno(mydata);   //出错代码

   strcpy(eDesc,mysql_error(mydata));  //出错信息
   return ErrorValue;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//下面是得到一些相关的信息
///////////////////////////////////////////////////////////////////////////////////////////////////
//以字符串形式返回客户端版本信息
const char* CMySQL_API::GetClientInfo()
{   

	return mysql_get_client_info();

}
//以整数形式返回客户端版本信息
unsigned long CMySQL_API::GetClientVersion()
{
   return mysql_get_client_version();
}

//返回描述连接的字符串
const char* CMySQL_API::GetHostInfo()
{
  if(mydata == NULL)
	return NULL;
  return mysql_get_host_info(mydata);

}

//以整数形式返回服务器的版本号
unsigned long CMySQL_API::GetServiceVersion()
{
   if(mydata == NULL)
	  return 0;
   return mysql_get_server_version(mydata);
}

//返回服务器的版本号
const char* CMySQL_API::GetServiceInfo()
{
   if(mydata == NULL)
	  return NULL;

   return mysql_get_server_info(mydata);
}

//返回连接所使用的协议版本
unsigned int CMySQL_API::GetConnectProtocolVersion()
{
   if(mydata == NULL)
	  return 0;
   
   return mysql_get_proto_info(mydata);
}


/////////////////////////////////////////////
//作用：创建并选中表
//返回TRUE    表示创建成功
//返回FALSE   表示失败  
/////////////////////////////////////////////
BOOL CMySQL_API::CreateDatabase(const char *DBName)
{
   BOOL status;
   char szSqlText[64];

   memset(szSqlText,'\0',64);
   //连接数据驱动
   status = ConnectMySQL(NULL);
   if(!status)
	 return FALSE;

   //创建数据库
   strcpy(szSqlText,"CREATE DATABASE ");
   if(DBName == NULL)
	  return FALSE;
   strcat(szSqlText,DBName);

   //执行创建
   status = ExecuteSQLCmd(szSqlText);
   if(!status)
   	 return FALSE;

   //选 择数据库
   status = mysql_select_db(mydata,DBName);
   //返回值
   //0: 正确
   //CR_COMMANDS_OUT_OF_SYNC           命令以一个不适当的次序被执行
   //CR_SERVER_GONE_ERROR              MySQL服务器关闭了。
   //CR_SERVER_LOST                    对服务器的连接在查询期间失去。 
   //CR_UNKNOWN_ERROR                  发生一个未知的错误。 

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
  
   //执行
   Result = ExecuteSQLCmd(szSqlText);

   return Result;
}

/////////////////////////////////////////////
//作用：创建并选中表
//返回TRUE    表示创建成功
//返回FALSE   表示失败  
/////////////////////////////////////////////
BOOL CMySQL_API::CreateTable(const char *tbName,PCHAR *Field,int Num)
{
   BOOL status;
   int i;
   char szSqlText[1000];

   memset(szSqlText,'\0',1000);
   //创建数据库
   strcpy(szSqlText,"CREATE TABLE ");
   if(tbName == NULL)
	  return FALSE;
   strcat(szSqlText,tbName);


   //先加是要加的字段括号
   strcat(szSqlText,"(");
   //字段
   if(Field != NULL)   //指定字段
   {
     for(i=0;i<Num;i++)
	 {
	    strcat(szSqlText,Field[i]);
		if(i<Num-1)
		  strcat(szSqlText,",");
	 }
   }
   else     //没指定字段就加一个自增的主键
    strcat(szSqlText,"EntryID int not null primary key auto_increment");
   
   //结束括号
   strcat(szSqlText,")");


  //执行创建
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
  
   //执行
   Result = ExecuteSQLCmd(szSqlText);

   return Result;
}

//得到记录集并得到第一行
unsigned __int64 CMySQL_API::QuestRecorderSet()
{
   //得到一个存储记录集的空间
   m_Res = mysql_store_result(mydata);   //内存要足够大
   //m_Res = mysql_use_result(mydata);       //必须通过fetch才可以得到(下面得不到记录总数)
   if(m_Res == NULL)
	 return -1;
   //得到记录集中有多少个对象
   ResordNum = mysql_num_rows(m_Res);  

   return ResordNum;
}

//
unsigned __int64 CMySQL_API::GetRecordNum()
{
   return ResordNum;
}

//列到指定列的字符值
char *CMySQL_API::GetCurrentColString(int Row,int Col)
{
  char **str; 
  str = GetRowString(Row);
  if(str == NULL)
	return NULL;
  else
	return str[Col];

}

//得到指定行列的数值
long int CMySQL_API::GetCurrentColValue(int Row,int Col)
{




   return 0;
}


//增加一行
BOOL CMySQL_API::InsertRow(const char *TableName,const char *ValueStr)
{
  char dstr[256];
  BOOL status;
  memset(dstr,'\0',256);
/////////////////////////////////////////////////
  strcpy(dstr,"INSERT INTO ");
  strcat(dstr,TableName);

  //为空的话不做什么
  if(ValueStr == NULL)
	  return FALSE;
  

  strcat(dstr," value ");
  strcat(dstr,ValueStr);
  
////////////////////////////////////////////////////////
  //举例
  //INSERT INTO cctv value(0,5,'8265')

  //执行SQL
  status = ExecuteSQLCmd(dstr);

  return status;
}


//修改指定的行
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

  //举例
  //UPDATE roomstate_base SET roomstate_base.baseType = '汤丹' where roomstate_base.baseType = '默认'


  //执行SQL
  status = ExecuteSQLCmd(dstr);

  return status;
}


//修改指定的行
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

  //举例
  //UPDATE roomstate_base SET roomstate_base.baseType = '汤丹' where roomstate_base.baseType = '默认'


  //执行SQL
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
   //记录集不能为空
   if(m_Res == NULL)
	 return NULL;
   //如果是顺序取
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


//删除指定的行
BOOL CMySQL_API::DeleteSpecifyRow(const char *TableName,const char *Condition)
{
  char dstr[256];
  BOOL status;
  memset(dstr,'\0',256);

/////////////////////////////////////////////////
  strcpy(dstr,"DELETE FROM ");
  strcat(dstr,TableName);

  //为空的话全删完
  if(Condition != NULL)
  {
    strcat(dstr," where ");
    strcat(dstr,Condition);
  }
////////////////////////////////////////////////////////
  //举例
  //DELETE FROM cctv where ID = 5
  //DELETE FROM cctv where Name = 'Johnson'

  //执行SQL
  status = ExecuteSQLCmd(dstr);

  return status;
}


//////////////////////////////////////////////////////////////////
//备份功能函数
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
















