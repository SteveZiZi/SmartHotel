#if !defined(AFX_MAINREALSTATUSDLG_H__B33C19E0_F3D5_40FC_8CAE_C5E25F3B6019__INCLUDED_)
#define AFX_MAINREALSTATUSDLG_H__B33C19E0_F3D5_40FC_8CAE_C5E25F3B6019__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainRealStatusDlg.h : header file
//
#include "LoadDlg.h"
/////////////////////////////////////////////////////////////////////////////
//�б��ؼ�
#include "..\\CommSource\\ListCtrl\\ListCtrlCl.h"
// CMainRealStatusDlg dialog
#define MAX_FLOOR_NUMBER	23
#define MAX_COUNT			150

//��ѯ�����ṹ��
typedef struct _SEARCH_CONDITION
{
	int	 nRoomType;			//����
	int  nBuilding;			//¥��
	
	int  nFloor;			//¥��		
}SEARCH_CONDITION,*PSEARCH_CONDITION;
//*************************************************


/////////////////////////////////////////////////////////////////////////////////
class CMainRealStatusDlg : public CDialog
{
public:
	PDWORD	pRoomTypeValue;					//��̬����
	BOOL	lReportStyle;					//���ڼ�¼��ǰ�б�ķ��
	SEARCH_CONDITION	m_Condition;

	//HANDLE	hInquiryThread;
// Construction
public:
    HWND hParentHwnd;
	CMenu  *m_pMenu;     
	CLoadDlg *pLoadDlg;
public:  //��������Ķ�̬���ӿ�
	HINSTANCE  hRoomModule;
    AFX_CALLDETAILMODULE CallDetailModule;
public:		//���¸���Ĺ��ܺ���
	int GetOneRoomDetail(int EntryIndex,PVOID lParam);
	int QuirySelRoomInfo(PVOID lParam);						//��ѯ��ǰ�ͷ�
	static UINT InquiryListRoomThread(PVOID lParam);		//��ѯ�߳�
	static UINT GetRoomInfoThread(PVOID lParam);

	void ConvertSearchCondition();
	void RefreshFloor(DWORD dwMaxFloor);
	void RefreshRoomType();									//�����
	void RefreshQuickRoomList(const char* sFilter);			//�����
	void RefresBuild();										//�ͷ���
	void ReloadRoomStateInfo();

	bool GetRoomTypeString(unsigned long Value,CString &str);		//�õ�������
	void InsertOneRoomEntry(PVOID lParam);							//���б��м�һ������
		
	void ReleaseAllMemory();
	void LoadImageList();
	void LoadFunModule();
	void InitPopMenu();
	void InitAllItem();
	void AdjustItemPosition();

	static CString WriteTempStatusToList(LPVOID lParam, int &airNum,CString &AirStatus);
	static CString WriteAirConditionToList(LPVOID lParam);
	static CString TempStatus(PVOID lParam,int &airNum,CString &AirStatus);
	static CString AirCondition(PVOID lParam,int &airNum);

	CMainRealStatusDlg(CWnd* pParent = NULL);   // standard constructor
    ~CMainRealStatusDlg();
// Dialog Data
	//{{AFX_DATA(CMainRealStatusDlg)
	enum { IDD = IDD_MAINREALSTATUS_DIALOG };
	CTabCtrl	m_BasicRoomStatus;
	CTabCtrl	m_RoomType;
	//CListCtrl	m_Room;
	CListCtrlCl m_Room;
	CComboBox	m_Floor;
	CComboBox	m_Building;
	BOOL		m_Flag;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainRealStatusDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainRealStatusDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickRsRoomlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelchangeComboBuilding();
	afx_msg void OnSelchangeComboFloor();
	afx_msg void OnSelchangeRsRoomtypetab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINREALSTATUSDLG_H__B33C19E0_F3D5_40FC_8CAE_C5E25F3B6019__INCLUDED_)
