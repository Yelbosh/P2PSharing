#include "StdAfx.h"
#include "LS.h"


LS::LS(void)
{
}

LS::LS(Peer* peer)
{
	this->peer = peer;
}

string LS::list()
{
	return this->peer->display();
}


LS::~LS(void)
{
}
