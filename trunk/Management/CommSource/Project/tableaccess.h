#ifndef TABLE_ACCESS_H
#define  TABLE_ACCESS_H
////////////////////////////////////////////////////////////////////////////////////////////////
//第一部分：房态表
//==========================================================================
unsigned __int64 GetRoomStatusRecord(int TypeFlag,PROOMSTATUS_ENTRY *pRoomStatus,const char *pExtern = NULL);

////////////////////////////////////////////////////////////////////////////////////////////////
//第二部分：设备表
//==========================================================================
unsigned __int64 GetEquipmentRecord(int TypeFlag,PEQUIPMENT_ENTRY *pEquipment,const char *pExtern = NULL);

////////////////////////////////////////////////////////////////////////////////////////////////
//第三部分：RCU表
//==========================================================================
unsigned __int64 GetRCUTypeRecord(PRCU_TYPE_ENTRY *pRCUType,const char *pExtern);
//设备配置方案表
unsigned __int64 GetDeviceCfgMethodRecord(CPtrArray &pRecordArray,const char *pExtern);
BOOL InsertDeviceCfgMethodRecord(PDEVICE_CFG_METHOD pTempEntry);
BOOL ModifyDeviceCfgMethodRecord(PDEVICE_CFG_METHOD pTempEntry,const char *pExtern);
BOOL DeleteDeviceCfgMethodRecord(PDEVICE_CFG_METHOD pTempEntry,const char *pExtern);
void ReleaseDeviceCfgMethodRecord(CPtrArray &pRecordArray);

//用户表
unsigned __int64 GetUserInfoRecord(CPtrArray &pRecordArray,const char *pExtern);
BOOL InsertUserInfoRecord(PUSER_INFORMATION lParam);
BOOL ModifyUserInfoRecord(PUSER_INFORMATION lParam,const char *pExtern);
BOOL DeleteUserInfoRecord(PUSER_INFORMATION lParam,const char *pExtern);
void ReleaseUserInfoRecord(CPtrArray &pRecordArray);

//添加记录表
unsigned __int64 GetLoginInfoRecord(CPtrArray &pRecordArray,const char *pExtern);
BOOL InsertLoginInfoRecord(LPVOID lParam);
BOOL ModifyLoginInfoRecord(LPVOID lParam,const char *pExtern);
BOOL DeleteLoginInfoRecord(LPVOID lParam,const char *pExtern);
void ReleaseLoginInfoRecord(CPtrArray &pRecordArray);


//增加工程部表
unsigned __int64 GetDepartmentInfoRecord(CPtrArray &pRecordArray,const char *pExtern);
BOOL InsertDepartmentInfoRecord(LPVOID pTempEntry);
BOOL ModifyDepartmentInfoRecord(LPVOID pTempEntry,const char *pExtern);
BOOL DeleteDepartmentInfoRecord(LPVOID pTempEntry,const char *pExtern);
void ReleaseDepartmentInfoRecord(CPtrArray &pRecordArray);


//第四部分：房类表
unsigned __int64 GetRoomTypeRecord(PROOM_TYPE_ENTRY *pRoomType,const char *pExtern);

//第五部分：楼号表
unsigned __int64	GetBuildingRecord(PBUILDING_ENTRY *pBuilding,const char *pExtern);

//第六部分：客房配置表
unsigned __int64	GetRoomRecord(PROOM_DETAIL_ENTRY *pRoom,const char *pExtern);



//**************************************************************************************
//======================================================================================
//得到客房的详细信息Buffer长度
int GetBufferLengthFromRoom(PVOID lParam,ULONG &InLenA,ULONG &InLenB);






#endif