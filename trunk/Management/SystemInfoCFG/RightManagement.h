#pragma once


// CRightManagement dialog

class CRightManagement : public CDialog
{
	DECLARE_DYNAMIC(CRightManagement)

public:
	CRightManagement(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRightManagement();
	void SetRelationItem(PVOID pItem);
	void UpdataDLG(CString result);

// Dialog Data
	enum { IDD = IDD_RIGHT_MANAGEMENT };
	HTREEITEM		hItem;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnClose();
public:
	afx_msg void OnDestroy();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	afx_msg void OnOK();
	afx_msg void OnBnClickedBtnSave();
};
