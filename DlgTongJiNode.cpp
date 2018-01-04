// DlgTongJiNode.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "DlgTongJiNode.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "Tools.h"

// DlgTongJiNode 对话框

IMPLEMENT_DYNAMIC(DlgTongJiNode, CDialogEx)

DlgTongJiNode::DlgTongJiNode(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgTongJiNode::IDD, pParent)
{


}

DlgTongJiNode::~DlgTongJiNode()
{
}

void DlgTongJiNode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ONLINE, OnlineList);
	DDX_Control(pDX, IDC_LIST_LOST, LostList);
	//DDX_Control(pDX, IDC_TREE_ONLINE, OnlineTree);
}


BEGIN_MESSAGE_MAP(DlgTongJiNode, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LSAVE, &DlgTongJiNode::OnRSave)
END_MESSAGE_MAP()


// DlgTongJiNode 消息处理程序
BOOL DlgTongJiNode::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	    // 获取对话框初始大小    
    GetClientRect(&m_rect);  //获取对话框的大小
    old.x=m_rect.right-m_rect.left;  
    old.y=m_rect.bottom-m_rect.top;
	// TODO:  在此添加额外的初始化
	
	OnlineList.InsertColumn(0,_T(""),LVCFMT_LEFT,50);
	OnlineList.InsertColumn(1,_T("入网MAC地址"),LVCFMT_CENTER,150);
	OnlineList.InsertColumn(2,_T("TEI"),LVCFMT_CENTER,50);
	OnlineList.InsertColumn(3,_T("电表地址"),LVCFMT_CENTER,150);
	OnlineList.InsertColumn(4,_T("模块类型"),LVCFMT_CENTER,200);
	LostList.InsertColumn(0,_T(""),LVCFMT_LEFT,50);
	LostList.InsertColumn(1,_T("未入网MAC地址"),LVCFMT_CENTER,150);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void DlgTongJiNode::ReSize(void)  
{  
    float fsp[2];  
    POINT Newp; //获取现在对话框的大小  
    CRect recta;      
    GetClientRect(&recta);     //取客户区大小    
    Newp.x=recta.right-recta.left;  
    Newp.y=recta.bottom-recta.top;  
    fsp[0]=(float)Newp.x/old.x;  
    fsp[1]=(float)Newp.y/old.y;  
    CRect Rect;  
    int woc;  
    CPoint OldTLPoint,TLPoint; //左上角  
    CPoint OldBRPoint,BRPoint; //右下角  
    HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //列出所有控件    
    while(hwndChild){      
        woc=::GetDlgCtrlID(hwndChild);//取得ID  
        GetDlgItem(woc)->GetWindowRect(Rect);    
        ScreenToClient(Rect);    
        OldTLPoint = Rect.TopLeft();    
        TLPoint.x = long(OldTLPoint.x*fsp[0]);    
        TLPoint.y = long(OldTLPoint.y*fsp[1]);    
        OldBRPoint = Rect.BottomRight();    
        BRPoint.x = long(OldBRPoint.x *fsp[0]);    
        BRPoint.y = long(OldBRPoint.y *fsp[1]);    
        Rect.SetRect(TLPoint,BRPoint);    
        GetDlgItem(woc)->MoveWindow(Rect,TRUE);  
        hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);      
    }
    old=Newp;  
}  
void DlgTongJiNode::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType,cx,cy);
    if(nType!=SIZE_MINIMIZED )  //判断窗口是不是最小化了，因为窗口最小化之后 ，窗口的长和宽会变成0，当前一次变化的时就会出现除以0的错误操作
    {
        ReSize();
    }
}

void DlgTongJiNode::ChangeSize(UINT nID,int x,int y)
{
    CWnd *pWnd = GetDlgItem(nID);
    if(pWnd!=NULL)
    {
        CRect rec;
        pWnd->GetWindowRect(&rec);//获取控件变化前的大小
        ScreenToClient(rec);   //将控件大小装换位在对话框中的区域坐标
        // x / m_rect.Width(); 伸缩rate
        rec.left = rec.left * x / m_rect.Width();
        rec.top = rec.top * y / m_rect.Height();
        rec.bottom = rec.bottom  * y / m_rect.Height();
        rec.right = rec.right * x / m_rect.Width();
        pWnd->MoveWindow(rec);//伸缩控件
    }
}

