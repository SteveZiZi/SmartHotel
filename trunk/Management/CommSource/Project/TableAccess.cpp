#include "stdafx.h"
////////////////////////////////////////////////////////////////
BOOL status = NULL;				//执行命令的状态返回结果
char **m_Row;					//一条记录
CString CmdStr;					//查询的命令字符串
unsigned __int64 RecordNum;		//查询的记录总数
////////////////////////////////////////////////////////////////////////////////////////////////
DWORD ConvertString2Hex(PCHAR pString,int nNum)
{
	DWORD dwValue = 0;
	int Index = 0;
	DWORD nTemp;
	for (Index=0;Index<nNum;Index++)
	{
		if ((pString[Index]<='9') && (pString[Index]>='0'))
		{	nTemp = pString[Index] - '0';	}
		if ((pString[Index]<='F') && (pString[Index]>='A'))
		{	nTemp = pString[Index] - 'A'+10;	}
		if ((pString[Index]<='f') && (pString[Index]>='a'))
		{	nTemp = pString[Index] - 'a'+10;	}

		dwValue |= nTemp << (4*(nNum-Index-1));
	}
	return dwValue;
}
//第一部分：房态表
//==========================================================================
unsigned __int64	GetRoomStatusRecord(int TypeFlag,PROOMSTATUS_ENTRY *pRoomStatus,const char *pExtern)
{
	unsigned __int64   Index = 0;
	PROOMSTATUS_ENTRY  pLastEntry;
	//构造房态字符串
	if(pExtern == NULL)
	CmdStr.Format("SELECT *FROM %s",sRoomStatusName[TypeFlag]); 
	else
	CmdStr.Format("SELECT *FROM %s WHERE %s",sRoomStatusName[TypeFlag],pExtern); 
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)CmdStr,FALSE);
	if(status == FALSE)
	{
		//char ErrInfo[MAX_PATH];
		//m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		return	Index;
	}
	//取记录数
	RecordNum = m_mysql->QuestRecorderSet();
	for(Index=0;Index<RecordNum;Index++)
	{
		PROOMSTATUS_ENTRY  m_pRoomState;
		m_pRoomState = new ROOMSTATUS_ENTRY;
		ZeroMemory(m_pRoomState,sizeof(ROOMSTATUS_ENTRY));
		//形如: 2   Name    50   30
		m_Row = m_mysql->GetRowString();
		//==============================================
		m_pRoomState->dwEntryIndex = atoi(m_Row[0]);
		strcpy(m_pRoomState->cName,m_Row[1]);
		m_pRoomState->bEnDualPort = atoi(m_Row[2]);
		m_pRoomState->dwExtend = atoi(m_Row[3]);
		strcpy(m_pRoomState->vSharpPath,m_Row[4]);
		//==============================================
		if(!Index)
			*pRoomStatus = m_pRoomState;
		else
			pLastEntry->pNext = m_pRoomState;
		pLastEntry = m_pRoomState;
	}

	if(RecordNum)
		pLastEntry->pNext = NULL;
	return	Index;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//第二部分：设备表
//==========================================================================
unsigned __int64	GetEquipmentRecord(int TypeFlag,PEQUIPMENT_ENTRY *pEquipment,const char *pExtern)
{
	unsigned __int64   Index = 0;
	PEQUIPMENT_ENTRY  pLastEntry;
	//构造字符串
	if(pExtern == NULL)
		CmdStr.Format("SELECT *FROM %s",sEquipmentTbName[TypeFlag]); 
	else
		CmdStr.Format("SELECT *FROM %s WHERE %s",sEquipmentTbName[TypeFlag],pExtern); 
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)CmdStr,FALSE);
	if(status == FALSE)
	{
		//char ErrInfo[MAX_PATH];
		//m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		return	Index;
	}
	//取记录数
	RecordNum = m_mysql->QuestRecorderSet();
	for(Index=0;Index<RecordNum;Index++)
	{
		PEQUIPMENT_ENTRY  m_pEquipment;
		m_pEquipment = new EQUIPMENT_ENTRY;
		ZeroMemory(m_pEquipment,sizeof(ROOMSTATUS_ENTRY));
		//形如:
		m_Row = m_mysql->GetRowString();
		//==============================================
		m_pEquipment->dwEntryIndex = atoi(m_Row[0]);
		strcpy(m_pEquipment->cName,m_Row[1]);
		m_pEquipment->bEnDualPort = atoi(m_Row[2]);
		m_pEquipment->wType = atoi(m_Row[3]);
		m_pEquipment->dwExtend = atoi(m_Row[4]);
		strcpy(m_pEquipment->vSharpPath,m_Row[5]);
		//==============================================
		if(!Index)
			*pEquipment = m_pEquipment;
		else
			pLastEntry->pNext = m_pEquipment;
		pLastEntry = m_pEquipment;
	}
	if(RecordNum)
		pLastEntry->pNext = NULL;
	return	Index;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//第三部分：RCU表
