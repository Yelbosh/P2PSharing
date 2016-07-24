// InputPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "P2PSharing.h"
#include "InputPage.h"
#include "afxdialogex.h"
#include "P2PSharingDlg.h"
#include "Tool.h"


// InputPage �Ի���

IMPLEMENT_DYNAMIC(InputPage, CDialogEx)

InputPage::InputPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(InputPage::IDD, pParent)
	, m_peerID(_T(""))
{

}

InputPage::~InputPage()
{
}

void InputPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_peerID);
}


BEGIN_MESSAGE_MAP(InputPage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &InputPage::OnBnClickedButton1)
END_MESSAGE_MAP()


// InputPage ��Ϣ�������


void InputPage::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if(this->m_peerID.IsEmpty() || this->m_peerID.GetLength() == 0)
	{
		AfxMessageBox(_T("ID can't be empty��"));
		return;
	}
	else if(!Tool::CheckNum(m_peerID))
	{
		AfxMessageBox(_T("ID must be number��"));
		return;
	}
	else
	{
		CP2PSharingDlg* parent = (CP2PSharingDlg*)(GetParent()->GetParent());//ȡ�ø�����ָ��
		int id = _ttoi(m_peerID);
		parent->InitPeerServer(id);//����PeerServer
		parent->UpdateTabControl();//����TabControl
	}
}


