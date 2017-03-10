// SubAirConditionModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TechnicianModule.h"
#include "SubAirConditionModuleDlg.h"
#include "UnitKeyConfigDlg.h"

#define		MAX_SUB_AIR_CONDITION_MODULE_NUM		2
const char		*pSubAirModuleName[32] = {"空调模块",""};
const USHORT	pSubAirModuleParam[] = {0x0400,0x0000};

// CSubAirConditionModuleDlg dialog

IMPLEMENT_DYNAMIC(CSubAirConditionModuleDlg, CDialog)

CSubAirConditionModuleDlg::CSubAirConditionModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubAirConditionModuleDlg::IDD, pParent)
{

}

CSubAirConditionModuleDlg::~CSubAirConditionModuleDlg()
{
}

void CSubAirConditionModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION, m_SpecialFun[0]);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION2, m_SpecialFun[1]);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION3, m_SpecialFun[2]);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION4, m_SpecialFun[3]);
	
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY, mEntryKey[0]);
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY2, mEntryKey[1]);
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY3, mEntryKey[2]);
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY4, mEntryKey[3]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME, mModuleName[0]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME2, mModuleName[1]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME3, mModuleName[2]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME4, mModuleName[3]);
}


BEGIN_MESSAGE_MAP(CSubAirConditionModuleDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_GET_SUB_MODULE_NAME,&CSubAirConditionModuleDlg::Msg_GetSubModuleName)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY1, &CSubAirConditionModuleDlg::OnStnDblclickStaticEntry1)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY2, &CSubAirConditionModuleDlg::OnStnDblclickStaticEntry2)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY3, &CSubAirConditionModuleDlg::OnStnDblclickStaticEntry3)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY4, &CSubAirConditionModuleDlg::OnStnDblclickStaticEntry4)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME, &CSubAirConditionModuleDlg::OnCbnSelchangeValidModuleName)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME2, &CSubAirConditionModuleDlg::OnCbnSelchangeValidModuleName2)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME3, &CSubAirConditionModuleDlg::OnCbnSelchangeValidModuleName3)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME4, &CSubAirConditionModuleDlg::OnCbnSelchangeValidModuleName4)
END_MESSAGE_MAP()


// CSubAirConditionModuleDlg message handlers
// CSubButtonModuleDlg 消息处理程序

BOOL CSubAirConditionModuleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	InitSpecialFunCombo();
	//InitAllDlgItemCtrl();

	//InitPopMenu();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
BOOL CSubAirConditionModuleDlg::PreTranslateMessage(MSG* pMsg)
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

void CSubAirConditionModuleDlg::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PreSubclassWindow();
}

void CSubAirConditionModuleDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
	if (bShow == TRUE)	{
	//	SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)pModule,nSubNameEntry);
		InitAllDlgItemCtrl();
	}


}
LRESULT CSubAirConditionModuleDlg::Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam)
{
//	PMODULE_ENTRY pModuleEntry = (PMODULE_ENTRY)wParam;
//	int iModuleEntry = (int)lParam;
//	BYTE nInput = (pSubButtonModuleParam[iModuleEntry] >> 8) & 0x00FF;
//	BYTE nOutPut = pSubButtonModuleParam[iModuleEntry]  & 0x00FF;
//	UINT nBaseItemID = IDC_ITEM_ENTRY1;
//	for (int Index = 0;Index < 20;Index++)
//	{
//		UINT bFlag = SW_HIDE;
//		if (Index	<	nInput)	{	bFlag = SW_SHOWNORMAL;	}
//		((CButton *)GetDlgItem(nBaseItemID+Index))->ShowWindow(bFlag);
//	}
//	((CButton *)GetDlgItem(IDC_ITEM_ENTRY21))->ShowWindow(SW_HIDE);
////===============================================================================================
//	CRect rt;
//	GetClientRect(rt);
//	rt.top = 10 + 40*(nInput/4);
//	m_ReleasionList.MoveWindow(rt,TRUE);
//
//
//	if (m_ReleasionList.GetItemCount())		{	m_ReleasionList.DeleteAllItems();	}
	return S_OK;
}
LRESULT CSubAirConditionModuleDlg::Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam)
{
	int nEntry = (int)lParam;
	PCHAR *pSubName = (PCHAR *)wParam;

	(*pSubName) =  NULL;
	if (nEntry < MAX_SUB_AIR_CONDITION_MODULE_NUM)	{	(*pSubName) = (PCHAR)pSubAirModuleName[nEntry];	}
	if (strcmp((*pSubName),"") == 0)	{	(*pSubName) =  NULL;	}

	return S_OK;
}
void  CSubAirConditionModuleDlg::InitAllDlgItemCtrl()
{

	if (pModule == NULL)	{		return;		}
	int Index = 0;
	//CString str;
//初始化各控件
	for (Index=0;Index<4;Index++)
	{
		FillModuleKeyReleasion(Index);
	}
	OnCbnSelchangeValidModuleName();
	OnCbnSelchangeValidModuleName2();
	OnCbnSelchangeValidModuleName3();
	OnCbnSelchangeValidModuleName4();
}