void DlgTongJiNode::InsertItemToOnlineList(CString strMAC , CString strTEI , CString strAddress , CString strType)
{
	CString strNumb;
	int n = 0;
	n = OnlineList.GetItemCount();
	strNumb.Format(_T("%d") , n + 1);
	OnlineList.InsertItem(n , strNumb);
	OnlineList.SetItemText(n , 1 , strMAC.Mid(0 , 2) + _T(":") + strMAC.Mid(2 , 2) + _T(":") + strMAC.Mid(4 , 2) + _T(":") + strMAC.Mid(6 , 2) + _T(":") + strMAC.Mid(8 , 2) + _T(":") + strMAC.Mid(10 , 2));
	OnlineList.SetItemText(n , 2 , strTEI);
	OnlineList.SetItemText(n , 3 , strAddress);
	switch(_ttoi(strType))
	{
	case 1:
		break;
	case 2:
		OnlineList.SetItemText(n , 4 , _T("集中器载波模块"));
		break;
	case 3:
		break;
	case 4:
		if (strMAC.Find(_T("BEBEBEBEBE")) != -1 )
		{
			OnlineList.SetItemText(n , 4 , _T("抄控器载波模块"));
		} 
		else
		{
			OnlineList.SetItemText(n , 4 , _T("单相表载波模块"));
		}
		break;
	}
	OnlineList.EnsureVisible(n,FALSE);
	OnlineList.RedrawItems(n,n);
}

void DlgTongJiNode::InsertItemToLostList(CString strMAC)
{
	CString strNumb;
	int n = 0;
	n = LostList.GetItemCount();
	strNumb.Format(_T("%d") , n + 1);
	LostList.InsertItem(n , strNumb);
	LostList.SetItemText(n , 1 , strMAC.Mid(0 , 2) + _T(":") + strMAC.Mid(2 , 2) + _T(":") + strMAC.Mid(4 , 2) + _T(":") + strMAC.Mid(6 , 2) + _T(":") + strMAC.Mid(8 , 2) + _T(":") + strMAC.Mid(10 , 2));
	LostList.EnsureVisible(n,FALSE);
	LostList.RedrawItems(n,n);
}

void DlgTongJiNode::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU_SAVESVC));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;

	//while (pWndPopupOwner->GetStyle() & WS_CHILD)
	//	pWndPopupOwner = pWndPopupOwner->GetParent();

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
}

void DlgTongJiNode::OnRSave()
{
        // TODO: Add your control notification handler code here   
    // 设置过滤器   
	CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
    TCHAR szFilter[] = _T("文件(*.csv)");   
    // 构造保存文件对话框   
    CFileDialog fileDlg(FALSE, _T("csv"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);   
    CString strFilePath;   
  
    // 显示保存文件对话框   
    if (IDOK == fileDlg.DoModal())   
    {   	
		int nHang= 0;
		char szANSIString[5000];
		//CString strlist;
		CString strUpDataMessage;

	    CString strlist = fileDlg.GetPathName();  
//int len =WideCharToMultiByte(CP_ACP,0,strlist,-1,NULL,0,NULL,NULL);  
//char *ptxtTemp =new char[len +1];  
//WideCharToMultiByte(CP_ACP,0,strlist,-1,ptxtTemp,len,NULL,NULL ); 
		int len =WideCharToMultiByte(CP_ACP,0,strlist,strlist.GetLength(),NULL,0,NULL,NULL);
		char * pFileName = new char[len + 1];
		WideCharToMultiByte(CP_ACP,0,strlist,strlist.GetLength(),pFileName,len,NULL,NULL);
		pFileName[len] ='\0';

		m_tools.AutoMakedir(pFileName);
		m_fp=fopen(pFileName,"r");
		if  ( m_fp == NULL )
		{
			m_fp=fopen(pFileName,"a+");

			if(m_fp != NULL) 
			{
				CString strTopLine = _T("MAC,TEI,TYPE\n");
				WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
				fwrite(szANSIString,wcslen(strTopLine),1,m_fp);
			}
		}
		else
		{
			fclose(m_fp); 
			m_fp=fopen(pFileName,"a+");
		} 
		int OnCountNum=OnlineList.GetItemCount();
		int LostCountNum=LostList.GetItemCount();
		if(m_fp != NULL) 
		{
			for(int i=0;i<OnCountNum;i++){
				CString strlistData[3];
				//CString strSn;
				//strSn.Format(_T("%d"),2);
				strlistData[0] = OnlineList.GetItemText(i,3);
				strlistData[1]=OnlineList.GetItemText(i,2);;
				strlistData[2]=_T("1");

				CString strTopLine = strlistData[0] + _T(",") + strlistData[1] + _T(",") + strlistData[2]+ _T("\n");
				WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
				fwrite(szANSIString,wcslen(strTopLine),1,m_fp);
			}
			for(int i=0;i<LostCountNum;i++){
				CString strlistData[3];
				//CString strSn;
				//strSn.Format(_T("%d"),2);
				strlistData[0] = LostList.GetItemText(i,1);
				strlistData[1]=_T("");
				strlistData[2]=_T("0");

				CString strTopLine = strlistData[0] + _T(",") + strlistData[1] + _T(",") + strlistData[2]+ _T("\n");
				WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,strTopLine,-1,szANSIString,sizeof(szANSIString),NULL,NULL);
				fwrite(szANSIString,wcslen(strTopLine),1,m_fp);
			}

			fclose(m_fp);
		}
        // 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
        //strFilePath = fileDlg.GetPathName();   
        //AfxMessageBox(strFilePath);//SetDlgItemText(IDC_SAVE_EDIT, strFilePath);   
    }   
}
