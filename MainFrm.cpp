
// MainFrm.cpp : CMainFrame 类的实现
//
#pragma comment(lib, "ws2_32.lib")  
#include<WinSock2.h>  


#include "stdafx.h"
#include "KD_Project.h"
#include "DlgConnection.h"
#include "MainFrm.h"
#include "Tools.h"
#include "cSerBuf_LoopRcv.h"
#include "DlgSelect.h"
#include "AddMacTest.h"

//extern cSerBuf_LoopRcv  m_loopRcv64507;
extern cSerBuf_LoopRcv m_loopRcv13762;

#define BIT_SET(x, bitn)    (x |=   (1 << bitn))
#define BIT_CLR(x, bitn)    (x &=  ~(1 << bitn))
#define IS_BIT_SET(x, bitn) ((x & (1 << bitn)) != 0)
#define IS_BIT_CLR(x, bitn) ((x & (1 << bitn)) == 0)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

//BEGIN_MESSAGE_MAP
BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_MESSAGE(WM_COMMNOTIFY, OnComm)
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_CONNECT_OPEN, &CMainFrame::OnConnectOpen)
	ON_COMMAND(ID_CONNECT_CLOSE, &CMainFrame::OnConnectClose)
	ON_COMMAND(ID_NETWORT_OPEN, &CMainFrame::OnNetwortOpen)
	ON_UPDATE_COMMAND_UI(ID_CONNECT_OPEN, &CMainFrame::OnUpdateConnectOpen)
	ON_UPDATE_COMMAND_UI(ID_CONNECT_CLOSE, &CMainFrame::OnUpdateConnectClose)
	ON_WM_TIMER()
	ON_COMMAND(ID_3762_OPEN, &CMainFrame::On3762Open)
	ON_COMMAND(ID_FRAMESHOW, &CMainFrame::OnFrameshow)
	ON_COMMAND(ID_COPYFRAME, &CMainFrame::OnCopyframe)
	ON_WM_CLOSE()
	ON_COMMAND(ID_ADDMETMSG, &CMainFrame::OnAddmetmsg)
	ON_COMMAND(ID_READMET, &CMainFrame::OnReadmet)
	ON_COMMAND(ID_ADDNODEMSG, &CMainFrame::OnAddnodemsg)
	ON_COMMAND(ID_DELNODEMSG, &CMainFrame::OnDelnodemsg)
	ON_COMMAND(ID_COPYMAC, &CMainFrame::OnCopymac)
	ON_COMMAND(ID_REBOOT, &CMainFrame::OnReboot)
	ON_COMMAND(ID_DELMETMSG, &CMainFrame::OnDelmetmsg)
	ON_COMMAND(ID_GETNODE, &CMainFrame::OnGetnode)
END_MESSAGE_MAP()


//static UINT indicators[] =
//{
//	ID_SEPARATOR,           // 状态行指示器
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
//};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
	m_bNetWork = FALSE;
	m_bNetWorkOpen = FALSE;
	m_bConnected = FALSE;
	m_bsetopen=TRUE;
	m_bsetclos=FALSE;
	m_bFrame3762 = FALSE;
	m_bFrame698 = FALSE;
	m_bCommunictStop = FALSE;
	m_strMAddress = _T("");
	m_376seq = 0;
	m_nConnectType = 0;
	m_PeiZhi_db=".\\配置文件\\13762Data.accdb";
}

CMainFrame::~CMainFrame()
{
	m_FrameShowWnd.ShowWindow(SW_HIDE);
	
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_ONENOTE; // 其他可用样式...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // 设置为 FALSE 会将关闭按钮放置在选项卡区域的右侧
	mdiTabParams.m_bTabIcons = FALSE;    // 设置为 TRUE 将在 MDI 选项卡上启用文档图标
	mdiTabParams.m_bAutoColor = TRUE;    // 设置为 FALSE 将禁用 MDI 选项卡的自动着色
	mdiTabParams.m_bDocumentMenu = TRUE; // 在选项卡区域的右边缘启用文档菜单
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 允许用户定义的工具栏操作:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	LoadStatusBar();
	

	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 启用增强的窗口管理对话框
	EnableWindowsDialog(ID_WINDOW_MANAGER, ID_WINDOW_MANAGER, TRUE);

	// 启用工具栏和停靠窗口菜单替换
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// 加载用户定义的工具栏图像
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}
	if((m_hPostMsgEvent=CreateEvent(NULL, FALSE, TRUE, NULL))==NULL)
		return FALSE;

	memset(&m_osRead, 0, sizeof(OVERLAPPED));
	memset(&m_osWrite, 0, sizeof(OVERLAPPED));

	// 为重叠读创建事件对象，手工重置，初始化为无信号的
	if((m_osRead.hEvent=CreateEvent(NULL, FALSE, FALSE, NULL))==NULL)
		return FALSE;

	// 为重叠写创建事件对象，手工重置，初始化为无信号的
	if((m_osWrite.hEvent=CreateEvent(NULL, FALSE, FALSE, NULL))==NULL)
		return FALSE;
	// 启用菜单个性化(最近使用的命令)
	// TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	/*CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);*/

	// 将文档名和应用程序名称在窗口标题栏上的顺序进行交换。这
	// 将改进任务栏的可用性，因为显示的文档名带有缩略图。
	ModifyStyle(0, FWS_PREFIXTITLE);

	m_Font70.CreatePointFont(90,_T("黑体"));
	m_Font100.CreatePointFont(100,_T("黑体"));
	m_Font120.CreatePointFont(125,_T("黑体"));


	CString strObjectView("信息窗口");  
	if (!m_FrameShowWnd.Create(strObjectView, this, CRect(0, 0, 200, 200), TRUE, 1001, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))  
	{  
		TRACE0("未能创建“信息窗口”窗口\n");  
		return 0; // 未能创建  
	}
	m_FrameShowWnd.EnableDocking(CBRS_ALIGN_ANY); //使可停靠与浮动  
	DockPane(&m_FrameShowWnd);
	m_FrameShowWnd.ShowWindow(SW_HIDE);

	CString strObjectView2("树形拓扑");  
	if (!mm_FrameShowWndTree.Create(strObjectView2, this, CRect(0, 0, 600, 400), TRUE, 1002, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))  
	{  
		TRACE0("未能创建“树形拓扑”窗口\n");  
		return 0; // 未能创建  
	}
	mm_FrameShowWndTree.EnableDocking(CBRS_ALIGN_ANY); //使可停靠与浮动  
	DockPane(&mm_FrameShowWndTree);
	mm_FrameShowWndTree.ShowWindow(SW_SHOW);

	return 0;
}

