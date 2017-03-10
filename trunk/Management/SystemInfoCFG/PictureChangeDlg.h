#if !defined(AFX_PICTURECHANGEDLG_H__9E751ED7_EBCA_4505_9051_A810CF660A95__INCLUDED_)
#define AFX_PICTURECHANGEDLG_H__9E751ED7_EBCA_4505_9051_A810CF660A95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PictureChangeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPictureChangeDlg dialog

class CPictureChangeDlg : public CDialog
{
// Construction
public:
	CPictureChangeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPictureChangeDlg)
	enum { IDD = IDD_PICTURE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictureChangeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPictureChangeDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTURECHANGEDLG_H__9E751ED7_EBCA_4505_9051_A810CF660A95__INCLUDED_)
