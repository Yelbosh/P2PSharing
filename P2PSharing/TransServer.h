#pragma once
#include "cthread.h"
#include "Sock.h"
#include "Peer.h"
using namespace SockUtil;

class TransServer :
	public CThread
{
private:
	int serverPort;
	int nodeId;
	CServerSocket serverSocket;
	CSocket* socket;
	Peer* peer;
public:
	TransServer(void);
	TransServer(Peer* peer,int serverPort, int nodeId);/*����һ���̣߳������ܴ�����Դ��socket�������ڸ��߳��������ÿһ���ļ�����������Ӧ���߳�*/
	void run();
	Peer* getPeer();
	void listenRequest();
	virtual ~TransServer(void);
};

