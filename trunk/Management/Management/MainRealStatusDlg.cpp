// MainRealStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include <afxmt.h>
#include "Management.h"
#include "MainRealStatusDlg.h"

#include "..\\CommSource\\Project\\DataTransferLay.h"		//数据传输层
#include <Winsock2.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define AIRTYPE 1

enum FANSPEEN
{
	FANCLOSE,
	FANLOW,
	FANMIDDLE,
	FANHEIGH,
};
//*************************************************
typedef struct _QUIRY_INFO
{
	PVOID wParam;				//存放对话框指针的
	
	PVOID lParam;				//存放房间条目的

	PVOID pGolabRoomInfo;
}QUIRY_INFO,*PQUIRY_INFO;

/////////////////////////////////////////////////////////////////////////////////
//右键单击弹出菜单项
#define  IDM_POPMENU_BASE     10
// CMainRealStatusDlg dialog
CMutex hMutex(FALSE,NULL,NULL);								//互斥变量
CEvent hRoomEntryEvent(FALSE,FALSE,NULL,NULL);				//右键点击客房结束
CEvent hInquiryCompleteEvent(FALSE,FALSE,NULL,NULL);		//查询结束的事件
BYTE GolabRunStatus = GOLAB_THREAD_IDLE;
HANDLE	hInquiryThread;

//FILE *fp = NULL;
//===========================================================================
CMainRealStatusDlg::CMainRealStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainRealStatusDlg::IDD, pParent),hRoomModule(NULL)
{
	//{{AFX_DATA_INIT(CMainRealStatusDlg)
		// NOTE: the ClassWizard will add member initialization here
	hParentHwnd = pParent->m_hWnd;
	//}}AFX_DATA_INIT
	pRoomTypeValue = NULL;
    lReportStyle = TRUE;
	hInquiryThread = INVALID_HANDLE_VALUE;
	pLoadDlg = NULL;
	m_Flag = FALSE;
}


CMainRealStatusDlg::~CMainRealStatusDlg()
{
	//删除菜单
	delete[] (CMenu *)m_pMenu;
	ReleaseAllMemory();
	//释放客房模块
	if(hRoomModule != NULL)
		FreeLibrary(hRoomModule);
//退出线程
	GolabRunStatus = GOLAB_THREAD_EXIT;							//设定要退出
	if (hInquiryThread != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hInquiryThread);
		hInquiryThread = INVALID_HANDLE_VALUE;
	}
	//fprintf(fp,"设置退出事件\n");
	//WaitForSingleObject(hInquiryCompleteEvent,INFINITE);		//等查询事件结束
	//fprintf(fp,"退出事件等到\n");
//退出数据传输
	//UnInitDataTransferLay();
	//fprintf(fp,"CMainRealStatusDlg End\n");

}

void CMainRealStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainRealStatusDlg)
	DDX_Control(pDX, IDC_TAB_BASIC_ROOMSTATUS, m_BasicRoomStatus);
	DDX_Control(pDX, IDC_RS_ROOMTYPETAB, m_RoomType);
	DDX_Control(pDX, IDC_RS_ROOMLIST, m_Room);
	DDX_Control(pDX, IDC_COMBO_FLOOR, m_Floor);
	DDX_Control(pDX, IDC_COMBO_BUILDING, m_Building);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainRealStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CMainRealStatusDlg)
	ON_NOTIFY(NM_RCLICK, IDC_RS_ROOMLIST, OnRclickRsRoomlist)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_COMBO_BUILDING, OnSelchangeComboBuilding)
	ON_CBN_SELCHANGE(IDC_COMBO_FLOOR, OnSelchangeComboFloor)
	ON_NOTIFY(TCN_SELCHANGE, IDC_RS_ROOMTYPETAB, OnSelchangeRsRoomtypetab)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainRealStatusDlg message handlers

BOOL CMainRealStatusDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//LoadImageList();
	// TODO: Add extra initialization here
	AdjustItemPosition();   //调整控件位置
	//加载各个模块信息
    LoadFunModule();
//初始化各控件的外观及条目
    InitAllItem();
	//RefreshQuickRoomList(NULL);
////////////////////////////////////////////////////////
	//加载查询线程
	if(GolabRunStatus == GOLAB_THREAD_IDLE)
	{
		GolabRunStatus = GOLAB_THREAD_RUN;
		hInquiryThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)InquiryListRoomThread,this,0,NULL);
		/*if(hInquiryThread != INVALID_HANDLE_VALUE)
			CloseHandle(hInquiryThread);
		else
			GolabRunStatus = GOLAB_THREAD_IDLE;*/
	}
	//更新房态信息
	//ReloadRoomStateInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainRealStatusDlg::AdjustItemPosition()
{
    CRect pRect;
	::GetClientRect(hParentHwnd,&pRect);
    //标签控件的大小
	::MoveWindow(GetDlgItem(IDC_RS_ROOMTYPETAB)->GetSafeHwnd(),100,0,pRect.Width()-100,30,TRUE);

	//列表框的大小
    ::MoveWindow(GetDlgItem(IDC_RS_ROOMLIST)->GetSafeHwnd(),100,25,pRect.Width()-320,pRect.Height()-25,TRUE);





	//MessageBox(str);
}

