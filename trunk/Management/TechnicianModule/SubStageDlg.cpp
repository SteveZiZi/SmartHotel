// SubStageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TechnicianModule.h"
#include "SubStageDlg.h"

// CSubStageDlg dialog
#define			MAX_SUB_SATGE_MODULE_NUM		14
const char		*pSubStageModuleName[14] = {"普通场景1","普通场景2","普通场景3","普通场景4","普通场景5","普通场景6","普通场景7","门卡插入场景","门卡拔出场景",
"红外检测有人场景","红外检测无人场景","总电源场景","房门场景",""};
const USHORT	pSubStageModuleParam[] = {0x0600,0x0A00,0x0A00,0x0000};



IMPLEMENT_DYNAMIC(CSubStageDlg, CDialog)

CSubStageDlg::CSubStageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubStageDlg::IDD, pParent)
	, mArgument(0)
{

}

CSubStageDlg::~CSubStageDlg()
{
}

void CSubStageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUN, m_ComboSpecialFun);
	DDX_Text(pDX, IDC_EDIT_PARAM, mArgument);
	DDX_Control(pDX, IDC_COMBO_MODULE_ENTRY, m_ModuleName);
	DDX_Control(pDX, IDC_COMBO_SUB_ENTRY, m_SubEntry);
	DDX_Control(pDX, IDC_DATA_LIST, m_DataList);
}


BEGIN_MESSAGE_MAP(CSubStageDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_GET_SUB_MODULE_NAME,&CSubStageDlg::Msg_GetSubModuleName)
	ON_BN_CLICKED(IDC_BTN_CLEAN, &CSubStageDlg::OnBnClickedBtnClean)
	ON_BN_CLICKED(IDC_BTN_ADD, &CSubStageDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CSubStageDlg::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CSubStageDlg::OnBnClickedBtnDelete)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_MODULE_ENTRY, &CSubStageDlg::OnCbnSelchangeComboModuleEntry)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DATA_LIST, &CSubStageDlg::OnLvnItemchangedDataList)
END_MESSAGE_MAP()


// CSubStageDlg message handlers

BOOL CSubStageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitSpecialFunCombo();
	InitListCtrl();
	//InitModule();
	//InitListModule();






	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSubStageDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

void CSubStageDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CSubStageDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}

void CSubStageDlg::OnBnClickedBtnClean()
{
	// TODO: Add your control notification handler code here
}

void CSubStageDlg::OnBnClickedBtnAdd()
{
	//UpdateData();
	BOOL bRest = FALSE;
	CONTROL_DEVICE_UNIT m_CtrlDevUnit;
	PCONTROL_DEVICE_UNIT	pCtrlDevUnit = NULL;
	ZeroMemory(&m_CtrlDevUnit,sizeof(CONTROL_DEVICE_UNIT));
// TODO: Add your control notification handler code here
	int nModuleEntry = m_ModuleName.GetCurSel();
	//if (m_SubEntry.GetCount())	{	m_SubEntry.ResetContent();	}
	if (nModuleEntry == -1)		{	return ;	}
	PMODULE_ENTRY  pModule =  (PMODULE_ENTRY)m_ModuleName.GetItemData(nModuleEntry);
	if (pModule == NULL)	{	return;	}
	m_CtrlDevUnit.bModuleEntry = pModule->bEntry;
//
	int nSubEntry = m_SubEntry.GetCurSel();
	if (nSubEntry  == -1)	{	return;		}
	nSubEntry = m_SubEntry.GetItemData(nSubEntry);
	m_CtrlDevUnit.bSubModuleItem = nSubEntry;
////
	int nSpec = m_ComboSpecialFun.GetCurSel();
	if (nSpec  == -1)	{	return;		}
	m_CtrlDevUnit.bSpecialFundef = nSpec;
//==============================================================================================
	m_CtrlDevUnit.dwArgument = GetDlgItemInt(IDC_EDIT_PARAM);//IDC_COMBO_SUB_ENTRY);//mArgument;


	pCtrlDevUnit = SearchModuleExist(&m_CtrlDevUnit);
	if (pCtrlDevUnit != NULL)	{	MessageBox("模块已经存在");		return;}
	pCtrlDevUnit = GetFreeEntryMem();
	if (pCtrlDevUnit == NULL)	{	MessageBox("模块已经超过存储空间");		return;}
	memcpy(pCtrlDevUnit,&m_CtrlDevUnit,sizeof(CONTROL_DEVICE_UNIT));
	UpdateListCtrl(pCtrlDevUnit,0);

















}

