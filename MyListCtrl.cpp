// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "KD_Project.h"
#include "MyListCtrl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
	m_itemYes=-1;
	m_nChooseList = -1;
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)//|NM_CUSTOMDRAW
	//ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomdraw )
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
//	ON_COMMAND(ID_COPYFRAME, &CMyListCtrl::OnCopyframe)
//	ON_UPDATE_COMMAND_UI(ID_COPYFRAME, &CMyListCtrl::OnUpdateCopyframe)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers

void   CMyListCtrl::DrawItem(LPDRAWITEMSTRUCT   lpDIS) 
{ 
	CDC* pDC = CDC::FromHandle(lpDIS->hDC); 
	
	LVITEM lvi = {0}; 
	lvi.mask = LVIF_STATE;//|LVIF_IMAGE; 
	lvi.stateMask = LVIS_FOCUSED | LVIS_SELECTED ; 
	lvi.iItem = lpDIS->itemID; 
	BOOL bGet = GetItem(&lvi); 
	
	BOOL bHighlight =((lvi.state & LVIS_DROPHILITED)||((lvi.state & LVIS_SELECTED) && 
		((GetFocus() == this)|| (GetStyle() & LVS_SHOWSELALWAYS)))); 
	
	// 画文本背景 
	CRect rcBack = lpDIS->rcItem; 
	pDC->SetBkMode(TRANSPARENT); 
	if( bHighlight ) 
	{ 
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT)); 
		pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT)); 
		
		pDC->FillRect(rcBack, &CBrush(::GetSysColor(COLOR_HIGHLIGHT))); 
	} 
	else 
	{ 
		CString str = _T("");
		CString str2 = _T("");
		switch (m_nChooseList)
		{
		case 0://信息
			//str = GetItemText(lpDIS->itemID,1);
			str2 = GetItemText(lpDIS->itemID,5);
			if (str2 == "成功")
			{
				pDC->SetTextColor(0x808000);
			}
			if (str2 == "失败")
			{
				pDC->SetTextColor(0x0000FF);
			}
			break;
		case 1://报文
			str = GetItemText(lpDIS->itemID,1);
			if (str == "发送>>")
			{
				pDC->SetTextColor(0x792355);
			}
			if (str == "接收<<")
			{
				pDC->SetTextColor(0x254738);
			}
			break;
		case 2://升级
			return;
		case 3://电表故障
			str = GetItemText(lpDIS->itemID,3);
			if (str == "入网")
			{
				pDC->SetTextColor(0x008000);
			}
			if (str == "未入网")
			{
				pDC->SetTextColor(0x0000FF);
			}
			if (str == "未在白名单")
			{
				pDC->SetTextColor(0x808000);
			}
			break;
		case 4://模块故障
			str = GetItemText(lpDIS->itemID,3);
			if (str == "入网")
			{
				pDC->SetTextColor(0x008000);
			}
			if (str == "未入网")
			{
				pDC->SetTextColor(0x0000FF);
			}
			if (str == "离线")
			{
				pDC->SetTextColor(0xC3C3C3);
			}
			if (str == "未在白名单")
			{
				pDC->SetTextColor(0x808000);
			}
			break;
		}
		
	} 
		//设置字体颜色 
	CString str; 
	
	//得到焦点大小 
	CRect rcFocus = lpDIS->rcItem; 
	rcFocus.DeflateRect(1,1,1,1); 
	
	if (lpDIS->itemAction & ODA_DRAWENTIRE) 
	{ 
		//写文本 
		CString szText; 
		for (int i = 0; i < 10; i++) 
		{ 
			CRect rcItem; 
			if ( !GetSubItemRect(lpDIS->itemID, i, LVIR_LABEL, rcItem )) 
				continue; 
			szText = GetItemText( lpDIS->itemID, i ); 
			rcItem.left += 5;
			rcItem.right -= 1; 
			pDC->DrawText(szText, lstrlen(szText), &rcItem, DT_LEFT|DT_VCENTER|DT_NOPREFIX|DT_SINGLELINE); 
		} 
	}
}



