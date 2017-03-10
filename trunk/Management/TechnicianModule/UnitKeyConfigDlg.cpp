// UnitKeyConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "technicianmodule.h"
#include "UnitKeyConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnitKeyConfigDlg dialog


CUnitKeyConfigDlg::CUnitKeyConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitKeyConfigDlg::IDD, pParent),mAdditionalParam(0)
{

	bParamFlag = FALSE;
	pKeyUnit = NULL;

	//{{AFX_DATA_INIT(CUnitKeyConfigDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CUnitKeyConfigDlg::CUnitKeyConfigDlg(int nEntry,CWnd* pParent)
: CDialog(CUnitKeyConfigDlg::IDD, pParent),mAdditionalParam(0)
{
	bParamFlag = FALSE;
	pKeyUnit = NULL;
	m_Entry = nEntry;
}


void CUnitKeyConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnitKeyConfigDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO_SPECIAL_FUNCTION, m_ComboSpecialFun);
	DDX_Control(pDX, IDC_VALID_MODULE_NAME, m_ComboModuleName);
	DDX_Control(pDX, IDC_VALID_SUB_KEY, m_ComboSubKey);
	DDX_Control(pDX, IDC_RELEASION_LIST, m_ReleasionList);
	DDX_Text(pDX, IDC_ADDITIONAL_PARAM, mAdditionalParam);
}


BEGIN_MESSAGE_MAP(CUnitKeyConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CUnitKeyConfigDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_CMD_CLEAN,&CUnitKeyConfigDlg::OnCmdCleanAll)
	ON_COMMAND(ID_CMD_ADD,&CUnitKeyConfigDlg::OnCmdAddReleasion)
	ON_COMMAND(ID_CMD_MODIFY,&CUnitKeyConfigDlg::OnCmdModifyReleasion)
	ON_COMMAND(ID_CMD_DELETE,&CUnitKeyConfigDlg::OnCmdDeleteReleasion)
	ON_BN_CLICKED(IDOK, &CUnitKeyConfigDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUnitKeyConfigDlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_VALID_MODULE_NAME, &CUnitKeyConfigDlg::OnCbnSelchangeValidModuleName)
	ON_NOTIFY(NM_RCLICK, IDC_RELEASION_LIST, &CUnitKeyConfigDlg::OnNMRclickReleasionList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_RELEASION_LIST, &CUnitKeyConfigDlg::OnLvnItemchangedReleasionList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnitKeyConfigDlg message handlers

BOOL CUnitKeyConfigDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		//屏掉回车和退出键
		if (pMsg->wParam == VK_RETURN)	{	OnBnClickedOk();		return TRUE;	}
		if (pMsg->wParam == VK_ESCAPE)  {	OnBnClickedCancel();	return TRUE;	}
			

		if(pMsg->wParam == VK_UP  || pMsg->wParam == VK_DOWN)
			return TRUE;

		if(pMsg->wParam == VK_LEFT  || pMsg->wParam == VK_RIGHT)
			return TRUE;

	}	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CUnitKeyConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitListCtrlStyle();
	InitListMenu();
	InitSpecialFunCombo();
// TODO:  Add extra initialization here
	FillModuleCtrl();
	FillListCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CUnitKeyConfigDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

void CUnitKeyConfigDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}

void CUnitKeyConfigDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (pKeyUnit == NULL)	{	MessageBox("对象空");		OnCancel();		}
	OnOK();
}

void CUnitKeyConfigDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}




void CUnitKeyConfigDlg::InitSpecialFunCombo()
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


void CUnitKeyConfigDlg::InitListCtrlStyle()
{
	int Index = 0;
	DWORD dwStyle = m_ReleasionList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
	//m_ModuleList.ModifyStyle(0,dwStyle);
	m_ReleasionList.SetExtendedStyle(dwStyle);
	//====================================================================================
	CRect rt;
	::GetClientRect(GetDlgItem(IDC_RELEASION_LIST)->GetSafeHwnd(),&rt);
	int nWidth = bParamFlag ?(rt.Width()/4):(rt.Width()/3);


	m_ReleasionList.InsertColumn(Index++,"",LVCFMT_CENTER,0);
	//m_ReleasionList.InsertColumn(Index++,"索引",LVCFMT_CENTER,60);
	m_ReleasionList.InsertColumn(Index++,"模块名称",LVCFMT_CENTER,nWidth);
	m_ReleasionList.InsertColumn(Index++,"子路索引",LVCFMT_CENTER,nWidth);
	m_ReleasionList.InsertColumn(Index++,"特殊功能",LVCFMT_CENTER,nWidth);

	
	if (bParamFlag == TRUE)	{	m_ReleasionList.InsertColumn(Index++,"子路参数",LVCFMT_CENTER,nWidth);	}
	else {	((CEdit *)GetDlgItem(IDC_ADDITIONAL_PARAM))->EnableWindow(FALSE);	}
}


