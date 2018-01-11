// MyFrameMsgTabCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "KD_Project.h"
#include "MyFrameMsgTabCtrl.h"
#include "MainFrm.h"
#include "SimJzq.h"
#include "GW13762.h"
#include "LogFile.h"
#include "CSG13762.h"
extern CLogFile plog;//打引用
extern CGW13762 Cgw13762;
extern CCSG13762 Ccsg13762;
extern CSimJzq  gSimJzq;
// CMyFrameMsgTabCtrl

IMPLEMENT_DYNAMIC(CMyFrameMsgTabCtrl, CTabCtrl)

CMyFrameMsgTabCtrl::CMyFrameMsgTabCtrl()
{
	//m_stat.Create(this);  
 //   m_stat.AddTool(GetDlgItem(IDC_BUTTON_MYBUTTON), _T("你想要添加的提示信息"));//.AddTool( GetDlgItem(IDC_BUTTON_MYBUTTON), "你想要添加的提示信息" ); 
	//m_stat.Activate(TRUE);
}

CMyFrameMsgTabCtrl::~CMyFrameMsgTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyFrameMsgTabCtrl, CTabCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_CMD, &CMyFrameMsgTabCtrl::OnBnClickedButtonCMD)
	ON_BN_CLICKED(IDC_BUTTON_DECODE, &CMyFrameMsgTabCtrl::OnBnClickedButtonDECODE)
	ON_BN_CLICKED(IDC_BUTTON_CLEARDECODE, &CMyFrameMsgTabCtrl::OnBnClickedButtonClearDECODE)
	ON_WM_RBUTTONDOWN(IDC_BUTTON_MYBUTTON, &CMyFrameMsgTabCtrl::OnBnClickedButtonDECODE)
END_MESSAGE_MAP()



// CMyFrameMsgTabCtrl 消息处理程序




int CMyFrameMsgTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	//CTabCtrl *pTabCtrl = GetTabControl();     
	// TODO:  在此添加您专用的创建代码
	//this->InsertItem
	//this-
	m_Font100K.CreatePointFont(90,_T(""));
	m_Font100H.CreatePointFont(95,_T(""));
	CRect rectDummy , rt;
	rectDummy.SetRectEmpty(); 

	m_ctrlMssage.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_OWNERDRAWFIXED,rectDummy,this,IDC_LISTXINXI);
	m_ctrlMssage.InsertColumn(0,_T("序号"),LVCFMT_LEFT,60);
	m_ctrlMssage.InsertColumn(1,_T("电表号"),LVCFMT_LEFT,180);
	m_ctrlMssage.InsertColumn(2,_T("TEI号"),LVCFMT_CENTER,80);
	m_ctrlMssage.InsertColumn(3,_T("协议类型"),LVCFMT_CENTER,130);
	m_ctrlMssage.InsertColumn(4,_T("正向有功总电能"),LVCFMT_CENTER,200);
	m_ctrlMssage.InsertColumn(5,_T("抄读结果"),LVCFMT_CENTER,100);
	m_ctrlMssage.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//m_ctrlMssage.m_nChooseList = 0;

	m_ctrlFrame.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_REPORT|LVS_OWNERDRAWFIXED,rectDummy,this,IDC_LISTXINXI);
	m_ctrlFrame.GetWindowRect(rt);
	m_ctrlFrame.InsertColumn(0,_T("时间"),LVCFMT_LEFT,160);
	m_ctrlFrame.InsertColumn(1,_T("收发"),LVCFMT_LEFT,50);
	m_ctrlFrame.InsertColumn(2,_T("报文"),LVCFMT_LEFT,1200);
	m_ctrlFrame.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_ctrlFrame.ShowWindow(SW_HIDE);
	m_ctrlFrame.m_nChooseList = 1;
	m_button=new CButton();
	m_checkboxbutton=new CButton();
	m_DecodeButton=new CButton();
	m_ClearDecodeButton=new CButton();
	//m_editMLH =new CEdit();//(CEdit*)GetDlgItem(IDC_EDIT_MSG);
	//m_editRec =new CEdit();
	//DWORD dwStyle = ::GetWindowLong(m_editMLH->GetSafeHwnd(), GWL_STYLE);
 //   dwStyle |= ES_NUMBER;
 //   ::SetWindowLong(m_editMLH->GetSafeHwnd(), GWL_STYLE, dwStyle);
	//m_editMLH->Create(WS_CHILD|ES_MULTILINE|ES_WANTRETURN, rectDummy, this,IDC_EDIT_MSG);
	//m_editMLH->LineScroll(m_editMLH->GetLineCount()); 
	//m_editRec->Create(WS_CHILD, rectDummy, this,IDC_EDIT_REC2);
	//m_editMLH->SetWindowTextW(_T("12\n12"));
	//m_editMLH->SetSel(-1,-1);
 //   m_editMLH->ReplaceSel(_T("12\n12r\n"));
	//m_editRec->SetWindowTextW(_T("12\n12"));
	//m_button->Create();
	m_checkboxbutton->Create(_T("16进制"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX , rectDummy, this, IDC_BUTTON_MYCHECKBOX );
	m_MYButton.Create(_T("测试"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rectDummy, this, IDC_BUTTON_MYBUTTON ); //创建按钮
	m_button->Create(_T("发送"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rectDummy, this, IDC_BUTTON_CMD ); //创建按钮
	m_cmdedit_send.Create(WS_CHILD|ES_MULTILINE|ES_WANTRETURN|WS_VISIBLE|WS_BORDER|ES_AUTOVSCROLL, rectDummy, this,IDC_EDIT_CMD);
	m_cmdedit_rec.Create(ES_MULTILINE|ES_AUTOVSCROLL|WS_BORDER|ES_WANTRETURN, rectDummy, this,IDC_EDIT_CMD_REC);
	m_button->SetFont(&m_Font100K);
	m_cmdedit_send.ShowWindow(SW_HIDE);
	m_cmdedit_rec.ShowWindow(SW_HIDE);
	m_cmdedit_send.SetFont(&m_Font100H);
	m_cmdedit_rec.SetFont(&m_Font100H);
	m_cmdedit_rec.ShowScrollBar(1);
	m_button->ShowWindow(SW_HIDE);
	m_MYButton.ShowWindow(SW_HIDE);
	//m_cmdedit_send.SetWindowTextW(_T(" 按'Shift'键可发送"));


	m_ClearDecodeButton->Create(_T("清空"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rectDummy, this, IDC_BUTTON_CLEARDECODE ); //创建按钮
	m_DecodeButton->Create(_T("解析"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rectDummy, this, IDC_BUTTON_DECODE ); //创建按钮
	m_cmdedit_Code.Create(WS_CHILD|ES_MULTILINE|ES_WANTRETURN|WS_VISIBLE|WS_BORDER|ES_AUTOVSCROLL, rectDummy, this,IDC_EDIT_CODE);
	m_cmdedit_Decode.Create(ES_MULTILINE|ES_AUTOVSCROLL|WS_BORDER|ES_WANTRETURN, rectDummy, this,IDC_EDIT_DECODE);
	m_cmdedit_Code.ShowWindow(SW_HIDE);
	m_cmdedit_Decode.ShowWindow(SW_HIDE);
	m_cmdedit_Code.ShowScrollBar(1);
	m_cmdedit_Code.SetFont(&m_Font100H);
	m_cmdedit_Decode.SetFont(&m_Font100H);
	m_cmdedit_Decode.ShowScrollBar(1);
	m_DecodeButton->ShowWindow(SW_HIDE);
	m_ClearDecodeButton->ShowWindow(SW_HIDE);
	m_DecodeButton->SetFont(&m_Font100K);
	m_ClearDecodeButton->SetFont(&m_Font100K);
	m_checkboxbutton->SetFont(&m_Font100K);
	m_checkboxbutton->ShowWindow(SW_HIDE);
	//m_MYButton.SubclassDlgItem(IDC_BUTTON_MYBUTTON,this);

	m_stat.Create(this);  
    //m_stat.AddTool(GetDlgItem(IDC_BUTTON_MYBUTTON), _T("你想要添加的提示信息/n 下一行"));//.AddTool( GetDlgItem(IDC_BUTTON_MYBUTTON), "你想要添加的提示信息" ); 
	m_stat.SetDelayTime(0); //设置延迟，如果为0则不等待，立即显示
    //m_stat.SetTipTextColor( RGB(0,0,255) ); //设置提示文本的颜色
    //m_stat.SetTipBkColor( RGB(255,255,255)); //设置提示框的背景颜色
    
	//m_stat.SetTipTextColor( RGB(0,25,34) ); //设置提示文本的颜色  设置颜色没作用
    //m_stat.SetTipBkColor( RGB(233,34,55)); //设置提示框的背景颜色
	m_stat.AddTool(GetDlgItem(IDC_BUTTON_MYBUTTON), _T("你想要添加的提示信息\n下一行\n下一行\n下一行\n下一行\n下一行"));
	m_stat.AddTool(GetDlgItem(IDC_BUTTON_CMD), _T("左侧发送框\n右侧接收框\n按shift键可发送"));
	m_stat.AddTool(GetDlgItem(IDC_EDIT_CMD), _T("发送窗口\n按shift键可发送"));
	m_stat.AddTool(GetDlgItem(IDC_EDIT_CMD_REC), _T("接收窗口"));
	m_stat.AddTool(GetDlgItem(IDC_EDIT_CODE), _T("输入解析帧的窗口"));
	m_stat.AddTool(GetDlgItem(IDC_EDIT_DECODE), _T("解析结果窗口"));
	m_stat.SetMaxTipWidth(600);
	//m_stat.Activate(TRUE);
	return 0;
}


void CMyFrameMsgTabCtrl::OnSize(UINT nType, int cx, int cy)
{
	CTabCtrl::OnSize(nType, cx, cy);
	CRect rectClient;
	GetClientRect(rectClient); 
	//m_editMLH->SetWindowPos(NULL, rectClient.left + 1, rectClient.top  + 25, rectClient.Width()/2, rectClient.Height()-25, SWP_NOACTIVATE | SWP_NOZORDER);
	//m_editRec->SetWindowPos(NULL, rectClient.left+rectClient.Width()/2+10, rectClient.top  + 25, rectClient.Width()/2-20, rectClient.Height()  - 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_button->SetWindowPos(NULL, rectClient.left+1, rectClient.top  + 30, 50, 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_cmdedit_send.SetWindowPos(NULL, rectClient.left + 85, rectClient.top  + 30, rectClient.Width()/2-70, rectClient.Height()-25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_cmdedit_rec.SetWindowPos(NULL, rectClient.left+rectClient.Width()/2+25, rectClient.top  + 30, rectClient.Width()/2-100, rectClient.Height()  - 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ctrlMssage.SetWindowPos(NULL, rectClient.left + 5, rectClient.top  + 30, rectClient.Width() - 2, rectClient.Height()  - 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ctrlFrame.SetWindowPos(NULL, rectClient.left + 5, rectClient.top  + 30, rectClient.Width() - 2, rectClient.Height()  - 25, SWP_NOACTIVATE | SWP_NOZORDER);


	m_checkboxbutton->SetWindowPos(NULL, rectClient.left+1, rectClient.top  +75, 75, 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_DecodeButton->SetWindowPos(NULL, rectClient.left+1, rectClient.top+30, 50, 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_cmdedit_Code.SetWindowPos(NULL, rectClient.left + 60, rectClient.top  + 30, rectClient.Width()/2-40, rectClient.Height()-25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_cmdedit_Decode.SetWindowPos(NULL, rectClient.left+rectClient.Width()/2+25, rectClient.top  + 30, rectClient.Width()/2-100, rectClient.Height()  - 25, SWP_NOACTIVATE | SWP_NOZORDER);
	m_ClearDecodeButton->SetWindowPos(NULL, rectClient.right-60, rectClient.top  + 30, 50, 25, SWP_NOACTIVATE | SWP_NOZORDER);
	// TODO: 在此处添加消息处理程序代码
	m_MYButton.SetWindowPos(NULL, rectClient.left+1, rectClient.top  + 105, 60, 25, SWP_NOACTIVATE | SWP_NOZORDER);
}
void CMyFrameMsgTabCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(GetCurSel())
	{
	case 0:
		m_ctrlMssage.ShowWindow(SW_SHOW);
		m_ctrlFrame.ShowWindow(SW_HIDE);
		m_checkboxbutton->ShowWindow(SW_HIDE);
		//m_editMLH->ShowWindow(SW_HIDE);
		//m_editRec->ShowWindow(SW_HIDE);
		m_button->ShowWindow(SW_HIDE);
		m_cmdedit_send.ShowWindow(SW_HIDE);
		m_cmdedit_rec.ShowWindow(SW_HIDE);

		m_DecodeButton->ShowWindow(SW_HIDE);
		m_cmdedit_Code.ShowWindow(SW_HIDE);
		m_cmdedit_Decode.ShowWindow(SW_HIDE);

		m_ClearDecodeButton->ShowWindow(SW_HIDE);


		m_MYButton.ShowWindow(SW_HIDE);

		break;
	case 1:
		m_checkboxbutton->ShowWindow(SW_HIDE);
		m_ctrlMssage.ShowWindow(SW_HIDE);
		m_ctrlFrame.ShowWindow(SW_SHOW);
		//m_editMLH->ShowWindow(SW_HIDE);
		//m_editRec->ShowWindow(SW_HIDE);
		m_button->ShowWindow(SW_HIDE);
		m_cmdedit_send.ShowWindow(SW_HIDE);
		m_cmdedit_rec.ShowWindow(SW_HIDE);

		m_ClearDecodeButton->ShowWindow(SW_HIDE);
		m_DecodeButton->ShowWindow(SW_HIDE);
		m_cmdedit_Code.ShowWindow(SW_HIDE);
		m_cmdedit_Decode.ShowWindow(SW_HIDE);

		m_MYButton.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_button->ShowWindow(SW_SHOW);
		m_checkboxbutton->ShowWindow(SW_SHOW);
		m_ctrlMssage.ShowWindow(SW_HIDE);
		m_ctrlFrame.ShowWindow(SW_HIDE);
		//m_editMLH->ShowWindow(SW_SHOW);
		//m_editRec->ShowWindow(SW_SHOW);
		m_cmdedit_send.ShowWindow(SW_SHOW);
		m_cmdedit_rec.ShowWindow(SW_SHOW);

		m_ClearDecodeButton->ShowWindow(SW_SHOW);
		m_DecodeButton->ShowWindow(SW_HIDE);
		m_cmdedit_Code.ShowWindow(SW_HIDE);
		m_cmdedit_Decode.ShowWindow(SW_HIDE);

		m_MYButton.ShowWindow(SW_HIDE);
		
		break;
	case 3:
				m_checkboxbutton->ShowWindow(SW_HIDE);
		m_button->ShowWindow(SW_HIDE);
		m_ctrlMssage.ShowWindow(SW_HIDE);
		m_ctrlFrame.ShowWindow(SW_HIDE);
		//m_editMLH->ShowWindow(SW_SHOW);
		//m_editRec->ShowWindow(SW_SHOW);
		m_cmdedit_send.ShowWindow(SW_HIDE);
		m_cmdedit_rec.ShowWindow(SW_HIDE);
		m_ClearDecodeButton->ShowWindow(SW_SHOW);
		m_DecodeButton->ShowWindow(SW_SHOW);
		m_cmdedit_Code.ShowWindow(SW_SHOW);
		
		m_cmdedit_Decode.ShowWindow(SW_SHOW);

		m_MYButton.ShowWindow(SW_HIDE);
		
      break;
	}
	CTabCtrl::OnLButtonUp(nFlags, point);
}



  DWORD WINAPI ThreadSendCMD (PVOID pParam) 
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMyFrameMsgTabCtrl * pView = (CMyFrameMsgTabCtrl *)pParam;
	INT8U ack = DACK_FAILURE;
	INT8U recvbuf[D376_MAXRCVBUFLEN];
	INT16U recvbuflen=0;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	CString mStr;
	INT8U pa[200]; 
	INT16U  temp16=0;
    pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_send.GetWindowText(mStr);
	if(pMain->m_FrameShowWnd.m_myTabCtrl.m_checkboxbutton->GetCheck()==1){
	     pView->Tools._str16tobuf16( mStr, pa , temp16 , false);
	     gSimJzq.SendBufToCom(pa,temp16);
    }
    else{
	   unsigned char s[1024];
	   int n=mStr.GetLength();
	   memcpy(s, (unsigned char *)mStr.GetBuffer(0), mStr.GetLength()*2); 
	   for(int j=0,i=0;j<n;i++,j++){
		pa[j]=s[i];
		i++;
	   }

	   gSimJzq.SendBufToCom(pa,n);
    }
	gSimJzq.GetCOMM376_2ToBuf(D376_MAXRCVBUFLEN , 5*1000 , 50 , recvbuf , recvbuflen);
	if(recvbuflen>0)
	{
		int nItem = 0;
	    CString m_recStr=pMain->m_tools._buf16tostr16(recvbuf , recvbuflen , true);
	   	CString strEditXianshi;
		pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.GetWindowText(strEditXianshi);
		pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.SetSel(strEditXianshi.GetLength(),strEditXianshi.GetLength());
		pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.ReplaceSel(m_recStr);


		ack = Cgw13762.Decode376_2Frame(recvbuf,recvbuflen,DstDecodeDataFrame);
		plog.saveLog_HexBuf(DATA_FILE,INPUT_DATA,recvbuf,recvbuflen);//打印接收帧数据
		nItem = pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemCount();
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.InsertItem( nItem,pMain-> m_strSysDateTime);
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 1, _T("接收<<"));
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 2 , pMain->m_tools._buf16tostr16(recvbuf , recvbuflen , true));
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.EnsureVisible(nItem,FALSE);
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.RedrawItems(nItem,nItem);
		if(ack == DACK_SUCESS)
		{
			plog.saveInformation_rev(DstDecodeDataFrame);
		}
		else
		{
		    plog.saveLog_err(DATA_FILE,NOTIME,_T(""),DACK_ERR_FORMAT);
		}
	}
	else{
		CString strEditXianshi;
		pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.GetWindowText(strEditXianshi);
		pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.SetSel(strEditXianshi.GetLength(),strEditXianshi.GetLength());
		pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_rec.ReplaceSel(_T("没有收到数据"));
	}

	//switch(ack)
	//{
	//case 0:
	//	pView->ShowZuzhenData();
	//	break;
	//case 0x13://失败
	//	pView->SetWindowText(_T("通讯失败！！！\r\n"));
	//	break;
	//case 0x30://SEQ不一致
	//	pView->ShowZuzhenData(ack);
	//	break;
	//case 0x0A://主节点不支持此命令
	//	pView->SetWindowText(_T("主节点不支持此命令！！！\r\n"));
	//	break;
	//default:
	//	pView->SetWindowText(_T("其他错误！！！\r\n"));
	//	break;
	//}
	pMain->m_FrameShowWnd.m_myTabCtrl.m_button->EnableWindow(TRUE);
	return 0;
}

BOOL CMyFrameMsgTabCtrl::PreTranslateMessage(MSG* pMsg) //文本响应enter键
{
  CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	INT8U ack = DACK_FAILURE;
	INT8U recvbuf[D376_MAXRCVBUFLEN];
	INT16U recvbuflen=0;
	sPartQGDW376_2CreatFrame sQGDW376_2HostFrame;
	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	int nItem = 0;
   //TODO: Add your specialized code here and/or call the base class
  if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SHIFT //shift消息
    && pMsg->hwnd == m_cmdedit_send.GetSafeHwnd())//来自m_TestEdit控件
  {
		CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();

		CString strMessageAddress;
		pMain->m_bCommunictStop = false;
		if (pMain->m_bConnected == TRUE)
		{

				m_button->EnableWindow(FALSE);
				m_hCMDThread=CreateThread (NULL,0,ThreadSendCMD,this,0,NULL);
				CloseHandle(m_hCMDThread);
		}
		else
		{
			AfxMessageBox(_T("请打开串口！"));
		}
  }
 

 if( pMsg->message == WM_MOUSEWHEEL )//滚轮事件
 {
		  short zDelta = (short)HIWORD(pMsg->wParam);  
		  short xPos   = (short)LOWORD(pMsg->lParam);   
		  short yPos   = (short)HIWORD(pMsg->lParam);  
		  CPoint pt;
		  GetCursorPos(&pt);
		  ScreenToClient(&pt);
		  if( m_cmdedit_rec.GetSafeHwnd())
		  {
		   CRect rectControl;
		   m_cmdedit_rec.GetWindowRect(&rectControl);
		   ScreenToClient(&rectControl);
		   if( rectControl.PtInRect(pt) )
		   {
			int lineIndex = m_cmdedit_rec.LineFromChar();
			if( zDelta < 0 )
			{
			 lineIndex += 1;
			}
			else
			{
			 lineIndex -= 1;
			}
			int charindex = m_cmdedit_rec.LineIndex(lineIndex);
			m_cmdedit_rec.SetSel(charindex,charindex);
		   }
		   return TRUE;
		  }
 }
   m_stat.RelayEvent(pMsg); 
   return CWnd::PreTranslateMessage(pMsg);

}

// HBRUSH CMyFrameMsgTabCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//        HBRUSH hbr = CMyFrameMsgTabCtrl::OnCtlColor(pDC,pWnd,nCtlColor);
//        //CString strText = _T("");
//		const char * strtext="";
//        if(strcmp((const char *)strtext,"123")==0 || strcmp(strtext,"服务器")==0)
//			//灰色
//			pDC->SetBkColor(RGB(0,0,255));
//        else
//           pDC->SetTextColor(RGB(0,0,255));   //蓝色
//         return hbr;
//}


 void CMyFrameMsgTabCtrl::OnBnClickedButtonCMD()//命令行
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();

	CString strMessageAddress;
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{

			m_button->EnableWindow(FALSE);
			m_hCMDThread=CreateThread (NULL,0,ThreadSendCMD,this,0,NULL);
            CloseHandle(m_hCMDThread);
	}
	else
	{
		AfxMessageBox(_T("请打开串口！"));
	}
}
 void CMyFrameMsgTabCtrl::OnBnClickedButtonDECODE(){//376.2协议解析
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();

	INT8U ack = DACK_FAILURE;
	INT8U recvbuf[D376_MAXRCVBUFLEN];
	INT16U recvbuflen=0;

	sPartQGDW376_2DeCodeFrame DstDecodeDataFrame;
	sPartQCSG376_2DeCodeFrame DstDecodeDataFrameNW;
	CString mStr;
    pMain->m_FrameShowWnd.m_myTabCtrl.m_cmdedit_Code.GetWindowText(mStr);
	Tools._str16tobuf16(mStr , recvbuf , recvbuflen);

	ack = Cgw13762.Decode376_2Frame(recvbuf,recvbuflen,DstDecodeDataFrame);
	if(ack==DACK_SUCESS){
		appendText(&m_cmdedit_Decode,_T("---------------------------------------------------------------------------------------------"));
		appendText(&m_cmdedit_Decode,_T("<----被国网376.2帧格式锁定！解析如下：---->"));
		appendText(&m_cmdedit_Decode,_T(""));
		appendText(&m_cmdedit_Decode,_T("控制域:【 ")+Tools._buf16tostr16(&DstDecodeDataFrame.s_head.u_con.s_conByte,1, true)+_T(" 】"));
		if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_DIR==0){
		    appendText(&m_cmdedit_Decode,_T("          传输方向位DIR:[ 0 ]  集中器发出的下行报文"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_DIR==1){
			appendText(&m_cmdedit_Decode,_T("          传输方向位DIR:[ 1 ]  由通信模块发出的上行报文"));
		}
		if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_DIR==0){
		    appendText(&m_cmdedit_Decode,_T("          启动标志位PRM:[ 0 ]  报文来自从动站"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_DIR==1){
			appendText(&m_cmdedit_Decode,_T("          启动标志位PRM:[ 1 ]  报文来自启动站"));
		}
	    if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_ComMode==3){
		    appendText(&m_cmdedit_Decode,_T("          通信方式:[ 3 ]  宽带载波通信"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_ComMode==2){
		    appendText(&m_cmdedit_Decode,_T("          通信方式:[ 2 ]  分布式路由载波通信"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_ComMode==1){
		    appendText(&m_cmdedit_Decode,_T("          通信方式:[ 1 ]  集中式路由载波通信"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_ComMode==10){
		    appendText(&m_cmdedit_Decode,_T("          通信方式:[ 10 ]  微功率无线通信"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_ComMode==1){
		    appendText(&m_cmdedit_Decode,_T("          通信方式:[ 20 ]  以太网通信"));
		}
		else{
		    appendText(&m_cmdedit_Decode,_T("          通信方式:[ ] 未知通信方式"));
		}

		appendText(&m_cmdedit_Decode,_T(""));
		appendText(&m_cmdedit_Decode,_T("信息域:【 ")+Tools._buf16tostr16(DstDecodeDataFrame.s_head.u_msg.s_msgbuf,5, true)+Tools._buf16tostr16(&DstDecodeDataFrame.s_head.s_Msg_Seq,1, true)+_T(" 】"));
		if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_DIR==0){
		    //appendText(&m_cmdedit_Decode,_T("          传输方向位DIR:[ 0 ]  集中器发出的下行报文"));
			if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_Msg_RouterFlag==0){
				appendText(&m_cmdedit_Decode,_T("          路由标识:[ 0 ]  通信模块带路由或工作在路由模式"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_Msg_RouterFlag==1){
				appendText(&m_cmdedit_Decode,_T("          路由标识:[ 1 ]  通信模块不带路由或工作在旁路模式"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_reserved_1==0){
				appendText(&m_cmdedit_Decode,_T("          附属节点标识:[ 0 ]  无附加节点"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_reserved_1==1){
				appendText(&m_cmdedit_Decode,_T("          附属节点标识:[ 1 ]  有附加节点"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_Msg_ComFlag==0){
				appendText(&m_cmdedit_Decode,_T("          通信模块标识:[ 0 ]  对主节点的操作"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_Msg_ComFlag==1){
				appendText(&m_cmdedit_Decode,_T("          通信模块标识:[ 1 ]  对从节点操作"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_reserved_2==0){
				appendText(&m_cmdedit_Decode,_T("          中继级别:[ 0 ]  无中继"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_reserved_2!=0){
						CString strNumb;
						int n = DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_reserved_2;
                        strNumb.Format(_T("%d") , n);
				appendText(&m_cmdedit_Decode,_T("          中继级别:[ ")+ strNumb+_T("] 有中继"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_chanle_num==0){
				appendText(&m_cmdedit_Decode,_T("          信道标识:[ 0 ]  不分信道"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_chanle_num!=0){
						CString strNumb;
						int n = DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_chanle_num;
                        strNumb.Format(_T("%d") , n);
				appendText(&m_cmdedit_Decode,_T("          信道标识:[ ")+ strNumb+_T("] 分信道"));
			}
			appendText(&m_cmdedit_Decode,_T("          帧序列号:[ ")+Tools._buf16tostr16(&DstDecodeDataFrame.s_head.s_Msg_Seq,1, true)+_T("]"));
		}
		else if(DstDecodeDataFrame.s_head.u_con.s_conBit.s_Con_DIR==1){
			//appendText(&m_cmdedit_Decode,_T("          传输方向位DIR:[ 1 ]  由通信模块发出的上行报文"));
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_RouterFlag==0){
				appendText(&m_cmdedit_Decode,_T("          路由标识:[ 0 ]  通信模块带路由或工作在路由模式"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_RouterFlag==1){
				appendText(&m_cmdedit_Decode,_T("          路由标识:[ 1 ]  通信模块不带路由或工作在旁路模式"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_reserved_1==0){
				appendText(&m_cmdedit_Decode,_T("          附属节点标识:[ 0 ]  无附加节点"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_reserved_1==1){
				appendText(&m_cmdedit_Decode,_T("          附属节点标识:[ 1 ]  有附加节点"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_ComFlag==0){
				appendText(&m_cmdedit_Decode,_T("          通信模块标识:[ 0 ]  对主节点的操作"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_ComFlag==1){
				appendText(&m_cmdedit_Decode,_T("          通信模块标识:[ 1 ]  对从节点操作"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_reserved_2==0){
				appendText(&m_cmdedit_Decode,_T("          中继级别:[ 0 ]  无中继"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_reserved_2!=0){
						CString strNumb;
						int n = DstDecodeDataFrame.s_head.u_msg.s_DownMsgBit.s_reserved_2;
                        strNumb.Format(_T("%d") , n);
				appendText(&m_cmdedit_Decode,_T("          中继级别:[ ")+ strNumb+_T("] 有中继"));
			}
			//s_Msg_phase:       
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_chanle_num==0){
				appendText(&m_cmdedit_Decode,_T("          信道标识:[ 0 ]  不分信道"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_chanle_num!=0){
						CString strNumb;
						int n = DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_chanle_num;
                        strNumb.Format(_T("%d") , n);
				appendText(&m_cmdedit_Decode,_T("          信道标识:[ ")+ strNumb+_T("] 分信道"));
			}
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_phase==0){
				appendText(&m_cmdedit_Decode,_T("          实测相线标识:[ 0 ]  不确定"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_phase!=0){
						CString strNumb;
						int n = DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_phase;
                        strNumb.Format(_T("%d") , n);
				appendText(&m_cmdedit_Decode,_T("          实测相线标识:[ ")+ strNumb+_T("] 有相线"));
			}

//s_Meter_flag:  
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Meter_flag==0){
				appendText(&m_cmdedit_Decode,_T("          电表通道特征:[ 0 ]  保留"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Meter_flag==1){
				appendText(&m_cmdedit_Decode,_T("          电表通道特征:[ 1 ]  物理信道为单相供电，逻辑信道为单信道"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Meter_flag==2){
				appendText(&m_cmdedit_Decode,_T("          电表通道特征:[ 2 ]  物理信道为单相供电，逻辑信道为两信道"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Meter_flag==3){
				appendText(&m_cmdedit_Decode,_T("          电表通道特征:[ 3 ]  物理信道为单相供电，逻辑信道为三信道"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Meter_flag==4){
				appendText(&m_cmdedit_Decode,_T("          电表通道特征:[ 4 ]  物理信道为三相供电，逻辑信道为三信道"));
			}
//s_CmdCsq
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_CmdCsq==0){
				appendText(&m_cmdedit_Decode,_T("          信号品质:[ 0 ]  无信号品质"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_CmdCsq!=0){
						CString strNumb;
						int n = DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_CmdCsq;
                        strNumb.Format(_T("%d") , n);
				appendText(&m_cmdedit_Decode,_T("          信号品质:[ ")+ strNumb+_T("] 1表示最低品质 1-15"));
			}
			//s_Msg_Event
			if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_Event==0){
				appendText(&m_cmdedit_Decode,_T("          事件标志:[ 0 ]  无上报事件"));
			}
			else if(DstDecodeDataFrame.s_head.u_msg.s_UpMsgBit.s_Msg_Event==1){
				appendText(&m_cmdedit_Decode,_T("          事件标志:[ 1 ]  有上报事件"));
			}
			appendText(&m_cmdedit_Decode,_T("          帧序列号:[ ")+Tools._buf16tostr16(&DstDecodeDataFrame.s_head.s_Msg_Seq,1, true)+_T("]"));

		}	

		//appendText(&m_cmdedit_Decode,_T(""));
		//appendText(&m_cmdedit_Decode,_T("信息域:【 ")+Tools._buf16tostr16(DstDecodeDataFrame.s_head.u_msg.s_msgbuf,5, true)+Tools._buf16tostr16(&DstDecodeDataFrame.s_head.s_Msg_Seq,1, true)+_T(" 】"));
		appendText(&m_cmdedit_Decode,_T(""));
		appendText(&m_cmdedit_Decode,_T("应用功能码AFN:【 ")+Tools._buf16tostr16(&DstDecodeDataFrame.s_head.s_AFN,1, true)+_T(" 】"));
		//appendText(&m_cmdedit_Decode,_T("数据单元标识FN:【 ")+Tools._buf16tostr16(DstDecodeDataFrame.s_head.s_FN,2, true)+_T(" 】"));
		//appendText(&m_cmdedit_Decode,_T("数据域数据:"));
	//		CMainFrame* pMainDlg= (CMainFrame*)AfxGetApp()->GetMainWnd();
		UINT8 a_Fn;//=(UINT8)sQGDW376_2HostFrame.s_head.s_FN;
		//INT8U pRbuf[6]={0,0,0,0,0,0};
		INT8U S;
		ST_Fn pstFn;
		S=(UINT8)(DstDecodeDataFrame.s_head.s_FN);
		(&pstFn)->DT1=S;
		(&pstFn)->DT2=DstDecodeDataFrame.s_head.s_FN>>8;
		a_Fn=pMain->getFn(pstFn);
		CString i_fn;
		int n = a_Fn;
        i_fn.Format(_T("%d") , n);
		appendText(&m_cmdedit_Decode,_T(""));
		INT8U fn1=DstDecodeDataFrame.s_head.s_FN;
		INT8U fn2=DstDecodeDataFrame.s_head.s_FN >> 8;
		CString sfn=Tools._buf16tostr16(&fn1 ,1, true)+Tools._buf16tostr16(&fn2 ,1, true);
		appendText(&m_cmdedit_Decode,_T("数据单元标识FN:【 ")+sfn+_T(" 】")+_T("F")+i_fn);

		appendText(&m_cmdedit_Decode,_T(""));
		appendText(&m_cmdedit_Decode,_T("应用数据:【 ")+Tools._buf16tostr16(DstDecodeDataFrame.s_RcvDataBuf , DstDecodeDataFrame.s_RcvDataLen, true)+_T(" 】"));
		//appendText(&m_cmdedit_Decode,_T("帧尾校验:【 ")+Tools._buf16tostr16(&DstDecodeDataFrame.s_RcvDataBuf[DstDecodeDataFrame.s_RcvDataLen-1],1, true)+_T(" 】"));
        appendText(&m_cmdedit_Decode,_T("---------------------------------------------------------------------------------------------"));
	}
	else{
		appendText(&m_cmdedit_Decode,_T("<----未被国网376.2帧格式锁定！---->"));
	}
	appendText(&m_cmdedit_Decode,_T(""));
	appendText(&m_cmdedit_Decode,_T("============================================================================================="));
	//appendText(&m_cmdedit_Decode,_T(""));
	//ack = Ccsg13762.Decode376_2Frame(recvbuf,recvbuflen,DstDecodeDataFrameNW);
	//if(ack==DACK_SUCESS){
	//	       
	//			appendText(&m_cmdedit_Decode,_T("---------------------------------------------------------------------------------------------"));
	//			appendText(&m_cmdedit_Decode,_T("<----被南网376.2帧格式锁定！请自行判断是否合理，解析如下：---->"));
	//			appendText(&m_cmdedit_Decode,_T(""));
	//			appendText(&m_cmdedit_Decode,_T("控制域:【 ")+Tools._buf16tostr16(&DstDecodeDataFrameNW.s_head.u_con.s_conByte,1, true)+_T(" 】"));
	//			if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_DIR==0){
	//				appendText(&m_cmdedit_Decode,_T("          传输方向位DIR:[ 0 ]  集中器发出的下行报文"));
	//			}
	//			else if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_DIR==1){
	//				appendText(&m_cmdedit_Decode,_T("          传输方向位DIR:[ 1 ]  由通信模块发出的上行报文"));
	//			}
	//			if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_DIR==0){
	//				appendText(&m_cmdedit_Decode,_T("          启动标志位PRM:[ 0 ]  报文来自从动站"));
	//			}
	//			else if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_DIR==1){
	//				appendText(&m_cmdedit_Decode,_T("          启动标志位PRM:[ 1 ]  报文来自启动站"));
	//			}

	//			if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_ADD==1){
	//				appendText(&m_cmdedit_Decode,_T("          地址域标识:[ 1 ]  带地址域"));
	//			}
	//			else if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_ADD==0){
	//				appendText(&m_cmdedit_Decode,_T("          地址域标识:[ 0 ]  不带地址域"));
	//			}
	//			CString strver;
	//			int n_ver = DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_VER;
	//			strver.Format(_T("%d") , n_ver);
	//			appendText(&m_cmdedit_Decode,_T("          版本号:[ ")+ strver+_T(" ]"));

	//			appendText(&m_cmdedit_Decode,_T(""));
	//			if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_ADD==1){
	//				appendText(&m_cmdedit_Decode,_T("地址域:【 ")+Tools._buf16tostr16(DstDecodeDataFrameNW.s_head.s_MainAddBuf,6, true)+Tools._buf16tostr16(DstDecodeDataFrameNW.s_head.s_DestAddBuf,6, true)+_T(" 】"));
	//				appendText(&m_cmdedit_Decode,_T("          主节点地址:[")+Tools._buf16tostr16(DstDecodeDataFrameNW.s_head.s_MainAddBuf,6, true)+_T(" ]"));
	//				appendText(&m_cmdedit_Decode,_T("          目的地址:[")+Tools._buf16tostr16(DstDecodeDataFrameNW.s_head.s_DestAddBuf,6, true)+_T(" ]"));
	//			}
	//			else if(DstDecodeDataFrameNW.s_head.u_con.s_conBit.s_Con_ADD==0){
	//				appendText(&m_cmdedit_Decode,_T("地址域:【】"));
	//				appendText(&m_cmdedit_Decode,_T("          无地址域"));
	//			}

	//			appendText(&m_cmdedit_Decode,_T(""));
	//			appendText(&m_cmdedit_Decode,_T("应用功能码AFN:【 ")+Tools._buf16tostr16(&DstDecodeDataFrameNW.s_head.s_AFN,1, true)+_T(" 】"));
	//			appendText(&m_cmdedit_Decode,_T(""));
	//			INT8U fn_1=DstDecodeDataFrameNW.s_head.s_FN;
	//	        INT8U fn_2=DstDecodeDataFrameNW.s_head.s_FN >> 8;
	//			INT8U fn_3=DstDecodeDataFrameNW.s_head.s_FN >> 16;
	//	        INT8U fn_4=DstDecodeDataFrameNW.s_head.s_FN >> 24;
	//	        CString sfn4=Tools._buf16tostr16(&fn_1 ,1, true)+Tools._buf16tostr16(&fn_2 ,1, true)+Tools._buf16tostr16(&fn_3 ,1, true)+Tools._buf16tostr16(&fn_4 ,1, true);
	//			CString sfn4d=Tools._buf16tostr16(&fn_4 ,1, true)+Tools._buf16tostr16(&fn_3 ,1, true)+Tools._buf16tostr16(&fn_2 ,1, true)+Tools._buf16tostr16(&fn_1 ,1, true);
	//	        appendText(&m_cmdedit_Decode,_T("数据单元标识FN:【 ")+sfn4+_T(" 】")+sfn4d);
	//			appendText(&m_cmdedit_Decode,_T(""));
	//			appendText(&m_cmdedit_Decode,_T("帧序列号:【 ")+Tools._buf16tostr16(&DstDecodeDataFrameNW.s_head.s_Msg_Seq,1, true)+_T("】"));
	//			appendText(&m_cmdedit_Decode,_T(""));
	//	        appendText(&m_cmdedit_Decode,_T("应用数据:【 ")+Tools._buf16tostr16(DstDecodeDataFrameNW.s_RcvDataBuf , DstDecodeDataFrameNW.s_RcvDataLen, true)+_T(" 】"));

	//			appendText(&m_cmdedit_Decode,_T("---------------------------------------------------------------------------------------------"));

	//	}
	//else{
	//	 appendText(&m_cmdedit_Decode,_T("<----未被南网376.2帧格式锁定！---->"));
	//	 appendText(&m_cmdedit_Decode,_T("---------------------------------------------------------------------------------------------"));
	//}
 }

 void CMyFrameMsgTabCtrl::appendText(CmdEdit *edit,CString mStr){//编辑框追加字符串
	 	CString strEditXianshi;
		edit->GetWindowText(strEditXianshi);
		edit->SetSel(strEditXianshi.GetLength(),strEditXianshi.GetLength());
		edit->ReplaceSel(mStr+_T("\r\n"));
 }

  void CMyFrameMsgTabCtrl::OnBnClickedButtonClearDECODE(){
	  switch(GetCurSel())
	{
	  case 2:
		  m_cmdedit_rec.SetWindowTextW(_T(""));
	  case 3:
	      m_cmdedit_Decode.SetWindowTextW(_T(""));
	 }
 }