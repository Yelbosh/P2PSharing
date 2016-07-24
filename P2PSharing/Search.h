#pragma once
#include "Peer.h"

class Search
{
private:
	int searchId;
	Peer* peer;
public:
	Search(void);
	Search(Peer* peer,int searchId);
	void startSearch(int get);//查找的入口函数
	void searchNext(string nextIp,int nextPort,string localip, int localport, int localid, int ttl, int get);//查找的连接函数
	void fileLocalTrans(string hash_ip,int hash_port,int hash_id,int key);//routing 信息在本地的时候的文件传送函数
	vector<vector<string>> resourceSplit(vector<string> addrs,int length);
	virtual ~Search(void);
};

