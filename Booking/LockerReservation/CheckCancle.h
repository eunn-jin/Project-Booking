#pragma once


// CheckCancle 대화 상자

class CheckCancle : public CDialogEx
{
	DECLARE_DYNAMIC(CheckCancle)

public:
	CheckCancle(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CheckCancle();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHECK_CANCLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
