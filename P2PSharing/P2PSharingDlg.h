
// P2PSharingDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "PeerServer.h"
#include "InputPage.h"
#include "StatusPage.h"
#include "JoinPage.h"
#include "SearchPage.h"

// CP2PSharingDlg �Ի���
class CP2PSharingDlg : public CDialogEx
{
// ����
public:
	CP2PSharingDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_P2PSHARING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CBrush m_brush;
	CFont m_font;
public:
	// Tab��ǩҳ������
	CTabCtrl m_Tab;
	InputPage *m_inputPage;
	StatusPage *m_statusPage;
	JoinPage *m_joinPage;
	SearchPage *m_searchPage;
	PeerServer peerServer;//�����ڵ��Peer
	/*�Զ��庯������--START--*/
	void InitInput();//��ʼ���˿�����ҳ��
	void InitPeerServer(int id);//��ʼ��PeerServer����
	void UpdateTabControl();//����TabControl
	void Test(); 
	/*�Զ��庯������--END--*/
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_Title;
};
