#pragma once
#include<iostream>
#include "Peer.h"
using namespace std;

class Join
{
private:
	Peer* peer;
	string dest_ip;
	int dest_port;
public:
	Join(void);
	Join(Peer* peer);
	Join(Peer* peer,string dest_ip,int dest_port);
	void startJoin();//加入网络拓扑的入口函数
	string findPre(int localId);//寻找自身的pre
	string findPre(string ip, int port);//根据ip和port来寻找pre
	string findSuc(int localId);//寻找自身的suc
	string findSuc(string ip, int port);//根据ip和port来寻找suc
	string findClosestPrecedingFinger(int id, string remoteIp, int remotePort);//寻找离给定id最近的ip和port分别如参数所示的节点的前继节点
	void init_finger_table();//初始化fingerTable
	void init_suc_suc_pre_pre();//更新前继的前继和后继的后继
	void update_neighbour();//更新邻居的前继和后继
	void update_others();//当加入网络拓扑时，需要通知其他节点，使他们更新自己的FingerTable
	void transfer_keys();//新节点加入网络拓扑时，这些小的哈希表需要update，其他节点需要把属于这个新节点的key传送给它
	void suc_suc_pre_pre();//更新前继的前继和后继的后继
	virtual ~Join(void);
};

