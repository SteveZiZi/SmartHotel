// DeviceInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomDetailModule.h"
#include "DeviceInfoDlg.h"
#include <Winsock2.h>

// CDeviceInfoDlg dialog

IMPLEMENT_DYNAMIC(CDeviceInfoDlg, CDialog)

CDeviceInfoDlg::CDeviceInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceInfoDlg::IDD, pParent)
{

}

CDeviceInfoDlg::~CDeviceInfoDlg()
{
}

void CDeviceInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_DEVICE_LIST,m_DeviceList);
}


BEGIN_MESSAGE_MAP(CDeviceInfoDlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK,IDC_DEVICE_LIST,&CDeviceInfoDlg::OnNMClickListDevicedata)
	ON_CBN_KILLFOCUS(IDC_DEVICE_LIST, &CDeviceInfoDlg::OnKillfocusCcomboBox)
	ON_BN_CLICKED(IDC_BTN_SET, &CDeviceInfoDlg::OnBnClickedBtnSet)
	ON_BN_CLICKED(IDC_BUT_GET, &CDeviceInfoDlg::OnBnClickedButGet)
END_MESSAGE_MAP()


// CDeviceInfoDlg message handlers

BOOL CDeviceInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	InitDataList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDeviceInfoDlg::InitDeviceInfo()
{
	DWORD nBytes,nRevLength;
	DWORD IpAddress;
	PBYTE pBuf = NULL;
	DWORD dwRtua = 10550;
	WORD  wMstaAndSeq = 0x005E;
	PRCU_ARG_GET_REQ_PACK_0202 pPack = NULL;
	pPack = new RCU_ARG_GET_REQ_PACK_0202;
	memset(pPack,0,sizeof(RCU_ARG_GET_REQ_PACK_0202));

	nRevLength = 256;
	pBuf = new BYTE[nRevLength];
	memset(pBuf,0,nRevLength);
	PROOM_DETAIL_ENTRY m_pRoomEntry = lpRoomDetail;
	// TODO: Add your control notification handler code here
	if((pPack == NULL) || (m_pRoomEntry == NULL))
	{
		delete pPack;
		delete[] pBuf;
		return;
	}
	nBytes = GetRCUargPacket0202(pPack);
	//RTUA
	pPack->dwRtua = DWORD2_BCD(dwRtua);
	pPack->wMstaAndSeq = 0x005E;
	//========================================================================			
	pPack->sPostFrame.bCS = Crc8((PBYTE)pPack,nBytes-1);
	//====================================================================
	IpAddress = inet_addr(m_pRoomEntry->sIpAddress);
	IpAddress = ToLittleEndian(IpAddress);

	nRevLength = SendDataWithResponse((PBYTE)pPack,nBytes,\
		pBuf,nRevLength,\
		IpAddress,m_pRoomEntry->dwPort);
	//=======================================================
	//UpdataAirNum(pBuf);
	UpdataList(pBuf);

	delete pPack;
	delete[] pBuf;
}

