// SearchPage.cpp : 实现文件
//

#include "stdafx.h"
#include "P2PSharing.h"
#include "SearchPage.h"
#include "afxdialogex.h"
#include "CommandHandle.h"
#include "PlayThread.h"
#include <mmsystem.h>
#include <windows.h>
#include "Tool.h"
#pragma comment(lib, "winmm.lib")


// SearchPage 对话框

IMPLEMENT_DYNAMIC(SearchPage, CDialogEx)

SearchPage::SearchPage(CWnd* pParent /*=NULL*/)
	: CDialogEx(SearchPage::IDD, pParent)
{

}

SearchPage::SearchPage(PeerServer* peerServer, CWnd* pParent /*=NULL*/)
	: CDialogEx(SearchPage::IDD, pParent)
{
	SearchPage::SearchPage(pParent);
	this->peerServer = peerServer;
}

SearchPage::~SearchPage()
{
}

void SearchPage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress1);
	DDX_Control(pDX, IDC_PERCENT1, m_percent1);
	DDX_Control(pDX, IDC_PROGRESS3, m_playProgress);
	DDX_Control(pDX, IDC_PROGRESS2, m_progress2);
	DDX_Control(pDX, IDC_PERCENT2, m_percent2);
	DDX_Control(pDX, IDC_PROGRESS4, m_progress3);
	DDX_Control(pDX, IDC_PROGRESS5, m_progress4);
	DDX_Control(pDX, IDC_PROGRESS6, m_progress5);
	DDX_Control(pDX, IDC_PROGRESS7, m_progress6);
	DDX_Control(pDX, IDC_PROGRESS8, m_progress7);
	DDX_Control(pDX, IDC_PROGRESS9, m_progress8);
	DDX_Control(pDX, IDC_PROGRESS10, m_progress9);
	DDX_Control(pDX, IDC_PROGRESS11, m_progress10);
	DDX_Control(pDX, IDC_PROGRESS12, m_progress11);
	DDX_Control(pDX, IDC_PROGRESS13, m_progress12);
	DDX_Control(pDX, IDC_PROGRESS14, m_progress13);
	DDX_Control(pDX, IDC_PROGRESS15, m_progress14);
	DDX_Control(pDX, IDC_PROGRESS16, m_progress15);
	DDX_Control(pDX, IDC_PROGRESS17, m_progress16);
	DDX_Control(pDX, IDC_PROGRESS18, m_progress17);
	DDX_Control(pDX, IDC_PROGRESS19, m_progress18);
	DDX_Control(pDX, IDC_PROGRESS20, m_progress19);
	DDX_Control(pDX, IDC_PROGRESS21, m_progress20);
	DDX_Control(pDX, IDC_PROGRESS22, m_progress21);
	DDX_Control(pDX, IDC_PROGRESS23, m_progress22);
	DDX_Control(pDX, IDC_PROGRESS24, m_progress23);
	DDX_Control(pDX, IDC_PROGRESS25, m_progress24);
	DDX_Control(pDX, IDC_PROGRESS26, m_progress25);
	DDX_Control(pDX, IDC_PROGRESS27, m_progress26);
	DDX_Control(pDX, IDC_PROGRESS28, m_progress27);
	DDX_Control(pDX, IDC_PROGRESS29, m_progress28);
	DDX_Control(pDX, IDC_PROGRESS30, m_progress29);
	DDX_Control(pDX, IDC_PROGRESS31, m_progress30);
	DDX_Control(pDX, IDC_PROGRESS32, m_progress31);
	DDX_Control(pDX, IDC_PROGRESS33, m_progress0);
	DDX_Control(pDX, IDC_PERCENT3, m_percent3);
	DDX_Control(pDX, IDC_PERCENT4, m_percent4);
	DDX_Control(pDX, IDC_PERCENT5, m_percent5);
	DDX_Control(pDX, IDC_PERCENT6, m_percent6);
	DDX_Control(pDX, IDC_PERCENT7, m_percent7);
	DDX_Control(pDX, IDC_PERCENT8, m_percent8);
	DDX_Control(pDX, IDC_PERCENT9, m_percent9);
	DDX_Control(pDX, IDC_PERCENT10, m_percent10);
	DDX_Control(pDX, IDC_PERCENT11, m_percent11);
	DDX_Control(pDX, IDC_PERCENT12, m_percent12);
	DDX_Control(pDX, IDC_PERCENT13, m_percent13);
	DDX_Control(pDX, IDC_PERCENT14, m_percent14);
	DDX_Control(pDX, IDC_PERCENT15, m_percent15);
	DDX_Control(pDX, IDC_PERCENT16, m_percent16);
	DDX_Control(pDX, IDC_PERCENT17, m_percent17);
	DDX_Control(pDX, IDC_PERCENT18, m_percent18);
	DDX_Control(pDX, IDC_PERCENT19, m_percent19);
	DDX_Control(pDX, IDC_PERCENT20, m_percent20);
	DDX_Control(pDX, IDC_PERCENT21, m_percent21);
	DDX_Control(pDX, IDC_PERCENT22, m_percent22);
	DDX_Control(pDX, IDC_PERCENT23, m_percent23);
	DDX_Control(pDX, IDC_PERCENT24, m_percent24);
	DDX_Control(pDX, IDC_PERCENT25, m_percent25);
	DDX_Control(pDX, IDC_PERCENT26, m_percent26);
	DDX_Control(pDX, IDC_PERCENT27, m_percent27);
	DDX_Control(pDX, IDC_PERCENT28, m_percent28);
	DDX_Control(pDX, IDC_PERCENT29, m_percent29);
	DDX_Control(pDX, IDC_PERCENT30, m_percent30);
	DDX_Control(pDX, IDC_PERCENT31, m_percent31);
	DDX_Control(pDX, IDC_PERCENT32, m_percent0);
}

