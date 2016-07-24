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
	void startSearch(int get);//���ҵ���ں���
	void searchNext(string nextIp,int nextPort,string localip, int localport, int localid, int ttl, int get);//���ҵ����Ӻ���
	void fileLocalTrans(string hash_ip,int hash_port,int hash_id,int key);//routing ��Ϣ�ڱ��ص�ʱ����ļ����ͺ���
	vector<vector<string>> resourceSplit(vector<string> addrs,int length);
	virtual ~Search(void);
};

