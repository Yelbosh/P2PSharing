#include "StdAfx.h"
#include "SendHandle.h"
#include "Sock.h"
#include "P2PSharing.h"
#include "Tool.h"

using namespace SockUtil;
using namespace std;


SendHandle::SendHandle(void)  
{
}
SendHandle::SendHandle(string des_ip,int des_port,string hash_ip,int hash_port,int key,int length,int startPos,int partLen)
{
	this->des_ip = des_ip;
	this->des_port = des_port;
	this->hash_ip = hash_ip;
	this->hash_port = hash_port;
	this->key = key;
	this->length = length;
	this->startPos = startPos;
	this->partLen = partLen;
}

void SendHandle::run()
{
	try{
		sendPart();
	}
	catch(...)
	{
		theApp.scout<<"exception occured during trans send!"<<endl;
	}
}

void SendHandle::sendPart()
{
	CSocket socket;
	//����������Socket
	if(socket.Connect(des_ip.c_str(),des_port)){
		AfxMessageBox(_T("Failed to send Resource!Please Check Network Connection!"));
		return;
	}
	//������Ʊ���
	int sendedCount = 0;
	
	//���ļ�,��seek��startPosition
	stringstream sss;sss<<key;
	CString fileName = Tool::QueryExePath();fileName += "Share\\";fileName += sss.str().c_str();fileName += ".pcm";
	CFile sendFile;
	sendFile.Abort();
	sendFile.Open(fileName,CFile::modeRead);
	sendFile.Seek(startPos,CFile::begin);
	//���建��������,����ʼ��
	int BUFFER_LENGTH = 1024;
	char* BUFFER = (char*)LocalAlloc(LMEM_FIXED,BUFFER_LENGTH);
	memset(BUFFER,0,BUFFER_LENGTH);
	//�����ļ���Ϣ
	stringstream ss;ss<<des_ip<<"-"<<des_port<<"-"<<hash_ip<<"-"<<hash_port<<"-"<<key<<"-"<<length<<"-"<<startPos<<"-"<<partLen;
	string fileInfo = ss.str();
	socket.WriteLine(fileInfo);
	//����ȷ����Ϣ
	string resp = socket.ReadLine();
	if(strcmp(resp.c_str(),"OK"))
	{
		AfxMessageBox(_T("Failed to get Node Response!Please Check!"));
		return;
	}else//������Դ�ļ����ݣ�ÿ�η���1K
	{
		while(true)
		{
			//��ȡ������BUFFER,���ҷ��Ͷ�ȡ������
			int nCnt;
			try{
				if(partLen-sendedCount >= BUFFER_LENGTH)
				{
					sendFile.Read(BUFFER,BUFFER_LENGTH);
					nCnt = socket.Send(BUFFER,BUFFER_LENGTH);
				}
				else
				{
					sendFile.Read(BUFFER,partLen-sendedCount);
					nCnt = socket.Send(BUFFER,partLen-sendedCount);
				}
			}catch(...)
			{
				AfxMessageBox(_T("Exception occured during Sending!Sending Failed!"));
				socket.Close();
				return;
			}
			//����BUFFER
			memset(BUFFER,0,BUFFER_LENGTH);

			//����sendedCount
			sendedCount += nCnt;
			if(sendedCount >= partLen)
			{
				sendedCount = partLen;
				sendFile.Close();
				return;
			}
		}
	}
}

SendHandle::~SendHandle(void)
{
}
