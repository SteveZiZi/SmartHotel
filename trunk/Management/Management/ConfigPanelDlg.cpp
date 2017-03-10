// ConfigPanelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "ConfigPanelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

// CConfigPanelDlg dialog


CConfigPanelDlg::CConfigPanelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigPanelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigPanelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigPanelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigPanelDlg)
	DDX_Control(pDX, IDC_BTN_MANAGE, m_Manage_Setting);
	DDX_Control(pDX, IDC_BTN_WARNNING, m_Warnning_Setting);
	DDX_Control(pDX, IDC_BTN_KEY, m_Key_Define);
	DDX_Control(pDX, IDC_BTN_ATTENTION, m_Notice_Setting);
	DDX_Control(pDX, IDC_BTN_PICTURE, m_Picture_Change);
	DDX_Control(pDX, IDC_BTN_COMMUNATION, m_Communication_Config);
	DDX_Control(pDX, IDC_BTN_RCU, m_RCU_Config);
	DDX_Control(pDX, IDC_BTN_AUTOEVENT, m_AutoEvent_Setting);
	DDX_Control(pDX, IDC_BTN_DEVICE, m_Device_Setting);
	DDX_Control(pDX, IDC_BTN_ROOMSTATUS, m_RoomStatus_Setting);
	DDX_Control(pDX, IDC_BTN_ROOMMODE, m_RoomMode_Setting);
	DDX_Control(pDX, IDC_BTN_ROOM, m_Room_Setting);
	DDX_Control(pDX, IDC_BTN_ROOMTYPE, m_RoomType_Setting);
	DDX_Control(pDX, IDC_BTN_USEINFO, m_Use_Manage);
	DDX_Control(pDX, IDC_BTN_SYSTEM, m_System_Setting);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigPanelDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigPanelDlg)
	ON_BN_CLICKED(IDC_BTN_ROOMSTATUS, OnBtnRoomstatus)
	ON_BN_CLICKED(IDC_BTN_DEVICE, OnBtnDevice)
	ON_BN_CLICKED(IDC_BTN_COMMUNATION, OnBtnCommunation)
	ON_BN_CLICKED(IDC_BTN_RCU, OnBtnRcu)
	ON_BN_CLICKED(IDC_BTN_ROOMTYPE, OnBtnRoomtype)
	ON_BN_CLICKED(IDC_BTN_ROOM, OnBtnRoom)
	ON_BN_CLICKED(IDC_BTN_ROOMMODE, OnBtnRoommode)
	ON_BN_CLICKED(IDC_BTN_SYSTEM, OnBtnSystem)
	ON_BN_CLICKED(IDC_BTN_USEINFO, OnBtnUseinfo)
	ON_BN_CLICKED(IDC_BTN_MANAGE, OnBtnManage)
	ON_BN_CLICKED(IDC_BTN_PICTURE, OnBtnPicture)
	ON_BN_CLICKED(IDC_BTN_AUTOEVENT, OnBtnAutoevent)
	ON_BN_CLICKED(IDC_BTN_ATTENTION, OnBtnAttention)
	ON_BN_CLICKED(IDC_BTN_KEY, OnBtnKey)
	ON_BN_CLICKED(IDC_BTN_WARNNING, OnBtnWarnning)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigPanelDlg message handlers

BOOL CConfigPanelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//(CStatic *)GetDlgItem(IDC_STATIC_SYSCFG)->ShowWindow(SW_HIDE);
	//(CStatic *)GetDlgItem(IDC_STATIC_ROOMINFO)->ShowWindow(SW_HIDE);
	//(CStatic *)GetDlgItem(IDC_STATIC_DEFAULT)->ShowWindow(SW_HIDE);
	// TODO: Add extra initialization here
	SetBtnView();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigPanelDlg::OnBtnRoomstatus() 
{
	// TODO: Add your control notification handler code here
    CManufactorClass  *m_Manufactor;

    m_Manufactor = new CManufactorClass();

	

    m_Manufactor->LoadRoomStatusDlg();

    delete (CManufactorClass *)m_Manufactor;
}

void CConfigPanelDlg::OnBtnDevice() 
{
	// TODO: Add your control notification handler code here
    CManufactorClass  *m_Manufactor;

    m_Manufactor = new CManufactorClass();

	

    m_Manufactor->LoadDeviceDlg();

    delete (CManufactorClass *)m_Manufactor;	
}

void CConfigPanelDlg::OnBtnCommunation() 
{
	// TODO: Add your control notification handler code here
	CManufactorClass  *m_Manufactor;
    m_Manufactor = new CManufactorClass();

	
    m_Manufactor->LoadCommunicationDlg();
    delete (CManufactorClass *)m_Manufactor;	
}

void CConfigPanelDlg::OnBtnRcu() 
{
	// TODO: Add your control notification handler code here
	CManufactorClass  *m_Manufactor;
    m_Manufactor = new CManufactorClass();

	m_Manufactor->SetDBHandle(m_mysql);
    m_Manufactor->LoadRCUDlg();
    delete (CManufactorClass *)m_Manufactor;	
}

void CConfigPanelDlg::OnBtnRoomtype() 
{
	// TODO: Add your control notification handler code here
	CRoomDetailClass  *m_RoomDetail;
    m_RoomDetail = new CRoomDetailClass();

	
    m_RoomDetail->LoadRoomTypeDlg();
    delete (CRoomDetailClass *)m_RoomDetail;		
}

void CConfigPanelDlg::OnBtnRoom() 
{
	// TODO: Add your control notification handler code here
	CRoomDetailClass  *m_RoomDetail;
    m_RoomDetail = new CRoomDetailClass();

	
    m_RoomDetail->LoadRoomDlg();
    delete (CRoomDetailClass *)m_RoomDetail;		
}

