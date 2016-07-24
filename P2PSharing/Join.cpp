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

/*�����������˵���ں���*/
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

/*����ip��port��Ѱ��pre*/
string Join::findPre(string ip, int port)
{
	CSocket socket;
	socket.Connect(ip.c_str(),port);//���ӷ�����
	string cmd = "yourpre";
	socket.WriteLine(cmd);
	//��ȡ��ѯ���
	string result = socket.ReadLine();
	theApp.scout<<result<<endl;
	return result;
}

/*Ѱ�������pre*/
string Join::findPre(int localId)
{
	theApp.scout<<"+++++++++in findPre++++++"<<endl;
	string remoteSucString=findSuc(dest_ip,dest_port);//�����ҵ��Լ�Ҫ���ӵĽڵ��ֱ�Ӻ�̽ڵ�
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
		if (RequestHandle::inRange(localId,remoteNodeId,remoteSuc,true,false))//����½ڵ��id��Ҫ���ӵĽڵ������ֱ�Ӻ��֮����ߵ���Ҫ���ӵĽڵ�id����Ҫ���ӵĽڵ��������ǰ��
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
		//������ڣ������Ѱ��
		theApp.scout<<localId<<" not in range from "<<remoteNodeId<<" to "<<remoteSuc<<endl;
		//��Ҫ���ӵĽڵ�ĺ���б����ҳ����½ڵ�id����Ľڵ㣬������Ҫ���ӵĽڵ㱾��
		string remoteNodeIdString=findClosestPrecedingFinger(localId,remoteIp,remotePort);
		vector<string> k = Tool::Split(remoteNodeIdString," ");
		remoteNodeIp = k[0];
		remoteNodePort = atoi(k[1].c_str());
		remoteNodeId = atoi(k[2].c_str());

		theApp.scout<<"next requestedNodeId "<<remoteNodeId<<endl;
		remoteSucString = findSuc(remoteIp,remotePort);//Ϊ��������׼��
		remoteIp = str[0];
		remotePort = atoi(str[1].c_str());
		remoteSuc = atoi(str[2].c_str());
	}
}

/*����ip��port��Ѱ��suc*/
string Join::findSuc(string ip, int port)
{
	CSocket socket;
	socket.Connect(ip.c_str(),port);//���ӷ�����
	string cmd = "yoursuc";
	socket.WriteLine(cmd);
	//��ȡ��ѯ���
	string result = socket.ReadLine();
	theApp.scout<<result<<endl;
	return result;
}

/*Ѱ�������suc*/
string Join::findSuc(int localId)
{
	theApp.scout<<"+++++++++in findSuc++++++"<<endl;
	string preString = findPre(localId);
	vector<string> k = Tool::Split(preString," ");
	string preIp = k[0];
	int port = atoi(k[1].c_str());
	int pre = atoi(k[2].c_str());
	/* ǰ���㷨��֤���½ڵ�ض�����ǰ�̺�ǰ�̵ĺ��֮�䣬����ֱ�ӷ���ǰ�̵ĺ��
	 * ���Ǵ�ʱǰ�̵ĺ��û�и���,��Ҫ��updateNeighbor�н�������
	*/
	return findSuc(preIp,port);
}

/*��Ҫ���ӵĽڵ�ĺ�̽ڵ������У��ҳ����½ڵ���������½ڵ��ǰ�̵Ľڵ�*/
string Join::findClosestPrecedingFinger(int id, string remoteIp, int remotePort)
{
	stringstream ss;
	ss<<id;
	string cmd = "closestprecedingfinger " + ss.str();
	CSocket socket;
	socket.Connect(remoteIp.c_str(),remotePort);
	socket.WriteLine(cmd);
	//��ȡ��ѯ���
	string result = socket.ReadLine();
	theApp.scout<<result<<endl;
	return result;
}

