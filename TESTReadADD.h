#pragma once


// CTESTReadADD
#include "User_Mcu_Cfg.h"
#include "Tools.h"
#include "GW13762.h"
#include "CDTL2007.h"
class CTESTReadADD : public CWnd
{
	DECLARE_DYNAMIC(CTESTReadADD)

public:
	CTESTReadADD();
	virtual ~CTESTReadADD();
	void C3762_TEST(HTREEITEM hTree);//方案处理函数
	CTools m_tool;
	CGW13762 m_Cgw13762;
protected:
	DECLARE_MESSAGE_MAP()
};


