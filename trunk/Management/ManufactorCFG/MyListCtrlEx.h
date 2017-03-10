#if !defined(AFX_MYLISTCTRLEX_H__FE1498EE_4049_41EC_A6A2_F40B656AFF17__INCLUDED_)
#define AFX_MYLISTCTRLEX_H__FE1498EE_4049_41EC_A6A2_F40B656AFF17__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrlEx.h : header file
//
/////////////////////////////////////////////////////////////////////////////
typedef struct _LIST_DATA_INFO
{
//对象类型
	DWORD dItemType;                 //对象类型和消息映射的一样
	int   EnableItem;                //是否灰掉
	BOOL  bUpdate;                   //是否有更新
	int   bSubItemStatus;            //子控件的状态(或是按钮的参数)
	int   nImaegIndex;
    

	LPVOID lpItemData;
}LIST_DATA_INFO,*PLIST_DATA_INFO;
/////////////////////////////////////////////////////////////////////////////
enum _SUBITEM_TYPE
{
	OSB_DEFAULT = 0,
	OSB_BUTTON,
	OSB_PICTURE,
	OSB_CHECKBUTTON,

};
// CMyListCtrlEx window





class CMyListCtrlEx : public CListCtrl
{
public:
	COLORREF		m_crWindow;
	COLORREF		m_crWindowText;
	COLORREF		m_crGrayText;

	int m_ItemHight;
	CFont m_Font; 
// Construction
public:
	CMyListCtrlEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrlEx)
	protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual int  InsertItem(int nItem, LPCTSTR lpszItem, int nImage=0);
	virtual BOOL SetItemText(int nItem, int nSubItem, LPTSTR lpszText);
	//virtual int SetItemData(int nItem, DWORD dwData);


public:
	void DrawItemButton(CDC *pDC,CRect iRect,LPCSTR lString,LPVOID lParam);
	void SetItemStatus(int nItem, int nSubItem,int nStatus);
	void DrawCheckBtn(CDC *pDC,CRect iRect, LPCSTR lpString,LPVOID lParam);
	void DrawItemPicture(CDC *pDC,LPCSTR imageName,CRect iRect);
	void DrawItemText(CDC *pDC,LPCSTR iString,CRect iRect,int  iFmt);
	void DrawSubItem(CDC *pDC,CRect rt,int Item);
	void SetTextAttr(int nHigh,const LPCSTR Shape,COLORREF  cText);
	void DrawAllItemFrame(CDC *pDC,CRect rt);
	void SetItemHigh(int nHigh);
	virtual ~CMyListCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrlEx)
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRLEX_H__FE1498EE_4049_41EC_A6A2_F40B656AFF17__INCLUDED_)
