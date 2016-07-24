#pragma once
#include "Peer.h"

class Leave
{
private:
	Peer* peer;
public:
	Leave(void);
	Leave(Peer* peer);
	void start_leave();//�뿪�������ں���
	void tell_neighbor();//��֪�ھӽڵ�
	void leave_transfer();//�������Լ���key��hashת������̽ڵ�
	void send_leave_msg();//���Լ��뿪�������Ϣ�ػ����ͣ�ʹ��ÿ���ڵ�����Լ���FingerTable
	virtual ~Leave(void);
};

