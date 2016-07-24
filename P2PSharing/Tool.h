#pragma once

#include <string>
#include <vector>
using namespace std;

class Tool
{
public:
	Tool(void);
	~Tool(void);
	static vector<string> Split(string str,char* substr);
	static bool Startwith(string str,char* substr);
	static bool CheckNum(CString str);
	static vector<CString> CSplit(CString &str,const CString find);
	static CString QueryExePath();
};

