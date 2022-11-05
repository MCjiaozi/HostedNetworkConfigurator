
// HostedNetworkConfiguratorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "HostedNetworkConfigurator.h"
#include "HostedNetworkConfiguratorDlg.h"
#include "afxdialogex.h"
#include "string"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHostedNetworkConfiguratorDlg 对话框

TCHAR* StringToChar(CString& str);

CHostedNetworkConfiguratorDlg::CHostedNetworkConfiguratorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOSTEDNETWORKCONFIGURATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHostedNetworkConfiguratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_5, m_output);
}

BEGIN_MESSAGE_MAP(CHostedNetworkConfiguratorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_KILLFOCUS()
//	ON_WM_KEYUP()
//	ON_WM_KEYDOWN()
ON_BN_CLICKED(IDC_RADIO_3, &CHostedNetworkConfiguratorDlg::OnBnClickedRadio3)
ON_BN_CLICKED(IDC_RADIO_30, &CHostedNetworkConfiguratorDlg::OnBnClickedRadio30)
ON_BN_CLICKED(IDC_RADIO_4, &CHostedNetworkConfiguratorDlg::OnBnClickedRadio4)
ON_BN_CLICKED(IDC_RADIO_40, &CHostedNetworkConfiguratorDlg::OnBnClickedRadio40)
ON_BN_CLICKED(IDOK, &CHostedNetworkConfiguratorDlg::OnBnClickedOk)
ON_BN_CLICKED(IDC_BUTTON_START, &CHostedNetworkConfiguratorDlg::OnBnClickedButtonStart)
ON_BN_CLICKED(IDC_BUTTON_STOP, &CHostedNetworkConfiguratorDlg::OnBnClickedButtonStop)
ON_BN_CLICKED(IDC_BUTTON_SHARE, &CHostedNetworkConfiguratorDlg::OnBnClickedButtonShare)
ON_BN_CLICKED(IDC_BUTTON_HELP, &CHostedNetworkConfiguratorDlg::OnBnClickedButtonHelp)
ON_BN_CLICKED(IDC_BUTTON_SHOW, &CHostedNetworkConfiguratorDlg::OnBnClickedButtonShow)
ON_BN_CLICKED(IDC_BUTTON_SAVE, &CHostedNetworkConfiguratorDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CHostedNetworkConfiguratorDlg 消息处理程序

BOOL CHostedNetworkConfiguratorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	OnBnClickedButtonHelp();
	if (GetConfig(_T("Saves"), _T("SSID")) == _T(""))GetDlgItem(IDC_EDIT_1)->SetWindowText(_T("default"));
	else GetDlgItem(IDC_EDIT_1)->SetWindowText(GetConfig(_T("Saves"), _T("SSID")));
	if (GetConfig(_T("Saves"), _T("Key")) == _T(""))GetDlgItem(IDC_EDIT_2)->SetWindowText(_T("123456789"));
	else GetDlgItem(IDC_EDIT_2)->SetWindowText(GetConfig(_T("Saves"), _T("Key")));
	if (GetConfig(_T("Saves"), _T("Mode")) == _T("disallow"))((CButton*)GetDlgItem(IDC_RADIO_30))->SetCheck(TRUE);
	else ((CButton*)GetDlgItem(IDC_RADIO_3))->SetCheck(TRUE);
	if (GetConfig(_T("Saves"), _T("KeyUsage")) == _T("temporary"))((CButton*)GetDlgItem(IDC_RADIO_40))->SetCheck(TRUE);
	else ((CButton*)GetDlgItem(IDC_RADIO_4))->SetCheck(TRUE);
	check();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHostedNetworkConfiguratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHostedNetworkConfiguratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CHostedNetworkConfiguratorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYUP && (GetFocus() == GetDlgItem(IDC_EDIT_1) || GetFocus() == GetDlgItem(IDC_EDIT_2)))check();
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CHostedNetworkConfiguratorDlg::check()
{
	CString ssid, key, mode, keyUsage, command;
	GetDlgItem(IDC_EDIT_1)->GetWindowText(ssid);
	GetDlgItem(IDC_EDIT_2)->GetWindowText(key);
	if (((CButton*)GetDlgItem(IDC_RADIO_3))->GetCheck() == 1)mode = _T("allow");
	else mode = _T("disallow");
	if (((CButton*)GetDlgItem(IDC_RADIO_4))->GetCheck() == 1)keyUsage = _T("persistent");
	else keyUsage = _T("temporary");
	command = _T("netsh wlan set hostednetwork ssid=") + ssid + _T(" key=") + key + _T(" mode=") + mode + _T(" keyUsage=") + keyUsage;
	GetDlgItem(IDC_EDIT_6)->SetWindowText(command);
}

void CHostedNetworkConfiguratorDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	check();
}