void CConfigPanelDlg::OnBtnRoommode() 
{
	// TODO: Add your control notification handler code here
	CRoomDetailClass  *m_RoomDetail;
    m_RoomDetail = new CRoomDetailClass();

	
    m_RoomDetail->LoadRoomModeDlg();
    delete (CRoomDetailClass *)m_RoomDetail;	
}

void CConfigPanelDlg::OnBtnSystem() 
{
	// TODO: Add your control notification handler code here
	CSystemInfoClass  *m_RoomDetail;
    m_RoomDetail = new CSystemInfoClass();

	
    m_RoomDetail->LoadSystemDlg();
    delete (CSystemInfoClass *)m_RoomDetail;		
}

void CConfigPanelDlg::OnBtnUseinfo() 
{
	// TODO: Add your control notification handler code here
	CSystemInfoClass  *m_RoomDetail;
    m_RoomDetail = new CSystemInfoClass();

	
    m_RoomDetail->LoadGuestInfoDlg();
    delete (CSystemInfoClass *)m_RoomDetail;			
}

void CConfigPanelDlg::OnBtnManage() 
{
	// TODO: Add your control notification handler code here
	CSystemInfoClass  *m_RoomDetail;
    m_RoomDetail = new CSystemInfoClass();

	
    m_RoomDetail->LoadBackUpDlg();
    delete (CSystemInfoClass *)m_RoomDetail;			
}

void CConfigPanelDlg::OnBtnPicture() 
{
	// TODO: Add your control notification handler code here
	CSystemInfoClass  *m_RoomDetail;
    m_RoomDetail = new CSystemInfoClass();

	
    m_RoomDetail->LoadPictureChangeDlg();
    delete (CSystemInfoClass *)m_RoomDetail;			
}

void CConfigPanelDlg::OnBtnAutoevent() 
{
	// TODO: Add your control notification handler code here
	CRoomDetailClass  *m_RoomDetail;
    m_RoomDetail = new CRoomDetailClass();

	
    m_RoomDetail->LoadAutoEventDlg();
    delete (CRoomDetailClass *)m_RoomDetail;	
}

void CConfigPanelDlg::OnBtnAttention() 
{
	// TODO: Add your control notification handler code here
	CSystemInfoClass  *m_RoomDetail;
    m_RoomDetail = new CSystemInfoClass();

	
    m_RoomDetail->LoadNoticeDlg();
    delete (CSystemInfoClass *)m_RoomDetail;		
}

void CConfigPanelDlg::OnBtnKey() 
{
	// TODO: Add your control notification handler code here
	CRoomDetailClass  *m_RoomDetail;
    m_RoomDetail = new CRoomDetailClass();

	
    m_RoomDetail->LoadKeyDefineDlg();
    delete (CRoomDetailClass *)m_RoomDetail;		
}

void CConfigPanelDlg::OnBtnWarnning() 
{
	// TODO: Add your control notification handler code here
	CRoomDetailClass  *m_RoomDetail;
    m_RoomDetail = new CRoomDetailClass();

	
    m_RoomDetail->LoadWarnningDlg();
    delete (CRoomDetailClass *)m_RoomDetail;		
}

void CConfigPanelDlg::SetBtnView()
{
	int textSize = 14;
//系统配置
	m_System_Setting.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_System_Setting.SetControlSource(L"Image\\Controlpanel\\hotelDefine.png",NULL);
//用户帐户(OK)
	m_Use_Manage.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_Use_Manage.SetControlSource(L"Image\\Controlpanel\\userDefine.png",NULL);
//日常维护
	m_Manage_Setting.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_Manage_Setting.SetControlSource(L"Image\\Controlpanel\\backAndRecover.png",NULL);

///////////////////////////////////////////
//房类设置
	m_RoomType_Setting.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_RoomType_Setting.SetControlSource(L"Image\\Controlpanel\\roomTypeDefine.png",NULL);
//客房设置
	m_Room_Setting.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_Room_Setting.SetControlSource(L"Image\\Controlpanel\\guestRoomDefine.png",NULL);
//客房模式
	m_RoomMode_Setting.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_RoomMode_Setting.SetControlSource(L"Image\\Controlpanel\\roleroomstate.png",NULL);

///////////////////////////////////////////
//房态配置
	m_RoomStatus_Setting.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_RoomStatus_Setting.SetControlSource(L"Image\\Controlpanel\\roomstatesetting.png",NULL);
//设备配置
	m_Device_Setting.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_Device_Setting.SetControlSource(L"Image\\Controlpanel\\equipment.png",NULL);
//自动事作
	m_AutoEvent_Setting.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_AutoEvent_Setting.SetControlSource(L"Image\\Controlpanel\\autoEventHandle.png",NULL);
//RCU配置
	m_RCU_Config.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_RCU_Config.SetControlSource(L"Image\\Controlpanel\\sceneDefine.png",NULL);
//通信设置
	m_Communication_Config.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_Communication_Config.SetControlSource(L"Image\\Controlpanel\\connType.png",NULL);
//图片变更
	m_Picture_Change.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_Picture_Change.SetControlSource(L"Image\\Controlpanel\\picchange.png",NULL);
//公告设置
	m_Notice_Setting.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_Notice_Setting.SetControlSource(L"Image\\Controlpanel\\noticeSetting.png",NULL);
//匙牌定义
	m_Key_Define.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_Key_Define.SetControlSource(L"Image\\Controlpanel\\keycardDefine.png",NULL);
//告警定义
	m_Warnning_Setting.SetTextStyle(RGB(0,0,255),textSize,"楷体");
	m_Warnning_Setting.SetControlSource(L"Image\\Controlpanel\\alarmDefine.png",NULL);

}

void CConfigPanelDlg::OnOK()
{

}
