// SubDeviceCfgMethodDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManufactorCFG.h"
#include "SubDeviceCfgMethodDlg.h"


// CSubDeviceCfgMethodDlg dialog

IMPLEMENT_DYNAMIC(CSubDeviceCfgMethodDlg, CDialog)

CSubDeviceCfgMethodDlg::CSubDeviceCfgMethodDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDeviceCfgMethodDlg::IDD, pParent)
{
	m_FileName = "";
}

CSubDeviceCfgMethodDlg::~CSubDeviceCfgMethodDlg()
{
}

void CSubDeviceCfgMethodDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_COMBO_DEVICE_ENTRY,m_DeviceEntry);
	DDX_Control(pDX,IDC_COMBO_DEVICE_TYPE,m_DeviceType);
	DDX_Control(pDX,IDC_COMBO_DEVICE_LUN,m_DeviceSubNum);
	DDX_Control(pDX,IDC_EDIT_SUB_NAME,m_SubName);
	DDX_Control(pDX,IDC_BTN_ADD,m_AddBtn);
	DDX_Control(pDX,IDC_BTN_MODIFY,m_ModifyBtn);
	DDX_Control(pDX,IDC_BTN_DELETE,m_DeleteBtn);
	DDX_Control(pDX,IDC_DATA_LIST,m_DataList);
	DDX_Control(pDX,IDC_PICTURE,m_Picture);
}


BEGIN_MESSAGE_MAP(CSubDeviceCfgMethodDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_ADD, &CSubDeviceCfgMethodDlg::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CSubDeviceCfgMethodDlg::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CSubDeviceCfgMethodDlg::OnBnClickedBtnDelete)
	ON_STN_CLICKED(IDC_PICTURE, &CSubDeviceCfgMethodDlg::OnStnClickedPicture)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DATA_LIST,&CSubDeviceCfgMethodDlg::OnItemchangedListRoom)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE_TYPE, &CSubDeviceCfgMethodDlg::OnCbnSelchangeComboDeviceType)
END_MESSAGE_MAP()


// CSubDeviceCfgMethodDlg message handlers

BOOL CSubDeviceCfgMethodDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_DeviceType.InsertString(0,"RCU主模块");
	m_DeviceType.InsertString(1,"空调模块");
	m_DeviceType.InsertString(2,"8路继电器模块");
	m_DeviceType.InsertString(3,"4路调光板");
	m_DeviceType.InsertString(4,"2路继电器模块");
	m_DeviceType.InsertString(5,"3路LED调光板");
	m_DeviceType.InsertString(6,"门牌显示模块");
	m_DeviceType.InsertString(7,"RFID插卡取点模块");
	m_DeviceType.InsertString(8,"20按键模块");
	//m_DeviceType.SetCurSel(0);

	// TODO:  Add extra initialization here	
	m_DeviceSubNum.EnableWindow(FALSE);
	m_AddBtn.EnableWindow(FALSE);
	m_ModifyBtn.EnableWindow(FALSE);
	m_DeleteBtn.EnableWindow(FALSE);

	//m_Picture.SetImage("Source\\Face.bmp");
	m_Picture.SetFrameEnable(1,RGB(0,0,255),0,TRUE);

	InitDataList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSubDeviceCfgMethodDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

void CSubDeviceCfgMethodDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CSubDeviceCfgMethodDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}

BOOL CSubDeviceCfgMethodDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

void CSubDeviceCfgMethodDlg::OnBnClickedBtnAdd()
{
	PDEVICE_CFG_METHOD pTempEntry = NULL;
	pTempEntry = new DEVICE_CFG_METHOD;
	ZeroMemory(pTempEntry,sizeof(DEVICE_CFG_METHOD));

	CString str;
	GetDlgItemText(IDC_EDIT_SUB_NAME,str);
	str.TrimLeft();
	str.TrimRight();

	if(str.IsEmpty())
	{
		MessageBox("增加的子路名为空，请重试","警告");
		delete pTempEntry;
		return;
	}
	
	
	// TODO: Add your control notification handler code here
	// 数据操作
	pTempEntry->dwMethodID = m_pRCUEntry->RCUId;
	pTempEntry->bEntry = GetDlgItemInt(IDC_COMBO_DEVICE_ENTRY);
	pTempEntry->bType = m_DeviceType.GetCurSel();
	pTempEntry->bSublun = GetDlgItemInt(IDC_COMBO_DEVICE_LUN);
	CString nameTemp;
	m_SubName.GetWindowText(nameTemp);
	strcpy(pTempEntry->sLun,nameTemp);
	strcpy(pTempEntry->LunView,m_FileName);

	if(CheckRoomExist(pTempEntry) == TRUE)
	{
		MessageBox("配置已存在","警告");
		delete pTempEntry;
		return;
	}

	InsertOneRow(m_DataList.GetItemCount(),pTempEntry);
	InsertDeviceCfgMethodRecord(pTempEntry);
	
}

