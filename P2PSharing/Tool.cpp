#include "StdAfx.h"
#include "Tool.h"

//split the C++ string into substrings
vector<string> Tool::Split(string str,char* substr)
{
	vector<string> strvec;
	string::size_type pos1, pos2;
    pos2 = str.find(substr);
	pos1 = 0;

    while (string::npos != pos2)
	{
		strvec.push_back(str.substr(pos1, pos2 - pos1));
        pos1 = pos2 + 1;
        pos2 = str.find(substr, pos1);
	}
	strvec.push_back(str.substr(pos1));
	return strvec;
}

//judge if the string starts with the substring
bool Tool::Startwith(string str,char* substr)
{
	string tmpsub(substr);
	if( strncmp(str.c_str(), tmpsub.c_str() ,tmpsub.length()) == 0 )
	{
		return true;
	}
	return false;
}

Tool::Tool(void)
{
}


Tool::~Tool(void)
{
}

/*检测CString是否为数字*/
bool Tool::CheckNum(CString str)
{
	bool bNumFlag = true;
	bool bFloatFlag = false;
	for(int i=0;i<str.GetLength();i++)
	{
		if(((int)str.GetAt(i)>=48&&(int)str.GetAt(i)<=57)) 
			continue;	
		else if(str.GetAt(i)=='.')
		{
			if(bFloatFlag)
			{
				bNumFlag = false;
				break; 
			}
			else
			{
				bFloatFlag = true;
				continue;
			}

		}
		else
		{
			bNumFlag = false;
			break;
		}
	}
	return bNumFlag;
}

/*切分CString*/
vector<CString> Tool::CSplit(CString &str,const CString find)
{
	vector<CString> ret;
	int start = 0;
	int pos = str.Find(find,start);
	int len = find.GetLength();
	int i = 0;
	while(true){
		if(pos<0){ //NO FIND   
			ret.push_back(str.Mid(start));
			break;
		}else{
			ret.push_back(str.Mid(start,pos-start));
			start = pos+len;
			pos = str.Find(find,start);
		}
		i++;
	}
	return ret;
}

//取得EXE文件路径，将共享文件放置于此
CString Tool::QueryExePath()
{
	TCHAR path[MAX_PATH];
	::GetModuleFileName(NULL,path,MAX_PATH);
	CString p(path);
	CString subp;
	int nPos = p.ReverseFind('\\');
	//ASSERT(-1!=nPos);
	return p.Left(nPos+1);
}