void CMainFrame::OnFrameshow()
{
	m_FrameShowWnd.ShowWindow(SW_SHOW);
}
void CMainFrame::Creat_File()
{

//#if 0
//	//初始化隐藏调试信息
//	displayComData = false;
//	GetDlgItem(IDC_BUTTON10)->SetWindowText("显示调试信息");
//#endif

	///////////打开本轮测试的LOG文件
	CString str,strTemp;
	SYSTEMTIME st;
	GetLocalTime(&st);
	CFileException fileException;

	str = _T(".\\日志\\DataFile-");
	strTemp.Format(_T("%.4d年%.2d月%.2d日"),st.wYear,st.wMonth,st.wDay);
	//strTemp.Format(_T("%.4d年%.2d月%.2d日%.2d点%.2d分%.2d秒"),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	if(!cfileData.Open(str+ strTemp +_T(".txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite 
		| CFile::shareDenyNone, &fileException))
	{
		//TRACE( "Can't open file, error = %u\n",fileException.m_cause );
		AfxMessageBox(_T("Can't open file,自动测试数据LOG无法保存"));
		bAutoTestRunCmd = false;
	}else TRACE("open data file ok \r\n");

	//str = _T(".\\log_3762\\ParsFile-");		
	//if(!cfileParse.Open(str+ strTemp +_T(".txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite 
	//	| CFile::shareDenyNone, &fileException))
	//{
	//	//TRACE( "Can't open file, error = %u\n",fileException.m_cause );
	//	AfxMessageBox(_T("Can't open PARSE file，自动测试解析LOG无法保存"));
	//	bAutoTestRunCmd = false;
	//}else TRACE("open parse file ok \r\n");

	cfileData.Write(str,str.GetLength());
}
void CMainFrame::Close_File()
{
	cfileData.Close();
	cfileParse.Close();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CMDIFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 为所有用户工具栏启用自定义按钮
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}
BOOL CMainFrame::LoadStatusBar()
{
	UINT indicators[] =
	{
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR
	};
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return FALSE;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_POPOUT,0);
	m_wndStatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_POPOUT,30);
	m_wndStatusBar.SetPaneText(1,_T("串口:"));
	m_wndStatusBar.SetPaneInfo(2,ID_SEPARATOR,SBPS_POPOUT,150);
	m_wndStatusBar.SetPaneText(2,_T("关闭"));
	m_wndStatusBar.SetPaneInfo(3,ID_SEPARATOR,SBPS_STRETCH,0);
	SetTimer(IDS_STATUSBARSYSTIME,500,NULL);
	return TRUE;
}
UINT CommProcc(LPVOID pParam)
{
	OVERLAPPED os;
	DWORD dwMask, dwTrans;
	COMSTAT ComStat;
	DWORD dwErrorFlags;

	CMainFrame* pMain= (CMainFrame*)pParam;

	memset(&os, 0, sizeof(OVERLAPPED));
	os.hEvent=CreateEvent(NULL, FALSE, FALSE, NULL);

	if(os.hEvent==NULL)
	{
		AfxMessageBox(_T("无法创建事件对象!"));
		return (UINT)-1;
	}

	while(pMain->m_bConnected)
	{
		ClearCommError(pMain->hCom,&dwErrorFlags,&ComStat);

		if(ComStat.cbInQue)
		{
			// 无限等待WM_COMMNOTIFY消息被处理完
			WaitForSingleObject(pMain->m_hPostMsgEvent, INFINITE);
			ResetEvent(pMain->m_hPostMsgEvent);

			// 通知视图
			//PostMessage(HWND_BROADCAST, WM_COMMNOTIFY, EV_RXCHAR, 0);
			PostMessage(pMain->m_hTermWnd, WM_COMMNOTIFY, EV_RXCHAR, 0);

			continue;
		}

		dwMask=0;

		if(!WaitCommEvent(pMain->hCom, &dwMask, &os)) // 重叠操作
		{

			if(GetLastError()==ERROR_IO_PENDING)
				// 无限等待重叠操作结果
				GetOverlappedResult(pMain->hCom, &os, &dwTrans, TRUE);
			else
			{
				CloseHandle(os.hEvent);
				return (UINT)-1;
			}
		}
	}

	CloseHandle(os.hEvent);
	return 0;
}
void CMainFrame::OnConnectOpen()
{
	CDlgConnection dlgConnection;
	CTools tools;
	INT16U temp16 = 0;
	while(1)
	{
		int nBTN = dlgConnection.DoModal();
		if (nBTN == IDOK)
		{
			COMMTIMEOUTS TimeOuts;

			tools._str16tobuf16(dlgConnection.m_strMainMAC , m_HostNodeAddress ,temp16,true);

			m_hTermWnd=this->GetSafeHwnd();
			int xunhuan=0;
			if(m_bConnected)
				return;
			if(connectType==0){//区分串口还是网络连接
				hCom=CreateFile(_T("\\\\.\\")+dlgConnection.m_strCommPort,
					GENERIC_READ|GENERIC_WRITE,
					0,
					NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
					NULL);
				SetupComm(hCom,MAXBLOCK,MAXBLOCK);
				SetCommMask(hCom, EV_RXCHAR);
				PurgeComm( hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR );  //清干净输入、输出缓冲区 

				// 把间隔超时设为最大，把总超时设为0将导致ReadFile立即返回并完成操作
				TimeOuts.ReadIntervalTimeout=MAXDWORD; 
				TimeOuts.ReadTotalTimeoutMultiplier=0; 
				TimeOuts.ReadTotalTimeoutConstant=0; 

				//设置写超时以指定WriteComm成员函数中的GetOverlappedResult函数的等待时间
				TimeOuts.WriteTotalTimeoutMultiplier=50;
				TimeOuts.WriteTotalTimeoutConstant=2000;

				SetCommTimeouts(hCom, &TimeOuts);

				DCB dcb;
				GetCommState(hCom,&dcb);
				dcb.BaudRate=_ttol(dlgConnection.m_strCommBaud);  //传输速率
				dcb.Parity=_ttol(dlgConnection.m_strCommParity);  //奇偶性
				dcb.ByteSize=_ttol(dlgConnection.m_strCommDatabit);    //起始位
				dcb.StopBits=_ttol(dlgConnection.m_strCommStopbit); //停止位
				if(SetCommState(hCom,&dcb))
				{
					m_pThread=AfxBeginThread(CommProcc, this, THREAD_PRIORITY_NORMAL, 
						0, CREATE_SUSPENDED, NULL); // 创建并挂起线程

					if(m_pThread==NULL)
					{
						CloseHandle(hCom);
						return;
					}
					else	
					{
						SetStatusBat(GetCommMessage(dlgConnection.m_strCommPort,dlgConnection.m_strCommBaud,dlgConnection.m_strCommParity,dlgConnection.m_strCommDatabit,dlgConnection.m_strCommStopbit));
						m_bsetopen = false;
						m_bsetclos = true;
						m_bConnected=TRUE;
						m_nConnectType = CONNECTCKQ;
						m_pThread->ResumeThread(); // 恢复线程运行
					}
					return;
				}
				else
				{
					AfxMessageBox(dlgConnection.m_strCommPort + _T(" 被占用或未找到!请检查串口"));
				}
			}
			if(connectType==1){
				//dlgConnection.m_strNetAdd
				//dlgConnection.m_strNetPassword
				//			cout<<"客户端";  
				//------加载套接字库----------  
				WORD wVersionRequested;//保存WinSock库版本号。不是C++标准的类型，是微软SDK中的类型，WORD的意思为字，是2byte（16位）的无符号整数，表示范围0~65535.  
				WSADATA wsaData;//存放windows socket初始化信息  
				int err;  
				wVersionRequested = MAKEWORD(1,1);  
				err=WSAStartup(wVersionRequested,&wsaData);//加载套接字库，成功返回0  
				if(err!=0) { 
					AfxMessageBox(_T("错误"));
					return;
				}
				
				if(LOBYTE(wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)//判断wsaData.wVersion低字节和高字节是否都为1，若版本不对应，调用WSACleanup函数终止对Socket的使用  
				{  
					WSACleanup();  
					return;  
				}  
				m_bConnected=TRUE;
				//--------创建套接字---------------  
				SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);  
  
				//--------向服务器发出连接请求------  
				//设置要连接的服务器的信息  
				SOCKADDR_IN addrSrv;  
				addrSrv.sin_addr.S_un.S_addr=inet_addr("172.20.0.1");//案例服务器和客户端都在本地，固可以使用本地回路地址127.0.0.1  
				addrSrv.sin_family=AF_INET;  
				addrSrv.sin_port=htons(6000);  
				connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));  
				//----------接收数据----------------  
				char recvBuf[100];  
				recv(sockClient,recvBuf,100,0);  
				//printf("%s\n",recvBuf);
				CString s;//=recvBuf;
				//s.Format(_T(recvBuf));
				s.Format(_T("%s"),recvBuf);

				AfxMessageBox(s);
				//----------发送数据----------------  
/*				CString sendBuf;  
					cin>>sendBuf;  
					send(sockClient,sendBuf.c_str,strlen(sendBuf.c_str())+1,0);  
			    send(sockClient,"22",strlen("22")+1,0); */ 

				//---------关闭套接字--------------  
				closesocket(sockClient);  
				WSACleanup(); 
				return;
			}
		}
		else
		{
			break;
		}
	}
	
}
void CMainFrame::OnConnectClose()
{
	
	if(!m_bConnected)
		return;
	m_bsetclos=FALSE;
	m_bsetopen=TRUE;
	m_bConnected=FALSE;

	//结束CommProc线程中WaitSingleObject函数的等待
	SetEvent(m_hPostMsgEvent); 

	//结束CommProc线程中WaitCommEvent的等待
	SetCommMask(hCom, 0); 

	//等待辅助线程终止
	WaitForSingleObject(m_pThread->m_hThread, INFINITE);
	m_pThread=NULL;
	SetStatusBat(_T("关闭"));
	m_nConnectType = 0;
	CloseHandle(hCom);
}

