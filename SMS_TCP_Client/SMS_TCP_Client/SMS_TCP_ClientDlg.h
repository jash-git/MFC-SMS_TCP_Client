
// SMS_TCP_ClientDlg.h : ���Y��
//

#pragma once


// CSMS_TCP_ClientDlg ��ܤ��
class CSMS_TCP_ClientDlg : public CDialogEx
{
// �غc
public:
	CSMS_TCP_ClientDlg(CWnd* pParent = NULL);	// �зǫغc�禡

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SMS_TCP_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_StrNowTime;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
