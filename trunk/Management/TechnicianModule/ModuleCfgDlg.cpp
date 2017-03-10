// ModuleCfgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TechnicianModule.h"
#include "ModuleCfgDlg.h"


// CModuleCfgDlg dialog

IMPLEMENT_DYNAMIC(CModuleCfgDlg, CDialog)

CModuleCfgDlg::CModuleCfgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModuleCfgDlg::IDD, pParent)
	, m_ModuleAddress(0)
{
	pSelModuleWnd = NULL;


	pSubOutModuleDlg = NULL;
	pSubButtonModuleDlg = NULL;
	pSubAirConditionModuleDlg = NULL;
	pSubIoModuleDlg = NULL;
	//pSubStageModuleDlg = NULL;
	pSubNumberDlg = NULL;
	pSubCardDlg = NULL;


	pSubStageDlg = NULL;
}

CModuleCfgDlg::~CModuleCfgDlg()
{
}

void CModuleCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CON_METHOD, m_ConMethod);
	DDX_Control(pDX, IDC_COMBO_MODULE_NAME, m_ComModuleName);
	DDX_Control(pDX, IDC_COMBO_MODULE_TYPE, m_ComModuleType);
	DDX_Control(pDX, IDC_MODULE_LIST, m_ModuleList);
	DDX_Text(pDX, IDC_MODULE_ADDRESS, m_ModuleAddress);
	DDX_Control(pDX, IDC_COMBO_DEVICE_TYPE, m_DeviceTypeKey);
}


BEGIN_MESSAGE_MAP(CModuleCfgDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_UPDATE_SELECT_CFG,Msg_UpdataSelectRoomCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_MODULE_TYPE, &CModuleCfgDlg::OnCbnSelchangeComboModuleType)
	ON_CBN_SELCHANGE(IDC_COMBO_MODULE_NAME, &CModuleCfgDlg::OnCbnSelchangeComboModuleName)
	ON_BN_CLICKED(IDC_BTN_ADD, &CModuleCfgDlg::OnBnClickedBtnAdd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_MODULE_LIST, &CModuleCfgDlg::OnLvnItemchangedModuleList)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CModuleCfgDlg::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// CModuleCfgDlg message handlers

BOOL CModuleCfgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	InitListCtrl();
	InitDeviceTypeKey();
	InitAllSubModule();

	SetDlgItemInt(IDC_MODULE_ADDRESS,rand());
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CModuleCfgDlg::PreTranslateMessage(MSG* pMsg)
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
	return CDialog::PreTranslateMessage(pMsg);
}

void CModuleCfgDlg::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	if (pSubOutModuleDlg != NULL)	{	delete pSubOutModuleDlg;		pSubOutModuleDlg = NULL;	}
	if (pSubButtonModuleDlg != NULL)	{	delete pSubButtonModuleDlg;		pSubButtonModuleDlg = NULL;	}
	if (pSubAirConditionModuleDlg != NULL)	{	delete pSubAirConditionModuleDlg;		pSubAirConditionModuleDlg = NULL;	}
	if (pSubIoModuleDlg != NULL)	{	delete pSubIoModuleDlg;		pSubIoModuleDlg = NULL;	}
//	if (pSubStageModuleDlg != NULL)	{	delete pSubStageModuleDlg;		pSubStageModuleDlg = NULL;	}
	if (pSubStageDlg != NULL)	{	delete pSubStageDlg;		pSubStageDlg = NULL;	}

	if (pSubCardDlg != NULL)	{	delete pSubCardDlg;		pSubCardDlg = NULL;	}
	if (pSubNumberDlg != NULL)	{	delete pSubNumberDlg;		pSubNumberDlg = NULL;	}





}

void CModuleCfgDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
}



LRESULT CModuleCfgDlg::Msg_UpdataSelectRoomCfg(WPARAM wParam,LPARAM lParam)
{
	if (m_DataManage.pRoomUnit == NULL)	{	return S_FALSE;	}
	int Index = 0;
	PMODULE_ENTRY pModule = reinterpret_cast<PMODULE_ENTRY>(m_DataManage.pRoomUnit->mModuleEntry);
//=================================================================================================
//1、显示房型名
	SetDlgItemText(IDC_EDIT_ROOM_NAME,(LPCSTR)(m_DataManage.pRoomUnit->sRoomName));
//2、显示通信方式
	m_ConMethod.SetCurSel(m_DataManage.pRoomUnit->ulConnectType);
//3、模块列表
	while (Index < MAX_MODULE_NUMBER)
	{
		if (pModule->bEntry){	InsertOneModuleToList(pModule);		}
		pModule++;
		Index++;
	}
	return S_OK;
}


