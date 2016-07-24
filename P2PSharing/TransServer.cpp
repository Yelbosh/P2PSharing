#include "StdAfx.h"
#include "TransServer.h"
#include "ReceiveHandle.h"

TransServer::TransServer(void)
{
}

TransServer::TransServer(Peer* peer,int serverPort, int nodeId)
{
	this->peer = peer;
	this->serverPort = serverPort;
	this->nodeId = nodeId;
}

void TransServer::run()
{
	try {
		listenRequest();
	} catch (...) {

	}
}

/*针对每一个传送文件的请求，创建线程*/
void TransServer::listenRequest()
{
	this->serverSocket = CServerSocket();
	this->serverSocket.SetPort(this->serverPort);
	while(true)
	{
		socket = this->serverSocket.Accept();
		ReceiveHandle* receiveHandle = new ReceiveHandle(socket);
		receiveHandle->start();
	}
}

Peer* TransServer::getPeer()
{
	return this->peer;
}

TransServer::~TransServer(void)
{
}
