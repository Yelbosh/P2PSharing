#include "StdAfx.h"
#include "RequestHandle.h"
#include<string>
#include "SendHandle.h"
#include "Tool.h"
#include <sstream>
#include "P2PSharing.h"


using namespace std;


RequestHandle::RequestHandle(void)
{
}

RequestHandle::RequestHandle(CSocket* socket, Peer* peer)
{
	this->socket = socket;
	this->peer = peer;
}

void RequestHandle::run()
{
	string cmd_rec;
	try
	{
		cmd_rec = socket->ReadLine();
	}catch(CSocketException)
	{
		theApp.scout<<"Receive command error !"<<endl;
		return;
	}
	//if cmd is null, just return
	if(cmd_rec.empty())
		return;
	//display the command text
	if (!Tool::Startwith(cmd_rec,"ping"))
	    theApp.scout<<"rec_cmd is " + cmd_rec<<endl;
	vector<string> str = Tool::Split(cmd_rec," ");
	//execute some commands according to the command head
	if(!strcmp(str[0].c_str(),"yoursuc"))//��ѯֱ�Ӻ�̽ڵ�
	{
		string cmd_to_send;
		cmd_to_send += this->peer->fingerTable.sucIP;
		cmd_to_send += " ";
		stringstream ss1,ss2;ss1<<this->peer->fingerTable.sucPort;ss2<<this->peer->fingerTable.sucId;
		cmd_to_send += ss1.str();
		cmd_to_send += " ";
		cmd_to_send += ss2.str();
		this->socket->WriteLine(cmd_to_send);
	}
	if(!strcmp(str[0].c_str(),"yoursucsuc"))//��ѯ��̺�̽ڵ�
	{
		string cmd_to_send;
		cmd_to_send += this->peer->fingerTable.sucsucIP;
		cmd_to_send += " ";
		stringstream ss1,ss2;ss1<<this->peer->fingerTable.sucsucPort;ss2<<this->peer->fingerTable.sucsucId;
		cmd_to_send += ss1.str();
		cmd_to_send += " ";
		cmd_to_send += ss2.str();
		this->socket->WriteLine(cmd_to_send);
	}
	else if(!strcmp(str[0].c_str(),"yourpre"))//��ѯֱ��ǰ�̽ڵ�
	{
		string cmd_to_send;
		cmd_to_send += this->peer->fingerTable.preIP;
		cmd_to_send += " ";
		stringstream ss1,ss2;ss1<<this->peer->fingerTable.prePort;ss2<<this->peer->fingerTable.preId;
		cmd_to_send += ss1.str();
		cmd_to_send += " ";
		cmd_to_send += ss2.str();
		this->socket->WriteLine(cmd_to_send);
	}
	else if(!strcmp(str[0].c_str(),"yourprepre"))//��ѯǰ��ǰ�̽ڵ�
	{
		string cmd_to_send;
		cmd_to_send += this->peer->fingerTable.prepreIP;
		cmd_to_send += " ";
		stringstream ss1,ss2;ss1<<this->peer->fingerTable.preprePort;ss2<<this->peer->fingerTable.prepreId;
		cmd_to_send += ss1.str();
		cmd_to_send += " ";
		cmd_to_send += ss2.str();
		this->socket->WriteLine(cmd_to_send);
	}
	else if(!strcmp(str[0].c_str(),"closestprecedingfinger"))//�ڱ��ؽڵ�ĺ���б��У���ѯ�����id�����ǰ�̽ڵ�
	{
		int id = atoi(str[1].c_str());
		string kstring = get_closest_preceding_finger(id);
		this->socket->WriteLine(kstring);
	}
	else if(!strcmp(str[0].c_str(),"newSuc"))//�����¼���ڵ��ǰ�̽ڵ�ĺ����Ϣ
	{
		int new_sucid = atoi(str[3].c_str());
	    int new_sucport = atoi(str[2].c_str());
	    string new_sucIp = str[1];
	    updateSuc(new_sucid,new_sucIp,new_sucport);
	    	
		int suc_suc = atoi(str[4].c_str());
	    string suc_suc_ip = str[5];
	    int suc_suc_port = atoi(str[6].c_str());
	    	
	    updateSucSuc(suc_suc,suc_suc_ip,suc_suc_port);
	}
	else if(!strcmp(str[0].c_str(),"newPre"))//�����¼���ڵ�ĺ�̽ڵ��ǰ����Ϣ
	{
		int new_preid = atoi(str[3].c_str());
	    int new_preport = atoi(str[2].c_str());
	    string new_preIp = str[1];
		updatePre(new_preid,new_preIp,new_preport);
		    
		int pre_pre = atoi(str[4].c_str());
		string pre_pre_ip = str[5];
		int pre_pre_port = atoi(str[6].c_str());
		updatePrePre(pre_pre,pre_pre_ip,pre_pre_port);
	}
	else if(!strcmp(str[0].c_str(),"set_your_suc_suc"))//�����Լ���̽ڵ�ĺ��
	{
		int new_suc_suc_id = atoi(str[1].c_str());
		string new_suc_suc_ip = str[2];
		int new_suc_suc_port = atoi(str[3].c_str());

		updateSucSuc(new_suc_suc_id,new_suc_suc_ip,new_suc_suc_port);
	}
	else if(!strcmp(str[0].c_str(),"set_your_pre_pre"))//�����Լ�ǰ�̽ڵ��ǰ��
	{
		int new_pre_pre_id = atoi(str[1].c_str());
		string new_pre_pre_ip = str[2];
		int new_pre_pre_port = atoi(str[3].c_str());

		updatePrePre(new_pre_pre_id,new_pre_pre_ip,new_pre_pre_port);
	}
	else if(!strcmp(str[0].c_str(),"new_node"))//�½ڵ�������磬�����������˽ṹ
	{
		int new_id = atoi(str[3].c_str());
	    string new_ip = str[1];
	    int new_port = atoi(str[2].c_str());
	    try {
			new_node_come(new_id,new_ip,new_port);
		} catch (...) {
				theApp.scout<<"exception occured during update others"<<endl;
		}
	}
	else if(!strcmp(str[0].c_str(),"transfer_key"))//����Դ�Ĺ�ϣ���н���
	{
		string new_ip = str[1];
		int new_port = atoi(str[2].c_str());
	    int new_id = atoi(str[3].c_str());
	    int new_preid = atoi(str[4].c_str());
	    try {
			transfer_keys(new_ip,new_port,new_id,new_preid);
		} catch (...) {
			theApp.scout<<"exception occured during transfer_key others"<<endl;
		}
	}
	else if(!strcmp(str[0].c_str(),"give_you_data_item"))//��Դ������
	{
		vector<string> s = Tool::Split(cmd_rec,"#");
	    string value = s[1];
		vector<string> k = Tool::Split(s[0]," ");
	    int key = atoi(k[1].c_str());
	    receive_data_item(key, value);
	}
	else if(!strcmp(str[0].c_str(),"search"))//��Դ�Ĳ�ѯ����
	{
		int search_id = atoi(str[1].c_str());
	    string origin_ip = str[2];
		int origin_port = atoi(str[3].c_str());
		int ttl = atoi(str[4].c_str());
		int get = atoi(str[5].c_str());
	    try {
			search_data(search_id,origin_ip,origin_port,ttl,get);
		} catch (...) {
			theApp.scout<<"Exception occured during search"<<endl;
		}
	}
	else if(!strcmp(str[0].c_str(),"find"))//��Դ��hash���ҵ�
	{
		int result = atoi(str[1].c_str());
	    if (result == -1){
			theApp.scout<<"search result: data not in the ring"<<endl;
			return;
		}
		//��ȡӵ�д���Դhash�Ľڵ����Ϣ
		string hash_ip = str[2];
		int hash_port = atoi(str[3].c_str());
		int hash_id = atoi(str[4].c_str());
		int key = atoi(str[5].c_str());
		int get = atoi(str[6].c_str());
		if(get == 1)
			//��ȡӵ�д���Դ��ip�б��������ļ�����
			file_trans_request(hash_ip,hash_port,hash_id,key);
		else
		{
			CSocket socket;
			socket.Connect(hash_ip.c_str(),hash_port);
			stringstream ss;ss<<key;
			string cmd = "keyvalue " + ss.str();
			socket.WriteLine(cmd);
	
			//��ȡ����
			string addrs = socket.ReadLine();
			socket.Close();
			string substr = peer->getLocalIp();stringstream subss;subss<<peer->getPort();substr += (" " + subss.str());
			if(addrs.find(substr) != -1){//������Դ�а���������Դ
				theApp.scout<<"the data is local"<<endl;
				return;
			}
			if(addrs != "")
			{
				//��ַ�б�,������ʾ
				vector<string> vec = Tool::Split(addrs,"-");
				string alertStr = "the resource exists in the following nodes��\r\n";
				for(int i=0;i<vec.size();i++){
					alertStr += vec[i];
					alertStr += "\r\n";
				}
				theApp.scout<<alertStr<<endl;
			}
		}
			
	}
	else if(!strcmp(str[0].c_str(),"keyvalue"))//��ȡ��Ӧ��value
	{
		int key = atoi(str[1].c_str());
		string cmd = "";
		map<int, vector<string>>::iterator iter;
		iter = peer->fingerTable.keyList.find(key);
		if(iter != peer->fingerTable.keyList.end())
		{
			vector<string> vec = iter->second;
			for(int i=0;i<vec.size();i++){
				cmd += vec[i];//�����ַ���
				if(i != vec.size() - 1)
					cmd += "-";
			}
		}
		else
		{
			//do nothing
		}
		this->socket->WriteLine(cmd);
	}
	else if(!strcmp(str[0].c_str(),"update_keylist"))//����keyList
	{
		int key = atoi(str[1].c_str());
		string item = str[2] + " " + str[3];
		peer->fingerTable.updateKeyList(key,item);
	}
	else if(!strcmp(str[0].c_str(),"resourceinfo"))//��ȡ��Ӧ��value
	{
		string key = str[1];
		CString fileName = Tool::QueryExePath();fileName += "Share\\";fileName += key.c_str();fileName += ".pcm";
		CFile sendFile;
		sendFile.Abort();
		int length;
		sendFile.Open(fileName,CFile::modeRead | CFile::shareDenyNone);
		length = sendFile.GetLength();
		sendFile.Close();
		
		string cmd;
		stringstream ss;ss<<length;cmd = ss.str();
		this->socket->WriteLine(cmd);
	}
	else if(!strcmp(str[0].c_str(),"transfer_part"))//���Է����ͽ����ļ���Ƭ������
	{
		string ip = str[1];
		int port = atoi(str[2].c_str());
		string hash_ip = str[4];
		int hash_port = atoi(str[5].c_str());
		int key = atoi(str[3].c_str());
		int length = atoi(str[6].c_str());
		int startPos = atoi(str[7].c_str());
		int partLen = atoi(str[8].c_str());
		//start up the sending thread
		SendHandle* sendHandle = new SendHandle(ip,port,hash_ip,hash_port,key,length,startPos,partLen);
		sendHandle->start();
	}
	else if(!strcmp(str[0].c_str(),"le"))//�ڵ��뿪���������
	{
		int le_id = atoi(str[1].c_str());
	    string le_suc_ip = str[2];
		int le_suc_port = atoi(str[3].c_str());
		int le_suc_id = atoi(str[4].c_str());
		int ttl = atoi(str[5].c_str());
		try{
			rec_leave(le_suc_ip,le_suc_port,le_id,le_suc_id,ttl);
		}
		catch(...)
		{
			theApp.scout<<"Exception occured during leave"<<endl;
		}
	}
	else if(!strcmp(str[0].c_str(),"your_suc_le"))//��̽ڵ��뿪����,update the suc to sucsuc
	{
		int next_id = atoi(str[2].c_str());
		string next_ip = str[3];
		int next_port = atoi(str[4].c_str());
    		
		int next_next_id = atoi(str[5].c_str());
    	string next_next_ip = str[6];
		int next_next_port = atoi(str[7].c_str());
    		
    	updateSuc(next_id,next_ip,next_port,next_next_id, next_next_ip, next_next_port);
	}
	else if(!strcmp(str[0].c_str(),"your_pre_le"))//ǰ�̽ڵ��뿪����,update the pre to prepre
	{
		int next_id = atoi(str[2].c_str());
    	string next_ip = str[3];
		int next_port = atoi(str[4].c_str());
    		
		int next_next_id = atoi(str[5].c_str());
    	string next_next_ip = str[6];
		int next_next_port = atoi(str[7].c_str());

    	updatePre(next_id,next_ip,next_port,next_next_id,next_next_ip,next_next_port);
	}
	else if(!strcmp(str[0].c_str(),"your_suc_suc_le"))//��̵ĺ�̽ڵ��뿪����
	{
		int next_id = atoi(str[2].c_str());
	    string next_ip = str[3];
		int next_port = atoi(str[4].c_str());
	    updateSucSuc(next_id,next_ip,next_port);
	}
	else if(!strcmp(str[0].c_str(),"your_pre_pre_le"))//ǰ�̵�ǰ�̽ڵ��뿪����
	{
		int next_id = atoi(str[2].c_str());
	    string next_ip = str[3];
		int next_port = atoi(str[4].c_str());
	    updatePrePre(next_id,next_ip,next_port);
	}
	else if(!strcmp(str[0].c_str(),"ping"))//���ڵ��Ƿ�����������Ϣ pong
	{
		socket->WriteLine("pong");
	}
	else if(!strcmp(str[0].c_str(),""))
	{
		//do nothing
	}
}

