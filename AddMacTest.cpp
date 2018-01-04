// AddMacTest.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "AddMacTest.h"
#include "afxdialogex.h"


// AddMacTest 对话框

IMPLEMENT_DYNAMIC(AddMacTest, CDialogEx)

AddMacTest::AddMacTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddMacTest::IDD, pParent)
	, m_TYPE(_T(""))
	, m_MAC(_T(""))
	, m_TEI(_T(""))
{

}

AddMacTest::~AddMacTest()
{
}

void AddMacTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_TYPE);
	DDV_MaxChars(pDX, m_TYPE, 1);
	DDX_Text(pDX, IDC_EDIT1, m_MAC);
	DDV_MaxChars(pDX, m_MAC, 12);
	DDX_Text(pDX, IDC_EDIT2, m_TEI);
	DDV_MaxChars(pDX, m_TEI, 6);
}


BEGIN_MESSAGE_MAP(AddMacTest, CDialogEx)
END_MESSAGE_MAP()


// AddMacTest 消息处理程序