BOOL CSubDeviceCfgMethodDlg::CheckRoomExist(LPVOID lParam)
{
	PDEVICE_CFG_METHOD m_pCurRoom = (PDEVICE_CFG_METHOD)lParam;
	int ItemNum,Index;
	PDEVICE_CFG_METHOD pTempEntry ;

	ItemNum = m_DataList.GetItemCount();
	for(Index=0;Index<ItemNum;Index++)
	{
		pTempEntry = (PDEVICE_CFG_METHOD)m_DataList.GetItemData(Index);
		if((m_pCurRoom->bEntry == pTempEntry->bEntry) && (m_pCurRoom->bType == pTempEntry->bType) && (m_pCurRoom->bSublun == pTempEntry->bSublun))
			return TRUE;
		
	}
	return FALSE;	
}


void CSubDeviceCfgMethodDlg::OnBnClickedBtnModify()
{
	PDEVICE_CFG_METHOD pTempEntry = NULL;
	pTempEntry = new DEVICE_CFG_METHOD;
	ZeroMemory(pTempEntry,sizeof(DEVICE_CFG_METHOD));

	CString str,temp,oldName,newName;
	int nSelIndex;

	POSITION pos = m_DataList.GetFirstSelectedItemPosition(); //拿到第一个被选择的项目位置；
	while(pos)
	{ 
		nSelIndex = m_DataList.GetNextSelectedItem(pos);//通过前一个位置,拿到下一个位置的项目的索引号;
		str = m_DataList.GetItemText(nSelIndex,1);
		pTempEntry->bEntry = _ttoi(str);

		temp = m_DataList.GetItemText(nSelIndex,2);

		str = m_DataList.GetItemText(nSelIndex,3);
		pTempEntry->bSublun = _ttoi(str);

		oldName = m_DataList.GetItemText(nSelIndex,4);
	}
	// 数据操作
	// TODO: Add your control notification handler code here
	pTempEntry->dwMethodID = m_pRCUEntry->RCUId;
	pTempEntry->bType = m_DeviceType.FindString(0,temp);  // 根据内容获取索引值
	BOOL stateEntry = FALSE;
	if (pTempEntry->bEntry != GetDlgItemInt(IDC_COMBO_DEVICE_ENTRY))
	{
		stateEntry = TRUE;
	}
	
	m_DeviceType.GetWindowText(str);
	BOOL stateType = FALSE;
	if (temp != str)
	{
		stateType = TRUE;
	}

	BOOL stateSubLun = FALSE;
	if (pTempEntry->bSublun != GetDlgItemInt(IDC_COMBO_DEVICE_LUN))
	{
		stateSubLun = TRUE;
	}

	BOOL stateSubName = FALSE;
	
	GetDlgItemText(IDC_EDIT_SUB_NAME,newName);
	if (oldName != newName)
	{
		stateSubName = TRUE;
	}

	CString tempFileName;
	tempFileName = OnModifyPicture();

	BOOL viewStatue = FALSE;
	if (tempFileName != m_FileName)
	{
		viewStatue = TRUE;
	}

	BOOL state = FALSE;
	if(stateEntry || stateSubLun || stateType || stateSubName || viewStatue)
	{
		state = TRUE;
	}
	else
	{
		state = FALSE;
		MessageBox("不需要修改","警告");
		//delete pTempEntry;
		return;
	}
	
	// TODO: Add your control notification handler code here
	pTempEntry->dwMethodID = m_pRCUEntry->RCUId;
	pTempEntry->bEntry = GetDlgItemInt(IDC_COMBO_DEVICE_ENTRY);
	pTempEntry->bType = m_DeviceType.GetCurSel();
	pTempEntry->bSublun = GetDlgItemInt(IDC_COMBO_DEVICE_LUN);
	CString nameTemp;
	m_SubName.GetWindowText(nameTemp);
	strcpy(pTempEntry->sLun,nameTemp);
	strcpy(pTempEntry->LunView,tempFileName);
	ModifyDeviceCfgMethodRecord(pTempEntry,NULL);
	UpdataListRow(nSelIndex,pTempEntry);
	
	//delete pTempEntry;
	//m_ModifyBtn.EnableWindow(FALSE);
}

