#pragma once


// CLandRecord dialog

class CLandRecord : public CDialog
{
	DECLARE_DYNAMIC(CLandRecord)

public:
	CLandRecord(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLandRecord();
	void SetRelationItem(PVOID pItem);
	void UpdataDLG(CString result);

// Dialog Data
	enum { IDD = IDD_LAND_RECORD };
	HTREEITEM		hItem;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
private:
	CListCtrl		m_RecordList;
	int groupID;
	DWORD power;

	void InitRecordList();
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
	afx_msg void OnBnClickedBtnInquiry();
private:
	void InsertOneRow(int Entry,LPVOID lParam);
public:
	afx_msg void OnBnClickedBtnDelete();
};