void CMainRealStatusDlg::InitAllItem()
{
//首先初始化客房列表框的条目信息
  	CRect Rect;
    ::GetClientRect(m_Room,&Rect);
    DWORD Style = m_Room.GetExtendedStyle();
    Style |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_Room.SetExtendedStyle(Style);

//	m_RoomStyleList.SetColColor(0,RGB(10,150,20)); //设置列背景色
//	m_RoomStyleList.SetColColor(2,RGB(30,100,90)); //设置列背景色
//	m_Room.SetBkColor(RGB(50,10,10));        //设置背景色
//	m_RoomStyleList.SetItemColor(1,1,RGB(100,100,10)); //设置指定单元背景色
	m_Room.SetRowHeigt(25);               //设置行高度
	m_Room.SetHeaderHeight(1.5);          //设置头部高度
	m_Room.SetHeaderFontHW(16,0);         //设置头部字体高度,和宽度,0表示缺省，自适应 
	m_Room.SetHeaderTextColor(RGB(255,200,100)); //设置头部字体颜色
//	m_RoomStyleList.SetTextColor(RGB(0,255,255));    //设置文本颜色
//	m_Room.SetHeaderBKColor(100,255,100,8); //设置头部背景色
	m_Room.SetFontHW(15,0);                 //设置字体高度，和宽度,0表示缺省宽度
//	m_Room.SetColTextColor(1,RGB(255,255,100)); //设置列文本颜色
//	m_Room.SetColTextColor(2,RGB(255,255,100)); //设置列文本颜色
//	m_Room.SetColTextColor(3,RGB(255,255,100)); //设置列文本颜色
//	m_RoomStyleList.SetItemTextColor(3,1,RGB(255,0,0));  //设置单元格字体颜色
    m_Room.InsertColumn(0,"Index",LVCFMT_LEFT,0);
    m_Room.InsertColumn(1,"门牌号",LVCFMT_CENTER,Rect.Width()/12);
    m_Room.InsertColumn(2,"楼座楼层",LVCFMT_CENTER,Rect.Width()/12);
    m_Room.InsertColumn(3,"房类",LVCFMT_CENTER,Rect.Width()/12);
    m_Room.InsertColumn(4,"基本房态",LVCFMT_CENTER,Rect.Width()/12);
    m_Room.InsertColumn(5,"临时房态",LVCFMT_CENTER,Rect.Width()/3);
    m_Room.InsertColumn(6,"设备",LVCFMT_CENTER,Rect.Width()/3);
///////////////////////////////////////////////////////////////////////////////////////////////////////
    //新建立一个右键弹出菜单在OnCommand中响应
    InitPopMenu();

	//初始化查询条件 
	m_Condition.nRoomType = -1;
	m_Condition.nFloor = -1;
	m_Condition.nBuilding = -1;

}

void CMainRealStatusDlg::ReloadRoomStateInfo()
{

}
/**********************************************************************************
$功能：初始化弹出菜单
//===================================================
***********************************************************************************/
void CMainRealStatusDlg::InitPopMenu()
{
   /*CMenu *popMenu;
   popMenu = new CMenu();
   popMenu->CreatePopupMenu();
   popMenu->AppendMenu(MF_CHECKED | MF_STRING,IDM_POPMENU_BASE+0x10,"列表模式");//添加菜单项
   popMenu->AppendMenu(MF_UNCHECKED |MF_STRING,IDM_POPMENU_BASE+0x11,"编辑模式");//添加菜单项
   */

   m_pMenu = new CMenu();       //m_pMenu->CreateMenu();
   m_pMenu->CreatePopupMenu();
   //显示外观模式显示切换菜单
   //m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE,"图标模式");//添加菜单项(Offset 0x00)
   //m_pMenu->AppendMenu(MF_SEPARATOR);//添加分隔线
   //先中房间的操作界面
   m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE+1,"客房");
   m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE+2,"房态");
   m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE+3,"设备");


   //m_pMenu->AppendMenu(MF_STRING|MF_GRAYED,IDM_POPMENU_BASE+0x10,"客房信息");//无效










   //m_pMenu->AppendMenu(MF_POPUP,(UINT)popMenu->m_hMenu,"切换");//添加菜单项
   //m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE+0x20,"信息");//添加菜单项
   //m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE+0x30,"删除");//添加菜单项
}

void CMainRealStatusDlg::OnRclickRsRoomlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if(m_Room.GetItemCount())
	{
	  CPoint pt;
      GetCursorPos(&pt);
  	  m_pMenu->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);	
	}
	*pResult = 0;
}



BOOL CMainRealStatusDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
   // TODO: Add your specialized code here and/or call the base class
	UINT uMsg=LOWORD(wParam);
	int CurrentSelEntry = -1;
	int Result;
	PROMM_INFO_TRANSFER m_pArgument = NULL;
	switch(uMsg)
	{
		case  IDM_POPMENU_BASE:      //表示显示的切换
				if(lReportStyle == FALSE)   //从图标切换到列表
				{
				 m_Room.ModifyStyle(LVS_ICON,LVS_REPORT);
				 m_pMenu->ModifyMenu(0,MF_STRING | MF_BYPOSITION,IDM_POPMENU_BASE,"图标模式");
				 lReportStyle = TRUE;
				}
				else
				{
				  m_Room.ModifyStyle(LVS_REPORT,LVS_ICON);
				  m_pMenu->ModifyMenu(0,MF_STRING | MF_BYPOSITION,IDM_POPMENU_BASE,"列表模式");

				  lReportStyle = FALSE;
				}
				break;
		case  IDM_POPMENU_BASE+1:
		case  IDM_POPMENU_BASE+2:
		case  IDM_POPMENU_BASE+3:
			   
				for(Result=0; Result<m_Room.GetItemCount(); Result++)
				{
					if(m_Room.GetItemState(Result, LVIS_SELECTED) == LVIS_SELECTED )
					{
						CurrentSelEntry = Result;
						break;
					}
				}
				/////////////////////////////////////////////////////////////////////
				if(CurrentSelEntry != -1)
				{
					m_pArgument = new ROMM_INFO_TRANSFER;
					ZeroMemory(m_pArgument,sizeof(ROMM_INFO_TRANSFER));
					//===============================================================
					m_pArgument->pRoomEntry = (PVOID)m_Room.GetItemData(CurrentSelEntry);	//客房信息
					//得到客房的信息
					Result = GetOneRoomDetail(CurrentSelEntry,m_pArgument);
					//if(((PROOM_DETAIL_ENTRY)m_pArgument->pRoomEntry)->pBuffer == NULL)
					if(Result == 0)
						break;
					else
					{
						GolabRunStatus = GOLAB_THREAD_PAUSE;
						SuspendThread(hInquiryThread);
						C_ChannelFactory::CloseAllChannels();
						CallDetailModule(m_pArgument,&m_mysql,uMsg-IDM_POPMENU_BASE-1);
						//=============================================================
						//C_ChannelFactory::CloseAllChannels();
						ResumeThread(hInquiryThread);
						GolabRunStatus = GOLAB_THREAD_RUN;
					}

				}
				
				break;
		default:
				break;
	}