void CModuleCfgDlg::InitListCtrl()
{
	CRect Rt; 
	DWORD dwStyleEx;
	::GetClientRect(m_ModuleList.GetSafeHwnd(),&Rt);
	//改变显示模式为报表
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	dwStyleEx = LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES;  //  
	m_ModuleList.SetExtendedStyle(dwStyleEx);

//	int Index = 0;
//	DWORD dwStyle = m_ModuleList.GetExtendedStyle();
//	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
//	//m_ModuleList.ModifyStyle(0,dwStyle);
//	m_ModuleList.SetExtendedStyle(dwStyle);
////====================================================================================
//	CRect rt;
//	::GetClientRect(GetDlgItem(IDC_MODULE_LIST)->GetSafeHwnd(),&rt);
	m_ModuleList.InsertColumn(0, NULL, LVCFMT_CENTER, 0);//插入列
	m_ModuleList.InsertColumn(1,"设备号",LVCFMT_CENTER,60);
	m_ModuleList.InsertColumn(2,"模块名称",LVCFMT_CENTER,Rt.Width()-140);
	m_ModuleList.InsertColumn(3,"模块地址",LVCFMT_CENTER,80);
	//m_ModuleList.InsertColumn(Index++,"索引",LVCFMT_CENTER,40);
	//m_ModuleList.InsertColumn(Index++,"索引",LVCFMT_CENTER,40);
}



