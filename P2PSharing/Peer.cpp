#include "StdAfx.h"
#include "Peer.h"


char* Peer::DEFAULT_DEST_IP = "127.0.0.1";

Peer::Peer(void)
{
}

Peer::Peer(int initPort,int identifier)
{
	this->port = initPort;
	this->identifier = identifier;
	this->fingerTable = FingerTable(this->identifier,Config::TABLE_SIZE);//初始化FingerTable，TableSize为5，共32个节点
}

string Peer::getLocalIp() throw (CSocketException)
{
	char szHostName[128] = {0};
	gethostname(szHostName, 128);
	/*hostent* phostent = gethostbyname(szHostName);
	string strip = inet_ntoa(*(in_addr*)&phostent->h_addr_list);*/
	hostent* host = gethostbyname("");
	string strip = inet_ntoa(*(struct in_addr*)*(host->h_addr_list));
	return strip;
}

string Peer::display()
{
	return this->fingerTable.display();
}

int Peer::getPort()
{
	return this->port;
}

void Peer::setPort(int newPort)
{
	this->port = newPort;
}

int Peer::getId()
{
	return this->identifier;
}

Peer::~Peer(void)
{
}
