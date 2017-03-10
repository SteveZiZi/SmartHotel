// SubButtonModuleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TechnicianModule.h"
#include "SubButtonModuleDlg.h"
#include "UnitKeyConfigDlg.h"


#define		MAX_SUB_BUTTON_MODULE_NUM		4
const char		*pSubButtonModuleName[32] = {"20路按键","12路按键","8路按键",""};
const USHORT	pSubButtonModuleParam[] = {0x1400,0x0C00,0x0800,0x0000};


// CSubButtonModuleDlg 对话框

IMPLEMENT_DYNAMIC(CSubButtonModuleDlg, CDialog)

CSubButtonModuleDlg::CSubButtonModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubButtonModuleDlg::IDD, pParent)
{
	pModule = NULL;
}

CSubButtonModuleDlg::~CSubButtonModuleDlg()
{
}

void CSubButtonModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RELEASION_LIST, m_ReleasionList);
}


BEGIN_MESSAGE_MAP(CSubButtonModuleDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_VIEW_CONFIG,&CSubButtonModuleDlg::OnViewConfigInfo)
	ON_COMMAND(ID_SET_CONFIG,&CSubButtonModuleDlg::OnSetConfigInfo)

	ON_MESSAGE(WM_ENABLE_CTRL_ITEM,&CSubButtonModuleDlg::Msg_EnableCtrlItem)
	ON_MESSAGE(WM_GET_SUB_MODULE_NAME,&CSubButtonModuleDlg::Msg_GetSubModuleName)
	ON_BN_CLICKED(IDC_ITEM_ENTRY1, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY2, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY3, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY4, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY5, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY6, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY7, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY8, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY9, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY10, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY11, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY12, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY13, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY14, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY15, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY16, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY17, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY18, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY19, &CSubButtonModuleDlg::OnBnClickedItemEntry)
	ON_BN_CLICKED(IDC_ITEM_ENTRY20, &CSubButtonModuleDlg::OnBnClickedItemEntry)
END_MESSAGE_MAP()


// CSubButtonModuleDlg 消息处理程序

BOOL CSubButtonModuleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	InitAllDlgItemCtrl();

	InitPopMenu();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
BOOL CSubButtonModuleDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		//屏掉回车和退出键
		if(pMsg->wParam == VK_RETURN  || pMsg->wParam == VK_ESCAPE)
			return TRUE;

		if(pMsg->wParam == VK_UP  || pMsg->wParam == VK_DOWN)
			return TRUE;

		if(pMsg->wParam == VK_LEFT  || pMsg->wParam == VK_RIGHT)
			return TRUE;

	}	
//=============================================================================================================

	return CDialog::PreTranslateMessage(pMsg);
}

void CSubButtonModuleDlg::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PreSubclassWindow();
}

void CSubButtonModuleDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
	if (bShow == TRUE)	{
		SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)pModule,nSubNameEntry);
		//InitAllDlgItemCtrl();
	}


}
LRESULT CSubButtonModuleDlg::Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam)
{
	PMODULE_ENTRY pModuleEntry = (PMODULE_ENTRY)wParam;
	int iModuleEntry = (int)lParam;
	BYTE nInput = (pSubButtonModuleParam[iModuleEntry] >> 8) & 0x00FF;
	BYTE nOutPut = pSubButtonModuleParam[iModuleEntry]  & 0x00FF;
	UINT nBaseItemID = IDC_ITEM_ENTRY1;
	for (int Index = 0;Index < 20;Index++)
	{
		UINT bFlag = SW_HIDE;
		if (Index	<	nInput)	{	bFlag = SW_SHOWNORMAL;	}
		((CButton *)GetDlgItem(nBaseItemID+Index))->ShowWindow(bFlag);
	}
	((CButton *)GetDlgItem(IDC_ITEM_ENTRY21))->ShowWindow(SW_HIDE);
//===============================================================================================
	CRect rt;
	GetClientRect(rt);
	rt.top = 10 + 40*(nInput/4);
	m_ReleasionList.MoveWindow(rt,TRUE);


	if (m_ReleasionList.GetItemCount())		{	m_ReleasionList.DeleteAllItems();	}
	return S_OK;
}
LRESULT CSubButtonModuleDlg::Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam)
{
	int nEntry = (int)lParam;
	PCHAR *pSubName = (PCHAR *)wParam;

	(*pSubName) =  NULL;
	if (nEntry < MAX_SUB_BUTTON_MODULE_NUM)	{	(*pSubName) = (PCHAR)pSubButtonModuleName[nEntry];	}
	if (strcmp((*pSubName),"") == 0)	{	(*pSubName) =  NULL;	}

	return S_OK;
}
void  CSubButtonModuleDlg::InitAllDlgItemCtrl()
{
	int Index = 0;
	DWORD dwStyle = m_ReleasionList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	//m_ModuleList.ModifyStyle(0,dwStyle);
	m_ReleasionList.SetExtendedStyle(dwStyle);
	//CRect rt;
	//::GetClientRect(GetDlgItem(IDC_RELEASION_LIST)->GetSafeHwnd(),&rt);
	//m_ReleasionList.InsertColumn(Index++,"序号",LVCFMT_CENTER,45);
	m_ReleasionList.InsertColumn(Index++,"模块序号",LVCFMT_CENTER,80);
	m_ReleasionList.InsertColumn(Index++,"子路",LVCFMT_LEFT,120);
	m_ReleasionList.InsertColumn(Index++,"特殊功能",LVCFMT_LEFT,160);


}


void  CSubButtonModuleDlg::FillModuleKeyReleasion(int nOffset)
{
	CString str;
	if (pModule == NULL)	{	return;	}
	PMODULE_KEY_UNIT		pModuleKeyUnit = &(pModule->mKeyUnit[nOffset]);
	PCONTROL_DEVICE_UNIT	pCtrlDeviceUnit = pModuleKeyUnit->mContent.mCtrlDeviceList.mCtrlDev;
//==================================================================================
	m_ReleasionList.DeleteAllItems();
	int Index=0,Entry=0;
	PCHAR pContext = NULL;
	if (pModuleKeyUnit->mContent.mCtrlDeviceList.bNumber){
		while (Index++<MAX_CTRL_MODULE_NUMBER)
		{
			if (Entry >= pModuleKeyUnit->mContent.mCtrlDeviceList.bNumber)	{	break;	}
			if (pCtrlDeviceUnit->bModuleEntry){
				str.Format("模块[%d]",pCtrlDeviceUnit->bModuleEntry);
			    m_ReleasionList.InsertItem(Entry,str);
				//*******************************************************************************
				//str.Format("[%d](%d)",pCtrlDeviceUnit->bModuleEntry,pCtrlDeviceUnit->bSubModuleItem);	
				//m_ReleasionList.SetItemText(Entry,1,str);
				pContext = m_DataManage.GetModuleKeyEntry(pCtrlDeviceUnit->bModuleEntry-1,pCtrlDeviceUnit->bSubModuleItem-1);
				m_ReleasionList.SetItemText(Entry,1,pContext);


				m_ReleasionList.SetItemText(Entry,2,m_DataManage.GetSpecialFunName(pCtrlDeviceUnit->bSpecialFundef));
			}
			pCtrlDeviceUnit++;
		}
	}
}


void CSubButtonModuleDlg::SetCfgModuleKey(UINT nOffset)
{
	CUnitKeyConfigDlg *pUnitKeyDlg = new CUnitKeyConfigDlg;
	if (pUnitKeyDlg == NULL)	{	MessageBox("调出配置模块失败");		return;		}
//=============================================================================================================
	pUnitKeyDlg->SetKeyMemory(&(pModule->mKeyUnit[nOffset]));
	if (pUnitKeyDlg->DoModal() == IDOK){
		pModule->mKeyUnit[nOffset].bEntry = nOffset+1;
		pModule->mKeyUnit[nOffset].bKeyAttribute = ATTRIBUTE_INPUT;
	}
//============================================================================================================
	delete pUnitKeyDlg;
	pUnitKeyDlg = NULL;

	FillModuleKeyReleasion(nOffset);
}


