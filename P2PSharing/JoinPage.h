#pragma once
#include "PeerServer.h"
#include "afxwin.h"

// JoinPage 对话框

class JoinPage : public CDialogEx
{
	DECLARE_DYNAMIC(JoinPage)

public:
	JoinPage(CWnd* pParent = NULL);   // 标准构造函数
	JoinPage(PeerServer* peerServer, CWnd* pParent = NULL);   // 自定义构造函数
	virtual ~JoinPage();

// 对话框数据
	enum { IDD = IDD_JOIN };
//自定义部分
	PeerServer* peerServer;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_leaveBtn;
	afx_msg void OnBnClickedButton2();
	CButton m_joinBtn;
	afx_msg void OnBnClickedButton4();
	DWORD m_Ip;
	CString m_Port;
	CEdit m_logEdit;
	virtual BOOL OnInitDialog();
	void UpdateLog();
	CString getLogText();
	CString formatLogText(CString cstr_log);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_searchID;
	afx_msg void OnBnClickedButton1();
};