void CUnitKeyConfigDlg::InitListMenu()
{
	mRmenu.CreatePopupMenu();
	mRmenu.AppendMenu(MF_STRING,ID_CMD_CLEAN,"清空关联项");
	mRmenu.AppendMenu(MF_SEPARATOR);

	mRmenu.AppendMenu(MF_STRING,ID_CMD_ADD,"增加关联项");
	mRmenu.AppendMenu(MF_STRING,ID_CMD_MODIFY,"修改关联项");
	mRmenu.AppendMenu(MF_STRING,ID_CMD_DELETE,"删除关联项");

}


BOOL CUnitKeyConfigDlg::InsertOneRow(LPVOID lParam,BOOL bFlag)
{
	CString str;
	PCHAR pSubName = NULL;

	if (lParam == NULL)		{	return FALSE;	}
	if (m_DataManage.pRoomUnit == NULL)		{	return FALSE;	}
//==================================================================================
	PCONTROL_DEVICE_UNIT pCtrlUnit = (PCONTROL_DEVICE_UNIT)lParam;
	int nEntry = -1;
	if (bFlag == FALSE){	nEntry = SearchExistCtrlDevice(pCtrlUnit->bModuleEntry,pCtrlUnit->bSubModuleItem);	}
	if (nEntry == -1)	{	nEntry = m_ReleasionList.GetItemCount();	}
	else {	return TRUE;	}
	
	m_ReleasionList.InsertItem(nEntry,NULL);
	
	pSubName = m_DataManage.GetSubModuleName(pCtrlUnit->bModuleEntry-1);
	m_ReleasionList.SetItemText(nEntry,1,pSubName);


	str.Format("子路号%d",pCtrlUnit->bSubModuleItem);
	m_ReleasionList.SetItemText(nEntry,2,str);

		
	m_ReleasionList.SetItemText(nEntry,3,m_DataManage.GetSpecialFunName(pCtrlUnit->bSpecialFundef));
	if (bParamFlag == TRUE){
		str.Format("%ld",pCtrlUnit->dwArgument);
		m_ReleasionList.SetItemText(nEntry,4,str);
	}



	m_ReleasionList.SetItemData(nEntry,(DWORD_PTR)pCtrlUnit);
	return TRUE;
}


int CUnitKeyConfigDlg::SearchExistCtrlDevice(UINT nModule,UINT nSubItem)
{
	int nEntry = -1;
	PCONTROL_DEVICE_UNIT pCtrlUnit = NULL;
	int nRowCnt = m_ReleasionList.GetItemCount();
	for (nEntry=0;nEntry<nRowCnt;nEntry++)
	{
		pCtrlUnit = (PCONTROL_DEVICE_UNIT)m_ReleasionList.GetItemData(nEntry);
		if (pCtrlUnit == NULL)	{	break;	}
		if ((pCtrlUnit->bModuleEntry == nModule) && (pCtrlUnit->bSubModuleItem == nSubItem))	{	break;	}
		else {	pCtrlUnit = NULL;	}
	}
//**************************************************************************************************************	
	if (pCtrlUnit == NULL)	{	nEntry = -1;	}
	return nEntry;
}



void CUnitKeyConfigDlg::FillListCtrl()
{
	PCONTROL_DEVICE_UNIT pCtrlDev = NULL;
	if (pKeyUnit == NULL)	{	return;		}
//==================================================================================================
	pCtrlDev = pKeyUnit->mContent.mCtrlDeviceList.mCtrlDev;
	int Index = 0;
	while (Index < MAX_CTRL_MODULE_NUMBER)
	{
		if (pCtrlDev->bModuleEntry == 0){
			Index++;
			pCtrlDev++;
			continue;
		}
		//==========================================================================================
		InsertOneRow(pCtrlDev,TRUE);
		Index++;
		pCtrlDev++;
	}
}

void CUnitKeyConfigDlg::FillModuleCtrl()
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
			m_ComboModuleName.InsertString(nEntry,str);
			m_ComboModuleName.SetItemData(nEntry,(DWORD_PTR)(&(m_DataManage.pRoomUnit->mModuleEntry[Index])));
			nEntry++;
		}
	}

	if (nEntry)	{	m_ComboModuleName.SetCurSel(m_Entry - 1);	}
	OnCbnSelchangeValidModuleName();
}


