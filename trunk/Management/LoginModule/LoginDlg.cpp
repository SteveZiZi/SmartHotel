// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LoginModule.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
	, m_UserName(_T(""))
	, m_Passwords(_T(""))
{
	//{{AFX_DATA_INIT(CLoginDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Control(pDX, IDC_COMBO_DEPARTMENT, m_Departament);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_USERNAME, m_UserName);
	DDX_Text(pDX, IDC_PASSWORD, m_Passwords);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO_DEPARTMENT, OnSelchangeComboDepartment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CurrentName.Empty();
	memset(CurrentPath,'\0',MAX_PATH);
	::GetCurrentDirectory(MAX_PATH,CurrentPath);
	sConfigFile.Format("%s\\LoginConfig.ini",CurrentPath);
	//strcat(CurrentPath,"\\Image\\Login\\");

	// TODO: Add extra initialization here
	InitDepartMent();








	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CLoginDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
   GetClientRect(&Rect);	
   //
   //ScreenToClient(&Rect.TopLeft());
   //画背景
   //DrawPicture(pDC,"Image\\Login\\Bk.jpg",Rect.TopLeft(),CSize(Rect.Width(),Rect.Height()),TRUE);
   //画Logo

    //return TRUE;
	return CDialog::OnEraseBkgnd(pDC);
}

HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);	
	// TODO: Change any attributes of the DC here
    switch(pWnd->GetDlgCtrlID())
	{
      case IDC_STATIC_DEPART:
	  case IDC_STATIC_NAME:      
	  case IDC_STATIC_PASSWORD:		
		     pDC->SetBkMode(TRANSPARENT); 
             //pDC->SetTextColor(RGB(0,0,255)); 
             return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 	
	    
	  case IDC_COMBO_DEPARTMENT:	
             pDC->SetTextColor(RGB(0,0,255)); 
             return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
	  case IDC_USERNAME:
	  case IDC_PASSWORD:
             pDC->SetTextColor(RGB(0,0,255)); 
             return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
	   default:
		     break;
	
	
	}
	// TODO: Return a different brush if the default is not desired
    return (HBRUSH)GetStockObject(WHITE_BRUSH);
	//return hbr;
}

void CLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	nDepartment = m_Departament.GetCurSel();
	
	CDialog::OnOK();
}

void CLoginDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CLoginDlg::DrawPicture(CDC *pDC, PCHAR Path, CPoint lt, CSize area, bool Flag)
{
    IPicture  *pPic;  
    IStream   *pStm;  
    BOOL      bResult;  

    HANDLE    hFile=NULL;  
    DWORD     dwFileSize,dwByteRead;  

    //打开硬盘中的图形文件  
    hFile=CreateFile(Path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);  
    if (hFile!=INVALID_HANDLE_VALUE)  
    {  
        dwFileSize=GetFileSize(hFile,NULL);//获取文件字节数  
        if(dwFileSize==0xFFFFFFFF)  
        {
            CloseHandle(hFile);
            return;  
        }
    }  
    else  
    {  
        return ;  
    }  


    //分配全局存储空间  
    HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,dwFileSize);  
    if(hGlobal==NULL)  
        return ;  

    LPVOID  pvData =GlobalLock(hGlobal);  

    if(pvData==NULL)//锁定分配内存块  
    {
        GlobalFree(hGlobal);
        return;  
    }
    ReadFile(hFile,pvData,dwFileSize,&dwByteRead,NULL);//把文件读入内存缓冲区  
    CloseHandle(hFile);//关闭打开的文件  

    GlobalUnlock(hGlobal);  

    CreateStreamOnHGlobal(hGlobal,TRUE,&pStm);  

    //装入图形文件  
    bResult=OleLoadPicture(pStm,dwFileSize,TRUE,IID_IPicture,(LPVOID*)&pPic);  
    GlobalFree(hGlobal);

    if(FAILED(bResult))  
        return ;  

    long   hmWidth;//图片的真实宽度  
    long   hmHeight;//图片的真实高度  
    pPic->get_Width(&hmWidth);  
    pPic->get_Height(&hmHeight);  


    //将图形输出到屏幕上（有点像BitBlt）  
    bResult=pPic->Render(pDC->m_hDC,lt.x,lt.y,area.cx,area.cy,0,hmHeight,hmWidth,-hmHeight,NULL);  
    //bResult=pPic->Render(pDC->m_hDC,0,0,area.cx,area.cy,0,hmHeight,hmWidth,-hmHeight,NULL);
    pPic->Release();  
}

