#include "StdAfx.h"
#include "Sock.h"
#include "Join.h"
#include "Tool.h"
#include "Stable.h"
#include<math.h>
#include "RequestHandle.h"
#include <sstream>
#include "P2PSharing.h"

using namespace SockUtil;

Join::Join(void)
{
}

Join::Join(Peer* peer)
{
	this->peer = peer;
	dest_ip=Peer::DEFAULT_DEST_IP;
	dest_port=Peer::DEFAULT_DEST_PORT;
}

Join::Join(Peer* peer,string dest_ip,int dest_port)
{
	this->peer = peer;
	this->dest_ip = dest_ip;
	this->dest_port = dest_port;
}

/*加入网络拓扑的入口函数*/
void Join::startJoin()
{
	theApp.scout<<"+++In the startJoin+++"<<endl;
	init_finger_table();
	update_neighbour();
	update_others();
	theApp.scout<<"before transfer key"<<endl;
	transfer_keys();
	//make the whole topology more stable
	Stable* stable = new Stable(peer,peer->fingerTable.preId,peer->fingerTable.preIP,peer->fingerTable.prePort,peer->fingerTable.prepreId,peer->fingerTable.prepreIP,peer->fingerTable.preprePort);
	stable->start();

}

/*根据ip和port来寻找pre*/
string Join::findPre(string ip, int port)
{
	CSocket socket;
	socket.Connect(ip.c_str(),port);//连接服务器
	string cmd = "yourpre";
	socket.WriteLine(cmd);
	//读取查询结果
	string result = socket.ReadLine();
	theApp.scout<<result<<endl;
	return result;
}

/*寻找自身的pre*/
string Join::findPre(int localId)
{
	theApp.scout<<"+++++++++in findPre++++++"<<endl;
	string remoteSucString=findSuc(dest_ip,dest_port);//首先找到自己要连接的节点的直接后继节点
	vector<string> str = Tool::Split(remoteSucString," ");
	string remoteIp = str[0];
	int remotePort = atoi(str[1].c_str());
	int remoteSuc = atoi(str[2].c_str());

	string remoteNodeIp=dest_ip;
	int remoteNodePort=dest_port;
	theApp.scout<<"the default suc is "<<remoteSuc<<endl;

	int remoteNodeId=dest_port-8000;
	while(true)
	{
		if (RequestHandle::inRange(localId,remoteNodeId,remoteSuc,true,false))//如果新节点的id在要连接的节点和它的直接后继之间或者等于要连接的节点id，则要连接的节点就是所求前继
		{
			theApp.scout<<localId<<" in range from "<<remoteNodeId<<" to "<<remoteSuc<<endl;
			theApp.scout<<"return in pre: "<<remoteNodeIp<<" "<<remoteNodePort<<" "<<remoteNodeId<<endl;
			string result = remoteNodeIp;
			result += " ";
			stringstream ss1,ss2;ss1<<remoteNodePort;ss2<<remoteNodeId;
			result += ss1.str();
			result += " ";
			result += ss2.str();
			return result;
		}
		//如果不在，则继续寻找
		theApp.scout<<localId<<" not in range from "<<remoteNodeId<<" to "<<remoteSuc<<endl;
		//在要连接的节点的后继列表中找出离新节点id最近的节点，可能是要连接的节点本身
		string remoteNodeIdString=findClosestPrecedingFinger(localId,remoteIp,remotePort);
		vector<string> k = Tool::Split(remoteNodeIdString," ");
		remoteNodeIp = k[0];
		remoteNodePort = atoi(k[1].c_str());
		remoteNodeId = atoi(k[2].c_str());

		theApp.scout<<"next requestedNodeId "<<remoteNodeId<<endl;
		remoteSucString = findSuc(remoteIp,remotePort);//为遍历做好准备
		remoteIp = str[0];
		remotePort = atoi(str[1].c_str());
		remoteSuc = atoi(str[2].c_str());
	}
}

/*根据ip和port来寻找suc*/
string Join::findSuc(string ip, int port)
{
	CSocket socket;
	socket.Connect(ip.c_str(),port);//连接服务器
	string cmd = "yoursuc";
	socket.WriteLine(cmd);
	//读取查询结果
	string result = socket.ReadLine();
	theApp.scout<<result<<endl;
	return result;
}

