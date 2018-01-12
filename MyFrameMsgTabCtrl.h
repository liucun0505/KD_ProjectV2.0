#pragma once
#include "CmdEdit.h"
#include "Cmybutton.h"
// CMyFrameMsgTabCtrl
#include "MyListCtrl.h"
#include "MyListCtrl_1.h"
#include "Tools.h"
class CMyFrameMsgTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyFrameMsgTabCtrl)

public:
	CMyFrameMsgTabCtrl();
	virtual ~CMyFrameMsgTabCtrl();


protected:
	DECLARE_MESSAGE_MAP()

public:
	MyListCtrl_1  m_ctrlMssage;
	CMyListCtrl m_ctrlFrame;
	CEdit* m_editMLH ;//(CEdit*)GetDlgItem(IDC_EDIT1);
	CEdit* m_editRec ;
	CmdEdit m_cmdedit_send;
	CmdEdit m_cmdedit_rec;
	CFont m_Font100H;
	CFont m_Font100K;
	HANDLE m_hCMDThread;
	//IDC_BUTTON_READ
	CButton * m_button;
	CButton *m_checkboxbutton;
	Cmybutton m_MYButton;
	CButton * m_DecodeButton;
	CButton * m_ClearDecodeButton;
	CmdEdit m_cmdedit_Code;
	CmdEdit m_cmdedit_Decode;
	CToolTipCtrl m_stat;
	CTools Tools;

	afx_msg void appendText(CmdEdit *edit,CString mStr);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	//afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonCMD();
	afx_msg void OnBnClickedButtonDECODE();
	afx_msg void OnBnClickedButtonClearDECODE();
	
};