void CSubStageDlg::OnBnClickedBtnModify()
{
	// TODO: Add your control notification handler code here
	//UpdateData();
	BOOL bRest = FALSE;
	CONTROL_DEVICE_UNIT m_CtrlDevUnit;
	PCONTROL_DEVICE_UNIT	pCtrlDevUnit = NULL;
	ZeroMemory(&m_CtrlDevUnit,sizeof(CONTROL_DEVICE_UNIT));
	// TODO: Add your control notification handler code here
	int nModuleEntry = m_ModuleName.GetCurSel();
	//if (m_SubEntry.GetCount())	{	m_SubEntry.ResetContent();	}
	if (nModuleEntry == -1)		{	return ;	}
	PMODULE_ENTRY  pModule =  (PMODULE_ENTRY)m_ModuleName.GetItemData(nModuleEntry);
	if (pModule == NULL)	{	return;	}
	m_CtrlDevUnit.bModuleEntry = pModule->bEntry;
	//
	int nSubEntry = m_SubEntry.GetCurSel();
	if (nSubEntry  == -1)	{	return;		}
	nSubEntry = m_SubEntry.GetItemData(nSubEntry);
	m_CtrlDevUnit.bSubModuleItem = nSubEntry;
	////
	int nSpec = m_ComboSpecialFun.GetCurSel();
	if (nSpec  == -1)	{	return;		}
	m_CtrlDevUnit.bSpecialFundef = nSpec;
	//==============================================================================================
	m_CtrlDevUnit.dwArgument = GetDlgItemInt(IDC_EDIT_PARAM);//IDC_COMBO_SUB_ENTRY);//mArgument;
	pCtrlDevUnit = SearchModuleExist(&m_CtrlDevUnit);
	if (pCtrlDevUnit == NULL)	{	MessageBox("模块不存在");	return;	}
	pCtrlDevUnit->bSpecialFundef = m_CtrlDevUnit.bSpecialFundef;
	pCtrlDevUnit->dwArgument = m_CtrlDevUnit.dwArgument;

	UpdateListCtrl(pCtrlDevUnit,1);




}

void CSubStageDlg::OnBnClickedBtnDelete()
{
	// TODO: Add your control notification handler code here
	BOOL bRest = FALSE;
	CONTROL_DEVICE_UNIT m_CtrlDevUnit;
	PCONTROL_DEVICE_UNIT	pCtrlDevUnit = NULL;
	ZeroMemory(&m_CtrlDevUnit,sizeof(CONTROL_DEVICE_UNIT));
	// TODO: Add your control notification handler code here
	int nModuleEntry = m_ModuleName.GetCurSel();
	//if (m_SubEntry.GetCount())	{	m_SubEntry.ResetContent();	}
	if (nModuleEntry == -1)		{	return ;	}
	PMODULE_ENTRY  pModule =  (PMODULE_ENTRY)m_ModuleName.GetItemData(nModuleEntry);
	if (pModule == NULL)	{	return;	}
	m_CtrlDevUnit.bModuleEntry = pModule->bEntry;
	//
	int nSubEntry = m_SubEntry.GetCurSel();
	if (nSubEntry  == -1)	{	return;		}
	nSubEntry = m_SubEntry.GetItemData(nSubEntry);
	m_CtrlDevUnit.bSubModuleItem = nSubEntry;



	pCtrlDevUnit = SearchModuleExist(&m_CtrlDevUnit);
	if (pCtrlDevUnit == NULL)	{	MessageBox("模块不存在");	return;	}
	UpdateListCtrl(&m_CtrlDevUnit,2);
	ZeroMemory(pCtrlDevUnit,sizeof(CONTROL_DEVICE_UNIT));
}

void CSubStageDlg::InitSpecialFunCombo()
{
	int Index = 0;
	PCHAR pContext = NULL;
	if (m_ComboSpecialFun.GetCount())	{	m_ComboSpecialFun.ResetContent();	}
	//============================================================================
	do {
		pContext = m_DataManage.GetSpecialFunName(Index);
		if (pContext != NULL){	m_ComboSpecialFun.InsertString(Index++,pContext);	}
	}while(pContext != NULL);

	if (m_ComboSpecialFun.GetCount())	{	m_ComboSpecialFun.SetCurSel(0);	}
}

