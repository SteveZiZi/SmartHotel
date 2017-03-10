// AccountManagement.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoCFG.h"
#include "AccountManagement.h"

// CAccountManagement dialog

IMPLEMENT_DYNAMIC(CAccountManagement, CDialog)

CAccountManagement::CAccountManagement(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountManagement::IDD, pParent)
{

}

CAccountManagement::~CAccountManagement()
{
}

void CAccountManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST_DATA,m_DataList);
	DDX_Control(pDX,IDC_EDIT_USER,m_EditUser);
	DDX_Control(pDX,IDC_EDIT_PASSWORD,m_EditPsw);
}

BEGIN_MESSAGE_MAP(CAccountManagement, CDialog)
	ON_BN_CLICKED(IDC_BTN_MODIFY_PASSWORD, &CAccountManagement::OnBnClickedBtnModifyPassword)
	ON_BN_CLICKED(IDC_BTN_ADD_USER, &CAccountManagement::OnBnClickedBtnAddUser)
	ON_BN_CLICKED(IDC_BTN_DELETE_USER, &CAccountManagement::OnBnClickedBtnDeleteUser)
	ON_NOTIFY(NM_CLICK,IDC_LIST_DATA,&CAccountManagement::OnNMClickListAccountdata)
	ON_EN_KILLFOCUS(IDC_LIST_DATA, &CAccountManagement::OnKillfocusEdit)//��Ӷ�̬���ɱ༭���ʧȥ������Ӧ����
END_MESSAGE_MAP()

BOOL CAccountManagement::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitDataList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAccountManagement::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
}

void CAccountManagement::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CAccountManagement::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}

BOOL CAccountManagement::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}
// CAccountManagement message handlers

void CAccountManagement::OnBnClickedBtnModifyPassword()
{
	// TODO: Add your control notification handler code here
	PUSER_INFORMATION pUserInfo = NULL;
	pUserInfo = new USER_INFORMATION;
	ZeroMemory(pUserInfo,sizeof(USER_INFORMATION));

	CString str,temp;

	POSITION pos = m_DataList.GetFirstSelectedItemPosition(); //�õ���һ����ѡ�����Ŀλ�ã�
	while(pos)
	{ 
		int nSelIndex = m_DataList.GetNextSelectedItem(pos);//ͨ��ǰһ��λ��,�õ���һ��λ�õ���Ŀ��������;
		str = m_DataList.GetItemText(nSelIndex,2);
		strcpy(pUserInfo->sName,str);

		str = m_DataList.GetItemText(nSelIndex,3);
		strcpy(pUserInfo->sPasswords,str);

		str = m_DataList.GetItemText(nSelIndex,4);
		pUserInfo->nDepartment = _ttoi(str);

		str = m_DataList.GetItemText(nSelIndex,5);
		pUserInfo->dwPermission = (unsigned long)_ttoi(str);
	}

	temp.Format("userID = \'%s\' ",pUserInfo->sName);
	ModifyUserInfoRecord(pUserInfo,temp);
}

void CAccountManagement::OnBnClickedBtnAddUser()
{
	// TODO: Add your control notification handler code here
	PUSER_INFORMATION pUserInfo = NULL;
	pUserInfo = new USER_INFORMATION;
	ZeroMemory(pUserInfo,sizeof(USER_INFORMATION));

	CString str;
	GetDlgItemText(IDC_EDIT_USER,str);
	strcpy(pUserInfo->sName,str);
	if (str.IsEmpty())
	{
		MessageBox("�˺Ų���Ϊ��","����");
		return;
	}
	GetDlgItemText(IDC_EDIT_PASSWORD,str);
	strcpy(pUserInfo->sPasswords,str);
	if (str.IsEmpty())
	{
		MessageBox("���벻��Ϊ��","����");
		return;
	}

	pUserInfo->nDepartment = groupID;
	pUserInfo->dwPermission = power; 
	if (CheckExit(pUserInfo))
	{
		MessageBox("�������û��Ѿ����ڣ������������û���","����");
		return;
	}
	InsertUserInfoRecord(pUserInfo);
	int count = m_DataList.GetItemCount();
	InsertOneRow(count,pUserInfo);
}

