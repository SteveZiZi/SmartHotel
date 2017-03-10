//���ļ���������ȫ��Ȩ�޽ṹ
#ifndef GOLAB_PERMISSION_H	//�궨������ظ�����
#define GOLAB_PERMISSION_H
//===============================================================================
#pragma pack(push,1)
//==========================================================================================
typedef struct _USER_PERMISSION    //�û�Ȩ�޽ṹ
{
////////////////////////////////////////////////////////
//BYTE[0] ��Ȩ���ֽ�
	union
	{
		BYTE Value;
		struct _MAIN_PERMISSION
		{
		BYTE bActiveRSEn:1;          //ʵʱ��̬Ȩ��[0]
		BYTE bControlPanelEn:1 ;     //�������Ȩ��[1]
		BYTE bCensusEn:1 ;           //ͳ�Ʋ�ѯȨ��[2]
		BYTE bLogViewEn:1 ;          //ͳ�Ʋ�ѯȨ��[3]
		BYTE bReservedEn:1 ;         //ʵʱ��̬Ȩ��[4]
		BYTE bExitEn:1 ;             //ʵʱ��̬Ȩ��[5]
		BYTE bReserved0:2 ;          //����Ȩ��[6-7]
		}bValue;
	}PermissionMain;
////////////////////////////////////////////////////////    
	//���������е�
	BYTE bSystemSet:1 ;       //ϵͳ����Ȩ��[8]
	BYTE bUser:1 ;            //�û��ʻ�Ȩ��[9]
	BYTE bNoticeSet:1 ;       //��������Ȩ��[10]
	BYTE bKeyDefine:1 ;       //���ƶ���Ȩ��[11] 
	BYTE bDailyUphold:1 ;      //�ճ�ά��Ȩ��[12]
	//��������
	BYTE bRoomStyleSet:1 ;    //��������Ȩ��[13]
	BYTE bRoomSet:1 ;         //�ͷ�����Ȩ��[14]
	BYTE bRoomMode:1 ;        //�ͷ�ģʽȨ��[15]
	BYTE bAutoMessage:1 ;     //�Զ��¼�Ȩ��[16]
	BYTE bPictureChange:1 ;   //ͼƬ���Ȩ��[17]
    //��������
	BYTE bRoomStateSet:1 ;    //��̬����Ȩ��[18]
	BYTE bDeviceConfig:1 ;    //�豸����Ȩ��[19]
	BYTE bRCUType:1 ;         //RCU����Ȩ��[20]
	BYTE bCommunicationSet:1 ;     //ͨѶ����Ȩ��[21]
	BYTE bWarningDefine:1 ;    //�澯����Ȩ��[22]
	BYTE bReserved1:1 ;       //����Ȩ��[23]
////////////////////////////////////////////////////////////
	BYTE bRoomAdjust:1 ;      //��̬����Ȩ��[24]
	BYTE bDeviceAdjust:1 ;    //�豸����Ȩ��[25]
	BYTE bDeviceTimer:1 ;         //�豸��ʱȨ��[26]
	BYTE bLCDNotice:1 ;     //LCD����Ȩ��[27]
	BYTE bSetTemperature:1 ;    //Ԥ���¶�Ȩ��[28]
	BYTE bPermissionSet:1 ;    //Ԥ���¶�Ȩ��[29]
	BYTE bReserved2:1 ;    //����Ȩ��[30]

	
	BYTE bOperationFunction:1 ;    //����Ա����[31]
}USER_PERMISSION,*PUSER_PERMISSION;
#pragma pack(pop)






















typedef struct _GOLAB_PERMISSION
{
//��һ���֣���������湦��
	union	{
		DWORD	dwMainValue;
		struct MAIN_DETAIl
		{
			DWORD Reserved:31;
			DWORD bEnOperateCfg:1;		//�Ƿ�������Ա����
		}MainDetail;
	}MainPermission;	//������Ȩ��
//縶����֣�
	DWORD Resv;
}GOLAB_PERMISSION,*PGOLAB_PERMISSION;















#endif