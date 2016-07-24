#include "StdAfx.h"
#include "Search.h"
#include "Get.h"


Get::Get(void)
{
}

Get::Get(Peer* peer,int key)
{
	this->peer = peer;
	this->key = key;
}

void Get::start_get()
{
	Search search(peer,key);
	search.startSearch(1);
}

Get::~Get(void)
{

}
