// MyListCtrl0.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "MyListCtrl0.h"


// CMyListCtrl0

IMPLEMENT_DYNAMIC(CMyListCtrl0, CListCtrl)

CMyListCtrl0::CMyListCtrl0()
{

}

CMyListCtrl0::~CMyListCtrl0()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl0, CListCtrl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()



// CMyListCtrl0 消息处理程序




void CMyListCtrl0::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 在此处添加消息处理程序代码
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENUMSGMET));
		CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;

	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}
