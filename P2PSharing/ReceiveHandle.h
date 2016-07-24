#pragma once
#include "CThread.h"
#include "Sock.h"

using namespace SockUtil;
using namespace std;

class ReceiveHandle :
	public CThread
{
private:
	CSocket* socket;
	/*string des_ip;
	int des_port;
	string hash_ip;
	int hash_port;
	int key;
	int length;
	int startPos;
	int partLen;
	int start;
	int bufLen;*/
public:
	ReceiveHandle(void);
	ReceiveHandle(CSocket* socket);
	void run();
	void receivePart();
	virtual ~ReceiveHandle(void);
};

