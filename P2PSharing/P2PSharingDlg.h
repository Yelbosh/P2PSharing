
// P2PSharingDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "PeerServer.h"
#include "InputPage.h"
#include "StatusPage.h"
#include "JoinPage.h"
#include "SearchPage.h"

// CP2PSharingDlg 对话框
class CP2PSharingDlg : public CDialogEx
{
// 构造
public:
	CP2PSharingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_P2PSHARING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CBrush m_brush;
	CFont m_font;
public:
	// Tab标签页父容器
	CTabCtrl m_Tab;
	InputPage *m_inputPage;
	StatusPage *m_statusPage;
	JoinPage *m_joinPage;
	SearchPage *m_searchPage;
	PeerServer peerServer;//代表本节点的Peer
	/*自定义函数部分--START--*/
	void InitInput();//初始化端口输入页面
	void InitPeerServer(int id);//初始化PeerServer部分
	void UpdateTabControl();//更新TabControl
	void Test(); 
	/*自定义函数部分--END--*/
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_Title;
};