//==========================================================================
unsigned __int64 GetRCUTypeRecord(PRCU_TYPE_ENTRY *pRCUType,const char *pExtern)
{
	unsigned __int64   Index = 0;
	PRCU_TYPE_ENTRY  pLastEntry;
	//构造字符串
	if(pExtern == NULL)
		CmdStr.Format("SELECT *FROM %s",RCUTypeTableName); 
	else
		CmdStr.Format("SELECT *FROM %s WHERE %s",RCUTypeTableName,pExtern); 
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)CmdStr,FALSE);
	if(status == FALSE)
	{
		//char ErrInfo[MAX_PATH];
		//m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		return	Index;
	}
	//取记录数
	RecordNum = m_mysql->QuestRecorderSet();
	for(Index=0;Index<RecordNum;Index++)
	{
		PRCU_TYPE_ENTRY  m_pEntry;
		m_pEntry = new RCU_TYPE_ENTRY();
		ZeroMemory(m_pEntry,sizeof(RCU_TYPE_ENTRY));
		//形如:
		m_Row = m_mysql->GetRowString();
		//==============================================
		m_pEntry->RCUId = atoi(m_Row[0]);
		strcpy(m_pEntry->RCUName,m_Row[1]);
		m_pEntry->wEquipPortNum = atoi(m_Row[2]);
		m_pEntry->wStatusPortNum = atoi(m_Row[3]);

		m_pEntry->pEquipDetail = new RCU_PORT_UNIT[m_pEntry->wEquipPortNum];
		m_pEntry->pStatusDetail = new RCU_PORT_UNIT[m_pEntry->wStatusPortNum];
		
		if(m_pEntry->pEquipDetail != NULL)
		{
			ZeroMemory(m_pEntry->pEquipDetail,sizeof(RCU_PORT_UNIT)*m_pEntry->wEquipPortNum);
			if(m_Row[4] != NULL)
			  memcpy(m_pEntry->pEquipDetail,m_Row[4],sizeof(RCU_PORT_UNIT)*m_pEntry->wEquipPortNum);
		}
		if(m_pEntry->pStatusDetail != NULL)
		{
			ZeroMemory(m_pEntry->pStatusDetail,sizeof(RCU_PORT_UNIT)*m_pEntry->wStatusPortNum);
			if(m_Row[5] != NULL)
			  memcpy(m_pEntry->pStatusDetail,m_Row[4],sizeof(RCU_PORT_UNIT)*m_pEntry->wStatusPortNum);
		}
		//nDataLen = (int)FieldLength[nCol];   pDataOut = (char*)(m_ItemMySqlRow[nCol]);
		//==============================================
		if(!Index)
			*pRCUType = m_pEntry;

		else
			pLastEntry->pNext = m_pEntry;

		pLastEntry = m_pEntry;
   }
   if(RecordNum)
		pLastEntry->pNext = NULL;
   return	Index;
}





////////////////////////////////////////////////////////////////////////////////////////////////
//设备配置方案表
//==========================================================================
unsigned __int64 GetDeviceCfgMethodRecord(CPtrArray &pRecordArray,const char *pExtern)
{
	unsigned __int64	nNum = 0;
	PDEVICE_CFG_METHOD  pTempEntry = NULL;
	//构造字符串
	if(pExtern == NULL)
		CmdStr.Format("SELECT *FROM %s",DeviceCfgMethodTableName); 
	else
		CmdStr.Format("SELECT *FROM %s WHERE %s",DeviceCfgMethodTableName,pExtern); 
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)CmdStr,FALSE);
	if(status == FALSE)	{	return nNum;}
	//取记录数
	RecordNum = m_mysql->QuestRecorderSet();
	for(nNum=0;nNum<RecordNum;nNum++)
	{
		pTempEntry = new DEVICE_CFG_METHOD;
		if (pTempEntry == NULL)	{	break;	}
		ZeroMemory(pTempEntry,sizeof(DEVICE_CFG_METHOD));
		m_Row = m_mysql->GetRowString();
		if (m_Row == NULL)	{	break;	}
		//==================================================
		pTempEntry->dwID =  atoi(m_Row[0]);
		pTempEntry->dwMethodID =  atoi(m_Row[1]);

		pTempEntry->bEntry =  atoi(m_Row[2]);
		pTempEntry->bType =  atoi(m_Row[3]);
		pTempEntry->bSublun =  atoi(m_Row[4]);
		//pTempEntry->bResv =  atoi(m_Row[5]);

		strcpy(pTempEntry->sLun,m_Row[5]);
		strcpy(pTempEntry->LunView,m_Row[6]);

		pRecordArray.Add(pTempEntry);
	}
	return	nNum;
}


