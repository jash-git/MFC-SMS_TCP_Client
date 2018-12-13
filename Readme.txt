利用MFC撰寫TCP簡訊發送程式

功能
	01.MFC+TIMER顯示目前時間
	02.CSOCKT每30秒發送一次連線 -> 傳送一次簡訊
		#include <afxsock.h>		// MFC socket extensions //Socket Step00
		
		if (!AfxSocketInit())
		{
			AfxMessageBox("Failed to Initialize Sockets");//Socket Step01
			return FALSE;
		}
		
		CSocket m_socket01;//Socket Step02
		
		m_socket01.Create();//Socket Step03
		
		m_socket01.Send(SendData.GetBuffer(0), SendData.GetLength());//Socket Step04
		
		char szRecv[20];
		m_socket01.Receive(szRecv, 20);//Socket Step04
		
		m_socket01.Close();//Socket Step05		
	03.每三秒偵測一次檔案，如果有新檔案就把檔案內容傳送給設備發送簡訊
	04.修改目錄名稱 SMS_DATA -> smstxt1
	05.離開按鈕實現
	06.SERVER 資訊讀取檔案
	07.30秒防呆指令	