/*01 �ڱ��ؽڵ�ĺ���б��У���ѯ�����id�����ǰ�̽ڵ� */
string RequestHandle::get_closest_preceding_finger(int id)
{
	for (int i=Config::TABLE_SIZE-1; i>=0; i--){
		int node=peer->fingerTable.getSucTableElement(i);
		if (inRange(node,peer->getId(),id,true,true))//���ؽڵ��̴Ӻ���ǰ���Ӵ�С�����������к��idС�ڸ���id�����Ϊ����ڵ�
		{
			string result = peer->fingerTable.getIp(i) + " ";
			stringstream ss;
			ss<<node;
			result += ss.str();
			return result;
		}
	}
	//���û�У��㷵�ر��ؽڵ�
	string result = peer->fingerTable.ip + " ";
	stringstream ss,ss1;
	ss<<peer->fingerTable.port;ss1<<peer->fingerTable.identifier;
	result += ss.str();result += " ";result += ss1.str();
	return result;
}

//update suc's suc
void RequestHandle::updateSucSuc(int new_sucid,string new_sucip,int new_sucport)
{
	peer->fingerTable.sucsucId=new_sucid;
	peer->fingerTable.sucsucPort=new_sucport;
	peer->fingerTable.sucsucIP=new_sucip;
}

