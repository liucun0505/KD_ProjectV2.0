#pragma once
#include "MyTreeCtrl.h"
#include "Tools.h"
#include "AccessData.h"
// m_FrameShowWndTree
class m_FrameShowWndTree : public CDockablePane
{
	DECLARE_DYNAMIC(m_FrameShowWndTree)

public:
	m_FrameShowWndTree();
	virtual ~m_FrameShowWndTree();
	CFont m_Font;
	CAccessData m_access;
	CTools m_tools;
	CString m_strlist[1000];
	CImageList m_imageList1;
	void InsertItemToTreeList(CString strTableName);
	void MyExpandTree(HTREEITEM hTreeItem);
protected:
	DECLARE_MESSAGE_MAP()
public:
	MyTreeCtrl m_treeData;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


