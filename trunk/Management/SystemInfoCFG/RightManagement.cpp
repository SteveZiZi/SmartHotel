// RightManagement.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInfoCFG.h"
#include "RightManagement.h"


// CRightManagement dialog

IMPLEMENT_DYNAMIC(CRightManagement, CDialog)

CRightManagement::CRightManagement(CWnd* pParent /*=NULL*/)
	: CDialog(CRightManagement::IDD, pParent)
{

}

CRightManagement::~CRightManagement()
{
}

void CRightManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRightManagement, CDialog)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CRightManagement::OnBnClickedBtnSave)
END_MESSAGE_MAP()

BOOL CRightManagement::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CRightManagement::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnClose();
}

void CRightManagement::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CRightManagement::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnEraseBkgnd(pDC);
}

BOOL CRightManagement::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::PreTranslateMessage(pMsg);
}
// CRightManagement message handlers

void CRightManagement::SetRelationItem(PVOID pItem)
{
	if(pItem != NULL)
		hItem = (HTREEITEM)pItem;
}
void CRightManagement::OnBnClickedBtnSave()
{
	// TODO: Add your control notification handler code here
}

void CRightManagement::UpdataDLG(CString result)
{

}

void CRightManagement::OnOK()
{

}