BOOL InsertDeviceCfgMethodRecord(PDEVICE_CFG_METHOD pTempEntry)
{
	BOOL bRest = FALSE;
	CString str;
	if (pTempEntry == NULL)	{	return bRest;	}

	str.Format("INSERT INTO %s VALUE(%d,%d,%d,%d,%d,'%s','%s')",DeviceCfgMethodTableName,\
		pTempEntry->dwID,pTempEntry->dwMethodID,pTempEntry->bEntry,pTempEntry->bType,pTempEntry->bSublun,\
		pTempEntry->sLun,pTempEntry->LunView);

	bRest = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(bRest == FALSE)
	{
		char ErrInfo[MAX_PATH];
		m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		//delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return	FALSE;
	}
	return bRest;
}


BOOL ModifyDeviceCfgMethodRecord(PDEVICE_CFG_METHOD pTempEntry,const char *pExtern)
{
	BOOL bRest = FALSE;
	CString str;
	if (pTempEntry == NULL)	{	return bRest;	}
	if (pExtern != NULL){
		str.Format("UPDATE %s SET LunString='%s',DeviceView='%s' WHERE %s",DeviceCfgMethodTableName,\
			pTempEntry->sLun,pTempEntry->LunView,pExtern);
	}else{
		str.Format("UPDATE %s SET LunString='%s',DeviceView='%s' WHERE RCUID=%d AND DeviceEntry=%d AND DeviceType=%d AND LunIndex=%d",DeviceCfgMethodTableName,\
			pTempEntry->sLun,pTempEntry->LunView,pTempEntry->dwMethodID,pTempEntry->bEntry,pTempEntry->bType,pTempEntry->bSublun);
	}
	bRest = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(bRest == FALSE)
	{
		char ErrInfo[MAX_PATH];
		m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		//delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return	FALSE;
	}
	return bRest;
}
BOOL DeleteDeviceCfgMethodRecord(PDEVICE_CFG_METHOD pTempEntry,const char *pExtern)
{
	BOOL bRest = FALSE;
	CString str;
	if (pTempEntry == NULL)	{	return bRest;	}
	if (pExtern != NULL){
		str.Format("DELETE FROM %s WHERE %s",DeviceCfgMethodTableName,pExtern);
	}else{
		str.Format("DELETE FROM %s WHERE RCUID=%d AND DeviceEntry=%d AND DeviceType=%d AND LunIndex=%d",DeviceCfgMethodTableName,\
			pTempEntry->dwMethodID,pTempEntry->bEntry,pTempEntry->bType,pTempEntry->bSublun);
	}
	bRest = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(bRest == FALSE)
	{
		char ErrInfo[MAX_PATH];
		m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		//delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return	FALSE;
	}
	return bRest;
}



void ReleaseDeviceCfgMethodRecord(CPtrArray &pRecordArray)
{
	PDEVICE_CFG_METHOD  pTempEntry = NULL;
	INT_PTR Index = 0;
	for (Index=0;Index<pRecordArray.GetCount();Index++)
	{
		pTempEntry = (PDEVICE_CFG_METHOD)pRecordArray.GetAt(Index);
		if (pTempEntry != NULL)	{	delete pTempEntry;	}
	}

	if (Index)	{	pRecordArray.RemoveAll();	}
}

