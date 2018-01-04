#pragma once


// AddMacTest 对话框

class AddMacTest : public CDialogEx
{
	DECLARE_DYNAMIC(AddMacTest)

public:
	AddMacTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddMacTest();

// 对话框数据
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_TYPE;
	CString m_MAC;
	CString m_TEI;
};
