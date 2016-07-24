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
	//������Ʊ���
	int isReceived = 0;//�Ƿ��ѽ��շֿ���Ϣ
	int receivedCount = 0;//�÷ֿ��ѽ��յ��ֽ���
	string des_ip,hash_ip;
	int des_port,hash_port,key,length,startPos,partLen;
	//���建��������,����ʼ��
	int BUFFER_LENGTH = 1024;
	char* BUFFER = (char*)LocalAlloc(LMEM_FIXED,BUFFER_LENGTH);
	memset(BUFFER,0,BUFFER_LENGTH);
	//���Ͻ������ݣ�ֱ���ֿ鴫�����
	CFile recvFile;
	while(true)
	{
		if(!isReceived)//���շֿ���Ϣ
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
			//�����ļ���Ϣ���ܱ�־
			isReceived = 1;
			//���ն�ȷ�Ͻ���
			string resp = "OK";
			socket->WriteLine(resp);
			//���ļ����������򴴽�
			stringstream sss;sss<<key;
			CString fileName = Tool::QueryExePath();fileName += "Share\\";fileName += sss.str().c_str();fileName += ".pcm";
			//�߳���ͬ��
			recvFile.Abort();
			recvFile.Open(fileName,CFile::modeWrite | CFile::modeCreate | CFile::shareDenyNone);
		}else
		{
			//��������
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
			//���¿��Ʊ���
			receivedCount += nRec;
			// ���¶�λ��д����ļ������Ҽ��϶��̶߳�д��
			recvFile.Seek(startPos+receivedCount,CFile::begin);
			recvFile.Write(BUFFER,nRec);
			//���û�����
			memset(BUFFER,0,BUFFER_LENGTH);
			//�����̱߳���
			theApp.AddValue(key,nRec);

			if(receivedCount >= partLen)
			{
				receivedCount = partLen;
				recvFile.Close();
				//��ÿһ�鴫�������ĩβ����Ƿ�Ӧ�ø���key
				if(theApp.GetValue(key) >= theApp.GetLength(key))
				{
					stringstream tmps,tmps2;tmps<<des_port-Config::TRANS_PORT_BASE+Config::PORT_BASE;tmps2<<key;
					string updatecmd = "update_keylist " + tmps2.str() + " " + des_ip + " " + tmps.str();
					CSocket updateSocket;
					updateSocket.Connect(hash_ip.c_str(),hash_port);
					updateSocket.WriteLine(updatecmd);
					updateSocket.Close();
				}
				//�ͷŻ�����

				return;
			}
		}
	}
}


ReceiveHandle::~ReceiveHandle(void)
{
}
