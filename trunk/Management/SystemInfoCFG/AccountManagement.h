#pragma once
#include "..\\CommSource\\Project\\usertype.h"

// CAccountManagement dialog

class CAccountManagement : public CDialog
{
	DECLARE_DYNAMIC(CAccountManagement)

public:
	CAccountManagement(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAccountManagement();
	void SetRelationItem(PVOID pItem);
	void UpdataDLG(CString result);

// Dialog Data
	enum { IDD = IDD_ACCOUNT_MANAGEMENT };
	HTREEITEM		hItem;
	PUSER_INFORMATION m_pUSEREntry;
	CListCtrl		m_DataList;
	CEdit			m_EditUser;
	CEdit			m_EditPsw;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnModifyPassword();
	afx_msg void OnBnClickedBtnAddUser();
	afx_msg void OnBnClickedBtnDeleteUser();
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnOK();
public:
	afx_msg void OnClose();
public:
	afx_msg void OnDestroy();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	int groupID;
	DWORD power;	//权限
	int e_Item;    //刚编辑的行  
	int e_SubItem; //刚编辑的列  

	CEdit m_Edit;  //生成单元编辑框对象
	bool haveeditcreate;//标志编辑框已经被创建
	void createEdit(NM_LISTVIEW  *pEditCtrl, CEdit *createdit, int &Item, int &SubItem, bool &havecreat);//创建单元格编辑框函数
	void distroyEdit(CListCtrl *list, CEdit* distroyedit, int &Item, int &SubItem);//销毁单元格编辑框对象
	afx_msg void OnNMClickListAccountdata(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKillfocusEdit();//动态生成编辑框失去焦点响应函数

	void InitDataList();
	void InsertOneRow(int Entry,LPVOID lParam);
	BOOL CheckExit(LPVOID lParam);
};