void CDeviceInfoDlg::UpdataList(PVOID lParam)
{
	PRCU_ARG_GET_RES_PACK_0202 pPack = reinterpret_cast<PRCU_ARG_GET_RES_PACK_0202>(lParam);
	int deviceNum,subNum,deviceType;
	CString str,temp;
	for(int count = 0;count < m_DeviceList.GetItemCount();count++)
	{
		str = m_DeviceList.GetItemText(count,1);
		deviceNum = _ttoi(str);
		str = m_DeviceList.GetItemText(count,3);
		subNum = _ttoi(str);
		for (int i = 0;i < 150;i = i + 10)
		{
			if (deviceNum == pPack->bContent[i])
			{
				deviceType = pPack->bContent[i+1];
				switch(deviceType)
				{
				case RELAY_EIGHT:
					if (pPack->bContent[i + 2 + subNum/8] & (0x01<<(subNum % 8)))
					{
						temp = "开";
						m_DeviceList.SetItemText(count,4,temp);
					}
					else
					{
						temp = "关";
						m_DeviceList.SetItemText(count,4,temp);
					}
					break;
				case LIGHT_FOUR:
					if (0 == pPack->bContent[subNum - 3 + i])
					{
						temp = "关";
						m_DeviceList.SetItemText(count,4,temp);
					}
					else
					{
						temp = "开";
						m_DeviceList.SetItemText(count,4,temp);
					}
					break;
				case RELAY_TWO:
					if (pPack->bContent[i + 2 + subNum/8] & (0x01<<(subNum % 8)))
					{
						temp = "开";
						m_DeviceList.SetItemText(count,4,temp);
					}
					else
					{
						temp = "关";
						m_DeviceList.SetItemText(count,4,temp);
					}
					break;
				case LIGHT_THREE:
					if (0 == pPack->bContent[subNum - 3 + i])
					{
						temp = "关";
						m_DeviceList.SetItemText(count,4,temp);
					}
					else
					{
						temp = "开";
						m_DeviceList.SetItemText(count,4,temp);
					}
					break;
				default:
					break;
				}
			}
		}
	}
}

void CDeviceInfoDlg::UpDataRoomInfo(PVOID lParam)
{
	PBUILDING_ENTRY  m_pEntryInfo = NULL;		//楼座链表
	PROMM_INFO_TRANSFER pRoomInfo = (PROMM_INFO_TRANSFER)lParam;
	lpRoomDetail = NULL;
	if (pRoomInfo == NULL)	{	return;	}
	lpRoomDetail = (PROOM_DETAIL_ENTRY)pRoomInfo->pRoomEntry;
	if (lpRoomDetail == NULL)	{	return;	}

	//增加列表中的内容
	CString temp;
	char pExtern[64];
	CPtrArray pRecordArray;
	temp.Format("RCUID = %d",lpRoomDetail->dwRoomTypeID);
	strcpy(pExtern,temp);
	m_DeviceList.DeleteAllItems();
	GetDeviceCfgMethodRecord(pRecordArray,pExtern);
	for (int j = 0;j < pRecordArray.GetSize();j++)
	{
		InsertOneRow(j,pRecordArray[j]);
	}
}

void CDeviceInfoDlg::InitDataList()
{
	haveccomboboxcreate = false;//初始化标志位，表示还没有创建下拉列表框
	CRect Rt; 
	DWORD dwStyleEx;
	::GetClientRect(m_DeviceList.GetSafeHwnd(),&Rt);
	//改变显示模式为报表
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	dwStyleEx = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;  //  
	m_DeviceList.SetExtendedStyle(dwStyleEx);
	////////////////////////////////////////////////////////
	m_DeviceList.InsertColumn( 0, NULL, LVCFMT_CENTER, 0);//插入列
	m_DeviceList.InsertColumn( 1, "设备序号", LVCFMT_CENTER, Rt.Width()/5);//插入列
	m_DeviceList.InsertColumn( 2, "设备名称", LVCFMT_CENTER, Rt.Width()/5);//插入列
	m_DeviceList.InsertColumn( 3, "设备子路", LVCFMT_CENTER, Rt.Width()/5);
	m_DeviceList.InsertColumn( 4, "设备状态", LVCFMT_CENTER, Rt.Width()/5);
	m_DeviceList.InsertColumn( 5, "更改状态", LVCFMT_CENTER, Rt.Width()/5);
}

void CDeviceInfoDlg::InsertOneRow(int Entry,LPVOID lParam)
{
	PDEVICE_CFG_METHOD	m_pEntryInfo = (PDEVICE_CFG_METHOD)lParam;
	CString str;
	int deviceNum,subNum,deviceType;
	//行第一列为空
	m_DeviceList.InsertItem(Entry,NULL);

	deviceType = m_pEntryInfo->bType;
	deviceNum = m_pEntryInfo->bEntry;
	str.Format("%d",deviceNum);
	m_DeviceList.SetItemText(Entry,1,str);

	str.Format("%s",m_pEntryInfo->sLun);
	m_DeviceList.SetItemText(Entry,2,str);
	
	subNum = m_pEntryInfo->bSublun;
	str.Format("%d",subNum);
	m_DeviceList.SetItemText(Entry,3,str);

	//str.Format("%s",m_pEntryInfo->bSublun);
	m_DeviceList.SetItemText(Entry,4,"空");
	m_DeviceList.SetItemText(Entry,5,"否");
}