void  CSubAirConditionModuleDlg::FillModuleKeyReleasion(int nOffset)
{
	CString str;
	if (pModule == NULL)	{	return;	}
	PMODULE_KEY_UNIT		pModuleKeyUnit = &(pModule->mKeyUnit[nOffset]);
	PCONTROL_DEVICE_UNIT	pCtrlDev = pModuleKeyUnit->mContent.mCtrlDeviceList.mCtrlDev;
//=====================================================================================================
	if (mModuleName[nOffset].GetCount())		{	mModuleName[nOffset].ResetContent();	}
	int nEntry = 0;
	for (int i=0;i<MAX_CTRL_MODULE_NUMBER;i++)
	{
		if (pCtrlDev->bModuleEntry){
			str.Format("[%d]",pCtrlDev->bModuleEntry);
			mModuleName[nOffset].InsertString(nEntry,str);
			mModuleName[nOffset].SetItemData(nEntry,(DWORD_PTR)pCtrlDev);
			nEntry++;
		}
		pCtrlDev++;
	}

	if (nEntry)	{	mModuleName[nOffset].SetCurSel(0);		}
}


void CSubAirConditionModuleDlg::SetCfgModuleKey(UINT nOffset)
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


//void CSubAirConditionModuleDlg::OnViewConfigInfo()
//{
//	UINT nID = GetFocus()->GetDlgCtrlID();
//	if ((nID < IDC_ITEM_ENTRY1) || (nID > IDC_ITEM_ENTRY20)){	return	;	}
//	
//	//FillModuleKeyReleasion(nID-IDC_ITEM_ENTRY1);
//}
//
//void CSubAirConditionModuleDlg::OnSetConfigInfo()
//{
//	UINT nID = GetFocus()->GetDlgCtrlID();
//	if ((nID < IDC_ITEM_ENTRY1) || (nID > IDC_ITEM_ENTRY20)){	return	;	}
//
//
//	//SetCfgModuleKey(nID-IDC_ITEM_ENTRY1);
//}

void CSubAirConditionModuleDlg::InitSpecialFunCombo()
{
	int Index = 0;
	PCHAR pContext = NULL;
	if (m_SpecialFun[0].GetCount())	{	m_SpecialFun[0].ResetContent();	}
	if (m_SpecialFun[1].GetCount())	{	m_SpecialFun[1].ResetContent();	}
	if (m_SpecialFun[2].GetCount())	{	m_SpecialFun[2].ResetContent();	}
	if (m_SpecialFun[3].GetCount())	{	m_SpecialFun[3].ResetContent();	}
	//============================================================================
	do {
		pContext = m_DataManage.GetSpecialFunName(Index);
		if (pContext != NULL){	
			m_SpecialFun[0].InsertString(Index,pContext);	
			m_SpecialFun[1].InsertString(Index,pContext);
			m_SpecialFun[2].InsertString(Index,pContext);
			m_SpecialFun[3].InsertString(Index,pContext);

			Index++;
		}
	}while(pContext != NULL);

//	if (m_ComboSpecialFun.GetCount())	{	m_ComboSpecialFun.SetCurSel(0);	}
}

