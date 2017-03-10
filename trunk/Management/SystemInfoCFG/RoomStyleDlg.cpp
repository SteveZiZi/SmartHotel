// RoomStyleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoCFG.h"
#include "RoomStyleDlg.h"


// CRoomStyleDlg dialog

IMPLEMENT_DYNAMIC(CRoomStyleDlg, CDialog)

CRoomStyleDlg::CRoomStyleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomStyleDlg::IDD, pParent)
{

}

CRoomStyleDlg::~CRoomStyleDlg()
{
}

void CRoomStyleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX,IDC_CHECK_EMERGENCY,m_CheckEmergency);
	DDX_Check(pDX,IDC_CHECK_DOOR_STATUS,m_CheckDoorStatus);
	DDX_Check(pDX,IDC_CHECK_MAGNETISM,m_CheckmMagnetmis);
	DDX_Check(pDX,IDC_CHECK_SUPPLY,m_CheckSupply);
	DDX_Check(pDX,IDC_CHECK_CLEAN,m_CheckClean);
	DDX_Check(pDX,IDC_CHECK_WASH,m_CheckWash);
	DDX_Check(pDX,IDC_CHECK_NODISTRUCT,m_CheckNoDistruct);
	DDX_Check(pDX,IDC_CHECK_WAIT,m_CheckWait);

	DDX_Check(pDX,IDC_CHECK_INFRARED,m_CheckInfrared);
	DDX_Check(pDX,IDC_CHECK_SERVER,m_CheckServer);
	DDX_Check(pDX,IDC_CHECK_BALCONY_MAGNETMIS,m_CheckBalconyMagnetmis);
	DDX_Check(pDX,IDC_CHECK_BED,m_CheckBed);
	DDX_Check(pDX,IDC_CHECK_SAFE,m_CheckSafe);
	DDX_Check(pDX,IDC_CHECK_CHECKOUT,m_CheckCheckOut);
	DDX_Check(pDX,IDC_CHECK_ACCOUNT,m_CheckAccount);
	DDX_Check(pDX,IDC_CHECK_REPAIR,m_CheckRepair);
}


BEGIN_MESSAGE_MAP(CRoomStyleDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CRoomStyleDlg::OnBnClickedBtnSave)
END_MESSAGE_MAP()

BOOL CRoomStyleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	InitAllItems();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRoomStyleDlg::InitAllItems()
{
	CString str;
	CString fileName = "config.txt";

	CStdioFile file;

	CFileException fileException;

	if(file.Open(fileName,CFile::typeText|CFile::modeRead),&fileException)
	{

		file.ReadString(str);

	}
	else
	{
		TRACE("Can't open file %s,error=%u\n",fileName,fileException.m_cause);
	}
	file.Close();

	char tempStr[16];
	for (int i = 0;i < str.GetLength();i++)
	{
		tempStr[i] = str[i];
	}
	if ('0' != tempStr[0])
	{
		m_CheckEmergency = TRUE;
	}
	else
	{
		m_CheckEmergency = FALSE;
	}

	if ('0' != tempStr[1])
	{
		m_CheckDoorStatus = TRUE;
	}
	else
	{
		m_CheckDoorStatus = FALSE;
	}

	if ('0' != tempStr[2])
	{
		m_CheckmMagnetmis = TRUE;
	}
	else
	{
		m_CheckmMagnetmis = FALSE;
	}

	if ('0' != tempStr[3])
	{
		m_CheckSupply = TRUE;
	}
	else
	{
		m_CheckSupply = FALSE;
	}

	if ('0' != tempStr[4])
	{
		m_CheckClean = TRUE;
	}
	else
	{
		m_CheckClean = FALSE;
	}

	if ('0' != tempStr[5])
	{
		m_CheckWash = TRUE;
	}
	else
	{
		m_CheckWash = FALSE;
	}

	if ('0' != tempStr[6])
	{
		m_CheckNoDistruct = TRUE;
	}
	else
	{
		m_CheckNoDistruct = FALSE;
	}

	if ('0' != tempStr[7])
	{
		m_CheckWait = TRUE;
	}
	else
	{
		m_CheckWait = FALSE;
	}

	if ('0' != tempStr[8])
	{
		m_CheckInfrared = TRUE;
	}
	else
	{
		m_CheckInfrared = FALSE;
	}

	if ('0' != tempStr[9])
	{
		m_CheckServer = TRUE;
	}
	else
	{
		m_CheckServer = FALSE;
	}

	if ('0' != tempStr[10])
	{
		m_CheckBalconyMagnetmis = TRUE;
	}
	else
	{
		m_CheckBalconyMagnetmis = FALSE;
	}

	if ('0' != tempStr[11])
	{
		m_CheckBed = TRUE;
	}
	else
	{
		m_CheckBed = FALSE;
	}

	if ('0' != tempStr[12])
	{
		m_CheckSafe = TRUE;
	}
	else
	{
		m_CheckSafe = FALSE;
	}

	if ('0' != tempStr[13])
	{
		m_CheckCheckOut = TRUE;
	}
	else
	{
		m_CheckCheckOut = FALSE;
	}

	if ('0' != tempStr[14])
	{
		m_CheckAccount = TRUE;
	}
	else
	{
		m_CheckAccount = FALSE;
	}

	if ('0' != tempStr[15])
	{
		m_CheckRepair = TRUE;
	}
	else
	{
		m_CheckRepair = FALSE;
	}

	/*m_CheckEmergency = TRUE;
	m_CheckDoorStatus = TRUE;
	m_CheckClean = TRUE;
	m_CheckWash = TRUE;
	m_CheckNoDistruct = TRUE;

	m_CheckServer = TRUE;
	m_CheckCheckOut = TRUE;
	m_CheckRepair = TRUE;*/
	UpdateData(FALSE); // 在前面dataexchange中绑定BOOL型变量后这句是必须的
}

