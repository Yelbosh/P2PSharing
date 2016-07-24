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
	void startJoin();//�����������˵���ں���
	string findPre(int localId);//Ѱ�������pre
	string findPre(string ip, int port);//����ip��port��Ѱ��pre
	string findSuc(int localId);//Ѱ�������suc
	string findSuc(string ip, int port);//����ip��port��Ѱ��suc
	string findClosestPrecedingFinger(int id, string remoteIp, int remotePort);//Ѱ�������id�����ip��port�ֱ��������ʾ�Ľڵ��ǰ�̽ڵ�
	void init_finger_table();//��ʼ��fingerTable
	void init_suc_suc_pre_pre();//����ǰ�̵�ǰ�̺ͺ�̵ĺ��
	void update_neighbour();//�����ھӵ�ǰ�̺ͺ��
	void update_others();//��������������ʱ����Ҫ֪ͨ�����ڵ㣬ʹ���Ǹ����Լ���FingerTable
	void transfer_keys();//�½ڵ������������ʱ����ЩС�Ĺ�ϣ����Ҫupdate�������ڵ���Ҫ����������½ڵ��key���͸���
	void suc_suc_pre_pre();//����ǰ�̵�ǰ�̺ͺ�̵ĺ��
	virtual ~Join(void);
};

