#include "StdAfx.h"
#include "Leave.h"
#include <sstream>

using namespace std;

Leave::Leave(void)
{
}

Leave::Leave(Peer* peer)
{
	this->peer = peer;
}

/*离开网络的入口函数*/
void Leave::start_leave()
{
	leave_transfer();
	send_leave_msg();
	tell_neighbor();
}

/*将属于自己的key的hash转移至后继节点*/
void Leave::leave_transfer()
{
	int suc_id = peer->fingerTable.sucId;
	string suc_ip = peer->fingerTable.sucIP;
	int suc_port = peer->fingerTable.sucPort;
	map<int,vector<string>>::iterator it;
	for(it=peer->fingerTable.keyList.begin();it!=peer->fingerTable.keyList.end();++it)
	{
		int key = it->first;
		vector<string> value = it->second;
		CSocket socket;
		socket.Connect(suc_ip.c_str(),suc_port);
		string cmd = "give_you_data_item ";
		stringstream ss;ss<<key;
		cmd += (ss.str() + "#");
		for(int i=0;i<value.size();i++)
		{
			cmd += value[i];
			if(i != value.size() - 1)
				cmd += "-";
		}
		socket.WriteLine(cmd);
		socket.Close();
	}
}


/*将自己离开网络的消息沿环传送，使得每个节点更新自己的FingerTable*/
void Leave::send_leave_msg()
{
	int leave_id = peer->getId();
	string suc_ip = peer->fingerTable.sucIP;
	int suc_port = peer->fingerTable.sucPort;
	CSocket socket;
	socket.Connect(suc_ip.c_str(),suc_port);
	string cmd = "le ";
	stringstream ss,ss1,ss2,ss3;ss<<leave_id;ss1<<peer->fingerTable.sucPort;ss2<<peer->fingerTable.sucId;ss3<<Peer::TTL;
	cmd += (ss.str() + " " + peer->fingerTable.sucIP + " " + ss1.str() + " " + ss2.str() + " " + ss3.str());
	socket.WriteLine(cmd);
	socket.Close();
}

/*告知邻居节点自己已离开网络拓扑，需要它们更新FingerTable中的信息*/
void Leave::tell_neighbor()
{
	//告知自己的前继节点自己即将离开
	stringstream ss1,ss2,ss3,ss4,ss5;ss1<<peer->getId();ss2<<peer->fingerTable.sucId;ss3<<peer->fingerTable.sucPort;ss4<<peer->fingerTable.sucsucId;ss5<<peer->fingerTable.sucsucPort;
	string cmd_to_pre = "your_suc_le " + ss1.str() + " " + ss2.str() + " " + peer->fingerTable.sucIP + " " + ss3.str() + " " + ss4.str() + " " + peer->fingerTable.sucsucIP + " " + ss5.str();
	CSocket pre_socket;
	pre_socket.Connect(peer->fingerTable.preIP.c_str(),peer->fingerTable.prePort);
	pre_socket.WriteLine(cmd_to_pre);
	pre_socket.Close();

	//告知自己的后继节点自己即将离开
	stringstream pss1,pss2,pss3,pss4,pss5;pss1<<peer->getId();pss2<<peer->fingerTable.preId;pss3<<peer->fingerTable.prePort;pss4<<peer->fingerTable.prepreId;pss5<<peer->fingerTable.preprePort;
	string cmd_to_suc = "your_pre_le " + pss1.str() + " " + pss2.str() + " " + peer->fingerTable.preIP + " " + pss3.str() + " " + ss4.str() + " " + peer->fingerTable.prepreIP + " " + pss5.str();
	CSocket suc_socket;
	suc_socket.Connect(peer->fingerTable.sucIP.c_str(),peer->fingerTable.sucPort);
	suc_socket.WriteLine(cmd_to_suc);
	suc_socket.Close();

	//告知自己的前继的前继自己即将离开
	string cmd = "set_your_suc_suc " + ss2.str() + " " + peer->fingerTable.sucIP + " " + ss3.str();
	CSocket prepre_socket;
	prepre_socket.Connect(peer->fingerTable.prepreIP.c_str(),peer->fingerTable.preprePort);
	prepre_socket.WriteLine(cmd);
	prepre_socket.Close();

	//告知自己的后继的后继自己即将离开
	cmd = "set_your_pre_pre " + pss2.str() + " " + peer->fingerTable.preIP + " " + pss3.str();
	CSocket sucsuc_socket;
	sucsuc_socket.Connect(peer->fingerTable.sucsucIP.c_str(),peer->fingerTable.sucsucPort);
	sucsuc_socket.WriteLine(cmd);
	sucsuc_socket.Close();
}

Leave::~Leave(void)
{
}
