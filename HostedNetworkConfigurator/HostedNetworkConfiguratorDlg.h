
// HostedNetworkConfiguratorDlg.h: 头文件
//

#pragma once


// CHostedNetworkConfiguratorDlg 对话框
class CHostedNetworkConfiguratorDlg : public CDialogEx
{
// 构造
public:
	CHostedNetworkConfiguratorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOSTEDNETWORKCONFIGURATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio30();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio40();
	void executeCmd(CString command, BOOL LOCK);
	void check();
	afx_msg void OnBnClickedOk();
	CEdit m_output;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonShare();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonShow();
	afx_msg void OnBnClickedButtonSave();
	CString GetConfig(CString AppName, CString KeyName);
	void WriteConfig(CString AppName, CString KeyName, CString Key);
};