LRESULT CMainFrame::OnComm(WPARAM wParam, LPARAM lParam)
{
	INT8U buf[1];
	CString str;
	int nLength;
	if(!m_bConnected || (wParam & EV_RXCHAR)!=EV_RXCHAR) // 是否是EV_RXCHAR事件?
	{
		SetEvent(m_hPostMsgEvent); // 允许发送下一个WM_COMMNOTIFY消息
		return 0L;
	}

	nLength=ReadComm(buf,1);
	if(nLength)
	{
		m_loopRcv13762.InPutRcvByte(buf[0]);
	}
	SetEvent(m_hPostMsgEvent);//允许发送下一个WM_COMMNOTIFY消息
	return 0L;
}
DWORD CMainFrame::ReadComm(INT8U *buf, DWORD dwLength)
{
	DWORD length=0;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	ClearCommError(hCom,&dwErrorFlags,&ComStat);
	length=min(dwLength, ComStat.cbInQue);
	ReadFile(hCom,buf,length,&length,&m_osRead);	
	return length;
}
void CMainFrame::OnUpdateConnectOpen(CCmdUI *pCmdUI)
{
	if (m_bsetopen)
	{
		pCmdUI-> Enable(TRUE); 
	}
	else
	{
		pCmdUI-> Enable(FALSE); 
	}
}
void CMainFrame::OnUpdateConnectClose(CCmdUI *pCmdUI)
{
	if (m_bsetclos)
	{
		pCmdUI-> Enable(TRUE); 
	}
	else
	{
		pCmdUI-> Enable(FALSE); 
	}
}
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime t = CTime::GetCurrentTime();//获取当前系统时间   
	m_strSysTime = t.Format("%H:%M:%S");
	m_strSysDateTime = t.Format("%Y年%m月%d日 %H:%M:%S");
	if (nIDEvent == IDS_STATUSBARSYSTIME)
	{
		CClientDC dc(this);  
		CSize cs = dc.GetTextExtent(m_strSysTime);//获取字符串长度   
		m_wndStatusBar.SetPaneInfo(4,ID_SEPARATOR,SBPS_POPOUT,cs.cx);//根据字符串长度设置窗格长度   
		m_wndStatusBar.SetPaneText(4,m_strSysTime,TRUE);
	}
	else
	{
		switch(nIDEvent)
		{
		case 0:
			break;
		}
	}
	
	CMDIFrameWndEx::OnTimer(nIDEvent);
}
void CMainFrame::SetStatusBat(CString strPort)
{
	m_wndStatusBar.SetPaneText(2,strPort,TRUE);
}
CString CMainFrame::GetCommMessage(CString strPort, CString strBaud , CString strParity , CString strDatabit, CString strStopbit)
{
	CString strData = strPort + _T("（") + strBaud + _T("，");
	switch(_ttoi(strParity))
	{
	case 0:
		strParity = "N";
		break;
	case 1:
		strParity = "E";
		break;
	case 2:
		strParity = "O";
		break;
	}
	switch(_ttoi(strStopbit))
	{
	case 0:
		strStopbit = "1";
		break;
	case 1:
		strStopbit = "1.5";
		break;
	case 2:
		strStopbit = "2";
		break;
	}
	strData += strParity + _T("，") + strDatabit + _T("，") + strStopbit + _T("）");
	return strData;
}
void CMainFrame::OnNetwortOpen()
{
	/*if(!m_bConnected)
	{
		AfxMessageBox(_T("请先打开串口连接抄控器!"));
		return;
	}*/
		
	m_nChooseView = OPENNET;
	CKD_ProjectApp* pApp=(CKD_ProjectApp*)AfxGetApp();
	if (m_bNetWork==FALSE)
	{
		pApp->m_pDocTemplate->OpenDocumentFile(NULL);
		m_pFrameNetWork=(CFrameSetNet *)GetActiveFrame();
		m_bNetWork=TRUE;
		return;
	}
	m_pFrameNetWork->MDIActivate();
}
void CMainFrame::On3762Open()
{
	if(!m_bConnected)
	{
		AfxMessageBox(_T("请先打开串口连接抄控器!"));
		return;
	}
	m_nChooseView = OPEN13762;
	///////////////////////////////////////////////////////////
	//DlgSelect dlgsetnw;
	//int nBTN = dlgsetnw.DoModal();
	//if(NW_OR_GW==0)
	//{
	//	m_PeiZhi=".\\配置文件\\13762树控件.ini";
	//	m_PeiZhi_db=".\\配置文件\\13762Data.accdb";
	//}
	//else if(NW_OR_GW==1)
	//{
	//	m_PeiZhi=".\\配置文件\\13762树控件NW.ini";
	//	m_PeiZhi_db=".\\配置文件\\13762DataNW.accdb";
	//}
	////////////////////////////////////////////////////////////
	CKD_ProjectApp* pApp=(CKD_ProjectApp*)AfxGetApp();
	pApp->m_pDocTemp3762->OpenDocumentFile(NULL);
	m_pFrame3762=(CFrame3762 *)GetActiveFrame();
	m_bFrame3762=TRUE;
	return;
	//if (m_bFrame3762==FALSE)
	//{
	//pApp->m_pDocTemp3762->OpenDocumentFile(NULL);
	//m_pFrame3762=(CFrame3762 *)GetActiveFrame();
	//m_bFrame3762=TRUE;
	//return;
	//}
	//m_pFrame3762->MDIActivate();
}

