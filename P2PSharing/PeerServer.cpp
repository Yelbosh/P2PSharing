#include "StdAfx.h"
#include "PeerServer.h"
#include "RequestHandle.h"
#include "TransServer.h"
#include <exception>

using namespace std;

PeerServer::PeerServer(void)
{
}

PeerServer::PeerServer(int serverPort, int nodeId)
{
	this->serverPort = serverPort;
	this->nodeId = nodeId;
	this->peer = Peer(this->serverPort,this->nodeId);
}

void PeerServer::setPort(int serverPort){
	this->serverPort = serverPort;
}

int PeerServer::getPort()
{
	return this->serverPort;
}
void PeerServer::setNodeId(int nodeId)
{
	this->nodeId = nodeId;
}
int PeerServer::getNodeId()
{
	return this->nodeId;
}

Peer* PeerServer::getPeer()
{
	return &(this->peer);
}

void PeerServer::listenRequest()
{
	this->serverSocket = CServerSocket();
	this->serverSocket.SetPort(this->serverPort);
	/*启动文件接收线程*/
	TransServer* transServer = new TransServer(&peer,Config::TRANS_PORT_BASE+nodeId,nodeId);
	transServer->start();

	while(true)
	{
		socket = this->serverSocket.Accept();
		RequestHandle* requestHandle = new RequestHandle(socket,&peer);
		requestHandle->start();
	}
}

void PeerServer::run()
{
	try {
		listenRequest();
	} catch (...) {
		AfxMessageBox(_T("Exception occured during listen request in peer server !"));
	}
}

PeerServer::~PeerServer(void)
{
}
