// Cmybutton.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "Cmybutton.h"


// Cmybutton

IMPLEMENT_DYNAMIC(Cmybutton, CButton)

Cmybutton::Cmybutton()
{

	EnableAutomation();
}

Cmybutton::~Cmybutton()
{
}

void Cmybutton::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CButton::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(Cmybutton, CButton)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(Cmybutton, CButton)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_Imybutton 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {FA12B997-F103-4706-9280-6B5480D9E8D9}
static const IID IID_Imybutton =
{ 0xFA12B997, 0xF103, 0x4706, { 0x92, 0x80, 0x6B, 0x54, 0x80, 0xD9, 0xE8, 0xD9 } };

BEGIN_INTERFACE_MAP(Cmybutton, CButton)
	INTERFACE_PART(Cmybutton, IID_Imybutton, Dispatch)	
	
END_INTERFACE_MAP()


// Cmybutton 消息处理程序
void Cmybutton::OnRButtonDown(UINT nFlags, CPoint point){
	AfxMessageBox(_T("请连接抄控器"));
}

