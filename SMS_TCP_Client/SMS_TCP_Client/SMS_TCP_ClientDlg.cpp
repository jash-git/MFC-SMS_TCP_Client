
// SMS_TCP_ClientDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "SMS_TCP_Client.h"
#include "SMS_TCP_ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSMS_TCP_ClientDlg 對話方塊



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
END_MESSAGE_MAP()


// CSMS_TCP_ClientDlg 訊息處理常式

BOOL CSMS_TCP_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此加入額外的初始設定
	SetTimer(1, 1000, NULL);//開啟Timer
	
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CSMS_TCP_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CSMS_TCP_ClientDlg::OnQueryDragIcon()
{

	return static_cast<HCURSOR>(m_hIcon);
}



void CSMS_TCP_ClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	CString SendData;

	KillTimer(1);

	CTime timeNow = CTime::GetCurrentTime();
	UpdateData(true);

	CSocket m_socket01;//Socket Step02
	m_socket01.Create();//Socket Step03
	bool check = m_socket01.Connect("192.168.0.102", 10006);
	if (check == true)
	{

		SendData.Format("%s%s", "0932639162:0:", timeNow.Format("%Y/%m/%d %H:%M:%S"));
		m_socket01.Send(SendData.GetBuffer(0), SendData.GetLength());//Socket Step04
		
		char szRecv[20];
		m_socket01.Receive(szRecv, 20);//Socket Step04

		m_StrNowTime = timeNow.Format("%Y/%m/%d %H:%M:%S")+ "\n" +SendData+"\n"+ szRecv;
		
		m_socket01.Close();//Socket Step05
	}

	UpdateData(false);

	SetTimer(1, 30000, NULL);//開啟Timer
	CDialogEx::OnTimer(nIDEvent);
}
