
// IntegerPartitionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IntegerPartition.h"
#include "IntegerPartitionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CIntegerPartitionDlg 对话框




CIntegerPartitionDlg::CIntegerPartitionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIntegerPartitionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CIntegerPartitionDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TYPE, m_wndType);
    DDX_Control(pDX, IDC_BEFORE, m_wndBefore);
    DDX_Control(pDX, IDC_AFTER, m_wndAfter);
}

BEGIN_MESSAGE_MAP(CIntegerPartitionDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_EN_CHANGE(IDC_BEFORE, &CIntegerPartitionDlg::OnEnChangeBefore)
    ON_CBN_SELCHANGE(IDC_TYPE, &CIntegerPartitionDlg::OnCbnSelchangeType)
END_MESSAGE_MAP()


// CIntegerPartitionDlg 消息处理程序

BOOL CIntegerPartitionDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

    // 向ComBox增加数据
    
	m_wndType.AddString(_T("NTFS"));
    m_wndType.AddString(_T("FAT32"));
    // 默认选中第一个 NTFS
    m_wndType.SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIntegerPartitionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIntegerPartitionDlg::OnPaint()
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
HCURSOR CIntegerPartitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 有新内容输入,需要进行计算
void CIntegerPartitionDlg::OnEnChangeBefore()
{
    // 保存了需要计算的字符串
    CString strText;
    // 获取内容
    m_wndBefore.GetWindowText( strText );
//////////////////////////////////////////////////////////////////////////
    // 将字符串转换为char[]
    int n = strText.GetLength();     // n = 14, len = 18 注意：以下n和len的值大小不同,n是按字符计算的，len是按字节计算的 
    //获取宽字节字符的大小，大小是按字节计算的
    int len =WideCharToMultiByte(CP_ACP,0,strText,strText.GetLength(),NULL,0,NULL,NULL);
    //为多字节字符数组申请空间，数组大小为按字节计算的宽字节字节大小
    char * pNewStrText = new char[len+1];  //以字节为单位
    //宽字节编码转换成多字节编码
    WideCharToMultiByte(CP_ACP,0,strText,strText.GetLength(),pNewStrText,len,NULL,NULL);
    pNewStrText[len] = '\0';   //多字节字符以'\0'结束
//////////////////////////////////////////////////////////////////////////
    // 将字符串转换成为数字
    int nBefore = atoi(pNewStrText);
    // 释放掉内存
    delete(pNewStrText);

    if( nBefore == 0)
    {
        AfxMessageBox(_T("对于分区为0GB我无法进行计算!"));
        return ;
    }
    // 保存了计算后的数据
    int data = 0;
    // 保存了转换后的字符串
    CString strAfter;
    // 进行计算
    if( m_wndType.GetCurSel() == 0)// 获取当前选择项判断分区类型
    {// NTFS
        data = (nBefore*1024)+5;
        
    }else
    {// FAT32
        data = (nBefore*1024)+((nBefore-1)*4);
    }
    // 将数字转换为字符串
    strAfter.Format(_T("%d"),data);
    // 保存到EDIT框中
    m_wndAfter.SetWindowText(strAfter);

}
// 下拉框的内容以改变
void CIntegerPartitionDlg::OnCbnSelchangeType()
{
    OnEnChangeBefore();
}