void CSubStageDlg::InitListCtrl()
{
	int Index = 0;
	DWORD dwStyle = m_DataList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	//m_ModuleList.ModifyStyle(0,dwStyle);
	m_DataList.SetExtendedStyle(dwStyle);
	//====================================================================================
	CRect rt;
	::GetClientRect(GetDlgItem(IDC_DATA_LIST)->GetSafeHwnd(),&rt);
	int nWidth = rt.Width()/4;


	m_DataList.InsertColumn(Index++,"",LVCFMT_CENTER,0);
	//m_ReleasionList.InsertColumn(Index++,"索引",LVCFMT_CENTER,60);
	m_DataList.InsertColumn(Index++,"模块名称",LVCFMT_CENTER,nWidth-10);
	m_DataList.InsertColumn(Index++,"子路索引",LVCFMT_CENTER,nWidth);
	m_DataList.InsertColumn(Index++,"特殊功能",LVCFMT_CENTER,nWidth+20);


	m_DataList.InsertColumn(Index++,"子路参数",LVCFMT_CENTER,nWidth-10);
}


void CSubStageDlg::InitModule()
{
	int Index = 0;
	CString str;
	PCHAR pName = NULL;
	int nEntry = 0;
	for (Index=0;Index<MAX_MODULE_NUMBER;Index++)
	{
		pName = m_DataManage.GetSubModuleName(Index);
		if (pName != NULL){
			str.Format("[%d]%s",m_DataManage.pRoomUnit->mModuleEntry[Index].bEntry,pName);
			m_ModuleName.InsertString(nEntry,str);
			m_ModuleName.SetItemData(nEntry,(DWORD_PTR)(&(m_DataManage.pRoomUnit->mModuleEntry[Index])));
			nEntry++;
		}
	}

	if (nEntry)	{	m_ModuleName.SetCurSel(0);	}
	OnCbnSelchangeComboModuleEntry();

}

LRESULT CSubStageDlg::Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam)
{
	int nEntry = (int)lParam;
	PCHAR *pSubName = (PCHAR *)wParam;
	(*pSubName) =  NULL;
	if (nEntry < MAX_SUB_SATGE_MODULE_NUM)	{	(*pSubName) = (PCHAR)pSubStageModuleName[nEntry];	}
	if (strcmp((*pSubName),"") == 0)	{	(*pSubName) =  NULL;	}
	return S_OK;
}



void CSubStageDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	if (bShow == TRUE){
		InitModule();
		//InitListModule();
	}else{
		if (m_ModuleName.GetCount())	{
			m_ModuleName.ResetContent();
		}
	}





	// TODO: Add your message handler code here
}

void CSubStageDlg::OnCbnSelchangeComboModuleEntry()
{
	// TODO: Add your control notification handler code here
	int nModuleEntry = m_ModuleName.GetCurSel();
	if (m_SubEntry.GetCount())	{	m_SubEntry.ResetContent();	}
	if (nModuleEntry == -1)		{	return ;	}
	PMODULE_ENTRY  pModule =  (PMODULE_ENTRY)m_ModuleName.GetItemData(nModuleEntry);
	if (pModule == NULL)	{	return;	}

	PMODULE_KEY_UNIT  pModuleKey = pModule->mKeyUnit;
	int Index = 0;
	nModuleEntry = pModule->bEntry-1;
	PCHAR pName = NULL;
	//==============================================================================================================
	while (Index < MAX_MODULE_KEY_NUMBER)
	{
		pName = m_DataManage.GetModuleKeyEntry(nModuleEntry,Index);
		if (pName != NULL)	{
			int nEntry = m_SubEntry.AddString(pName);
			m_SubEntry.SetItemData(nEntry,Index+1);
		}
		Index++;
		pModuleKey++;
	}
	//==============================================================================================================
	if (m_SubEntry.GetCount())	{	
		m_SubEntry.SetCurSel(0);	
	}
}


PCONTROL_DEVICE_UNIT CSubStageDlg::GetFreeEntryMem()
{
	PCONTROL_DEVICE_UNIT pDeviceUnit = NULL;
	int i,j;
	for (i=0;i<MAX_MODULE_KEY_NUMBER;i++)
	{
		if (&(m_pModule->mKeyUnit[i]) == NULL)	{	break;	}
		for (j=0;j<MAX_CTRL_MODULE_NUMBER;j++)
		{
			if (m_pModule->mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].bModuleEntry == 0){
				pDeviceUnit = &(m_pModule->mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j]);
				break;
			}
		}
		if (pDeviceUnit != NULL){	break;	}
	}
	return pDeviceUnit;
}



