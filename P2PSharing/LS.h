#pragma once

#include "Peer.h"
using namespace std;

class LS
{
private:
	Peer* peer;
public:
	LS(void);
	string list();
	LS(Peer* peer);
	virtual ~LS(void);
};

