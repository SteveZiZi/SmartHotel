// ManagementDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Management.h"
#include "ManagementDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
const CSize BtnSize(65,80);
const int Gap = 20;             //间距
const int Top = 10;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManagementDlg dialog

CManagementDlg::CManagementDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CManagementDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CManagementDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CManagementDlg::~CManagementDlg()
{
   //if(lpPermissions != NULL)
   //  delete[] lpPermissions;
	if(m_pRealStatusDlg != NULL)
		delete[] (CMainRealStatusDlg  *)m_pRealStatusDlg;
	if(m_pConfigPanel != NULL)
		delete[] (CConfigPanelDlg  *)m_pConfigPanel;

}


void CManagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManagementDlg)
	DDX_Control(pDX, IDCANCEL, m_Exit);
	DDX_Control(pDX, IDC_BTN_CENSUS, m_Census);
	DDX_Control(pDX, IDC_BTN_CONFIG, m_ConfigPannel);
	DDX_Control(pDX, IDC_BTN_ACTUL_ROOMSTATE, m_ActureRS);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CManagementDlg, CDialog)
	//{{AFX_MSG_MAP(CManagementDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_ACTUL_ROOMSTATE, OnBtnActulRoomstate)
	ON_BN_CLICKED(IDC_BTN_CONFIG, OnBtnConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManagementDlg message handlers

BOOL CManagementDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon	
	// TODO: Add extra initialization here
	AdjustItemPosition();

	InitSubDialog();
    //////////////////////////////////////

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CManagementDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CManagementDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CManagementDlg::AdjustItemPosition()
{
//全屏
////////////////////////////////////////////////////////////////////////////////
#ifdef FULL_SCREEN_COVER_TASK
   int cx,cy; 
   cx = GetSystemMetrics(SM_CXSCREEN); 
   cy = GetSystemMetrics(SM_CYSCREEN); 

   rcWorkArea.BottomRight() = CPoint(cx, cy); 
   rcWorkArea.TopLeft() = CPoint(0, 0); 
#else   
   SystemParametersInfo(SPI_GETWORKAREA,   0,&rcWorkArea,   0); 
#endif
   MoveWindow(rcWorkArea);
   //ScreenToClient(rcWorkArea);
/////////////////////////////////////////////////////////////////////////////////
//按钮的位置
  int Num = 0;
//===========================================================
  //实时房态按钮
  if(GolabPermission->PermissionMain.bValue.bActiveRSEn)   //实时房态
  {
    //m_ActureRS.SetBtnBkColor(RGB(0,255,0),RGB(255,0,0));
	m_ActureRS.SetTextStyle(RGB(255,255,255),12,"楷体");
	//m_ActureRS.SetControlSource(L"Image\\Management\\menu1.png",NULL,(float)1.3);
	m_ActureRS.SetControlSource(L"Image\\Management\\menu1.png",NULL,(float)1.3);
	//m_btnTest.SetControlSource(L"13-1.png",L"15-1.png");
    //m_ActureRS.SetControlSource(L"Image\\Image\\Management\\menu1.png",NULL);


    ::MoveWindow(GetDlgItem(IDC_BTN_ACTUL_ROOMSTATE)->GetSafeHwnd(),rcWorkArea.left+Num*(BtnSize.cx+Gap)+Gap,rcWorkArea.top+Top,BtnSize.cx,BtnSize.cy,TRUE);
    ::ShowWindow(GetDlgItem(IDC_BTN_ACTUL_ROOMSTATE)->GetSafeHwnd(),SW_SHOW);
	Num++;

  } 
  else
    ::ShowWindow(GetDlgItem(IDC_BTN_ACTUL_ROOMSTATE)->GetSafeHwnd(),SW_HIDE);
  //控制面板按钮
  if(GolabPermission->PermissionMain.bValue.bControlPanelEn)   //控制面板
  {
	m_ConfigPannel.SetTextStyle(RGB(255,255,255),12,"楷体");
	m_ConfigPannel.SetControlSource(L"Image\\Management\\menu2.png",NULL,(float)1.3);


    ::MoveWindow(GetDlgItem(IDC_BTN_CONFIG)->GetSafeHwnd(),rcWorkArea.left+Num*(BtnSize.cx+Gap)+Gap,rcWorkArea.top+Top,BtnSize.cx,BtnSize.cy,TRUE);
    ::ShowWindow(GetDlgItem(IDC_BTN_CONFIG)->GetSafeHwnd(),SW_SHOW);
	Num++;
  } 
  else
    ::ShowWindow(GetDlgItem(IDC_BTN_CONFIG)->GetSafeHwnd(),SW_HIDE);

  //统计查询
 // if(GolabPermission->PermissionMain.bValue.bCensusEn)   //
 // {
	//m_Census.SetTextStyle(RGB(255,255,255),12,"楷体");
	//m_Census.SetControlSource(L"Image\\Management\\menu3.png",NULL,(float)1.3);


 //   ::MoveWindow(GetDlgItem(IDC_BTN_CENSUS)->GetSafeHwnd(),rcWorkArea.left+Num*(BtnSize.cx+Gap)+Gap,rcWorkArea.top+Top,BtnSize.cx,BtnSize.cy,TRUE);
 //   ::ShowWindow(GetDlgItem(IDC_BTN_CENSUS)->GetSafeHwnd(),SW_SHOW);
	//Num++;
 // } 
 // else
 //   ::ShowWindow(GetDlgItem(IDC_BTN_CENSUS)->GetSafeHwnd(),SW_HIDE);


  //日志信息
  GolabPermission->PermissionMain.bValue.bLogViewEn = 0;
  if(GolabPermission->PermissionMain.bValue.bLogViewEn)   //
  {


    ::MoveWindow(GetDlgItem(IDC_BTN_LOGINFO)->GetSafeHwnd(),rcWorkArea.left+Num*(BtnSize.cx+Gap)+Gap,rcWorkArea.top+Top,BtnSize.cx,BtnSize.cy,TRUE);
    ::ShowWindow(GetDlgItem(IDC_BTN_LOGINFO)->GetSafeHwnd(),SW_SHOW);
	Num++;
  } 
  else
    ::ShowWindow(GetDlgItem(IDC_BTN_LOGINFO)->GetSafeHwnd(),SW_HIDE);


  //
  GolabPermission->PermissionMain.bValue.bReservedEn = 0;
  if(GolabPermission->PermissionMain.bValue.bReservedEn)   //
  {

    ::MoveWindow(GetDlgItem(IDC_BTN)->GetSafeHwnd(),rcWorkArea.left+Num*(BtnSize.cx+Gap)+Gap,rcWorkArea.top+Top,BtnSize.cx,BtnSize.cy,TRUE);
    ::ShowWindow(GetDlgItem(IDC_BTN)->GetSafeHwnd(),SW_SHOW);
	Num++;
  } 
  else
    ::ShowWindow(GetDlgItem(IDC_BTN)->GetSafeHwnd(),SW_HIDE);


  //退出
  if(GolabPermission->PermissionMain.bValue.bExitEn)   //
  {
	m_Exit.SetTextStyle(RGB(255,255,255),12,"楷体");
	m_Exit.SetControlSource(L"Image\\Management\\menu4.png",NULL,(float)1.3);


    ::MoveWindow(GetDlgItem(IDCANCEL)->GetSafeHwnd(),rcWorkArea.left+Num*(BtnSize.cx+Gap)+Gap,rcWorkArea.top+Top,BtnSize.cx,BtnSize.cy,TRUE);
    ::ShowWindow(GetDlgItem(IDCANCEL)->GetSafeHwnd(),SW_SHOW);
	Num++;
  } 
  else
    ::ShowWindow(GetDlgItem(IDCANCEL)->GetSafeHwnd(),SW_HIDE);












	//CRect	rcHeadArea;				//头部
	//CRect	rcCuntomerArea;			//客户区	
///////////////////////////////////////////////////////////////////////////////////
//客户区的位置移动
	rcCustomerArea.left = 0;
	rcCustomerArea.right = rcWorkArea.right - GetSystemMetrics(SM_CXFRAME);
	
	rcCustomerArea.top = BtnSize.cy + GetSystemMetrics(SM_CYSIZE);
	rcCustomerArea.bottom = rcWorkArea.bottom - GetSystemMetrics(SM_CYFRAME);
	::MoveWindow(GetDlgItem(IDC_CUSTOM)->GetSafeHwnd(),rcCustomerArea.left,rcCustomerArea.top,rcCustomerArea.right,rcCustomerArea.bottom,TRUE);
	//::MoveWindow(GetDlgItem(IDC_CUSTOM)->GetSafeHwnd(),0,BtnSize.cy+Top*3,rcWorkArea.right,rcWorkArea.bottom-140,TRUE);
   //::ShowWindow(GetDlgItem(IDC_CUSTOM)->GetSafeHwnd(),SW_HIDE);
}

BOOL CManagementDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
    CRect Rect;
    GetClientRect(&Rect);
////////////////////////////////////////////////////////////////////////////////////////////
    //画背景图片
    CFileFind m_Find;
	CString str;
    //////////////////////////////////////
    str.Format("%s",MainBkGround);
	if(m_Find.FindFile(str))   //文件存在绘背景
	{
	   CBitmap btm;
	   HBITMAP hbtm;
	   BITMAP bitmap;
	   CDC dcMem;

	   hbtm = (HBITMAP) ::LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
       if(hbtm != NULL)
		btm.Attach(hbtm);
	   else
		return CDialog::OnEraseBkgnd(pDC);

	   dcMem.CreateCompatibleDC(pDC);
	   dcMem.SelectObject(&btm);
       btm.GetBitmap(&bitmap);

	   //CSize sm(sizeof(BITMAP),&bitmap);
       //pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&dcMem,0,0,SRCCOPY);
       pDC->StretchBlt(0,0,Rect.Width(),rcCustomerArea.top,&dcMem,0,0,bitmap.bmWidth,rcCustomerArea.top,SRCCOPY);
       dcMem.DeleteDC();
	   return TRUE;
	}
return CDialog::OnEraseBkgnd(pDC);
}

