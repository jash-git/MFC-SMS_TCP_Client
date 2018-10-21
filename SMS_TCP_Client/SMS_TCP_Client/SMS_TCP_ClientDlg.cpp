
// SMS_TCP_ClientDlg.cpp : ��@��
//

#include "stdafx.h"
#include "SMS_TCP_Client.h"
#include "SMS_TCP_ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSMS_TCP_ClientDlg ��ܤ��



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


// CSMS_TCP_ClientDlg �T���B�z�`��

BOOL CSMS_TCP_ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	ShowWindow(SW_MINIMIZE);

	// TODO: �b���[�J�B�~����l�]�w
	SetTimer(1, 1000, NULL);//�}��Timer
	
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CSMS_TCP_ClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CSMS_TCP_ClientDlg::OnQueryDragIcon()
{

	return static_cast<HCURSOR>(m_hIcon);
}



void CSMS_TCP_ClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
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

	SetTimer(1, 30000, NULL);//�}��Timer
	CDialogEx::OnTimer(nIDEvent);
}
