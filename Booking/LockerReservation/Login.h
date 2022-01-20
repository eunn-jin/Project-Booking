#pragma once


// Login 대화 상자

class Login : public CDialogEx
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Login();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DIALOG };
#endif

private:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit m_edit_id;
	CEdit m_edit_pw;
};
