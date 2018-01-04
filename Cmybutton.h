#pragma once


// Cmybutton

class Cmybutton : public CButton
{
	DECLARE_DYNAMIC(Cmybutton)

public:
	Cmybutton();
	virtual ~Cmybutton();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