//用户表的配置
unsigned __int64 GetUserInfoRecord(CPtrArray &pRecordArray,const char *pExtern)
{
	unsigned __int64	nNum = 0;
	PUSER_INFORMATION  pTempEntry = NULL;
	//构造字符串
	if(pExtern == NULL)
		CmdStr.Format("SELECT *FROM %s",UserTableName); 
	else
		CmdStr.Format("SELECT *FROM %s WHERE %s",UserTableName,pExtern); 
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)CmdStr,FALSE);
	if(status == FALSE)	{	return nNum;}
	//取记录数
	RecordNum = m_mysql->QuestRecorderSet();
	for(nNum=0;nNum<RecordNum;nNum++)
	{
		pTempEntry = new USER_INFORMATION;
		if (pTempEntry == NULL)	{	break;	}
		ZeroMemory(pTempEntry,sizeof(USER_INFORMATION));
		m_Row = m_mysql->GetRowString();
		if (m_Row == NULL)	{	break;	}
		//==================================================
		strcpy(pTempEntry->sName,m_Row[0]);
		strcpy(pTempEntry->sPasswords,m_Row[1]);
		pTempEntry->nDepartment =  atoi(m_Row[2]);
		pTempEntry->dwPermission =  ConvertString2Hex(m_Row[3],8);
		pRecordArray.Add(pTempEntry);
	}
	return	nNum;
}

BOOL InsertUserInfoRecord(PUSER_INFORMATION pTempEntry)
{
	BOOL bRest = FALSE;
	CString str;
	if (pTempEntry == NULL)	{	return bRest;	}

	str.Format("INSERT INTO %s VALUE('%s','%s',%d,'%08X')",UserTableName,\
		pTempEntry->sName,pTempEntry->sPasswords,pTempEntry->nDepartment,pTempEntry->dwPermission);

	bRest = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(bRest == FALSE)
	{
		char ErrInfo[MAX_PATH];
		m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		//delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return	FALSE;
	}
	return bRest;
}
BOOL ModifyUserInfoRecord(PUSER_INFORMATION pTempEntry,const char *pExtern)
{
	BOOL bRest = FALSE;
	CString str;
	if (pTempEntry == NULL)	{	return bRest;	}
	if (pExtern != NULL){
		str.Format("UPDATE %s SET password='%s',Permission='%08X' WHERE %s",UserTableName,\
			pTempEntry->sPasswords,pTempEntry->dwPermission,pExtern);
	}else{
		str.Format("UPDATE %s SET password='%s',Permission='%08X' WHERE userID='%s'",UserTableName,\
				   pTempEntry->sPasswords,pTempEntry->dwPermission,pTempEntry->sName);
	}
	bRest = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(bRest == FALSE)
	{
		char ErrInfo[MAX_PATH];
		m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		//delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return	FALSE;
	}
	return bRest;
}
BOOL DeleteUserInfoRecord(PUSER_INFORMATION pTempEntry,const char *pExtern)
{
	BOOL bRest = FALSE;
	CString str;
	if (pTempEntry == NULL)	{	return bRest;	}
	if (pExtern == NULL){	return TRUE;	}
	str.Format("DELETE FROM %s WHERE %s",UserTableName,pExtern);

	bRest = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(bRest == FALSE)
	{
		char ErrInfo[MAX_PATH];
		m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		//delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return	FALSE;
	}
	return bRest;
}
void ReleaseUserInfoRecord(CPtrArray &pRecordArray)
{
	PUSER_INFORMATION  pTempEntry = NULL;
	INT_PTR Index = 0;
	for (Index=0;Index<pRecordArray.GetCount();Index++)
	{
		pTempEntry = (PUSER_INFORMATION)pRecordArray.GetAt(Index);
		if (pTempEntry != NULL)	{	delete pTempEntry;	}
	}

	if (Index)	{	pRecordArray.RemoveAll();	}
}




////////////////////////////////////////////////////////////////////////////////////////////////
//第四部分：房类配置表
//==========================================================================
unsigned __int64	GetRoomTypeRecord(PROOM_TYPE_ENTRY *pRoomType,const char *pExtern)
{
	unsigned __int64   Index = 0;
	PROOM_TYPE_ENTRY  pLastEntry;
	//构造字符串
	if(pExtern == NULL)
		CmdStr.Format("SELECT *FROM %s",roomTypeSettingTableName); 
	else
		CmdStr.Format("SELECT *FROM %s WHERE %s",roomTypeSettingTableName,pExtern); 
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)CmdStr,FALSE);
	if(status == FALSE)
	{
	  //char ErrInfo[MAX_PATH];
	  //m_mysql->GetMySQLError(ErrInfo);
	  //MessageBox(ErrInfo);
	  return	Index;
	}
 //取记录数
	RecordNum = m_mysql->QuestRecorderSet();
	for(Index=0;Index<RecordNum;Index++)
	{
		PROOM_TYPE_ENTRY  m_pEntry;
		m_pEntry = new ROOM_TYPE_ENTRY();
		ZeroMemory(m_pEntry,sizeof(ROOM_TYPE_ENTRY));
		//形如:
		m_Row = m_mysql->GetRowString();
		//==============================================
		m_pEntry->dwEntryIndex = atoi(m_Row[0]);
		strcpy(m_pEntry->cName,m_Row[1]);
		m_pEntry->dwExRCU = atoi(m_Row[2]);
		//==============================================
		if(!Index)
			*pRoomType = m_pEntry;
		else
			pLastEntry->pNext = m_pEntry;

		pLastEntry = m_pEntry;
	}
	if(RecordNum)
		pLastEntry->pNext = NULL;
   return	Index;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//第五部分：楼座配置表
