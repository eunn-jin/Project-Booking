#pragma once


// CheckChoice 대화 상자

class CheckChoice : public CDialog
{
	DECLARE_DYNAMIC(CheckChoice)

public:
	CheckChoice(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CheckChoice();
	char* lock_num;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHECK_CHOICE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
};
