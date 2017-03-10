#if !defined(AFX_SUBROOMDETAILINFODLG_H__A2578E03_CFDD_48B2_9167_DAC1ECD27A2B__INCLUDED_)
#define AFX_SUBROOMDETAILINFODLG_H__A2578E03_CFDD_48B2_9167_DAC1ECD27A2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubRoomDetailInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubRoomDetailInfoDlg dialog

class CSubRoomDetailInfoDlg : public CDialog
{
// Construction
public:
	PROOM_DETAIL_ENTRY	m_pCurEntryInfo;
public:
	PVOID GetRelationData();
	void InitContext();
	void InitRoomType();
	void SetRelationData(PVOID lParam);
	 
	CSubRoomDetailInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSubRoomDetailInfoDlg)
	enum { IDD = IDD_SUB_ROOM_DETAIL_INFO_DIALOG };
	CComboBox	m_RoomType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubRoomDetailInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSubRoomDetailInfoDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBROOMDETAILINFODLG_H__A2578E03_CFDD_48B2_9167_DAC1ECD27A2B__INCLUDED_)
