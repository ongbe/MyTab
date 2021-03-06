
// MyTabDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MyTab.h"
#include "MyTabDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyTabDlg 对话框



CMyTabDlg::CMyTabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MYTAB_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tab);
}

BEGIN_MESSAGE_MAP(CMyTabDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CMyTabDlg::OnTcnSelchangeTab)
END_MESSAGE_MAP()


// CMyTabDlg 消息处理程序

BOOL CMyTabDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	TCITEM tc1, tc2;
	tc1.mask = TCIF_TEXT;
	tc1.pszText = _T("视频播放");
	tc2.mask = TCIF_TEXT;
	tc2.pszText = _T("参数编辑");

	m_tab.InsertItem(0, &tc1);
	m_tab.InsertItem(1, &tc2); //到这里只是添加了两个tab页

	CRect rec;
	m_tab.GetClientRect(&rec);//获得TAB控件的坐标

							  //定位选项卡页的位置，这里可以根据情况自己调节偏移量
	rec.bottom -= 2;
	rec.left += 1;
	rec.top += 27;
	rec.right -= 3;

	//创建子页面
	m_page1.Create(IDD_DIALOG1, GetDlgItem(IDC_TAB));
	m_page2.Create(IDD_DIALOG2, GetDlgItem(IDC_TAB));
	//将子页面移动到指定的位置
	m_page1.MoveWindow(&rec);
	m_page2.MoveWindow(&rec);
	//显示子页面
	m_page1.ShowWindow(SW_SHOW);
	m_page2.ShowWindow(SW_HIDE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyTabDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyTabDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyTabDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyTabDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_tab.GetCurSel())
	{
	case 0:
			m_page1.ShowWindow(SW_SHOW);
			m_page2.ShowWindow(SW_HIDE);
			break;
	case 1:
			m_page1.ShowWindow(SW_HIDE);
			m_page2.ShowWindow(SW_SHOW);
			break;
	default:
		break;
	}
	*pResult = 0;
}