void CModuleCfgDlg::InitAllSubModule()
{
	int Index = 0;
//按键模块
	if (pSubButtonModuleDlg == NULL)	{
		pSubButtonModuleDlg = new CSubButtonModuleDlg;
		if (pSubButtonModuleDlg != NULL)	{
			pSubButtonModuleDlg->Create(IDD_SUB_BUTTON_MODULE_DIALOG,GetDlgItem(IDC_STATIC_CUSTOMER));
			pSubButtonModuleDlg->ShowWindow(SW_HIDE);
			m_ComModuleType.InsertString(Index,pSubButtonModuleDlg->GetModuleName());
			m_ComModuleType.SetItemData(Index++,(DWORD_PTR)pSubButtonModuleDlg);

			m_DataManage.pModuleLinkList.Add(pSubButtonModuleDlg);
		}
	}
//初始化模块和列表(输出模块)
	if (pSubOutModuleDlg == NULL)	{
		pSubOutModuleDlg = new CSubOutPutModuleDlg;
		if (pSubOutModuleDlg != NULL)	{
			pSubOutModuleDlg->Create(IDD_SUB_OUTPUT_MODULE_DIALOG,GetDlgItem(IDC_STATIC_CUSTOMER));
			pSubOutModuleDlg->ShowWindow(SW_HIDE);
			m_ComModuleType.InsertString(Index,pSubOutModuleDlg->GetModuleName());
			m_ComModuleType.SetItemData(Index++,(DWORD_PTR)pSubOutModuleDlg);


			m_DataManage.pModuleLinkList.Add(pSubOutModuleDlg);
		}
	}

//IO模块
	if (pSubIoModuleDlg == NULL)
	{
		pSubIoModuleDlg = new CSubIoModuleDlg;
		if (pSubIoModuleDlg != NULL)
		{
			pSubIoModuleDlg->Create(IDD_SUB_IO_MODULE_DIALOG,GetDlgItem(IDC_STATIC_CUSTOMER));
			pSubIoModuleDlg->ShowWindow(SW_HIDE);

			m_ComModuleType.InsertString(Index,pSubIoModuleDlg->GetModuleName());
			m_ComModuleType.SetItemData(Index++,(DWORD_PTR)pSubIoModuleDlg);

			m_DataManage.pModuleLinkList.Add(pSubIoModuleDlg);
		}
	}
//门卡门牌
	if (pSubCardDlg == NULL)
	{
		pSubCardDlg = new CSubCardDlg;
		if (pSubCardDlg != NULL)
		{
			pSubCardDlg->Create(IDD_SUB_CARD_DIALOG,GetDlgItem(IDC_STATIC_CUSTOMER));
			pSubCardDlg->ShowWindow(SW_HIDE);

			m_ComModuleType.InsertString(Index,pSubCardDlg->GetModuleName());
			m_ComModuleType.SetItemData(Index++,(DWORD_PTR)pSubCardDlg);

			m_DataManage.pModuleLinkList.Add(pSubCardDlg);
		}
	}



//空调模块
	if (pSubAirConditionModuleDlg == NULL)
	{
		pSubAirConditionModuleDlg = new CSubAirConditionModuleDlg;
		if (pSubAirConditionModuleDlg != NULL)
		{
			pSubAirConditionModuleDlg->Create(IDD_SUB_AIRCONDITION_MODULE_DIALOG,GetDlgItem(IDC_STATIC_CUSTOMER));
			pSubButtonModuleDlg->ShowWindow(SW_HIDE);

			m_ComModuleType.InsertString(Index,pSubAirConditionModuleDlg->GetModuleName());
			m_ComModuleType.SetItemData(Index++,(DWORD_PTR)pSubAirConditionModuleDlg);

			m_DataManage.pModuleLinkList.Add(pSubAirConditionModuleDlg);
		}
	}
//门牌显示模块
	if (pSubNumberDlg == NULL)
	{
		pSubNumberDlg = new CSubNumberDlg;
		if (pSubNumberDlg != NULL)
		{
			pSubNumberDlg->Create(IDD_SUB_NUMBER_DIALOG,GetDlgItem(IDC_STATIC_CUSTOMER));
			pSubNumberDlg->ShowWindow(SW_HIDE);

			m_ComModuleType.InsertString(Index,pSubNumberDlg->GetModuleName());
			m_ComModuleType.SetItemData(Index++,(DWORD_PTR)pSubNumberDlg);

			m_DataManage.pModuleLinkList.Add(pSubCardDlg);
		}
	}
//场景模块
	if (pSubStageDlg == NULL)
	{
		pSubStageDlg = new CSubStageDlg;
		if (pSubStageDlg != NULL)
		{
			pSubStageDlg->Create(IDD_SUB_STAGE_DIALOG,GetDlgItem(IDC_STATIC_CUSTOMER));
			pSubStageDlg->ShowWindow(SW_HIDE);

			m_ComModuleType.InsertString(Index,pSubStageDlg->GetModuleName());
			m_ComModuleType.SetItemData(Index++,(DWORD_PTR)pSubStageDlg);

			m_DataManage.pModuleLinkList.Add(pSubStageDlg);
		}
	}
	//if (pSubStageModuleDlg == NULL)
	//{
	//	pSubStageModuleDlg = new CSubStageModuleDlg;
	//	if (pSubStageModuleDlg != NULL)
	//	{
	//		pSubStageModuleDlg->Create(IDD_SUB_STAGE_MODULE_DIALOG,GetDlgItem(IDC_STATIC_CUSTOMER));
	//		pSubStageModuleDlg->ShowWindow(SW_HIDE);

	//		m_ComModuleType.InsertString(Index,pSubStageModuleDlg->GetModuleName());
	//		m_ComModuleType.SetItemData(Index++,(DWORD_PTR)pSubStageModuleDlg);

	//		m_DataManage.pModuleLinkList.Add(pSubStageModuleDlg);
	//	}
	//}




//默认的类型选择
	if (m_ComModuleType.GetCount())	{		m_ComModuleType.SetCurSel(0);	}
	OnCbnSelchangeComboModuleType();

}
void CModuleCfgDlg::OnCbnSelchangeComboModuleType()
{
	// TODO: Add your control notification handler code here
	int nIndex = m_ComModuleType.GetCurSel();
	if (nIndex == -1)	{	return;	}
	CWnd *pWnd = (CWnd *)(m_ComModuleType.GetItemData(nIndex));
//============================================================================================
	PCHAR pSubName = NULL;
	int Index = 0;
//1、子模块全清空
	if (m_ComModuleName.GetCount())	{	m_ComModuleName.ResetContent();		}
	while (1)
	{
		pWnd->SendMessage(WM_GET_SUB_MODULE_NAME,(WPARAM)&pSubName,Index);
		if (pSubName == NULL)	{	break;	}
		m_ComModuleName.InsertString(Index++,pSubName);
	}
	if (m_ComModuleName.GetCount())	{	m_ComModuleName.SetCurSel(0);	}
	OnCbnSelchangeComboModuleName();
}

void CModuleCfgDlg::OnCbnSelchangeComboModuleName()
{
	// TODO: Add your control notification handler code here
	int nSubIndex = m_ComModuleName.GetCurSel();
	if (nSubIndex == -1)	{	return;	}


	//pSubOutModuleDlg->PostMessage(WM_ENABLE_CTRL_ITEM,NULL,nSubIndex);
}

