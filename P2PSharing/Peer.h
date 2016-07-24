#pragma once

#include "Config.h"
#include "FingerTable.h"
#include "Sock.h"

using namespace std;
using namespace SockUtil;

class Peer
{
private:
	int port;
	int identifier;
	CServerSocket serverSocket;
	CSocket socket;
public:
	Peer(void);
	Peer(int initPort,int identifier);
	virtual ~Peer(void);
	string display();
	int getPort();
	void setPort(int newPort);
	int getId();
	static string getLocalIp() throw (CSocketException);//取得本地ip
	static char* DEFAULT_DEST_IP;//the default IP
	static const int DEFAULT_DEST_PORT=8000;//the default PORT
	static const int TTL = 32;// the default TTL
	FingerTable fingerTable;
};

