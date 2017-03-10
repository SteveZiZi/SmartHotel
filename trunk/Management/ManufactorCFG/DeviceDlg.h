#if !defined(AFX_DEVICEDLG_H__786693F8_10A5_41D3_B85E_8A05B4F5CF0A__INCLUDED_)
#define AFX_DEVICEDLG_H__786693F8_10A5_41D3_B85E_8A05B4F5CF0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeviceDlg.h : header file
//
//#include "MyListCtrlEx.h"
/////////////////////////////////////////////////////////////////////////////
#define MAX_ENTRY_NUMBER      5
// CDeviceDlg dialog

class CDeviceDlg : public CDialog
{
public:
	ITEM_ENTRTY m_PreItem;		
	CEdit		*pEdit;
public:
	afx_msg LRESULT DoAddOpt(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT DoModifyOpt(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT DoDeleteOpt(WPARAM wParam, LPARAM lParam);
public:
	ULONG GetNextDbIndex();
	void UpdataItemStringFromEdit(unsigned int nItem, unsigned int nSubItem);
	void SetEditStringFromItem(unsigned int nItem, unsigned int nSubItem);
	int InertOneRow(int Index,LPVOID lParam);
	void DeleteAllListContext();
	void EnumAllTableRecord(int TableIndex);

	void InitDeviceListCtrl();
	void InitDeviceClass();
	CDeviceDlg(CWnd* pParent = NULL);   // standard constructor
    ~CDeviceDlg();
// Dialog Data
	//{{AFX_DATA(CDeviceDlg)
	enum { IDD = IDD_DEVICE_DIALOG };
	CListCtrl	m_DeviceList;
	//CMyListCtrlEx m_DeviceList;

	CTabCtrl	m_DeviceEntry;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeviceDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeviceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabDeviceclass(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListDevice(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListDevice(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICEDLG_H__786693F8_10A5_41D3_B85E_8A05B4F5CF0A__INCLUDED_)