void CHostedNetworkConfiguratorDlg::OnBnClickedRadio30()
{
	// TODO: 在此添加控件通知处理程序代码
	check();
}


void CHostedNetworkConfiguratorDlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	check();
}


void CHostedNetworkConfiguratorDlg::OnBnClickedRadio40()
{
	// TODO: 在此添加控件通知处理程序代码
	check();
}


void CHostedNetworkConfiguratorDlg::executeCmd(CString command, BOOL LOCK)
{
	CString getLine;
	GetDlgItem(IDC_EDIT_5)->GetWindowText(getLine);
	GetDlgItem(IDC_EDIT_5)->SetWindowText(getLine + _T("正在尝试执行：") + command + _T("\r\n"));
	HANDLE hReadPipe, hWritePipe;
	SECURITY_ATTRIBUTES safety;
	safety.nLength = sizeof(SECURITY_ATTRIBUTES);
	safety.lpSecurityDescriptor = NULL;
	safety.bInheritHandle = TRUE;
	if (!CreatePipe(&hReadPipe, &hWritePipe, &safety, 0))
	{
		MessageBox(_T("创建管道错误！"));
	}
	TCHAR* cmdStr = StringToChar(command);
	STARTUPINFO startupInfo = { sizeof(startupInfo) };
	startupInfo.hStdError = hWritePipe;
	startupInfo.hStdOutput = hWritePipe;
	startupInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	if (LOCK) {
		startupInfo.wShowWindow = SW_HIDE;
	}
	else {
		startupInfo.wShowWindow = SW_SHOW;
	}
	PROCESS_INFORMATION pinfo;
	if (!CreateProcess(NULL, cmdStr, NULL, NULL, TRUE, NULL, NULL, NULL, &startupInfo, &pinfo))
	{
		MessageBox(_T("创建进程错误！"));
	}
	CloseHandle(pinfo.hProcess);
	CloseHandle(pinfo.hThread);
	CloseHandle(hWritePipe);
	char buffer[4096];
	DWORD byteRead;
	CString output;
	while (true)
	{
		memset(buffer, 0, 4096);
		if (ReadFile(hReadPipe, buffer, 4095, &byteRead, NULL) == NULL)
		{
			break;
		}
		output += buffer;
	}
	CloseHandle(hReadPipe);
	GetDlgItem(IDC_EDIT_5)->GetWindowText(getLine);
	GetDlgItem(IDC_EDIT_5)->SetWindowText(getLine + _T("输出：\r\n") + output + _T("==========\r\n"));
	m_output.LineScroll(m_output.GetLineCount());
}
TCHAR* StringToChar(CString& str)
{
	int len = str.GetLength();
	TCHAR* tr = str.GetBuffer(len);
	str.ReleaseBuffer();
	return tr;
}

void CHostedNetworkConfiguratorDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString command;
	GetDlgItem(IDC_EDIT_6)->GetWindowText(command);
	executeCmd(_T("cmd.exe /c ") + command, TRUE);
	//CDialogEx::OnOK();
}


void CHostedNetworkConfiguratorDlg::OnBnClickedButtonStart()
{
	executeCmd(_T("netsh.exe wlan start hostednetwork"), TRUE);
	// TODO: 在此添加控件通知处理程序代码
}


void CHostedNetworkConfiguratorDlg::OnBnClickedButtonStop()
{
	executeCmd(_T("netsh.exe wlan stop hostednetwork"), TRUE);
	// TODO: 在此添加控件通知处理程序代码
}


void CHostedNetworkConfiguratorDlg::OnBnClickedButtonShare()
{
	executeCmd(_T("rundll32.exe shell32.dll,Control_RunDLL Ncpa.cpl"), TRUE);
	// TODO: 在此添加控件通知处理程序代码
}