void CSubDeviceCfgMethodDlg::OnBnClickedBtnDelete()
{
	// TODO: Add your control notification handler code here
	PDEVICE_CFG_METHOD pTempEntry = NULL;
	pTempEntry = new DEVICE_CFG_METHOD;
	ZeroMemory(pTempEntry,sizeof(DEVICE_CFG_METHOD));

	CString str,temp;

	POSITION pos = m_DataList.GetFirstSelectedItemPosition(); //拿到第一个被选择的项目位置；
	while(pos)
	{ 
		int nSelIndex = m_DataList.GetNextSelectedItem(pos);//通过前一个位置,拿到下一个位置的项目的索引号;
		str = m_DataList.GetItemText(nSelIndex,1);
		pTempEntry->bEntry = _ttoi(str);

		temp = m_DataList.GetItemText(nSelIndex,2);
		pTempEntry->bType = m_DeviceType.FindString(0,temp);

		str = m_DataList.GetItemText(nSelIndex,3);
		pTempEntry->bSublun = _ttoi(str);

		str = m_DataList.GetItemText(nSelIndex,4);
		strcpy(pTempEntry->sLun,str);
		m_DataList.DeleteItem(nSelIndex);//删除所选择的那项;
		pos = m_DataList.GetFirstSelectedItemPosition();//因为前面删除了一项,所以list的结构发生了变化,所以得重新再判断第一个位置拿到pos;
	}
	// 数据操作
	// TODO: Add your control notification handler code here
	
	// TODO: Add your control notification handler code here
	pTempEntry->dwMethodID = m_pRCUEntry->RCUId;
	//pTempEntry->bEntry = 3;
	//pTempEntry->bType = 5;
	//pTempEntry->bSublun = 1;
	//strcpy(pTempEntry->sLun,"左床灯");
	strcpy(pTempEntry->LunView,m_FileName);
	DeleteDeviceCfgMethodRecord(pTempEntry,NULL);
	delete pTempEntry;
}

void CSubDeviceCfgMethodDlg::InitDataList()
{
	CRect Rt; 
	DWORD dwStyleEx;
	::GetClientRect(m_DataList.GetSafeHwnd(),&Rt);
	//改变显示模式为报表
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	dwStyleEx = LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES;  //  
	m_DataList.SetExtendedStyle(dwStyleEx);
	////////////////////////////////////////////////////////
	m_DataList.InsertColumn( 0, NULL, LVCFMT_CENTER, 0);//插入列
	m_DataList.InsertColumn( 1, "设备序号", LVCFMT_CENTER, Rt.Width()/4);//插入列
	m_DataList.InsertColumn( 2, "设备类型", LVCFMT_CENTER, Rt.Width()/4 );//插入列
	m_DataList.InsertColumn( 3, "子路号", LVCFMT_CENTER, Rt.Width()/4 );
	m_DataList.InsertColumn( 4, "子路名称", LVCFMT_CENTER, Rt.Width()/4 );
}

void CSubDeviceCfgMethodDlg::SetRelationItem(PVOID pItem)
{
	if(pItem != NULL)
		hItem = (HTREEITEM)pItem;
}

void CSubDeviceCfgMethodDlg::UpdataRCU(PVOID lParam)
{
	//PRCU_TYPE_ENTRY m_pEntryInfo;
	m_pRCUEntry = (PRCU_TYPE_ENTRY)lParam;
	CString str;
	m_DeviceEntry.EnableWindow(FALSE);
	m_DeviceEntry.ResetContent();
	CPtrArray pRecordArray;
	char pExtern[64];
	if(m_pRCUEntry != NULL)
	{
		m_DeviceEntry.EnableWindow(TRUE);
		//SetDlgItemInt(IDC_RCU_RS_NUM,m_pRCUEntry->wStatusPortNum);
		for (int i = 0; i < m_pRCUEntry->wStatusPortNum; i++)
		{
			str.Format("%d", 1 + i);
			m_DeviceEntry.InsertString(i,str);
			m_DeviceEntry.SetCurSel(0);
		}
		CString temp;
		temp.Format("RCUID = %d",m_pRCUEntry->RCUId);
		strcpy(pExtern,temp);
		m_DataList.DeleteAllItems();
		GetDeviceCfgMethodRecord(pRecordArray,pExtern);
		for (int j = 0;j < pRecordArray.GetSize();j++)
		{
			InsertOneRow(j,pRecordArray[j]);
		}
		//m_DeviceType.SetCurSel(0);
		SetDlgItemText(IDC_EDIT_SUB_NAME,NULL);
	}
	else
	{
		m_DeviceSubNum.EnableWindow(FALSE);
	}
	//m_Picture.SetImage("Source\\Pic.jpg");
}