void CMainFrame::SendBufToCOMM(INT8U * sendbuf,INT16U sendLen , INT8U nType)
{
	DWORD  nsize = 0;
	m_loopRcv13762.ClrRcvBuf();
	switch(nType)
	{
	case 0:
		WriteFile(hCom,sendbuf,sendLen,&nsize,&m_osWrite);
		break;
	case 1:
		//WriteFile(m_hCom645,sendbuf,sendLen,&nsize,&m_osWrite2);
		break;
	}
	///////保存日志
	int nItem = m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemCount();
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.InsertItem(nItem , m_strSysDateTime);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 1, _T("发送>>"));
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.SetItemText(nItem , 2 , m_tools._buf16tostr16(sendbuf , sendLen , true));
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.EnsureVisible(nItem,FALSE);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.RedrawItems(nItem,nItem);
}
unsigned char CMainFrame::getFn(ST_Fn stFn)
{
	unsigned char fn = 0;
	char i = 0;
	
	for (;i<8;i++)
	{
		if (IS_BIT_SET(stFn.DT1,i))
		{
			fn = i+1;
			break;
		}
	}
	fn += (stFn.DT2 << 3); 

	return fn;
}

void CMainFrame::OnCopyframe()
{
	CString strCopy = m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.GetItemText (m_FrameShowWnd.m_myTabCtrl.m_ctrlFrame.m_itemYes , 2);
	if (strCopy == "")
	{
		return;
	}
	CStringA strA;
	strA = strCopy;
	if(OpenClipboard())   
	{   
		HGLOBAL   clipbuffer;   
		char   *   buffer;   
		EmptyClipboard();   
		clipbuffer   =   GlobalAlloc(GMEM_DDESHARE,   strA.GetLength()+1);   
		buffer   =   (char*)GlobalLock(clipbuffer);   
		strcpy(buffer, (LPSTR)(LPCSTR)strA);
		GlobalUnlock(clipbuffer);   
		SetClipboardData(CF_TEXT,clipbuffer);   
		CloseClipboard();   
	}
}