BEGIN_MESSAGE_MAP(SearchPage, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &SearchPage::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_Play1, &SearchPage::OnBnClickedPlay1)
	ON_BN_CLICKED(IDC_PLAYSTOP, &SearchPage::OnBnClickedPlaystop)
	ON_BN_CLICKED(IDC_Play2, &SearchPage::OnBnClickedPlay2)
	ON_BN_CLICKED(IDC_BUTTON2, &SearchPage::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &SearchPage::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &SearchPage::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &SearchPage::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &SearchPage::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &SearchPage::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &SearchPage::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &SearchPage::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &SearchPage::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &SearchPage::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &SearchPage::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &SearchPage::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &SearchPage::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &SearchPage::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &SearchPage::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON3, &SearchPage::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON19, &SearchPage::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON35, &SearchPage::OnBnClickedButton35)
	ON_BN_CLICKED(IDC_BUTTON36, &SearchPage::OnBnClickedButton36)
	ON_BN_CLICKED(IDC_BUTTON37, &SearchPage::OnBnClickedButton37)
	ON_BN_CLICKED(IDC_BUTTON38, &SearchPage::OnBnClickedButton38)
	ON_BN_CLICKED(IDC_BUTTON39, &SearchPage::OnBnClickedButton39)
	ON_BN_CLICKED(IDC_BUTTON40, &SearchPage::OnBnClickedButton40)
	ON_BN_CLICKED(IDC_BUTTON41, &SearchPage::OnBnClickedButton41)
	ON_BN_CLICKED(IDC_BUTTON42, &SearchPage::OnBnClickedButton42)
	ON_BN_CLICKED(IDC_BUTTON43, &SearchPage::OnBnClickedButton43)
	ON_BN_CLICKED(IDC_BUTTON44, &SearchPage::OnBnClickedButton44)
	ON_BN_CLICKED(IDC_BUTTON45, &SearchPage::OnBnClickedButton45)
	ON_BN_CLICKED(IDC_BUTTON46, &SearchPage::OnBnClickedButton46)
	ON_BN_CLICKED(IDC_BUTTON47, &SearchPage::OnBnClickedButton47)
	ON_BN_CLICKED(IDC_BUTTON48, &SearchPage::OnBnClickedButton48)
	ON_BN_CLICKED(IDC_BUTTON21, &SearchPage::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &SearchPage::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON23, &SearchPage::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, &SearchPage::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON25, &SearchPage::OnBnClickedButton25)
	ON_BN_CLICKED(IDC_BUTTON26, &SearchPage::OnBnClickedButton26)
	ON_BN_CLICKED(IDC_BUTTON27, &SearchPage::OnBnClickedButton27)
	ON_BN_CLICKED(IDC_BUTTON28, &SearchPage::OnBnClickedButton28)
	ON_BN_CLICKED(IDC_BUTTON29, &SearchPage::OnBnClickedButton29)
	ON_BN_CLICKED(IDC_BUTTON30, &SearchPage::OnBnClickedButton30)
	ON_BN_CLICKED(IDC_BUTTON31, &SearchPage::OnBnClickedButton31)
	ON_BN_CLICKED(IDC_BUTTON32, &SearchPage::OnBnClickedButton32)
	ON_BN_CLICKED(IDC_BUTTON33, &SearchPage::OnBnClickedButton33)
	ON_BN_CLICKED(IDC_BUTTON34, &SearchPage::OnBnClickedButton34)
	ON_BN_CLICKED(IDC_Play3, &SearchPage::OnBnClickedPlay3)
	ON_BN_CLICKED(IDC_Play4, &SearchPage::OnBnClickedPlay4)
	ON_BN_CLICKED(IDC_Play5, &SearchPage::OnBnClickedPlay5)
	ON_BN_CLICKED(IDC_Play6, &SearchPage::OnBnClickedPlay6)
	ON_BN_CLICKED(IDC_Play7, &SearchPage::OnBnClickedPlay7)
	ON_BN_CLICKED(IDC_Play8, &SearchPage::OnBnClickedPlay8)
	ON_BN_CLICKED(IDC_Play9, &SearchPage::OnBnClickedPlay9)
	ON_BN_CLICKED(IDC_Play10, &SearchPage::OnBnClickedPlay10)
	ON_BN_CLICKED(IDC_Play11, &SearchPage::OnBnClickedPlay11)
	ON_BN_CLICKED(IDC_Play12, &SearchPage::OnBnClickedPlay12)
	ON_BN_CLICKED(IDC_Play13, &SearchPage::OnBnClickedPlay13)
	ON_BN_CLICKED(IDC_Play14, &SearchPage::OnBnClickedPlay14)
	ON_BN_CLICKED(IDC_Play15, &SearchPage::OnBnClickedPlay15)
	ON_BN_CLICKED(IDC_Play16, &SearchPage::OnBnClickedPlay16)
	ON_BN_CLICKED(IDC_Play17, &SearchPage::OnBnClickedPlay17)
	ON_BN_CLICKED(IDC_Play18, &SearchPage::OnBnClickedPlay18)