void CSubButtonModuleDlg::OnBnClickedItemEntry()
{
// TODO: Add your control notification handler code here
	CPoint pt;
	GetCursorPos(&pt);
	mRmenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,pt.x,pt.y,this);

}

void CSubButtonModuleDlg::InitPopMenu()
{
//	int Index,i;
//	CString str;
//	UINT mID,sID;
//	CMenu pSubMenu;
//	CMenu pSubEntryMenu[16];
//先删除菜单
	//while(mRmenu.GetMenuItemCount()){	mRmenu.DeleteMenu(0,MF_BYPOSITION);	}
//	//=================================================================
//	//存在数据的话允许有全清选项
//	if(m_SensorList.GetItemCount()){
//		mRmenu.AppendMenu(MF_STRING,ID_POP_MENU_BASE,"清空全部");	
//	}	
//	//=============================================================
	mRmenu.CreatePopupMenu();
	mRmenu.AppendMenu(MF_STRING,ID_VIEW_CONFIG,"查看配置");
	mRmenu.AppendMenu(MF_STRING,ID_SET_CONFIG,"配置按键");
//	pSubMenu.CreatePopupMenu();
//	mRmenu.AppendMenu(MF_POPUP,(UINT)pSubMenu.m_hMenu,"增加");	//插入菜单
//	mID = ID_POP_MENU_BASE + 0x010000;
//
//	for(Index=0;Index<pSensorNameList.GetCount();Index++)		//增加所有的传感器类型
//	{
//		POSITION pt = pSensorNameList.FindIndex(Index);
//		PUNIT_SENSOE_INFO pSensor = (PUNIT_SENSOE_INFO)pSensorNameList.GetAt(pt);
//		sID = mID | (((pSensor->SensorType)&0xFF)<<8);
//		pSubEntryMenu[Index].CreatePopupMenu();
//		for(i=0;i<32;i++)
//		{
//			str.Format("%d",i+1);
//			pSubEntryMenu[Index].AppendMenu(MF_STRING,sID+i+1,str);	
//		}	
//		pSubMenu.AppendMenu(MF_POPUP,(UINT)pSubEntryMenu[Index].m_hMenu,pSensor->SensorName);
//
//
//
//
//
//
//
//
//
//
//
//
//
//#if 0
//		sID = mID + ((Index+1)<<8);
//		pSubEntryMenu[Index].CreatePopupMenu();
//		for(i=0;i<32;i++)
//		{
//			str.Format("%d",i+1);
//			pSubEntryMenu[Index].AppendMenu(MF_STRING,sID+i,str);	
//		}
//
//		POSITION pt = pSensorNameList.FindIndex(Index);
//		PUNIT_SENSOE_INFO pSensor = (PUNIT_SENSOE_INFO)pSensorNameList.GetAt(pt);
//		pSubMenu.AppendMenu(MF_POPUP,(UINT)pSubEntryMenu[Index].m_hMenu,pSensor->SensorName);
//		//pSubMenu.AppendMenu(MF_STRING,sID,pSensor->SensorName);	
//		//pSubEntryMenu.Detach();
//		//while(pSubEntryMenu.GetMenuItemCount()){
//		//	pSubEntryMenu.DeleteMenu(0,MF_BYPOSITION);
//		//}
//#endif
//	}
//	pSubMenu.Detach();
//
//	//=============================================================
//	if(nIndex != -1)
//		mRmenu.AppendMenu(MF_STRING,ID_POP_MENU_BASE + 0x020000,"删除");	
}


void CSubButtonModuleDlg::OnViewConfigInfo()
{
	UINT nID = GetFocus()->GetDlgCtrlID();
	if ((nID < IDC_ITEM_ENTRY1) || (nID > IDC_ITEM_ENTRY20)){	return	;	}
	
	FillModuleKeyReleasion(nID-IDC_ITEM_ENTRY1);
}

void CSubButtonModuleDlg::OnSetConfigInfo()
{
	UINT nID = GetFocus()->GetDlgCtrlID();
	if ((nID < IDC_ITEM_ENTRY1) || (nID > IDC_ITEM_ENTRY20)){	return	;	}


	SetCfgModuleKey(nID-IDC_ITEM_ENTRY1);
}


