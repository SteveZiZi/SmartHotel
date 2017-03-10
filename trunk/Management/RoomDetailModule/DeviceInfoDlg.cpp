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
						temp = "��";
						m_DeviceList.SetItemText(count,4,temp);
					}
					else
					{
						temp = "��";
						m_DeviceList.SetItemText(count,4,temp);
					}
					break;
				case LIGHT_FOUR:
					if (0 == pPack->bContent[subNum - 3 + i])
					{
						temp = "��";
						m_DeviceList.SetItemText(count,4,temp);
					}
					else
					{
						temp = "��";
						m_DeviceList.SetItemText(count,4,temp);
					}
					break;
				case RELAY_TWO:
					if (pPack->bContent[i + 2 + subNum/8] & (0x01<<(subNum % 8)))
					{
						temp = "��";
						m_DeviceList.SetItemText(count,4,temp);
					}
					else
					{
						temp = "��";
						m_DeviceList.SetItemText(count,4,temp);
					}
					break;
				case LIGHT_THREE:
					if (0 == pPack->bContent[subNum - 3 + i])
					{
						temp = "��";
						m_DeviceList.SetItemText(count,4,temp);
					}
					else
					{
						temp = "��";
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
	PBUILDING_ENTRY  m_pEntryInfo = NULL;		//¥������
	PROMM_INFO_TRANSFER pRoomInfo = (PROMM_INFO_TRANSFER)lParam;
	lpRoomDetail = NULL;
	if (pRoomInfo == NULL)	{	return;	}
	lpRoomDetail = (PROOM_DETAIL_ENTRY)pRoomInfo->pRoomEntry;
	if (lpRoomDetail == NULL)	{	return;	}

	//�����б��е�����
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
	haveccomboboxcreate = false;//��ʼ����־λ����ʾ��û�д��������б��
	CRect Rt; 
	DWORD dwStyleEx;
	::GetClientRect(m_DeviceList.GetSafeHwnd(),&Rt);
	//�ı���ʾģʽΪ����
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	dwStyleEx = LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;  //  
	m_DeviceList.SetExtendedStyle(dwStyleEx);
	////////////////////////////////////////////////////////
	m_DeviceList.InsertColumn( 0, NULL, LVCFMT_CENTER, 0);//������
	m_DeviceList.InsertColumn( 1, "�豸���", LVCFMT_CENTER, Rt.Width()/5);//������
	m_DeviceList.InsertColumn( 2, "�豸����", LVCFMT_CENTER, Rt.Width()/5);//������
	m_DeviceList.InsertColumn( 3, "�豸��·", LVCFMT_CENTER, Rt.Width()/5);
	m_DeviceList.InsertColumn( 4, "�豸״̬", LVCFMT_CENTER, Rt.Width()/5);
	m_DeviceList.InsertColumn( 5, "����״̬", LVCFMT_CENTER, Rt.Width()/5);
}

