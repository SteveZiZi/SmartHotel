// MainRealStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include <afxmt.h>
#include "Management.h"
#include "MainRealStatusDlg.h"

#include "..\\CommSource\\Project\\DataTransferLay.h"		//���ݴ����
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
	PVOID wParam;				//��ŶԻ���ָ���
	
	PVOID lParam;				//��ŷ�����Ŀ��

	PVOID pGolabRoomInfo;
}QUIRY_INFO,*PQUIRY_INFO;

/////////////////////////////////////////////////////////////////////////////////
//�Ҽ����������˵���
#define  IDM_POPMENU_BASE     10
// CMainRealStatusDlg dialog
CMutex hMutex(FALSE,NULL,NULL);								//�������
CEvent hRoomEntryEvent(FALSE,FALSE,NULL,NULL);				//�Ҽ�����ͷ�����
CEvent hInquiryCompleteEvent(FALSE,FALSE,NULL,NULL);		//��ѯ�������¼�
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
	//ɾ���˵�
	delete[] (CMenu *)m_pMenu;
	ReleaseAllMemory();
	//�ͷſͷ�ģ��
	if(hRoomModule != NULL)
		FreeLibrary(hRoomModule);
//�˳��߳�
	GolabRunStatus = GOLAB_THREAD_EXIT;							//�趨Ҫ�˳�
	if (hInquiryThread != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hInquiryThread);
		hInquiryThread = INVALID_HANDLE_VALUE;
	}
	//fprintf(fp,"�����˳��¼�\n");
	//WaitForSingleObject(hInquiryCompleteEvent,INFINITE);		//�Ȳ�ѯ�¼�����
	//fprintf(fp,"�˳��¼��ȵ�\n");
//�˳����ݴ���
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
	AdjustItemPosition();   //�����ؼ�λ��
	//���ظ���ģ����Ϣ
    LoadFunModule();
//��ʼ�����ؼ�����ۼ���Ŀ
    InitAllItem();
	//RefreshQuickRoomList(NULL);
////////////////////////////////////////////////////////
	//���ز�ѯ�߳�
	if(GolabRunStatus == GOLAB_THREAD_IDLE)
	{
		GolabRunStatus = GOLAB_THREAD_RUN;
		hInquiryThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)InquiryListRoomThread,this,0,NULL);
		/*if(hInquiryThread != INVALID_HANDLE_VALUE)
			CloseHandle(hInquiryThread);
		else
			GolabRunStatus = GOLAB_THREAD_IDLE;*/
	}
	//���·�̬��Ϣ
	//ReloadRoomStateInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainRealStatusDlg::AdjustItemPosition()
{
    CRect pRect;
	::GetClientRect(hParentHwnd,&pRect);
    //��ǩ�ؼ��Ĵ�С
	::MoveWindow(GetDlgItem(IDC_RS_ROOMTYPETAB)->GetSafeHwnd(),100,0,pRect.Width()-100,30,TRUE);

	//�б��Ĵ�С
    ::MoveWindow(GetDlgItem(IDC_RS_ROOMLIST)->GetSafeHwnd(),100,25,pRect.Width()-320,pRect.Height()-25,TRUE);





	//MessageBox(str);
}