//update pre's pre
void RequestHandle::updatePrePre(int new_id,string new_ip, int new_port){
	peer->fingerTable.prepreId=new_id;
	peer->fingerTable.prepreIP=new_ip;
	peer->fingerTable.preprePort=new_port;
}
	
//update suc
void RequestHandle::updateSuc(int new_sucid,string new_sucip,int new_sucport){
	peer->fingerTable.sucId=new_sucid;
	peer->fingerTable.sucPort=new_sucport;
	peer->fingerTable.sucIP=new_sucip;
}

//update suc and suc's suc
void RequestHandle::updateSuc(int new_sucid,string new_sucip,int new_sucport, int suc_suc_id, string suc_suc_ip, int suc_suc_port){
	peer->fingerTable.sucId=new_sucid;
	peer->fingerTable.sucPort=new_sucport;
	peer->fingerTable.sucIP=new_sucip;
		
	peer->fingerTable.sucsucId=suc_suc_id;
	peer->fingerTable.sucsucPort=suc_suc_port;
	peer->fingerTable.sucsucIP=suc_suc_ip;
}

//update pre
void RequestHandle::updatePre(int new_preid, string new_preip,int new_preport){
	peer->fingerTable.preId=new_preid;
	peer->fingerTable.prePort=new_preport;
	peer->fingerTable.preIP=new_preip;
}