BOOL CDeviceInfoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

void CDeviceInfoDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CDeviceInfoDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}

HBRUSH CDeviceInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CDeviceInfoDlg::OnBnClickedBtnSet()
{
	// TODO: Add your control notification handler code here
	DWORD nBytes,nRevLength;
	DWORD IpAddress;
	PBYTE pBuf = NULL;
	DWORD dwRtua = 10550;
	WORD  wMstaAndSeq = 0x005E;
	PRCU_ARG_SET_REQ_PACK_0201 pPack = NULL;

	nRevLength = 256;
	pBuf = new BYTE[nRevLength];
	memset(pBuf,0,nRevLength);
	PROOM_DETAIL_ENTRY m_pRoomEntry = lpRoomDetail;
	// TODO: Add your control notification handler code here
	pPack = new RCU_ARG_SET_REQ_PACK_0201;
	if((pPack == NULL) || (m_pRoomEntry == NULL))
	{
		delete pPack;
		delete[] pBuf;
		return;
	}
	int deviceCount = m_DeviceList.GetItemCount();
	nBytes = SetDeviceSwitchStatusPacket(pPack,deviceCount);
	//RTUA
	pPack->sPreFrame.dwRtua = DWORD2_BCD(dwRtua);
	pPack->sPreFrame.wMstaAndSeq = 0x005E;
	//========================================================================		
	WriteDataToPack(pPack);	
	pPack->sPostFrame.bCS = Crc8((PBYTE)pPack,nBytes-1);
	//====================================================================
	IpAddress = inet_addr(m_pRoomEntry->sIpAddress);
	IpAddress = ToLittleEndian(IpAddress);

	nRevLength = SendDataWithResponse((PBYTE)pPack,nBytes,\
		pBuf,nRevLength,\
		IpAddress,m_pRoomEntry->dwPort);
	//=======================================================
	PRCU_ARG_SET_RES_UNIT pUnit = reinterpret_cast<PRCU_ARG_SET_RES_UNIT>(pBuf+16);
	nBytes = 0;
	CString str;
	while(pUnit->uEntry != 0x00)
	{
		if(pUnit->bResult != 0x00)
		{
			str.Format("数据项编号:%04X 设置失败[%s]",pUnit->uEntry,ErrString[pUnit->bResult]);
			MessageBox(str);
		}
		pUnit++;
	}

	delete pPack;
	delete[] pBuf;
}

void CDeviceInfoDlg::WriteDataToPack(PVOID lParam)
{
	PRCU_ARG_SET_REQ_PACK_0201 pPack = (PRCU_ARG_SET_REQ_PACK_0201)lParam;
	int deviceNum,subNum,deviceType;
	CString str,temp;
	int count = m_DeviceList.GetItemCount();

	int listNum[15];
	int changeCount = 0;

	int index = 0;
	for (int j = 0;j < count;j++)
	{
		str = m_DeviceList.GetItemText(j,5);
		if ("是" == str)
		{
			changeCount++;
			listNum[index] = j;
			index++;
		}
		if (changeCount > 15)
		{
			MessageBox("最大允许改变个数为15，请重新选择！","警告");
			return;
		}
	}
	for (int i = 0,j = 0; i < (changeCount * 7); i = i + 7)
	{
		str = m_DeviceList.GetItemText(listNum[j],1);
		deviceNum = _ttoi(str);
		str = m_DeviceList.GetItemText(listNum[j],3);
		subNum = _ttoi(str);
		temp = m_DeviceList.GetItemText(listNum[j],4);
		pPack->bContent[i] = deviceNum;
		pPack->bContent[i + 1] = subNum;
		if ("关" == temp)
		{
			pPack->bContent[i + 2] = 0x0A;
		}
		if ("开" == temp)
		{
			pPack->bContent[i + 2] = 0x09;
		}
		j++;
	}
}