//==========================================================================
unsigned __int64	GetBuildingRecord(PBUILDING_ENTRY *pBuilding,const char *pExtern)
{
	unsigned __int64   Index = 0;
	PBUILDING_ENTRY  pLastEntry;
	//构造字符串
	if(pExtern == NULL)
		CmdStr.Format("SELECT *FROM %s",BuildingTableName); 
	else
		CmdStr.Format("SELECT *FROM %s WHERE %s",BuildingTableName,pExtern); 
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)CmdStr,FALSE);
	if(status == FALSE)
	{
	  //char ErrInfo[MAX_PATH];
	  //m_mysql->GetMySQLError(ErrInfo);
	  //MessageBox(ErrInfo);
	  return	Index;
	}
 //取记录数
   RecordNum = m_mysql->QuestRecorderSet();
   for(Index=0;Index<RecordNum;Index++)
   {
	 PBUILDING_ENTRY  m_pEntry;
	 m_pEntry = new BUILDING_ENTRY();
	 ZeroMemory(m_pEntry,sizeof(BUILDING_ENTRY));
	 //形如:
	 m_Row = m_mysql->GetRowString();
	 //==============================================
	 m_pEntry->dwEntryIndex = atoi(m_Row[0]);
	 strcpy(m_pEntry->cName,m_Row[1]);
     m_pEntry->dwFloorNum = atoi(m_Row[2]);
	 m_pEntry->dwExtend = atoi(m_Row[3]);
	 //==============================================
	 if(!Index)
	   *pBuilding = m_pEntry;
	 else
		pLastEntry->pNext = m_pEntry;
	 
	 pLastEntry = m_pEntry;
   }
   if(RecordNum)
		pLastEntry->pNext = NULL;
   return	Index;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//第六部分：客房配置表
//==========================================================================
unsigned __int64	GetRoomRecord(PROOM_DETAIL_ENTRY *pRoom,const char *pExtern)
{
	unsigned __int64   Index = 0;
	PROOM_DETAIL_ENTRY  pLastEntry;
	//构造字符串
	if(pExtern == NULL)
		CmdStr.Format("SELECT *FROM %s",RoomSetTableName); 
	else
		CmdStr.Format("SELECT *FROM %s WHERE %s",RoomSetTableName,pExtern); 
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)CmdStr,FALSE);
	
	if(status == FALSE)
	{
	  //char ErrInfo[MAX_PATH];
	  //m_mysql->GetMySQLError(ErrInfo);
	  //MessageBox(ErrInfo);
	  return	Index;
	}
 //取记录数
   RecordNum = m_mysql->QuestRecorderSet();
   for(Index=0;Index<RecordNum;Index++)
   {
	 PROOM_DETAIL_ENTRY  m_pEntry;
	 m_pEntry = new ROOM_DETAIL_ENTRY();
	 ZeroMemory(m_pEntry,sizeof(ROOM_DETAIL_ENTRY));
	 //形如:
	 m_Row = m_mysql->GetRowString();
	 //==============================================
	 m_pEntry->dwEntryIndex = atoi(m_Row[0]);
	 m_pEntry->bRoomNum = atoi(m_Row[1]);
	 m_pEntry->bFloorNum = atoi(m_Row[2]);
	 m_pEntry->bBuildingNum = atoi(m_Row[3]);
	 m_pEntry->dwRoomTypeID = atoi(m_Row[4]);
	 strcpy(m_pEntry->sIpAddress,m_Row[5]);

     m_pEntry->dwPort = atoi(m_Row[6]);

	 m_pEntry->pEquipBlock = NULL;
	 m_pEntry->pStatusBlock = NULL;
	 //==============================================
	 if(!Index)
	   *pRoom = m_pEntry;

	 else
		pLastEntry->pNext = m_pEntry;
	 
	 pLastEntry = m_pEntry;
   }
   if(RecordNum)
		pLastEntry->pNext = NULL;
   return	Index;
}

