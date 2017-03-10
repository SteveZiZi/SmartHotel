// TechnicianDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TechnicianModule.h"
#include "TechnicianDlg.h"
//=================================================
#include "AddRoomDlg.h"
#include "UnitSettingDlg.h"








#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTechnicianDlg dialog


CTechnicianDlg::CTechnicianDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTechnicianDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTechnicianDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pModuleStage = NULL;
	bFirstTimeFlag = TRUE;
}


void CTechnicianDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTechnicianDlg)
	DDX_Control(pDX, IDC_TREE_ROOMNAME, m_RoomTree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTechnicianDlg, CDialog)
	//{{AFX_MSG_MAP(CTechnicianDlg)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_ADD_RT, OnBtnAddRt)
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_ROOMNAME, OnSelchangedTreeRoomname)
	ON_BN_CLICKED(IDC_SETTING, OnSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTechnicianDlg message handlers

BOOL CTechnicianDlg::PreTranslateMessage(MSG* pMsg) 
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

BOOL CTechnicianDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if (pModuleStage == NULL)	{	pModuleStage = new CModuleCfgDlg;	
		pModuleStage->Create(IDD_MODULE_CFG_DIALOG,GetDlgItem(IDC_CUSTOM));
	}
	pModuleStage->ShowWindow(SW_HIDE);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CTechnicianDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CTechnicianDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	// TODO: Add your message handler code here
	if (pModuleStage != NULL)	{	delete pModuleStage;	pModuleStage = NULL;	}
}

void CTechnicianDlg::OnBtnAddRt() 
{
	int Rest = IDCANCEL;
	PROOM	pRoom = NULL;
	// TODO: Add your control notification handler code here
	CAddRoomDlg *pAddDlg = new CAddRoomDlg;
	Rest = pAddDlg->DoModal();
//==================================================================
	if (Rest == IDOK)	{
		pRoom = new ROOM;
		ZeroMemory(pRoom,sizeof(ROOM));
		//==================================================
		strcpy((PCHAR)(pRoom->sRoomName),pAddDlg->m_RoomName);
		pRoom->ulConnectType = pAddDlg->nMethod;
		
		pRoom->hItem = hFindRoomPos((PCHAR)(pRoom->sRoomName));
		if (pRoom->hItem == NULL){
			pRoom->hItem = m_RoomTree.InsertItem((PCHAR)(pRoom->sRoomName),0,0);
			m_RoomTree.SetItemData(pRoom->hItem,(DWORD)pRoom);
		}else{
			MessageBox("客房已经存在,请重试");
			delete pRoom;
		}
	}
}

