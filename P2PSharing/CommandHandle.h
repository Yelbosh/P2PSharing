#pragma once
#include "cthread.h"
#include <string>
#include "Peer.h"

using namespace std;

class CommandHandle :
	public CThread
{
private:
	string cmd;
	Peer* peer;
public:
	CommandHandle(void);
	CommandHandle(string cmd,Peer* peer);
	virtual ~CommandHandle(void);
	void run();
	bool isGoodCommand();
	void falseCommand();
	void handle();
};

