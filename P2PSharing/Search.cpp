#include "StdAfx.h"
#include "Search.h"
#include "Tool.h"
#include<math.h>
#include "Sock.h"
#include "RequestHandle.h"
#include <sstream>
#include "P2PSharing.h"

using namespace SockUtil;
using namespace std;

Search::Search(void)
{
}

Search::Search(Peer* peer,int searchId)
{
	this->peer = peer;
	this->searchId = searchId;
}

/*查找的入口函数*/
void Search::startSearch(int get)
{
	theApp.scout<<"++++In the start search++++"<<endl;
	map<int, vector<string>>::iterator iter;
	iter = peer->fingerTable.keyList.find(searchId);
	if (iter != peer->fingerTable.keyList.end())//如果在本地找到
	{
		theApp.scout<<"the data hash is local"<<endl;
		//socket 连接自身会出现异常
		//searchNext(peer->fingerTable.ip,peer->fingerTable.port,peer->fingerTable.ip,peer->fingerTable.port, searchId,Peer::TTL,get);
		//直接发送传送命令
		fileLocalTrans(peer->fingerTable.ip,peer->fingerTable.port, peer->getId(),searchId);
		return ;
	}
	//查看suc列表
	for (int i=0; i<Config::TABLE_SIZE; i++){
		int low = ((int)(peer->getId() + pow(2., i))%Config::NODE_SUM);
		int high = ((int)(peer->getId()+pow(2., i+1))%Config::NODE_SUM);
		if (RequestHandle::inRange(searchId, low, high, false, true))
		{   
			vector<string> p = Tool::Split(peer->fingerTable.getIp(i)," ");
			string nextIp = p[0];
			int nextPort = atoi(p[1].c_str());
			
			//查找的连接
			searchNext(nextIp,nextPort,peer->fingerTable.ip,peer->fingerTable.port, searchId, Peer::TTL,get);
			return;
		}
	}
}

/*查找的连接函数*/
void Search::searchNext(string nextIp,int nextPort,string localip, int localport, int localid, int ttl, int get)
{
	CSocket socket;
	socket.Connect(nextIp.c_str(),nextPort);
	stringstream ss,ss1,ss2,ss3;ss<<searchId;ss1<<localport;ss2<<ttl;ss3<<get;
	string new_cmd = "search " + ss.str() + " " + localip + " " + ss1.str() + " " + ss2.str() + " " + ss3.str(); 
	socket.WriteLine(new_cmd);
	socket.Close();
}

/*直接根据本地routing信息进行传送*/
void Search::fileLocalTrans(string hash_ip,int hash_port,int hash_id,int key)
{
	stringstream ss;ss<<key;
	string addrs = "";
	map<int, vector<string>>::iterator iter;
	iter = peer->fingerTable.keyList.find(key);
	if(iter != peer->fingerTable.keyList.end())
	{
		vector<string> vec = iter->second;
		for(int i=0;i<vec.size();i++){
			addrs += vec[i];//构造字符串
			if(i != vec.size() - 1)
				addrs += "-";
		}
	}
	//根据地址信息发送传送邀请
	string substr = peer->getLocalIp();stringstream subss;subss<<peer->getPort();substr += (" " + subss.str());
	if(addrs.find(substr) != -1){//本地资源中包含搜索资源
		theApp.scout<<"the data is local"<<endl;
		AfxMessageBox(_T("the data is local!"));
		return;
	}
	if(addrs != "")
	{
		vector<string> vec = Tool::Split(addrs,"-");
		//获取文件信息
		vector<string> addr0 = Tool::Split(vec[0]," ");
		string ip0 = addr0[0];
		int port = atoi(addr0[1].c_str());
		CSocket tmpSocket;
		tmpSocket.Connect(ip0.c_str(),port);
		string cmdinfo = "resourceinfo ";stringstream sss;sss<<key;cmdinfo += sss.str();
		tmpSocket.WriteLine(cmdinfo);
		string info = tmpSocket.ReadLine();
		tmpSocket.Close();
		int length = atoi(info.c_str());
		//改变app中的变量
		theApp.SetLength(key,length);
		//分片算法
		vector<vector<string>> result = resourceSplit(vec,length);
		//分片传输的请求
		for(int i=0;i<result.size();i++)
		{
			vector<string> infos = result[i];
			vector<string> addr = Tool::Split(infos[0]," ");
			//获取IP和Port
			string tmpIp = addr[0];
			int tmpPort = atoi(addr[1].c_str());
			//获取地址开始处和长度
			int tmpStart = atoi(infos[1].c_str());
			int tmpLength = atoi(infos[2].c_str());
			CSocket tmpTranserSocket;
			tmpTranserSocket.Connect(tmpIp.c_str(),tmpPort);
			stringstream tmpss1,tmpss2,tmpss3,tmpss4,tmpss5;tmpss1<<Config::TRANS_PORT_BASE+peer->getId();tmpss2<<hash_port;tmpss3<<length;tmpss4<<tmpStart;tmpss5<<tmpLength;
			string tmpcmd = "transfer_part " + peer->fingerTable.ip + " " + tmpss1.str() + " " + ss.str() + " " + hash_ip + " " + tmpss2.str() + " " + tmpss3.str() + " " + tmpss4.str() + " " + tmpss5.str();
			tmpTranserSocket.WriteLine(tmpcmd);
			tmpTranserSocket.Close();
		}
	}

}

/*将一个文件资源进行分片，返回的是一个二维数组，子数组中存储的是：ip&port,startPos,Length*/
vector<vector<string>> Search::resourceSplit(vector<string> addrs,int length)
{
	vector<vector<string>> result;
	if(addrs.size() >= 1)
	{
		vector<string> vec;
		vec.push_back(addrs[0]);
		stringstream ss1,ss2;ss1<<0;ss2<<length;
		vec.push_back(ss1.str());
		vec.push_back(ss2.str());
		result.push_back(vec);
	}else
	{
		int left = length/(1024*2);
		int leftLen = left * 1024;
		int startPos2 = left * 1024;
		int rightLen = length - leftLen;
		//push left part
		vector<string> vec;
		vec.push_back(addrs[0]);
		stringstream ss1,ss2;ss1<<0;ss2<<leftLen;
		vec.push_back(ss1.str());
		vec.push_back(ss2.str());
		result.push_back(vec);
		//push right part
		vector<string> vec2;
		vec2.push_back(addrs[1]);
		stringstream ss3,ss4;ss3<<startPos2;ss4<<rightLen;
		vec2.push_back(ss3.str());
		vec2.push_back(ss4.str());
		result.push_back(vec2);
	}
	return result;
}

Search::~Search(void)
{
}
