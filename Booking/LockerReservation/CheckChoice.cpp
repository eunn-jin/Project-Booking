// CheckChoice.cpp: 구현 파일
//

#include "pch.h"
#include "LockerReservation.h"
#include "CheckChoice.h"
#include "afxdialogex.h"


// CheckChoice 대화 상자

IMPLEMENT_DYNAMIC(CheckChoice, CDialog)

CheckChoice::CheckChoice(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_CHECK_CHOICE, pParent)
{

}

CheckChoice::~CheckChoice()
{
}

void CheckChoice::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	char str[BUFSIZ];
	wsprintf(str, "%s번 사물함을 예약하시겠습니까?", lock_num);
	SetDlgItemText(IDC_STATIC, str);
}


BEGIN_MESSAGE_MAP(CheckChoice, CDialog)
END_MESSAGE_MAP()


// CheckChoice 메시지 처리기
