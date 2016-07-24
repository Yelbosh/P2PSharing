#pragma once
#include "Peer.h"

class Leave
{
private:
	Peer* peer;
public:
	Leave(void);
	Leave(Peer* peer);
	void start_leave();//离开网络的入口函数
	void tell_neighbor();//告知邻居节点
	void leave_transfer();//将属于自己的key的hash转移至后继节点
	void send_leave_msg();//将自己离开网络的消息沿环传送，使得每个节点更新自己的FingerTable
	virtual ~Leave(void);
};