void CTechnicianDlg::OnImport() 
{
	// TODO: Add your control notification handler code here
	CString sFileName;
	BOOL Result = FALSE;
	///////////////////////////////////////////////////////////////////////////
	char CurrentPath[MAX_PATH];
	memset(CurrentPath,'\0',MAX_PATH);
	GetCurrentDirectory(MAX_PATH,CurrentPath);
	////////////////////////////////////////////////////////////////////////////////////////////////	
	int status;
	//CString ScriptFileName,str,temp;
	//CStdioFile m_file;
	CFileDialog hFileDlg(TRUE,NULL,NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_READONLY,
		TEXT("配置文件 (*.dat)|*.dat;|所有文件(*.*)|*.*||"),NULL);
	hFileDlg.m_ofn.nFilterIndex=1;
	hFileDlg.m_ofn.hwndOwner=m_hWnd;
	hFileDlg.m_ofn.lStructSize=sizeof(OPENFILENAME);
	hFileDlg.m_ofn.lpstrTitle=TEXT("选择配置文件...\0");
	hFileDlg.m_ofn.nMaxFile=MAX_PATH;
	status = hFileDlg.DoModal();
	if(status == IDCANCEL)	{	return;	}
//得到并显示文件名
	sFileName.Empty();
	sFileName = hFileDlg.GetPathName();		
	SetCurrentDirectory(CurrentPath);	
	if(sFileName.IsEmpty())
		return;
//==========================================================================================================
	PROOM pRoomUnit = new ROOM;
	ZeroMemory(pRoomUnit,sizeof(ROOM));
	HANDLE m_File = INVALID_HANDLE_VALUE;
	DWORD nBytes;
	m_File = CreateFile(sFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
	if(m_File == NULL)	
	{	
		MessageBox("配置文件错误");
		delete pRoomUnit;		
		return;		
	}
	//Buf = reinterpret_cast<BYTE *>(tempRoom);
	//nBytes = sizeof(ROOM);
	ReadFile(m_File,(PBYTE)pRoomUnit,sizeof(ROOM),&nBytes,NULL);
	CloseHandle(m_File);
//===========================================================================================================
	pRoomUnit->hItem = hFindRoomPos((PCHAR)(pRoomUnit->sRoomName));
	if (pRoomUnit->hItem == NULL){
		pRoomUnit->hItem = m_RoomTree.InsertItem((PCHAR)(pRoomUnit->sRoomName),0,0);
		m_RoomTree.SetItemData(pRoomUnit->hItem,(DWORD)pRoomUnit);
	}else{
		MessageBox("客房已经存在,请重试");
		delete pRoomUnit;
	}
}

void CTechnicianDlg::OnExport() 
{
	// TODO: Add your control notification handler code here
	//CString str,FullName,sName;
	HTREEITEM hItem = m_RoomTree.GetSelectedItem();
	if (hItem == NULL)	{	MessageBox("请选择一个房型");		return ;	}
	SaveTreeItem(hItem);
	//MessageBox("保存成功");
	//STEP 1:设置文件夹名称
#if 0
	CSetExportFolderDlg* m_pFolderName;
	m_pFolderName = new CSetExportFolderDlg();

	Result = m_pFolderName->DoModal();
	m_pFolderName->GetFolderName(sName);

	delete[] (CSetExportFolderDlg*)m_pFolderName;
	if(Result == IDCANCEL)
		return;

	//STEP 2:构建全路径
	FullName.Format("%s\\%s\\%s",RunDirectory,ExportFolderName,sName);   
	//STEP 3:从树控件中导出所有的房型
	HTREEITEM hTree;
	PROOM_CONFIG_INFO  tempRoom;

	//PROOMTYPE tempRoom;
	HANDLE m_File;
	PBYTE Buf;
	DWORD nBytes;

	hTree = m_RoomName.GetRootItem();
	while(hTree)  //遍历树控件
	{
		tempRoom = (PROOM_CONFIG_INFO)m_RoomName.GetItemData(hTree);
		//============================================================
		str.Format("%s\\%s",FullName,(PCHAR)tempRoom->sRoonCfgName);
		m_File = CreateFile(str,GENERIC_WRITE,FILE_SHARE_READ |FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,0,NULL);     
		Buf = reinterpret_cast<BYTE *>(tempRoom);
		nBytes = sizeof(ROOM_CONFIG_INFO);
		WriteFile(m_File,Buf,nBytes,&nBytes,NULL);
		CloseHandle(m_File);
		//============================================================
		hTree = m_RoomName.GetNextItem(hTree,TVGN_NEXT);   //往下移
	}
#endif
	
}

void CTechnicianDlg::OnSelchangedTreeRoomname(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	//HTREEITEM hCurrentItem = pNMTreeView->itemNew.hItem;		//得到当前选中的树对象
	PROOM	m_pRoom = (PROOM)(pNMTreeView->itemNew.lParam);
	if (m_pRoom == NULL)	{	return;	}
//================================================================================================	
	if (bFirstTimeFlag == TRUE){
		pModuleStage->ShowWindow(SW_SHOWNORMAL);
		bFirstTimeFlag = FALSE;
	}
	
	m_DataManage.SetRoomContainer(m_pRoom);				//设置配置信息为全局状态
	pModuleStage->PostMessage(WM_UPDATE_SELECT_CFG,1,(LPARAM)m_pRoom);
//================================================================================================
	*pResult = 0;
}

void CTechnicianDlg::OnSetting() 
{
	// TODO: Add your control notification handler code here
//	HTREEITEM hTempItem;
//	hTempItem = m_RoomName.GetSelectedItem();
//	if(hTempItem == NULL)	{	MessageBox("没有选中配置项");	return;	}
	if (m_DataManage.pRoomUnit == NULL)		{		MessageBox("没有选中配置项");	return;		}
	//弹出对话框
	int Result = IDCANCEL;
	CUnitSettingDlg	*m_pSettingDlg;
	m_pSettingDlg = new CUnitSettingDlg();
	if(m_pSettingDlg != NULL)	{	Result = m_pSettingDlg->DoModal();	}
	if(m_pSettingDlg != NULL)	{	delete m_pSettingDlg;		m_pSettingDlg = NULL;	}
}


HTREEITEM CTechnicianDlg::hFindRoomPos(PCHAR pRoomName)
{
	HTREEITEM hItem = NULL;
	PROOM	pRoom = NULL;
//============================================================
	if (m_RoomTree.GetCount())
	{
		CString str;
		hItem = m_RoomTree.GetRootItem();
		while (hItem)
		{
			str = m_RoomTree.GetItemText(hItem);
			if (strcmp(pRoomName,(LPSTR)(LPCSTR)str) == 0){
				break;
			}
			hItem = m_RoomTree.GetNextItem(hItem,TVGN_NEXT);
		}
	}
	return hItem;
}

void CTechnicianDlg::SaveTreeItem(HTREEITEM hItem)
{
	PROOM	pRoom = NULL;
	CString sName,str;
	char pFullName[MAX_PATH];
	ZeroMemory(pFullName,MAX_PATH);
	GetCurrentDirectory(MAX_PATH,pFullName);
	str.Format("%s\\OperatorCFG\\%s.dat",pFullName,sName);
	pRoom = (PROOM)m_RoomTree.GetItemData(hItem);
	sName = m_RoomTree.GetItemText(hItem);

	if (pRoom == NULL){	MessageBox("房型保存失败，内容为空");	return ;	}
	
//***************************************************************************************************
	HANDLE m_File = INVALID_HANDLE_VALUE;
	DWORD nBytes;
	m_File = CreateFile(str,GENERIC_WRITE,FILE_SHARE_READ |FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,0,NULL);
	if(m_File == NULL)	{	MessageBox("存储路径错误");		return;		}
	//Buf = reinterpret_cast<BYTE *>(tempRoom);
	//nBytes = sizeof(ROOM);
	WriteFile(m_File,(PBYTE)pRoom,sizeof(ROOM),&nBytes,NULL);
	CloseHandle(m_File);
}