void CDeviceInfoDlg::OnNMClickListDevicedata(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	//printf("行：%d，列：%d\n", pEditCtrl->iItem, pEditCtrl->iSubItem);
	if (pEditCtrl->iItem==-1)//点击到非工作区
	{
		if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
		{
			distroyCcombobox(&m_DeviceList, &m_comBox, e_Item, e_SubItem);
			haveccomboboxcreate = false;
		}
	}
	else if (pEditCtrl->iSubItem == 4)
	{
		if (haveccomboboxcreate == true)
		{
			if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//如果点中的单元格不是之前创建好的
			{
				distroyCcombobox(&m_DeviceList, &m_comBox, e_Item, e_SubItem);
				haveccomboboxcreate = false;
				createCcombobox(pEditCtrl, &m_comBox, e_Item, e_SubItem, haveccomboboxcreate);//创建编辑框
				m_comBox.AddString("开");
				m_comBox.AddString("关");
				//m_comBox.ShowDropDown();//自动下拉
			}
			else//点中的单元格是之前创建好的
			{
				m_comBox.SetFocus();//设置为焦点 
			}
		}
		else
		{
			e_Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			e_SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			createCcombobox(pEditCtrl, &m_comBox, e_Item, e_SubItem, haveccomboboxcreate);//创建编辑框
			m_comBox.AddString("开");
			m_comBox.AddString("关");
			//m_comBox.ShowDropDown();//自动下拉
		}
	}
	else if (pEditCtrl->iSubItem == 5)
	{
		if (haveccomboboxcreate == true)
		{
			if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//如果点中的单元格不是之前创建好的
			{
				distroyCcombobox(&m_DeviceList, &m_comBox, e_Item, e_SubItem);
				haveccomboboxcreate = false;
				createCcombobox(pEditCtrl, &m_comBox, e_Item, e_SubItem, haveccomboboxcreate);//创建编辑框
				m_comBox.AddString("否");
				m_comBox.AddString("是");
				//m_comBox.ShowDropDown();//自动下拉
			}
			else//点中的单元格是之前创建好的
			{
				m_comBox.SetFocus();//设置为焦点 
			}
		}
		else
		{
			e_Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			e_SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			createCcombobox(pEditCtrl, &m_comBox, e_Item, e_SubItem, haveccomboboxcreate);//创建编辑框
			m_comBox.AddString("否");
			m_comBox.AddString("是");
			//m_comBox.ShowDropDown();//自动下拉
		}
	}
	*pResult = 0;
}

void CDeviceInfoDlg::createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccomboboxobj, int &Item, int &SubItem, bool &havecreat)//创建单元格下拉列表框函数
//pEditCtrl为列表对象指针，createccombobox为下拉列表框指针对象，
//Item为创建单元格在列表中的行，SubItem则为列，havecreat为对象创建标准
{
	Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	havecreat = true;
	createccomboboxobj->Create(WS_CHILD | WS_VISIBLE |  CBS_DROPDOWN | CBS_OEMCONVERT, CRect(0, 0, 0, 0), this, IDC_DEVICE_LIST);
	createccomboboxobj->SetFont(this->GetFont(), FALSE);//设置字体,不设置这里的话上面的字会很突兀的感觉
	createccomboboxobj->SetParent(&m_DeviceList);//将list control设置为父窗口,生成的Ccombobox才能正确定位,这个也很重要
	CRect  EditRect;
	m_DeviceList.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);//获取单元格的空间位置信息
	EditRect.SetRect(EditRect.left + 1, EditRect.top, EditRect.left + m_DeviceList.GetColumnWidth(e_SubItem) - 1, EditRect.bottom+60);//+1和-1可以让编辑框不至于挡住列表框中的网格线
	CString strItem = m_DeviceList.GetItemText(e_Item, e_SubItem);//获得相应单元格字符
	createccomboboxobj->SetWindowText(strItem);//将单元格字符显示在编辑框上
	createccomboboxobj->MoveWindow(&EditRect);//将编辑框位置放在相应单元格上
	createccomboboxobj->ShowWindow(SW_SHOW);//显示编辑框在单元格上面
}

