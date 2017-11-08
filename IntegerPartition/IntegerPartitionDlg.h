
// IntegerPartitionDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CIntegerPartitionDlg �Ի���
class CIntegerPartitionDlg : public CDialog
{
// ����
public:
	CIntegerPartitionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_INTEGERPARTITION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    // ��������
    CComboBox m_wndType;
    // ����ǰ(GB)
    CEdit m_wndBefore;
    // �����(MB)
    CEdit m_wndAfter;
    afx_msg void OnEnChangeBefore();
    afx_msg void OnCbnSelchangeType();
};