//==========================================================================================
	if(m_pArgument != NULL)
	{
		PROOM_DETAIL_ENTRY m_pRoomEntry = (PROOM_DETAIL_ENTRY)m_pArgument->pRoomEntry;
		if (m_pRoomEntry != NULL){
			if (m_pRoomEntry->pBuffer != NULL){
				delete[] m_pRoomEntry->pBuffer;
				m_pRoomEntry->pBuffer = NULL;
			}
		}

		//删除传输信息
		if(m_pArgument->peBuf != NULL)
			delete[] m_pArgument->peBuf;
		if(m_pArgument->psBuf != NULL)
			delete[] m_pArgument->psBuf;

		//delete[] m_pArgument;	
	}
	return CDialog::OnCommand(wParam, lParam);
}




void CMainRealStatusDlg::LoadFunModule()
{
//第一部分：加载房间详细情况的模块
	hRoomModule = LoadLibrary(RoomModuleName);
	if(hRoomModule == NULL)
	{
	 MessageBox("加载房间详情模块失改");
	 return;
	}
	//============================================================
	CallDetailModule = (AFX_CALLDETAILMODULE)GetProcAddress(hRoomModule,"CallDetailModule");









}


void CMainRealStatusDlg::RefresBuild()
{
	//先检查是否为空不是就清空
	if(m_Building.GetCount())
		m_Building.ResetContent();

	PBUILDING_ENTRY  m_pEntryInfo = NULL;		//楼座链表							//树链
	PBUILDING_ENTRY  m_pTempEntryInfo = NULL;
	ULONG	Result;				//查表的结果
	ULONG   RecordNum = 0;		//加入树中的索引
	//链接所有的记录到链表
	Result = (ULONG)GetBuildingRecord(&m_pEntryInfo,NULL);
	if(!Result || (m_pEntryInfo==NULL))
	{
		return;
	}
	m_Building.InsertString(0,"=所有楼座=");
	//增加到列表框中去
	while(RecordNum<Result)
	{
		RecordNum++;
		m_pTempEntryInfo = m_pEntryInfo->pNext;
		//m_Building.AddString(m_pEntryInfo->cName);
		m_Building.InsertString(RecordNum,m_pEntryInfo->cName);
		m_Building.SetItemData(RecordNum,(DWORD)m_pEntryInfo->dwEntryIndex);

		delete[] m_pEntryInfo;
		m_pEntryInfo = m_pTempEntryInfo;
	}
	m_Building.SetCurSel(0);
/////////////////////////////////////////////////////////////////////////////////
	RefreshFloor(MAX_FLOOR_NUMBER);
}

HBRUSH CMainRealStatusDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

	// TODO: Return a different brush if the default is not desired
	//return CreateSolidBrush(COLOR_BACKGROUND);//GetSysColor(COLOR_WINDOW));
	return hbr;
}

void CMainRealStatusDlg::LoadImageList()
{
   CImageList* pImageList;
   pImageList = new CImageList();
   pImageList->Create(104, 108, ILC_COLOR32, 0, 10);
 /*//如下是增加一副图片中的多个图标
 	// Create 256 color image lists
	HIMAGELIST hList = ImageList_Create(32,32, ILC_COLOR8 |ILC_MASK , 8, 1);
	m_cImageListNormal.Attach(hList);

	hList = ImageList_Create(16, 16, ILC_COLOR8 | ILC_MASK, 8, 1);
	m_cImageListSmall.Attach(hList);


	// Load the large icons
	CBitmap cBmp;
	cBmp.LoadBitmap(IDB_IMAGES_NORMAL);
	m_cImageListNormal.Add(&cBmp, RGB(255,0, 255));
	cBmp.DeleteObject();

	// Load the small icons
	cBmp.LoadBitmap(IDB_IMAGES_SMALL);
	m_cImageListSmall.Add(&cBmp, RGB(255,0, 255));

	// Attach them
	m_cListCtrl.SetImageList(&m_cImageListNormal, LVSIL_NORMAL);
	m_cListCtrl.SetImageList(&m_cImageListSmall, LVSIL_SMALL);
*/
 //方法1： 添加图标，图标可以随图像列表大小自动拉伸
 //pImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON1));
 //pImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON2));
 //=======================================================================================
 //方法2： 添加位图，并使黑色为透明色,如果图像列表大小和位图大小不一致可能会导致天添加失败
 //CBitmap bmp;
 //bmp.LoadBitmap(IDB_BITMAP1)
 //pImageList->Add(&bmp, RGB(0, 0, 0));
 //bmp.DeleteObject();
 //bmp.LoadBitmap(IDB_BITMAP2)
 //pImageList->Add(&bmp, RGB(0, 0, 0));
 //=======================================================================================
 //方法3： 添加位图，从文件外面加载
 HBITMAP hBitmap;
 CBitmap *pBitmap;
 CString FilePathName = "Image\\RealTimeStatus\\";
 pBitmap = new   CBitmap;
 // 从文件导入位图
 hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),FilePathName+"room_default.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 pBitmap->Attach(hBitmap);
 pImageList->Add(pBitmap, RGB(0,0,0));

 hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),FilePathName+"S0.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 pBitmap->Attach(hBitmap);
 pImageList->Add(pBitmap, RGB(0,0,0));
 hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),FilePathName+"S1.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 pBitmap->Attach(hBitmap);
 pImageList->Add(pBitmap, RGB(0,0,0));
 hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),FilePathName+"S2.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 pBitmap->Attach(hBitmap);
 pImageList->Add(pBitmap, RGB(0,0,0));
 hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),FilePathName+"S3.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 pBitmap->Attach(hBitmap);
 pImageList->Add(pBitmap, RGB(0,0,0));
 hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),FilePathName+"S4.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 pBitmap->Attach(hBitmap);
 pImageList->Add(pBitmap, RGB(0,0,0));
 hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),FilePathName+"S5.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
 pBitmap->Attach(hBitmap);
 pImageList->Add(pBitmap, RGB(0,0,0));


	






	
	
	
//	m_ImageList.Create(
   m_Room.SetImageList(pImageList,LVSIL_NORMAL);
}