//update pre's pre
void RequestHandle::updatePre(int new_preid, string new_preip,int new_preport, int pre_pre_id, string pre_pre_ip, int pre_pre_port){
	peer->fingerTable.preId=new_preid;
	peer->fingerTable.prePort=new_preport;
	peer->fingerTable.preIP=new_preip;
		
	peer->fingerTable.prepreId=pre_pre_id;
	peer->fingerTable.prepreIP=pre_pre_ip;
	peer->fingerTable.preprePort=pre_pre_port;
}

//���»���ÿһ���ڵ��fingerTable�еĺ���б�
void RequestHandle::new_node_come(int id, string ip, int port)
{
	int localid = peer->getId();
	if (id == localid)
		return;
	for (int i=0; i<Config::TABLE_SIZE; i++){
		int low = (int) (peer->getId()+pow(2., i))%Config::NODE_SUM;
		int finger = peer->fingerTable.getSucTableElement(i);
		theApp.scout<<"id: "<<id<<endl;
		theApp.scout<<"low: "<<low<<endl;
		theApp.scout<<"finger: "<<finger<<endl;
			
		int new_distance = id-low;
		if (new_distance < 0)
			new_distance += Config::NODE_SUM;
			
		int cur_distance=finger-low;
		if (cur_distance <0)
			cur_distance += Config::NODE_SUM;
			
		theApp.scout<<"++++new dis: "<<new_distance<<" ++++"<<endl;
		theApp.scout<<"++++cur dis: "<<cur_distance<<" ++++"<<endl;
		if (new_distance<cur_distance){
			peer->fingerTable.sucTable[i] = id;
			stringstream ss;ss<<port;
			peer->fingerTable.ipTable[i] = ip+" "+ss.str();
		}
	}
	stringstream tmp,tmp1;tmp<<port;tmp1<<id;
	string cmd = "new_node " + ip + " " + tmp.str() + " " + tmp1.str();
	CSocket socket;
	socket.Connect(peer->fingerTable.sucIP.c_str(),peer->fingerTable.sucPort);
	socket.WriteLine(cmd);
	socket.Close();
}

