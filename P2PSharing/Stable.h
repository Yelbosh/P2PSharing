#pragma once
#include <string>
#include "CThread.h"
#include "Peer.h"

using namespace std;

class Stable:
	public CThread
{
private:
	Peer* peer;
	int detect_id;
	string detect_ip;
	int detect_port;
	int detect_id2;
	string detect_ip2;
	int detect_port2;
public:
	Stable(void);
	Stable(Peer* peer,int id,string ip,int port,int id2,string ip2,int port2);
	void run();
	bool detectPre();/*检测前继结点是否在工作*/
	void preRecover();/*将前继结点进行更新*/
	void sendRecover();/*告诉node环上的其他结点，前继结点已经离开*/

	bool detectPrePre();/*检测前继前继结点是否在工作*/
	void prepreRecover();/*将前继前继结点进行更新*/
	void sendRecover2();/*告诉node环上的其他结点，前继前继结点已经离开*/
	virtual ~Stable(void);
};

