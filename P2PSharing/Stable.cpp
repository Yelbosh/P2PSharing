#include "StdAfx.h"
#include "Stable.h"
#include "Sock.h"
#include "Tool.h"
#include <iostream>
#include <sstream>
#include "P2PSharing.h"


using namespace std;
using namespace SockUtil;


Stable::Stable(void)
{
}

Stable::Stable(Peer* peer,int id,string ip,int port,int id2,string ip2,int port2)
{
	this->peer = peer;
	this->detect_id=id;
	this->detect_ip=ip;
	this->detect_port=port;
	this->detect_id2=id2;
	this->detect_ip2=ip2;
	this->detect_port2=port2 ;
}

void Stable::run()
{
	while(true){
		//���ǰ��
		if (!detectPre()){
			preRecover();
			sendRecover();
		}
		//���ǰ�̵�ǰ��
		if (!detectPrePre()){
			prepreRecover();
			sendRecover2();
		}
		try{
			Sleep(2000);
			//theApp.scout<<"stable the network!"<<endl;
		}catch(...)
		{
			theApp.scout<<"exception occured during Sleep in Stable!"<<endl;
		}
	}
}

/*���ǰ�̽���Ƿ��ڹ���*/
bool Stable::detectPre()
{
	string preIp = peer->fingerTable.preIP;
	int prePort = peer->fingerTable.prePort;
	try{
		CSocket socket;
		socket.Connect(preIp.c_str(),prePort);
		string cmd = "ping";
		socket.WriteLine(cmd);
		string rec_msg;
		rec_msg = socket.ReadLine();
		socket.Close();
		if (rec_msg == "pong")
			return true;
	}catch(...)
	{
		return false;
	}
	return false;
}

/*���ǰ��ǰ�̽���Ƿ��ڹ���*/
bool Stable::detectPrePre()
{
	string prepreIp = peer->fingerTable.prepreIP;
	int preprePort = peer->fingerTable.preprePort;
	try{
		CSocket socket;
		socket.Connect(prepreIp.c_str(),preprePort);
		string cmd = "ping";
		socket.WriteLine(cmd);
		string rec_msg;
		rec_msg = socket.ReadLine();
		socket.Close();
		if (rec_msg == "pong")
			return true;
	}catch(...)
	{
		//return false;
	}
	return true;
}

/*��ǰ�̽����и���*/
void Stable::preRecover()
{
	//����ǰ�̵�ǰ�̵���Ϣ
	string ip = peer->fingerTable.prepreIP;
	int port = peer->fingerTable.preprePort;
	int id = peer->fingerTable.prepreId;

	stringstream ss1,ss2,ss3,ss4;ss1<<peer->getId();ss2<<peer->fingerTable.port;ss3<<peer->fingerTable.sucId;ss4<<peer->fingerTable.sucPort;
	string cmd = "your_suc_le " + ss1.str() + " " + ss1.str() + " " + peer->fingerTable.ip + " " + ss2.str() + " " + ss3.str() + " " + peer->fingerTable.sucIP + " " + ss4.str();
	CSocket socket;
	socket.Connect(ip.c_str(),port);
	socket.WriteLine(cmd);
	socket.Close();

	//���º�̵ĺ�̵���Ϣ
	stringstream ss5,ss6;ss5<<id;ss6<<port;
	cmd="your_pre_pre_le " + ss1.str() + " " + ss5.str() + " " + ip + " " + ss6.str();
	CSocket sucSocket;
	sucSocket.Connect(peer->fingerTable.sucIP.c_str(),peer->fingerTable.sucPort);
	sucSocket.WriteLine(cmd);
	sucSocket.Close();

	//�����������Ϣ
	peer->fingerTable.preId = peer->fingerTable.prepreId;//����pre��Ϣ
	peer->fingerTable.preIP = peer->fingerTable.prepreIP;
	peer->fingerTable.prePort = peer->fingerTable.preprePort;
	cmd = "yourpre";
	CSocket preSocket;
	preSocket.Connect(peer->fingerTable.preIP.c_str(),peer->fingerTable.prePort);
	preSocket.WriteLine(cmd);
	string rec;
	rec = preSocket.ReadLine();
	vector<string> s = Tool::Split(rec," ");//����prepre��Ϣ
	peer->fingerTable.prepreId = atoi(s[2].c_str());
	peer->fingerTable.prepreIP = s[0];
	peer->fingerTable.preprePort = atoi(s[1].c_str());
	//����sucTable
	for (int i=0; i<peer->fingerTable.sucTable.size();i++){
		int fingerNode = peer->fingerTable.sucTable[i];
		if (fingerNode == detect_id2)
		{
			peer->fingerTable.sucTable[i] = peer->getId();
			stringstream portstr;portstr<<peer->fingerTable.port;
			peer->fingerTable.ipTable[i] = (peer->fingerTable.ip + " " + portstr.str());
		}
	}
}