//用于按要求更新客房列表信息
//传入的值为房类信息-1表示所有的其它表示房类ID
void CMainRealStatusDlg::RefreshQuickRoomList(const char* sFilter)
{
	PROOM_DETAIL_ENTRY m_pEntryInfo;
	ULONG	Result;
	ULONG   RecordNum = 0;
	CString str;

	GolabRunStatus = GOLAB_THREAD_PAUSE;
	CString		TempCash[MAX_COUNT * 2];
//==============================================================
	//第一次进入的时候没有数据部进行缓存
	if (m_Flag)
	{
		// 记录表格中的临时房态和空调设备信息，以便切换页面进行缓存
		for (int i = 0; i < m_Room.GetItemCount();i++)
		{
			TempCash[2*i] = m_Room.GetItemText(i,5);
			TempCash[2*i + 1] = m_Room.GetItemText(i,6);
		}
	}
		
	//先将列表框清空
	while(m_Room.GetItemCount())
	{
		m_pEntryInfo = (PROOM_DETAIL_ENTRY)m_Room.GetItemData(0);
		delete [] (PROOM_DETAIL_ENTRY)m_pEntryInfo;
		m_Room.DeleteItem(0);
	}
	m_pEntryInfo = NULL;
	//链接所有的记录到链表
	Result = (ULONG)GetRoomRecord(&m_pEntryInfo,sFilter);
	if(!Result || m_pEntryInfo==NULL)
	{
		hMutex.Unlock();
		SetDlgItemInt(IDC_ROOM_NUM,Result);
		return;
	}
//增加到列表框中去		
	while(RecordNum<Result)
	{
		InsertOneRoomEntry(m_pEntryInfo);
		m_pEntryInfo = m_pEntryInfo->pNext;
		RecordNum++;
	}

	// 第一次没缓存，所以不会往表格中写内容
	if (m_Flag)
	{
		// 将缓存放到列表中
		for (int i = 0; i < m_Room.GetItemCount();i++)
		{
			m_Room.SetItemText(i,5,TempCash[2*i]);
			m_Room.SetItemText(i,6,TempCash[2*i + 1]);
		}
	}
	
	GolabRunStatus = GOLAB_THREAD_RUN;
//=========================================================================
	SetDlgItemInt(IDC_ROOM_NUM,Result);
	m_Flag = TRUE;
}

void CMainRealStatusDlg::ReleaseAllMemory()
{
//清空房类链表
	if(pRoomTypeValue != NULL)
		delete[] pRoomTypeValue;
}

void CMainRealStatusDlg::InsertOneRoomEntry(PVOID lParam)
{
	PROOM_DETAIL_ENTRY pRoomInfo = (PROOM_DETAIL_ENTRY)lParam;
	int CurrentEntry = m_Room.GetItemCount();
	CString str;
	//////////////////////////////////////////////////////////
	m_Room.InsertItem(CurrentEntry,NULL);
	//门牌号
	str.Format("%02d%02d",pRoomInfo->bFloorNum,pRoomInfo->bRoomNum);
	m_Room.SetItemText(CurrentEntry,1,str);
	//楼座楼层
	str.Format("%c-%02d",pRoomInfo->bBuildingNum,pRoomInfo->bFloorNum);
	m_Room.SetItemText(CurrentEntry,2,str);
	//房类
	GetRoomTypeString(pRoomInfo->dwRoomTypeID,str);
	m_Room.SetItemText(CurrentEntry,3,str);
	//基本房态
	str = "空置";
	m_Room.SetItemText(CurrentEntry,4,str);

	//临时房态
	str = "空";
	m_Room.SetItemText(CurrentEntry,5,str);

	//设备
	str = "空";
	m_Room.SetItemText(CurrentEntry,6,str);

	m_Room.SetItemData(CurrentEntry,(DWORD_PTR)pRoomInfo);
}

bool CMainRealStatusDlg::GetRoomTypeString(unsigned long Value,CString &str)
{
	int RoomTypeNum;
	int i;
	RoomTypeNum = m_RoomType.GetItemCount();
	str.Empty();
	for(i=0;i<RoomTypeNum;i++)
	{
		if(Value == pRoomTypeValue[i])
			break;
	}
	
	if(i>RoomTypeNum)
	{
	   str.Format("%d-%d",i,RoomTypeNum);
	   return FALSE;
	}
///////////////////////////////////////////////////
	TC_ITEM iItemTC; 
	iItemTC.mask=TCIF_TEXT|TCIF_IMAGE; 
	iItemTC.pszText=(LPSTR)(LPCSTR)str; 
	iItemTC.cchTextMax = MAX_PATH; 
	m_RoomType.GetItem(i,&iItemTC); 

	return TRUE;
}


//*********************************************************
//更新房类信息
//=========================================================
//从房态表中读出所有的房态名，并将该类型存放在名称对应的
//下标的pRoomTypeValue[]中表示房态的主键值
//======================================================
void CMainRealStatusDlg::RefreshRoomType()
{
	ULONG	Result;
	ULONG   RecordNum = 0;
	PROOM_TYPE_ENTRY	m_pEntryInfo = NULL;	
	PROOM_TYPE_ENTRY	m_pTempEntryInfo = NULL;	
	//先将列表框清空
	if(m_RoomType.GetItemCount())
	{
		delete[] pRoomTypeValue;
		m_RoomType.DeleteAllItems();
	}
	//链接所有的记录到链表
	Result = (ULONG)GetRoomTypeRecord(&m_pEntryInfo,NULL);
	if(!Result)
		return;

	pRoomTypeValue = new DWORD[Result+1];
	ZeroMemory(pRoomTypeValue,sizeof(DWORD)*(Result+1));
	m_RoomType.InsertItem(RecordNum,"所有类型");
	pRoomTypeValue[0] = -1;
	//增加到列表框中去		
	while(RecordNum<Result)
	{
		RecordNum++;
		m_pTempEntryInfo = m_pEntryInfo->pNext;
		m_RoomType.InsertItem(RecordNum,m_pEntryInfo->cName);
		pRoomTypeValue[RecordNum] = m_pEntryInfo->dwEntryIndex;

		delete[] m_pEntryInfo;
		m_pEntryInfo = m_pTempEntryInfo;
	}
}

