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
	string getIp(int i);//��ȡip��ַ
	int getSucTableElement(int i);//��ȡ����б���λ��Ϊi��Ԫ��
	void init();//��ʼ��FingerTable
	int getPreId ();//��ȡǰ�̽ڵ��id
	int getSuccessorId();//��ȡ��̽ڵ��id
	string display();//��ʾ��FingerTable�Ľṹq
	void updateKeyList(int key,string item);
	~FingerTable(void);

	//��ʶ����tablesize
	int identifier;
	int tableSize;

	//����ip�Ͷ˿�
	string ip;
	int port;
	//��ֱ��ά���Ľڵ��id
	int preId;
	int sucId;
	int prepreId;
	int sucsucId;
	//ǰ�̺ͺ�̵�ip,�˿�
	string preIP;
	int prePort;
	string sucIP;
	int sucPort;
	//ǰ��ǰ�̺ͺ�̺�̵�ip�Ͷ˿�
	string sucsucIP;
	int sucsucPort;
	string prepreIP;
	int preprePort;

	vector<int> sucTable;//��̽ڵ���б�
	vector<string>  ipTable;//��̽ڵ�����Ӧ��ip��port

	map<int,vector<string>> keyList;//�洢������Դ����Ӧ��ip��ַ
};

