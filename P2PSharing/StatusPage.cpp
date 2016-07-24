// StatusPage.cpp : 实现文件
//

#include "stdafx.h"
#include "P2PSharing.h"
#include "StatusPage.h"
#include "afxdialogex.h"
#include "LS.h"

// StatusPage 对话框

IMPLEMENT_DYNAMIC(StatusPage, CDialogEx)

StatusPage::StatusPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(StatusPage::IDD, pParent)
	, m_peerStatus(_T(""))
{
	
}

StatusPage::StatusPage(PeerServer* peerServer,CWnd* pParent /*=NULL*/)
	: CDialogEx(StatusPage::IDD, pParent)
{
	StatusPage::StatusPage(pParent);
	this->peerServer = peerServer;
}

StatusPage::~StatusPage()
{
}

void StatusPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATUS, m_peerStatus);
}


BEGIN_MESSAGE_MAP(StatusPage, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// StatusPage 消息处理程序


BOOL StatusPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ls = LS(this->peerServer->getPeer());
	this->m_peerStatus = ls.list().c_str();
	UpdateData(false);
	//启动Timer
	SetTimer(1,800,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void StatusPage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case 1:
		this->m_peerStatus = ls.list().c_str();
		UpdateData(false);
		break;
	case 2:
		break;
	}
	//CDialogEx::OnTimer(nIDEvent);
}
