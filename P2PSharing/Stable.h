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
	bool detectPre();/*���ǰ�̽���Ƿ��ڹ���*/
	void preRecover();/*��ǰ�̽����и���*/
	void sendRecover();/*����node���ϵ�������㣬ǰ�̽���Ѿ��뿪*/

	bool detectPrePre();/*���ǰ��ǰ�̽���Ƿ��ڹ���*/
	void prepreRecover();/*��ǰ��ǰ�̽����и���*/
	void sendRecover2();/*����node���ϵ�������㣬ǰ��ǰ�̽���Ѿ��뿪*/
	virtual ~Stable(void);
};