/*
 * ����Դ��id���н���
 */
void RequestHandle::transfer_keys(string new_ip, int new_port, int new_id, int new_pre)
{
	vector<map<int,vector<string>>::iterator> removedList;
	map<int,vector<string>>::iterator it;
	for(it=peer->fingerTable.keyList.begin();it!=peer->fingerTable.keyList.end();++it)
	{
		int key = it->first;
		vector<string> value = it->second;

		// if the key belongs to the new node
		if (inRange(key, new_pre, new_id,true, false)){
			transfer_data_item(new_ip, new_port, key,value );
			removedList.push_back(it);
		}
	}
	for (int i=0; i<removedList.size();i++){
		map<int,vector<string>>::iterator it = removedList[i];
		peer->fingerTable.keyList.erase(it);
	}
}

/*��Դhash�Ľ���*/
void RequestHandle::transfer_data_item(string new_ip, int new_port, int key, vector<string> value)
{
	CSocket socket;
	socket.Connect(new_ip.c_str(),new_port);
	stringstream ss;ss<<key;
	string cmd = "give_you_data_item " + ss.str() + "#";
	for(int i=0;i<value.size();i++)//����value����ip�ַ���
	{
		cmd += value[i];
		if(i != value.size() -1)
			cmd += "-";
	}
	socket.WriteLine(cmd);
	socket.Close();
}

