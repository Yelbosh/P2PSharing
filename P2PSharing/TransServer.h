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
	TransServer(Peer* peer,int serverPort, int nodeId);/*启动一个线程，来接受传送资源的socket，并且在该线程中再针对每一个文件传送启动相应的线程*/
	void run();
	Peer* getPeer();
	void listenRequest();
	virtual ~TransServer(void);
};