/*寻找自身的suc*/
string Join::findSuc(int localId)
{
	theApp.scout<<"+++++++++in findSuc++++++"<<endl;
	string preString = findPre(localId);
	vector<string> k = Tool::Split(preString," ");
	string preIp = k[0];
	int port = atoi(k[1].c_str());
	int pre = atoi(k[2].c_str());
	/* 前继算法保证了新节点必定处于前继和前继的后继之间，所以直接返回前继的后继
	 * 但是此时前继的后继没有更新,需要在updateNeighbor中进行设置
	*/
	return findSuc(preIp,port);
}

/*在要连接的节点的后继节点链表中，找出离新节点最近且是新节点的前继的节点*/
string Join::findClosestPrecedingFinger(int id, string remoteIp, int remotePort)
{
	stringstream ss;
	ss<<id;
	string cmd = "closestprecedingfinger " + ss.str();
	CSocket socket;
	socket.Connect(remoteIp.c_str(),remotePort);
	socket.WriteLine(cmd);
	//读取查询结果
	string result = socket.ReadLine();
	theApp.scout<<result<<endl;
	return result;
}

/*初始化FingerTable,更新新加入节点的前继，后继，后继列表，以及前继的前继、后继的后继*/
void Join::init_finger_table()
{
	string preString=findPre(peer->getId());//首先找到新节点的前继
	vector<string> preS = Tool::Split(preString," ");
	string preIp = preS[0];
	int prePort = atoi(preS[1].c_str());
	int pre = atoi(preS[2].c_str());

	string sucString=findSuc(peer->getId());//然后找到新节点的后继
	vector<string> sucS = Tool::Split(sucString," ");
	string sucIp = sucS[0];
	int sucPort = atoi(sucS[1].c_str());
	int suc = atoi(sucS[2].c_str());

	theApp.scout<<"preString:"+preString<<endl;
	theApp.scout<<"sucString:"+sucString<<endl;

	//直接设置新节点的fingerTable
	peer->fingerTable.sucId = suc;
	peer->fingerTable.sucIP = sucIp;
	peer->fingerTable.sucPort = sucPort;
			
	peer->fingerTable.preIP = preIp;
	peer->fingerTable.prePort = prePort;
	peer->fingerTable.preId = pre;

	//后继列表中第一个（即直接后继）也同步更新
	peer->fingerTable.sucTable[0] = suc;
	stringstream ss;ss<<sucPort;
	peer->fingerTable.ipTable[0] = (sucIp+" "+ss.str());
	//更新后继列表中的其他节点
	for(int i=1;i<Config::TABLE_SIZE;i++){
		theApp.scout<<"++++++in for +++++  "<<i<<endl;
		sucString = findSuc(((int)(peer->getId()+pow(2., i))%Config::NODE_SUM));
		sucS = Tool::Split(sucString," ");
		sucIp = sucS[0];
		sucPort = atoi(sucS[1].c_str());
		suc = atoi(sucS[2].c_str());
				
		int k = ((int)(peer->getId()+pow(2., i))%Config::NODE_SUM);
		//如果k大于等于前继而小于本身，则后继便是本身
		if (RequestHandle::inRange(k,pre,peer->getId(),true,false))
		{
			suc = peer->getId();
			sucIp = peer->fingerTable.ip;
			sucPort = peer->fingerTable.port;
		}
		peer->fingerTable.sucTable[i] = suc;
		stringstream tmpss;tmpss<<sucPort;
		peer->fingerTable.ipTable[i] = (sucIp+" "+tmpss.str());
	}
	//更新前继的前继和后继的后继
	init_suc_suc_pre_pre();
}

/* 更新新加入节点的前继的前继和后继的后继
 * 通过向前继节点发出yourpre命令找出前继的前继，向后继节点发出yoursuc命令找出后继的后继
 */
void Join::init_suc_suc_pre_pre()
{
	//后继的后继
	string cmd = "yoursuc";
	CSocket socket;
	socket.Connect(peer->fingerTable.sucIP.c_str(),peer->fingerTable.sucPort);
	socket.WriteLine(cmd);
	string k = socket.ReadLine();
	vector<string> s = Tool::Split(k," ");
	peer->fingerTable.sucsucIP = s[0];
	peer->fingerTable.sucsucPort = atoi(s[1].c_str());
	peer->fingerTable.sucsucId = atoi(s[2].c_str());
	socket.Close();

	theApp.scout<<"@@@@@@@@@@@@@@@"<<endl;

	//前继的前继
	cmd = "yourpre";
	socket.Connect(peer->fingerTable.preIP.c_str(),peer->fingerTable.prePort);
	socket.WriteLine(cmd);
	k = socket.ReadLine();
	s = Tool::Split(k," ");
	peer->fingerTable.prepreIP = s[0];
	peer->fingerTable.preprePort = atoi(s[1].c_str());
	peer->fingerTable.prepreId = atoi(s[2].c_str());
	socket.Close();
}