BOOL CAccountManagement::CheckExit(LPVOID lParam)
{
	PUSER_INFORMATION pUserInfo = (PUSER_INFORMATION)lParam;
	CPtrArray pRecordArray;
	GetUserInfoRecord(pRecordArray,NULL);
	for (int j = 0;j < pRecordArray.GetSize();j++)
	{
		PUSER_INFORMATION pUserInfoTemp = (PUSER_INFORMATION)pRecordArray[j];
		if (0 == strcmp(pUserInfoTemp->sName,pUserInfo->sName))
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CAccountManagement::OnBnClickedBtnDeleteUser()
{
	// TODO: Add your control notification handler code here
	PUSER_INFORMATION pUserInfo = NULL;
	pUserInfo = new USER_INFORMATION;
	ZeroMemory(pUserInfo,sizeof(USER_INFORMATION));

	CString str,temp;

	POSITION pos = m_DataList.GetFirstSelectedItemPosition(); //�õ���һ����ѡ�����Ŀλ�ã�
	while(pos)
	{ 
		int nSelIndex = m_DataList.GetNextSelectedItem(pos);//ͨ��ǰһ��λ��,�õ���һ��λ�õ���Ŀ��������;
		str = m_DataList.GetItemText(nSelIndex,2);
		strcpy(pUserInfo->sName,str);

		str = m_DataList.GetItemText(nSelIndex,3);
		strcpy(pUserInfo->sPasswords,str);

		str = m_DataList.GetItemText(nSelIndex,4);
		pUserInfo->nDepartment = _ttoi(str);

		str = m_DataList.GetItemText(nSelIndex,5);
		pUserInfo->dwPermission = (unsigned long)_ttoi(str);
		m_DataList.DeleteItem(nSelIndex);//ɾ����ѡ�������;
		pos = m_DataList.GetFirstSelectedItemPosition();//��Ϊǰ��ɾ����һ��,����list�Ľṹ�����˱仯,���Ե��������жϵ�һ��λ���õ�pos;
	}
	
	temp.Format("userID = \'%s\' ",pUserInfo->sName);

	DeleteUserInfoRecord(pUserInfo,temp);
	delete []pUserInfo;
}

void CAccountManagement::SetRelationItem(PVOID pItem)
{
	if(pItem != NULL)
		hItem = (HTREEITEM)pItem;
}

void CAccountManagement::InitDataList()
{
	CRect Rt; 
	DWORD dwStyleEx;
	::GetClientRect(m_DataList.GetSafeHwnd(),&Rt);
	//�ı���ʾģʽΪ����
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	dwStyleEx = LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES;  //  
	m_DataList.SetExtendedStyle(dwStyleEx);
	////////////////////////////////////////////////////////
	m_DataList.InsertColumn( 0, NULL, LVCFMT_CENTER, 0);//������
	m_DataList.InsertColumn( 1, "���", LVCFMT_CENTER, Rt.Width()/5);//������
	m_DataList.InsertColumn( 2, "�û���", LVCFMT_CENTER, Rt.Width()/5 );//������
	m_DataList.InsertColumn( 3, "����", LVCFMT_CENTER, Rt.Width()/5 );//������
	m_DataList.InsertColumn( 4, "���", LVCFMT_CENTER, Rt.Width()/5 );//������
	m_DataList.InsertColumn( 5, "Ȩ��", LVCFMT_CENTER, Rt.Width()/5 );//������
}

void CAccountManagement::UpdataDLG(CString result)
{
	if ("ǰ̨��" == result)
	{
		groupID = 0;
		power = 0;
	}
	if ("���̲�" == result)
	{
		groupID = 1;
		power = 0x8000003f;
	}
	if ("�ܾ���" == result)
	{
		groupID = 2;
		power = 0;
	}
	if ("����" == result)
	{
		groupID = 3;
		power = 0;
	}
	if ("����Ա" == result)
	{
		groupID = 4;
		power = 0x8000003f;
	}

	CPtrArray pRecordArray;
	char pExtern[64];

	CString temp;
	temp.Format("groupsID = %d",groupID);
	strcpy(pExtern,temp);
	m_DataList.DeleteAllItems();
	GetUserInfoRecord(pRecordArray,pExtern);
	for (int j = 0;j < pRecordArray.GetSize();j++)
	{
		InsertOneRow(j,pRecordArray[j]);
	}
}

void CAccountManagement::InsertOneRow(int Entry,LPVOID lParam)
{
	PUSER_INFORMATION	m_pUserInfo = (PUSER_INFORMATION)lParam;
	CString str;
	//�е�һ��Ϊ��
	m_DataList.InsertItem(Entry,NULL);

	str.Format("%d",Entry + 1);
	m_DataList.SetItemText(Entry,1,str);

	str.Format("%s",m_pUserInfo->sName);
	m_DataList.SetItemText(Entry,2,str);

	str.Format("%s",m_pUserInfo->sPasswords);
	m_DataList.SetItemText(Entry,3,str);

	str.Format("%d",m_pUserInfo->nDepartment);
	m_DataList.SetItemText(Entry,4,str);

	str.Format("%ld",m_pUserInfo->dwPermission);
	m_DataList.SetItemText(Entry,5,str);
	//�����ṹ��
	m_DataList.SetItemData(Entry,(DWORD_PTR)m_pUserInfo);
}

void CAccountManagement::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat)//������Ԫ��༭����
//pEditCtrlΪ�б����ָ�룬createditΪ�༭��ָ�����
//ItemΪ������Ԫ�����б��е��У�SubItem��Ϊ�У�havecreatΪ���󴴽���׼
{
	Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN,
		CRect(0, 0, 0, 0), this, IDC_LIST_DATA);//�����༭�����,IDC_EDIT_CREATEIDΪ�ؼ�ID��3000�������¿�ͷ����
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);//��������,����������Ļ�������ֻ��ͻأ�ĸо�
	createdit->SetParent(&m_DataList);//��list control����Ϊ������,���ɵ�Edit������ȷ��λ,���Ҳ����Ҫ
	CRect  EditRect;
	m_DataList.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);//��ȡ��Ԫ��Ŀռ�λ����Ϣ
	EditRect.SetRect(EditRect.left+1, EditRect.top+1, EditRect.left + m_DataList.GetColumnWidth(e_SubItem)-1, EditRect.bottom-1);//+1��-1�����ñ༭�����ڵ�ס�б���е�������
	CString strItem = m_DataList.GetItemText(e_Item, e_SubItem);//�����Ӧ��Ԫ���ַ�
	createdit->SetWindowText(strItem);//����Ԫ���ַ���ʾ�ڱ༭����
	createdit->MoveWindow(&EditRect);//���༭��λ�÷�����Ӧ��Ԫ����
	createdit->ShowWindow(SW_SHOW);//��ʾ�༭���ڵ�Ԫ������
	createdit->SetFocus();//����Ϊ���� 
	createdit->SetSel(-1);//���ù�����ı������ֵ����
}

