#pragma once


// ShowNetTreeView 视图

class ShowNetTreeView : public CTreeView
{
	DECLARE_DYNCREATE(ShowNetTreeView)

protected:
	ShowNetTreeView();           // 动态创建所使用的受保护的构造函数
	virtual ~ShowNetTreeView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};
