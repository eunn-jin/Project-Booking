// CheckCancle.cpp: 구현 파일
//

#include "pch.h"
#include "LockerReservation.h"
#include "CheckCancle.h"
#include "afxdialogex.h"


// CheckCancle 대화 상자

IMPLEMENT_DYNAMIC(CheckCancle, CDialogEx)

CheckCancle::CheckCancle(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHECK_CANCLE, pParent)
{

}

CheckCancle::~CheckCancle()
{
}

void CheckCancle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CheckCancle, CDialogEx)
END_MESSAGE_MAP()


// CheckCancle 메시지 처리기