//************************************************************************************
//  Get BufferLength From Room
//************************************************************************************
int GetBufferLengthFromRoom(PVOID lParam,ULONG &InLenA,ULONG &InLenB)
{
	PROOM_DETAIL_ENTRY  pRoomEntry = (PROOM_DETAIL_ENTRY)lParam;		//客房
	PROOM_TYPE_ENTRY	pRoomTypeEntry = NULL;
	PRCU_TYPE_ENTRY		pRCUEntry = NULL;
	int RCU = -1;
	CString str;
	ULONG Result;
//****************************************************************************
	InLenA = InLenB = 0;
	if(lParam == NULL)
		return -1;

//1:先得到RCU
	str.Format("ID=%d",pRoomEntry->dwRoomTypeID);
	Result = (ULONG)GetRoomTypeRecord(&pRoomTypeEntry,str);
	if(!Result)
	{
		while(pRoomTypeEntry != NULL)
		{
			PROOM_TYPE_ENTRY mRt = 	pRoomTypeEntry->pNext;
			delete[] pRoomTypeEntry;
			pRoomTypeEntry = mRt;
		}
		return -1;
	}
	RCU = pRoomTypeEntry->dwExRCU;
//2:再得到数量
	str.Format("ID=%d",pRoomTypeEntry->dwExRCU);
	Result = (ULONG)GetRCUTypeRecord(&pRCUEntry,str);
	if(!Result)
	{
		while(pRoomTypeEntry != NULL)
		{
			PROOM_TYPE_ENTRY mRt = 	pRoomTypeEntry->pNext;
			delete[] pRoomTypeEntry;
			pRoomTypeEntry = mRt;
		}
		//*************************************************
		while(pRCUEntry != NULL)
		{
			PRCU_TYPE_ENTRY mRcu = pRCUEntry->pNext;
			delete[] pRCUEntry;
			pRCUEntry = mRcu;
		}
		return -1;
	}

	InLenA = pRCUEntry->wEquipPortNum;								//设备端口数	
	InLenB = pRCUEntry->wStatusPortNum;
//****************************************************************
	while(pRoomTypeEntry != NULL)
	{
		PROOM_TYPE_ENTRY mRt = 	pRoomTypeEntry->pNext;
		delete[] pRoomTypeEntry;
		pRoomTypeEntry = mRt;
	}
	while(pRCUEntry != NULL)
	{
		PRCU_TYPE_ENTRY mRcu = pRCUEntry->pNext;
		delete[] pRCUEntry;
		pRCUEntry = mRcu;
	}
	return RCU;
}