END_MESSAGE_MAP()

//针对每一个timer处理的逻辑

void SearchPage::timerProcess(int key,CProgressCtrl& m_progress,CStatic& m_percent)
{
	double percent_dou = ((double)theApp.GetValue(key)) / theApp.GetLength(key);
	int percent_int = percent_dou*100;
	stringstream ss;ss<<percent_int;
	CString cs_percent = _T("");cs_percent += ss.str().c_str();
	m_percent.SetWindowTextW(cs_percent);
	m_progress.SetRange(0,100);
	m_progress.SetStep(1);
	m_progress.SetPos(percent_int);
	UpdateData(false);
	if((theApp.GetLength(key)!=0) && (theApp.GetValue(key) == theApp.GetLength(key)))
	{
		m_progress.SetRange(0,100);
		m_progress.SetStep(1);
		m_progress.SetPos(100);
		//关停timer
		KillTimer(key);
		//重置和key相关的变量
		theApp.SetValue(key,0);
		theApp.SetLength(key,0);
	}
}

void SearchPage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
	case 1:
	{
		timerProcess(1,m_progress1,m_percent1);
		break;
	}
	case 2:
	{
		timerProcess(2,m_progress2,m_percent2);
		break;
	}
	case 3:
	{
		timerProcess(3,m_progress3,m_percent3);
		break;
	}
	case 4:
	{
		timerProcess(4,m_progress4,m_percent4);
		break;
	}
	case 5:
	{
		timerProcess(5,m_progress5,m_percent5);
		break;
	}
	case 6:
	{
		timerProcess(6,m_progress6,m_percent6);
		break;
	}
	case 7:
	{
		timerProcess(7,m_progress7,m_percent7);
		break;
	}
	case 8:
	{
		timerProcess(8,m_progress8,m_percent8);
		break;
	}
	case 9:
	{
		timerProcess(9,m_progress9,m_percent9);
		break;
	}
	case 10:
	{
		timerProcess(10,m_progress10,m_percent10);
		break;
	}
	case 11:
	{
		timerProcess(11,m_progress11,m_percent11);
		break;
	}
	case 12:
	{
		timerProcess(12,m_progress12,m_percent12);
		break;
	}
	case 13:
	{
		timerProcess(13,m_progress13,m_percent13);
		break;
	}
	case 14:
	{
		timerProcess(14,m_progress14,m_percent14);
		break;
	}
	case 15:
	{
		timerProcess(15,m_progress15,m_percent15);
		break;
	}
	case 16:
	{
		timerProcess(16,m_progress16,m_percent16);
		break;
	}
	case 17:
	{
		timerProcess(17,m_progress17,m_percent17);
		break;
	}
	case 18:
	{
		timerProcess(18,m_progress18,m_percent18);
		break;
	}
	case 19:
	{
		timerProcess(19,m_progress19,m_percent19);
		break;
	}
	case 20:
	{
		timerProcess(20,m_progress20,m_percent20);
		break;
	}
	case 21:
	{
		timerProcess(21,m_progress21,m_percent21);
		break;
	}
	case 22:
	{
		timerProcess(22,m_progress22,m_percent22);
		break;
	}
	case 23:
	{
		timerProcess(23,m_progress23,m_percent23);
		break;
	}
	case 24:
	{
		timerProcess(24,m_progress24,m_percent24);
		break;
	}
	case 25:
	{
		timerProcess(25,m_progress25,m_percent25);
		break;
	}
	case 26:
	{
		timerProcess(26,m_progress26,m_percent26);
		break;
	}
	case 27:
	{
		timerProcess(27,m_progress27,m_percent27);
		break;
	}
	case 28:
	{
		timerProcess(28,m_progress28,m_percent28);
		break;
	}
	case 29:
	{
		timerProcess(29,m_progress29,m_percent29);
		break;
	}
	case 30:
	{
		timerProcess(30,m_progress30,m_percent30);
		break;
	}
	case 31:
	{
		timerProcess(31,m_progress31,m_percent31);
		break;
	}
	case 0:
	{
		timerProcess(0,m_progress0,m_percent0);
		break;
	}
	//Play的进度条
	case 100:
		m_playProgress.SetRange(0,100);
		m_playProgress.SetStep(1);
		m_playProgress.SetPos(theApp.playPer);
		break;
	}
}
               