/*���յ�key��hash*/
void RequestHandle::receive_data_item(int key, string value)
{
	vector<string> vec = Tool::Split(value,"-");
	peer->fingerTable.keyList.insert(pair<int,vector<string>>(key, vec));
}

/*�յ�ĳ�ڵ㼴���뿪���˵���Ϣ������FingerTable�ĸ��¼�����Ϣ�Ĵ���*/
void RequestHandle::rec_leave(string le_ip, int le_port, int le_id, int le_suc_id,int ttl)
{
	if (le_id == peer->getId())
		return;
	if(ttl < 0)
		return;
	//�������ڵ��У�����б���Ԫ��idΪ�뿪�ڵ�ĺ�̽ڵ�ȫ����Ϊ�뿪�ڵ�ĺ�̽ڵ�
	for (int i=0; i<peer->fingerTable.tableSize;i++){
		int finger_node = peer->fingerTable.getSucTableElement(i);
		if (finger_node==le_id){
			peer->fingerTable.sucTable[i] = le_suc_id;
			stringstream ss;ss<<le_port;
			peer->fingerTable.ipTable[i] = (le_ip+ " " + ss.str());
		}
	}
	CSocket socket;
	socket.Connect(peer->fingerTable.sucIP.c_str(),peer->fingerTable.sucPort);
	string cmd = "le ";
	stringstream ss,ss1,ss2,ss3;ss<<le_id;ss1<<le_port;ss2<<le_suc_id;ss3<<(ttl-1);
	cmd += (ss.str() + " " + le_ip + " " + ss1.str() + " " + ss2.str() + " " + ss3.str());
	socket.WriteLine(cmd);
	socket.Close();
}

/*�����ļ���Ϣ����*/
void RequestHandle::search_data(int searchid, string origin_ip, int origin_port, int ttl, int get)
{
	CSocket socket;
	socket.Connect(origin_ip.c_str(),origin_port);
	string new_cmd = "";
	if (ttl < 0)//����һȦû���ҵ�
	{
		stringstream ss;ss<<searchid;
		new_cmd = "find -1 " + ss.str();
		socket.WriteLine(new_cmd);
		socket.Close();
		return;
	}
	map<int, vector<string>>::iterator iter;
	iter = peer->fingerTable.keyList.find(searchid);
	if(iter != peer->fingerTable.keyList.end())//�ڱ��ڵ���Դ�б����ҵ�,ֻ��hash��������Դʵ�ʴ�ŵĵ�ַ
	{
		stringstream ss1,ss2,ss3,ss4;ss1<<peer->fingerTable.port;ss2<<searchid;ss3<<get;ss4<<peer->getId();
		new_cmd="find 0 " + peer->fingerTable.ip + " " + ss1.str() + " " + ss4.str() + " " + ss2.str() + " " + ss3.str();
		socket.WriteLine(new_cmd);
		socket.Close();
	}
	else{//forward the msg to search
		int low = peer->getId() + 1;
		int high = -1;
			
		for (int i=0; i<Config::TABLE_SIZE; i++){
			high=((int) (low+pow(2., i))%Config::NODE_SUM);
			if (RequestHandle::inRange(searchid, low, high, false, true))
			{   
				vector<string> p = Tool::Split(peer->fingerTable.getIp(i)," ");
				string nextIp = p[0];
				int nextPort = atoi(p[1].c_str());
				
				//send out search information

				theApp.scout<<searchid<<"in range from "<<low<<" to "<<high<<endl;
				theApp.scout<<"forward addr: "<<nextIp<<" "<<nextPort<<endl;
				searchNext(nextIp,nextPort,origin_ip, origin_port, searchid,ttl-1, get);
				return;
			}	
		}
	}
}

