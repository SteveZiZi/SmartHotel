// BackUpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoCFG.h"
#include "BackUpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackUpDlg dialog


CBackUpDlg::CBackUpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBackUpDlg::IDD, pParent)
{
	m_PathName = "D:\\MySQLbak";
	//{{AFX_DATA_INIT(CBackUpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBackUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST_FILE,m_FileList);
	//{{AFX_DATA_MAP(CBackUpDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBackUpDlg, CDialog)
	//{{AFX_MSG_MAP(CBackUpDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_BACKUP, &CBackUpDlg::OnBnClickedBtnBackup)
	ON_BN_CLICKED(IDC_BTN_IMPORT, &CBackUpDlg::OnBnClickedBtnImport)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FILE, &CBackUpDlg::OnLvnItemchangedListFile)
END_MESSAGE_MAP()

BOOL CBackUpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitList();
	UpdataList(TRUE);
	//UpdataList();
	// TODO:  Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CBackUpDlg::InitList()
{
	CRect Rt; 
	DWORD dwStyleEx;
	::GetClientRect(m_FileList.GetSafeHwnd(),&Rt);
	//改变显示模式为报表
	ModifyStyle(LVS_TYPEMASK,LVS_REPORT);
	dwStyleEx = LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES | LVS_EX_GRIDLINES;  //  
	m_FileList.SetExtendedStyle(dwStyleEx);
	////////////////////////////////////////////////////////
	m_FileList.InsertColumn( 0, NULL, LVCFMT_CENTER, 0);//插入列
	m_FileList.InsertColumn( 1, "文件序号", LVCFMT_CENTER, Rt.Width()/2 );//插入列
	m_FileList.InsertColumn( 2, "文件名称", LVCFMT_CENTER, Rt.Width()/2 );//插入列
	//m_FileList.InsertColumn( 3, "文件类型", LVCFMT_CENTER, Rt.Width()/3 );
}

void CBackUpDlg::UpdataList(BOOL flag)
{
	if (TRUE == flag)
	{
		m_FileList.DeleteAllItems();
	}

	CString str;
	m_PathName+="\\*.*";  
	HANDLE file;  
	WIN32_FIND_DATA fileData;  
	int num = 0; // 列表号
  
	file = FindFirstFile(m_PathName.GetBuffer(), &fileData);

	bool bState = false;  
	bState = FindNextFile(file, &fileData);  
	while(bState){  
		
		m_FileList.InsertItem(num,NULL);
		str.Format("%d",num);
		m_FileList.SetItemText(num,1,str);

		m_FileList.SetItemText(num,2,fileData.cFileName);
		//wcstombs(line,(const char*)fileData.cFileName,259);  
		bState = FindNextFile(file, &fileData); 
		num++;
	} 
	if (TRUE == flag)
	{
		m_FileList.DeleteItem(0);	
	}	 
}

BOOL CBackUpDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

void CBackUpDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CBackUpDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}
/////////////////////////////////////////////////////////////////////////////
// CBackUpDlg message handlers

void CBackUpDlg::OnBnClickedBtnBackup()
{
	// TODO: Add your control notification handler code here
	system("导出数据表.bat");
	m_PathName = "D:\\MySQLbak";
	UpdataList(TRUE);
}

void CBackUpDlg::OnBnClickedBtnImport()
{
	// TODO: Add your control notification handler code here
	//CFileDialog fileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("All Files (*.*)|*.*||"), NULL);
	//char Path[MAX_PATH];

	//if (IDOK == fileDialog.DoModal())
	//{
	//	m_FileName = fileDialog.GetFileName();
	//	GetCurrentDirectory(MAX_PATH,Path);
	//	m_PathName = Path;
	//	UpdataList(TRUE);
	//	/*system("a.bat");*/
	//	return;
	//}
	//UpdataList(FALSE);
	int nSelIndex;
	CString fileName;

	POSITION pos = m_FileList.GetFirstSelectedItemPosition(); //拿到第一个被选择的项目位置；
	while(pos)
	{ 
		nSelIndex = m_FileList.GetNextSelectedItem(pos);//通过前一个位置,拿到下一个位置的项目的索引号;
		fileName = m_FileList.GetItemText(nSelIndex,2);
	}

	CString CdCmd,ExecCmd;
	CdCmd = "echo off\ncd \/d C:\\MySQL\\MySQL Server 5.0\\bin\n";
	ExecCmd = "mysql -hlocalhost -uroot -p123456 hoteldb <D:\\MySQLbak\\";
	ExecCmd += fileName;

	char* outFile = "导入数据表.bat";
	CStdioFile file;
	CFileException fileException;
	if(file.Open(outFile,CFile::typeText|CFile::modeCreate|CFile::modeReadWrite),&fileException)
	{

		file.WriteString(CdCmd + ExecCmd);

	}
	else
	{
		TRACE("Can't open file %s,error=%u\n",outFile,fileException.m_cause);
	}
	file.Close();

	system("导入数据表.bat");
}

void CBackUpDlg::OnLvnItemchangedListFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;  // 当前行数
	// TODO: Add your control notification handler code here
	if(pNMListView->iItem == -1)
		return;
	
	*pResult = 0;
}

void CBackUpDlg::OnOK()
{

}