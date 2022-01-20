
// LockerReservationDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "LockerReservation.h"
#include "LockerReservationDlg.h"
#include "afxdialogex.h"
#include "Login.h"
#include "CheckChoice.h"
#include "CheckCancle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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


// CLockerReservationDlg 대화 상자



CLockerReservationDlg::CLockerReservationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOCKERRESERVATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLockerReservationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLockerReservationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLockerReservationDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCLE, &CLockerReservationDlg::OnBnClickedButtonCancle)
	ON_BN_CLICKED(IDC_BUTTON1, &CLockerReservationDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLockerReservationDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CLockerReservationDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CLockerReservationDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CLockerReservationDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CLockerReservationDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CLockerReservationDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CLockerReservationDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CLockerReservationDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CLockerReservationDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CLockerReservationDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CLockerReservationDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CLockerReservationDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CLockerReservationDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CLockerReservationDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CLockerReservationDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CLockerReservationDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON18, &CLockerReservationDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON19, &CLockerReservationDlg::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON20, &CLockerReservationDlg::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON21, &CLockerReservationDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CLockerReservationDlg::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON23, &CLockerReservationDlg::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, &CLockerReservationDlg::OnBnClickedButton24)
END_MESSAGE_MAP()


// CLockerReservationDlg 메시지 처리기

BOOL CLockerReservationDlg::OnInitDialog()
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

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	h_socket = socket(AF_INET, SOCK_STREAM, 0);//소켓 생성
	memset(&srv_addr, 0, sizeof(struct sockaddr_in));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	srv_addr.sin_port = htons(PORT);
	int res = connect(h_socket, (LPSOCKADDR)&srv_addr, sizeof(srv_addr));
	if (res == 0)
	{
		Login LoginDialog;
		INT_PTR Lcheck = LoginDialog.DoModal();
		if (Lcheck == IDOK)
		{
			;
		}
		else if (Lcheck == IDCANCEL)
		{
			::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
		}
	}
	else
	{
		::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
	}
	
	CLockerReservationDlg::OnBnClickedOk();
	CLockerReservationDlg::GetMynum();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CLockerReservationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLockerReservationDlg::OnPaint()
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
HCURSOR CLockerReservationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CLockerReservationDlg::Doublecheck(char* l_num)	//사물함 예약 함수, return이 1이면 성공, 0이면 예약 실패
{
	int num;
	char textbuf[BUFSIZ];
	memset(textbuf, 0, BUFSIZ);

	num = recv(h_socket, textbuf, BUFSIZ - 1, NULL);
	if (num < 0)
	{
		AfxMessageBox("doublecheck error");
	}
	textbuf[num] = '\0';

	if (strncmp(textbuf, "OKRL",4) == 0)
	{
		memset(textbuf, 0, BUFSIZ);
		num = recv(h_socket, textbuf, 3, NULL);
		if (num < 0)
		{
			AfxMessageBox("doublecheck error");
		}
		textbuf[num] = '\0';
		
		if (strncmp(textbuf, "ORL",3) == 0)
		{
			CheckChoice Checkchoice;
			Checkchoice.lock_num = l_num;
			INT_PTR Lcheck = Checkchoice.DoModal();
			if (Lcheck == IDOK)	//모달에서 YES눌렀을 경우
			{
				send(h_socket, "YS", 2, 0);
				num = recv(h_socket, textbuf, 2, 0);
				if (num < 0)
				{
					AfxMessageBox("double check 3 error");
				}
				textbuf[num] = '\0';
				if (strcmp(textbuf, "NO") == 0)	//모달까지 넘어갔지만, 다른 사람이 겹쳐서 먼저 예약했을 경우
				{
					AfxMessageBox("이미 선택된 사물함입니다.");
					return 0;
				}
				return 1;	//사물함 예약 성공
			}
			else if (Lcheck == IDCANCEL)	//모달에서 NO눌렀을 경우
			{
				send(h_socket, "NO", 2, 0);
				return 0;
			}
		}
		else //이미 선택된 사물함일 경우
		{
			AfxMessageBox("이미 선택된 사물함입니다.");
			return 0;
		}
	}
	else if (strncmp(textbuf, "NORL",4) == 0)	//이미 예약된 사물함일 경우
	{
		AfxMessageBox("이미 예약을 한 사물함이 있습니다.");
		return 0;
	}
	else
	{
		return 0;
	}
}

void CLockerReservationDlg::OnBnClickedOk()	//새로고침 버튼
{
	char *sign, *ptr;
	char textbuf[BUFSIZ];
	int num;
	
	sign = "UD";

	memset(textbuf, 0, BUFSIZ);
	sprintf(textbuf, "%s,", sign);
	send(h_socket, textbuf, BUFSIZ-1, NULL);
	
	memset(textbuf, 0, BUFSIZ);
	num = recv(h_socket, textbuf, BUFSIZ-1, 0);
	if (num < 0)
	{
		AfxMessageBox("Client receive error");
	}
	textbuf[num] = '\0';
	ptr = strtok(textbuf, ",");

	for (int j = 0; j < LOCKERNUM; j++)
	{
		ptr = strtok(NULL, ",");
		if (ptr != NULL)
		{
			num = atoi(ptr);
			Locker[j] = num;
		}
		else
		{
			break;
		}
	}

	ButtonBlock();
}

