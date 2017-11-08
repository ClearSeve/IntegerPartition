
// IntegerPartitionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IntegerPartition.h"
#include "IntegerPartitionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CIntegerPartitionDlg �Ի���




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


// CIntegerPartitionDlg ��Ϣ�������

BOOL CIntegerPartitionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    // ��ComBox��������
    
	m_wndType.AddString(_T("NTFS"));
    m_wndType.AddString(_T("FAT32"));
    // Ĭ��ѡ�е�һ�� NTFS
    m_wndType.SetCurSel(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIntegerPartitionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CIntegerPartitionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ������������,��Ҫ���м���
void CIntegerPartitionDlg::OnEnChangeBefore()
{
    // ��������Ҫ������ַ���
    CString strText;
    // ��ȡ����
    m_wndBefore.GetWindowText( strText );
//////////////////////////////////////////////////////////////////////////
    // ���ַ���ת��Ϊchar[]
    int n = strText.GetLength();     // n = 14, len = 18 ע�⣺����n��len��ֵ��С��ͬ,n�ǰ��ַ�����ģ�len�ǰ��ֽڼ���� 
    //��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����
    int len =WideCharToMultiByte(CP_ACP,0,strText,strText.GetLength(),NULL,0,NULL,NULL);
    //Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ŀ��ֽ��ֽڴ�С
    char * pNewStrText = new char[len+1];  //���ֽ�Ϊ��λ
    //���ֽڱ���ת���ɶ��ֽڱ���
    WideCharToMultiByte(CP_ACP,0,strText,strText.GetLength(),pNewStrText,len,NULL,NULL);
    pNewStrText[len] = '\0';   //���ֽ��ַ���'\0'����
//////////////////////////////////////////////////////////////////////////
    // ���ַ���ת����Ϊ����
    int nBefore = atoi(pNewStrText);
    // �ͷŵ��ڴ�
    delete(pNewStrText);

    if( nBefore == 0)
    {
        AfxMessageBox(_T("���ڷ���Ϊ0GB���޷����м���!"));
        return ;
    }
    // �����˼���������
    int data = 0;
    // ������ת������ַ���
    CString strAfter;
    // ���м���
    if( m_wndType.GetCurSel() == 0)// ��ȡ��ǰѡ�����жϷ�������
    {// NTFS
        data = (nBefore*1024)+5;
        
    }else
    {// FAT32
        data = (nBefore*1024)+((nBefore-1)*4);
    }
    // ������ת��Ϊ�ַ���
    strAfter.Format(_T("%d"),data);
    // ���浽EDIT����
    m_wndAfter.SetWindowText(strAfter);

}
// ������������Ըı�
void CIntegerPartitionDlg::OnCbnSelchangeType()
{
    OnEnChangeBefore();
}
