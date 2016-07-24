
// P2PSharingDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CP2PSharingDlg �Ի���




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


// CP2PSharingDlg ��Ϣ�������

BOOL CP2PSharingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_font.CreatePointFont(200,_T("Times New Roman"));
	m_brush.CreateSolidBrush(RGB(255,255,255));
	InitInput();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CP2PSharingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CP2PSharingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CP2PSharingDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

//=========================== �Զ��庯������ START ===========================
/*��ʼ��ID����ҳ��*/
void CP2PSharingDlg::InitInput()
{
	m_inputPage = new InputPage;
	m_Tab.InsertItem(0, _T("Input ID"));
	m_inputPage->Create(IDD_INPUT, &m_Tab); 
	//�趨��Tab����ʾ�ķ�Χ   
	CRect rc;  
	m_Tab.GetClientRect(rc);  
	rc.top += 20;  
	m_inputPage->MoveWindow(&rc);
	m_inputPage->ShowWindow(SW_SHOW);  
}

/*��ʼ��PeerServer�������*/
void CP2PSharingDlg::InitPeerServer(int id)
{
	//CWinSock::Finalize();
	CWinSock::Initialize();//����socket�������
	int serverPort = Config::PORT_BASE + id;
	//ͬʱ��ʼ������static
	CString title = _T("Node ");
	stringstream ss;ss<<id;
	title += ss.str().c_str();
	m_Title = title;
	UpdateData(false);
	peerServer = PeerServer(serverPort,id);//��ʼ��PeerServer
	peerServer.start();//����PeerServer
	//���IDΪ0��������Stable�߳�
	if(id == 0)
	{
		/*Peer* peer0 = peerServer.getPeer();
		Stable* stable0 = new Stable(peer0,peer0->fingerTable.preId,peer0->fingerTable.preIP,peer0->fingerTable.port);
		stable0->start();*/
	}
}

/*Update TabControl����*/
void CP2PSharingDlg::UpdateTabControl()
{
	//�Ƴ���һ����ǩҳ
	m_inputPage->ShowWindow(SW_HIDE);
	m_Tab.DeleteItem(0);
	//��������������ǩҳ
	m_statusPage = new StatusPage(&peerServer);
	m_joinPage = new JoinPage(&peerServer);
	m_searchPage = new SearchPage(&peerServer);
	m_Tab.InsertItem(0, _T("                    Peer Status                    "));
	m_Tab.InsertItem(1, _T("              Join and Leave and Search          "));
	m_Tab.InsertItem(2, _T("               Download and Play             "));
	m_statusPage->Create(IDD_STATUS, &m_Tab); 
	m_joinPage->Create(IDD_JOIN, &m_Tab);
	m_searchPage->Create(IDD_SEARCH, &m_Tab);
	//�趨��Tab����ʾ�ķ�Χ   
	CRect rc;  
	m_Tab.GetClientRect(rc);  
	rc.top += 20;  
	m_statusPage->MoveWindow(&rc);
	m_joinPage->MoveWindow(&rc);
	m_searchPage->MoveWindow(&rc);
	//������ʾ
	m_statusPage->ShowWindow(SW_SHOW);  
	m_joinPage->ShowWindow(SW_HIDE);
	m_searchPage->ShowWindow(SW_HIDE);
}

/* JUST FOR TEST */
void CP2PSharingDlg::Test()
{
	AfxMessageBox(_T("Test"));
}
//=========================== �Զ��庯������ END ===========================

HBRUSH CP2PSharingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if(pWnd->GetDlgCtrlID() == IDC_TITLE)
	{
		pDC->SetBkColor(RGB(255,255,255));
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SelectObject(&m_font);
		return m_brush;
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
