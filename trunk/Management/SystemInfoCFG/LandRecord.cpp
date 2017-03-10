// LandRecord.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoCFG.h"
#include "LandRecord.h"


// CLandRecord dialog

IMPLEMENT_DYNAMIC(CLandRecord, CDialog)

CLandRecord::CLandRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CLandRecord::IDD, pParent)
{

}

CLandRecord::~CLandRecord()
{
}

void CLandRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_RECORD_LIST,m_RecordList);
}


BEGIN_MESSAGE_MAP(CLandRecord, CDialog)
	ON_BN_CLICKED(IDC_BTN_INQUIRY, &CLandRecord::OnBnClickedBtnInquiry)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CLandRecord::OnBnClickedBtnDelete)
END_MESSAGE_MAP()

BOOL CLandRecord::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitRecordList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLandRecord::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

void CLandRecord::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CLandRecord::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}

BOOL CLandRecord::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}
// CLandRecord message handlers

void CLandRecord::OnBnClickedBtnInquiry()
{
	// TODO: Add your control notification handler code here
	CPtrArray pRecordArray;

	m_RecordList.DeleteAllItems();
	GetLoginInfoRecord(pRecordArray,NULL);
	for (int j = 0;j < pRecordArray.GetSize();j++)
	{
		InsertOneRow(j,pRecordArray[j]);
	}
}

void CLandRecord::InsertOneRow(int Entry,LPVOID lParam)
{
	PUSER_LOGIN_INFORMATION	pUserloginInfo = (PUSER_LOGIN_INFORMATION)lParam;
	CString str;
	//行第一列为空
	m_RecordList.InsertItem(Entry,NULL);

	str.Format("%s",pUserloginInfo->sName);
	m_RecordList.SetItemText(Entry,1,str);

	str.Format("%d-%d-%d %d:%d:%d",pUserloginInfo->mtLogin.GetYear(),pUserloginInfo->mtLogin.GetMonth(),\
		pUserloginInfo->mtLogin.GetDay(),pUserloginInfo->mtLogin.GetHour(),pUserloginInfo->mtLogin.GetMinute(),\
		pUserloginInfo->mtLogin.GetSecond());
	m_RecordList.SetItemText(Entry,2,str);
	
	str.Format("%d-%d-%d %d:%d:%d",pUserloginInfo->mtExit.GetYear(),pUserloginInfo->mtExit.GetMonth(),\
		pUserloginInfo->mtExit.GetDay(),pUserloginInfo->mtExit.GetHour(),pUserloginInfo->mtExit.GetMinute(),\
		pUserloginInfo->mtExit.GetSecond());
	m_RecordList.SetItemText(Entry,3,str);
}

void CLandRecord::SetRelationItem(PVOID pItem)
{
	if(pItem != NULL)
		hItem = (HTREEITEM)pItem;
}

void CLandRecord::UpdataDLG(CString result)
{
	if ("前台部" == result)
	{
		groupID = 5;
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
	//m_RecordList.DeleteAllItems();
}

void CLandRecord::InitRecordList()
{
	CRect Rt; 
	DWORD dwStyleEx;
	::GetClientRect(m_RecordList.GetSafeHwnd(),&Rt);
	//改变显示模式为报表
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	dwStyleEx = LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES;  //  
	m_RecordList.SetExtendedStyle(dwStyleEx);
	////////////////////////////////////////////////////////
	m_RecordList.InsertColumn( 0, NULL, LVCFMT_CENTER, 0);//插入列
	m_RecordList.InsertColumn( 1, "用户名", LVCFMT_CENTER, Rt.Width()/5);//插入列
	m_RecordList.InsertColumn( 2, "登陆时间", LVCFMT_CENTER, Rt.Width()* 2/5 );//插入列
	m_RecordList.InsertColumn( 3, "登出时间", LVCFMT_CENTER, Rt.Width()* 2/5 );//插入列
}

void CLandRecord::OnOK()
{

}
void CLandRecord::OnBnClickedBtnDelete()
{
	// TODO: Add your control notification handler code here
	PUSER_LOGIN_INFORMATION pUserLoginInfo = NULL;
	pUserLoginInfo = new USER_LOGIN_INFORMATION;
	ZeroMemory(pUserLoginInfo,sizeof(USER_LOGIN_INFORMATION));

	CString str,temp;

	POSITION pos = m_RecordList.GetFirstSelectedItemPosition(); //拿到第一个被选择的项目位置；
	while(pos)
	{ 
		int nSelIndex = m_RecordList.GetNextSelectedItem(pos);//通过前一个位置,拿到下一个位置的项目的索引号;
		str = m_RecordList.GetItemText(nSelIndex,1);
		strcpy(pUserLoginInfo->sName,str);

		str = m_RecordList.GetItemText(nSelIndex,2);
		int  nYear,nMonth,nDate,nHour,nMin,nSec;
		sscanf(str,"%d-%d-%d %d:%d:%d",&nYear,&nMonth,&nDate,&nHour,&nMin,&nSec);
		CTime loginIn(nYear,nMonth,nDate,nHour,nMin,nSec);
		pUserLoginInfo->mtLogin = loginIn;

		str = m_RecordList.GetItemText(nSelIndex,3);
		sscanf(str,"%d-%d-%d %d:%d:%d",&nYear,&nMonth,&nDate,&nHour,&nMin,&nSec);
		CTime logOut(nYear,nMonth,nDate,nHour,nMin,nSec);
		pUserLoginInfo->mtExit = logOut;
		m_RecordList.DeleteItem(nSelIndex);//删除所选择的那项;
		pos = m_RecordList.GetFirstSelectedItemPosition();//因为前面删除了一项,所以list的结构发生了变化,所以得重新再判断第一个位置拿到pos;
	}

	DeleteLoginInfoRecord(pUserLoginInfo,NULL);
	delete pUserLoginInfo;
}
