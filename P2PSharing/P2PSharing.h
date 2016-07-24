
// P2PSharing.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include <sstream>
#include "RWLockImpl.h"


// CP2PSharingApp:
// 有关此类的实现，请参阅 P2PSharing.cpp
//

class CP2PSharingApp : public CWinApp
{
public:
	CP2PSharingApp();

// 重写
public:
	virtual BOOL InitInstance();
	std::stringstream scout;
	CMyRWLock Lock;
	/*线程共享变量*/
	volatile int value1;int length1;volatile int value2;int length2;volatile int value3;int length3;volatile int value4;int length4;volatile int value5;int length5;volatile int value6;int length6;volatile int value7;int length7;volatile int value8;int length8;
	volatile int value9;int length9;volatile int value10;int length10;volatile int value11;int length11;volatile int value12;int length12;volatile int value13;int length13;volatile int value14;int length14;volatile int value15;int length15;volatile int value16;int length16;
	volatile int value17;int length17;volatile int value18;int length18;volatile int value19;int length19;volatile int value20;int length20;volatile int value21;int length21;volatile int value22;int length22;volatile int value23;int length23;volatile int value24;int length24;
	volatile int value25;int length25;volatile int value26;int length26;volatile int value27;int length27;volatile int value28;int length28;volatile int value29;int length29;volatile int value30;int length30;volatile int value31;int length31;volatile int value0;int length0;

	/*播放音乐时要用到的变量*/
	int playKey;
	int playPer;
	HANDLE playHandle;
	
// 实现

//自定义的方法
	int GetValue(int key);//获取vilatile变量的值
	void SetValue(int key,int value);//改变vilatile变量的值
	void AddValue(int key,int value);
	int GetLength(int key);//获取长度的值
	void SetLength(int key,int length);//设置长度的值

	DECLARE_MESSAGE_MAP()
};

extern CP2PSharingApp theApp;