void CMainRealStatusDlg::RefreshFloor(DWORD dwMaxFloor)
{
	DWORD Index;
	CString str;
	if(m_Floor.GetCount())
		m_Floor.ResetContent();
	m_Floor.InsertString(0,"=所有楼层=");
	for(Index =0;Index<dwMaxFloor+1;Index++)
	{
		str.Format("楼层[%d]",Index+1);
		m_Floor.InsertString(Index+1,str);
	}
	m_Floor.SetCurSel(0);
}

void CMainRealStatusDlg::OnSelchangeComboBuilding() 
{
	// TODO: Add your control notification handler code here
	m_Condition.nBuilding = (int)m_Building.GetItemData(m_Building.GetCurSel());
	if(m_Condition.nBuilding == 0)
		m_Condition.nBuilding = -1;
	ConvertSearchCondition();
}

void CMainRealStatusDlg::OnSelchangeComboFloor() 
{
	// TODO: Add your control notification handler code here
	m_Condition.nFloor = m_Floor.GetCurSel();
	if(m_Condition.nFloor == 0)
		m_Condition.nFloor = -1;

	ConvertSearchCondition();	
}

void CMainRealStatusDlg::OnSelchangeRsRoomtypetab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_Condition.nRoomType = pRoomTypeValue[m_RoomType.GetCurSel()];
	ConvertSearchCondition();	
	*pResult = 0;
}

void CMainRealStatusDlg::ConvertSearchCondition()
{
	CString str,temp;
	BOOL status = FALSE;
	str.Empty();
//////////////////////////////////////////////////////////////////////////
	if(m_Condition.nBuilding != -1)		//楼座
	{
		str.Format("BuildingID=%d",m_Condition.nBuilding);
		status = TRUE;
	}

	if(m_Condition.nFloor != -1)		//楼层
	{
		if(status == TRUE)
			temp.Format(" AND FloorNum=%d",m_Condition.nFloor);
		else
			temp.Format("FloorNum=%d",m_Condition.nFloor);
		status = TRUE;
		str = str + temp;
	}

	if(m_Condition.nRoomType != -1)		//房态
	{
		if(status == TRUE)
			temp.Format(" AND RoomtypeID=%d",m_Condition.nRoomType);
		else
			temp.Format("RoomtypeID=%d",m_Condition.nRoomType);
		status = TRUE;
		str = str + temp;
	}

	if(str.IsEmpty())
	{
		RefreshQuickRoomList(NULL);
	}
	else
	{
		m_Flag = FALSE;
		RefreshQuickRoomList(str);
	}
}


//查询所有的房态线程
UINT CMainRealStatusDlg::InquiryListRoomThread(PVOID lParam)
{
#if 1
	CMainRealStatusDlg *m_Dlg = (CMainRealStatusDlg *)lParam;
	int	CurrentEntry = 0;		//当前的列表索引
	PROOM_DETAIL_ENTRY m_pEntryInfo = NULL;
	//InitDataTransferLay();			//初始化数据传输
	int Result = 0;
	int airNum = 0;
	//fp = fopen("CCTV.log","wt");		//开记录文件
	//fprintf(fp,"InquiryListRoomThread Start\n");
	//////////////////////////////////////////////////////////////////////////
	while(GolabRunStatus != GOLAB_THREAD_EXIT)	//只要不为退出就一直在这执行
	{
		if(GolabRunStatus == GOLAB_THREAD_PAUSE)
		{
			SuspendThread(hInquiryThread);
		}
		//==============================================================
		hMutex.Lock();		//取一条数据
		if(!m_Dlg->m_Room.GetItemCount())		//如果列表为空不要做
		{
			hMutex.Unlock();	
			continue;
		}
		//如果当前的比之前的大则从头开始
		if(m_Dlg->m_Room.GetItemCount() <= CurrentEntry)
			CurrentEntry = 0;
		//*******************************************************
		m_pEntryInfo = (PROOM_DETAIL_ENTRY)m_Dlg->m_Room.GetItemData(CurrentEntry);			//
		//*******************************************************
		hMutex.Unlock();	
		//==============================================================
		Result = m_Dlg->QuirySelRoomInfo(m_pEntryInfo);
		CString		AirStatus;
		if(Result != 0)		//加入一个指令到队列中是否OK
		{
			m_Dlg->m_Room.SetItemText(CurrentEntry,4,"在线");
			CString str;
			//临时房态
			str = TempStatus(m_pEntryInfo,airNum,AirStatus);
			m_Dlg->m_Room.SetItemText(CurrentEntry,5,str);
			//Sleep(50);
			// 空调设备
			//str = AirCondition(m_pEntryInfo,airNum);
			m_Dlg->m_Room.SetItemText(CurrentEntry,6,AirStatus);
			//Sleep(200);
		}
		else
		{
			m_Dlg->m_Room.SetItemText(CurrentEntry,4,"离线");
			m_Dlg->m_Room.SetItemText(CurrentEntry,5,"空");
			m_Dlg->m_Room.SetItemText(CurrentEntry,6,"空");
		}
		//Sleep(200);
		CurrentEntry++;
	}
	//fprintf(fp,"InquiryListRoomThread End\n");
	GolabRunStatus = GOLAB_THREAD_IDLE;		//退出了就将状态清空
	hInquiryCompleteEvent.SetEvent();
	//fprintf(fp,"InquiryListRoomThread Exit\n");
	//fclose(fp);
	hMutex.Lock();
#endif
	return 1;
}