void CManagementDlg::InitSubDialog()
{
  CWnd *m_Hwnd;
  m_Hwnd = GetDlgItem(IDC_CUSTOM);
  //主实时房态显示CMainRealStatusDlg  *m_pRealStatusDlg;
  m_pRealStatusDlg = new CMainRealStatusDlg(m_Hwnd);
  m_pRealStatusDlg->Create(IDD_MAINREALSTATUS_DIALOG,m_Hwnd);
  m_pRealStatusDlg->ShowWindow(SW_SHOWNORMAL);
  
  //控制面板   CConfigPanelDlg  *m_pConfigPanel;
  m_pConfigPanel = new CConfigPanelDlg(m_Hwnd);
  m_pConfigPanel->Create(IDD_CONFIG_DIALOG,m_Hwnd);
  m_pConfigPanel->ShowWindow(SW_HIDE);





}

void CManagementDlg::OnBtnActulRoomstate() 
{
	// TODO: Add your control notification handler code here
	GolabRunStatus = GOLAB_THREAD_RUN;
	ResumeThread(hInquiryThread);
    m_pRealStatusDlg->ShowWindow(SW_SHOWNORMAL);	
	m_pConfigPanel->ShowWindow(SW_HIDE);
}

void CManagementDlg::OnBtnConfig() 
{
	// TODO: Add your control notification handler code here
	GolabRunStatus = GOLAB_THREAD_PAUSE;
	m_pConfigPanel->ShowWindow(SW_SHOWNORMAL);
	m_pRealStatusDlg->ShowWindow(SW_HIDE);
}

BOOL CManagementDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;	
	}
	return CDialog::PreTranslateMessage(pMsg);
}
