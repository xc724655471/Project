#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// LoginWind dialog

class LoginWind : public CDialogEx
{
	DECLARE_DYNAMIC(LoginWind)

public:
	LoginWind(CWnd* pParent = NULL);   // standard constructor
	virtual ~LoginWind();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	CIPAddressCtrl m_IP;
//	CEdit m_IP;
//	CEdit m_Name;
	CString m_name;
	CString m_IP;
	CString m_Port;
	CString m_Username;
	CString m_Password;

	afx_msg void OnBnClickedButtonOk();
	virtual BOOL OnInitDialog();
};
