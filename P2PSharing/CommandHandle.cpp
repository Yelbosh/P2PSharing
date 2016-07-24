#include "StdAfx.h"
#include "CommandHandle.h"
#include "Tool.h"
#include "LS.h"
#include "Join.h"
#include "Search.h"
#include "Leave.h"
#include "Get.h"
using namespace std;

CommandHandle::CommandHandle(void)
{
}

CommandHandle::CommandHandle(string cmd,Peer* peer)
{
	this->cmd = cmd;
	this->peer = peer;
}

void CommandHandle::run()
{
	try{
		handle();
	}catch(...)
	{
		AfxMessageBox(_T("Exception occured during handle ! "));
		return;
	}
}

void CommandHandle::handle()
{
	if (!isGoodCommand())
		falseCommand();
	else
	{
		if(Tool::Startwith(cmd,"get"))//获取文件资源
		{
			vector<string> s = Tool::Split(cmd," ");
			int searchId = atoi(s[1].c_str());
			Get get(peer,searchId);
			get.start_get();
		}
		else if(Tool::Startwith(cmd,"ls"))//打印节点自身的FingerTable
		{
			LS ls(peer);
			cout<<ls.list()<<endl;
		}
		else if(Tool::Startwith(cmd,"search"))//搜索文件资源
		{
			vector<string> s = Tool::Split(cmd," ");
			int searchId = atoi(s[1].c_str());
			Search search(peer,searchId);
			search.startSearch(0);
		}
		else if(Tool::Startwith(cmd,"join"))//节点加入网络
		{
			vector<string> cmdstrs = Tool::Split(cmd," ");
			if(cmdstrs.size() > 1)
			{
				string ipstr = cmdstrs[1];
				int join_port = atoi(cmdstrs[2].c_str());
				Join join(peer,ipstr,join_port);
				join.startJoin();
			}
			else
			{
				Join join(peer,Peer::DEFAULT_DEST_IP,Peer::DEFAULT_DEST_PORT);
				join.startJoin();
			}
		}
		else if(Tool::Startwith(cmd,"le"))//节点离开网络
		{
			Leave leave(peer);
			leave.start_leave();
		}
		else//命令有问题
		{
			AfxMessageBox(_T("bad command!"));
			return;
		}
	}
}

bool CommandHandle::isGoodCommand()
{
	return true;
}

void CommandHandle::falseCommand()
{
}

CommandHandle::~CommandHandle(void)
{
}