void CHostedNetworkConfiguratorDlg::OnBnClickedButtonHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	CString getLine;
	GetDlgItem(IDC_EDIT_5)->GetWindowText(getLine);
	GetDlgItem(IDC_EDIT_5)->SetWindowText(getLine + _T("使用方法：\r\n")+
		_T("1.设置SSID（无线局域网络名称）和KEY（无线局域网络密码，应为 8 到 63 个 ASCII 字符组成的字符串），\r\n   其他选项可保持默认。\r\n")+
		_T("2.单击“执行命令”，等待命令执行完成。\r\n")+
		_T("3.单击“设置网络共享”（或打开“控制面板\\网络和 Internet\\网络连接”），弹出窗口后选择有正常网络连接的适配器，右键单击，\r\n   选择“属性”，选择“共享”标签页，勾选“允许其他网络用户通过此计算机的 Internet 连接来连接(N)”复选框，\r\n   在“家庭网络连接(H)”处选择描述为 Microsoft Virtual WiFi Miniport Adapter 的适配器名称\r\n   （在上级窗口可查看名称，一般为“无线网络连接 2”），点击确定，关闭子窗口。\r\n")+
		_T("4.回到本程序，单击“启动承载网络”，等待命令执行完成。\r\n")+
		_T("注意事项：\r\n")+
		_T("1.须先启用网络共享，再启动承载网络。否则，承载网络可能无 Internet 访问，重复第3、4步即可解决。\r\n")+
		_T("2.系统无线适配器必须支持承载网络。单击“显示无线 LAN 驱动属性”，若显示“支持的承载网络  : 是”，即为支持，反之为不支持。\r\n")+
		_T("==========\r\n"));
	m_output.LineScroll(m_output.GetLineCount());
}


void CHostedNetworkConfiguratorDlg::OnBnClickedButtonShow()
{
	// TODO: 在此添加控件通知处理程序代码
	executeCmd(_T("netsh.exe wlan show drivers"), TRUE);
}


void CHostedNetworkConfiguratorDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ssid, key, mode, keyUsage;
	GetDlgItem(IDC_EDIT_1)->GetWindowText(ssid);
	GetDlgItem(IDC_EDIT_2)->GetWindowText(key);
	if (((CButton*)GetDlgItem(IDC_RADIO_3))->GetCheck() == 1)mode = _T("allow");
	else mode = _T("disallow");
	if (((CButton*)GetDlgItem(IDC_RADIO_4))->GetCheck() == 1)keyUsage = _T("persistent");
	else keyUsage = _T("temporary");
	WriteConfig(_T("Saves"), _T("SSID"), ssid);
	WriteConfig(_T("Saves"), _T("Key"), key);
	WriteConfig(_T("Saves"), _T("Mode"), mode);
	WriteConfig(_T("Saves"), _T("KeyUsage"), keyUsage);
	wchar_t buffer[MAX_PATH];
	GetEnvironmentVariable(_T("APPDATA"), buffer, MAX_PATH);
	CString lpPath = CString(buffer) + _T("\\HostedNetworkConfigurator\\config.ini");
	CString getLine;
	GetDlgItem(IDC_EDIT_5)->GetWindowText(getLine);
	GetDlgItem(IDC_EDIT_5)->SetWindowText(getLine + _T("已保存配置至：\r\n") + lpPath + _T("\r\n") + _T("==========\r\n"));
	m_output.LineScroll(m_output.GetLineCount());
}


CString CHostedNetworkConfiguratorDlg::GetConfig(CString AppName, CString KeyName) {
	CString Key;
	wchar_t buffer[MAX_PATH];
	GetEnvironmentVariable(_T("APPDATA"), buffer, MAX_PATH);
	CString lpPath = CString(buffer) + _T("\\HostedNetworkConfigurator\\config.ini");
	GetPrivateProfileString(AppName, KeyName, _T(""), Key.GetBuffer(MAX_PATH), MAX_PATH, lpPath);
	return Key;
}


void CHostedNetworkConfiguratorDlg::WriteConfig(CString AppName, CString KeyName, CString Key) {
	wchar_t buffer[MAX_PATH];
	GetEnvironmentVariable(_T("APPDATA"), buffer, MAX_PATH);
	CString lpPath = CString(buffer) + _T("\\HostedNetworkConfigurator\\config.ini");
	CString lpPath2 = CString(buffer) + _T("\\HostedNetworkConfigurator");
	if (!PathIsDirectory(lpPath2)) {
		CreateDirectory(lpPath2, 0);
	}
	WritePrivateProfileString(AppName, KeyName, Key, lpPath);
}