void CDeviceInfoDlg::InsertOneRow(int Entry,LPVOID lParam)
{
	PDEVICE_CFG_METHOD	m_pEntryInfo = (PDEVICE_CFG_METHOD)lParam;
	CString str;
	int deviceNum,subNum,deviceType;
	//�е�һ��Ϊ��
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
	m_DeviceList.SetItemText(Entry,4,"��");
	m_DeviceList.SetItemText(Entry,5,"��");
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
			str.Format("��������:%04X ����ʧ��[%s]",pUnit->uEntry,ErrString[pUnit->bResult]);
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
		if ("��" == str)
		{
			changeCount++;
			listNum[index] = j;
			index++;
		}
		if (changeCount > 15)
		{
			MessageBox("�������ı����Ϊ15��������ѡ��","����");
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
		if ("��" == temp)
		{
			pPack->bContent[i + 2] = 0x0A;
		}
		if ("��" == temp)
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
	//printf("�У�%d���У�%d\n", pEditCtrl->iItem, pEditCtrl->iSubItem);
	if (pEditCtrl->iItem==-1)//������ǹ�����
	{
		if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
		{
			distroyCcombobox(&m_DeviceList, &m_comBox, e_Item, e_SubItem);
			haveccomboboxcreate = false;
		}
	}
	else if (pEditCtrl->iSubItem == 4)
	{
		if (haveccomboboxcreate == true)
		{
			if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//������еĵ�Ԫ����֮ǰ�����õ�
			{
				distroyCcombobox(&m_DeviceList, &m_comBox, e_Item, e_SubItem);
				haveccomboboxcreate = false;
				createCcombobox(pEditCtrl, &m_comBox, e_Item, e_SubItem, haveccomboboxcreate);//�����༭��
				m_comBox.AddString("��");
				m_comBox.AddString("��");
				//m_comBox.ShowDropDown();//�Զ�����
			}
			else//���еĵ�Ԫ����֮ǰ�����õ�
			{
				m_comBox.SetFocus();//����Ϊ���� 
			}
		}
		else
		{
			e_Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			e_SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			createCcombobox(pEditCtrl, &m_comBox, e_Item, e_SubItem, haveccomboboxcreate);//�����༭��
			m_comBox.AddString("��");
			m_comBox.AddString("��");
			//m_comBox.ShowDropDown();//�Զ�����
		}
	}
	else if (pEditCtrl->iSubItem == 5)
	{
		if (haveccomboboxcreate == true)
		{
			if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//������еĵ�Ԫ����֮ǰ�����õ�
			{
				distroyCcombobox(&m_DeviceList, &m_comBox, e_Item, e_SubItem);
				haveccomboboxcreate = false;
				createCcombobox(pEditCtrl, &m_comBox, e_Item, e_SubItem, haveccomboboxcreate);//�����༭��
				m_comBox.AddString("��");
				m_comBox.AddString("��");
				//m_comBox.ShowDropDown();//�Զ�����
			}
			else//���еĵ�Ԫ����֮ǰ�����õ�
			{
				m_comBox.SetFocus();//����Ϊ���� 
			}
		}
		else
		{
			e_Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			e_SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			createCcombobox(pEditCtrl, &m_comBox, e_Item, e_SubItem, haveccomboboxcreate);//�����༭��
			m_comBox.AddString("��");
			m_comBox.AddString("��");
			//m_comBox.ShowDropDown();//�Զ�����
		}
	}
	*pResult = 0;
}

void CDeviceInfoDlg::createCcombobox(NM_LISTVIEW  *pEditCtrl, CComboBox *createccomboboxobj, int &Item, int &SubItem, bool &havecreat)//������Ԫ�������б����
//pEditCtrlΪ�б����ָ�룬createccomboboxΪ�����б��ָ�����
//ItemΪ������Ԫ�����б��е��У�SubItem��Ϊ�У�havecreatΪ���󴴽���׼
{
	Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	havecreat = true;
	createccomboboxobj->Create(WS_CHILD | WS_VISIBLE |  CBS_DROPDOWN | CBS_OEMCONVERT, CRect(0, 0, 0, 0), this, IDC_DEVICE_LIST);
	createccomboboxobj->SetFont(this->GetFont(), FALSE);//��������,����������Ļ�������ֻ��ͻأ�ĸо�
	createccomboboxobj->SetParent(&m_DeviceList);//��list control����Ϊ������,���ɵ�Ccombobox������ȷ��λ,���Ҳ����Ҫ
	CRect  EditRect;
	m_DeviceList.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);//��ȡ��Ԫ��Ŀռ�λ����Ϣ
	EditRect.SetRect(EditRect.left + 1, EditRect.top, EditRect.left + m_DeviceList.GetColumnWidth(e_SubItem) - 1, EditRect.bottom+60);//+1��-1�����ñ༭�����ڵ�ס�б���е�������
	CString strItem = m_DeviceList.GetItemText(e_Item, e_SubItem);//�����Ӧ��Ԫ���ַ�
	createccomboboxobj->SetWindowText(strItem);//����Ԫ���ַ���ʾ�ڱ༭����
	createccomboboxobj->MoveWindow(&EditRect);//���༭��λ�÷�����Ӧ��Ԫ����
	createccomboboxobj->ShowWindow(SW_SHOW);//��ʾ�༭���ڵ�Ԫ������
}

void CDeviceInfoDlg::distroyCcombobox(CListCtrl *list, CComboBox* distroyccomboboxobj, int &Item, int &SubItem)
{
	CString meditdata;
	distroyccomboboxobj->GetWindowText(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//������Ӧ��Ԫ���ַ�
	distroyccomboboxobj->DestroyWindow();//���ٶ����д�����Ҫ�����٣���Ȼ�ᱨ��
}

void CDeviceInfoDlg::OnKillfocusCcomboBox()
{
	if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
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
//	if (haveccomboboxcreate == true)//���֮ǰ�����������б������ٵ�
//	{
//		distroyCcombobox(&m_DeviceList, &m_comBox, e_Item, e_SubItem);
//		haveccomboboxcreate = false;
//	}
//}

//ÿдһ�е�ʱ����в�ѯ Ч�ʽϵ�   ���׳��ֿ�������
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