//用户登陆信息的记录获取
unsigned __int64 GetLoginInfoRecord(CPtrArray &pRecordArray,const char *pExtern)
{
	unsigned __int64	nNum = 0;
	PUSER_LOGIN_INFORMATION  pTempEntry = NULL;
	//构造字符串
	if(pExtern == NULL)
		CmdStr.Format("SELECT *FROM %s",UserLoginInfoTableName); 
	else
		CmdStr.Format("SELECT *FROM %s WHERE %s",UserLoginInfoTableName,pExtern); 
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)CmdStr,FALSE);
	if(status == FALSE)	{	return nNum;}
	//取记录数
	RecordNum = m_mysql->QuestRecorderSet();
	for(nNum=0;nNum<RecordNum;nNum++)
	{
		pTempEntry = new USER_LOGIN_INFORMATION;
		if (pTempEntry == NULL)	{	break;	}
		pTempEntry->dwID = 0;
		ZeroMemory(pTempEntry->sName,MAX_PATH);
		m_Row = m_mysql->GetRowString();
		if (m_Row == NULL)	{	break;	}
		//==================================================
		pTempEntry->dwID =  atoi(m_Row[0]);
		strcpy(pTempEntry->sName,m_Row[1]);
		int  nYear,nMonth,nDate,nHour,nMin,nSec;
		sscanf(m_Row[2],"%d-%d-%d %d:%d:%d",&nYear,&nMonth,&nDate,&nHour,&nMin,&nSec);
		CTime loginIn(nYear,nMonth,nDate,nHour,nMin,nSec);
		pTempEntry->mtLogin = loginIn;
		
		sscanf(m_Row[3],"%d-%d-%d %d:%d:%d",&nYear,&nMonth,&nDate,&nHour,&nMin,&nSec);
		CTime logOut(nYear,nMonth,nDate,nHour,nMin,nSec);
		pTempEntry->mtExit = logOut;
		//strcpy(pTempEntry->LunView,m_Row[6]);

		pRecordArray.Add(pTempEntry);
	}
	return	nNum;
}
BOOL InsertLoginInfoRecord(LPVOID lParam)
{
	BOOL bRest = FALSE;
	PUSER_LOGIN_INFORMATION  pTempEntry = reinterpret_cast<PUSER_LOGIN_INFORMATION>(lParam);
	CString str;
	if (pTempEntry == NULL)	{	return bRest;	}

	str.Format("INSERT INTO %s VALUE(%d,'%s','%d-%d-%d %d:%d:%d','%d-%d-%d %d:%d:%d')",UserLoginInfoTableName,\
		pTempEntry->dwID,pTempEntry->sName,pTempEntry->mtLogin.GetYear(),pTempEntry->mtLogin.GetMonth(),\
		pTempEntry->mtLogin.GetDay(),pTempEntry->mtLogin.GetHour(),pTempEntry->mtLogin.GetMinute(),pTempEntry->mtLogin.GetSecond(),\
		pTempEntry->mtExit.GetYear(),pTempEntry->mtExit.GetMonth(),pTempEntry->mtExit.GetDay(),\
		pTempEntry->mtExit.GetHour(),pTempEntry->mtExit.GetMinute(),pTempEntry->mtExit.GetSecond());

	bRest = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(bRest == FALSE)
	{
		char ErrInfo[MAX_PATH];
		m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		//delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return	FALSE;
	}
	return bRest;
}
BOOL ModifyLoginInfoRecord(LPVOID lParam,const char *pExtern)
{
	BOOL bRest = FALSE;
	CString str;
	PUSER_LOGIN_INFORMATION  pTempEntry = reinterpret_cast<PUSER_LOGIN_INFORMATION>(lParam);
	if (pTempEntry == NULL)	{	return bRest;	}
	if (pExtern != NULL){
		str.Format("UPDATE %s SET LoginOut=%d-%d-%d %d:%d:%d WHERE LoginIn=%d-%d-%d %d:%d:%d",UserLoginInfoTableName,\
			pTempEntry->mtExit.GetYear(),pTempEntry->mtExit.GetMonth(),pTempEntry->mtExit.GetDay(),
			pTempEntry->mtExit.GetHour(),pTempEntry->mtExit.GetMinute(),pTempEntry->mtExit.GetSecond(),\
			pTempEntry->mtLogin.GetYear(),pTempEntry->mtLogin.GetMonth(),pTempEntry->mtLogin.GetDay(),\
			pTempEntry->mtLogin.GetHour(),pTempEntry->mtLogin.GetMinute(),pTempEntry->mtLogin.GetSecond());
	}
	bRest = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(bRest == FALSE)
	{
		char ErrInfo[MAX_PATH];
		m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		//delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return	FALSE;
	}
	return bRest;
}
BOOL DeleteLoginInfoRecord(LPVOID lParam,const char *pExtern)
{
	BOOL bRest = FALSE;
	CString str;
	PUSER_LOGIN_INFORMATION  pTempEntry = reinterpret_cast<PUSER_LOGIN_INFORMATION>(lParam);
	if (pTempEntry == NULL)	{	return bRest;	}
	if (pExtern != NULL){
		str.Format("DELETE FROM %s WHERE %s",UserLoginInfoTableName,pExtern);
	}else{
		str.Format("DELETE FROM %s WHERE LoginIn='%d-%d-%d %d:%d:%d'",UserLoginInfoTableName,\
			pTempEntry->mtLogin.GetYear(),pTempEntry->mtLogin.GetMonth(),pTempEntry->mtLogin.GetDay(),\
			pTempEntry->mtLogin.GetHour(),pTempEntry->mtLogin.GetMinute(),pTempEntry->mtLogin.GetSecond());
	}
	bRest = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(bRest == FALSE)
	{
		char ErrInfo[MAX_PATH];
		m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		//delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return	FALSE;
	}
	return bRest;
}



void ReleaseLoginInfoRecord(CPtrArray &pRecordArray)
{
	PUSER_LOGIN_INFORMATION  pTempEntry = NULL;
	INT_PTR Index = 0;
	for (Index=0;Index<pRecordArray.GetCount();Index++)
	{
		pTempEntry = (PUSER_LOGIN_INFORMATION)pRecordArray.GetAt(Index);
		if (pTempEntry != NULL)	{	delete pTempEntry;	}
	}

	if (Index)	{	pRecordArray.RemoveAll();	}
}