void CMainRealStatusDlg::InitAllItem()
{
//���ȳ�ʼ���ͷ��б�����Ŀ��Ϣ
  	CRect Rect;
    ::GetClientRect(m_Room,&Rect);
    DWORD Style = m_Room.GetExtendedStyle();
    Style |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
    m_Room.SetExtendedStyle(Style);

//	m_RoomStyleList.SetColColor(0,RGB(10,150,20)); //�����б���ɫ
//	m_RoomStyleList.SetColColor(2,RGB(30,100,90)); //�����б���ɫ
//	m_Room.SetBkColor(RGB(50,10,10));        //���ñ���ɫ
//	m_RoomStyleList.SetItemColor(1,1,RGB(100,100,10)); //����ָ����Ԫ����ɫ
	m_Room.SetRowHeigt(25);               //�����и߶�
	m_Room.SetHeaderHeight(1.5);          //����ͷ���߶�
	m_Room.SetHeaderFontHW(16,0);         //����ͷ������߶�,�Ϳ��,0��ʾȱʡ������Ӧ 
	m_Room.SetHeaderTextColor(RGB(255,200,100)); //����ͷ��������ɫ
//	m_RoomStyleList.SetTextColor(RGB(0,255,255));    //�����ı���ɫ
//	m_Room.SetHeaderBKColor(100,255,100,8); //����ͷ������ɫ
	m_Room.SetFontHW(15,0);                 //��������߶ȣ��Ϳ��,0��ʾȱʡ���
//	m_Room.SetColTextColor(1,RGB(255,255,100)); //�������ı���ɫ
//	m_Room.SetColTextColor(2,RGB(255,255,100)); //�������ı���ɫ
//	m_Room.SetColTextColor(3,RGB(255,255,100)); //�������ı���ɫ
//	m_RoomStyleList.SetItemTextColor(3,1,RGB(255,0,0));  //���õ�Ԫ��������ɫ
    m_Room.InsertColumn(0,"Index",LVCFMT_LEFT,0);
    m_Room.InsertColumn(1,"���ƺ�",LVCFMT_CENTER,Rect.Width()/12);
    m_Room.InsertColumn(2,"¥��¥��",LVCFMT_CENTER,Rect.Width()/12);
    m_Room.InsertColumn(3,"����",LVCFMT_CENTER,Rect.Width()/12);
    m_Room.InsertColumn(4,"������̬",LVCFMT_CENTER,Rect.Width()/12);
    m_Room.InsertColumn(5,"��ʱ��̬",LVCFMT_CENTER,Rect.Width()/3);
    m_Room.InsertColumn(6,"�豸",LVCFMT_CENTER,Rect.Width()/3);
///////////////////////////////////////////////////////////////////////////////////////////////////////
    //�½���һ���Ҽ������˵���OnCommand����Ӧ
    InitPopMenu();

	//��ʼ����ѯ���� 
	m_Condition.nRoomType = -1;
	m_Condition.nFloor = -1;
	m_Condition.nBuilding = -1;

}

void CMainRealStatusDlg::ReloadRoomStateInfo()
{

}
/**********************************************************************************
$���ܣ���ʼ�������˵�
//===================================================
***********************************************************************************/
void CMainRealStatusDlg::InitPopMenu()
{
   /*CMenu *popMenu;
   popMenu = new CMenu();
   popMenu->CreatePopupMenu();
   popMenu->AppendMenu(MF_CHECKED | MF_STRING,IDM_POPMENU_BASE+0x10,"�б�ģʽ");//��Ӳ˵���
   popMenu->AppendMenu(MF_UNCHECKED |MF_STRING,IDM_POPMENU_BASE+0x11,"�༭ģʽ");//��Ӳ˵���
   */

   m_pMenu = new CMenu();       //m_pMenu->CreateMenu();
   m_pMenu->CreatePopupMenu();
   //��ʾ���ģʽ��ʾ�л��˵�
   //m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE,"ͼ��ģʽ");//��Ӳ˵���(Offset 0x00)
   //m_pMenu->AppendMenu(MF_SEPARATOR);//��ӷָ���
   //���з���Ĳ�������
   m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE+1,"�ͷ�");
   m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE+2,"��̬");
   m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE+3,"�豸");


   //m_pMenu->AppendMenu(MF_STRING|MF_GRAYED,IDM_POPMENU_BASE+0x10,"�ͷ���Ϣ");//��Ч










   //m_pMenu->AppendMenu(MF_POPUP,(UINT)popMenu->m_hMenu,"�л�");//��Ӳ˵���
   //m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE+0x20,"��Ϣ");//��Ӳ˵���
   //m_pMenu->AppendMenu(MF_STRING,IDM_POPMENU_BASE+0x30,"ɾ��");//��Ӳ˵���
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
		case  IDM_POPMENU_BASE:      //��ʾ��ʾ���л�
				if(lReportStyle == FALSE)   //��ͼ���л����б�
				{
				 m_Room.ModifyStyle(LVS_ICON,LVS_REPORT);
				 m_pMenu->ModifyMenu(0,MF_STRING | MF_BYPOSITION,IDM_POPMENU_BASE,"ͼ��ģʽ");
				 lReportStyle = TRUE;
				}
				else
				{
				  m_Room.ModifyStyle(LVS_REPORT,LVS_ICON);
				  m_pMenu->ModifyMenu(0,MF_STRING | MF_BYPOSITION,IDM_POPMENU_BASE,"�б�ģʽ");

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
					m_pArgument->pRoomEntry = (PVOID)m_Room.GetItemData(CurrentSelEntry);	//�ͷ���Ϣ
					//�õ��ͷ�����Ϣ
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

		//ɾ��������Ϣ
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
//��һ���֣����ط�����ϸ�����ģ��
	hRoomModule = LoadLibrary(RoomModuleName);
	if(hRoomModule == NULL)
	{
	 MessageBox("���ط�������ģ��ʧ��");
	 return;
	}
	//============================================================
	CallDetailModule = (AFX_CALLDETAILMODULE)GetProcAddress(hRoomModule,"CallDetailModule");









}


