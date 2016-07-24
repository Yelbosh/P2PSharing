#pragma once

#include "Sock.h"
#include "cthread.h"
#include "Peer.h"

using namespace SockUtil;

class PeerServer :
	public CThread
{
private:
	int serverPort;
	int nodeId;
	CServerSocket serverSocket;
	CSocket* socket;
	Peer peer;
public:
	PeerServer(void);
	PeerServer(int serverPort, int nodeId);
	void setPort(int serverPort);
	int getPort();
	void setNodeId(int nodeId);
	Peer* getPeer();
	int getNodeId();
	void listenRequest() throw (CSocketException);
	virtual ~PeerServer(void);
	void run();
};

