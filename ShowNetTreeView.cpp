// ShowNetTreeView.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "ShowNetTreeView.h"


// ShowNetTreeView

IMPLEMENT_DYNCREATE(ShowNetTreeView, CTreeView)

ShowNetTreeView::ShowNetTreeView()
{

}

ShowNetTreeView::~ShowNetTreeView()
{
}

BEGIN_MESSAGE_MAP(ShowNetTreeView, CTreeView)
END_MESSAGE_MAP()


// ShowNetTreeView 诊断

#ifdef _DEBUG
void ShowNetTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void ShowNetTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// ShowNetTreeView 消息处理程序



BOOL ShowNetTreeView::PreCreateWindow(CREATESTRUCT& cs)//定义tree风格
{
	// TODO: 在此添加专用代码和/或调用基类
	if (!CTreeView::PreCreateWindow (cs))  
	    return FALSE;  
	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS |  
	TVS_SHOWSELALWAYS;

	 return TRUE;
}


