#pragma once
#include "CThread.h"
#include <string>
using namespace std;

class SendHandle :
	public CThread
{
private:
	string des_ip;
	int des_port;
	string hash_ip;
	int hash_port;
	int key;
	int length;
	int startPos;
	int partLen;
public:
	SendHandle(void);
	SendHandle(string des_ip,int des_port,string hash_ip,int hash_port,int key,int length,int startPos,int partLen);
	void run();
	void sendPart();
	virtual ~SendHandle(void);
};