void SearchPage::OnBnClickedPlaystop()
{
	CString captain;
	GetDlgItemText(IDC_PLAYSTOP,captain);
	if(captain == "Stop")
	{
		//设置文本
		CString newcap("Continue");
		SetDlgItemText(IDC_PLAYSTOP,newcap);
		// TODO: 在此添加控件通知处理程序代码
		try{
			SuspendThread(theApp.playHandle);
		}catch(...)
		{
			
		}
		
	}
	else
	{
		//设置文本
		CString newcap("Stop");
		SetDlgItemText(IDC_PLAYSTOP,newcap);
		// TODO: 在此添加控件通知处理程序代码
		try{
			ResumeThread(theApp.playHandle);
		}catch(...)
		{
			
		}
	}
	
}

//===============================DOWNLOAD 函数==========================
void SearchPage::downloadStart(int key)
{
	stringstream ss;ss<<key;
	string cmdstr = "get " + ss.str();
	CommandHandle* commandHandle = new CommandHandle(cmdstr,peerServer->getPeer());
	try{
		commandHandle->start();
	}
	catch(...)
	{
		AfxMessageBox(_T("Exception occured during Join ! Please check your network connection !"));
		return;
	}
	SetTimer(key,500,NULL);
}
void SearchPage::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(1);
}

void SearchPage::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(2);
}

void SearchPage::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(3);
}

void SearchPage::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(4);
}

void SearchPage::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(5);
}

