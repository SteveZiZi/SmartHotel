#pragma once

class CDataManage
{
public:
	CDataManage(void);
	~CDataManage(void);
public:
	PROOM		pRoomUnit;					//�ͷ���ϸ�����ýṹ
	CPtrArray	pSepeciallLinkList;			//���⹦������
	CPtrArray	pModuleLinkList;			//ģ����������

public:
	int		LoadSpecialLinkList(BOOL Flag = TRUE);
	void	SetRoomContainer(LPVOID lParam);
	PMODULE_ENTRY SearchModuleExit(DWORD dwAddress);			//����ģ���Ƿ����
	//=============================================================================
	PCHAR GetModuleKeyEntry(int nModule,int nSubKey);
	PCHAR GetSpecialFunName(int nValue);

	PCHAR GetSubModuleName(int nModule);
	PMODULE_ENTRY InsertModule(int nItem,int nSubItem,int nDeviceType,DWORD dwAddress);
	void DeleteModule(int Entry);
	//==================================================================================
	DWORD GetAppointedModuleCfgData(PBYTE &pBuf,int iEntry);				//��ȡ����ģ�������
	DWORD GetTotalModuleCfgData(LPVOID lParam,PBYTE &pBuf);								//��ȡ����ģ�������
	
	DWORD GetDataPos(BYTE bValue);
	DWORD GetStageDataContext(LPVOID lParam,PBYTE pBuf);

private:
	enum SCENE
	{
		SCENEONE = 0,
		SCENETWO,
		SCENETHREE,
		SCENEFOUR,
		SCENEFIVE,
		SCENESIX,
		SCENESEVEN,
		SCENECARDIN,
		SCENECARDOUT,
		SCENEINFRAREDON,
		SCENEINFRAREDOFF,
		SCENESUPPLY,
		SCENEDOOR,
	};
};




