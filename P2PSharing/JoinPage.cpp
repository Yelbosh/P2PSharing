// JoinPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "P2PSharing.h"
#include "JoinPage.h"
#include "afxdialogex.h"
#include "Tool.h"
#include "CommandHandle.h"
#include <sstream>


// JoinPage �Ի���

IMPLEMENT_DYNAMIC(JoinPage, CDialogEx)

JoinPage::JoinPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(JoinPage::IDD, pParent)
	, m_Ip(0)
	, m_Port(_T(""))
	, m_searchID(_T(""))
{

}

JoinPage::JoinPage(PeerServer* peerServer, CWnd* pParent /*=NULL*/)
	: CDialogEx(JoinPage::IDD, pParent)
{
	JoinPage::JoinPage(pParent);
	this->peerServer = peerServer;
}

JoinPage::~JoinPage()
{
}

void JoinPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, m_leaveBtn);
	DDX_Control(pDX, IDC_BUTTON4, m_joinBtn);
	DDX_IPAddress(pDX, IDC_IPADDRESS2, m_Ip);
	DDX_Text(pDX, IDC_EDIT2, m_Port);
	DDX_Control(pDX, IDC_EDIT3, m_logEdit);
	DDX_Text(pDX, IDC_EDIT1, m_searchID);
}


BEGIN_MESSAGE_MAP(JoinPage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &JoinPage::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &JoinPage::OnBnClickedButton4)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &JoinPage::OnBnClickedButton1)
END_MESSAGE_MAP()


// JoinPage ��Ϣ�������


//�뿪����ʱ����Ӧ����
void JoinPage::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	string cmdstr = "le";
	CommandHandle* commandHandle = new CommandHandle(cmdstr,peerServer->getPeer());
	try{
		commandHandle->start();
	}
	catch(...)
	{
		AfxMessageBox(_T("Exception occured during Le ! Please check your network connection !"));
		return;
	}
	//�뿪�ɹ�,����leave��ť����ʾjoin��ť
	m_joinBtn.ShowWindow(SW_SHOW);
	m_leaveBtn.ShowWindow(SW_HIDE);
}

//��������ʱ����Ӧ����
void JoinPage::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if(!m_Ip)
	{
		AfxMessageBox(_T("IP can't be empty��"));
		return;
	}
	else if(this->m_Port.IsEmpty() || this->m_Port.GetLength() == 0)
	{
		AfxMessageBox(_T("ID can't be empty��"));
		return;
	}
	else if(!Tool::CheckNum(m_Port))
	{
		AfxMessageBox(_T("ID must be number��"));
		return;
	}
	else
	{
		CString IPstr;
		IPstr.Format(_T("%d.%d.%d.%d"),(m_Ip>>24)&0xff,(m_Ip>>16)&0xff,(m_Ip>>8)&0xff,m_Ip&0xff ); 
		string strIP = CT2A(IPstr.GetBuffer(0));
		int port = _ttoi(m_Port);port = 8000 + port;stringstream ss;ss<<port;
		string strPort = ss.str();
		string cmdstr = "join " + strIP + " " + strPort; 
		
		CommandHandle* commandHandle = new CommandHandle(cmdstr,peerServer->getPeer());
		try{
			commandHandle->start();
		}
		catch(...)
		{
			AfxMessageBox(_T("Exception occured during Join ! Please check your network connection !"));
			return;
		}
	}
	//���ӳɹ�,����join��ť����ʾleave��ť
	m_joinBtn.ShowWindow(SW_HIDE);
	m_leaveBtn.ShowWindow(SW_SHOW);
}


BOOL JoinPage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//�󶨱���IP
	string IPstr = this->peerServer->getPeer()->getLocalIp();
	DWORD dwAddress= ntohl( inet_addr(IPstr.c_str()));   
	m_Ip = dwAddress;  
	UpdateData(false);
	//����log�߳�
	SetTimer(1,200,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//��������Log���߳�
void JoinPage::UpdateLog()
{
	string result;
	result = theApp.scout.str();
	theApp.scout.str("");
	CString tmp(result.c_str());
	if(tmp.IsEmpty() || tmp.GetLength() == 0)  
		return;
	else
	{
		//����m_logEdit��ֵ
		tmp.Replace(_T("\n"),_T("\r\n"));
		CString old = getLogText();
		CString final = old + tmp;
		final = formatLogText(final);
		m_logEdit.SetWindowTextW(final);
	}
}

void JoinPage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case 1:
		UpdateLog();
		break;
	case 2:
		break;
	}
}

//��ȡlogEdit������
CString JoinPage::getLogText()
{
	m_logEdit.SetReadOnly();
	CString str_data;
	m_logEdit.GetWindowTextW(str_data);
	//m_logEdit.GetLine(0,str_data.GetBuffer(len), len);
	//str_data.ReleaseBuffer(len);
	return str_data;
}

/*��ʽ���ı�������*/
CString JoinPage::formatLogText(CString cstr_log)
{
	vector<CString> arr = Tool::CSplit(cstr_log,L"\r\n");
	CString result = L"";
	if(arr.size() > 25)
	{
		for(int i=arr.size()-25;i<arr.size();i++)
		{
			result += arr[i];
			result += "\r\n";
		}
		return result;
	}
	else
	{
		return cstr_log;
	}
	
}

//������ť��������
void JoinPage::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if(this->m_searchID.IsEmpty() || this->m_searchID.GetLength() == 0)
	{
		AfxMessageBox(_T("ID can't be empty��"));
		return;
	}
	else if(!Tool::CheckNum(m_searchID))
	{
		AfxMessageBox(_T("ID must be number��"));
		return;
	}
	else
	{
		int id = _ttoi(m_searchID);
		stringstream ss;ss<<id;
		string cmdstr = "search " + ss.str(); 
		CommandHandle* commandHandle = new CommandHandle(cmdstr,peerServer->getPeer());
		try{
			commandHandle->start();
		}
		catch(...)
		{
			AfxMessageBox(_T("Exception occured during Search ! Please check your network connection !"));
			return;
		}
	}
}
