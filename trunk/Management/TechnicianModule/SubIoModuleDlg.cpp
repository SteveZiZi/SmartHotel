// SubIoModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TechnicianModule.h"
#include "SubIoModuleDlg.h"
#include "UnitKeyConfigDlg.h"


#define		MAX_SUB_IO_MODULE_NUM		4
const char		*pSubIOModuleName[32] = {"12/8路模块","8/4路模块","4/2路模块",""};
const USHORT	pSubIOModuleParam[] = {0x0C08,0x0804,0x0402,0x0000};
// CSubIoModuleDlg dialog

IMPLEMENT_DYNAMIC(CSubIoModuleDlg, CDialog)

CSubIoModuleDlg::CSubIoModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubIoModuleDlg::IDD, pParent)
{
	pModule = NULL;
}

CSubIoModuleDlg::~CSubIoModuleDlg()
{
}

void CSubIoModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_ITEM, m_KeyItemTree);
	DDX_Control(pDX, IDC_ITEM_ENTRY1, m_ComboEntryName[0]);
	DDX_Control(pDX, IDC_ITEM_ENTRY2, m_ComboEntryName[1]);
	DDX_Control(pDX, IDC_ITEM_ENTRY3, m_ComboEntryName[2]);
	DDX_Control(pDX, IDC_ITEM_ENTRY4, m_ComboEntryName[3]);
	DDX_Control(pDX, IDC_ITEM_ENTRY5, m_ComboEntryName[4]);
	DDX_Control(pDX, IDC_ITEM_ENTRY6, m_ComboEntryName[5]);
	DDX_Control(pDX, IDC_ITEM_ENTRY7, m_ComboEntryName[6]);
	DDX_Control(pDX, IDC_ITEM_ENTRY8, m_ComboEntryName[7]);
}


BEGIN_MESSAGE_MAP(CSubIoModuleDlg, CDialog)
	ON_MESSAGE(WM_ENABLE_CTRL_ITEM,&CSubIoModuleDlg::Msg_EnableCtrlItem)
	ON_MESSAGE(WM_GET_SUB_MODULE_NAME,&CSubIoModuleDlg::Msg_GetSubModuleName)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_ITEM, &CSubIoModuleDlg::OnNMDblclkTreeItem)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSubIoModuleDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CSubIoModuleDlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()


// CSubIoModuleDlg 消息处理程序

BOOL CSubIoModuleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
BOOL CSubIoModuleDlg::PreTranslateMessage(MSG* pMsg)
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
void CSubIoModuleDlg::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PreSubclassWindow();
}
void CSubIoModuleDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
	//if (bShow == TRUE)	{
	//	SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)pModule,nSubNameEntry);
		//InitAllDlgItemCtrl();
	//}


}
LRESULT CSubIoModuleDlg::Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam)
{
	PMODULE_ENTRY pModuleEntry = (PMODULE_ENTRY)wParam;
	int iModuleEntry = (int)lParam;
	BYTE nInput = (pSubIOModuleParam[iModuleEntry] >> 8) & 0x00FF;
	BYTE nOutPut = pSubIOModuleParam[iModuleEntry]  & 0x00FF;
	UINT nBaseItemID = IDC_ITEM_ENTRY1;
	UINT nBaseStaticID = IDC_STATIC_ENTRY1;
	for (int Index = 0;Index < 8;Index++)
	{
		UINT bFlag = SW_HIDE;
		if (Index	<	nOutPut)	{	bFlag = SW_SHOWNORMAL;	}
		((CComboBox *)GetDlgItem(nBaseItemID+Index))->ShowWindow(bFlag);
		((CStatic *)GetDlgItem(nBaseStaticID+Index))->ShowWindow(bFlag);
	}
//===============================================================================================
	InitAllDlgItemCtrl();
	return S_OK;
}
LRESULT CSubIoModuleDlg::Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam)
{
	int nEntry = (int)lParam;
	PCHAR *pSubName = (PCHAR *)wParam;

	(*pSubName) =  NULL;
	if (nEntry < MAX_SUB_IO_MODULE_NUM)	{	(*pSubName) = (PCHAR)pSubIOModuleName[nEntry];	}
	if (strcmp((*pSubName),"") == 0)	{	(*pSubName) =  NULL;	}

	return S_OK;
}

