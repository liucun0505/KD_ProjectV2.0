// FrameShowWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "FrameShowWnd.h"


// CFrameShowWnd

IMPLEMENT_DYNAMIC(CFrameShowWnd, CDockablePane)

CFrameShowWnd::CFrameShowWnd()
{


}

CFrameShowWnd::~CFrameShowWnd()
{
}


BEGIN_MESSAGE_MAP(CFrameShowWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
//	ON_COMMAND(ID_COPYFRAME, &CFrameShowWnd::OnCopyframe)
END_MESSAGE_MAP()



// CFrameShowWnd 消息处理程序




int CFrameShowWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;      

	m_Font.CreatePointFont(94,_T("宋体"));

	CRect rectDummy;
	rectDummy.SetRectEmpty(); 
	m_myTabCtrl.Create(TCS_TABS|WS_CHILD|WS_VISIBLE,rectDummy,this,IDC_TABLE_MYSHOWFRAME);   
	m_myTabCtrl.SetFont(&m_Font); 
	m_myTabCtrl.InsertItem(0,_T("     电表信息     "));  
	m_myTabCtrl.InsertItem(1,_T("     报文记录     ")); 
	m_myTabCtrl.InsertItem(2,_T("      命令行      "));
	m_myTabCtrl.InsertItem(3,_T("   376.2报文解析  "));
	return 0;
}


void CFrameShowWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if (GetSafeHwnd() == NULL)  
	{
		return;
	}
	CRect rectClient;
	GetClientRect(rectClient); 
	m_myTabCtrl.SetWindowPos(NULL, rectClient.left + 1, rectClient.top  + 1, rectClient.Width() - 2, rectClient.Height()  - 2, SWP_NOACTIVATE | SWP_NOZORDER);

}