void CMainRealStatusDlg::RefresBuild()
{
	//�ȼ���Ƿ�Ϊ�ղ��Ǿ����
	if(m_Building.GetCount())
		m_Building.ResetContent();

	PBUILDING_ENTRY  m_pEntryInfo = NULL;		//¥������							//����
	PBUILDING_ENTRY  m_pTempEntryInfo = NULL;
	ULONG	Result;				//���Ľ��
	ULONG   RecordNum = 0;		//�������е�����
	//�������еļ�¼������
	Result = (ULONG)GetBuildingRecord(&m_pEntryInfo,NULL);
	if(!Result || (m_pEntryInfo==NULL))
	{
		return;
	}
	m_Building.InsertString(0,"=����¥��=");
	//���ӵ��б����ȥ
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
 /*//����������һ��ͼƬ�еĶ��ͼ��
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
 //����1�� ���ͼ�꣬ͼ�������ͼ���б��С�Զ�����
 //pImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON1));
 //pImageList->Add(AfxGetApp()->LoadIcon(IDI_ICON2));
 //=======================================================================================
 //����2�� ���λͼ����ʹ��ɫΪ͸��ɫ,���ͼ���б��С��λͼ��С��һ�¿��ܻᵼ�������ʧ��
 //CBitmap bmp;
 //bmp.LoadBitmap(IDB_BITMAP1)
 //pImageList->Add(&bmp, RGB(0, 0, 0));
 //bmp.DeleteObject();
 //bmp.LoadBitmap(IDB_BITMAP2)
 //pImageList->Add(&bmp, RGB(0, 0, 0));
 //=======================================================================================
 //����3�� ���λͼ�����ļ��������
 HBITMAP hBitmap;
 CBitmap *pBitmap;
 CString FilePathName = "Image\\RealTimeStatus\\";
 pBitmap = new   CBitmap;
 // ���ļ�����λͼ
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

//���ڰ�Ҫ����¿ͷ��б���Ϣ
//�����ֵΪ������Ϣ-1��ʾ���е�������ʾ����ID
void CMainRealStatusDlg::RefreshQuickRoomList(const char* sFilter)
{
	PROOM_DETAIL_ENTRY m_pEntryInfo;
	ULONG	Result;
	ULONG   RecordNum = 0;
	CString str;

	GolabRunStatus = GOLAB_THREAD_PAUSE;
	CString		TempCash[MAX_COUNT * 2];
//==============================================================
	//��һ�ν����ʱ��û�����ݲ����л���
	if (m_Flag)
	{
		// ��¼����е���ʱ��̬�Ϳյ��豸��Ϣ���Ա��л�ҳ����л���
		for (int i = 0; i < m_Room.GetItemCount();i++)
		{
			TempCash[2*i] = m_Room.GetItemText(i,5);
			TempCash[2*i + 1] = m_Room.GetItemText(i,6);
		}
	}
		
	//�Ƚ��б�����
	while(m_Room.GetItemCount())
	{
		m_pEntryInfo = (PROOM_DETAIL_ENTRY)m_Room.GetItemData(0);
		delete [] (PROOM_DETAIL_ENTRY)m_pEntryInfo;
		m_Room.DeleteItem(0);
	}
	m_pEntryInfo = NULL;
	//�������еļ�¼������
	Result = (ULONG)GetRoomRecord(&m_pEntryInfo,sFilter);
	if(!Result || m_pEntryInfo==NULL)
	{
		hMutex.Unlock();
		SetDlgItemInt(IDC_ROOM_NUM,Result);
		return;
	}
//���ӵ��б����ȥ		
	while(RecordNum<Result)
	{
		InsertOneRoomEntry(m_pEntryInfo);
		m_pEntryInfo = m_pEntryInfo->pNext;
		RecordNum++;
	}

	// ��һ��û���棬���Բ����������д����
	if (m_Flag)
	{
		// ������ŵ��б���
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
//��շ�������
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
	//���ƺ�
	str.Format("%02d%02d",pRoomInfo->bFloorNum,pRoomInfo->bRoomNum);
	m_Room.SetItemText(CurrentEntry,1,str);
	//¥��¥��
	str.Format("%c-%02d",pRoomInfo->bBuildingNum,pRoomInfo->bFloorNum);
	m_Room.SetItemText(CurrentEntry,2,str);
	//����
	GetRoomTypeString(pRoomInfo->dwRoomTypeID,str);
	m_Room.SetItemText(CurrentEntry,3,str);
	//������̬
	str = "����";
	m_Room.SetItemText(CurrentEntry,4,str);

	//��ʱ��̬
	str = "��";
	m_Room.SetItemText(CurrentEntry,5,str);

	//�豸
	str = "��";
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
//���·�����Ϣ
//=========================================================
//�ӷ�̬���ж������еķ�̬�������������ʹ�������ƶ�Ӧ��
//�±��pRoomTypeValue[]�б�ʾ��̬������ֵ
//======================================================
void CMainRealStatusDlg::RefreshRoomType()
{
	ULONG	Result;
	ULONG   RecordNum = 0;
	PROOM_TYPE_ENTRY	m_pEntryInfo = NULL;	
	PROOM_TYPE_ENTRY	m_pTempEntryInfo = NULL;	
	//�Ƚ��б�����
	if(m_RoomType.GetItemCount())
	{
		delete[] pRoomTypeValue;
		m_RoomType.DeleteAllItems();
	}
	//�������еļ�¼������
	Result = (ULONG)GetRoomTypeRecord(&m_pEntryInfo,NULL);
	if(!Result)
		return;

	pRoomTypeValue = new DWORD[Result+1];
	ZeroMemory(pRoomTypeValue,sizeof(DWORD)*(Result+1));
	m_RoomType.InsertItem(RecordNum,"��������");
	pRoomTypeValue[0] = -1;
	//���ӵ��б����ȥ		
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
	m_Floor.InsertString(0,"=����¥��=");
	for(Index =0;Index<dwMaxFloor+1;Index++)
	{
		str.Format("¥��[%d]",Index+1);
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
	if(m_Condition.nBuilding != -1)		//¥��
	{
		str.Format("BuildingID=%d",m_Condition.nBuilding);
		status = TRUE;
	}

	if(m_Condition.nFloor != -1)		//¥��
	{
		if(status == TRUE)
			temp.Format(" AND FloorNum=%d",m_Condition.nFloor);
		else
			temp.Format("FloorNum=%d",m_Condition.nFloor);
		status = TRUE;
		str = str + temp;
	}

	if(m_Condition.nRoomType != -1)		//��̬
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


//��ѯ���еķ�̬�߳�
UINT CMainRealStatusDlg::InquiryListRoomThread(PVOID lParam)
{
#if 1
	CMainRealStatusDlg *m_Dlg = (CMainRealStatusDlg *)lParam;
	int	CurrentEntry = 0;		//��ǰ���б�����
	PROOM_DETAIL_ENTRY m_pEntryInfo = NULL;
	//InitDataTransferLay();			//��ʼ�����ݴ���
	int Result = 0;
	int airNum = 0;
	//fp = fopen("CCTV.log","wt");		//����¼�ļ�
	//fprintf(fp,"InquiryListRoomThread Start\n");
	//////////////////////////////////////////////////////////////////////////
	while(GolabRunStatus != GOLAB_THREAD_EXIT)	//ֻҪ��Ϊ�˳���һֱ����ִ��
	{
		if(GolabRunStatus == GOLAB_THREAD_PAUSE)
		{
			SuspendThread(hInquiryThread);
		}
		//==============================================================
		hMutex.Lock();		//ȡһ������
		if(!m_Dlg->m_Room.GetItemCount())		//����б�Ϊ�ղ�Ҫ��
		{
			hMutex.Unlock();	
			continue;
		}
		//�����ǰ�ı�֮ǰ�Ĵ����ͷ��ʼ
		if(m_Dlg->m_Room.GetItemCount() <= CurrentEntry)
			CurrentEntry = 0;
		//*******************************************************
		m_pEntryInfo = (PROOM_DETAIL_ENTRY)m_Dlg->m_Room.GetItemData(CurrentEntry);			//
		//*******************************************************
		hMutex.Unlock();	
		//==============================================================
		Result = m_Dlg->QuirySelRoomInfo(m_pEntryInfo);
		CString		AirStatus;
		if(Result != 0)		//����һ��ָ��������Ƿ�OK
		{
			m_Dlg->m_Room.SetItemText(CurrentEntry,4,"����");
			CString str;
			//��ʱ��̬
			str = TempStatus(m_pEntryInfo,airNum,AirStatus);
			m_Dlg->m_Room.SetItemText(CurrentEntry,5,str);
			//Sleep(50);
			// �յ��豸
			//str = AirCondition(m_pEntryInfo,airNum);
			m_Dlg->m_Room.SetItemText(CurrentEntry,6,AirStatus);
			//Sleep(200);
		}
		else
		{
			m_Dlg->m_Room.SetItemText(CurrentEntry,4,"����");
			m_Dlg->m_Room.SetItemText(CurrentEntry,5,"��");
			m_Dlg->m_Room.SetItemText(CurrentEntry,6,"��");
		}
		//Sleep(200);
		CurrentEntry++;
	}
	//fprintf(fp,"InquiryListRoomThread End\n");
	GolabRunStatus = GOLAB_THREAD_IDLE;		//�˳��˾ͽ�״̬���
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
		str = "��";
		AirStatus = "��";
		return str;
	}
	// ͬʱ��ȡ�յ�״̬
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
	//	str = "��";
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
		str = "��";
		return str;
	}
	
	//����ģʽ
	/*if (!pPack->bContent[0])
	{
		str = "����ģʽ������ ";
	}
	else
	{
		str = "����ģʽ���ļ� ";
	}*/

	if (!pPack->bContent[1])
	{
		str += "����ģʽ������ ";
	}
	else
	{
		str += "����ģʽ������ ";
	}

	str += "�յ������¶ȣ�";
	CString tempSetting;
	tempSetting.Format("%d",pPack->bContent[2]);
	str += tempSetting;
	str += "�� ";

	str += "�����¶ȣ�";
	CString temp;
	temp.Format("%d",pPack->bContent[3]);
	str += temp;
	str += "�� ";

	int fan = pPack->bContent[4];
	switch (fan)
	{
	case FANCLOSE:
		str += "�յ����٣���";
		break;
	case FANLOW:
		str += "�յ����٣�����";
		break;
	case FANMIDDLE:
		str += "�յ����٣�����";
		break;
	case FANHEIGH:
		str += "�յ����٣�����";
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
		str = "��";
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
		AirStatus += "����ģʽ������ ";
	}
	else
	{
		AirStatus += "����ģʽ������ ";
	}

	AirStatus += "�յ������¶ȣ�";
	CString tempSetting;
	tempSetting.Format("%d",pPack->bContent[i+3]);
	AirStatus += tempSetting;
	AirStatus += "�� ";

	AirStatus += "�����¶ȣ�";
	CString temp;
	temp.Format("%d",pPack->bContent[i+4]);
	AirStatus += temp;
	AirStatus += "�� ";

	int fan = pPack->bContent[i+5];
	switch (fan)
	{
	case FANCLOSE:
		AirStatus += "�յ����٣���";
		break;
	case FANLOW:
		AirStatus += "�յ����٣�����";
		break;
	case FANMIDDLE:
		AirStatus += "�յ����٣�����";
		break;
	case FANHEIGH:
		AirStatus += "�յ����٣�����";
		break;
	default:
		break;
	}
	
	// ����Ϊ��ȡconfig.txt��·�����������SourceͼƬ��Դ��·����������ȡ�ļ�ʧ��
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
		strContent = "������ť�Ѱ��� ";
	}
	if (!(pPack->bContent[2] & 0x01) && ('0' != tempStr[0]))
	{
		strContent = "������ťδ���� ";
	}

	if ((pPack->bContent[2] & (0x01 << 1)) && ('0' != tempStr[1]))
	{
		strContent += "�ſ�δ���� ";
	}
	if (!(pPack->bContent[2] & (0x01 << 1)) && ('0' != tempStr[1]))
	{
		strContent += "�ſ��Ѳ��� ";
	}

	if ((pPack->bContent[2] & (0x01 << 2)) && ('0' != tempStr[2]))
	{
		strContent += "���ſ� ";
	} 
	if (!(pPack->bContent[2] & (0x01 << 2)) && ('0' != tempStr[2]))
	{
		strContent += "���Ź� ";
	}

	if ((pPack->bContent[2] & (0x01 << 3)) && ('0' != tempStr[3]))
	{
		strContent += "�ܵ�Դ�� ";
	} 
	if (!(pPack->bContent[2] & (0x01 << 3)) && ('0' != tempStr[3]))
	{
		strContent += "�ܵ�Դ�� ";
	}

	if ((pPack->bContent[2] & (0x01 << 4)) && ('0' != tempStr[4]))
	{
		strContent += "�����俪 ";
	} 
	if (!(pPack->bContent[2] & (0x01 << 4)) && ('0' != tempStr[4]))
	{
		strContent += "������� ";
	}

	if ((pPack->bContent[2] & (0x01 << 5)) && ('0' != tempStr[5]))
	{
		strContent += "ϴ�·��� ";
	} 
	if (!(pPack->bContent[2] & (0x01 << 5)) && ('0' != tempStr[5]))
	{
		strContent += "ϴ�·���� ";
	}

	if ((pPack->bContent[2] & (0x01 << 6)) && ('0' != tempStr[6]))
	{
		strContent += "������ſ� ";
	} 
	if (!(pPack->bContent[2] & (0x01 << 6)) && ('0' != tempStr[6]))
	{
		strContent += "������Ź� ";
	}

	if ((pPack->bContent[2] & (0x01 << 7)) && ('0' != tempStr[7]))
	{
		strContent += "���Ժ� ";
	} 
	if (!(pPack->bContent[2] & (0x01 << 7)) && ('0' != tempStr[7]))
	{
		strContent += "���Ժ�� ";
	}

	if ((pPack->bContent[3] & 0x01) && ('0' != tempStr[8]))
	{
		strContent += "���������� ";
	} 
	if (!(pPack->bContent[3] & 0x01) && ('0' != tempStr[8]))
	{
		strContent += "���������� ";
	}

	if ((pPack->bContent[3] & (0x01 << 1)) && ('0' != tempStr[9]))
	{
		strContent += "��������� ";
	} 
	if (!(pPack->bContent[3] & (0x01 << 1)) && ('0' != tempStr[9]))
	{
		strContent += "��������� ";
	}

	if ((pPack->bContent[3] & (0x01 << 2)) && ('0' != tempStr[10]))
	{
		strContent += "��̨�ſ� ";
	} 
	if (!(pPack->bContent[3] & (0x01 << 2)) && ('0' != tempStr[10]))
	{
		strContent += "��̨�Ź� ";
	}

	if ((pPack->bContent[3] & (0x01 << 3)) && ('0' != tempStr[11]))
	{
		strContent += "ҹ���� ";
	} 
	if (!(pPack->bContent[3] & (0x01 << 3)) && ('0' != tempStr[11]))
	{
		strContent += "ҹ���� ";
	}

	if ((pPack->bContent[3] & (0x01 << 4)) && ('0' != tempStr[12]))
	{
		strContent += "�����俪 ";
	} 
	if (!(pPack->bContent[3] & (0x01 << 4)) && ('0' != tempStr[12]))
	{
		strContent += "������� ";
	}

	if ((pPack->bContent[3] & (0x01 << 5)) && ('0' != tempStr[13]))
	{
		strContent += "�����˷��� ";
	} 
	if (!(pPack->bContent[3] & (0x01 << 5)) && ('0' != tempStr[13]))
	{
		strContent += "�����˷��� ";
	}

	if ((pPack->bContent[3] & (0x01 << 6)) && ('0' != tempStr[14]))
	{
		strContent += "���˿� ";
	} 
	if (!(pPack->bContent[3] & (0x01 << 6)) && ('0' != tempStr[14]))
	{
		strContent += "���˹� ";
	}

	if ((pPack->bContent[3] & (0x01 << 7)) && ('0' != tempStr[15]))
	{
		strContent += "ά���п�";
	} 
	if (!(pPack->bContent[3] & (0x01 << 7)) && ('0' != tempStr[15]))
	{
		strContent += "ά���й�";
	}
	return strContent;
}

