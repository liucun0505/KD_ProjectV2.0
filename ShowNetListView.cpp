// ShowNetListView.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "ShowNetListView.h"


// ShowNetListView

IMPLEMENT_DYNCREATE(ShowNetListView, CListView)

ShowNetListView::ShowNetListView()
{

}

ShowNetListView::~ShowNetListView()
{
}

BEGIN_MESSAGE_MAP(ShowNetListView, CListView)
END_MESSAGE_MAP()


// ShowNetListView 诊断

#ifdef _DEBUG
void ShowNetListView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void ShowNetListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// ShowNetListView 消息处理程序


BOOL ShowNetListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CListView::PreCreateWindow(cs);
		if (!CListView::PreCreateWindow (cs))  
	    return FALSE;  
	cs.style |= WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_OWNERDRAWFIXED;

	return TRUE;
}