BOOL CRoomStyleDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}

void CRoomStyleDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CRoomStyleDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}
// CRoomStyleDlg message handlers

void CRoomStyleDlg::OnBnClickedBtnSave()
{
	// TODO: Add your control notification handler code here
	CButton* pBtn;
	int state;
	CString str;

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_EMERGENCY);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckEmergency = TRUE;
		str = "1";
	}
	else
	{
		m_CheckEmergency = FALSE;
		str = "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_DOOR_STATUS);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckDoorStatus = TRUE;
		str += "1";
	}
	else
	{
		m_CheckDoorStatus = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_MAGNETISM);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckmMagnetmis = TRUE;
		str += "1";
	}
	else
	{
		m_CheckmMagnetmis = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_SUPPLY);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckSupply = TRUE;
		str += "1";
	}
	else
	{
		m_CheckSupply = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_CLEAN);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckClean = TRUE;
		str += "1";
	}
	else
	{
		m_CheckClean = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_WASH);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckWash = TRUE;
		str += "1";
	}
	else
	{
		m_CheckWash = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_NODISTRUCT);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckNoDistruct = TRUE;
		str += "1";
	}
	else
	{
		m_CheckNoDistruct = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_WAIT);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckWait = TRUE;
		str += "1";
	}
	else
	{
		m_CheckWait = FALSE;
		str += "0";
	}

	/////////////////////////////////
	pBtn = (CButton*)GetDlgItem(IDC_CHECK_INFRARED);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckInfrared = TRUE;
		str += "1";
	}
	else
	{
		m_CheckInfrared = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_SERVER);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckServer = TRUE;
		str += "1";
	}
	else
	{
		m_CheckServer = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_BALCONY_MAGNETMIS);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckBalconyMagnetmis = TRUE;
		str += "1";
	}
	else
	{
		m_CheckBalconyMagnetmis = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_BED);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckBed = TRUE;
		str += "1";
	}
	else
	{
		m_CheckBed = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_SAFE);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckSafe = TRUE;
		str += "1";
	}
	else
	{
		m_CheckSafe = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_CHECKOUT);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckCheckOut = TRUE;
		str += "1";
	}
	else
	{
		m_CheckCheckOut = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_ACCOUNT);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckAccount = TRUE;
		str += "1";
	}
	else
	{
		m_CheckAccount = FALSE;
		str += "0";
	}

	pBtn = (CButton*)GetDlgItem(IDC_CHECK_REPAIR);
	state = pBtn->GetCheck();
	if (state)
	{
		m_CheckRepair = TRUE;
		str += "1";
	}
	else
	{
		m_CheckRepair = FALSE;
		str += "0";
	}
	UpdateData(FALSE);

	char* fileName = "config.txt";

	CStdioFile file;

	CFileException fileException;

	if(file.Open(fileName,CFile::typeText|CFile::modeCreate|CFile::modeReadWrite),&fileException)

	{

		file.WriteString(str);

	}

	else

	{
		TRACE("Can't open file %s,error=%u\n",fileName,fileException.m_cause);
	}
	file.Close();
}

void CRoomStyleDlg::OnOK()
{

}