void CLockerReservationDlg::ButtonBlock()
{
	int j;
	int btnType;

	for (j = 0; j < LOCKERNUM; j++)
	{
		if (Locker[j] != 0)
		{
			btnType = IDC_BUTTON1 + j;
			GetDlgItem(btnType)->EnableWindow(FALSE);
		}
		else
		{
			btnType = IDC_BUTTON1 + j;
			GetDlgItem(btnType)->EnableWindow(TRUE);
		}
	}
}

void CLockerReservationDlg::GetMynum()
{
	char* ptr;
	char textbuf[BUFSIZ];
	
	memset(textbuf, 0, BUFSIZ);
	sprintf(textbuf, "WN,%s.", My_ID);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	memset(textbuf, 0, BUFSIZ);
	int num = recv(h_socket, textbuf, BUFSIZ - 1, 0);
	if (num < 0)
	{
		AfxMessageBox("Client receive error");
	}
	textbuf[num] = '\0';
	ptr = strtok(textbuf, ",");
	if (strcmp(ptr, "OK") == 0)
	{
		ptr = strtok(NULL, ",");
		My_num = atoi(ptr);
		sprintf(textbuf, "내 사물함 번호:%d ", My_num);
		SetDlgItemText(IDC_STATIC_MY, textbuf);
	}
}

void CLockerReservationDlg::OnBnClickedButtonCancle()	//예약취소 버튼
{
	CheckCancle Checkcancle;
	INT_PTR Lcheck = Checkcancle.DoModal();
	if (Lcheck == IDOK)	//모달에서 YES눌렀을 경우
	{
		char* sign;
		char textbuf[BUFSIZ];
		sign = "CL";

		memset(textbuf, 0, BUFSIZ);
		sprintf(textbuf, "%s,%s.", sign, My_ID);
		send(h_socket, textbuf, BUFSIZ - 1, NULL);

		memset(textbuf, 0, BUFSIZ);
		int num = recv(h_socket, textbuf, BUFSIZ - 1, 0);
		if (num < 0)
		{
			AfxMessageBox("Client receive error");
		}
		textbuf[num] = '\0';
		if (strcmp(textbuf, "OKCL") == 0)
		{
			SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 00");
			My_num = 0;
		}
		else if (strcmp(textbuf, "NOCL") == 0)
		{
			AfxMessageBox("예약한 사물함이 없습니다.");
		}
	}
	else if (Lcheck == IDCANCEL)	//모달에서 NO눌렀을 경우
	{
		;
	}

	CLockerReservationDlg::OnBnClickedOk();
}

void CLockerReservationDlg::OnBnClickedButton1()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 1);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("01");
	if (check == 1)
	{
		My_num = 1;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 01");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton2()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 2);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("02");
	if (check == 1)
	{
		My_num = 2;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 02");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton3()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 3);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("03");
	if (check == 1)
	{
		My_num = 3;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 03");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton4()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 4);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("04");
	if (check == 1)
	{
		My_num = 4;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 04");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton5()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 5);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("05");
	if (check == 1)
	{
		My_num = 5;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 05");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton6()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 6);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("06");
	if (check == 1)
	{
		My_num = 6;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 06");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton7()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 7);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("07");
	if (check == 1)
	{
		My_num = 7;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 07");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton8()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 8);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("08");
	if (check == 1)
	{
		My_num = 8;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 08");
	}

	CLockerReservationDlg::OnBnClickedOk();
}

void CLockerReservationDlg::OnBnClickedButton9()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 9);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("09");
	if (check == 1)
	{
		My_num = 9;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 09");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton10()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 10);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("10");
	if (check == 1)
	{
		My_num = 10;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 10");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton11()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 11);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("11");
	if (check == 1)
	{
		My_num = 11;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 11");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton12()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 12);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("12");
	if (check == 1)
	{
		My_num = 12;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 12");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton13()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 13);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("13");
	if (check == 1)
	{
		My_num = 13;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 13");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton14()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 14);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("14");
	if (check == 1)
	{
		My_num = 14;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 14");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton15()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 15);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("15");
	if (check == 1)
	{
		My_num = 15;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 15");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton16()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 16);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("16");
	if (check == 1)
	{
		My_num = 16;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 16");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton17()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 17);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("17");
	if (check == 1)
	{
		My_num = 17;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 17");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton18()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 18);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("18");
	if (check == 1)
	{
		My_num = 18;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 18");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton19()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 19);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("19");
	if (check == 1)
	{
		My_num = 19;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 19");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton20()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 20);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("20");
	if (check == 1)
	{
		My_num = 20;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 20");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton21()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 21);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("21");
	if (check == 1)
	{
		My_num = 21;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 21");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton22()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 22);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("22");
	if (check == 1)
	{
		My_num = 22;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 22");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton23()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 23);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("23");
	if (check == 1)
	{
		My_num = 23;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 23");
	}

	CLockerReservationDlg::OnBnClickedOk();
}


void CLockerReservationDlg::OnBnClickedButton24()
{
	char* sign;
	char textbuf[BUFSIZ];
	sign = "RL";
	memset(textbuf, 0, BUFSIZ);

	sprintf(textbuf, "%s,%s,%d.", sign, My_ID, 24);
	send(h_socket, textbuf, BUFSIZ - 1, NULL);

	int check = Doublecheck("24");
	if (check == 1)
	{
		My_num = 24;
		SetDlgItemText(IDC_STATIC_MY, "내 사물함 번호: 24");
	}

	CLockerReservationDlg::OnBnClickedOk();
}