void CLoginDlg::InitDepartMent()
{
    int Index,Num;
	CString str;
    char rStr[MAX_PATH];
    //WritePrivateProfileString("LoginParren","TotalNum","5",sConfigFile);
	Num = GetPrivateProfileInt("LoginParren","TotalNum",0,sConfigFile);
	for(Index = 0;Index < Num;Index++)
	{
	  str.Format("Entry%d",Index);
      memset(rStr,'\0',MAX_PATH);
      //WritePrivateProfileString(str,"Name",sName,sConfigFile);
	  GetPrivateProfileString(str,"Name",NULL,rStr,MAX_PATH,sConfigFile);
    ///////////////////////////////////////////////////////////
      m_Departament.InsertString(Index,rStr);
	}

/////////////////////////////////////////////////////////////////////////////////
	if(Num == 0)
	{
		::EnableWindow(GetDlgItem(IDC_USERNAME)->GetSafeHwnd(),FALSE);
	    ::EnableWindow(GetDlgItem(IDC_PASSWORD)->GetSafeHwnd(),FALSE);

		//::EnableWindow(GetDlgItem(IDOK)->GetSafeHwnd(),FALSE);
		//::EnableWindow(GetDlgItem(IDCANCEL)->GetSafeHwnd(),FALSE);
	}
    else
	{
	  m_Departament.SetCurSel(0);
	  OnSelchangeComboDepartment();
	}



////////////////////////////////////////////////////////////////////////////////    
    










/*
    Index = m_Departament.AddString("前台部");
	//m_Departament.SetItemData(Index,Index);

    Index = m_Departament.AddString("工程部");
	//m_Departament.SetItemData(Index,Index);

    Index = m_Departament.AddString("总经办");
	//m_Departament.SetItemData(Index,Index);

    Index = m_Departament.AddString("管理员");
	//m_Departament.SetItemData(Index,Index);
*/	
}

void CLoginDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
   HDC hDC;	
   CRect rt;
   hDC = ::GetDC(GetDlgItem(IDC_LOGO)->GetSafeHwnd());
   ::GetClientRect(GetDlgItem(IDC_LOGO)->GetSafeHwnd(),&rt);
   DrawPicture(CDC::FromHandle(hDC),"Image\\Login\\Logo.jpg",CPoint(0,0),CSize(rt.Width(),rt.Height()),TRUE);

   //画初始的图片
   if(!CurrentName.IsEmpty())
   {
      hDC = ::GetDC(GetDlgItem(IDC_CUSTOMER)->GetSafeHwnd());
      ::GetClientRect(GetDlgItem(IDC_CUSTOMER)->GetSafeHwnd(),&rt);
      //ScreenToClient(&rt.TopLeft());
      DrawPicture(CDC::FromHandle(hDC),(LPSTR)(LPCSTR)CurrentName,CPoint(0,0),CSize(rt.Width(),rt.Height()),TRUE);
   }	
	// Do not call CDialog::OnPaint() for painting messages
}

void CLoginDlg::OnSelchangeComboDepartment() 
{
	// TODO: Add your control notification handler code here
    int sIndex;
	CString str;

	char sName[MAX_PATH];
    sIndex = m_Departament.GetCurSel();

    /////////////////////////////////////////////////////
    str.Format("Entry%d",sIndex);
    memset(sName,'\0',MAX_PATH);
    //WritePrivateProfileString(str,"Name",sName,sConfigFile);
	GetPrivateProfileString(str,"View","",sName,MAX_PATH,sConfigFile);
    if(sName[0] != '\0')
	  CurrentName.Format("%s\\Image\\Login\\%s",CurrentPath,sName);
    else
	  CurrentName.Empty();

	///////////////
	if(!CurrentName.IsEmpty())
	{
	  HDC hDC;	
      CRect rt;
      hDC = ::GetDC(GetDlgItem(IDC_CUSTOMER)->GetSafeHwnd());
      ::GetClientRect(GetDlgItem(IDC_CUSTOMER)->GetSafeHwnd(),&rt);
	  //rt = rt + CRect(0,0,60,60);
	  //::MoveWindow(GetDlgItem(IDC_CUSTOMER)->GetSafeHwnd(),rt.left,rt.top,rt.right,rt.bottom,TRUE);
      //ScreenToClient(&rt.TopLeft());
      DrawPicture(CDC::FromHandle(hDC),(LPSTR)(LPCSTR)CurrentName,CPoint(0,0),CSize(rt.Width(),rt.Height()),TRUE);
    }
    else
	{
	   CDC *pDC;
	   CRect rt;
	   pDC = CDC::FromHandle(::GetDC(GetDlgItem(IDC_CUSTOMER)->GetSafeHwnd()));
	   ::GetClientRect(GetDlgItem(IDC_CUSTOMER)->GetSafeHwnd(),&rt);
	
	   pDC->RoundRect(rt,CPoint(10,10));
	}




	//}




    //m_Departament.GetLBText(sIndex,sName);



    //MessageBox(sConfigFile);

	













}
