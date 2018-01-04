#pragma once


// ShowNetListView 视图

class ShowNetListView : public CListView
{
	DECLARE_DYNCREATE(ShowNetListView)

protected:
	ShowNetListView();           // 动态创建所使用的受保护的构造函数
	virtual ~ShowNetListView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};

