//���ļ�������������ݿ���صı�Ķ���Ͳ���
#ifndef MYSQL_DB_TYPE	//�궨������ظ�����
#define MYSQL_DB_TYPE
//===============================================================================
#define		ENTRY_NAME_BUF_SIZE			64

#define		BM_ADD_DB_ENTRY				WM_USER+200				//������Ϣ
#define		BM_MODIFY_DB_ENTRY			BM_ADD_DB_ENTRY+1		//�޸���Ϣ
#define		BM_DELETE_DB_ENTRY			BM_MODIFY_DB_ENTRY+1	//ɾ����Ϣ

#define		EQUMENT_DATA_SIZE			4
#define		STATUS_DATA_SIZE			4
//�б���һ������
typedef	struct _ITEM_ENTRTY
{
	UINT	Item;
	UINT	SubItem;
	bool	Flag;
}ITEM_ENTRTY,*PITEM_ENTRTY;




//A����̬�����ͽṹ����
//����������̬����ʱ��̬������̬����
#include "RoomStatusType.h"		

//B���豸�����ͽṹ����
//�����յ������⡢����
#include "DeviceType.h"			





//C��RCU�����ͽṹ����
//����RCU1��RCU2
#include "RCUType.h"	



//D����������ͽṹ����
//�����󴲷���С����
#include "RoomType.h"	



//E:�ͷ�����
#include "RoomDetailType.h"

//F:�û���
#include "UserType.h"

//G:���̲�
#include "Department.h"



//H:��½��¼
#include "UserloginInfo.h"





#endif