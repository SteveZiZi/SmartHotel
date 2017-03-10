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
	ON_EN_KILLFOCUS(IDC_LIST_DATA, &CAccountManagement::OnKillfocusEdit)//添加动态生成编辑框的失去焦点响应函数
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

	POSITION pos = m_DataList.GetFirstSelectedItemPosition(); //拿到第一个被选择的项目位置；
	while(pos)
	{ 
		int nSelIndex = m_DataList.GetNextSelectedItem(pos);//通过前一个位置,拿到下一个位置的项目的索引号;
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
		MessageBox("账号不能为空","警告");
		return;
	}
	GetDlgItemText(IDC_EDIT_PASSWORD,str);
	strcpy(pUserInfo->sPasswords,str);
	if (str.IsEmpty())
	{
		MessageBox("密码不能为空","警告");
		return;
	}

	pUserInfo->nDepartment = groupID;
	pUserInfo->dwPermission = power; 
	if (CheckExit(pUserInfo))
	{
		MessageBox("新增的用户已经存在，请重新输入用户名","警告");
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

	POSITION pos = m_DataList.GetFirstSelectedItemPosition(); //拿到第一个被选择的项目位置；
	while(pos)
	{ 
		int nSelIndex = m_DataList.GetNextSelectedItem(pos);//通过前一个位置,拿到下一个位置的项目的索引号;
		str = m_DataList.GetItemText(nSelIndex,2);
		strcpy(pUserInfo->sName,str);

		str = m_DataList.GetItemText(nSelIndex,3);
		strcpy(pUserInfo->sPasswords,str);

		str = m_DataList.GetItemText(nSelIndex,4);
		pUserInfo->nDepartment = _ttoi(str);

		str = m_DataList.GetItemText(nSelIndex,5);
		pUserInfo->dwPermission = (unsigned long)_ttoi(str);
		m_DataList.DeleteItem(nSelIndex);//删除所选择的那项;
		pos = m_DataList.GetFirstSelectedItemPosition();//因为前面删除了一项,所以list的结构发生了变化,所以得重新再判断第一个位置拿到pos;
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
	//改变显示模式为报表
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	dwStyleEx = LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES;  //  
	m_DataList.SetExtendedStyle(dwStyleEx);
	////////////////////////////////////////////////////////
	m_DataList.InsertColumn( 0, NULL, LVCFMT_CENTER, 0);//插入列
	m_DataList.InsertColumn( 1, "序号", LVCFMT_CENTER, Rt.Width()/5);//插入列
	m_DataList.InsertColumn( 2, "用户名", LVCFMT_CENTER, Rt.Width()/5 );//插入列
	m_DataList.InsertColumn( 3, "密码", LVCFMT_CENTER, Rt.Width()/5 );//插入列
	m_DataList.InsertColumn( 4, "组号", LVCFMT_CENTER, Rt.Width()/5 );//插入列
	m_DataList.InsertColumn( 5, "权限", LVCFMT_CENTER, Rt.Width()/5 );//插入列
}

void CAccountManagement::UpdataDLG(CString result)
{
	if ("前台部" == result)
	{
		groupID = 0;
		power = 0;
	}
	if ("工程部" == result)
	{
		groupID = 1;
		power = 0x8000003f;
	}
	if ("总经办" == result)
	{
		groupID = 2;
		power = 0;
	}
	if ("服务部" == result)
	{
		groupID = 3;
		power = 0;
	}
	if ("管理员" == result)
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
	//行第一列为空
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
	//关联结构体
	m_DataList.SetItemData(Entry,(DWORD_PTR)m_pUserInfo);
}

void CAccountManagement::createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat)//创建单元格编辑框函数
//pEditCtrl为列表对象指针，createdit为编辑框指针对象，
//Item为创建单元格在列表中的行，SubItem则为列，havecreat为对象创建标准
{
	Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
	createdit->Create(ES_AUTOHSCROLL | WS_CHILD | ES_LEFT | ES_WANTRETURN,
		CRect(0, 0, 0, 0), this, IDC_LIST_DATA);//创建编辑框对象,IDC_EDIT_CREATEID为控件ID号3000，在文章开头定义
	havecreat = true;
	createdit->SetFont(this->GetFont(), FALSE);//设置字体,不设置这里的话上面的字会很突兀的感觉
	createdit->SetParent(&m_DataList);//将list control设置为父窗口,生成的Edit才能正确定位,这个也很重要
	CRect  EditRect;
	m_DataList.GetSubItemRect(e_Item, e_SubItem, LVIR_LABEL, EditRect);//获取单元格的空间位置信息
	EditRect.SetRect(EditRect.left+1, EditRect.top+1, EditRect.left + m_DataList.GetColumnWidth(e_SubItem)-1, EditRect.bottom-1);//+1和-1可以让编辑框不至于挡住列表框中的网格线
	CString strItem = m_DataList.GetItemText(e_Item, e_SubItem);//获得相应单元格字符
	createdit->SetWindowText(strItem);//将单元格字符显示在编辑框上
	createdit->MoveWindow(&EditRect);//将编辑框位置放在相应单元格上
	createdit->ShowWindow(SW_SHOW);//显示编辑框在单元格上面
	createdit->SetFocus();//设置为焦点 
	createdit->SetSel(-1);//设置光标在文本框文字的最后
}

void CAccountManagement::distroyEdit(CListCtrl *list,CEdit* distroyedit, int &Item, int &SubItem)
{
	CString meditdata;
	distroyedit->GetWindowText(meditdata);
	list->SetItemText(Item, SubItem, meditdata);//获得相应单元格字符
	distroyedit->DestroyWindow();//销毁对象，有创建就要有销毁，不然会报错
}

void CAccountManagement::OnNMClickListAccountdata(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW  *pEditCtrl = (NM_LISTVIEW *)pNMHDR;
	//printf("行：%d，列：%d\n", pEditCtrl->iItem, pEditCtrl->iSubItem);
	if (pEditCtrl->iItem==-1)//点击到非工作区
	{
		if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
		{
			distroyEdit(&m_DataList, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
			haveeditcreate = false;
		}
	}
	else if (pEditCtrl->iSubItem == 3)
	{
		
		if (haveeditcreate == true)
		{
			if (!(e_Item == pEditCtrl->iItem && e_SubItem == pEditCtrl->iSubItem))//如果点中的单元格不是之前创建好的
			{
				distroyEdit(&m_DataList, &m_Edit, e_Item, e_SubItem);
				haveeditcreate = false;
				createEdit(pEditCtrl, &m_Edit, e_Item, e_SubItem, haveeditcreate);//创建编辑框
			}
			else//点中的单元格是之前创建好的
			{
				m_Edit.SetFocus();//设置为焦点 
			}
		}
		else
		{
			e_Item = pEditCtrl->iItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			e_SubItem = pEditCtrl->iSubItem;//将点中的单元格的行赋值给“刚编辑过的行”以便后期处理
			createEdit(pEditCtrl, &m_Edit, e_Item, e_SubItem, haveeditcreate);//创建编辑框
		}
	}
	*pResult = 0;
}

void CAccountManagement::OnKillfocusEdit()
{
	if (haveeditcreate == true)//如果之前创建了编辑框就销毁掉
	{
		distroyEdit(&m_DataList, &m_Edit, e_Item, e_SubItem);//销毁单元格编辑框对象
		haveeditcreate = false;
	}
}

void CAccountManagement::OnOK()
{
	OnKillfocusEdit();
}