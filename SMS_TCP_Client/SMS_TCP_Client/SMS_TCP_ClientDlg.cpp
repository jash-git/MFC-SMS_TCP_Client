
// SMS_TCP_ClientDlg.cpp : ¹ê§@ÀÉ
//

#include "stdafx.h"
#include "SMS_TCP_Client.h"
#include "SMS_TCP_ClientDlg.h"
#include "afxdialogex.h"
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSMS_TCP_ClientDlg ¹ï¸Ü¤è¶ô

CString gStrIP;
int gintPort;
int gintTimerCount;

CSMS_TCP_ClientDlg::CSMS_TCP_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SMS_TCP_CLIENT_DIALOG, pParent)
	, m_StrNowTime(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSMS_TCP_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NowTime, m_StrNowTime);
}

BEGIN_MESSAGE_MAP(CSMS_TCP_ClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CSMS_TCP_ClientDlg::OnClickedButton1)
END_MESSAGE_MAP()


// CSMS_TCP_ClientDlg °T®§³B²z±`¦¡

BOOL CSMS_TCP_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ³]©w¦¹¹ï¸Ü¤è¶ôªº¹Ï¥Ü¡C·íÀ³¥Îµ{¦¡ªº¥Dµøµ¡¤£¬O¹ï¸Ü¤è¶ô®É¡A
	// ®Ø¬[·|¦Û°Ê±q¨Æ¦¹§@·~
	SetIcon(m_hIcon, TRUE);			// ³]©w¤j¹Ï¥Ü
	SetIcon(m_hIcon, FALSE);		// ³]©w¤p¹Ï¥Ü

	ShowWindow(SW_MINIMIZE);

	// TODO: ¦b¦¹¥[¤JÃB¥~ªºªì©l³]©w
	//---
	//SERVER ÙY?×xÈ¡™n°¸
	gStrIP="192.168.0.102";
	gintPort= 10006;
	gintTimerCount = 0;
	char buf[50];
	char buf0[100];
	CString StrBuf;
	int i = 0;
	FILE *pf=NULL;
	fopen_s(&pf,"ServerInfo.txt", "r");
	while (fgets(buf, 512, pf) != NULL)
	{
		switch (i)
		{
		case 0:
			//sscanf_s(buf,"IP:%s", buf0);
			StrBuf = buf;
			gStrIP = StrBuf.Mid(0, (StrBuf.GetLength()-1));
			break;
		case 1:
			//sscanf_s(buf,"Port:%s", buf0);
			StrBuf = buf;
			gintPort=_ttoi(StrBuf);
			break;
		}
		i++;
	}
	fclose(pf);
	//---SERVER ÙY?×xÈ¡™n°¸
	SetTimer(1, 1000, NULL);//¶}±ÒTimer
	
	return TRUE;  // ¶Ç¦^ TRUE¡A°£«D±z¹ï±±¨î¶µ³]©wµJÂI
}

// ¦pªG±N³Ì¤p¤Æ«ö¶s¥[¤J±zªº¹ï¸Ü¤è¶ô¡A±z»Ý­n¤U¦Cªºµ{¦¡½X¡A
// ¥H«KÃ¸»s¹Ï¥Ü¡C¹ï©ó¨Ï¥Î¤å¥ó/ÀËµø¼Ò¦¡ªº MFC À³¥Îµ{¦¡¡A
// ®Ø¬[·|¦Û°Ê§¹¦¨¦¹§@·~¡C

void CSMS_TCP_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Ã¸»sªº¸Ë¸m¤º®e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ±N¹Ï¥Ü¸m¤¤©ó¥Î¤áºÝ¯x§Î
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ´yÃ¸¹Ï¥Ü
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ·í¨Ï¥ÎªÌ©ì¦²³Ì¤p¤Æµøµ¡®É¡A
// ¨t²Î©I¥s³o­Ó¥\¯à¨ú±o´å¼ÐÅã¥Ü¡C
HCURSOR CSMS_TCP_ClientDlg::OnQueryDragIcon()
{

	return static_cast<HCURSOR>(m_hIcon);
}



