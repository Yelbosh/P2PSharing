#pragma once

#include <process.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

typedef void *HANDLE;

class CThread
{
public:
	CThread(void);
	void start();
    virtual void run();
    HANDLE getThread();
	virtual ~CThread(void);
private:
	HANDLE hThread;
    static void agent(void *p);
};



