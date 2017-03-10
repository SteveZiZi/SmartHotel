// LoadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "management.h"
#include "LoadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoadDlg dialog


CLoadDlg::CLoadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoadDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	lpPicName = NULL;
	IsReady = FALSE;

	uTimeOutValue = DEFAULT_TIMEOUT_VALUE;
	uCostTimes = 0;
}


void CLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoadDlg)
	DDX_Control(pDX, IDC_GIF_PICTURE, m_GifPic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoadDlg, CDialog)
	//{{AFX_MSG_MAP(CLoadDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadDlg message handlers

BOOL CLoadDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	//m_GifPic.Load("D:\\VC控件应用之自绘\\图片框\\GI-Play\\res\\214.gif");
	//m_gif2.Load(MAKEINTRESOURCE(IDR_GIF2),_T("GIF") );
	m_GifPic.Load(lpPicName);	//加载动画
	ReSetItemSize();			//重新设置动画的路径
	m_GifPic.Draw();
	//初始化值
	uCostTimes = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoadDlg::ReSetItemSize()
{
	SIZE m_Size;
	CPoint pt(0,0);
	CRect ClientRect(0,0,0,0);
	CRect BtnRect(0,0,0,0);
//第一步：得到图片的大小
	m_Size = m_GifPic.GetSize();
	if((m_Size.cx && m_Size.cx)== 0)
		return;

//第二步得到窗口矩形大小
	//GetWindowRect(ScreenRect);		//
	GetClientRect(&ClientRect);
	ClientToScreen(&pt);

	ClientRect.left = pt.x;
	ClientRect.top = pt.y;
	ClientRect.right = ClientRect.left + m_Size.cx;
	ClientRect.bottom = ClientRect.top + m_Size.cy + 30;

	MoveWindow(ClientRect,FALSE);	
//得到按钮的大小
	BtnRect.left = 0;//ClientRect.left+ClientRect.Width()/4;
	BtnRect.right = BtnRect.left + ClientRect.Width();

	BtnRect.top = ClientRect.bottom-pt.y-25;
	BtnRect.bottom = BtnRect.top + 25;
	((CButton *)GetDlgItem(IDCANCEL))->MoveWindow(BtnRect,FALSE);



	//BtnRect.left = pt.x + ClientRect.Width()/4;
	//BtnRect.right = pt.x + ClientRect.Width()*3/4;

	//BtnRect.top = pt.y+m_Size.cy+10;
	//BtnRect.bottom = BtnRect.top + 40;

	//((CButton *)GetDlgItem(IDCANCEL))->MoveWindow(BtnRect,FALSE);
	//ScreenToClient(&pt);

	
	
	
	
	
	
	
	
/*	
	
	CPoint pCenter(0,0);
	CRect Rect(0,0,0,0);
	

	

//////////////////////////////////////////////
	ClientToScreen(&pt);
	//GetWindowRect(Rect);		//
	pCenter.x = GetSystemMetrics(SM_CXSCREEN)/2;		//得到x坐标
	pCenter.y = GetSystemMetrics(SM_CYSCREEN)/2;		//得到y坐标
	
	Rect.left = pCenter.x - m_Size.cx/2;
	Rect.top = pCenter.y - m_Size.cy/2;
	
	Rect.right = Rect.left + m_Size.cx*2;
	Rect.bottom = Rect.top + m_Size.cy*2;
	//移到合适的位置
	MoveWindow(Rect,FALSE);	
	//GetClientRect(&Rect);
	ScreenToClient(&pt); 
	//MoveWindow(0,0,m_Size.cx,m_Size.cy,FALSE);
	//m_GifPic.MoveWindow(0,0,m_Size.cx,m_Size.cy,FALSE);
*/
}


void CLoadDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString str;
//
	str.Format("%d 秒%d",++uCostTimes,IsReady);
	SetDlgItemText(IDCANCEL,str);
	//if((uCostTimes >= uTimeOutValue) || (IsReady == FALSE))
	/*if(IsReady == FALSE)
	{
		MessageBox("str");
		KillTimer(0);
		SendMessage(WM_CLOSE);
		//exit(0);
	}*/
	CDialog::OnTimer(nIDEvent);
}


void CLoadDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	IsReady = FALSE;
	CDialog::OnCancel();
}

BOOL CLoadDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;	
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
