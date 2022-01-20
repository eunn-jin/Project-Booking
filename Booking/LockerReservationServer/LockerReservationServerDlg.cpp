
// LockerReservationServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "LockerReservationServer.h"
#include "LockerReservationServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CListBox CLockerReservationServerDlg::m_list_context;
SOCKET CLockerReservationServerDlg::ClientSocket;
t_Locker* CLockerReservationServerDlg::Locker_p;
std::mutex locker_mutex;
std::mutex list_mutex;
std::mutex button_mutex;
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLockerReservationServerDlg 대화 상자

CLockerReservationServerDlg::CLockerReservationServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOCKERRESERVATIONSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLockerReservationServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Context, m_list_context);
}

BEGIN_MESSAGE_MAP(CLockerReservationServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLockerReservationServerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLockerReservationServerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLockerReservationServerDlg 메시지 처리기

BOOL CLockerReservationServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	//소켓 생성
	m_listen_socket = socket(AF_INET, SOCK_STREAM, 0);	//TCP사용
	if (m_listen_socket == INVALID_SOCKET)
	{
		MessageBox("서버 소켓 생성 실패");
		return TRUE;
	}
	
	memset(&srv_addr, 0, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);	//모든 address 허용
	srv_addr.sin_port = htons(PORT);
	
	if (bind(m_listen_socket, (sockaddr*)&srv_addr, sizeof(srv_addr)) == SOCKET_ERROR)
	{
		MessageBox("BIND ERROR");
		return TRUE;
	}
	
	if (listen(m_listen_socket, MAXCLIENT) == SOCKET_ERROR)
	{
		MessageBox("Listen ERROR");
		return TRUE;
	}
	
	Locker_p = new t_Locker[LOCKERNUM];

	LoadFileReservation();
	AfxBeginThread(AcceptFunc, this);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CLockerReservationServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CLockerReservationServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CLockerReservationServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLockerReservationServerDlg::OnLbnSelchangeListContext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

UINT CLockerReservationServerDlg::AcceptFunc(LPVOID pParam)
{
	CLockerReservationServerDlg* pDlg = (CLockerReservationServerDlg*)pParam;
	
	while (TRUE)
	{
		char str[BUFSIZ];
		SOCKADDR_IN addr;
		memset(&addr, 0, sizeof(addr));
		int iAddrLen = sizeof(addr);
		ClientSocket = accept(pDlg->m_listen_socket, (sockaddr*)&addr, &iAddrLen);
		if (ClientSocket == INVALID_SOCKET)
		{
			AfxMessageBox("Accept Error");
			continue;
		}
		sprintf(str, "%s[%d]가 연결되었습니다.", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
		AddEventString(str);

		AfxBeginThread(RecvFunc, new CRecvParam(pDlg, ClientSocket));

	}
}

UINT CLockerReservationServerDlg::RecvFunc(LPVOID pParam)
{
	CRecvParam* p = (CRecvParam*)pParam;
	CLockerReservationServerDlg* pDlg = p->m_pDlg;
	SOCKET ClientSocket = p->m_ClientSocket;
	
	char *sign, *ptr;
	char Client_id[BUFSIZ], Client[BUFSIZ], lock_num[BUFSIZ];
	int check = 0;	int iRecvLen = 0; int res = 0;
	char rectemp[BUFSIZ];	char rectext[BUFSIZ];
	char* sendtext;	char test[BUFSIZ];

	while (TRUE)
	{	
		iRecvLen = recv(ClientSocket, rectemp, BUFSIZ-1, NULL);
		if (iRecvLen <= 0)
		{
			break;
		}
		else
		{
			rectemp[iRecvLen] = '\0';
			ptr = strtok(rectemp, ",");
			strcpy(Client_id, ptr);
			ptr = strtok(NULL, ".");
			strcpy(Client, ptr);
			
			check = checkLogin(Client_id, Client);
			if (check == 1)	//로그인 성공
			{
				sendtext = "Success";
				sendtext = LockerState(sendtext);
				sprintf(sendtext, "%s.", sendtext);
				send(ClientSocket, sendtext, BUFSIZ-1, NULL);
				break;
			}
			else
			{
				send(ClientSocket, "No,", BUFSIZ - 1, NULL);
			}
		}
	}

	while (TRUE)
	{
		memset(rectemp, 0, BUFSIZ);
		iRecvLen = recv(ClientSocket, rectemp, BUFSIZ - 1, NULL);
		if (iRecvLen <= 0)
		{
			sprintf(rectemp, "%s가 종료하였습니다.", Client_id);
			AddEventString(rectemp);
			break;
		}

		rectemp[iRecvLen] = '\0';
		ptr = strtok(rectemp, ",");
		sign = ptr;
		
		if (strcmp(sign, "RL") == 0)
		{
			ptr = strtok(NULL, ",");
			strcpy(Client, ptr);

			check = checkname(Client);
			if (check == 0)
			{
				ptr = strtok(NULL, ".");
				strcpy(lock_num, ptr);
				send(ClientSocket, "OKRL", 4, 0);
				check = checklock(lock_num);
				if (check == 0)
				{
					res = pDlg->ReservationFunc(Client, lock_num, ClientSocket);
					if (res == 2) //성공
					{
						sprintf(sendtext, "%s가 %s번 사물함을 예약하였습니다.", Client, lock_num);
						AddEventString(sendtext);
					}
					else if (res == 1)	//모달에서 no가 들어왔을때
					{
						;
					}
					else //안에서 동시에 접근했을때...
					{
						send(ClientSocket, "NRL", 3, 0);
					}
				}
				else
				{
					send(ClientSocket, "NRL", 3, 0);
				}
			}
			else //이미 예약을 한 사물함이 있다.
			{
				send(ClientSocket, "NORL", 4, 0);
			}
		}
		else if (strcmp(sign, "UD") == 0)
		{
			sendtext = LockerState(sign);
			sprintf(sendtext, "%s,", sendtext);
			send(ClientSocket, sendtext, BUFSIZ - 1, NULL);
		}
		else if (strcmp(sign, "CL") == 0)
		{
			ptr = strtok(NULL, ".");
			strcpy(Client, ptr);
			check = checkname(Client);
			if (check != 0)
			{
				Locker_p[check - 1].locker_num = 0;
				send(ClientSocket, "OKCL", 4, 0);
				sprintf(sendtext, "%s가 %d번 사물함을 취소하였습니다.", Client, check);
				AddEventString(sendtext);
				pDlg->loadState();
			}
			else
			{
				send(ClientSocket, "NOCL", 4, 0);
			}
		}
		else if (strcmp(sign, "WN") == 0)
		{
			ptr = strtok(NULL, ".");
			strcpy(Client, ptr);
			check = checkname(Client);
			if (check != 0)
			{
				sprintf(sendtext, "OK,%d.", check);
				send(ClientSocket, sendtext, BUFSIZ-1, 0);
			}
			else
			{
				send(ClientSocket, "NO", 2, 0);
			}
		}

	}

	return 0;
}

int CLockerReservationServerDlg::ReservationFunc(char* Client_id, char* lock_num, SOCKET ClientSocket)
{
	int l_num;
	int res = 0;	int j = 0;
	l_num = atoi(lock_num);
	char buf[BUFSIZ];
	
	for (j = 0; j < LOCKERNUM; j++)
	{
		if (j == (l_num-1))
		{
			if (!locker_mutex.try_lock())
			{
				break;
			}
			send(ClientSocket, "ORL", 3, 0);

			if (Locker_p[j].locker_num == 0)
			{
				int num = recv(ClientSocket, buf, 2, 0);
				buf[num] = '\0';
				if (strncmp(buf, "YS", 2) == 0)
				{
					Locker_p[j].locker_num = j + 1;
					strcpy(Locker_p[j].user, Client_id);
					send(ClientSocket, "OK", 2, 0);
					loadState();
					res = 2;
				}
				else //예약 취소
				{
					res = 1;
				}
			}
			else
			{
				send(ClientSocket, "NO", 2, 0);	//예약된 사물함
				res = 0;
			}
			locker_mutex.unlock();
		}

		if (res != 0)
		{
			break;
		}
	}

	return res;
}

void CLockerReservationServerDlg::loadState()
{
	button_mutex.lock();

	int num, btnType;

	for (int j = 0; j < LOCKERNUM; j++)
	{
		num = Locker_p[j].locker_num;
		if (num == 0)
		{
			btnType = IDC_BUTTON1 + j;
			GetDlgItem(btnType)->EnableWindow(TRUE);
		}
		else
		{
			btnType = IDC_BUTTON1 + j;
			GetDlgItem(btnType)->EnableWindow(FALSE);
		}
	}

	button_mutex.unlock();
}

int CLockerReservationServerDlg::checklock(char* lock_num)
{
	int num = atoi(lock_num);

	if (Locker_p[num - 1].locker_num == 0)	//비어있는 사물함이다
	{
		return 0;
	}
	else //이미 예약되어있는 사물함이다
	{
		return num;
	}
}

int CLockerReservationServerDlg::checkname(char* Client_id)
{
	int j = 0;
	for (j = 0; j < LOCKERNUM; j++)
	{
		if (Locker_p[j].locker_num != 0)
		{
			if (strcmp(Locker_p[j].user, Client_id) == 0)
			{
				return (j + 1);	//이름이 있다.
			}
		}
	}

	return 0;	//이름이 없다
}


int CLockerReservationServerDlg::checkLogin(char* Client_id, char* Client_pw)
{
	char buffer[BUFSIZ], * ps;
	char *strID, *strPW;
	char text[BUFSIZ];
	CString m_strPath;
	CFileDialog dlg(FALSE, _T("*.txt"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.txt)|*.txt|"), NULL);

	m_strPath = dlg.GetPathName();

	if (m_strPath.Right(4) != ".txt")
	{
		m_strPath += "IDList.txt";
	}

	FILE* stream = fopen(m_strPath, "r");
	if (stream == NULL) return 0;

	while (fgets(buffer, BUFSIZ-1, stream) != NULL) // 텍스트파일을 한줄씩 읽습니다.
	{
		ps = strchr(buffer, '\n'); // 제일 뒤쪽의 new line의 char을 찿아.
		if (ps != NULL) *ps = '\0';// new line의 char을 null문자로 바꿉니다.

		strID = strtok(buffer, ",");
		strPW = strtok(NULL, ".");

		if (strcmp(Client_id, strID) == 0)
		{
			if (strcmp(Client_pw, strPW) == 0)
			{
				sprintf(text, "%s가 접속했습니다. ", strID);
				AddEventString(text);

				return 1;
			}
		}
	}

	fclose(stream);
	return 0;
}

void CLockerReservationServerDlg::AddEventString(const char* ap_string)	//list의 맨 아래에 새로운 글 추가
{
	list_mutex.lock();
	
	int index = m_list_context.InsertString(-1, ap_string);
	m_list_context.SetCurSel(index);

	list_mutex.unlock();
}

void CLockerReservationServerDlg::LoadFileReservation()	//사물함 상태 파일에서 가져오기
{
	char buffer[BUFSIZ];
	char *state, *ps;
	int i = 0;
	CString m_strPath;
	CFileDialog dlg(FALSE, _T("*.txt"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.txt)|*.txt|"), NULL);

	m_strPath = dlg.GetPathName();

	if (m_strPath.Right(4) != ".txt")
	{
		m_strPath += "result.txt";
	}

	FILE* stream = fopen(m_strPath, "r");
	if (stream == NULL)
	{
		AfxMessageBox("사물함 예약 상황 파일 오픈 에러");
	}

	while (i<LOCKERNUM) // 텍스트파일을 한줄씩 읽습니다.
	{
		fgets(buffer, BUFSIZ, stream);
		state = strtok(buffer, ",");

		if (strcmp(state,"0") == 0)
		{
			Locker_p[i].locker_num = 0;
			strcpy(Locker_p[i].user, "0");
		}
		else
		{
			Locker_p[i].locker_num = i + 1;
			state = strtok(NULL, ".");
			strcpy(Locker_p[i].user, state);
		}
		i++;
	}

	fclose(stream);
	loadState();
}

char* CLockerReservationServerDlg::LockerState(char* state)	//현재 사물함 상태 가져오기
{
	int j;
	char temp[BUFSIZ];

	sprintf(temp, "%s", state);

	for (j = 0; j < LOCKERNUM; j++)
	{
		sprintf(temp, "%s,%d", temp, Locker_p[j].locker_num);
	}

	return temp;
}

void CLockerReservationServerDlg::OnBnClickedOk()	//파일에 저장
{
	CString m_strPath;
	CStdioFile file;
	CFileException ex;
	CFileDialog dlg(FALSE, _T("*.txt"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.txt)|*.txt|"), NULL);
	char temp[BUFSIZ];

	m_strPath = dlg.GetPathName();

	if (m_strPath.Right(4) != ".txt")
	{
		m_strPath += "result.txt";
	}

	file.Open(m_strPath, CFile::modeCreate | CFile::modeReadWrite, &ex);
	for (int j = 0; j < LOCKERNUM-1; j++)
	{
		int num = Locker_p[j].locker_num;
		if (num == 0)
		{
			sprintf(temp, "0,0.\n");
		}
		else
		{
			sprintf(temp, "%d,%s.\n", num, Locker_p[j].user);
		}
		file.WriteString(temp);
	}

	int num = Locker_p[LOCKERNUM - 1].locker_num;
	if (num == 0)
	{
		sprintf(temp, "0,0.");
	}
	else
	{
		sprintf(temp, "%d,%s.", num, Locker_p[LOCKERNUM - 1].user);
	}
	file.WriteString(temp);

	file.Close();
}

void CLockerReservationServerDlg::OnBnClickedCancel()
{
	CLockerReservationServerDlg::OnBnClickedOk();	//파일 저장
	CDialogEx::OnCancel();	//종료
	
}
