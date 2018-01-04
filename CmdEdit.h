#pragma once


// CmdEdit

class CmdEdit : public CEdit
{
	DECLARE_DYNAMIC(CmdEdit)
	//Overrides
public:
	CmdEdit();
	virtual ~CmdEdit();
	virtual void OnFinalRelease();
	void OnNcPaint();
public:
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg  HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
public:
    CBitmap m_Bitmap;
    CBrush m_Brush;
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnEnChange();
protected:
	
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


