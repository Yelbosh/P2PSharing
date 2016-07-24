
// P2PSharingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "P2PSharing.h"
#include "P2PSharingDlg.h"
#include "afxdialogex.h"

#include "Stable.h"
#include "StatusPage.h"
#include "JoinPage.h"
#include "SearchPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CP2PSharingDlg 对话框




CP2PSharingDlg::CP2PSharingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CP2PSharingDlg::IDD, pParent)
	, m_Title(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CP2PSharingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Text(pDX, IDC_TITLE, m_Title);
}

BEGIN_MESSAGE_MAP(CP2PSharingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CP2PSharingDlg::OnTcnSelchangeTab1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CP2PSharingDlg 消息处理程序

BOOL CP2PSharingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_font.CreatePointFont(200,_T("Times New Roman"));
	m_brush.CreateSolidBrush(RGB(255,255,255));
	InitInput();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CP2PSharingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CP2PSharingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CP2PSharingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CP2PSharingDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int tab = m_Tab.GetCurSel();
	switch (tab)
	{
	case 0:
		m_statusPage->ShowWindow(SW_SHOW); 
		m_joinPage->ShowWindow(SW_HIDE);
		m_searchPage->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_statusPage->ShowWindow(SW_HIDE); 
		m_joinPage->ShowWindow(SW_SHOW);
		m_searchPage->ShowWindow(SW_HIDE);
		break;
	case 2:
		m_statusPage->ShowWindow(SW_HIDE); 
		m_joinPage->ShowWindow(SW_HIDE);
		m_searchPage->ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}

//=========================== 自定义函数部分 START ===========================
/*初始化ID输入页面*/
void CP2PSharingDlg::InitInput()
{
	m_inputPage = new InputPage;
	m_Tab.InsertItem(0, _T("Input ID"));
	m_inputPage->Create(IDD_INPUT, &m_Tab); 
	//设定在Tab内显示的范围   
	CRect rc;  
	m_Tab.GetClientRect(rc);  
	rc.top += 20;  
	m_inputPage->MoveWindow(&rc);
	m_inputPage->ShowWindow(SW_SHOW);  
}

/*初始化PeerServer服务程序*/
void CP2PSharingDlg::InitPeerServer(int id)
{
	//CWinSock::Finalize();
	CWinSock::Initialize();//启动socket服务程序
	int serverPort = Config::PORT_BASE + id;
	//同时初始化标题static
	CString title = _T("Node ");
	stringstream ss;ss<<id;
	title += ss.str().c_str();
	m_Title = title;
	UpdateData(false);
	peerServer = PeerServer(serverPort,id);//初始化PeerServer
	peerServer.start();//启动PeerServer
	//如果ID为0，则启动Stable线程
	if(id == 0)
	{
		/*Peer* peer0 = peerServer.getPeer();
		Stable* stable0 = new Stable(peer0,peer0->fingerTable.preId,peer0->fingerTable.preIP,peer0->fingerTable.port);
		stable0->start();*/
	}
}

/*Update TabControl程序*/
void CP2PSharingDlg::UpdateTabControl()
{
	//移除第一个标签页
	m_inputPage->ShowWindow(SW_HIDE);
	m_Tab.DeleteItem(0);
	//插入其他三个标签页
	m_statusPage = new StatusPage(&peerServer);
	m_joinPage = new JoinPage(&peerServer);
	m_searchPage = new SearchPage(&peerServer);
	m_Tab.InsertItem(0, _T("                    Peer Status                    "));
	m_Tab.InsertItem(1, _T("              Join and Leave and Search          "));
	m_Tab.InsertItem(2, _T("               Download and Play             "));
	m_statusPage->Create(IDD_STATUS, &m_Tab); 
	m_joinPage->Create(IDD_JOIN, &m_Tab);
	m_searchPage->Create(IDD_SEARCH, &m_Tab);
	//设定在Tab内显示的范围   
	CRect rc;  
	m_Tab.GetClientRect(rc);  
	rc.top += 20;  
	m_statusPage->MoveWindow(&rc);
	m_joinPage->MoveWindow(&rc);
	m_searchPage->MoveWindow(&rc);
	//设置显示
	m_statusPage->ShowWindow(SW_SHOW);  
	m_joinPage->ShowWindow(SW_HIDE);
	m_searchPage->ShowWindow(SW_HIDE);
}

/* JUST FOR TEST */
void CP2PSharingDlg::Test()
{
	AfxMessageBox(_T("Test"));
}
//=========================== 自定义函数部分 END ===========================

HBRUSH CP2PSharingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if(pWnd->GetDlgCtrlID() == IDC_TITLE)
	{
		pDC->SetBkColor(RGB(255,255,255));
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SelectObject(&m_font);
		return m_brush;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