void CSubAirConditionModuleDlg::OnStnDblclickStaticEntry1()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(0);
	OnCbnSelchangeValidModuleName();

}

void CSubAirConditionModuleDlg::OnStnDblclickStaticEntry2()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(1);

	OnCbnSelchangeValidModuleName2();
}

void CSubAirConditionModuleDlg::OnStnDblclickStaticEntry3()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(2);
	OnCbnSelchangeValidModuleName3();
}

void CSubAirConditionModuleDlg::OnStnDblclickStaticEntry4()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(3);
	OnCbnSelchangeValidModuleName4();
}

void CSubAirConditionModuleDlg::OnCbnSelchangeValidModuleName()
{
	// TODO: Add your control notification handler code here
	int nOffset = 0;
	if (mEntryKey[nOffset].GetCount())	{	mEntryKey[nOffset].ResetContent();	}
	int Index = mModuleName[nOffset].GetCurSel();
	if (Index == -1)	{	return;	}
	PCONTROL_DEVICE_UNIT	pCtrlDev = (PCONTROL_DEVICE_UNIT)(mModuleName[nOffset].GetItemData(Index));
	if (pCtrlDev == NULL)	{	return;	}
	CString str;
	str.Format("子路【%d】",pCtrlDev->bSubModuleItem);
	mEntryKey[nOffset].AddString(str);
	mEntryKey[nOffset].SetCurSel(0);


	m_SpecialFun[nOffset].SetCurSel(pCtrlDev->bSpecialFundef);
}

void CSubAirConditionModuleDlg::OnCbnSelchangeValidModuleName2()
{
	// TODO: Add your control notification handler code here
	int nOffset = 1;
	if (mEntryKey[nOffset].GetCount())	{	mEntryKey[nOffset].ResetContent();	}
	int Index = mModuleName[nOffset].GetCurSel();
	if (Index == -1)	{	return;	}
	PCONTROL_DEVICE_UNIT	pCtrlDev = (PCONTROL_DEVICE_UNIT)(mModuleName[nOffset].GetItemData(Index));
	if (pCtrlDev == NULL)	{	return;	}
	CString str;
	str.Format("子路【%d】",pCtrlDev->bSubModuleItem);
	mEntryKey[nOffset].AddString(str);
	mEntryKey[nOffset].SetCurSel(0);


	m_SpecialFun[nOffset].SetCurSel(pCtrlDev->bSpecialFundef);
}

void CSubAirConditionModuleDlg::OnCbnSelchangeValidModuleName3()
{
	// TODO: Add your control notification handler code here
	int nOffset = 2;
	if (mEntryKey[nOffset].GetCount())	{	mEntryKey[nOffset].ResetContent();	}
	int Index = mModuleName[nOffset].GetCurSel();
	if (Index == -1)	{	return;	}
	PCONTROL_DEVICE_UNIT	pCtrlDev = (PCONTROL_DEVICE_UNIT)(mModuleName[nOffset].GetItemData(Index));
	if (pCtrlDev == NULL)	{	return;	}
	CString str;
	str.Format("子路【%d】",pCtrlDev->bSubModuleItem);
	mEntryKey[nOffset].AddString(str);
	mEntryKey[nOffset].SetCurSel(0);


	m_SpecialFun[nOffset].SetCurSel(pCtrlDev->bSpecialFundef);
}

void CSubAirConditionModuleDlg::OnCbnSelchangeValidModuleName4()
{
	// TODO: Add your control notification handler code here
	int nOffset = 3;
	if (mEntryKey[nOffset].GetCount())	{	mEntryKey[nOffset].ResetContent();	}
	int Index = mModuleName[nOffset].GetCurSel();
	if (Index == -1)	{	return;	}
	PCONTROL_DEVICE_UNIT	pCtrlDev = (PCONTROL_DEVICE_UNIT)(mModuleName[nOffset].GetItemData(Index));
	if (pCtrlDev == NULL)	{	return;	}
	CString str;
	str.Format("子路【%d】",pCtrlDev->bSubModuleItem);
	mEntryKey[nOffset].AddString(str);
	mEntryKey[nOffset].SetCurSel(0);


	m_SpecialFun[nOffset].SetCurSel(pCtrlDev->bSpecialFundef);
}
