#pragma once
#include "PeerServer.h"
#include "LS.h"

// StatusPage 对话框

class StatusPage : public CDialogEx
{
	DECLARE_DYNAMIC(StatusPage)

public:
	StatusPage(CWnd* pParent = NULL);   // 标准构造函数
	StatusPage(PeerServer* peerServer,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~StatusPage();

// 对话框数据
	enum { IDD = IDD_STATUS };
//自定义部分
	PeerServer* peerServer;
	LS ls;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_peerStatus;
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