void CSubDeviceCfgMethodDlg::InsertOneRow(int Entry,LPVOID lParam)
{
	PDEVICE_CFG_METHOD	m_pEntryInfo = (PDEVICE_CFG_METHOD)lParam;
	CString str;
	//行第一列为空
	m_DataList.InsertItem(Entry,NULL);

	str.Format("%d",m_pEntryInfo->bEntry);
	m_DataList.SetItemText(Entry,1,str);

	m_DeviceType.GetLBText(m_pEntryInfo->bType,str);
	m_DataList.SetItemText(Entry,2,str);

	str.Format("%d",m_pEntryInfo->bSublun);
	m_DataList.SetItemText(Entry,3,str);

	str.Format("%s",m_pEntryInfo->sLun);
	m_DataList.SetItemText(Entry,4,str);
	//关联结构体
	m_DataList.SetItemData(Entry,(DWORD_PTR)m_pEntryInfo);
}

void CSubDeviceCfgMethodDlg::UpdataListRow(int Entry,LPVOID lParam)
{
	PDEVICE_CFG_METHOD	m_pEntryInfo = (PDEVICE_CFG_METHOD)lParam;
	CString str;

	str.Format("%d",m_pEntryInfo->bEntry);
	m_DataList.SetItemText(Entry,1,str);

	m_DeviceType.GetLBText(m_pEntryInfo->bType,str);
	m_DataList.SetItemText(Entry,2,str);

	str.Format("%d",m_pEntryInfo->bSublun);
	m_DataList.SetItemText(Entry,3,str);

	str.Format("%s",m_pEntryInfo->sLun);
	m_DataList.SetItemText(Entry,4,str);
	//关联结构体
	m_DataList.SetItemData(Entry,(DWORD_PTR)m_pEntryInfo);
}

void CSubDeviceCfgMethodDlg::OnCbnSelchangeComboDeviceType()
{
	int nIndex;
	//CString temp;
	//GetDlgItemText(IDC_COMBO_DEVICE_TYPE,temp);
	//nIndex = m_DeviceType.FindString(0,temp); // 第一个参数为从哪个索引开始寻找
	nIndex = m_DeviceType.GetCurSel();
	if(nIndex == -1)
	{
		return;
	}
	m_DeviceSubNum.ResetContent();
	CString str;

	switch (nIndex)
	{
	case 0:
		m_DeviceSubNum.EnableWindow(FALSE);
		m_AddBtn.EnableWindow(FALSE);
		m_ModifyBtn.EnableWindow(FALSE);
		m_DeleteBtn.EnableWindow(FALSE);
		break;
	case 1:
		m_DeviceSubNum.EnableWindow(FALSE);
		m_AddBtn.EnableWindow(FALSE);
		m_ModifyBtn.EnableWindow(FALSE);
		m_DeleteBtn.EnableWindow(FALSE);
		break;
	case 2:
		m_DeviceSubNum.EnableWindow(TRUE);
		m_AddBtn.EnableWindow(TRUE);
		m_ModifyBtn.EnableWindow(TRUE);
		m_DeleteBtn.EnableWindow(TRUE);
		for (int i = 0;i < 20; i++)
		{
			str.Format("%d", 1 + i);
			m_DeviceSubNum.InsertString(i,str);
		}
		m_DeviceSubNum.SetCurSel(0);
		break;
	case 3:
		m_DeviceSubNum.EnableWindow(TRUE);
		m_AddBtn.EnableWindow(TRUE);
		m_ModifyBtn.EnableWindow(TRUE);
		m_DeleteBtn.EnableWindow(TRUE);
		for (int i = 0;i < 8; i++)
		{
			str.Format("%d", 1 + i);
			m_DeviceSubNum.InsertString(i,str);
		}
		m_DeviceSubNum.SetCurSel(0);
		break;
	case 4:
		m_DeviceSubNum.EnableWindow(TRUE);
		m_AddBtn.EnableWindow(TRUE);
		m_ModifyBtn.EnableWindow(TRUE);
		m_DeleteBtn.EnableWindow(TRUE);
		for (int i = 0;i < 8; i++)
		{
			str.Format("%d", 1 + i);
			m_DeviceSubNum.InsertString(i,str);
		}
		m_DeviceSubNum.SetCurSel(0);
		break;
	case 5:
		m_DeviceSubNum.EnableWindow(TRUE);
		m_AddBtn.EnableWindow(TRUE);
		m_ModifyBtn.EnableWindow(TRUE);
		m_DeleteBtn.EnableWindow(TRUE);
		for (int i = 0;i < 8; i++)
		{
			str.Format("%d", 1 + i);
			m_DeviceSubNum.InsertString(i,str);
		}
		m_DeviceSubNum.SetCurSel(0);
		break;
	case 6:
		m_DeviceSubNum.EnableWindow(FALSE);
		m_AddBtn.EnableWindow(FALSE);
		m_ModifyBtn.EnableWindow(FALSE);
		m_DeleteBtn.EnableWindow(FALSE);
		break;
	case 7:
		m_DeviceSubNum.EnableWindow(FALSE);
		m_AddBtn.EnableWindow(FALSE);
		m_ModifyBtn.EnableWindow(FALSE);
		m_DeleteBtn.EnableWindow(FALSE);
		break;
	case 8:
		m_DeviceSubNum.EnableWindow(FALSE);
		m_AddBtn.EnableWindow(FALSE);
		m_ModifyBtn.EnableWindow(FALSE);
		m_DeleteBtn.EnableWindow(FALSE);
		break;
	default:
		break;
	}
}

