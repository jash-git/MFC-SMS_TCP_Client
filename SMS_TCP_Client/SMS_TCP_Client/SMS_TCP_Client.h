
// SMS_TCP_Client.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CSMS_TCP_ClientApp: 
// �аѾ\��@�����O�� SMS_TCP_Client.cpp
//

class CSMS_TCP_ClientApp : public CWinApp
{
public:
	CSMS_TCP_ClientApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CSMS_TCP_ClientApp theApp;