//增加工程部表
unsigned __int64 GetDepartmentInfoRecord(CPtrArray &pRecordArray,const char *pExtern)
{
	unsigned __int64	nNum = 0;
	PDEPARTMENT_INFORMATION  pTempEntry = NULL;
	//构造字符串
	if(pExtern == NULL)
		CmdStr.Format("SELECT *FROM %s",DepartmentTableName); 
	else
		CmdStr.Format("SELECT *FROM %s WHERE %s",DepartmentTableName,pExtern); 
	status = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)CmdStr,FALSE);
	if(status == FALSE)	{	return nNum;}
	//取记录数
	RecordNum = m_mysql->QuestRecorderSet();
	for(nNum=0;nNum<RecordNum;nNum++)
	{
		pTempEntry = new DEPARTMENT_INFORMATION;
		if (pTempEntry == NULL)	{	break;	}
		ZeroMemory(pTempEntry,sizeof(DEPARTMENT_INFORMATION));
		m_Row = m_mysql->GetRowString();
		if (m_Row == NULL)	{	break;	}
		//==================================================
		pTempEntry->dwID =  atoi(m_Row[0]);
		strcpy(pTempEntry->sName,m_Row[1]);
		pTempEntry->dwPermission =  atoi(m_Row[2]);

		pRecordArray.Add(pTempEntry);
	}
	return	nNum;
}

BOOL InsertDepartmentInfoRecord(LPVOID lParam)
{
	BOOL bRest = FALSE;
	CString str;
	PDEPARTMENT_INFORMATION  pTempEntry = reinterpret_cast<PDEPARTMENT_INFORMATION>(lParam);
	if (pTempEntry == NULL)	{	return bRest;	}

	str.Format("INSERT INTO %s VALUE(%d,'%s',%d)",DepartmentTableName,\
		pTempEntry->dwID,pTempEntry->sName,pTempEntry->dwPermission);

	bRest = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(bRest == FALSE)
	{
		char ErrInfo[MAX_PATH];
		m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		//delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return	FALSE;
	}
	return bRest;
}
BOOL ModifyDepartmentInfoRecord(LPVOID lParam,const char *pExtern)
{
	BOOL bRest = FALSE;
	CString str;
	PDEPARTMENT_INFORMATION  pTempEntry = reinterpret_cast<PDEPARTMENT_INFORMATION>(lParam);
	if (pTempEntry == NULL)	{	return bRest;	}
	if (pExtern != NULL){
		str.Format("UPDATE %s SET  authority=%d WHERE %s",DepartmentTableName,pTempEntry->dwPermission,pExtern);
	}else{
		str.Format("UPDATE %s SET authority=%d WHERE groupsName='%s'",DepartmentTableName,\
			pTempEntry->dwPermission,pTempEntry->sName);
	}
	bRest = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(bRest == FALSE)
	{
		char ErrInfo[MAX_PATH];
		m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		//delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return	FALSE;
	}
	return bRest;
}
BOOL DeleteDepartmentInfoRecord(LPVOID lParam,const char *pExtern)
{
	BOOL bRest = FALSE;
	CString str;
	PDEPARTMENT_INFORMATION  pTempEntry = reinterpret_cast<PDEPARTMENT_INFORMATION>(lParam);
	if (pTempEntry == NULL)	{	return bRest;	}
	if (pExtern != NULL){
		str.Format("DELETE FROM %s WHERE %s",DepartmentTableName,pExtern);
	}else{
		str.Format("DELETE FROM %s WHERE groupsName='%s'",DepartmentTableName,pTempEntry->sName);
	}
	bRest = m_mysql->ExecuteSQLCmd((LPSTR)(LPCSTR)str,FALSE);
	if(bRest == FALSE)
	{
		char ErrInfo[MAX_PATH];
		m_mysql->GetMySQLError(ErrInfo);
		//MessageBox(ErrInfo);
		//delete[] (PRCU_TYPE_ENTRY)m_pEntryInfo;
		return	FALSE;
	}
	return bRest;
}
void ReleaseDepartmentInfoRecord(CPtrArray &pRecordArray)
{
	PDEPARTMENT_INFORMATION  pTempEntry = NULL;
	INT_PTR Index = 0;
	for (Index=0;Index<pRecordArray.GetCount();Index++)
	{
		pTempEntry = (PDEPARTMENT_INFORMATION)pRecordArray.GetAt(Index);
		if (pTempEntry != NULL)	{	delete pTempEntry;	}
	}

	if (Index)	{	pRecordArray.RemoveAll();	}
}
