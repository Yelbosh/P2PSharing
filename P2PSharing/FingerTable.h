#pragma once

#include<string>
#include<vector>
#include<map>

using namespace std;

class FingerTable
{
public:
	FingerTable(void);
	FingerTable(int identifier, int tableSize);
	string getIp(int i);//获取ip地址
	int getSucTableElement(int i);//获取后继列表中位置为i的元素
	void init();//初始化FingerTable
	int getPreId ();//获取前继节点的id
	int getSuccessorId();//获取后继节点的id
	string display();//显示出FingerTable的结构q
	void updateKeyList(int key,string item);
	~FingerTable(void);

	//标识符和tablesize
	int identifier;
	int tableSize;

	//本地ip和端口
	string ip;
	int port;
	//所直接维护的节点的id
	int preId;
	int sucId;
	int prepreId;
	int sucsucId;
	//前继和后继的ip,端口
	string preIP;
	int prePort;
	string sucIP;
	int sucPort;
	//前继前继和后继后继的ip和端口
	string sucsucIP;
	int sucsucPort;
	string prepreIP;
	int preprePort;

	vector<int> sucTable;//后继节点的列表
	vector<string>  ipTable;//后继节点所对应的ip和port

	map<int,vector<string>> keyList;//存储各个资源所对应的ip地址
};