/*��ǰ��ǰ�̽����и���*/
void Stable::prepreRecover()
{
	string cmd;
	//����ǰ��ǰ�̵�ǰ�̵���Ϣ����֪��suc�Ѿ��뿪
	string ip = peer->fingerTable.preIP;
	int port = peer->fingerTable.prePort;
	int id = peer->fingerTable.preId;
	//��ȡǰ�̵�prepre
	cmd = "yourprepre";
	CSocket preSocket1;
	preSocket1.Connect(ip.c_str(),port);
	preSocket1.WriteLine(cmd);
	string rec1;
	rec1 = preSocket1.ReadLine();
	vector<string> s1 = Tool::Split(rec1," ");//����prepre��Ϣ
	//��ȡ��prepre��ǰ��
	int pre_prepreId = atoi(s1[2].c_str());
	string pre_prepreIP = s1[0];
	int pre_preprePort = atoi(s1[1].c_str());
	//��֪prepreǰ�������Ѿ��뿪
	stringstream ss1,ss2,ss3,ss4;ss1<<id;ss2<<port;ss3<<peer->getId();ss4<<peer->getPort();
	cmd = "your_suc_le " + ss1.str() + " " + ss1.str() + " " + ip + " " + ss2.str() + " " + ss3.str() + " " + peer->getLocalIp() + " " + ss4.str();
	CSocket socket;
	socket.Connect(pre_prepreIP.c_str(),pre_preprePort);
	socket.WriteLine(cmd);
	socket.Close();

	//���º�̵ĺ�̵���Ϣ
	/*stringstream ss5,ss6;ss5<<id;ss6<<port;
	cmd="your_pre_le " + ss1.str() + " " + ss5.str() + " " + ip + " " + ss6.str();
	CSocket sucSocket;
	sucSocket.Connect(peer->fingerTable.sucIP.c_str(),peer->fingerTable.sucPort);
	sucSocket.WriteLine(cmd);
	sucSocket.Close();*/

	//�����������Ϣ
	peer->fingerTable.prepreId = pre_prepreId;//����pre��Ϣ
	peer->fingerTable.prepreIP = pre_prepreIP;
	peer->fingerTable.prePort = pre_preprePort;
	//����sucTable
	for (int i=0; i<peer->fingerTable.sucTable.size();i++){
		int fingerNode = peer->fingerTable.sucTable[i];
		if (fingerNode == detect_id)
		{
			peer->fingerTable.sucTable[i] = id;
			stringstream portstr;portstr<<port;
			peer->fingerTable.ipTable[i] = (ip + " " + portstr.str());
		}
	}
}


/*����node���ϵ�������㣬ǰ�̽���Ѿ��뿪*/
void Stable::sendRecover()
{
	stringstream ss1,ss2,ss3,ss4;ss1<<this->detect_id;ss2<<peer->fingerTable.port;ss3<<peer->getId();ss4<<Config::NODE_SUM;
	string cmd = "le " + ss1.str() + " " + peer->fingerTable.ip + " " + ss2.str() + " " + ss3.str() + " " + ss4.str();
	this->detect_id = peer->fingerTable.preId;
	this->detect_ip = peer->fingerTable.preIP;
	this->detect_port = peer->fingerTable.prePort;
	CSocket socket;
	socket.Connect(peer->fingerTable.sucIP.c_str(),peer->fingerTable.sucPort);
	socket.WriteLine(cmd);
	socket.Close();
}

/*����node���ϵ�������㣬ǰ��ǰ�̽���Ѿ��뿪*/
void Stable::sendRecover2()
{
	stringstream ss1,ss2,ss3,ss4;ss1<<this->detect_id2;ss2<<peer->fingerTable.prePort;ss3<<peer->fingerTable.preId;ss4<<Config::NODE_SUM;
	string cmd = "le " + ss1.str() + " " + peer->fingerTable.preIP + " " + ss2.str() + " " + ss3.str() + " " + ss4.str();
	this->detect_id2 = peer->fingerTable.prepreId;
	this->detect_ip2 = peer->fingerTable.prepreIP;
	this->detect_port2 = peer->fingerTable.preprePort;
	CSocket socket;
	socket.Connect(peer->fingerTable.sucIP.c_str(),peer->fingerTable.sucPort);
	socket.WriteLine(cmd);
	socket.Close();
}

Stable::~Stable(void)
{
}
