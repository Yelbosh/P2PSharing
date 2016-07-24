
// P2PSharing.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "P2PSharing.h"
#include "P2PSharingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CP2PSharingApp

BEGIN_MESSAGE_MAP(CP2PSharingApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CP2PSharingApp 构造

CP2PSharingApp::CP2PSharingApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	this->scout.str("");
}


// 唯一的一个 CP2PSharingApp 对象

CP2PSharingApp theApp;


// CP2PSharingApp 初始化

BOOL CP2PSharingApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CP2PSharingDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

//获取vilatile变量的值
int CP2PSharingApp::GetValue(int key)
{
	int result = 0;
	Lock.ReadLock();  
	switch(key)
	{
	case 1:
		result = value1;
		break;
	case 2:
		result = value2;
		break;
	case 3:
		result = value3;
		break;
	case 4:
		result = value4;
		break;
	case 5:
		result = value5;
		break;
	case 6:
		result = value6;
		break;
	case 7:
		result = value7;
		break;
	case 8:
		result = value8;
		break;
	case 9:
		result = value9;
		break;
	case 10:
		result = value10;
		break;
	case 11:
		result = value1;
		break;
	case 12:
		result = value12;
		break;
	case 13:
		result = value13;
		break;
	case 14:
		result = value14;
		break;
	case 15:
		result = value15;
		break;
	case 16:
		result = value16;
		break;
	case 17:
		result = value17;
		break;
	case 18:
		result = value18;
		break;
	case 19:
		result = value19;
		break;
	case 20:
		result = value20;
		break;
	case 21:
		result = value21;
		break;
	case 22:
		result = value22;
		break;
	case 23:
		result = value23;
		break;
	case 24:
		result = value24;
		break;
	case 25:
		result = value25;
		break;
	case 26:
		result = value26;
		break;
	case 27:
		result = value27;
		break;
	case 28:
		result = value28;
		break;
	case 29:
		result = value29;
		break;
	case 30:
		result = value30;
		break;
	case 31:
		result = value31;
		break;
	case 0:
		result = value0;
		break;
	}
	
	Lock.Unlock();
	return result;
}

//改变vilatile变量的值
void CP2PSharingApp::SetValue(int key,int value)
{
	Lock.WriteLock();
	switch(key)
	{
	case 1:
		value1 = value;
		break;
	case 2:
		value2 = value;
		break;
	case 3:
		value3 = value;
		break;
	case 4:
		value4 = value;
		break;
	case 5:
		value5 = value;
		break;
	case 6:
		value6 = value;
		break;
	case 7:
		value7 = value;
		break;
	case 8:
		value8 = value;
		break;
	case 9:
		value9 = value;
		break;
	case 10:
		value10 = value;
		break;
	case 11:
		value11 = value;
		break;
	case 12:
		value12 = value;
		break;
	case 13:
		value13 = value;
		break;
	case 14:
		value14 = value;
		break;
	case 15:
		value15 = value;
		break;
	case 16:
		value16 = value;
		break;
	case 17:
		value17 = value;
		break;
	case 18:
		value18 = value;
		break;
	case 19:
		value19 = value;
		break;
	case 20:
		value20 = value;
		break;
	case 21:
		value21 = value;
		break;
	case 22:
		value22 = value;
		break;
	case 23:
		value23 = value;
		break;
	case 24:
		value24 = value;
		break;
	case 25:
		value25 = value;
		break;
	case 26:
		value26 = value;
		break;
	case 27:
		value27 = value;
		break;
	case 28:
		value28 = value;
		break;
	case 29:
		value29 = value;
		break;
	case 30:
		value30 = value;
		break;
	case 31:
		value31 = value;
		break;
	case 0:
		value0 = value;
		break;
	}
	Lock.Unlock();
}

//增加value变量的值
void CP2PSharingApp::AddValue(int key,int value)
{
	int base = GetValue(key);
	int result = base + value;
	SetValue(key,result);
}

//获取length变量的值
int CP2PSharingApp::GetLength(int key)
{
	int result = 0;
	Lock.ReadLock();  
	switch(key)
	{
	case 1:
		result = length1;
		break;
	case 2:
		result = length2;
		break;
	case 3:
		result = length3;
		break;
	case 4:
		result = length4;
		break;
	case 5:
		result = length5;
		break;
	case 6:
		result = length6;
		break;
	case 7:
		result = length7;
		break;
	case 8:
		result = length8;
		break;
	case 9:
		result = length9;
		break;
	case 10:
		result = length10;
		break;
	case 11:
		result = length11;
		break;
	case 12:
		result = length12;
		break;
	case 13:
		result = length13;
		break;
	case 14:
		result = length14;
		break;
	case 15:
		result = length15;
		break;
	case 16:
		result = length16;
		break;
	case 17:
		result = length17;
		break;
	case 18:
		result = length18;
		break;
	case 19:
		result = length19;
		break;
	case 20:
		result = length20;
		break;
	case 21:
		result = length21;
		break;
	case 22:
		result = length22;
		break;
	case 23:
		result = length23;
		break;
	case 24:
		result = length24;
		break;
	case 25:
		result = length25;
		break;
	case 26:
		result = length26;
		break;
	case 27:
		result = length27;
		break;
	case 28:
		result = length28;
		break;
	case 29:
		result = length29;
		break;
	case 30:
		result = length30;
		break;
	case 31:
		result = length31;
		break;
	case 0:
		result = length0;
		break;
	}
	Lock.Unlock();
	return result;
}

//改变length变量的值
void CP2PSharingApp::SetLength(int key,int length)
{
	Lock.WriteLock();
	switch(key)
	{
	case 1:
		length1 = length;
		break;
	case 2:
		length2 = length;
		break;
	case 3:
		length3 = length;
		break;
	case 4:
		length4 = length;
		break;
	case 5:
		length5 = length;
		break;
	case 6:
		length6 = length;
		break;
	case 7:
		length7 = length;
		break;
	case 8:
		length8 = length;
		break;
	case 9:
		length9 = length;
		break;
	case 10:
		length10 = length;
		break;
	case 11:
		length11 = length;
		break;
	case 12:
		length12 = length;
		break;
	case 13:
		length13 = length;
		break;
	case 14:
		length14 = length;
		break;
	case 15:
		length15 = length;
		break;
	case 16:
		length16 = length;
		break;
	case 17:
		length17 = length;
		break;
	case 18:
		length18 = length;
		break;
	case 19:
		length19 = length;
		break;
	case 20:
		length20 = length;
		break;
	case 21:
		length21 = length;
		break;
	case 22:
		length22 = length;
		break;
	case 23:
		length23 = length;
		break;
	case 24:
		length24 = length;
		break;
	case 25:
		length25 = length;
		break;
	case 26:
		length26 = length;
		break;
	case 27:
		length27 = length;
		break;
	case 28:
		length28 = length;
		break;
	case 29:
		length29 = length;
		break;
	case 30:
		length30 = length;
		break;
	case 31:
		length31 = length;
		break;
	case 0:
		length0 = length;
		break;
	}
	Lock.Unlock();
}