CString CMainRealStatusDlg::TempStatus(PVOID lParam,int &airNum,CString &AirStatus)
{
	CString str;
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
	PROOM_DETAIL_ENTRY m_pRoomEntry = reinterpret_cast<PROOM_DETAIL_ENTRY>(lParam);
	// TODO: Add your control notification handler code here
	if((pPack == NULL) || (m_pRoomEntry == NULL))
	{
		delete pPack;
		delete[] pBuf;
		return NULL;
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
	if (0 == nRevLength)
	{
		delete pPack;
		delete[] pBuf;
		str = "空";
		AirStatus = "空";
		return str;
	}
	// 同时读取空调状态
	str = WriteTempStatusToList(pBuf,airNum,AirStatus);

	delete pPack;
	delete[] pBuf;
	return str;
}

CString CMainRealStatusDlg::AirCondition(PVOID lParam,int &airNum)
{
	//CString str;
	//DWORD nBytes,nRevLength;
	//DWORD IpAddress;
	//PBYTE pBuf = NULL;
	//DWORD dwRtua = 10550;
	//WORD  wMstaAndSeq = 0x005E;
	//PRCU_ARG_AIR_GET_REQ_PACK_021X pPack = NULL;
	//pPack = new RCU_ARG_AIR_GET_REQ_PACK_021X;
	//memset(pPack,0,sizeof(RCU_ARG_AIR_GET_REQ_PACK_021X));

	//nRevLength = 256;
	//pBuf = new BYTE[nRevLength];
	//memset(pBuf,0,nRevLength);
	//PROOM_DETAIL_ENTRY m_pRoomEntry = reinterpret_cast<PROOM_DETAIL_ENTRY>(lParam);;
	//// TODO: Add your control notification handler code here
	//if((pPack == NULL) || (m_pRoomEntry == NULL))
	//	return NULL;
	//nBytes = GetAirConditionPacket(pPack,airNum);
	////RTUA
	//pPack->dwRtua = DWORD2_BCD(dwRtua);
	//pPack->wMstaAndSeq = 0x005E;
	////========================================================================			
	//pPack->sPostFrame.bCS = Crc8((PBYTE)pPack,nBytes-1);
	////====================================================================
	//IpAddress = inet_addr(m_pRoomEntry->sIpAddress);
	//IpAddress = ToLittleEndian(IpAddress);

	//nRevLength = SendDataWithResponse((PBYTE)pPack,nBytes,\
	//	pBuf,nRevLength,\
	//	IpAddress,m_pRoomEntry->dwPort);
	////=======================================================

	//if (0 == nRevLength)
	//{
	//	str = "空";
	//	return str;
	//}

	//str = WriteAirConditionToList(pBuf);	

	//delete[] pPack;
	//delete[] pBuf;
	//return str;
	return NULL;
}

CString CMainRealStatusDlg::WriteAirConditionToList(LPVOID lParam)
{
	PRCU_ARG_AIR_GET_RES_PACK_021X pPack = reinterpret_cast<PRCU_ARG_AIR_GET_RES_PACK_021X>(lParam);
	CString str;
	if ( NULL == pPack)
	{
		str = "空";
		return str;
	}
	
	//季节模式
	/*if (!pPack->bContent[0])
	{
		str = "季节模式：冬季 ";
	}
	else
	{
		str = "季节模式：夏季 ";
	}*/

	if (!pPack->bContent[1])
	{
		str += "工作模式：制热 ";
	}
	else
	{
		str += "工作模式：制冷 ";
	}

	str += "空调设置温度：";
	CString tempSetting;
	tempSetting.Format("%d",pPack->bContent[2]);
	str += tempSetting;
	str += "℃ ";

	str += "房间温度：";
	CString temp;
	temp.Format("%d",pPack->bContent[3]);
	str += temp;
	str += "℃ ";

	int fan = pPack->bContent[4];
	switch (fan)
	{
	case FANCLOSE:
		str += "空调风速：关";
		break;
	case FANLOW:
		str += "空调风速：低速";
		break;
	case FANMIDDLE:
		str += "空调风速：中速";
		break;
	case FANHEIGH:
		str += "空调风速：高速";
		break;
	default:
		break;
	}
	return str;
}

CString CMainRealStatusDlg::WriteTempStatusToList(LPVOID lParam,int &airNum,CString &AirStatus)
{
	PRCU_ARG_GET_RES_PACK_0202 pPack = reinterpret_cast<PRCU_ARG_GET_RES_PACK_0202>(lParam);
	CString str;
	if (NULL == pPack)
	{
		str = "空";
		return str;
	}
	int i;
	for (i = 1; i < 150;i =i + 10)
	{
		if (AIRTYPE == pPack->bContent[i])
		{
			airNum = pPack->bContent[i - 1];
			break;
		}
	}

	AirStatus = "";
	if (pPack->bContent[i+2])
	{
		AirStatus += "工作模式：制热 ";
	}
	else
	{
		AirStatus += "工作模式：制冷 ";
	}

	AirStatus += "空调设置温度：";
	CString tempSetting;
	tempSetting.Format("%d",pPack->bContent[i+3]);
	AirStatus += tempSetting;
	AirStatus += "℃ ";

	AirStatus += "房间温度：";
	CString temp;
	temp.Format("%d",pPack->bContent[i+4]);
	AirStatus += temp;
	AirStatus += "℃ ";

	int fan = pPack->bContent[i+5];
	switch (fan)
	{
	case FANCLOSE:
		AirStatus += "空调风速：关";
		break;
	case FANLOW:
		AirStatus += "空调风速：低速";
		break;
	case FANMIDDLE:
		AirStatus += "空调风速：中速";
		break;
	case FANHEIGH:
		AirStatus += "空调风速：高速";
		break;
	default:
		break;
	}
	
	// 以下为获取config.txt的路径，否则会变成Source图片资源的路径，发生读取文件失败
	char Path[MAX_PATH];
	ZeroMemory(Path,MAX_PATH);
	GetCurrentDirectory(MAX_PATH,Path);
	CString pathStr;
	pathStr = Path;
	CString fileName = "\\config.txt";
	CString fileNameWithPath;
	/*CString source = "\\Source";
	CString OperatorCFG = "\\OperatorCFG";
	int pos = pathStr.Find(source);
	if (pos < 0)
	{
		if (pathStr.Find(OperatorCFG) > 0)
		{
			pathStr.Replace(OperatorCFG,"");
		}
		fileNameWithPath.Format("%s%s",pathStr,fileName);
	}
	else
	{
		pathStr.Replace(source,"");
		fileNameWithPath.Format("%s\\%s",pathStr,fileName);
	}*/
	fileNameWithPath = pathStr + fileName;

	CStdioFile file;

	CFileException fileException;

	if(file.Open(fileNameWithPath,CFile::typeText|CFile::modeRead),&fileException)
	{

		file.ReadString(str);
	}
	else
	{
		TRACE("Can't open file %s,error=%u\n",fileName,fileException.m_cause);
	}

	char tempStr[16];
	for (int i = 0;i < str.GetLength();i++)
	{
		tempStr[i] = str[i];
	}

	CString strContent;
	if ((pPack->bContent[2] & 0x01) && ('0' != tempStr[0]))
	{
		strContent = "紧急按钮已按下 ";
	}
	if (!(pPack->bContent[2] & 0x01) && ('0' != tempStr[0]))
	{
		strContent = "紧急按钮未按下 ";
	}

	if ((pPack->bContent[2] & (0x01 << 1)) && ('0' != tempStr[1]))
	{
		strContent += "门卡未插入 ";
	}
	if (!(pPack->bContent[2] & (0x01 << 1)) && ('0' != tempStr[1]))
	{
		strContent += "门卡已插入 ";
	}

	if ((pPack->bContent[2] & (0x01 << 2)) && ('0' != tempStr[2]))
	{
		strContent += "大门开 ";
	} 
	if (!(pPack->bContent[2] & (0x01 << 2)) && ('0' != tempStr[2]))
	{
		strContent += "大门关 ";
	}

	if ((pPack->bContent[2] & (0x01 << 3)) && ('0' != tempStr[3]))
	{
		strContent += "总电源开 ";
	} 
	if (!(pPack->bContent[2] & (0x01 << 3)) && ('0' != tempStr[3]))
	{
		strContent += "总电源开 ";
	}

	if ((pPack->bContent[2] & (0x01 << 4)) && ('0' != tempStr[4]))
	{
		strContent += "清理房间开 ";
	} 
	if (!(pPack->bContent[2] & (0x01 << 4)) && ('0' != tempStr[4]))
	{
		strContent += "清理房间关 ";
	}

	if ((pPack->bContent[2] & (0x01 << 5)) && ('0' != tempStr[5]))
	{
		strContent += "洗衣服务开 ";
	} 
	if (!(pPack->bContent[2] & (0x01 << 5)) && ('0' != tempStr[5]))
	{
		strContent += "洗衣服务关 ";
	}

	if ((pPack->bContent[2] & (0x01 << 6)) && ('0' != tempStr[6]))
	{
		strContent += "请勿打扰开 ";
	} 
	if (!(pPack->bContent[2] & (0x01 << 6)) && ('0' != tempStr[6]))
	{
		strContent += "请勿打扰关 ";
	}

	if ((pPack->bContent[2] & (0x01 << 7)) && ('0' != tempStr[7]))
	{
		strContent += "请稍后开 ";
	} 
	if (!(pPack->bContent[2] & (0x01 << 7)) && ('0' != tempStr[7]))
	{
		strContent += "请稍后关 ";
	}

	if ((pPack->bContent[3] & 0x01) && ('0' != tempStr[8]))
	{
		strContent += "红外检测有人 ";
	} 
	if (!(pPack->bContent[3] & 0x01) && ('0' != tempStr[8]))
	{
		strContent += "红外检测无人 ";
	}

	if ((pPack->bContent[3] & (0x01 << 1)) && ('0' != tempStr[9]))
	{
		strContent += "有请求服务 ";
	} 
	if (!(pPack->bContent[3] & (0x01 << 1)) && ('0' != tempStr[9]))
	{
		strContent += "无请求服务 ";
	}

	if ((pPack->bContent[3] & (0x01 << 2)) && ('0' != tempStr[10]))
	{
		strContent += "阳台门开 ";
	} 
	if (!(pPack->bContent[3] & (0x01 << 2)) && ('0' != tempStr[10]))
	{
		strContent += "阳台门关 ";
	}

	if ((pPack->bContent[3] & (0x01 << 3)) && ('0' != tempStr[11]))
	{
		strContent += "夜床开 ";
	} 
	if (!(pPack->bContent[3] & (0x01 << 3)) && ('0' != tempStr[11]))
	{
		strContent += "夜床关 ";
	}

	if ((pPack->bContent[3] & (0x01 << 4)) && ('0' != tempStr[12]))
	{
		strContent += "保险箱开 ";
	} 
	if (!(pPack->bContent[3] & (0x01 << 4)) && ('0' != tempStr[12]))
	{
		strContent += "保险箱关 ";
	}

	if ((pPack->bContent[3] & (0x01 << 5)) && ('0' != tempStr[13]))
	{
		strContent += "请求退房开 ";
	} 
	if (!(pPack->bContent[3] & (0x01 << 5)) && ('0' != tempStr[13]))
	{
		strContent += "请求退房关 ";
	}

	if ((pPack->bContent[3] & (0x01 << 6)) && ('0' != tempStr[14]))
	{
		strContent += "结账开 ";
	} 
	if (!(pPack->bContent[3] & (0x01 << 6)) && ('0' != tempStr[14]))
	{
		strContent += "结账关 ";
	}

	if ((pPack->bContent[3] & (0x01 << 7)) && ('0' != tempStr[15]))
	{
		strContent += "维修中开";
	} 
	if (!(pPack->bContent[3] & (0x01 << 7)) && ('0' != tempStr[15]))
	{
		strContent += "维修中关";
	}
	return strContent;
}

void CMainRealStatusDlg::OnDestroy() 
{
	// TODO: Add your message handler code here
	//清空列表框的内容
	//PROOM_DETAIL_ENTRY pRoomInfo;
	//hMutex.Lock();		//取一条数据
	//while(m_Room.GetItemCount())
	//{
	//	pRoomInfo = (PROOM_DETAIL_ENTRY)m_Room.GetItemData(0);

	//	delete [] (PROOM_DETAIL_ENTRY)pRoomInfo;
	//	m_Room.DeleteItem(0);
	//}	
	//hMutex.Unlock();		//取一条数据
	//
	CDialog::OnDestroy();
}


int CMainRealStatusDlg::QuirySelRoomInfo(PVOID lParam)
{
	/*PROMM_INFO_TRANSFER m_pTrans = (PROMM_INFO_TRANSFER)lParam;
	PROOM_DETAIL_ENTRY m_pEntryInfo = (PROOM_DETAIL_ENTRY)m_pTrans->pRoomEntry;*/
	PROOM_DETAIL_ENTRY m_pEntryInfo = (PROOM_DETAIL_ENTRY)lParam;
	//=========================================================================
	DATA_TRANS_PRE  PreBuf;		//发送的前缀
	DWORD	IpAddress;			//Ip地址
	USHORT	nPort;				//端口	
	int Result = -1;
	PUCHAR pBuf = NULL;
	DWORD pLength = 0;
//******************************************************************************
	if(m_pEntryInfo == NULL)
	{
		Result = 0;
		return Result;
	}
	//=======================================================================
	IpAddress = BIG_ENDIAN_DWORD(inet_addr(m_pEntryInfo->sIpAddress));
	nPort = (USHORT)m_pEntryInfo->dwPort;
	/////////////////////////////////////////////////////////////////////////
	FillPreBuffer(&PreBuf,CMD_QUEST_ALL_INFO,(USHORT)m_pEntryInfo->bFloorNum,(USHORT)m_pEntryInfo->bRoomNum,0,0);
	/////////////////////////////////////////////////////////////////////////
//	Result = QuiryHostInNet(&PreBuf,IpAddress,nPort,NULL,0,m_pEntryInfo->pBuffer,m_pTrans->pTotalLength);	
	
	//************************************************************************
	/*if(m_pTrans->pTotalLength > 0)
		RecordBuffer("RecvBuf.v",m_pEntryInfo->pBuffer,m_pTrans->pTotalLength);*/

	return Result;
}

int CMainRealStatusDlg::GetOneRoomDetail(int EntryIndex,PVOID lParam)
{
	PROMM_INFO_TRANSFER m_pTransInfo = (PROMM_INFO_TRANSFER)lParam;
	PROOM_DETAIL_ENTRY m_pRoomEntry = (PROOM_DETAIL_ENTRY)m_pTransInfo->pRoomEntry;

	int Result = 0;
	if((lParam == NULL) || (EntryIndex == -1))
		return Result;
	DWORD	dwRtua = 10550;
	WORD	wMsta = 0x005E;
	DWORD IpAddress;
/////////////////////////////////////////////////////////////////////////////////////
	BYTE pSendBuf[256];
	WORD DataEntry[20];
	int DataEntryNum = 0;

	DWORD nBytes = 0;
	memset(pSendBuf,0,256);


	memset(DataEntry,0,20);
	DataEntry[DataEntryNum++] = 0x0106;
	DataEntry[DataEntryNum++] = 0x0107;
	DataEntry[DataEntryNum++] = 0x0202;
//================================================================================
	nBytes = QuiryRCUFramePack(pSendBuf,DataEntry,DataEntryNum,\
				dwRtua,wMsta);

	m_pRoomEntry->pBuffer = new BYTE[256];
	memset(m_pRoomEntry->pBuffer,0,256);

	//====================================================================
	IpAddress = inet_addr(m_pRoomEntry->sIpAddress);
	IpAddress = ToLittleEndian(IpAddress);

	nBytes = SendDataWithResponse((PBYTE)pSendBuf,nBytes,\
		m_pRoomEntry->pBuffer,256,\
		IpAddress,(USHORT)m_pRoomEntry->dwPort);
	if (0 == nBytes)
	{
		MessageBox("获取房间信息失败，请重新配置房间IP和端口号！","警告");
	}
	return nBytes;
}

UINT CMainRealStatusDlg::GetRoomInfoThread(PVOID lParam)
{
	PROMM_INFO_TRANSFER m_pTransInfo = (PROMM_INFO_TRANSFER)lParam;
	CMainRealStatusDlg *m_Dlg = (CMainRealStatusDlg *)m_pTransInfo->ParentDlg;
	PROOM_DETAIL_ENTRY m_pRoomEntry = (PROOM_DETAIL_ENTRY)m_pTransInfo->pRoomEntry;
	int Result = -1;
	m_Dlg->pLoadDlg->SetTimer(0,1000,NULL);		//启动超时计算
//======================================================================================
//第一步：得到客房的Buffer长度(以及返回RCU值)
	m_pTransInfo->RCU = GetBufferLengthFromRoom(m_pTransInfo->pRoomEntry,m_pTransInfo->eLength,m_pTransInfo->sLength);
	m_pTransInfo->pTotalLength = m_pTransInfo->eLength * EQUMENT_DATA_SIZE + m_pTransInfo->sLength * STATUS_DATA_SIZE;
	if(m_pTransInfo->RCU != -1)		//有对应的RCU
	{//往下继续
		m_pRoomEntry->pBuffer = new BYTE[m_pTransInfo->pTotalLength];
		if(m_pRoomEntry->pBuffer == NULL)
			return -1;
		ZeroMemory(m_pRoomEntry->pBuffer,m_pTransInfo->pTotalLength);
		//==================================================
		if(m_pTransInfo->eLength > 0)
			m_pRoomEntry->pEquipBlock = m_pRoomEntry->pBuffer;
		else
			m_pRoomEntry->pEquipBlock = NULL;

		if(m_pTransInfo->sLength > 0)
			m_pRoomEntry->pStatusBlock = m_pRoomEntry->pBuffer+(m_pTransInfo->sLength * STATUS_DATA_SIZE);
		else
			m_pRoomEntry->pStatusBlock = NULL;
	}
//========================================================================================================
	Result = m_Dlg->QuirySelRoomInfo(m_pTransInfo);					//请求客房的信息
//========================================================================================================	
	m_Dlg->pLoadDlg->SetCurrentStatus(FALSE);
	m_Dlg->pLoadDlg->KillTimer(0);

	//m_Dlg->pLoadDlg->SetDlgItemText(IDCANCEL,"OK");
	m_Dlg->pLoadDlg->SendMessage(WM_CLOSE);
	//m_Dlg->pLoadDlg->DestroyWindow();
//=====================================================================================
	return 1;
}

BOOL CMainRealStatusDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;	
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMainRealStatusDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
	if(bShow == TRUE)
	{//初始化各个控件
	//更新房类信息(从数据库中读回)
		RefreshRoomType();
	//更新楼层信息
		RefresBuild();
	//更新客房列表
		ConvertSearchCondition();
//*******************************************************************
		//fp = fopen("CCTV.log","wt");		//开记录文件

	
	
	
















	}
	else
	{//删除各个控件
	
	










		//fclose(fp);
	}
}
