// PictureChangeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoCFG.h"
#include "PictureChangeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPictureChangeDlg dialog


CPictureChangeDlg::CPictureChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPictureChangeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPictureChangeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPictureChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPictureChangeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPictureChangeDlg, CDialog)
	//{{AFX_MSG_MAP(CPictureChangeDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictureChangeDlg message handlers
