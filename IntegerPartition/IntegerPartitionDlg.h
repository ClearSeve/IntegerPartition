
// IntegerPartitionDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CIntegerPartitionDlg 对话框
class CIntegerPartitionDlg : public CDialog
{
// 构造
public:
	CIntegerPartitionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_INTEGERPARTITION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    // 分区类型
    CComboBox m_wndType;
    // 计算前(GB)
    CEdit m_wndBefore;
    // 计算后(MB)
    CEdit m_wndAfter;
    afx_msg void OnEnChangeBefore();
    afx_msg void OnCbnSelchangeType();
};
