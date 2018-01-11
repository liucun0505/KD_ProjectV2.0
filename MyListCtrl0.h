#pragma once


// CMyListCtrl0

class CMyListCtrl0 : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl0)

public:
	CMyListCtrl0();
	virtual ~CMyListCtrl0();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


