#pragma once
#include "PeerServer.h"
#include "LS.h"

// StatusPage �Ի���

class StatusPage : public CDialogEx
{
	DECLARE_DYNAMIC(StatusPage)

public:
	StatusPage(CWnd* pParent = NULL);   // ��׼���캯��
	StatusPage(PeerServer* peerServer,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~StatusPage();

// �Ի�������
	enum { IDD = IDD_STATUS };
//�Զ��岿��
	PeerServer* peerServer;
	LS ls;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_peerStatus;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