void CMainFrame::OnClose()
{
	
    CMainFrame* pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	if(6 == MessageBox(_T("该软件正在运行，是否退出？") , _T("系统提示") ,MB_YESNO))
	{
		//m_access.DelectDataFromTable(_T(".\\配置文件\\13762Data.accdb"),_T("TPShow"),_T(""));
		m_access.DelectDataFromTable(pMain->m_PeiZhi_db,_T("TPShow"),_T(""));
		CMDIFrameWndEx::OnClose();
	}
}

CString CMainFrame::GetRecvErrName(INT8U nChoose)
{
	CString str;
	switch(nChoose)
	{
	case 0:
		str = _T(">>>>失败:通信超时");
		break;
	case 1:
		str = _T(">>>>失败:无效数据单元");
		break;
	case 2:
		str = _T(">>>>失败:长度错");
		break;
	case 3:
		str = _T(">>>>失败:校验错误");
		break;
	case 4:
		str = _T(">>>>失败:信息类不存在");
		break;
	case 5:
		str = _T(">>>>失败:格式错误");
		break;
	case 6:
		str = _T(">>>>失败:表号重复");
		break;
	case 7:
		str = _T(">>>>失败:表号不存在");
		break;
	case 8:
		str = _T(">>>>失败:电表应用层无应答");
		break;
	case 9:
		str = _T(">>>>失败:主节点忙");
		break;
	case 10:
		str = _T(">>>>失败:主节点不支持此命令");
		break;
	case 11:
		str = _T(">>>>失败:从节点不应答");
		break;
	case 12:
		str = _T(">>>>失败:从节点不在网内");
		break;
	}
	return str;
}
//
CString CMainFrame::GetAckErrName(INT8U nChoose)
{
	CString str;
	switch(nChoose)
	{
	case 0x13://失败
		str = _T("失败");
		break;
	case 0x30://SEQ不一致
		str = _T("SEQ不一致");
		break;
	case 0x0A://主节点不支持此命令
		str = _T("主节点不支持此命令");
		break;
	case 0xA0://通讯超时
		str = _T("通讯超时");
		break;
	default:
		str = _T("其他错误");
		break;
	}
	return str;
}

void CMainFrame::OnAddmetmsg()
{
	// TODO: 在此添加命令处理程序代码

	INT_PTR nRes;             // 用于保存DoModal函数的返回值   
    CString str;
    AddMacTest tipDlg;           // 构造对话框类CTipDlg的实例   
    nRes = tipDlg.DoModal();  // 弹出对话框   
    if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
        return;   
  
    // 将各控件中的数据保存到相应的变量   
    UpdateData(TRUE);   
  
    //   
	int m=m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetItemCount();
	str.Format(_T("%d") , m + 1);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.InsertItem(m,str);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(m ,1,tipDlg.m_MAC);
	m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(m ,2,tipDlg.m_TEI);  
	m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(m ,3,tipDlg.m_TYPE); 
	//m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.EnsureVisible(m,FALSE);
	//m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.RedrawItems(m,m); 
    // 根据各变量的值更新相应的控件。和的编辑框会显示m_editSum的值   
    UpdateData(FALSE);  
}

