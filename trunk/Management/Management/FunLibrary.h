/*******************************************************************************
$$$  This HeadFile is use for declare Dll Library Type for use 
@@@  FunLibrary.h
###  Detail:
*******************************************************************************/
typedef struct _ROMM_INFO_TRANSFER
{
	PVOID	pRoomEntry;					//客房的信息
	ULONG	RCU;						//RCU的类型
	//设备Buffer
	PUCHAR	peBuf;
	ULONG	eLength;
	//房态Buffer
	PUCHAR	psBuf;
	ULONG	sLength;
	//
	ULONG	pTotalLength;
	PVOID	ParentDlg;					//值为This
}ROMM_INFO_TRANSFER,*PROMM_INFO_TRANSFER;





//Part 1: Room Detail Module DLL
#define RoomModuleName  (TEXT("RoomDetailModule.dll"))
//==================================================================
typedef int (*AFX_CALLDETAILMODULE)(LPVOID lParam,LPVOID wParam,int Index);    //定义呼出