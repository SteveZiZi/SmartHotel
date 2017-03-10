// SubStageModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TechnicianModule.h"
#include "SubStageModuleDlg.h"
#include "UnitKeyConfigDlg.h"

//#define		MAX_SUB_SATGE_MODULE_NUM		4
//const char		*pSubStageModuleName[32] = {"普通场景","门卡场景","总电源场景",""};
//const USHORT	pSubStageModuleParam[] = {0x0600,0x0A00,0x0A00,0x0000};

// CSubStageModuleDlg dialog

IMPLEMENT_DYNAMIC(CSubStageModuleDlg, CDialog)

CSubStageModuleDlg::CSubStageModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubStageModuleDlg::IDD, pParent)
{

}

CSubStageModuleDlg::~CSubStageModuleDlg()
{
}

void CSubStageModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION,  m_SpecialFun[0]);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION1, m_SpecialFun[1]);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION2, m_SpecialFun[2]);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION3, m_SpecialFun[3]);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION4, m_SpecialFun[4]);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION5, m_SpecialFun[5]);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION6, m_SpecialFun[6]);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION7, m_SpecialFun[7]);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION8, m_SpecialFun[8]);
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION9, m_SpecialFun[9]);	
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY, mEntryKey[0]);
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY1, mEntryKey[1]);
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY2, mEntryKey[2]);
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY3, mEntryKey[3]);
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY4, mEntryKey[4]);
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY5, mEntryKey[5]);
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY6, mEntryKey[6]);
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY7, mEntryKey[7]);
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY8, mEntryKey[8]);
	DDX_Control(pDX, IDC_SUB_KEY_ENTRY9, mEntryKey[9]);

	DDX_Control(pDX, IDC_VALID_MODULE_NAME, mModuleName[0]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME1, mModuleName[1]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME2, mModuleName[2]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME3, mModuleName[3]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME4, mModuleName[4]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME5, mModuleName[5]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME6, mModuleName[6]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME7, mModuleName[7]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME8, mModuleName[8]);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME9, mModuleName[9]);
}


BEGIN_MESSAGE_MAP(CSubStageModuleDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_GET_SUB_MODULE_NAME,&CSubStageModuleDlg::Msg_GetSubModuleName)
	ON_MESSAGE(WM_ENABLE_CTRL_ITEM,&CSubStageModuleDlg::Msg_EnableCtrlItem)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME, &CSubStageModuleDlg::OnCbnSelchangeValidModuleName)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME1, &CSubStageModuleDlg::OnCbnSelchangeValidModuleName)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME2, &CSubStageModuleDlg::OnCbnSelchangeValidModuleName)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME3, &CSubStageModuleDlg::OnCbnSelchangeValidModuleName)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME4, &CSubStageModuleDlg::OnCbnSelchangeValidModuleName)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME5, &CSubStageModuleDlg::OnCbnSelchangeValidModuleName)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME6, &CSubStageModuleDlg::OnCbnSelchangeValidModuleName)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME7, &CSubStageModuleDlg::OnCbnSelchangeValidModuleName)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME8, &CSubStageModuleDlg::OnCbnSelchangeValidModuleName)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME9, &CSubStageModuleDlg::OnCbnSelchangeValidModuleName)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY, &CSubStageModuleDlg::OnStnDblclickStaticEntry)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY1, &CSubStageModuleDlg::OnStnDblclickStaticEntry1)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY2, &CSubStageModuleDlg::OnStnDblclickStaticEntry2)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY3, &CSubStageModuleDlg::OnStnDblclickStaticEntry3)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY4, &CSubStageModuleDlg::OnStnDblclickStaticEntry4)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY5, &CSubStageModuleDlg::OnStnDblclickStaticEntry5)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY6, &CSubStageModuleDlg::OnStnDblclickStaticEntry6)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY7, &CSubStageModuleDlg::OnStnDblclickStaticEntry7)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY8, &CSubStageModuleDlg::OnStnDblclickStaticEntry8)
	ON_STN_DBLCLK(IDC_STATIC_ENTRY9, &CSubStageModuleDlg::OnStnDblclickStaticEntry9)
END_MESSAGE_MAP()


// CSubStageModuleDlg message handlers

BOOL CSubStageModuleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitSpecialFunCombo();
	//InitAllDlgItemCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSubStageModuleDlg::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PreSubclassWindow();
}

BOOL CSubStageModuleDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

void CSubStageModuleDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
	if (bShow == TRUE)	{
		SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)pModule,nSubNameEntry);
	//	InitAllDlgItemCtrl();
	}


}
LRESULT CSubStageModuleDlg::Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam)
{
	PMODULE_ENTRY pModuleEntry = (PMODULE_ENTRY)wParam;
	BYTE nInput = (pSubStageModuleParam[nSubNameEntry] >> 8) & 0x00FF;
	BYTE nOutPut = pSubStageModuleParam[nSubNameEntry]  & 0x00FF;
//===============================================================================================
	for (int Index = 0;Index < 10;Index++)
	{
		int nFlag = SW_HIDE;
		if (Index < nInput)	{	nFlag = SW_SHOWNORMAL;	
			mEntryKey[Index].ResetContent();
			m_SpecialFun[Index].SetCurSel(-1);
			SetDlgItemText(IDC_EDIT_ARGUMENT+Index,NULL);
		}
		((CStatic *)GetDlgItem(IDC_STATIC_ENTRY+Index))->ShowWindow(nFlag);
		((CComboBox *)GetDlgItem(IDC_VALID_MODULE_NAME+Index))->ShowWindow(nFlag);
		((CComboBox *)GetDlgItem(IDC_SUB_KEY_ENTRY+Index))->ShowWindow(nFlag);
		((CComboBox *)GetDlgItem(IDC_COMBO_SPECIAL_FUNCTION+Index))->ShowWindow(nFlag);
		((CEdit *)GetDlgItem(IDC_EDIT_ARGUMENT+Index))->ShowWindow(nFlag);
		//=============================================================================================
		if (pModuleEntry && (nFlag == SW_SHOWNORMAL))	{	FillModuleKeyReleasion(Index);	}		
	}
	return S_OK;
}





LRESULT CSubStageModuleDlg::Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam)
{
	int nEntry = (int)lParam;
	PCHAR *pSubName = (PCHAR *)wParam;
	(*pSubName) =  NULL;
	if (nEntry < MAX_SUB_SATGE_MODULE_NUM)	{	(*pSubName) = (PCHAR)pSubStageModuleName[nEntry];	}
	if (strcmp((*pSubName),"") == 0)	{	(*pSubName) =  NULL;	}
	return S_OK;
}
void CSubStageModuleDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CSubStageModuleDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}


void CSubStageModuleDlg::InitSpecialFunCombo()
{
	int Index = 0,nEntry=0;
	PCHAR pContext = NULL;
	for (Index =0;Index<10;Index++){
		if (m_SpecialFun[Index].GetCount())	{	m_SpecialFun[Index].ResetContent();	}
	}
	Index = 0;
	//============================================================================
	do {
		Index =0 ;
		pContext = m_DataManage.GetSpecialFunName(nEntry);
		if (pContext != NULL){	
			for (Index =0;Index<10;Index++){
				m_SpecialFun[Index].AddString(pContext);
			}
			nEntry++;
		}
	}while(pContext != NULL);
}

void  CSubStageModuleDlg::FillModuleKeyReleasion(int nOffset)
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
	if (nEntry)	{	mModuleName[nOffset].SetCurSel(0);		OnSelchangeValidModuleName(nOffset);	}
}
void CSubStageModuleDlg::OnCbnSelchangeValidModuleName()
{
	// TODO: Add your control notification handler code here
	UINT nID = GetFocus()->GetDlgCtrlID();
	int nOffset = nID-IDC_VALID_MODULE_NAME;	
//==========================================================================
	if (nOffset > 9)	{ return;	}
	OnSelchangeValidModuleName(nOffset);
}

void CSubStageModuleDlg::SetCfgModuleKey(UINT nOffset)
{
	CUnitKeyConfigDlg *pUnitKeyDlg = new CUnitKeyConfigDlg;
	if (pUnitKeyDlg == NULL)	{	MessageBox("调出配置模块失败");		return;		}
	//=============================================================================================================
	pUnitKeyDlg->SetParamValidFlag(TRUE);
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


void CSubStageModuleDlg::OnSelchangeValidModuleName(int nOffset)
{
	UINT nArgID = IDC_EDIT_ARGUMENT + nOffset;
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
	SetDlgItemInt(nArgID,pCtrlDev->dwArgument);
}



void CSubStageModuleDlg::OnStnDblclickStaticEntry()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(0);
}
void CSubStageModuleDlg::OnStnDblclickStaticEntry1()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(1);
}
void CSubStageModuleDlg::OnStnDblclickStaticEntry2()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(2);
}
void CSubStageModuleDlg::OnStnDblclickStaticEntry3()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(3);
}
void CSubStageModuleDlg::OnStnDblclickStaticEntry4()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(4);
}
void CSubStageModuleDlg::OnStnDblclickStaticEntry5()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(5);
}
void CSubStageModuleDlg::OnStnDblclickStaticEntry6()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(6);
}
void CSubStageModuleDlg::OnStnDblclickStaticEntry7()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(7);
}
void CSubStageModuleDlg::OnStnDblclickStaticEntry8()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(8);
}
void CSubStageModuleDlg::OnStnDblclickStaticEntry9()
{
	// TODO: Add your control notification handler code here
	SetCfgModuleKey(9);
}