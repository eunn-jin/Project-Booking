
// LockerReservationServerDlg.h: 헤더 파일
//

#pragma once
#define MAXCLIENT 50
#define PORT 18000
#define LOCKERNUM 24
#define BUFSIZ 1024

static struct t_Locker
{
	int locker_num;
	char user[BUFSIZ];
};

// CLockerReservationServerDlg 대화 상자
class CLockerReservationServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CLockerReservationServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOCKERRESERVATIONSERVER_DIALOG };
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

private:
	SOCKET m_listen_socket;
	sockaddr_in srv_addr;
	CList<SOCKET> m_ClientSocketList;

public:
	afx_msg void OnLbnSelchangeListContext();
	static UINT CLockerReservationServerDlg::AcceptFunc(LPVOID pParam);
	static UINT CLockerReservationServerDlg::RecvFunc(LPVOID pParam);

protected:
	static int CLockerReservationServerDlg::checkLogin(char* Client_id, char* Client_pw);
	static void AddEventString(const char* ap_string);
	void CLockerReservationServerDlg::LoadFileReservation();
	static char* CLockerReservationServerDlg::LockerState(char* state);
	int CLockerReservationServerDlg::ReservationFunc(char* Client_id, char* lock_num, SOCKET ClientSocket);
	static int CLockerReservationServerDlg::checkname(char* Client_id);
	static int CLockerReservationServerDlg::checklock(char* lock_num);
	void CLockerReservationServerDlg::loadState();

protected:
	static CListBox m_list_context;
	static SOCKET ClientSocket;
	static t_Locker* Locker_p;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};

class CRecvParam
{
public:
	CRecvParam(CLockerReservationServerDlg* pDlg, SOCKET ClientSocket)
		:m_pDlg(pDlg), m_ClientSocket(ClientSocket)
	{}
	~CRecvParam()
	{
		closesocket(m_ClientSocket);
	}
	CLockerReservationServerDlg* m_pDlg;
	SOCKET m_ClientSocket;
};
