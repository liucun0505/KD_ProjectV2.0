// ViewLetTree.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "ViewLetTree.h"
#include "KD_ProjectView.h"
#include "ChildFrm.h"
#include "RightTabView.h"
#include "MainFrm.h"


// CViewLetTree

IMPLEMENT_DYNCREATE(CViewLetTree, CTreeView)

CViewLetTree::CViewLetTree()
{

}

CViewLetTree::~CViewLetTree()
{
}

BEGIN_MESSAGE_MAP(CViewLetTree, CTreeView)
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewLetTree::OnNMClick)
//	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CViewLetTree 诊断

#ifdef _DEBUG
void CViewLetTree::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CViewLetTree::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CViewLetTree 消息处理程序


void CViewLetTree::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	
	// TODO: 在此添加专用代码和/或调用基类
	HICON hIcon[15];      // 图标句柄数组 
	hIcon[0] = theApp.LoadIcon(IDI_CLOSE1); 
	hIcon[1] = theApp.LoadIcon(IDI_OPEN1);
	hIcon[2] = theApp.LoadIcon(IDI_CLOSE2); 
	hIcon[3] = theApp.LoadIcon(IDI_OPEN2); 
	    // 创建图像序列CImageList对象   
    m_ilDrives.Create(25, 32, ILC_COLOR32, 4, 4);   
    // 将三个图标添加到图像序列   
    for (int i=0; i<4; i++)   
    {   
        m_ilDrives.Add(hIcon[i]);   
    }
	GetTreeCtrl().SetImageList(&m_ilDrives, TVSIL_NORMAL);
	HTREEITEM hEagles = GetTreeCtrl().InsertItem(_T("网络搜索"),0,1);
	hEagles = GetTreeCtrl().InsertItem(_T("网络拓扑"),0,1);
	GetTreeCtrl().InsertItem(_T("拓扑显示"),2,3,hEagles);

	hEagles = GetTreeCtrl().InsertItem(_T("模块监控"),0,1);
	GetTreeCtrl().InsertItem(_T("点对点通讯"),2,3,hEagles);
	GetTreeCtrl().InsertItem(_T("故障信息"),2,3,hEagles);

	hEagles = GetTreeCtrl().InsertItem(_T("表档案与表管理"),0,1);
	//GetTreeCtrl().InsertItem(_T("表档案与表管理"),2,3,hEagles);
	//GetTreeCtrl().InsertItem(_T("表档案采集"),2,3,hEagles);
	hEagles = GetTreeCtrl().InsertItem(_T("常用查询与设定"),0,1);
	hEagles = GetTreeCtrl().InsertItem(_T("模块升级"),0,1);
	hEagles = GetTreeCtrl().InsertItem(_T("抄控器转发376.2"),0,1);
	hEagles = GetTreeCtrl().InsertItem(_T("转发应用层报文"),0,1);
}


BOOL CViewLetTree::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (!CTreeView::PreCreateWindow (cs))  
	return FALSE;  
	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS |  
	TVS_SHOWSELALWAYS;
	return TRUE;
}


void CViewLetTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	CMainFrame* pMF=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	NM_TREEVIEW* pHdr = (NM_TREEVIEW*)pNMHDR;
	CString strTreeName = _T("");
	CPoint point;
	UINT uFlag = 0 ;
	GetCursorPos(&point);
	GetTreeCtrl().ScreenToClient(&point);
	HTREEITEM item = GetTreeCtrl().HitTest(point, &uFlag);
	if (GetTreeCtrl().GetChildItem(item) == NULL)
	{
		CChildFrame * pChild = (CChildFrame *)GetParent();
		strTreeName = GetTreeCtrl().GetItemText(item);
		if (strTreeName == _T("网络搜索"))
		{
			GetDocument()->UpdateAllViews(this,0,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("拓扑显示"))
		{
			GetDocument()->UpdateAllViews(this,1,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("点对点通讯"))
		{
			GetDocument()->UpdateAllViews(this,2,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("常用查询与设定"))
		{
			GetDocument()->UpdateAllViews(this,3,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("模块升级"))
		{
			GetDocument()->UpdateAllViews(this,4,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("故障信息"))
		{
			GetDocument()->UpdateAllViews(this,5,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("抄控器转发376.2"))
		{
			GetDocument()->UpdateAllViews(this,6,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("转发应用层报文"))
		{
			GetDocument()->UpdateAllViews(this,9,(CObject *)(LPCTSTR) strTreeName);
		}
		/*if (strTreeName == _T("表档案采集"))
		{
			GetDocument()->UpdateAllViews(this,6,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("模块升级"))
		{
			GetDocument()->UpdateAllViews(this,7,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("配置窗口"))
		{
			GetDocument()->UpdateAllViews(this,8,(CObject *)(LPCTSTR) strTreeName);
		}
		if (strTreeName == _T("转发应用层报文"))
		{
			GetDocument()->UpdateAllViews(this,9,(CObject *)(LPCTSTR) strTreeName);
		}*/
	}
	
	*pResult = 0;
}