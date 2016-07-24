#include "StdAfx.h"
#include "CThread.h"


CThread::CThread(void)
{
}


CThread::~CThread(void)
{
}

void CThread::start()
{
        hThread =(HANDLE)_beginthread(agent, 0, (void *)this);
}
void CThread::run()
{

}
void CThread::agent(void *p)
{
        CThread *agt = (CThread *)p;
        agt->run();
}
HANDLE CThread::getThread()
{
        return hThread;
}