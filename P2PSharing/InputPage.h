#pragma once


// InputPage �Ի���

class InputPage : public CDialogEx
{
	DECLARE_DYNAMIC(InputPage)

public:
	InputPage(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~InputPage();

// �Ի�������
	enum { IDD = IDD_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_peerID;
	afx_msg void OnBnClickedButton1();
};
