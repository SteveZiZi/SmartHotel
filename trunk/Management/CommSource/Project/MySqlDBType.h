//该文件用来定义和数据库相关的表的定义和操作
#ifndef MYSQL_DB_TYPE	//宏定义避免重复定义
#define MYSQL_DB_TYPE
//===============================================================================
#define		ENTRY_NAME_BUF_SIZE			64

#define		BM_ADD_DB_ENTRY				WM_USER+200				//增加消息
#define		BM_MODIFY_DB_ENTRY			BM_ADD_DB_ENTRY+1		//修改消息
#define		BM_DELETE_DB_ENTRY			BM_MODIFY_DB_ENTRY+1	//删除消息

#define		EQUMENT_DATA_SIZE			4
#define		STATUS_DATA_SIZE			4
//列表框的一个对象
typedef	struct _ITEM_ENTRTY
{
	UINT	Item;
	UINT	SubItem;
	bool	Flag;
}ITEM_ENTRTY,*PITEM_ENTRTY;




//A：房态的类型结构定义
//例：基本房态、临时房态、服务房态……
#include "RoomStatusType.h"		

//B：设备的类型结构定义
//例：空调、调光、开关
#include "DeviceType.h"			





//C：RCU的类型结构定义
//例：RCU1、RCU2
#include "RCUType.h"	



//D：房类的类型结构定义
//例：大床房、小床房
#include "RoomType.h"	



//E:客房设置
#include "RoomDetailType.h"

//F:用户表
#include "UserType.h"

//G:工程部
#include "Department.h"



//H:登陆记录
#include "UserloginInfo.h"





#endif