// SubOutPutModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TechnicianModule.h"
#include "SubOutPutModuleDlg.h"
// CSubOutPutModuleDlg dialog
#define		MAX_SUB_OUT_PUT_MODULE_NUM		4
const char		*pSubOutputModuleName[32] = {"2路输出","4路输出","8路输出",""};
const USHORT	pSubOutputModuleParam[] = {0x0002,0x0004,0x0008,0x0000};



//======================================================================================================================
IMPLEMENT_DYNAMIC(CSubOutPutModuleDlg, CDialog)

CSubOutPutModuleDlg::CSubOutPutModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubOutPutModuleDlg::IDD, pParent)
{
	pModule = NULL;
}

CSubOutPutModuleDlg::~CSubOutPutModuleDlg()
{
}

void CSubOutPutModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ITEM_ENTRY1, m_ComboEntryName[0]);
	DDX_Control(pDX, IDC_ITEM_ENTRY2, m_ComboEntryName[1]);
	DDX_Control(pDX, IDC_ITEM_ENTRY3, m_ComboEntryName[2]);
	DDX_Control(pDX, IDC_ITEM_ENTRY4, m_ComboEntryName[3]);
	DDX_Control(pDX, IDC_ITEM_ENTRY5, m_ComboEntryName[4]);
	DDX_Control(pDX, IDC_ITEM_ENTRY6, m_ComboEntryName[5]);
	DDX_Control(pDX, IDC_ITEM_ENTRY7, m_ComboEntryName[6]);
	DDX_Control(pDX, IDC_ITEM_ENTRY8, m_ComboEntryName[7]);
}


BEGIN_MESSAGE_MAP(CSubOutPutModuleDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(WM_ENABLE_CTRL_ITEM,&CSubOutPutModuleDlg::Msg_EnableCtrlItem)
	ON_MESSAGE(WM_GET_SUB_MODULE_NAME,&CSubOutPutModuleDlg::Msg_GetSubModuleName)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSubOutPutModuleDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CSubOutPutModuleDlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()


// CSubOutPutModuleDlg message handlers

BOOL CSubOutPutModuleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSubOutPutModuleDlg::PreTranslateMessage(MSG* pMsg)
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

void CSubOutPutModuleDlg::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PreSubclassWindow();
}

void CSubOutPutModuleDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
	if (bShow == TRUE)	{
		SendMessage(WM_ENABLE_CTRL_ITEM,(WPARAM)pModule,nSubNameEntry);
		//InitAllDlgItemCtrl();
	}


}



LRESULT CSubOutPutModuleDlg::Msg_EnableCtrlItem(WPARAM wParam,LPARAM lParam)
{
	PMODULE_ENTRY pModuleEntry = (PMODULE_ENTRY)wParam;
	int iModuleEntry = (int)lParam;
	BYTE nInput = (pSubOutputModuleParam[iModuleEntry] >> 8) & 0x00FF;
	BYTE nOutPut = pSubOutputModuleParam[iModuleEntry]  & 0x00FF;
	
	UINT nBaseStaticID = IDC_STATIC_ENTRY1;
	UINT nBaseItemID = IDC_ITEM_ENTRY1;

	for (int Index = 0;Index < 8;Index++)
	{
		UINT bFlag = SW_HIDE;
		if (Index	<	nOutPut)	{	bFlag = SW_SHOWNORMAL;	}
		((CStatic *)GetDlgItem(nBaseStaticID+Index))->ShowWindow(bFlag);
		((CComboBox *)GetDlgItem(nBaseItemID+Index))->ShowWindow(bFlag);
		if (pModuleEntry)	{	((CComboBox *)GetDlgItem(nBaseItemID+Index))->SetWindowText(pModuleEntry->mKeyUnit[Index].mContent.pName);	}
	}
	return S_OK;
}

LRESULT CSubOutPutModuleDlg::Msg_GetSubModuleName(WPARAM wParam,LPARAM lParam)
{
	int nEntry = (int)lParam;
	PCHAR *pSubName = (PCHAR *)wParam;

	(*pSubName) =  NULL;
	if (nEntry < MAX_SUB_OUT_PUT_MODULE_NUM)	{	(*pSubName) = (PCHAR)pSubOutputModuleName[nEntry];	}
	if (strcmp((*pSubName),"") == 0)	{	(*pSubName) =  NULL;	}

	return S_OK;
}



void  CSubOutPutModuleDlg::InitAllDlgItemCtrl()
{
	int Index = 0;
	BYTE nInput = (pSubOutputModuleParam[nSubNameEntry] >> 8) & 0x00FF;
	BYTE nOutPut = pSubOutputModuleParam[nSubNameEntry]  & 0x00FF;
	for (Index = 0;Index < nOutPut;Index++)
	{
		//SetDlgItemText(m_ComboEntryName[Index].mContent.pName);
		m_ComboEntryName[Index].SetWindowText(pModule->mKeyUnit[Index].mContent.pName);
	}
}


void CSubOutPutModuleDlg::OnBnClickedBtnSave()
{
	int Index = 0;
	CString str;
	if (pModule == NULL)	{	return;	}
	PMODULE_KEY_UNIT	pModuleKey = pModule->mKeyUnit;
	BYTE nOutPut = pSubOutputModuleParam[nSubNameEntry]  & 0x00FF;
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

void CSubOutPutModuleDlg::OnBnClickedBtnClear()
{
	if (pModule == NULL)	{	return;	}
	ZeroMemory(pModule->mKeyUnit,sizeof(MODULE_KEY_UNIT)*MAX_MODULE_KEY_NUMBER);
	// TODO: Add your control notification handler code here
	InitAllDlgItemCtrl();
}