void CMainFrame::InsertItemToOnlineList(CString strTableName)
{
	//ShowNetListView *pViewOnlineList=(ShowNetListView*)m_cSplitter.GetPane(0,1);//放在OnCreate函数里
	m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.DeleteAllItems();
	CString strNumb;
	CString m_strlist[1000];
	CString str;
	CString str_nodeNum = _T("");
	CString strAllDatalist[500][6];
	CString f_strDatalist[6][500];
	int nNumb = 0 , nAlldataNumb;
	int n = 0 , m = 0 , i = 0;
	m_access.SelectDataFromTable(m_PeiZhi_db/*_T(".\\配置文件\\HistTPShow.accdb")*/, strTableName , _T("TP_MAC,TP_TEI,TP_PTEI,TP_ROLE") ,_T("") ,m_strlist ,nAlldataNumb);
	if(nAlldataNumb>0){
		for(n = 0 ; n < nAlldataNumb ; n++)
		{
			m_tools.Split(m_strlist[n] , _T("$") ,strAllDatalist[n] , nNumb);
	        str.Format(_T("%d") , n + 1);
	        m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.InsertItem(n,str);
	        m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,1,strAllDatalist[n][0]);
	        m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,2,strAllDatalist[n][1]); 
			m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,3,strAllDatalist[n][2]);
			if(strAllDatalist[n][3]==_T("2")){
				m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,4,_T("CCO"));
			}
			else if(strAllDatalist[n][3]==_T("4")){
				m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,4,_T("STA"));
			}
			else if(strAllDatalist[n][3]==_T("6")){
				m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,4,_T("PCO"));
			}
			else{
				m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(n ,4,_T("未知角色"));
			}
		}
	}


	//pViewOnlineList->GetListCtrl().InsertItem(n , strNumb);
	//pViewOnlineList->GetListCtrl().SetItemText(n , 1 , strAddress);
	////pViewOnlineList->GetListCtrl().SetItemText(n , 1 , strMAC.Mid(0 , 2) + _T(":") + strMAC.Mid(2 , 2) + _T(":") + strMAC.Mid(4 , 2) + _T(":") + strMAC.Mid(6 , 2) + _T(":") + strMAC.Mid(8 , 2) + _T(":") + strMAC.Mid(10 , 2));
	//pViewOnlineList->GetListCtrl().SetItemText(n , 2 , strTEI);
	//pViewOnlineList->GetListCtrl().EnsureVisible(n,FALSE);
	//pViewOnlineList->GetListCtrl().RedrawItems(n,n);
}



DWORD WINAPI ThreadSendbufRead (PVOID pParam)
{
	//AfxMessageBox(_T("升级"));
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	sPartQGDW376_2CreatFrame ptSendQGDW376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDWF0376_2;
	sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2;
	INT8U vSrcBuf[200];
	INT16U vSrcLen=0;
	CString NodeMAC,NodeTEI,NodeTYPE;
	INT8U Sendbufdata[2000] ,AddrBuf[7],TEIBuf[2];
	INT16U Sendbuflen = 0,temp16 = 0,teilen;
	INT8U ack = -1;
	if(pMain->i_Threadsend==7)
	{
       int num=pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetItemCount();

	    ack = pMain->MainFSimJzq.HostSendRcv376_2NoBuf(AFN01,F2,ptSendQGDW376_2,ptRecvQGDW376_2);
		if(ack==DACK_SUCESS){
			if(num==0){
			    pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.InsertItem(0,_T(""));//.SetItemText(1,5,_T("参数初始化成功"));
		        pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(0,5,_T("参数初始化成功"));
			}
			else{
				pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(0,5,_T("参数初始化成功"));
			}

		}
		else{
			if(num==0){
			    pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.InsertItem(0,_T(""));//.SetItemText(1,5,_T("参数初始化成功"));
		        pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(0,5,_T("参数初始化失败"));
			}
			else{
				pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(0,5,_T("参数初始化失败"));
			}
		}
	}
	else if(pMain->i_Threadsend==8){
		INT16U nSelect = pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetItemCount();
		for (int k = 0; k < nSelect; k++)
        {
			pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(k,7,_T(""));
		}


		INT16U u16BeginNumb_Node = 1;
		INT8U u8ReadCount_Node = 0 , n = 0 , temp8 = 0;
		INT16U temp16_Node = 0 , u16Numb = 0;
		ack = pMain->MainFSimJzq.HostSendRcv376_2NoBuf(AFN10,F1,ptSendQGDW376_2,ptRecvQGDW376_2);
		if (ack != 0) return 0;
		temp16_Node = ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | ptRecvQGDW376_2.s_RcvDataBuf[0];

		for (int k = nSelect; k < temp16_Node; k++)
		{
			pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.InsertItem(k,_T(""));
		}
		int NUM=0;
		while(temp16_Node)
		{
			u16BeginNumb_Node += u8ReadCount_Node;
			if (temp16_Node >10)
			{
				u8ReadCount_Node = 10;
			}
			else
			{
				u8ReadCount_Node = temp16_Node;
			}
			temp16_Node -= u8ReadCount_Node;
			vSrcLen = 3;
			vSrcBuf[0] = (INT8U)u16BeginNumb_Node;
			vSrcBuf[1] = (INT8U)(u16BeginNumb_Node>>8);
			vSrcBuf[2] = u8ReadCount_Node;
			ack =pMain->MainFSimJzq.HostSendRcv376_2Buf(AFN10,F2,vSrcBuf,vSrcLen,ptSendQGDW376_2,ptRecvQGDW376_2);
			if (ack != 0) return 0;

			temp8 = ptRecvQGDW376_2.s_RcvDataBuf[2];
			for (int n = 0; n < temp8; n++,NUM++)
			{
				NodeMAC = pMain->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[3 + 8 * n] , 6 , false , true);
				//NodeMAC=pMain->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[3] , 6);
	            pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(NUM,7,NodeMAC);
			}
		}

	}
	else{
		int nSelect = pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetSelectedCount();
		if (nSelect == 0) 
		{ 
			AfxMessageBox(_T("未选中节点"));
			return 0;

		} 

		POSITION pos = pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetFirstSelectedItemPosition(); 
		while (nSelect) 
		{ 

			int nItem = pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetNextSelectedItem(pos); 

				NodeMAC=pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetItemText(nItem,1);
				NodeTEI=pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetItemText(nItem,2);
				NodeTYPE=pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetItemText(nItem,3);

				pMain->m_tools._str16tobuf16(NodeMAC , AddrBuf , temp16 , true);//小端模式
				pMain->m_tools._str16tobuf16(NodeTEI , TEIBuf , teilen , true);
				if(pMain->i_Threadsend==1){//抄表
	//-----------------------测试抄表-------------------------------------
					AddrBuf[6]=2;
					ack=pMain->MainFSimJzq.ReadMeterAndCmpMter(1,AddrBuf,0x00010000,ptSendQGDW376_2,ptRecvQGDWF0376_2);
					if(ack == DACK_SUCESS)
					{
						pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(nItem,5,_T("成功"));
			            pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.EnsureVisible(nItem,FALSE);
		                pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.RedrawItems(nItem,nItem);
					}
					else{
							pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(nItem,5,_T("失败"));
									pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.EnsureVisible(nItem,FALSE);
		pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.RedrawItems(nItem,nItem);
					}
				}
				else if(pMain->i_Threadsend==4){//添加从节点

					vSrcBuf[0]=0x01;
					pMain->m_tools._str16tobuf16(NodeMAC , &vSrcBuf[1] , temp16 , true);//小端模式
					vSrcBuf[7]=0x02;
					vSrcLen=8;
					ack =pMain->MainFSimJzq.HostSendRcv376_2Buf(AFN11,F1,vSrcBuf,vSrcLen,ptSendQGDW376_2,ptRecvQGDWF0376_2);
					if(ptSendQGDW376_2.s_head.s_Msg_Seq == ptRecvQGDWF0376_2.s_head.s_Msg_Seq)
					{
						if((ptRecvQGDWF0376_2.s_head.s_AFN == 0x00) &&(ptRecvQGDWF0376_2.s_head.s_FN == F1))
						{
							ack = DACK_SUCESS;
							pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(nItem,5,_T("成功"));
						}
						else if((ptRecvQGDWF0376_2.s_head.s_AFN == 0x00) &&(ptRecvQGDWF0376_2.s_head.s_FN == F2))
						{
							ack =ptRecvQGDWF0376_2.s_RcvDataBuf[0];
							pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(nItem,5,_T("失败"));
						}

						else
						{
							pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(nItem,5,_T("失败"));
							ack = DACK_FAILURE;
						}
					}
					else
					{
						pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(nItem,5,_T("失败"));
						ack = DACK_EER_SEQERR;
					}     
				}
				else if(pMain->i_Threadsend==5){//删除从节点
					vSrcBuf[0]=0x01;
					pMain->m_tools._str16tobuf16(NodeMAC , &vSrcBuf[1] , temp16 , true);//小端模式
					vSrcLen=7;
					ack =pMain->MainFSimJzq.HostSendRcv376_2Buf(AFN11,F2,vSrcBuf,vSrcLen,ptSendQGDW376_2,ptRecvQGDWF0376_2);
					if(ptSendQGDW376_2.s_head.s_Msg_Seq == ptRecvQGDWF0376_2.s_head.s_Msg_Seq)
					{
						if((ptRecvQGDWF0376_2.s_head.s_AFN == 0x00) &&(ptRecvQGDWF0376_2.s_head.s_FN == F1))
						{
							ack = DACK_SUCESS;
							pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(nItem,5,_T("成功"));
						}
						else if((ptRecvQGDWF0376_2.s_head.s_AFN == 0x00) &&(ptRecvQGDWF0376_2.s_head.s_FN == F2))
						{
							ack =ptRecvQGDWF0376_2.s_RcvDataBuf[0];
							pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(nItem,5,_T("失败"));
						}

						else
						{
							pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(nItem,5,_T("失败"));
							ack = DACK_FAILURE;
						}
					}
					else
					{
						pMain->m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.SetItemText(nItem,5,_T("失败"));
						ack = DACK_EER_SEQERR;
					}     
				}
			nSelect--;
		} 
	}


	
	return 0;
}
void CMainFrame::OnReadmet()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strMessageAddress;
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{
		i_Threadsend=1;
		m_hThreadsend=CreateThread (NULL,0,ThreadSendbufRead,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("请打开串口！"));
	}
}


