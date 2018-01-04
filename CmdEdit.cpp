// CmdEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "CmdEdit.h"


// CmdEdit

IMPLEMENT_DYNAMIC(CmdEdit, CEdit)

CmdEdit::CmdEdit()
{

	EnableAutomation();
}

CmdEdit::~CmdEdit()
{
}

void CmdEdit::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CEdit::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CmdEdit, CEdit)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CmdEdit, CEdit)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ImdEdit 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {C5AC946D-DCC7-4BA7-A06B-6E8DAE19FBCE}
static const IID IID_ImdEdit =
{ 0xC5AC946D, 0xDCC7, 0x4BA7, { 0xA0, 0x6B, 0x6E, 0x8D, 0xAE, 0x19, 0xFB, 0xCE } };

BEGIN_INTERFACE_MAP(CmdEdit, CEdit)
	INTERFACE_PART(CmdEdit, IID_ImdEdit, Dispatch)
END_INTERFACE_MAP()


// CmdEdit 消息处理程序

//HBRUSH CmdEdit::CtlColor(CDC* pDC, UINT nCtlColor)
//{
// COLORREF clr = RGB(255,0,0);
// pDC->SetTextColor(clr);   //设置黑色的文本
// clr = RGB(255,0,0);
// pDC->SetBkColor(clr);     //设置红色的背景
// HBRUSH m_bkBrush = ::CreateSolidBrush(clr);
// return m_bkBrush;  //作为约定，返回背景色对应的刷子句柄
//}
//HBRUSH CmdEdit::CtlColor(CDC* pDC, UINT nCtlColor)  
//{     
//    pDC->SetBkMode(TRANSPARENT);                 // 透明     
//    pDC->SetTextColor(RGB(23, 236, 26));           // 字体色彩   
//    return (HBRUSH)GetStockObject(DKGRAY_BRUSH);    // 字体背景(OnEraseBkgnd只是避免闪烁)  
//}  

//void CmdEdit::OnNcpaint()  
//{  
//    CRect rect, rc;  
//    CDC* pDC;  
//    int  nSaveDC;  
//  
//  
//    pDC = GetWindowDC();  
//    GetWindowRect(&rect);  
//    rect -= rect.TopLeft();  
//  
//  
//    rc = rect;  
//    rc.InflateRect(-GetSystemMetrics(SM_CXEDGE), -GetSystemMetrics(SM_CYEDGE));  
//  
//  
//    nSaveDC = pDC->SaveDC();  
//    pDC->ExcludeClipRect(&rc);  
//    pDC->FillSolidRect(&rect, RGB(24,24,255));  
//    pDC->RestoreDC(nSaveDC);  
//  
//  
//    pDC->FrameRect(&rect, &CBrush(RGB(24,254,35)));  
//    ReleaseDC(pDC);  
//}  


void CmdEdit::OnNcPaint()
{
	CRect rc;
	GetWindowRect(&rc);
	CRect rcWindow(0,0,rc.Width(),rc.Height());

	CBrush brushFrame;
	brushFrame.CreateSolidBrush(RGB(255,24,11));

	CWindowDC dc(this);
	dc.FrameRect(&rcWindow,&brushFrame);
}
BOOL CmdEdit::OnEraseBkgnd(CDC* pDC)
{
     //TODO: 在此添加消息处理程序代码和/或调用默认值
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    memDC.SelectObject(&m_Bitmap);
    BITMAP m_Bmp;
    m_Bitmap.GetBitmap(&m_Bmp);
    CRect rect;
    GetClientRect(&rect);
//拉伸贴图
    pDC->StretchBlt(0,0,rect.Width() ,rect.Height(),&memDC,0,0,m_Bmp.bmWidth,m_Bmp.bmHeight,SRCCOPY);
    memDC.DeleteDC();
    return TRUE;
    //return CEdit::OnEraseBkgnd(pDC);
}
HBRUSH CmdEdit::CtlColor(CDC* pDC,  UINT nCtlColor)
{
    // TODO:  在此更改 DC 的任何属性
//透明
    pDC->SetBkMode(TRANSPARENT);
	//pDC->SetTextColor
//字体色彩
    pDC->SetTextColor(RGB(0,255,0));
//空的画笔
        return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
    // TODO:  如果默认的不是所需画笔，则返回另一个画笔
}
void CmdEdit::OnEnChange()
{
//使无效
    Invalidate();
}