/*��ѯ���Ӻ���*/
void RequestHandle::searchNext(string next_ip,int next_port, string origin_ip, int origin_port, int searchid, int ttl, int get)
{
	CSocket socket;
	socket.Connect(next_ip.c_str(),next_port);
	stringstream ss1,ss2,ss3,ss4;ss1<<searchid;ss2<<origin_port;ss3<<ttl;ss4<<get;
	string new_cmd = "search " + ss1.str() + " " + origin_ip + " " + ss2.str() + " " + ss3.str() + " " + ss4.str(); 
	socket.WriteLine(new_cmd);
	socket.Close();
}

/*��ȡӵ�д���Դhash�Ľڵ����Ϣ�����Ұ�����Ƭ�㷨*/
void RequestHandle::file_trans_request(string hash_ip,int hash_port,int hash_id,int key)
{
	//��ȡ���ļ���owner
	CSocket socket;
	socket.Connect(hash_ip.c_str(),hash_port);
	stringstream ss;ss<<key;
	string cmd = "keyvalue " + ss.str();
	socket.WriteLine(cmd);
	
	//��ȡ����
	string addrs = socket.ReadLine();
	socket.Close();
	string substr = peer->getLocalIp();stringstream subss;subss<<peer->getPort();substr += (" " + subss.str());
	if(addrs.find(substr) != -1){//������Դ�а���������Դ
		theApp.scout<<"the data is local"<<endl;
		AfxMessageBox(_T("the data is local!"));
		return;
	}
	if(addrs != "")
	{
		//��ַ�б�,������ʾ
		vector<string> vec = Tool::Split(addrs,"-");
		/*CString alertStr = _T("the resource exists in the following nodes��\r\n");
		for(int i=0;i<vec.size();i++){
			alertStr += (vec[i].c_str());
			alertStr += _T("\r\n");
		}
		AfxMessageBox(alertStr);*/
		//��ȡ�ļ���Ϣ
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
		//�ı�app�еı���
		theApp.SetLength(key,length);
		//CString mmm = _T("");mmm+=info.c_str();
		//AfxMessageBox(mmm);
		//��Ƭ�㷨
		vector<vector<string>> result = resourceSplit(vec,length);
		//��Ƭ���������
		for(int i=0;i<result.size();i++)
		{
			vector<string> infos = result[i];
			vector<string> addr = Tool::Split(infos[0]," ");
			//��ȡIP��Port
			string tmpIp = addr[0];
			int tmpPort = atoi(addr[1].c_str());
			//��ȡ��ַ��ʼ���ͳ���
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

/*��һ���ļ���Դ���з�Ƭ�����ص���һ����ά���飬�������д洢���ǣ�ip&port,startPos,Length*/
vector<vector<string>> RequestHandle::resourceSplit(vector<string> addrs,int length)
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

/*Give an id, judge if it's in the range from low to high in clockwise ,open means it can't be equal to the boundry*/
bool RequestHandle::inRange(int id, int low, int high, bool low_open, bool high_open)
{
	if (low<high)
	{
		if (low_open && high_open){
			if (id>low && id<high)
				return true;
			else
				return false;
		   }
		else if (!low_open && high_open){
			if (id>=low && id<high)
				return true;
			else
				return false;
			}
		else if (low_open && !high_open){
			if (id>low && id<=high)
				return true;
			else
				return false;
		}
		else{
			if (id>=low && id<=high)
				return true;
			else
				return false;
		}	
	}
	else{
		if (low_open && high_open){
				if (id>low || id<high)
					return true;
				else
					return false;	
			}
			else if (!low_open && high_open){
				if (id>=low || id<high)
					return true;
				else
					return false;
			}
				
			else if (low_open && !high_open){
				if (id>low || id<=high)
					return true;
				else
					return false;
			}
			else {
				if (id>=low || id<=high)
					return true;
				else
					return false;
			}
			
	}
}

RequestHandle::~RequestHandle(void)
{
}
