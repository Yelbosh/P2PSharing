#include "StdAfx.h"
#include<exception>
#include "FingerTable.h"
#include "Peer.h"
#include<math.h>
#include<sstream>


FingerTable::FingerTable(void)
{
}

FingerTable::FingerTable(int identifier, int tableSize){
		this->identifier=identifier;
		this->tableSize=tableSize;
		sucTable.clear();
		ipTable.clear();
		port=Config::PORT_BASE+identifier;
		ip=Peer::getLocalIp();
		keyList.clear();
		init();
}

string FingerTable::getIp(int i)
{
	return this->ipTable[i];//获取第i个后继节点的ip地址和端口
}

int FingerTable::getSucTableElement(int i)
{
	return this->sucTable[i];//获取第i个后继节点的node的id
}

/**
*初始化FingerTable
*/
void FingerTable::init()
{
	for (int i=0; i<tableSize; i++)  //init finger table
	{	
		sucTable.push_back(0);
		ipTable.push_back(" ");
	}
	if(identifier == 0)//node 0必须作为该网络拓扑中的第一个node出现，以下为对其初始化部分
	{
		for (int i=0; i<tableSize; i++){
			stringstream ss;
			ss<<port;
			ipTable[i] = ip + " " + ss.str();
		}
		sucId=0;
		preId=0;
		prepreId=0;
		sucsucId=0;
			
		sucIP=ip;
		preIP=ip;
		sucsucIP=ip;
		prepreIP=ip;
			
		sucsucPort=Peer::DEFAULT_DEST_PORT;
		preprePort=Peer::DEFAULT_DEST_PORT;
		sucPort=Peer::DEFAULT_DEST_PORT;
		prePort=Peer::DEFAULT_DEST_PORT;

		for (int i=0; i<Config::NODE_SUM; i++)// 所有的文件刚开始都存放在Node 0中
		{	 
			stringstream ss;
			ss<<i;
			vector<string> tmpvec;
			stringstream tmpss;tmpss<<port;
			tmpvec.push_back(ip + " " + tmpss.str());
			keyList[i] = tmpvec;
		}
	}
	else
	{
		sucId=-1;
		preId=-1;
	}
}

/**
*获得前继节点Id
*/
int FingerTable::getPreId()
{
	return this->preId;
}

/**
*获得后继节点Id
*/
int FingerTable::getSuccessorId()
{
	return this->sucId;
}

/**
*将FingerTable按格式打印
*/
string FingerTable::display()
{
	int k=0;
	string result = "";
	stringstream ss1;
	ss1<<this->identifier;
	result += (ss1.str()+"'s fingerTable\r\n");
	stringstream ss2;
	ss2<<sucId;
	result += ("successor: "+ss2.str());
	result += (" "+sucIP+" ");
	stringstream ss3,ss4;
	ss3<<sucPort;ss4<<preId;
	result += (ss3.str()+" predecessor: "+ss4.str());
	result += (" "+preIP+" ");
	stringstream ss5;
	ss5<<prePort;
	result += (ss5.str()+ "\n");
	//print the sucsuc and the prepre
	stringstream pp2;
	pp2<<sucsucId;
	result += ("sucsuccessor: "+pp2.str());
	result += (" "+sucIP+" ");
	stringstream pp3,pp4;
	pp3<<sucsucPort;pp4<<prepreId;
	result += (pp3.str()+" prepredecessor: "+pp4.str());
	result += (" "+prepreIP+" ");
	stringstream pp5;
	pp5<<preprePort;
	result += (pp5.str()+ "\n");
	//print the suc list
	for (int i=0; i<tableSize; i++){
		stringstream ss6,ss7,ss8,ss9;
		ss6<<i;ss7<<((int)(identifier+pow(2., i))%Config::NODE_SUM);ss8<<((int)(identifier+pow(2., i+1))%Config::NODE_SUM);ss9<<sucTable[i];
		result += (ss6.str()+"  from ");
		result += (ss7.str()+" to ");
		result += (ss8.str()+"  "+ss9.str());
		result += ("  "+ipTable[i]);
		result += "\n";
	}
	result += ("key list: \n");
	map<int,vector<string>>::iterator it;
	int i = 0;
    for(it=keyList.begin();it!=keyList.end();++it)
	{
		int key = it->first;
		vector<string> value = it->second;
		stringstream ss10;
		ss10<<key;
		result += (ss10.str() + " : ");
		for(int j=0;j<value.size();j++)
		{
			result += value[j];
			if(j != value.size() - 1)
				result += "#";
		}
		if(i%2 == 0)
			result += "\t";
		else
			result += "\n";
		i++;
	}
    return result;
}

//更新updateKeyList
void FingerTable::updateKeyList(int key,string item)
{
	map<int,vector<string>>::iterator it;
	it = keyList.find(key);
    if(it == keyList.end())
    {
	 	return;
    }
    else
    {
		vector<string>* vec = &(it->second);
		for(int i=0;i<vec->size();i++)//查看是否含有
		{
			if((*vec)[i] == item)
				return;
		}
		vec->push_back(item);
    }
}

FingerTable::~FingerTable(void)
{
}
