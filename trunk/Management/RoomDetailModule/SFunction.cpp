#include "stdafx.h"
#include "RoomDetailModule.h"
#include "SFunction.h"
#include "MainRoomInfoDlg.h"

CMySQL_API *m_mysql;
////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
ROOM_MODULE_API  int CallDetailModule(LPVOID lParam,LPVOID wParam,int Index)
{ 
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); 
	CMainRoomInfoDlg *m_pDlg;
	INT_PTR Result = IDOK;
	m_mysql = (CMySQL_API *)lParam;

	m_pDlg = new CMainRoomInfoDlg;
	if (m_pDlg == NULL)	{	return IDCANCEL;}
	m_pDlg->SetDataBuffer(lParam);
	m_pDlg->nSelect = Index%3;
	////m_pDlg->SetDefaultModule(Index);   //设置默认的选项
	////m_pDlg->SetDefaultBuf(lParam);
	Result = m_pDlg->DoModal();
	delete m_pDlg;
	C_ChannelFactory::CloseAllChannels();
	return (int)Result;
}