void CMainRealStatusDlg::OnDestroy() 
{
	// TODO: Add your message handler code here
	//����б�������
	//PROOM_DETAIL_ENTRY pRoomInfo;
	//hMutex.Lock();		//ȡһ������
	//while(m_Room.GetItemCount())
	//{
	//	pRoomInfo = (PROOM_DETAIL_ENTRY)m_Room.GetItemData(0);

	//	delete [] (PROOM_DETAIL_ENTRY)pRoomInfo;
	//	m_Room.DeleteItem(0);
	//}	
	//hMutex.Unlock();		//ȡһ������
	//
	CDialog::OnDestroy();
}


int CMainRealStatusDlg::QuirySelRoomInfo(PVOID lParam)
{
	/*PROMM_INFO_TRANSFER m_pTrans = (PROMM_INFO_TRANSFER)lParam;
	PROOM_DETAIL_ENTRY m_pEntryInfo = (PROOM_DETAIL_ENTRY)m_pTrans->pRoomEntry;*/
	PROOM_DETAIL_ENTRY m_pEntryInfo = (PROOM_DETAIL_ENTRY)lParam;
	//=========================================================================
	DATA_TRANS_PRE  PreBuf;		//���͵�ǰ׺
	DWORD	IpAddress;			//Ip��ַ
	USHORT	nPort;				//�˿�	
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
		MessageBox("��ȡ������Ϣʧ�ܣ����������÷���IP�Ͷ˿ںţ�","����");
	}
	return nBytes;
}