/* 更新新加入节点的前继节点的后继和后继的后继，
 * 以及新加入节点的后继节点的前继和前继的前继
 */
void Join::update_neighbour()
{
	theApp.scout<<"++++update neighbour++++"<<endl;
	int suc = peer->fingerTable.sucId;
	string sucIp = peer->fingerTable.sucIP;
	int sucPort = peer->fingerTable.sucPort;
			
	int pre = peer->fingerTable.preId;
	string preIp = peer->fingerTable.preIP;
	int prePort = peer->fingerTable.prePort;

	//更新前继节点的后继和后继的后继
	stringstream ss1,ss2,ss3,ss4,ss5,ss6;
	ss1<<peer->fingerTable.port;ss2<<sucPort;ss3<<prePort;
	ss4<<peer->getId();ss5<<suc;ss6<<pre;
	string cmd = "newSuc " + peer->fingerTable.ip + " " + ss1.str() + " " + ss4.str() + " " + ss5.str() + " " + sucIp + " " + ss2.str();
	CSocket socket;
	socket.Connect(preIp.c_str(),prePort);
	socket.WriteLine(cmd);
	socket.Close();

	//更新后继节点的前继和前继的前继
	cmd = "newPre " + peer->fingerTable.ip + " " + ss1.str() + " " + ss4.str() + " " + ss6.str() + " " + preIp + " " + ss3.str();
	socket.Connect(sucIp.c_str(),sucPort);
	socket.WriteLine(cmd);
	socket.Close();

	//更新前继的前继和后继的后继，他们只需要部分字段
	suc_suc_pre_pre();
}

/* 更新环上每一个节点的FingerTable中的后继列表
*/
void Join::update_others()
{
	theApp.scout<<"++++update others++++"<<endl;
	int localId = peer->getId();
	string localIp = peer->fingerTable.ip;
	int localport = peer->fingerTable.port;
			
	int suc = peer->fingerTable.sucId;
	string sucIp = peer->fingerTable.sucIP;
	int sucPort = peer->fingerTable.sucPort;
	
	stringstream ss,ss1;ss<<localport;ss1<<localId;
	string cmd = "new_node " + localIp + " " + ss.str() + " " + ss1.str();
	CSocket socket;
	socket.Connect(sucIp.c_str(),sucPort);
	socket.WriteLine(cmd);
	socket.Close();
}

/*
 * 新节点加入拓扑时，需要把本属于它的key的hash从别的节点上转移过来
 */
void Join::transfer_keys()
{
	theApp.scout<<"++++ In the transfer key++++"<<endl;
	int sucId = peer->fingerTable.sucId;
	string sucIp = peer->fingerTable.sucIP;
	int sucPort = peer->fingerTable.sucPort;
	stringstream ss1,ss2,ss3,ss4;ss1<<peer->fingerTable.port;ss2<<peer->getId();ss3<<peer->fingerTable.preId;
	string cmd = "transfer_key " + peer->fingerTable.ip + " " + ss1.str() + " " + ss2.str() + " " + ss3.str();
	if (sucId == peer->getId())
		return;
	CSocket socket;
	socket.Connect(peer->fingerTable.sucIP.c_str(),peer->fingerTable.sucPort);
	socket.WriteLine(cmd);
	socket.Close();
}

/*更新前继的前继和后继的后继*/
void Join::suc_suc_pre_pre()
{
	CSocket socket;
	socket.Connect(peer->fingerTable.sucsucIP.c_str(),peer->fingerTable.sucsucPort);
	string cmd = "set_your_pre_pre ";
	stringstream ss,ss1;ss<<peer->getId();ss1<<peer->getPort();
	cmd += (ss.str() + " " + peer->getLocalIp() + " " + ss1.str());
	socket.WriteLine(cmd);
	socket.Close();

	socket.Connect(peer->fingerTable.prepreIP.c_str(),peer->fingerTable.preprePort);
	cmd = "set_your_suc_suc ";
	cmd += (ss.str() + " " + peer->getLocalIp() + " " + ss1.str());
	socket.WriteLine(cmd);
	socket.Close();
}

Join::~Join(void)
{
}