void CDeviceInfoDlg::distroyCcombobox(CListCtrl *list, CComboBox* distroyccomboboxobj, int &Item, int &SubItem)
{
	CString meditdata;
	distroyccomboboxobj->GetWindowText(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//更新相应单元格字符
	distroyccomboboxobj->DestroyWindow();//销毁对象，有创建就要有销毁，不然会报错
}

void CDeviceInfoDlg::OnKillfocusCcomboBox()
{
	if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
	{
		distroyCcombobox(&m_DeviceList, &m_comBox, e_Item, e_SubItem);
		haveccomboboxcreate = false;
	}
}
void CDeviceInfoDlg::OnBnClickedButGet()
{
	// TODO: Add your control notification handler code here
	InitDeviceInfo();
}

void CDeviceInfoDlg::OnOK()
{
	OnKillfocusCcomboBox();
}
//void CDeviceInfoDlg::OnKillfocusEdit()
//{
//	if (haveccomboboxcreate == true)//如果之前创建了下拉列表框就销毁掉
//	{
//		distroyCcombobox(&m_DeviceList, &m_comBox, e_Item, e_SubItem);
//		haveccomboboxcreate = false;
//	}
//}

//每写一行的时候进行查询 效率较低   容易出现卡死现象
//void CDeviceInfoDlg::UpdataStatus(int deviceNum,int subNum,int deviceType)
//{
//	DWORD nBytes,nRevLength;
//	DWORD IpAddress;
//	PBYTE pBuf = NULL;
//	DWORD dwRtua = 10550;
//	WORD  wMstaAndSeq = 0x005E;
//	PRCU_ARG_AIR_GET_REQ_PACK_021X pPack = NULL;
//	pPack = new RCU_ARG_AIR_GET_REQ_PACK_021X;
//	memset(pPack,0,sizeof(RCU_ARG_AIR_GET_REQ_PACK_021X));
//
//	nRevLength = 256;
//	pBuf = new BYTE[nRevLength];
//	memset(pBuf,0,nRevLength);
//	PROOM_DETAIL_ENTRY m_pRoomEntry = lpRoomDetail;
//	// TODO: Add your control notification handler code here
//	if((pPack == NULL) || (m_pRoomEntry == NULL))
//		return;
//	int airNum = GetDlgItemInt(IDC_AIR_NUM);
//	nBytes = GetDeviceStatusPacket(pPack,deviceNum);
//	//RTUA
//	pPack->dwRtua = DWORD2_BCD(dwRtua);
//	pPack->wMstaAndSeq = 0x005E;
//	//========================================================================			
//	pPack->sPostFrame.bCS = Crc8((PBYTE)pPack,nBytes-1);
//	//====================================================================
//	IpAddress = inet_addr(m_pRoomEntry->sIpAddress);
//	IpAddress = ToLittleEndian(IpAddress);
//
//	nRevLength = SendDataWithResponse((PBYTE)pPack,nBytes,\
//		pBuf,nRevLength,\
//		IpAddress,m_pRoomEntry->dwPort);
//	//=======================================================
//	//UpdataAllItems(pBuf,TRUE);
//	switch(deviceType)
//	{
//	case 2:
//		break;
//	case 3:
//		break;
//	case 4:
//		break;
//	case 5:
//		break;
//	}
//	if (pBuf->bContent[subNum - 1])
//	{
//	}
//	delete[] pPack;
//	delete[] pBuf;
//}