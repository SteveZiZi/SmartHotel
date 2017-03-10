#if !defined(AFX_MAINREALSTATUSDLG_H__B33C19E0_F3D5_40FC_8CAE_C5E25F3B6019__INCLUDED_)
#define AFX_MAINREALSTATUSDLG_H__B33C19E0_F3D5_40FC_8CAE_C5E25F3B6019__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainRealStatusDlg.h : header file
//
#include "LoadDlg.h"
/////////////////////////////////////////////////////////////////////////////
//列表框控件
#include "..\\CommSource\\ListCtrl\\ListCtrlCl.h"
// CMainRealStatusDlg dialog
#define MAX_FLOOR_NUMBER	23
#define MAX_COUNT			150

//查询条件结构体
typedef struct _SEARCH_CONDITION
{
	int	 nRoomType;			//房类
	int  nBuilding;			//楼座
	
	int  nFloor;			//楼层		
}SEARCH_CONDITION,*PSEARCH_CONDITION;
//*************************************************


/////////////////////////////////////////////////////////////////////////////////
class CMainRealStatusDlg : public CDialog
{
public:
	PDWORD	pRoomTypeValue;					//房态数据
	BOOL	lReportStyle;					//用于记录当前列表的风格
	SEARCH_CONDITION	m_Condition;

	//HANDLE	hInquiryThread;
// Construction
public:
    HWND hParentHwnd;
	CMenu  *m_pMenu;     
	CLoadDlg *pLoadDlg;
public:  //房间详情的动态链接库
	HINSTANCE  hRoomModule;
    AFX_CALLDETAILMODULE CallDetailModule;
public:		//更新各表的功能函数
	int GetOneRoomDetail(int EntryIndex,PVOID lParam);
	int QuirySelRoomInfo(PVOID lParam);						//查询当前客房
	static UINT InquiryListRoomThread(PVOID lParam);		//查询线程
	static UINT GetRoomInfoThread(PVOID lParam);

	void ConvertSearchCondition();
	void RefreshFloor(DWORD dwMaxFloor);
	void RefreshRoomType();									//房类表
	void RefreshQuickRoomList(const char* sFilter);			//房间表
	void RefresBuild();										//客房表
	void ReloadRoomStateInfo();

	bool GetRoomTypeString(unsigned long Value,CString &str);		//得到房类名
	void InsertOneRoomEntry(PVOID lParam);							//往列表中加一个房间
		
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