void CSMS_TCP_ClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ¦b¦¹¥[¤J±zªº°T®§³B²z±`¦¡µ{¦¡½X©M (©Î) ©I¥s¹w³]­È
	CString StrPort; 
	StrPort.Format("%d",gintPort);
	CString SendData;
	FILE *pf = NULL;
	TCHAR gstrCurDrt[500];//¦s©ñ¥Ø¨ä¥Ø¿ý¦r¦ê
	int nLen = ::GetCurrentDirectory(500, gstrCurDrt);//¨ú±o¥Ø«eµ{¦¡¸ô®|
	if (gstrCurDrt[nLen] != '\\')
	{
		gstrCurDrt[nLen++] = '\\';
		gstrCurDrt[nLen] = '\0';
	}

	KillTimer(1);
	CString StrCallExePath;
	CString StrCallExeName;
	CString StrListName;
	StrCallExeName = gstrCurDrt;
	StrCallExeName += "smstxt1\\get_list.bat ";
	StrCallExePath = gstrCurDrt;
	StrCallExePath += "smstxt1\\";
	StrListName = gstrCurDrt;
	StrListName += "smstxt1\\list.txt";

	fopen_s(&pf,StrCallExeName.GetBuffer(0), "w");
	fprintf(pf, "dir /b /on >list.txt");
	fclose(pf);

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.wShowWindow = SW_MINIMIZE;
	si.dwFlags = STARTF_USESHOWWINDOW;
	BOOL fRet = CreateProcess(NULL,
		StrCallExeName.GetBuffer(0),
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE,
		NULL,
		StrCallExePath.GetBuffer(0),
		&si,
		&pi);
	if (fRet)
	{
		WaitForSingleObject(pi.hProcess, INFINITE);
	}

	pf = NULL;
	char buf[513];
	CArray <CString, CString&> ArrayData;
	ArrayData.RemoveAll();
	fopen_s(&pf, StrListName.GetBuffer(0), "r");
	while (fgets(buf, 512, pf) != NULL)
	{
		CString StrBuf = buf;
		if ( (StrBuf != "\n") && (StrBuf != "get_list.bat\n") && (StrBuf != "list.txt\n") )
		{

			ArrayData.Add(StrBuf.Left(StrBuf.GetLength()-1));
		}
	}
	fclose(pf);
	
	CTime timeNow = CTime::GetCurrentTime();
	gintTimerCount++;
	UpdateData(true);
	if (ArrayData.GetCount() == 0)
	{
		m_StrNowTime = "IP:"+ gStrIP+"\tPort:" + StrPort +"\n" + timeNow.Format("%Y/%m/%d %H:%M:%S") + "\nWaiting...";
		if (gintTimerCount >= 12)//30Ãë·À´ôÖ¸Áî
		{
			gintTimerCount = 0;
			CSocket m_socket00;//Socket Step02
			m_socket00.Create();//Socket Step03
			bool check = m_socket00.Connect(gStrIP, gintPort);
			if (check == true)
			{
				SendData = "$$$AT+GET2?";
				m_socket00.Send(SendData.GetBuffer(0), SendData.GetLength());//Socket Step04
				char szRecv[20];
				m_socket00.Receive(szRecv, 20);//Socket Step04
				m_StrNowTime = "IP:" + gStrIP + "\tPort:" + StrPort + "\n" + timeNow.Format("%Y/%m/%d %H:%M:%S") + "\n" + SendData + "\n" + szRecv;
			}
			m_socket00.Close();//Socket Step05
		}
	}
	else
	{
		gintTimerCount = 0;
		CSocket m_socket01;//Socket Step02
		m_socket01.Create();//Socket Step03
		bool check = m_socket01.Connect(gStrIP, gintPort);
		if (check == true)
		{
			for (int i = 0; i < ArrayData.GetCount(); i++)
			{
				CString StrFileName = gstrCurDrt;
				StrFileName += "smstxt1\\";
				StrFileName += ArrayData.GetAt(i);
				pf = NULL;
				fopen_s(&pf, StrFileName.GetBuffer(0), "r");
				while (fgets(buf, 512, pf) != NULL)
				{
					SendData.Format("%s", buf);
					m_socket01.Send(SendData.GetBuffer(0), SendData.GetLength());//Socket Step04

					char szRecv[20];
					m_socket01.Receive(szRecv, 20);//Socket Step04
					m_StrNowTime = "IP:" + gStrIP + "\tPort:" + StrPort + "\n" + timeNow.Format("%Y/%m/%d %H:%M:%S") + "\n" + SendData + "\n" + szRecv;
					break;
				}
				fclose(pf);
				::DeleteFile(StrFileName.GetBuffer());
				::Sleep(1000);
			}	
		}
		m_socket01.Close();//Socket Step05
	}
	UpdateData(false);

	SetTimer(1, 3000, NULL);//¶}±ÒTimer
	CDialogEx::OnTimer(nIDEvent);
}


void CSMS_TCP_ClientDlg::OnClickedButton1()
{
	// TODO: ÔÚ´Ë¼ÓÈë¿ØÖÆ?¸æÖª?Àí³£Ê½³ÌÊ½´a
	OnOK();//ëxé_°´âo?¬F
}