PCONTROL_DEVICE_UNIT CSubStageDlg::SearchModuleExist(PCONTROL_DEVICE_UNIT pCtrlUnit)
{
	PCONTROL_DEVICE_UNIT pDeviceUnit = NULL;
	int i,j;
	if (NULL == pCtrlUnit)	
	{	
		return NULL;	
	}
	for (i=0;i<MAX_MODULE_KEY_NUMBER;i++)
	{
		if (&(m_pModule->mKeyUnit[i]) == NULL)	{	break;	}
		for (j=0;j<MAX_CTRL_MODULE_NUMBER;j++)
		{
			if ((m_pModule->mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].bModuleEntry == pCtrlUnit->bModuleEntry) && \
			(m_pModule->mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j].bSubModuleItem == pCtrlUnit->bSubModuleItem))
			{
				pDeviceUnit = &(m_pModule->mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j]);
				break;
			}
		}
		if (pDeviceUnit != NULL){	break;	}
	}
	return pDeviceUnit;
}


void CSubStageDlg::UpdateListCtrl(LPVOID lParam,int n)
{
	int nEntry = 0;
	CString str;
	PCONTROL_DEVICE_UNIT pDeviceUnit = (PCONTROL_DEVICE_UNIT)lParam;
	if (n == 0){
		nEntry = m_DataList.GetItemCount();
		m_DataList.InsertItem(nEntry,NULL);
		m_DataList.SetItemData(nEntry,(DWORD_PTR)pDeviceUnit);
	}else if(n == 1){
		nEntry = nFindStringInList(lParam);
	}else if (n==2)
	{
		nEntry = nFindStringInList(lParam);
		if (nEntry != -1){
			m_DataList.DeleteItem(nEntry);
		}
		return;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_DataList.SetItemText(nEntry,1, m_DataManage.GetSubModuleName(pDeviceUnit->bModuleEntry-1));
	m_DataList.SetItemText(nEntry,2, m_DataManage.GetModuleKeyEntry(pDeviceUnit->bModuleEntry-1,pDeviceUnit->bSubModuleItem-1));
	m_DataList.SetItemText(nEntry,3,m_DataManage.GetSpecialFunName(pDeviceUnit->bSpecialFundef));
	str.Format("%d",pDeviceUnit->dwArgument);
	m_DataList.SetItemText(nEntry,4,str);








}

int  CSubStageDlg::nFindStringInList(LPVOID lParam)
{
	int nEntry = -1;
	CString str;
	PCONTROL_DEVICE_UNIT pDeviceUnit = (PCONTROL_DEVICE_UNIT)lParam;
	PCONTROL_DEVICE_UNIT pTempUnit = NULL;
	for (int Index=0;Index<m_DataList.GetItemCount();Index++)
	{
		pTempUnit = (PCONTROL_DEVICE_UNIT)m_DataList.GetItemData(Index);
		if (pTempUnit == NULL)	{	continue;	}
		if ((pDeviceUnit->bModuleEntry == pTempUnit->bModuleEntry) && (pDeviceUnit->bSubModuleItem == pTempUnit->bSubModuleItem))
		{
			nEntry = Index;
			break;
		}
	}
	return nEntry;
}


void CSubStageDlg::InitListModule()
{
	PCONTROL_DEVICE_UNIT pDeviceUnit = NULL;
	int i,j,n;
	if (m_DataList.GetItemCount()){
		m_DataList.DeleteAllItems();
	}

	n = 0;
	for (i=0;i<MAX_MODULE_KEY_NUMBER;i++)
	{
		//if (&(pModule->mKeyUnit[i]) == NULL)	{	break;	}
		for (j=0;j<MAX_CTRL_MODULE_NUMBER;j++)
		{
			pDeviceUnit = &(m_pModule->mKeyUnit[i].mContent.mCtrlDeviceList.mCtrlDev[j]);
			if (pDeviceUnit->bSubModuleItem != 0)
			{
				UpdateListCtrl(pDeviceUnit,0);
				n++;
			}
		}
	}
}
void CSubStageDlg::OnLvnItemchangedDataList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	PCONTROL_DEVICE_UNIT pDeviceUnit = NULL;
	int i = 0;
	// TODO: Add your control notification handler code here
	if (pNMLV->iItem != -1)
	{
		pDeviceUnit = (PCONTROL_DEVICE_UNIT)m_DataList.GetItemData(pNMLV->iItem);
		if (pDeviceUnit != NULL)
		{
			m_ModuleName.SetCurSel(pDeviceUnit->bModuleEntry-1);
			OnCbnSelchangeComboModuleEntry();
			for (i=0;i<m_SubEntry.GetCount();i++){
				if (pDeviceUnit->bSubModuleItem == m_SubEntry.GetItemData(i)){
					break;
				}
			}
			m_SubEntry.SetCurSel(i);
			m_ComboSpecialFun.SetCurSel(pDeviceUnit->bSpecialFundef);
			SetDlgItemInt(IDC_EDIT_PARAM,pDeviceUnit->dwArgument);
		}
	}








	*pResult = 0;
}
