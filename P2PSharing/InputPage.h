#pragma once


// InputPage 对话框

class InputPage : public CDialogEx
{
	DECLARE_DYNAMIC(InputPage)

public:
	InputPage(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~InputPage();

// 对话框数据
	enum { IDD = IDD_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_peerID;
	afx_msg void OnBnClickedButton1();
};