void  CSubIoModuleDlg::FillModuleKeyReleasion(int nOffset,BOOL bFlag)
{
	HTREEITEM hItem = TVI_ROOT;//m_KeyItemTree.GetRootItem();
	if (bFlag == FALSE)	{	hItem = m_KeyItemTree.GetSelectedItem();	}
//===========================================================================================
	if (bFlag == TRUE){
		CString str;
		str.Format("子路【%d】",nOffset+1);
		hItem = m_KeyItemTree.InsertItem(str,hItem,NULL);
		//m_KeyItemTree.SetItemData(hItem,(DWORD_PTR)&(pModule->mKeyUnit[nOffset]));
		m_KeyItemTree.SetItemData(hItem,nOffset);
	}else{
		HTREEITEM hNextItem = m_KeyItemTree.GetNextItem(hItem,TVGN_CHILD);
		if (hNextItem != NULL)	{	CleanSubItem(hNextItem);	}
	}
//================================================================================================
	PMODULE_KEY_UNIT pKey = (PMODULE_KEY_UNIT)(&(pModule->mKeyUnit[nOffset]));
	PCONTROL_DEVICE_UNIT pCtrl = pKey->mContent.mCtrlDeviceList.mCtrlDev;
	CString ssm;
	if (pKey == NULL)	{	return;		}
	for (int Index=0;Index<MAX_CTRL_MODULE_NUMBER;Index++,pCtrl++)
	{
		if (pCtrl->bModuleEntry != 0){
			ssm.Format("模块【%d】，子  路[%d]，特殊功能:%d",pCtrl->bModuleEntry,pCtrl->bSubModuleItem,pCtrl->bSpecialFundef);
			m_KeyItemTree.InsertItem(ssm,hItem);
		}
	}












}


void CSubIoModuleDlg::SetCfgModuleKey(UINT nOffset)
{
	CUnitKeyConfigDlg *pUnitKeyDlg = new CUnitKeyConfigDlg(pModule->bEntry);
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

void CSubIoModuleDlg::InitAllDlgItemCtrl()
{
//树控件
	CString str;
	if (m_KeyItemTree.GetCount())	{	m_KeyItemTree.DeleteAllItems();	}
	BYTE nInput = (pSubIOModuleParam[nSubNameEntry] >> 8) & 0x00FF;

	for (int Index=0;Index<nInput;Index++)
	{
		FillModuleKeyReleasion(Index,TRUE);
	}
//============================================================================================
	BYTE nOutPut = pSubIOModuleParam[nSubNameEntry]  & 0x00FF;
	UINT nBaseItemID = IDC_ITEM_ENTRY1;
	for (int Index=0;Index<nOutPut;Index++)
	{
		if (pModule->mKeyUnit[Index+nInput].mContent.pName[0] != 0){
			SetDlgItemText(nBaseItemID+Index,pModule->mKeyUnit[Index+nInput].mContent.pName);
		}else{
			SetDlgItemText(nBaseItemID+Index,NULL);
		}
	}
}


void CSubIoModuleDlg::CleanSubItem(HTREEITEM hParent)
{
	if (hParent == NULL)	{	return;	}
	HTREEITEM hItem = m_KeyItemTree.GetNextItem(hParent,TVGN_NEXT);
	if (hItem != NULL)	{ CleanSubItem(hItem);	}
	m_KeyItemTree.DeleteItem(hParent);
}
void CSubIoModuleDlg::OnNMDblclkTreeItem(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_KeyItemTree.GetSelectedItem();
	int nOffset = m_KeyItemTree.GetItemData(hItem);
	SetCfgModuleKey(nOffset);

	*pResult = 0;
}

void CSubIoModuleDlg::OnBnClickedBtnSave()
{
	// TODO: Add your control notification handler code here
	int Index = 0;
	CString str;
	if (pModule == NULL)	{	return;	}
	BYTE nInput = (pSubIOModuleParam[nSubNameEntry] >> 8) & 0x00FF;
	PMODULE_KEY_UNIT	pModuleKey = pModule->mKeyUnit+nInput;
	BYTE nOutPut = pSubIOModuleParam[nSubNameEntry]  & 0x00FF;
	// TODO: Add your control notification handler code here
	for (int Index = 0;Index < nOutPut;pModuleKey++,Index++)
	{
		m_ComboEntryName[Index].GetWindowText(str);
		str.TrimLeft();
		str.TrimRight();
		if (str.IsEmpty())	{	
			ZeroMemory(pModuleKey,sizeof(MODULE_KEY_UNIT));
			continue;
		}
		pModuleKey->bEntry = Index+1;
		pModuleKey->bKeyAttribute = ATTRIBUTE_OUTPUT;				//
		strcpy(pModuleKey->mContent.pName,(char *)(LPCSTR)str);
		//m_ComboEntryName[Index].GetWindowText(pModuleKey->mContent.pName,sizeof(CONTROL_DEVICE_UNIT)*MAX_CTRL_MODULE_NUMBER+1);	
	}
}

void CSubIoModuleDlg::OnBnClickedBtnClear()
{
	// TODO: Add your control notification handler code here
	if (pModule == NULL)	{	return;	}
	BYTE nInput = (pSubIOModuleParam[nSubNameEntry] >> 8) & 0x00FF;
	BYTE nOutput = pSubIOModuleParam[nSubNameEntry] & 0x00FF;

	PMODULE_KEY_UNIT pKey = (PMODULE_KEY_UNIT)(pModule->mKeyUnit+nInput);
	ZeroMemory(pKey,sizeof(MODULE_KEY_UNIT)*nOutput);
	// TODO: Add your control notification handler code here
	InitAllDlgItemCtrl();
}