void CMainFrame::OnAddnodemsg()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strMessageAddress;
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{
		i_Threadsend=4;
		m_hThreadsend=CreateThread (NULL,0,ThreadSendbufRead,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("请打开串口！"));
	}
}


void CMainFrame::OnDelnodemsg()
{
	// TODO: 在此添加命令处理程序代码
		CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strMessageAddress;
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{
		i_Threadsend=5;
		m_hThreadsend=CreateThread (NULL,0,ThreadSendbufRead,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("请打开串口！"));
	}
}


void CMainFrame::OnCopymac()
{
	// TODO: 在此添加命令处理程序代码
	int nSelect = m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetSelectedCount();
	if (nSelect == 0) 
	{ 

		AfxMessageBox(_T("未选中节点"));
		return ;

	} 
	CString strCopy=_T("");
	POSITION pos = m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetFirstSelectedItemPosition(); 
    while (nSelect) 
    { 
		int nItem = m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetNextSelectedItem(pos); 
		strCopy+= m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetItemText (nItem , 1)+_T("\r\n");
		nSelect--;
	}

	if (strCopy == "")
	{
		return;
	}
	CStringA strA;
	strA = strCopy;
	if(OpenClipboard())   
	{   
		HGLOBAL   clipbuffer;   
		char   *   buffer;   
		EmptyClipboard();   
		clipbuffer   =   GlobalAlloc(GMEM_DDESHARE,   strA.GetLength()+1);   
		buffer   =   (char*)GlobalLock(clipbuffer);   
		strcpy(buffer, (LPSTR)(LPCSTR)strA);
		GlobalUnlock(clipbuffer);   
		SetClipboardData(CF_TEXT,clipbuffer);   
		CloseClipboard();   
	}
}


