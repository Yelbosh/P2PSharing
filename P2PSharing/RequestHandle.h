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
	//直接更新后继信息
	void updateSucSuc(int new_sucid,string new_sucip,int new_sucport);
	void updatePrePre(int new_id,string new_ip, int new_port);
	void updateSuc(int new_sucid,string new_sucip,int new_sucport);
	void updateSuc(int new_sucid,string new_sucip,int new_sucport, int suc_suc_id, string suc_suc_ip, int suc_suc_port);
	void updatePre(int new_preid, string new_preip,int new_preport);
	void updatePre(int new_preid, string new_preip,int new_preport, int pre_pre_id, string pre_pre_ip, int pre_pre_port);
	
	void new_node_come(int id, string ip, int port);//更新环上每一个节点的FingerTable中的后继列表
	void transfer_keys(string new_ip, int new_port, int new_id, int new_pre);//将资源的hash进行交接
	void transfer_data_item(string new_ip, int new_port, int key, vector<string> value);//transfer_key 子函数
	void receive_data_item(int key, string value);//接收到key的hash
	void rec_leave(string le_ip, int le_port, int le_id, int le_suc_id,int ttl);//收到某节点即将离开拓扑的消息，进行FingerTable的更新及其消息的传递
	void search_data(int searchid, string origin_ip, int origin_port, int ttl, int get);//查找文件信息函数
	void searchNext(string next_ip,int next_port, string origin_ip, int origin_port, int searchid, int ttl, int get);//查询连接函数
	void file_trans_request(string hash_ip,int hash_port,int hash_id,int key);//获取拥有此资源hash的节点的信息
	vector<vector<string>> resourceSplit(vector<string> addrs,int length);
	static bool inRange(int id, int low, int high, bool low_open, bool high_open);
	virtual ~RequestHandle(void);
};