void SearchPage::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(6);
}

void SearchPage::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(7);
}

void SearchPage::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(8);
}

void SearchPage::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(9);
}

void SearchPage::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(10);
}

void SearchPage::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(11);
}

void SearchPage::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(12);
}

void SearchPage::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(13);
}

void SearchPage::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(14);
}

void SearchPage::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(15);
}

void SearchPage::OnBnClickedButton18()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(16);
}

void SearchPage::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(17);
}

void SearchPage::OnBnClickedButton19()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(18);
}

void SearchPage::OnBnClickedButton35()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(19);
}

void SearchPage::OnBnClickedButton36()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(20);
}

void SearchPage::OnBnClickedButton37()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(21);
}

void SearchPage::OnBnClickedButton38()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(22);
}

void SearchPage::OnBnClickedButton39()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(23);
}

void SearchPage::OnBnClickedButton40()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(24);
}

void SearchPage::OnBnClickedButton41()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(25);
}

void SearchPage::OnBnClickedButton42()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(26);
}

void SearchPage::OnBnClickedButton43()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(27);
}

void SearchPage::OnBnClickedButton44()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(28);
}

void SearchPage::OnBnClickedButton45()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(29);
}

void SearchPage::OnBnClickedButton46()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(30);
}

void SearchPage::OnBnClickedButton47()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(31);
}

void SearchPage::OnBnClickedButton48()
{
	// TODO: 在此添加控件通知处理程序代码
	downloadStart(0);
}
//===============================DOWNLOAD 函数==========================

//===============================PLAY 函数==========================
void SearchPage::OnBnClickedPlay1()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(1);
}

void SearchPage::OnBnClickedPlay2()
{
	playMusic(2);
}

void SearchPage::OnBnClickedButton21()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(3);
}

void SearchPage::OnBnClickedButton22()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(4);
}

void SearchPage::OnBnClickedButton23()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(5);
}

void SearchPage::OnBnClickedButton24()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(6);
}

void SearchPage::OnBnClickedButton25()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(7);
}

void SearchPage::OnBnClickedButton26()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(8);
}

void SearchPage::OnBnClickedButton27()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(9);
}

void SearchPage::OnBnClickedButton28()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(10);
}

void SearchPage::OnBnClickedButton29()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(11);
}

void SearchPage::OnBnClickedButton30()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(12);
}

void SearchPage::OnBnClickedButton31()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(13);
}

void SearchPage::OnBnClickedButton32()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(14);
}

void SearchPage::OnBnClickedButton33()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(15);
}

void SearchPage::OnBnClickedButton34()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(16);
}

void SearchPage::OnBnClickedPlay3()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(17);
}

void SearchPage::OnBnClickedPlay4()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(18);
}

void SearchPage::OnBnClickedPlay5()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(19);
}

void SearchPage::OnBnClickedPlay6()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(20);
}

void SearchPage::OnBnClickedPlay7()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(21);
}

void SearchPage::OnBnClickedPlay8()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(22);
}

void SearchPage::OnBnClickedPlay9()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(23);
}

void SearchPage::OnBnClickedPlay10()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(24);
}

void SearchPage::OnBnClickedPlay11()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(25);
}

void SearchPage::OnBnClickedPlay12()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(26);
}

void SearchPage::OnBnClickedPlay13()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(27);
}

void SearchPage::OnBnClickedPlay14()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(28);
}

void SearchPage::OnBnClickedPlay15()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(29);
}

void SearchPage::OnBnClickedPlay16()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(30);
}

void SearchPage::OnBnClickedPlay17()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(31);
}

void SearchPage::OnBnClickedPlay18()
{
	// TODO: 在此添加控件通知处理程序代码
	playMusic(0);
}

void SearchPage::playMusic(int key)
{
	//重置Stop按钮
	CString newcap("Stop");
	SetDlgItemText(IDC_PLAYSTOP,newcap);
	theApp.playPer = 0;
	SuspendThread(theApp.playHandle);
	KillTimer(100);
	SetTimer(100,500,NULL);
	theApp.playKey = key;
	PlayThread* playThread = new PlayThread(theApp.playKey);
	playThread->start();
	theApp.playHandle = playThread->getThread();
}