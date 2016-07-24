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

/*根据theApp中的信息来进行音乐的播放*/
void PlayThread::play()
{
	int BUFFER_LENGTH = 1024 * 1024;
	char* buf = (char*)LocalAlloc(LMEM_FIXED,BUFFER_LENGTH);
	FILE*           thbgm;//文件
	int             cnt;
	HWAVEOUT        hwo;
	WAVEHDR         wh;
	WAVEFORMATEX    wfx;
	HANDLE          wait;

	wfx.wFormatTag = WAVE_FORMAT_PCM;//设置波形声音的格式
	wfx.nChannels = 1;//设置音频文件的通道数量
	wfx.nSamplesPerSec = 8000;//设置每个声道播放和记录时的样本频率
	wfx.nAvgBytesPerSec = 16000;//设置请求的平均数据传输率,单位byte/s。这个值对于创建缓冲大小是很有用的
	wfx.nBlockAlign = 2;//以字节为单位设置块对齐
	wfx.wBitsPerSample = 16;
	wfx.cbSize = 0;//额外信息的大小
	wait = CreateEvent(NULL, 0, 0, NULL);
	waveOutOpen(&hwo, WAVE_MAPPER, &wfx, (DWORD_PTR)wait, 0L, CALLBACK_EVENT);//打开一个给定的波形音频输出装置来进行回放
	int key = theApp.playKey;
	if(key < 0)
		return;
	int length;
	//打开指定的音频文件
	stringstream sss;sss<<theApp.playKey;
	CString fileName = Tool::QueryExePath();fileName += "Share\\";fileName += sss.str().c_str();fileName += ".pcm";
	try{
		fopen_s(&thbgm, CT2A(fileName.GetBuffer(0)), "rb");
	}catch(...)
	{
		AfxMessageBox(_T("读取文件发生异常！"));
		return;
	}
	//如果得到的长度不为0，说明还在传送中
	if(theApp.GetLength(theApp.playKey) != 0)
	{
		length = theApp.GetLength(theApp.playKey);
	}
	else//传送完毕
	{
		
		fseek(thbgm,0,SEEK_END);     //定位到文件末   
		length = ftell(thbgm); 
		fseek(thbgm,0,SEEK_SET);     //定位到文件首部
	}
	int playCnt = 0;
	//重置已经播放的字节数
	theApp.playPer = 0;
	while(playCnt < length){
		int dolenght = 0;
		int playsize = 1024;
		fseek(thbgm,playCnt,SEEK_SET);
		cnt = fread(buf, sizeof(char), 1024 * 1024, thbgm);//读取文件1M的数据到内存来进行播放，通过这个部分的修改，增加线程可变成网络音频数据的实时传输。当然如果希望播放完整的音频文件，也是要在这里稍微改一改
		while (cnt>0) {//这一部分需要特别注意的是在循环回来之后不能花太长的时间去做读取数据之类的工作，不然在每个循环的间隙会有“哒哒”的噪音
			wh.lpData = buf + dolenght;
			wh.dwBufferLength = playsize;
			wh.dwFlags = 0L;
			wh.dwLoops = 1L;
			waveOutPrepareHeader(hwo, &wh, sizeof(WAVEHDR));//准备一个波形数据块用于播放
			waveOutWrite(hwo, &wh, sizeof(WAVEHDR));//在音频媒体中播放第二个函数wh指定的数据
			WaitForSingleObject(wait, INFINITE);//用来检测hHandle事件的信号状态，在某一线程中调用该函数时，线程暂时挂起，如果在挂起的INFINITE毫秒内，线程所等待的对象变为有信号状态，则该函数立即返回
			dolenght = dolenght + playsize;
			cnt = cnt - playsize;
			playCnt += playsize;
			//计算出百分比
			double percent_dou = ((double)playCnt / length);
			theApp.playPer = percent_dou * 100;
		}
	}
	theApp.playPer = 100;
	waveOutClose(hwo);
	fclose(thbgm);
	LocalFree(buf);
}