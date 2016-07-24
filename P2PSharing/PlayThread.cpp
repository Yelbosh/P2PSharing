#include "StdAfx.h"
#include "PlayThread.h"
#include <stdio.h>
#include <mmsystem.h>
#include <windows.h>
#include "P2PSharing.h"
#include "Tool.h"

#pragma comment(lib, "winmm.lib")


PlayThread::PlayThread(void)
{
}

PlayThread::PlayThread(int key)
{
	this->key;
}


PlayThread::~PlayThread(void)
{
}

void PlayThread::run()
{
	try{
		play();
	}catch(...)
	{
		AfxMessageBox(_T("Exception occured during play ! "));
		return;
	}
}

/*����theApp�е���Ϣ���������ֵĲ���*/
void PlayThread::play()
{
	int BUFFER_LENGTH = 1024 * 1024;
	char* buf = (char*)LocalAlloc(LMEM_FIXED,BUFFER_LENGTH);
	FILE*           thbgm;//�ļ�
	int             cnt;
	HWAVEOUT        hwo;
	WAVEHDR         wh;
	WAVEFORMATEX    wfx;
	HANDLE          wait;

	wfx.wFormatTag = WAVE_FORMAT_PCM;//���ò��������ĸ�ʽ
	wfx.nChannels = 1;//������Ƶ�ļ���ͨ������
	wfx.nSamplesPerSec = 8000;//����ÿ���������źͼ�¼ʱ������Ƶ��
	wfx.nAvgBytesPerSec = 16000;//���������ƽ�����ݴ�����,��λbyte/s�����ֵ���ڴ��������С�Ǻ����õ�
	wfx.nBlockAlign = 2;//���ֽ�Ϊ��λ���ÿ����
	wfx.wBitsPerSample = 16;
	wfx.cbSize = 0;//������Ϣ�Ĵ�С
	wait = CreateEvent(NULL, 0, 0, NULL);
	waveOutOpen(&hwo, WAVE_MAPPER, &wfx, (DWORD_PTR)wait, 0L, CALLBACK_EVENT);//��һ�������Ĳ�����Ƶ���װ�������лط�
	int key = theApp.playKey;
	if(key < 0)
		return;
	int length;
	//��ָ������Ƶ�ļ�
	stringstream sss;sss<<theApp.playKey;
	CString fileName = Tool::QueryExePath();fileName += "Share\\";fileName += sss.str().c_str();fileName += ".pcm";
	try{
		fopen_s(&thbgm, CT2A(fileName.GetBuffer(0)), "rb");
	}catch(...)
	{
		AfxMessageBox(_T("��ȡ�ļ������쳣��"));
		return;
	}
	//����õ��ĳ��Ȳ�Ϊ0��˵�����ڴ�����
	if(theApp.GetLength(theApp.playKey) != 0)
	{
		length = theApp.GetLength(theApp.playKey);
	}
	else//�������
	{
		
		fseek(thbgm,0,SEEK_END);     //��λ���ļ�ĩ   
		length = ftell(thbgm); 
		fseek(thbgm,0,SEEK_SET);     //��λ���ļ��ײ�
	}
	int playCnt = 0;
	//�����Ѿ����ŵ��ֽ���
	theApp.playPer = 0;
	while(playCnt < length){
		int dolenght = 0;
		int playsize = 1024;
		fseek(thbgm,playCnt,SEEK_SET);
		cnt = fread(buf, sizeof(char), 1024 * 1024, thbgm);//��ȡ�ļ�1M�����ݵ��ڴ������в��ţ�ͨ��������ֵ��޸ģ������߳̿ɱ��������Ƶ���ݵ�ʵʱ���䡣��Ȼ���ϣ��������������Ƶ�ļ���Ҳ��Ҫ��������΢��һ��
		while (cnt>0) {//��һ������Ҫ�ر�ע�������ѭ������֮���ܻ�̫����ʱ��ȥ����ȡ����֮��Ĺ�������Ȼ��ÿ��ѭ���ļ�϶���С����ա�������
			wh.lpData = buf + dolenght;
			wh.dwBufferLength = playsize;
			wh.dwFlags = 0L;
			wh.dwLoops = 1L;
			waveOutPrepareHeader(hwo, &wh, sizeof(WAVEHDR));//׼��һ���������ݿ����ڲ���
			waveOutWrite(hwo, &wh, sizeof(WAVEHDR));//����Ƶý���в��ŵڶ�������whָ��������
			WaitForSingleObject(wait, INFINITE);//�������hHandle�¼����ź�״̬����ĳһ�߳��е��øú���ʱ���߳���ʱ��������ڹ����INFINITE�����ڣ��߳����ȴ��Ķ����Ϊ���ź�״̬����ú�����������
			dolenght = dolenght + playsize;
			cnt = cnt - playsize;
			playCnt += playsize;
			//������ٷֱ�
			double percent_dou = ((double)playCnt / length);
			theApp.playPer = percent_dou * 100;
		}
	}
	theApp.playPer = 100;
	waveOutClose(hwo);
	fclose(thbgm);
	LocalFree(buf);
}