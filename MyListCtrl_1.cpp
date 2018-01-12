// MyListCtrl_1.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "MyListCtrl_1.h"


// MyListCtrl_1

IMPLEMENT_DYNAMIC(MyListCtrl_1, CListCtrl)

MyListCtrl_1::MyListCtrl_1()
{

}

MyListCtrl_1::~MyListCtrl_1()
{
}


BEGIN_MESSAGE_MAP(MyListCtrl_1, CListCtrl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()



// MyListCtrl_1 消息处理程序




void MyListCtrl_1::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
    CMenu menu;//
    VERIFY(menu.LoadMenu(IDR_MENUMSGMET));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;

	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}
