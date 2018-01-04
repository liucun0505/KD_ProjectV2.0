#pragma once
#include "afxcmn.h"
#include "Tools.h"

// DlgTongJiNode 对话框

class DlgTongJiNode : public CDialogEx
{
	DECLARE_DYNAMIC(DlgTongJiNode)

public:
	DlgTongJiNode(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgTongJiNode();

// 对话框数据
	enum { IDD = IDD_DIALOG_TONGJI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
protected:
    CRect m_rect;
    void ChangeSize(UINT nID,int x,int y);
    void ReSize(void);  
    POINT old; 
public:
	void InsertItemToOnlineList(CString strMAC , CString strTEI , CString strAddress , CString strType);
	void InsertItemToLostList(CString strMAC);
	virtual BOOL OnInitDialog();
	afx_msg void OnRSave();
	CListCtrl OnlineList;
	CListCtrl LostList;
	//CTreeCtrl OnlineTree;
	CTools m_tools;
	FILE* m_fp;
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
