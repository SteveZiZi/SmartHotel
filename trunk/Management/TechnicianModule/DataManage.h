#pragma once

class CDataManage
{
public:
	CDataManage(void);
	~CDataManage(void);
public:
	PROOM		pRoomUnit;					//客房详细的配置结构
	CPtrArray	pSepeciallLinkList;			//特殊功能链表
	CPtrArray	pModuleLinkList;			//模块类型链表

public:
	int		LoadSpecialLinkList(BOOL Flag = TRUE);
	void	SetRoomContainer(LPVOID lParam);
	PMODULE_ENTRY SearchModuleExit(DWORD dwAddress);			//查找模块是否存在
	//=============================================================================
	PCHAR GetModuleKeyEntry(int nModule,int nSubKey);
	PCHAR GetSpecialFunName(int nValue);

	PCHAR GetSubModuleName(int nModule);
	PMODULE_ENTRY InsertModule(int nItem,int nSubItem,int nDeviceType,DWORD dwAddress);
	void DeleteModule(int Entry);
	//==================================================================================
	DWORD GetAppointedModuleCfgData(PBYTE &pBuf,int iEntry);				//获取配置模块的内容
	DWORD GetTotalModuleCfgData(LPVOID lParam,PBYTE &pBuf);								//获取所有模块的内容
	
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