void CAccountManagement::distroyEdit(CListCtrl *list,CEdit* distroyedit, int &Item, int &SubItem)
{
	CString meditdata;
	distroyedit->GetWindowText(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//�����Ӧ��Ԫ���ַ�
	distroyedit->DestroyWindow();//���ٶ����д�����Ҫ�����٣���Ȼ�ᱨ��
}

void CAccountManagement::OnNMClickListAccountdata(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	//printf("�У�%d���У�%d\n", pEditCtrl->iItem, pEditCtrl->iSubItem);
	if (pEditCtrl->iItem==-1)//������ǹ�����
	{
		if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
		{
			distroyEdit(&m_DataList, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
			haveeditcreate = false;
		}
	}
	else if (pEditCtrl->iSubItem == 3)
	{
		
		if (haveeditcreate == true)
		{
			if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//������еĵ�Ԫ����֮ǰ�����õ�
			{
				distroyEdit(&m_DataList, &m_Edit, e_Item, e_SubItem);
				haveeditcreate = false;
				createEdit(pEditCtrl, &m_Edit, e_Item, e_SubItem, haveeditcreate);//�����༭��
			}
			else//���еĵ�Ԫ����֮ǰ�����õ�
			{
				m_Edit.SetFocus();//����Ϊ���� 
			}
		}
		else
		{
			e_Item = pEditCtrl->iItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			e_SubItem = pEditCtrl->iSubItem;//�����еĵ�Ԫ����и�ֵ�����ձ༭�����С��Ա���ڴ���
			createEdit(pEditCtrl, &m_Edit, e_Item, e_SubItem, haveeditcreate);//�����༭��
		}
	}
	*pResult = 0;
}

void CAccountManagement::OnKillfocusEdit()
{
	if (haveeditcreate == true)//���֮ǰ�����˱༭������ٵ�
	{
		distroyEdit(&m_DataList, &m_Edit, e_Item, e_SubItem);//���ٵ�Ԫ��༭�����
		haveeditcreate = false;
	}
}

void CAccountManagement::OnOK()
{
	OnKillfocusEdit();
}