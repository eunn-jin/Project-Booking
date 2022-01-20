
// LockerReservationDlg.h: 헤더 파일
//

#pragma once
#define BUFSIZ 1024
#define LOCKERNUM 24
#define PORT 18000

// CLockerReservationDlg 대화 상자
class CLockerReservationDlg : public CDialogEx
{
// 생성입니다.
public:
	CLockerReservationDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOCKERRESERVATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	int CLockerReservationDlg::Doublecheck(char* l_num);
	void CLockerReservationDlg::ButtonBlock();
	void CLockerReservationDlg::GetMynum();

public:
	SOCKET h_socket;
	sockaddr_in srv_addr;
	char My_ID[BUFSIZ];
	int My_num = 0;
	int Locker[LOCKERNUM] = { 0, };

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonCancle();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton21();
	afx_msg void OnBnClickedButton22();
	afx_msg void OnBnClickedButton23();
	afx_msg void OnBnClickedButton24();
};