void CUnitKeyConfigDlg::OnCbnSelchangeValidModuleName()
{
	// TODO: Add your control notification handler code here
	int nModuleEntry = m_ComboModuleName.GetCurSel();
	if (m_ComboSubKey.GetCount())	{	m_ComboSubKey.ResetContent();	}
	if (nModuleEntry == -1)		{	return ;	}
	PMODULE_ENTRY  pModule =  (PMODULE_ENTRY)m_ComboModuleName.GetItemData(nModuleEntry);
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
			int nEntry = m_ComboSubKey.AddString(pName);
			m_ComboSubKey.SetItemData(nEntry,Index+1);
		}
		Index++;
		pModuleKey++;
	}
//==============================================================================================================
	if (m_ComboSubKey.GetCount())	{	m_ComboSubKey.SetCurSel(0);	}
}



void CUnitKeyConfigDlg::UpDateListRowContext(int nRow,LPVOID lParam)
{
	CString str;
	PCHAR pSubName = NULL;

	if (lParam == NULL)		{	return ;	}
	if (m_DataManage.pRoomUnit == NULL)		{	return ;	}
	//==================================================================================
	PCONTROL_DEVICE_UNIT pCtrlUnit = (PCONTROL_DEVICE_UNIT)lParam;

	pSubName = m_DataManage.GetSubModuleName(pCtrlUnit->bModuleEntry-1);
	m_ReleasionList.SetItemText(nRow,1,pSubName);

	str.Format("子路号%d",pCtrlUnit->bSubModuleItem);
	m_ReleasionList.SetItemText(nRow,2,str);

	m_ReleasionList.SetItemText(nRow,3,m_DataManage.GetSpecialFunName(pCtrlUnit->bSpecialFundef));
	if (bParamFlag == TRUE){
		str.Format("%ld",pCtrlUnit->dwArgument);
		m_ReleasionList.SetItemText(nRow,4,str);
	}
}



void CUnitKeyConfigDlg::OnNMRclickReleasionList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CPoint pt;
	GetCursorPos(&pt);
	mRmenu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,pt.x,pt.y,this);
	*pResult = 0;
}


void CUnitKeyConfigDlg::OnCmdCleanAll()
{
	if (pKeyUnit == NULL)	{		MessageBox("键位不能为空");		return;		}
//=========================================================================================
	if (m_ReleasionList.GetItemCount())		{	m_ReleasionList.DeleteAllItems();	}
	ZeroMemory(&(pKeyUnit->mContent.mCtrlDeviceList),sizeof(CTRL_DEVICE_LIST));

}

void CUnitKeyConfigDlg::OnCmdAddReleasion()
{
	UpdateData();
//==============================================================================================
	int nEntry = 0;
	nEntry = m_ComboModuleName.GetCurSel();
	if (nEntry == -1)	{	MessageBox("模块类型为空");		return;	}
	PMODULE_ENTRY  pModule = (PMODULE_ENTRY)m_ComboModuleName.GetItemData(nEntry);
	nEntry = m_ComboSubKey.GetCurSel();
	if (nEntry == -1)	{	MessageBox("模块子路为空");		return;	}
//==============================================================================================
	int nModuleEntry = pModule->bEntry;
	int nKeyEntry = m_ComboSubKey.GetItemData(nEntry);
	PCONTROL_DEVICE_UNIT pCtrlDev = GetEmptyCtrlDeviceUnit(nModuleEntry,nKeyEntry);
	//==========================================================================================
	//CString	str;
	//str.Format("M[%d][%d]	%d,%d",nModuleEntry,nKeyEntry,m_ComboSpecialFun.GetCurSel(),mAdditionalParam);
	//if (pCtrlDev == NULL)	{	MessageBox(str);		return;		}
	if (pCtrlDev == NULL)	{	MessageBox("关联项已存在");		return;		}

	ZeroMemory(pCtrlDev,sizeof(CONTROL_DEVICE_UNIT));
	pCtrlDev->bModuleEntry = nModuleEntry;			//模块索引号
	pCtrlDev->bSubModuleItem = nKeyEntry;			//子路索引

	pCtrlDev->bSpecialFundef = m_ComboSpecialFun.GetCurSel();
	pCtrlDev->dwArgument = mAdditionalParam;
//===============================================================================================
	InsertOneRow(pCtrlDev);

	pKeyUnit->mContent.mCtrlDeviceList.bNumber++;
}

