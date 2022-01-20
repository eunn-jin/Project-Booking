// Login.cpp: 구현 파일
//

#include "pch.h"
#include "LockerReservation.h"
#include "Login.h"
#include "afxdialogex.h"
#include "LockerReservationDlg.h"


// Login 대화 상자

IMPLEMENT_DYNAMIC(Login, CDialogEx)

Login::Login(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{

}

Login::~Login()
{
    
}

void Login::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_ID, m_edit_id);
    DDX_Control(pDX, IDC_EDIT_PW, m_edit_pw);
}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_BN_CLICKED(IDOK, &Login::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &Login::OnBnClickedCancel)
END_MESSAGE_MAP()


// Login 메시지 처리기


void Login::OnBnClickedOk()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    SOCKET h_socket = ((CLockerReservationDlg*)GetParent())->h_socket;
    CString ID, PW;
    char buf[BUFSIZ], pChar[BUFSIZ];
    int num = 0;
    char c_id[BUFSIZ], c_pw[BUFSIZ];
    char* temp;
    memset(buf, 0, BUFSIZ);

    m_edit_id.GetWindowTextA(ID);   //ID값 읽어오기
    m_edit_pw.GetWindowTextA(PW);   //PW값 읽어오기
    
    strcpy(c_id, (LPSTR)(LPCTSTR)ID);
    strcpy(c_pw, (LPSTR)(LPCTSTR)PW);

    sprintf(pChar, "%s,%s.", c_id, c_pw);  //ID, PW 합치기
    send(h_socket, pChar, BUFSIZ-1, NULL);  //Server로 전송
    
    num = recv(h_socket, buf, BUFSIZ-1, NULL);
    
    if (num < 0)
    {
        AfxMessageBox("client: receive error");
    }
    
    temp = strtok(buf, ",");
    if (strcmp(temp, "Success") == 0)
    {
        strcpy(((CLockerReservationDlg*)GetParent())->My_ID, c_id);
        CDialogEx::OnOK();
    }
    else
    {
        AfxMessageBox("로그인에 실패했습니다.");
    }

}


void Login::OnBnClickedCancel()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    CDialogEx::OnCancel();
}