void CModuleCfgDlg::OnBnClickedBtnAdd()
{
	PMODULE_ENTRY pModuleEntry = NULL;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int nIndex = m_ComModuleType.GetCurSel();	
	int nSubIndex = m_ComModuleName.GetCurSel();
	int nDeviceTypeEntry = m_DeviceTypeKey.GetCurSel();
	if ((nIndex == -1) && (nSubIndex == -1))		{		return;		}
//======================================================================================================================
	pModuleEntry = m_DataManage.InsertModule(nIndex,nSubIndex,nDeviceTypeEntry,m_ModuleAddress);
	if (pModuleEntry == NULL)	{	
		MessageBox("模块地址已经存在配置信息中");
		return ;
	}
	InsertOneModuleToList(pModuleEntry);














}



void	CModuleCfgDlg::InsertOneModuleToList(PMODULE_ENTRY pModule)
{
	CString str;
	PCHAR pSubName = NULL;
	int nEntry = m_ModuleList.GetItemCount();
//================================================================================
	m_ModuleList.InsertItem(nEntry,NULL);

	str.Format("%d",pModule->bEntry);
	m_ModuleList.SetItemText(nEntry,1,str);

	CWnd *pWnd = (CWnd *)(m_ComModuleType.GetItemData(pModule->bModuleType));
	pWnd->SendMessage(WM_GET_SUB_MODULE_NAME,(WPARAM)&pSubName,pModule->bModuleName);
	if (pSubName != NULL)	{
		m_ModuleList.SetItemText(nEntry,2,pSubName);
	}else{	m_ModuleList.SetItemText(nEntry,2,"**********");	}
	str.Format("%ld",pModule->dwModuleAddress);
	m_ModuleList.SetItemText(nEntry,3,str);
	m_ModuleList.SetItemData(nEntry,(DWORD_PTR)pModule);
}
void CModuleCfgDlg::OnLvnItemchangedModuleList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	PMODULE_ENTRY pModule = NULL;

	*pResult = 0;
// TODO: Add your control notification handler code here
	if((pNMListView->uNewState)  && !(pNMListView->uOldState))
	{
		pModule = (PMODULE_ENTRY)m_ModuleList.GetItemData(pNMListView->iItem);
		if (pModule == NULL)	{	return ;	}
		m_ComModuleType.SetCurSel(pModule->bModuleType);
		OnCbnSelchangeComboModuleType();
	//========================================================================================================
		m_ComModuleName.SetCurSel(pModule->bModuleName);
		m_DeviceTypeKey.SetCurSel(pModule->bDeviceType);
		SetDlgItemInt(IDC_MODULE_ADDRESS,pModule->dwModuleAddress);
		//===========================================================================
		CWnd *pWnd = (CWnd *)m_ComModuleType.GetItemData(pModule->bModuleType);
		ActiveSelModule(pWnd,pModule->bModuleName,pModule);



		//PMCU_INFO m_pMCU = &(((PROOM_CONFIG_INFO)lpCfgBuf)->MCU[m_ComMcuIndex.GetCurSel()]);
		////==================================================================================================================
		////显示的模块信息
		//m_ComModuleType.SetCurSel(m_pMCU->Module[nModuleIndex].ModuleClass);
		//OnSelchangeComboModuleType();
		//m_ComModuleName.SetCurSel(m_pMCU->Module[nModuleIndex].ModuleName);
		//m_ComModuleIndex.SetCurSel(nModuleIndex);	
		//SetDlgItemInt(IDC_MODULE_ADDRESS,m_pMCU->Module[nModuleIndex].ModuleAddress);
		////=================================================================
		//UpdateDlgView(m_pMCU,nModuleIndex);
	}


}


void CModuleCfgDlg::ActiveSelModule(CWnd *pWnd,UINT nSubItem,PVOID lParam)
{
//======================================================================================================
	if (pWnd == pSubOutModuleDlg)	{
		pSubOutModuleDlg->SetModuleMemory(nSubItem,lParam);	
		if (pWnd != pSelModuleWnd){		pSubOutModuleDlg->ShowWindow(SW_SHOWNORMAL);	}
		else {	pSubOutModuleDlg->SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)lParam,nSubItem);		}
	}else{
		pSubOutModuleDlg->ShowWindow(SW_HIDE);
	}
//======================================================================================================
	if (pWnd == pSubButtonModuleDlg)	{
		pSubButtonModuleDlg->SetModuleMemory(nSubItem,lParam);	
		if (pWnd != pSelModuleWnd){		pSubButtonModuleDlg->ShowWindow(SW_SHOWNORMAL);	}
		else {	pSubButtonModuleDlg->SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)lParam,nSubItem);		}
	}else{
		pSubButtonModuleDlg->ShowWindow(SW_HIDE);
	}	