void CUnitKeyConfigDlg::OnCmdModifyReleasion()
{
	POSITION pos = m_ReleasionList.GetFirstSelectedItemPosition();
	int iEntry = m_ReleasionList.GetNextSelectedItem(pos);
	if (iEntry == -1)	{	return;	}
	PCONTROL_DEVICE_UNIT pCtrlDevUnit = (PCONTROL_DEVICE_UNIT)m_ReleasionList.GetItemData(iEntry);

	UpdateData();
	int nEntry = 0;
	nEntry = m_ComboModuleName.GetCurSel();
	if (nEntry == -1)	{	MessageBox("模块类型为空");		return;	}
	PMODULE_ENTRY  pModule = (PMODULE_ENTRY)m_ComboModuleName.GetItemData(nEntry);
	nEntry = m_ComboSubKey.GetCurSel();
	if (nEntry == -1)	{	MessageBox("模块子路为空");		return;	}
	//==============================================================================================
	int nModuleEntry = pModule->bEntry;
	int nKeyEntry = m_ComboSubKey.GetItemData(nEntry);
	PCONTROL_DEVICE_UNIT pCtrlDev = GetEmptyCtrlDeviceUnit(nModuleEntry,nKeyEntry,FALSE);
	if ((pCtrlDevUnit != NULL) && (pCtrlDev != pCtrlDevUnit))	{	MessageBox("关联项存在，请不要重新关联");	return;		}
	

	ZeroMemory(pCtrlDevUnit,sizeof(CONTROL_DEVICE_UNIT));
	pCtrlDevUnit->bModuleEntry = nModuleEntry;			//模块索引号
	pCtrlDevUnit->bSubModuleItem = nKeyEntry;			//子路索引

	pCtrlDevUnit->bSpecialFundef = m_ComboSpecialFun.GetCurSel();
	pCtrlDevUnit->dwArgument = mAdditionalParam;
	//===============================================================================================
	UpDateListRowContext(iEntry,pCtrlDevUnit);
}

void CUnitKeyConfigDlg::OnCmdDeleteReleasion()
{
	int iEntry = -1;
	PCONTROL_DEVICE_UNIT pCtrlDevUnit = NULL;
	POSITION pos = m_ReleasionList.GetFirstSelectedItemPosition();
	if (pos == NULL){	return;	}		//没有点选中时直接返回
	else
	{
		while (pos)
		{
			iEntry = m_ReleasionList.GetNextSelectedItem(pos);
			//保存当前的iEntry
			pCtrlDevUnit = (PCONTROL_DEVICE_UNIT)m_ReleasionList.GetItemData(iEntry);
			ZeroMemory(pCtrlDevUnit,sizeof(CONTROL_DEVICE_UNIT));
			m_ReleasionList.DeleteItem(iEntry);
			pKeyUnit->mContent.mCtrlDeviceList.bNumber--;
		}
	}
}



PCONTROL_DEVICE_UNIT CUnitKeyConfigDlg::GetEmptyCtrlDeviceUnit(int nModuleEntry,int nKeyEntry,BOOL bFlag)
{
	if (pKeyUnit == NULL)	{	MessageBox("键位空");		return NULL;	}
	PCONTROL_DEVICE_UNIT pCtrlDevUnit = pKeyUnit->mContent.mCtrlDeviceList.mCtrlDev;
	PCONTROL_DEVICE_UNIT pEmptyUnit = NULL;

	int Index = 0;
	for (Index =0;Index < MAX_CTRL_MODULE_NUMBER;Index++)
	{
		if (pCtrlDevUnit->bModuleEntry == 0)	{		pEmptyUnit = pCtrlDevUnit;		break;}
		else {	
			if ((pCtrlDevUnit->bModuleEntry == nModuleEntry) && (pCtrlDevUnit->bSubModuleItem == nKeyEntry)){
				pEmptyUnit = NULL;
				break;
			}
		}
		pCtrlDevUnit++;
	}
//=================================================================================================================
	if (Index >= MAX_CTRL_MODULE_NUMBER)	{	pCtrlDevUnit = NULL;	}

	if (bFlag == TRUE)	{		return pEmptyUnit;	}
	else {	return pCtrlDevUnit;	}
}
void CUnitKeyConfigDlg::OnLvnItemchangedReleasionList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
	// TODO: Add your control notification handler code here
	if ((pNMLV->uNewState) && (pNMLV->uOldState == 0)){
		PCONTROL_DEVICE_UNIT pCtrlDevUnit = (PCONTROL_DEVICE_UNIT)(pNMLV->lParam);
		if (pCtrlDevUnit == NULL)	{	return;	}	
		//=====================================================================================
		m_ComboModuleName.SetCurSel(pCtrlDevUnit->bModuleEntry-1);
		OnCbnSelchangeValidModuleName();
		for (int Index = 0;Index<m_ComboSubKey.GetCount();Index++)
		{
			if (m_ComboSubKey.GetItemData(Index) == pCtrlDevUnit->bSubModuleItem){
				m_ComboSubKey.SetCurSel(Index);
				break;
			}
		}
		//=====================================================================================
		m_ComboSpecialFun.SetCurSel(pCtrlDevUnit->bSpecialFundef);
		if (bParamFlag == TRUE)	{	SetDlgItemInt(IDC_ADDITIONAL_PARAM,pCtrlDevUnit->dwArgument);	}
	}
}

