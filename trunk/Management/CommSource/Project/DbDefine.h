//该页定义数据库的相关表和结构
/*Part1: 数据库的配置结构*/
typedef struct _MYSQL_CONFIG    //数据库配置结构
{
  char HostName[255];   //主机名
  char UserName[255];   //用户名
  char PassWord[255];   //密码
  int Port;

  char DBName[255];   //数据库名
}MYSQL_CONFIG,*PMYSQL_CONFIG;

/*Part2: 消息的定义*/
#define WM_EX_ADD       WM_USER+10				//增加
#define WM_EX_MODIFY    WM_EX_ADD+1				//修改
#define WM_EX_DELETE    WM_EX_MODIFY+1			//删除

#define WM_EX_LOAD		WM_USER+20				//加载
#define WM_EX_UPDATE    WM_EX_LOAD+1			//更新
//******************************************************************************************************
//                       常规设置的各表和结构
//******************************************************************************************************







//******************************************************************************************************
//                       工程设置的各表和结构
//******************************************************************************************************
//==========================================================================
//房类配置表相关的信息
//#define roomTypeSettingTableName   (TEXT("RoomTypeSet"))
//const char roomTypeSettingTableName[] = {("RoomTypeSet")};     //房间类型配置表
/*const char RTSTColumn[][32] = {"roomtypeID","roomtypeName","RCUID"};
typedef struct _ROOM_TYPE    //房类结构
{
  unsigned long Index;       //索引
  char RoomTypeName[255];    //房类名
  unsigned long RCUType;     //RCU类型编号
}ROOMTYPE,*PROOMTYPE;*/
//============================================================================
//楼座设置表相关的信处
/*#define BuildingSetTableName   (TEXT("BuildingSet"))
const char BuildingColumn[][32] = {"buildingID","buildingName","ShowStyleIndex"};
typedef struct _BUILDINGSET_TYPE    //房类结构
{
  unsigned long m_dBuilding;       //楼座序号
  char m_BuildingName[255];        //楼座名
  DWORD m_ShowStyle;
}BUILDINGSET,*PBUILDINGSET;
//==========================================================================
//房间设置表
//#define roomSetTableName   (TEXT("RoomSet"))
const char RSColumn[][32] = {"roomID","doorNum","floorNum","buildingID","roomtypeID","IPaddress","portValue"};
typedef struct _ROOM_SET    //房间结构
{
  unsigned long Index;       //索引
  int RoomNum;
  int FloorNum;
  int Building;
  int RoomType;    //房类名
  char IpAddress[32];
  int PortValues;
}ROOMSET,*PROOMSET;
*/
//******************************************************************************************************
//                       出厂设置的各表和结构
//******************************************************************************************************
//===================================================================================================
//房态配置表
/*#define roomStateBaseTableName   (TEXT("RoomState_Base"))
#define roomStateTempTableName   (TEXT("RoomState_Temp"))
#define roomStateServiceTableName   (TEXT("RoomState_Service"))
#define roomStateOtherTableName   (TEXT("RoomState_Other"))
//const char roomStateBaseTableName[] ={("RoomState_Base")};          //基本房态表
const char RSTBColumn[][32] = {"B_ID","baseType","ctrlDirection","picture"};
const char RSTTColumn[][32] = {"T_ID","tempType","ctrlDirection","picture"};
const char RSSTColumn[][32] = {"S_ID","ServiceType","ctrlDirection","picture"};
const char RSOTColumn[][32] = {"O_ID","OtherType","ctrlDirection","picture"};
typedef struct _ROOM_STATE    //基本房态结构
{
  unsigned long Index;        //索引
  char RoomStateName[255];    //基本房态名
  int DubleDirection;         //是否双向
  char ViewPath[255];         //图片名
}ROOMSTATE,*PROOMSTATE;
//设备配置表
#define EquipmentAirTableName   (TEXT("Equipment_Air"))
#define EquipmentLightTableName   (TEXT("Equipment_Light"))
#define EquipmentSwitchTableName   (TEXT("Equipment_Switch"))
#define EquipmentPowerSaveSwitchTableName   (TEXT("Equipment_PowerSaveSwitch"))
//
const char EPAColumn[][32] = {"airID","airconditName","isTiming","ctrlDirection","windSpd","temperature"};
const char EPLColumn[][32] = {"lightID","lightName","isTiming","ctrlDirection","brightness",""};
const char EPSColumn[][32] = {"switchID","switchName","isTiming","ctrlDirection","stutes",""};
//const char RSOTColumn[][32] = {"O_ID","OtherType","ctrlDirection","picture"};
typedef struct _DEVICE_CONFIG    //配置结构
{
  unsigned long Index;           //索引
  char DeviceConfigName[255];    //设备名
  int Timing;                    //是否定时
  int DubleDirection;            //是否双向
  int Argument;                  //基本房态名
  int Reserved;
}DEVICECONFIG,*PDEVICECONFIG;
*/
//RCU类型表
/*#define RCUTypeTableName   (TEXT("RCUInfo"))
//const char  RCUTypeTableName[] ={("RCUInfo")};                    //RCU类型表
const char RCUColumn[][32] = {"RCUID","RCUName","equipPortNum","statePortNum"};
typedef struct _RCU_TYPE    //基本房态结构
{
  unsigned long RCUId;            //索引
  char RCUName[255];              //
  unsigned long wEquipPortNum;        //
  unsigned long wStatePortNum;    //
}RCUTYPE,*PRCUTYPE;
#define  RCUDevicePortConfigName   (TEXT("RCUDevicePortCFG"))           //设备端口配置表
#define  RCURoomStatePortConfigName  (TEXT("RCURoomStatePortCFG"))     //房态端口配置表
*/










/*
const char roomStateTempName[] = _T("RoomState_Temp");          //临时房态表
const char roomStateServiceName[] = _T("RoomState_Service");    //服务房态表
const char roomStateOtherName[] = _T("RoomState_Other");        //其它房态表
//====================================================================================================

//房态配置表
//const char roomStateTempName[] = _T("RoomState_Temp");          //临时房态表
//const char roomStateServiceName[] = _T("RoomState_Service");    //服务房态表
//const char roomStateOtherName[] = _T("RoomState_Other");        //其它房态表
//设备配置表
const char equipmentAirName[] = _T("Equipment_Air");                    //空调设备表
const char equipmentLightName[] = _T("Equipment_Light");                //调光设备表
const char equipmentPowerSaveName[] = _T("RoomState_PowerSave");        //节电开关表
const char equipmentSwitchName[] = _T("Equipment_Switch");              //开关电器表
//RCU类型
const char RCUInfoName[] = _T("RCUInfo");                                //RCU类型表
//const char RCUDevicePortConfigName[] = _T("RCUDevicePortCFG");           //设备端口配置表
//const char RCURoomStatePortConfigName[] = _T("RCURoomStatePortCFG");     //房态端口配置表
*/







