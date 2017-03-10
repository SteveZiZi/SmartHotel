#ifndef TABLE_ACCESS_H
#define  TABLE_ACCESS_H
////////////////////////////////////////////////////////////////////////////////////////////////
//��һ���֣���̬��
//==========================================================================
unsigned __int64 GetRoomStatusRecord(int TypeFlag,PROOMSTATUS_ENTRY *pRoomStatus,const char *pExtern = NULL);

////////////////////////////////////////////////////////////////////////////////////////////////
//�ڶ����֣��豸��
//==========================================================================
unsigned __int64 GetEquipmentRecord(int TypeFlag,PEQUIPMENT_ENTRY *pEquipment,const char *pExtern = NULL);

////////////////////////////////////////////////////////////////////////////////////////////////
//�������֣�RCU��
//==========================================================================
unsigned __int64 GetRCUTypeRecord(PRCU_TYPE_ENTRY *pRCUType,const char *pExtern);
//�豸���÷�����
unsigned __int64 GetDeviceCfgMethodRecord(CPtrArray &pRecordArray,const char *pExtern);
BOOL InsertDeviceCfgMethodRecord(PDEVICE_CFG_METHOD pTempEntry);
BOOL ModifyDeviceCfgMethodRecord(PDEVICE_CFG_METHOD pTempEntry,const char *pExtern);
BOOL DeleteDeviceCfgMethodRecord(PDEVICE_CFG_METHOD pTempEntry,const char *pExtern);
void ReleaseDeviceCfgMethodRecord(CPtrArray &pRecordArray);

//�û���
unsigned __int64 GetUserInfoRecord(CPtrArray &pRecordArray,const char *pExtern);
BOOL InsertUserInfoRecord(PUSER_INFORMATION lParam);
BOOL ModifyUserInfoRecord(PUSER_INFORMATION lParam,const char *pExtern);
BOOL DeleteUserInfoRecord(PUSER_INFORMATION lParam,const char *pExtern);
void ReleaseUserInfoRecord(CPtrArray &pRecordArray);

//��Ӽ�¼��
unsigned __int64 GetLoginInfoRecord(CPtrArray &pRecordArray,const char *pExtern);
BOOL InsertLoginInfoRecord(LPVOID lParam);
BOOL ModifyLoginInfoRecord(LPVOID lParam,const char *pExtern);
BOOL DeleteLoginInfoRecord(LPVOID lParam,const char *pExtern);
void ReleaseLoginInfoRecord(CPtrArray &pRecordArray);


//���ӹ��̲���
unsigned __int64 GetDepartmentInfoRecord(CPtrArray &pRecordArray,const char *pExtern);
BOOL InsertDepartmentInfoRecord(LPVOID pTempEntry);
BOOL ModifyDepartmentInfoRecord(LPVOID pTempEntry,const char *pExtern);
BOOL DeleteDepartmentInfoRecord(LPVOID pTempEntry,const char *pExtern);
void ReleaseDepartmentInfoRecord(CPtrArray &pRecordArray);


//���Ĳ��֣������
unsigned __int64 GetRoomTypeRecord(PROOM_TYPE_ENTRY *pRoomType,const char *pExtern);

//���岿�֣�¥�ű�
unsigned __int64	GetBuildingRecord(PBUILDING_ENTRY *pBuilding,const char *pExtern);

//�������֣��ͷ����ñ�
unsigned __int64	GetRoomRecord(PROOM_DETAIL_ENTRY *pRoom,const char *pExtern);



//**************************************************************************************
//======================================================================================
//�õ��ͷ�����ϸ��ϢBuffer����
int GetBufferLengthFromRoom(PVOID lParam,ULONG &InLenA,ULONG &InLenB);






#endif