//======================================================================================================
	if (pWnd == pSubAirConditionModuleDlg)	{
		pSubAirConditionModuleDlg->SetModuleMemory(nSubItem,lParam);	
		if (pWnd != pSelModuleWnd){		pSubAirConditionModuleDlg->ShowWindow(SW_SHOWNORMAL);	}
		else {	pSubAirConditionModuleDlg->SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)lParam,nSubItem);		}
	}else{
		pSubAirConditionModuleDlg->ShowWindow(SW_HIDE);
	}	
//======================================================================================================
	if (pWnd == pSubIoModuleDlg)	{
		pSubIoModuleDlg->SetModuleMemory(nSubItem,lParam);	
		if (pWnd != pSelModuleWnd){		pSubIoModuleDlg->ShowWindow(SW_SHOWNORMAL);	}
		pSubIoModuleDlg->SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)lParam,nSubItem);
	}else{
		pSubIoModuleDlg->ShowWindow(SW_HIDE);
	}		
//======================================================================================================
	if (pWnd == pSubStageDlg)	{
		pSubStageDlg->SetModuleMemory(nSubItem,lParam);	
		pSubStageDlg->InitListModule();
		if (pWnd != pSelModuleWnd){		
			pSubStageDlg->ShowWindow(SW_SHOWNORMAL);	
		}
		//pSubStageDlg->SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)lParam,nSubItem);
	}else{
		pSubStageDlg->ShowWindow(SW_HIDE);
	}		
	//if (pWnd == pSubStageModuleDlg)	{
	//	pSubStageModuleDlg->SetModuleMemory(nSubItem,lParam);	
	//	if (pWnd != pSelModuleWnd){		pSubStageModuleDlg->ShowWindow(SW_SHOWNORMAL);	}
	//	pSubStageModuleDlg->SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)lParam,nSubItem);
	//}else{
	//	pSubStageModuleDlg->ShowWindow(SW_HIDE);
	//}	
//======================================================================================================
	if (pWnd == pSubCardDlg)	{
		pSubCardDlg->SetModuleMemory(nSubItem,lParam);	
		if (pWnd != pSelModuleWnd){		pSubCardDlg->ShowWindow(SW_SHOWNORMAL);	}
		pSubCardDlg->SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)lParam,nSubItem);
	}else{
		pSubCardDlg->ShowWindow(SW_HIDE);
	}	
//======================================================================================================
	if (pWnd == pSubNumberDlg)	{
		pSubNumberDlg->SetModuleMemory(nSubItem,lParam);	
		if (pWnd != pSelModuleWnd){		pSubNumberDlg->ShowWindow(SW_SHOWNORMAL);	}
		pSubNumberDlg->SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)lParam,nSubItem);
	}else{
		pSubNumberDlg->ShowWindow(SW_HIDE);
	}	



	pSelModuleWnd = pWnd;
}

void   CModuleCfgDlg::InitDeviceTypeKey()
{
	const char *pDeviceType[] = {"RCU主模块","空调模块","8路继电器模块","4路调光板","2路继电器模块","3路LED调光板","门牌显示模块","RFID插卡取电模块","20按键模块"};
	int nEntry = 0;
	for (nEntry=0;nEntry<9;nEntry++)
	{
		m_DeviceTypeKey.InsertString(nEntry,pDeviceType[nEntry]);
	}
	m_DeviceTypeKey.SetCurSel(0);
}

void CModuleCfgDlg::OnBnClickedBtnDelete()
{
	// TODO: Add your control notification handler code here
	CString str;
	int entry;
	POSITION pos = m_ModuleList.GetFirstSelectedItemPosition(); //拿到第一个被选择的项目位置；
	if (NULL == pos)
	{
		return;
	}
	while(pos)
	{ 
		int nSelIndex = m_ModuleList.GetNextSelectedItem(pos);//通过前一个位置,拿到下一个位置的项目的索引号;
		str = m_ModuleList.GetItemText(nSelIndex,1);
		entry = _ttoi(str);
		m_ModuleList.DeleteItem(nSelIndex);//删除所选择的那项;
		m_DataManage.DeleteModule(entry);
		pos = m_ModuleList.GetFirstSelectedItemPosition();//因为前面删除了一项,所以list的结构发生了变化,所以得重新再判断第一个位置拿到pos;
	}
}