#pragma once
#include "PeerServer.h"
#include "afxcmn.h"
#include "afxwin.h"

// SearchPage 对话框

class SearchPage : public CDialogEx
{
	DECLARE_DYNAMIC(SearchPage)

public:
	SearchPage(CWnd* pParent = NULL);   // 标准构造函数
	SearchPage(PeerServer* peerServer, CWnd* pParent = NULL);   // 自定义构造函数
	virtual ~SearchPage();

// 对话框数据
	enum { IDD = IDD_SEARCH };
//自定义部分
	PeerServer* peerServer;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void playMusic(int key);
	void downloadStart(int key);
		void timerProcess(int key,CProgressCtrl& m_progress,CStatic& m_percent);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CProgressCtrl m_progress1;
	CStatic m_percent1;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedPlay1();
	CProgressCtrl m_playProgress;
	afx_msg void OnBnClickedPlaystop();
	afx_msg void OnBnClickedPlay2();
	CProgressCtrl m_progress2;
	CStatic m_percent2;
	CProgressCtrl m_progress3;
	CProgressCtrl m_progress4;
	CProgressCtrl m_progress5;
	CProgressCtrl m_progress6;
	CProgressCtrl m_progress7;
	CProgressCtrl m_progress8;
	CProgressCtrl m_progress9;
	CProgressCtrl m_progress10;
	CProgressCtrl m_progress11;
	CProgressCtrl m_progress12;
	CProgressCtrl m_progress13;
	CProgressCtrl m_progress14;
	CProgressCtrl m_progress15;
	CProgressCtrl m_progress16;
	CProgressCtrl m_progress17;
	CProgressCtrl m_progress18;
	CProgressCtrl m_progress19;
	CProgressCtrl m_progress20;
	CProgressCtrl m_progress21;
	CProgressCtrl m_progress22;
	CProgressCtrl m_progress23;
	CProgressCtrl m_progress24;
	CProgressCtrl m_progress25;
	CProgressCtrl m_progress26;
	CProgressCtrl m_progress27;
	CProgressCtrl m_progress28;
	CProgressCtrl m_progress29;
	CProgressCtrl m_progress30;
	CProgressCtrl m_progress31;
	CProgressCtrl m_progress0;
	CStatic m_percent3;
	CStatic m_percent4;
	CStatic m_percent5;
	CStatic m_percent6;
	CStatic m_percent7;
	CStatic m_percent8;
	CStatic m_percent9;
	CStatic m_percent10;
	CStatic m_percent11;
	CStatic m_percent12;
	CStatic m_percent13;
	CStatic m_percent14;
	CStatic m_percent15;
	CStatic m_percent16;
	CStatic m_percent17;
	CStatic m_percent18;
	CStatic m_percent19;
	CStatic m_percent20;
	CStatic m_percent21;
	CStatic m_percent22;
	CStatic m_percent23;
	CStatic m_percent24;
	CStatic m_percent25;
	CStatic m_percent26;
	CStatic m_percent27;
	CStatic m_percent28;
	CStatic m_percent29;
	CStatic m_percent30;
	CStatic m_percent31;
	CStatic m_percent0;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton35();
	afx_msg void OnBnClickedButton36();
	afx_msg void OnBnClickedButton37();
	afx_msg void OnBnClickedButton38();
	afx_msg void OnBnClickedButton39();
	afx_msg void OnBnClickedButton40();
	afx_msg void OnBnClickedButton41();
	afx_msg void OnBnClickedButton42();
	afx_msg void OnBnClickedButton43();
	afx_msg void OnBnClickedButton44();
	afx_msg void OnBnClickedButton45();
	afx_msg void OnBnClickedButton46();
	afx_msg void OnBnClickedButton47();
	afx_msg void OnBnClickedButton48();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton24();
	afx_msg void OnBnClickedButton25();
	afx_msg void OnBnClickedButton26();
	afx_msg void OnBnClickedButton27();
	afx_msg void OnBnClickedButton28();
	afx_msg void OnBnClickedButton29();
	afx_msg void OnBnClickedButton30();
	afx_msg void OnBnClickedButton31();
	afx_msg void OnBnClickedButton32();
	afx_msg void OnBnClickedButton33();
	afx_msg void OnBnClickedButton34();
	afx_msg void OnBnClickedPlay3();
	afx_msg void OnBnClickedPlay4();
	afx_msg void OnBnClickedPlay5();
	afx_msg void OnBnClickedPlay6();
	afx_msg void OnBnClickedPlay7();
	afx_msg void OnBnClickedPlay8();
	afx_msg void OnBnClickedPlay9();
	afx_msg void OnBnClickedPlay10();
	afx_msg void OnBnClickedPlay11();
	afx_msg void OnBnClickedPlay12();
	afx_msg void OnBnClickedPlay13();
	afx_msg void OnBnClickedPlay14();
	afx_msg void OnBnClickedPlay15();
	afx_msg void OnBnClickedPlay16();
	afx_msg void OnBnClickedPlay17();
	afx_msg void OnBnClickedPlay18();
};
