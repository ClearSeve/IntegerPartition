
// IntegerPartition.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIntegerPartitionApp:
// �йش����ʵ�֣������ IntegerPartition.cpp
//

class CIntegerPartitionApp : public CWinAppEx
{
public:
	CIntegerPartitionApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIntegerPartitionApp theApp;