UINT CMainRealStatusDlg::GetRoomInfoThread(PVOID lParam)
{
	PROMM_INFO_TRANSFER m_pTransInfo = (PROMM_INFO_TRANSFER)lParam;
	CMainRealStatusDlg *m_Dlg = (CMainRealStatusDlg *)m_pTransInfo->ParentDlg;
	PROOM_DETAIL_ENTRY m_pRoomEntry = (PROOM_DETAIL_ENTRY)m_pTransInfo->pRoomEntry;
	int Result = -1;
	m_Dlg->pLoadDlg->SetTimer(0,1000,NULL);		//������ʱ����
//======================================================================================
//��һ�����õ��ͷ���Buffer����(�Լ�����RCUֵ)
	m_pTransInfo->RCU = GetBufferLengthFromRoom(m_pTransInfo->pRoomEntry,m_pTransInfo->eLength,m_pTransInfo->sLength);
	m_pTransInfo->pTotalLength = m_pTransInfo->eLength * EQUMENT_DATA_SIZE + m_pTransInfo->sLength * STATUS_DATA_SIZE;
	if(m_pTransInfo->RCU != -1)		//�ж�Ӧ��RCU
	{//���¼���
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
	Result = m_Dlg->QuirySelRoomInfo(m_pTransInfo);					//����ͷ�����Ϣ
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
	{//��ʼ�������ؼ�
	//���·�����Ϣ(�����ݿ��ж���)
		RefreshRoomType();
	//����¥����Ϣ
		RefresBuild();
	//���¿ͷ��б�
		ConvertSearchCondition();
//*******************************************************************
		//fp = fopen("CCTV.log","wt");		//����¼�ļ�

	
	
	
















	}
	else
	{//ɾ�������ؼ�
	
	










		//fclose(fp);
	}
}