/*��ʼ��FingerTable,�����¼���ڵ��ǰ�̣���̣�����б��Լ�ǰ�̵�ǰ�̡���̵ĺ��*/
void Join::init_finger_table()
{
	string preString=findPre(peer->getId());//�����ҵ��½ڵ��ǰ��
	vector<string> preS = Tool::Split(preString," ");
	string preIp = preS[0];
	int prePort = atoi(preS[1].c_str());
	int pre = atoi(preS[2].c_str());

	string sucString=findSuc(peer->getId());//Ȼ���ҵ��½ڵ�ĺ��
	vector<string> sucS = Tool::Split(sucString," ");
	string sucIp = sucS[0];
	int sucPort = atoi(sucS[1].c_str());
	int suc = atoi(sucS[2].c_str());

	theApp.scout<<"preString:"+preString<<endl;
	theApp.scout<<"sucString:"+sucString<<endl;

	//ֱ�������½ڵ��fingerTable
	peer->fingerTable.sucId = suc;
	peer->fingerTable.sucIP = sucIp;
	peer->fingerTable.sucPort = sucPort;
			
	peer->fingerTable.preIP = preIp;
	peer->fingerTable.prePort = prePort;
	peer->fingerTable.preId = pre;

	//����б��е�һ������ֱ�Ӻ�̣�Ҳͬ������
	peer->fingerTable.sucTable[0] = suc;
	stringstream ss;ss<<sucPort;
	peer->fingerTable.ipTable[0] = (sucIp+" "+ss.str());
	//���º���б��е������ڵ�
	for(int i=1;i<Config::TABLE_SIZE;i++){
		theApp.scout<<"++++++in for +++++  "<<i<<endl;
		sucString = findSuc(((int)(peer->getId()+pow(2., i))%Config::NODE_SUM));
		sucS = Tool::Split(sucString," ");
		sucIp = sucS[0];
		sucPort = atoi(sucS[1].c_str());
		suc = atoi(sucS[2].c_str());
				
		int k = ((int)(peer->getId()+pow(2., i))%Config::NODE_SUM);
		//���k���ڵ���ǰ�̶�С�ڱ������̱��Ǳ���
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
	//����ǰ�̵�ǰ�̺ͺ�̵ĺ��
	init_suc_suc_pre_pre();
}

/* �����¼���ڵ��ǰ�̵�ǰ�̺ͺ�̵ĺ��
 * ͨ����ǰ�̽ڵ㷢��yourpre�����ҳ�ǰ�̵�ǰ�̣����̽ڵ㷢��yoursuc�����ҳ���̵ĺ��
 */
void Join::init_suc_suc_pre_pre()
{
	//��̵ĺ��
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

	//ǰ�̵�ǰ��
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

/* �����¼���ڵ��ǰ�̽ڵ�ĺ�̺ͺ�̵ĺ�̣�
 * �Լ��¼���ڵ�ĺ�̽ڵ��ǰ�̺�ǰ�̵�ǰ��
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

	//����ǰ�̽ڵ�ĺ�̺ͺ�̵ĺ��
	stringstream ss1,ss2,ss3,ss4,ss5,ss6;
	ss1<<peer->fingerTable.port;ss2<<sucPort;ss3<<prePort;
	ss4<<peer->getId();ss5<<suc;ss6<<pre;
	string cmd = "newSuc " + peer->fingerTable.ip + " " + ss1.str() + " " + ss4.str() + " " + ss5.str() + " " + sucIp + " " + ss2.str();
	CSocket socket;
	socket.Connect(preIp.c_str(),prePort);
	socket.WriteLine(cmd);
	socket.Close();

	//���º�̽ڵ��ǰ�̺�ǰ�̵�ǰ��
	cmd = "newPre " + peer->fingerTable.ip + " " + ss1.str() + " " + ss4.str() + " " + ss6.str() + " " + preIp + " " + ss3.str();
	socket.Connect(sucIp.c_str(),sucPort);
	socket.WriteLine(cmd);
	socket.Close();

	//����ǰ�̵�ǰ�̺ͺ�̵ĺ�̣�����ֻ��Ҫ�����ֶ�
	suc_suc_pre_pre();
}

/* ���»���ÿһ���ڵ��FingerTable�еĺ���б�
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
 * �½ڵ��������ʱ����Ҫ�ѱ���������key��hash�ӱ�Ľڵ���ת�ƹ���
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

/*����ǰ�̵�ǰ�̺ͺ�̵ĺ��*/
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
