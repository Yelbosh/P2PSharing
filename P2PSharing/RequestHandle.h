#pragma once

#include "cthread.h"
#include "Peer.h"
#include "Sock.h"

using namespace SockUtil;

class RequestHandle :
	public CThread
{
private:
	CSocket* socket;
	Peer* peer;
public:
	RequestHandle(void);
	RequestHandle(CSocket* socket, Peer* peer);
	void run();
	string get_closest_preceding_finger(int id);
	//ֱ�Ӹ��º����Ϣ
	void updateSucSuc(int new_sucid,string new_sucip,int new_sucport);
	void updatePrePre(int new_id,string new_ip, int new_port);
	void updateSuc(int new_sucid,string new_sucip,int new_sucport);
	void updateSuc(int new_sucid,string new_sucip,int new_sucport, int suc_suc_id, string suc_suc_ip, int suc_suc_port);
	void updatePre(int new_preid, string new_preip,int new_preport);
	void updatePre(int new_preid, string new_preip,int new_preport, int pre_pre_id, string pre_pre_ip, int pre_pre_port);
	
	void new_node_come(int id, string ip, int port);//���»���ÿһ���ڵ��FingerTable�еĺ���б�
	void transfer_keys(string new_ip, int new_port, int new_id, int new_pre);//����Դ��hash���н���
	void transfer_data_item(string new_ip, int new_port, int key, vector<string> value);//transfer_key �Ӻ���
	void receive_data_item(int key, string value);//���յ�key��hash
	void rec_leave(string le_ip, int le_port, int le_id, int le_suc_id,int ttl);//�յ�ĳ�ڵ㼴���뿪���˵���Ϣ������FingerTable�ĸ��¼�����Ϣ�Ĵ���
	void search_data(int searchid, string origin_ip, int origin_port, int ttl, int get);//�����ļ���Ϣ����
	void searchNext(string next_ip,int next_port, string origin_ip, int origin_port, int searchid, int ttl, int get);//��ѯ���Ӻ���
	void file_trans_request(string hash_ip,int hash_port,int hash_id,int key);//��ȡӵ�д���Դhash�Ľڵ����Ϣ
	vector<vector<string>> resourceSplit(vector<string> addrs,int length);
	static bool inRange(int id, int low, int high, bool low_open, bool high_open);
	virtual ~RequestHandle(void);
};

