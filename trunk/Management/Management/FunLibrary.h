/*******************************************************************************
$$$  This HeadFile is use for declare Dll Library Type for use 
@@@  FunLibrary.h
###  Detail:
*******************************************************************************/
typedef struct _ROMM_INFO_TRANSFER
{
	PVOID	pRoomEntry;					//�ͷ�����Ϣ
	ULONG	RCU;						//RCU������
	//�豸Buffer
	PUCHAR	peBuf;
	ULONG	eLength;
	//��̬Buffer
	PUCHAR	psBuf;
	ULONG	sLength;
	//
	ULONG	pTotalLength;
	PVOID	ParentDlg;					//ֵΪThis
}ROMM_INFO_TRANSFER,*PROMM_INFO_TRANSFER;





//Part 1: Room Detail Module DLL
#define RoomModuleName  (TEXT("RoomDetailModule.dll"))
//==================================================================
typedef int (*AFX_CALLDETAILMODULE)(LPVOID lParam,LPVOID wParam,int Index);    //�������