BOOL CMyListCtrl::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	HD_NOTIFY   *pHDNotify   =   (HD_NOTIFY*)lParam; 
	int item;
	switch(   pHDNotify-> hdr.code   )   
	{ 
	case   HDN_ITEMCHANGINGA: 
	case   HDN_ITEMCHANGINGW: 
	case   HDN_ENDTRACK: 
		{ 
			if(pHDNotify-> iItem   ==   0   )//选中的是第一列，以下类似 
                //取得item的值，
			{
				item=GetItemCount();
				RedrawItems(0,item-1);
			}
			if(pHDNotify-> iItem   ==   1   ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);
			}
			
			if(pHDNotify-> iItem   ==   2   ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);
			}
			
            if(pHDNotify-> iItem   ==   3   ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);		
			}
			if(pHDNotify-> iItem   ==   4   ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);		
			}if(pHDNotify-> iItem   ==   5   ) 
			{
				item=GetItemCount();
				RedrawItems(0,item-1);		
			}
			break;
		} 
	} 
	return CListCtrl::OnNotify(wParam, lParam, pResult);
}


void CMyListCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_nChooseList == 1)
	{
		DeleteAllItems();
	}
	*pResult = 0;
	//NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
 //
 //   // Take the default processing unless we set this to something else below.
 //   *pResult = CDRF_DODEFAULT;
 //
 //   // First thing - check the draw stage. If it's the control's prepaint
 //   // stage, then tell Windows we want messages for every item.
 //
 //   if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
 //       {
 //       *pResult = CDRF_NOTIFYITEMDRAW;
 //       }
 //   else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
 //       {
 //       // This is the notification message for an item. We'll request
 //       // notifications before each subitem's prepaint stage.
 //
 //       *pResult = CDRF_NOTIFYSUBITEMDRAW;
 //       }
 //   else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
 //       {
 //       // This is the prepaint stage for a subitem. Here's where we set the
 //       // item's text and background colors. Our return value will tell
 //       // Windows to draw the subitem itself, but it will use the new colors
 //       // we set here.
 //       // The text color will cycle through red, green, and light blue.
 //       // The background color will be light blue for column 0, red for
 //       // column 1, and black for column 2.
 //  
 //       COLORREF crText, crBkgnd;
 //      
 //       if ( 0 == pLVCD->iSubItem )
 //           {
 //           crText = RGB(255,0,0);
 //           crBkgnd = RGB(128,128,255);
 //           }
 //       else if ( 1 == pLVCD->iSubItem )
 //           {
 //           crText = RGB(0,255,0);
 //           crBkgnd = RGB(255,0,0);
 //           }
 //       else
 //           {
 //           crText = RGB(128,128,255);
 //           crBkgnd = RGB(0,0,0);
 //           }
 //
 //       // Store the colors back in the NMLVCUSTOMDRAW struct.
 //       pLVCD->clrText = crText;
 //       pLVCD->clrTextBk = crBkgnd;
 //
 //       // Tell Windows to paint the control itself.
 //       *pResult = CDRF_DODEFAULT;
 //       }
}


void CMyListCtrl::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;//
	switch (m_nChooseList)
	{
	case 0:
		VERIFY(menu.LoadMenu(IDR_MENUMSGMET));
	    break;
	case 1://报文右键菜单
		VERIFY(menu.LoadMenu(IDR_MENU_COPYFRAME));
		break;
	case 2://升级右键菜单
		VERIFY(menu.LoadMenu(IDR_RBMENU_MODERR2));
		break;
	case 3://电报故障右键菜单
		VERIFY(menu.LoadMenu(IDR_RBMENU_METERR));
		break;
	case 4://模块故障右键菜单
		VERIFY(menu.LoadMenu(IDR_RBMENU_MODERR));
		break;
	case 5://模块故障右键菜单
		break;
	}

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;

	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}
void CMyListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int item=GetItemCount();
	RedrawItems(0,item-1);
	m_itemYes=HitTest(point,&nFlags);
}

void CMyListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	RedrawItems(m_itemYes,m_itemYes);
	m_itemYes=HitTest(point,&nFlags);
	
	CListCtrl::OnLButtonDown(nFlags, point);
	if (m_itemYes==(-1))
	{
		int item=GetItemCount();
		RedrawItems(0,item-1);
	}
}