void CMainFrame::OnReboot()
{
	// TODO: 在此添加命令处理程序代码
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strMessageAddress;
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{
		i_Threadsend=7;
		m_hThreadsend=CreateThread (NULL,0,ThreadSendbufRead,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("请打开串口！"));
	}
}


void CMainFrame::OnDelmetmsg()
{
	// TODO: 在此添加命令处理程序代码
	int nSelect = m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetSelectedCount();
	if (nSelect == 0) 
	{ 

		AfxMessageBox(_T("未选中节点"));
		return ;

	} 
	POSITION pos = m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetFirstSelectedItemPosition(); 
    while (pos) 
    { 
		int nItem = m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetNextSelectedItem(pos); 
		m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.DeleteItem(nItem);
		pos = m_FrameShowWnd.m_myTabCtrl.m_ctrlMssage.GetFirstSelectedItemPosition();
	}
}


void CMainFrame::OnGetnode()
{
	CMainFrame * pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString strMessageAddress;
	pMain->m_bCommunictStop = false;
	if (pMain->m_bConnected == TRUE)
	{
		i_Threadsend=8;
		m_hThreadsend=CreateThread (NULL,0,ThreadSendbufRead,this,0,NULL);
		CloseHandle(m_hThreadsend);
	}
	else
	{
		AfxMessageBox(_T("请打开串口！"));
	}
	//INT16U u16BeginNumb = 0;
	//INT8U SendDatabuf[10];
	//INT8U ack = 0 , u8SendAFN = 0 ,AddrBuf[7] , u8ReadCount = 0;
	//INT16U SendDatalen = 0 ,temp16 = 0;
	////CString strAllTPdata = _T("");
	//sPartQGDW376_2CreatFrame ptSendQGDW376_2,sQGDW376_2HostFrame;
	//sPartQGDW376_2DeCodeFrame ptRecvQGDW376_2,sRecv376_2HostFrame;
	// //TODO: 在此添加命令处理程序代码
	//				INT16U u16BeginNumb_Node = 1;
	//				INT8U u8ReadCount_Node = 0 , n = 0 , temp8 = 0;
	//				INT16U temp16_Node = 0 , u16Numb = 0;
	//				CString strMAC = _T("") , strWhere = _T("");
	//				CString strNumb , strSTAMsg[1024] , strlist[10];
	//				int nlistNumb = 0 , nlistUN = 0 , nInNetNumb = 0 , nUnNetNumb = 0 , nLostNumb = 0 , nUnWhiteNumb = 0;
	//				
	//                m_tools._str16tobuf16( m_strMAddress , AddrBuf , temp16_Node , true);
	//				ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F1 , SendDatabuf , SendDatalen , ptSendQGDW376_2 , ptRecvQGDW376_2 , ptRecvQGDW376_2);
	//				if (ack != 0) return 0;
	//				temp16_Node = ptRecvQGDW376_2.s_RcvDataBuf[1] << 8 | ptRecvQGDW376_2.s_RcvDataBuf[0];
	//				while(temp16_Node)
	//				{
	//					u16BeginNumb_Node += u8ReadCount_Node;
	//					if (temp16_Node >10)
	//					{
	//						u8ReadCount_Node = 10;
	//					}
	//					else
	//					{
	//						u8ReadCount_Node = temp16_Node;
	//					}
	//					temp16_Node -= u8ReadCount_Node;
	//					SendDatalen = 3;
	//					SendDatabuf[0] = (INT8U)u16BeginNumb_Node;
	//					SendDatabuf[1] = (INT8U)(u16BeginNumb_Node>>8);
	//					SendDatabuf[2] = u8ReadCount_Node;
	//					ack = gSimJzq.HostSendRcv376_2F0F8(AddrBuf , 0x10 , F2 , SendDatabuf , SendDatalen , ptSendQGDW376_2, ptRecvQGDW376_2 , ptRecvQGDW376_2);
	//					if (ack != 0) return 0;

	//					temp8 = ptRecvQGDW376_2.s_RcvDataBuf[2];
	//					for (n = 0; n < temp8; n++)
	//					{
	//						strMAC = pView->m_tools._buf16tostr16(&ptRecvQGDW376_2.s_RcvDataBuf[3 + 8 * n] , 6 , false , true);
	//						strWhere = _T("TP_MAC='") + strMAC + _T("'");
	//						pView->m_access.SelectDataFromTable(pMain->m_PeiZhi_db, _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
	//						//pView->m_access.SelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , _T("TP_TEI,TP_ROLE") , strWhere , strSTAMsg , nlistNumb);
	//						if (nlistNumb == 0)
	//						{
	//							nUnNetNumb += 1;
	//							//pView->InsertItemToList(strMAC , _T("无") , _T("未入网") , _T("") , _T("未知") , _T(""));

	//							pView->m_DlgTongJiNode.InsertItemToLostList(strMAC);
	//						}
	//						else
	//						{
	//							nInNetNumb += 1;
	//							pView->m_tools.Split(strSTAMsg[0] , _T("$") , strlist , nlistNumb);
	//							//pView->InsertItemToList(strMAC , strlist[0] , _T("入网") , _T("") , strMAC , strlist[1]);
	//							pView->m_DlgTongJiNode.InsertItemToOnlineList(strMAC,strlist[0],strMAC, strlist[1]);
	//							pView->m_access.DelectDataFromTable(pMain->m_PeiZhi_db , _T("TPMODERR") , strWhere);
	//							//pView->m_access.DelectDataFromTable(_T(".\\配置文件\\13762Data.accdb") , _T("TPMODERR") , strWhere);
	//						}
	//					}
	//				}
	//				pView->m_nOnlineNumb[5]=nUnNetNumb;
}
