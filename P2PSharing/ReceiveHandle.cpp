#include "StdAfx.h"
#include "ReceiveHandle.h"
#include "P2PSharing.h"
#include "Tool.h"
#include "Config.h"


ReceiveHandle::ReceiveHandle(void)
{
}

ReceiveHandle::ReceiveHandle(CSocket* socket)
{
	this->socket = socket;
}

void ReceiveHandle::run()
{
	try
	{
		receivePart();
	}catch(...)
	{
		theApp.scout<<"Exception occured during receive part!"<<endl;
	}
}

void ReceiveHandle::receivePart()
{
	//定义控制变量
	int isReceived = 0;//是否已接收分块信息
	int receivedCount = 0;//该分块已接收的字节数
	string des_ip,hash_ip;
	int des_port,hash_port,key,length,startPos,partLen;
	//定义缓冲区属性,并初始化
	int BUFFER_LENGTH = 1024;
	char* BUFFER = (char*)LocalAlloc(LMEM_FIXED,BUFFER_LENGTH);
	memset(BUFFER,0,BUFFER_LENGTH);
	//不断接收数据，直到分块传输完毕
	CFile recvFile;
	while(true)
	{
		if(!isReceived)//接收分块信息
		{
			string fileInfo = socket->ReadLine();
			vector<string> vec = Tool::Split(fileInfo,"-");
			des_ip = vec[0];
			des_port = atoi(vec[1].c_str());
			hash_ip = vec[2];
			hash_port = atoi(vec[3].c_str());
			key = atoi(vec[4].c_str());
			length = atoi(vec[5].c_str());
			startPos = atoi(vec[6].c_str());
			partLen = atoi(vec[7].c_str());
			//设置文件信息接受标志
			isReceived = 1;
			//接收端确认接收
			string resp = "OK";
			socket->WriteLine(resp);
			//打开文件，不存在则创建
			stringstream sss;sss<<key;
			CString fileName = Tool::QueryExePath();fileName += "Share\\";fileName += sss.str().c_str();fileName += ".pcm";
			//线程锁同步
			recvFile.Abort();
			recvFile.Open(fileName,CFile::modeWrite | CFile::modeCreate | CFile::shareDenyNone);
		}else
		{
			//接收数据
			int nRec;
			try{
				nRec = socket->Read(BUFFER,BUFFER_LENGTH);
			}
			catch(...)
			{
				AfxMessageBox(_T("Failed in receiving data!"));
				socket->Close();
				return;
			}
			//更新控制变量
			receivedCount += nRec;
			// 重新定位待写入的文件，并且加上多线程读写锁
			recvFile.Seek(startPos+receivedCount,CFile::begin);
			recvFile.Write(BUFFER,nRec);
			//重置缓冲区
			memset(BUFFER,0,BUFFER_LENGTH);
			//更新线程变量
			theApp.AddValue(key,nRec);

			if(receivedCount >= partLen)
			{
				receivedCount = partLen;
				recvFile.Close();
				//在每一块传输结束的末尾检查是否应该更新key
				if(theApp.GetValue(key) >= theApp.GetLength(key))
				{
					stringstream tmps,tmps2;tmps<<des_port-Config::TRANS_PORT_BASE+Config::PORT_BASE;tmps2<<key;
					string updatecmd = "update_keylist " + tmps2.str() + " " + des_ip + " " + tmps.str();
					CSocket updateSocket;
					updateSocket.Connect(hash_ip.c_str(),hash_port);
					updateSocket.WriteLine(updatecmd);
					updateSocket.Close();
				}
				//释放缓冲区

				return;
			}
		}
	}
}


ReceiveHandle::~ReceiveHandle(void)
{
}
