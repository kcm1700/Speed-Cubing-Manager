
// Speed-Cubing-Manager.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CSpeedCubingManagerApp:
// �� Ŭ������ ������ ���ؼ��� Speed-Cubing-Manager.cpp�� �����Ͻʽÿ�.
//

class CSpeedCubingManagerApp : public CWinApp
{
public:
	CSpeedCubingManagerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CSpeedCubingManagerApp theApp;