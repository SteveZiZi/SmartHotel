//��ҳ�������ݿ����ر�ͽṹ
/*Part1: ���ݿ�����ýṹ*/
typedef struct _MYSQL_CONFIG    //���ݿ����ýṹ
{
  char HostName[255];   //������
  char UserName[255];   //�û���
  char PassWord[255];   //����
  int Port;

  char DBName[255];   //���ݿ���
}MYSQL_CONFIG,*PMYSQL_CONFIG;

/*Part2: ��Ϣ�Ķ���*/
#define WM_EX_ADD       WM_USER+10				//����
#define WM_EX_MODIFY    WM_EX_ADD+1				//�޸�
#define WM_EX_DELETE    WM_EX_MODIFY+1			//ɾ��

#define WM_EX_LOAD		WM_USER+20				//����
#define WM_EX_UPDATE    WM_EX_LOAD+1			//����
//******************************************************************************************************
//                       �������õĸ���ͽṹ
//******************************************************************************************************







//******************************************************************************************************
//                       �������õĸ���ͽṹ
//******************************************************************************************************
//==========================================================================
//�������ñ���ص���Ϣ
//#define roomTypeSettingTableName   (TEXT("RoomTypeSet"))
//const char roomTypeSettingTableName[] = {("RoomTypeSet")};     //�����������ñ�
/*const char RTSTColumn[][32] = {"roomtypeID","roomtypeName","RCUID"};
typedef struct _ROOM_TYPE    //����ṹ
{
  unsigned long Index;       //����
  char RoomTypeName[255];    //������
  unsigned long RCUType;     //RCU���ͱ��
}ROOMTYPE,*PROOMTYPE;*/
//============================================================================
//¥�����ñ���ص��Ŵ�
/*#define BuildingSetTableName   (TEXT("BuildingSet"))
const char BuildingColumn[][32] = {"buildingID","buildingName","ShowStyleIndex"};
typedef struct _BUILDINGSET_TYPE    //����ṹ
{
  unsigned long m_dBuilding;       //¥�����
  char m_BuildingName[255];        //¥����
  DWORD m_ShowStyle;
}BUILDINGSET,*PBUILDINGSET;
//==========================================================================
//�������ñ�
//#define roomSetTableName   (TEXT("RoomSet"))
const char RSColumn[][32] = {"roomID","doorNum","floorNum","buildingID","roomtypeID","IPaddress","portValue"};
typedef struct _ROOM_SET    //����ṹ
{
  unsigned long Index;       //����
  int RoomNum;
  int FloorNum;
  int Building;
  int RoomType;    //������
  char IpAddress[32];
  int PortValues;
}ROOMSET,*PROOMSET;
*/
//******************************************************************************************************
//                       �������õĸ���ͽṹ
//******************************************************************************************************
//===================================================================================================
//��̬���ñ�
/*#define roomStateBaseTableName   (TEXT("RoomState_Base"))
#define roomStateTempTableName   (TEXT("RoomState_Temp"))
#define roomStateServiceTableName   (TEXT("RoomState_Service"))
#define roomStateOtherTableName   (TEXT("RoomState_Other"))
//const char roomStateBaseTableName[] ={("RoomState_Base")};          //������̬��
const char RSTBColumn[][32] = {"B_ID","baseType","ctrlDirection","picture"};
const char RSTTColumn[][32] = {"T_ID","tempType","ctrlDirection","picture"};
const char RSSTColumn[][32] = {"S_ID","ServiceType","ctrlDirection","picture"};
const char RSOTColumn[][32] = {"O_ID","OtherType","ctrlDirection","picture"};
typedef struct _ROOM_STATE    //������̬�ṹ
{
  unsigned long Index;        //����
  char RoomStateName[255];    //������̬��
  int DubleDirection;         //�Ƿ�˫��
  char ViewPath[255];         //ͼƬ��
}ROOMSTATE,*PROOMSTATE;
//�豸���ñ�
#define EquipmentAirTableName   (TEXT("Equipment_Air"))
#define EquipmentLightTableName   (TEXT("Equipment_Light"))
#define EquipmentSwitchTableName   (TEXT("Equipment_Switch"))
#define EquipmentPowerSaveSwitchTableName   (TEXT("Equipment_PowerSaveSwitch"))
//
const char EPAColumn[][32] = {"airID","airconditName","isTiming","ctrlDirection","windSpd","temperature"};
const char EPLColumn[][32] = {"lightID","lightName","isTiming","ctrlDirection","brightness",""};
const char EPSColumn[][32] = {"switchID","switchName","isTiming","ctrlDirection","stutes",""};
//const char RSOTColumn[][32] = {"O_ID","OtherType","ctrlDirection","picture"};
typedef struct _DEVICE_CONFIG    //���ýṹ
{
  unsigned long Index;           //����
  char DeviceConfigName[255];    //�豸��
  int Timing;                    //�Ƿ�ʱ
  int DubleDirection;            //�Ƿ�˫��
  int Argument;                  //������̬��
  int Reserved;
}DEVICECONFIG,*PDEVICECONFIG;
*/
//RCU���ͱ�
/*#define RCUTypeTableName   (TEXT("RCUInfo"))
//const char  RCUTypeTableName[] ={("RCUInfo")};                    //RCU���ͱ�
const char RCUColumn[][32] = {"RCUID","RCUName","equipPortNum","statePortNum"};
typedef struct _RCU_TYPE    //������̬�ṹ
{
  unsigned long RCUId;            //����
  char RCUName[255];              //
  unsigned long wEquipPortNum;        //
  unsigned long wStatePortNum;    //
}RCUTYPE,*PRCUTYPE;
#define  RCUDevicePortConfigName   (TEXT("RCUDevicePortCFG"))           //�豸�˿����ñ�
#define  RCURoomStatePortConfigName  (TEXT("RCURoomStatePortCFG"))     //��̬�˿����ñ�
*/










/*
const char roomStateTempName[] = _T("RoomState_Temp");          //��ʱ��̬��
const char roomStateServiceName[] = _T("RoomState_Service");    //����̬��
const char roomStateOtherName[] = _T("RoomState_Other");        //������̬��
//====================================================================================================

//��̬���ñ�
//const char roomStateTempName[] = _T("RoomState_Temp");          //��ʱ��̬��
//const char roomStateServiceName[] = _T("RoomState_Service");    //����̬��
//const char roomStateOtherName[] = _T("RoomState_Other");        //������̬��
//�豸���ñ�
const char equipmentAirName[] = _T("Equipment_Air");                    //�յ��豸��
const char equipmentLightName[] = _T("Equipment_Light");                //�����豸��
const char equipmentPowerSaveName[] = _T("RoomState_PowerSave");        //�ڵ翪�ر�
const char equipmentSwitchName[] = _T("Equipment_Switch");              //���ص�����
//RCU����
const char RCUInfoName[] = _T("RCUInfo");                                //RCU���ͱ�
//const char RCUDevicePortConfigName[] = _T("RCUDevicePortCFG");           //�豸�˿����ñ�
//const char RCURoomStatePortConfigName[] = _T("RCURoomStatePortCFG");     //��̬�˿����ñ�
*/







