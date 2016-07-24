// StatusPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "P2PSharing.h"
#include "StatusPage.h"
#include "afxdialogex.h"
#include "LS.h"

// StatusPage �Ի���

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


// StatusPage ��Ϣ�������


BOOL StatusPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ls = LS(this->peerServer->getPeer());
	this->m_peerStatus = ls.list().c_str();
	UpdateData(false);
	//����Timer
	SetTimer(1,800,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void StatusPage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