void CSubDeviceCfgMethodDlg::OnItemchangedListRoom(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;  // 当前行数
	// TODO: Add your control notification handler code here
	if(pNMListView->iItem == -1)
		return;

	PDEVICE_CFG_METHOD pTempEntry = (PDEVICE_CFG_METHOD)m_DataList.GetItemData(pNMListView->iItem);
	if(pTempEntry == NULL)
		return;

	OnCbnSelchangeComboDeviceType();
	//=========================================================================
	m_DeviceSubNum.EnableWindow(TRUE);
	//SetDlgItemInt(IDC_COMBO_DEVICE_ENTRY,pTempEntry->bEntry);
	m_DeviceEntry.SetCurSel(pTempEntry->bEntry -1);
	m_DeviceType.SetCurSel(pTempEntry->bType);
	SetDlgItemInt(IDC_COMBO_DEVICE_LUN,pTempEntry->bSublun);
	//m_DeviceSubNum.SetCurSel(pTempEntry->bSublun - 1);
	m_SubName.SetWindowText(pTempEntry->sLun);
	//SetDlgItemText(IDC_EDIT_SUB_NAME,pTempEntry->sLun);

	CString	str;
	char Path[MAX_PATH];
	ZeroMemory(Path,MAX_PATH);
	GetCurrentDirectory(MAX_PATH,Path);
	str.Format("%s\\Source\\%s",Path,pTempEntry->LunView);
	m_Picture.SetImage(str);
	m_Picture.SetFrameEnable(1,RGB(0,0,255),0,TRUE);
	//UpdateWindow();
	SetCurrentDirectory(Path);

	
	*pResult = 0;
}


void CSubDeviceCfgMethodDlg::OnStnClickedPicture()
{
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("All Files (*.*)|*.*||"), NULL);
	CString	str;
	char Path[MAX_PATH];
	ZeroMemory(Path,MAX_PATH);
	GetCurrentDirectory(MAX_PATH,Path);

	if (IDOK == dlgFile.DoModal())
	{
		m_FileName = dlgFile.GetFileName();
		str.Format("%s\\Source\\%s",Path,m_FileName);
		m_Picture.SetImage(str);
		m_Picture.SetFrameEnable(1,RGB(0,0,255),0,TRUE);
		
		//Invalidate(TRUE);
		//UpdateWindow();
		//MessageBox(m_FileName);
	}
	SetCurrentDirectory(Path);
}

CString CSubDeviceCfgMethodDlg::OnModifyPicture()
{
	CString temp;
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("All Files (*.*)|*.*||"), NULL);
	CString	str;
	char Path[MAX_PATH];
	ZeroMemory(Path,MAX_PATH);
	GetCurrentDirectory(MAX_PATH,Path);

	if (IDOK == dlgFile.DoModal())
	{
		temp = dlgFile.GetFileName();
		str.Format("%s\\Source\\%s",Path,temp);
		m_Picture.SetImage(str);
		m_Picture.SetFrameEnable(1,RGB(0,0,255),0,TRUE);

		Invalidate(TRUE);
		UpdateWindow();
		//MessageBox(m_FileName);
	}
	SetCurrentDirectory(Path);
	return temp;
}

void CSubDeviceCfgMethodDlg::OnOK()
{

}