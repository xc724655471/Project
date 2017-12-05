// LoginWind.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "LoginWind.h"
#include "afxdialogex.h"


// LoginWind dialog

IMPLEMENT_DYNAMIC(LoginWind, CDialogEx)

LoginWind::LoginWind(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
{
	//GetDlgItem(IDC_IPADDRESS_DEVICE_IP)->SetWindowTextW(_T("192.168.0.252"));
	//GetDlgItem(IDC_EDIT_DEVICE_PORT)->SetWindowTextW(_T("8000"));
	//GetDlgItem(IDC_EDIT_DEVICE_USERNAME)->SetWindowTextW(_T("admin"));
	//GetDlgItem(IDC_EDIT_DEVICE_PASSWORD)->SetWindowTextW(_T("Changeme"));
}

LoginWind::~LoginWind()
{
}

void LoginWind::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_IPADDRESS_DEVICE_IP, m_IP);
	//  DDX_Control(pDX, IDC_EDIT_DEVICE_NAME, m_IP);
	//  DDX_Control(pDX, IDC_EDIT_DEVICE_NAME, m_Name);
}


BEGIN_MESSAGE_MAP(LoginWind, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &LoginWind::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// LoginWind message handlers


void LoginWind::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here
	 GetDlgItem(IDC_IPADDRESS_DEVICE_IP)->GetWindowTextW(m_IP);
	 GetDlgItem(IDC_EDIT_DEVICE_PORT)->GetWindowTextW(m_Port);
	 GetDlgItem(IDC_EDIT_DEVICE_USERNAME)->GetWindowTextW(m_Username);
	 GetDlgItem(IDC_EDIT_DEVICE_PASSWORD)->GetWindowTextW(m_Password);
	 CDialog::OnOK();
}


BOOL LoginWind::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	GetDlgItem(IDC_IPADDRESS_DEVICE_IP)->SetWindowTextW(_T("192.168.0.254"));
	GetDlgItem(IDC_EDIT_DEVICE_PORT)->SetWindowTextW(_T("8000"));
	GetDlgItem(IDC_EDIT_DEVICE_USERNAME)->SetWindowTextW(_T("admin"));
	GetDlgItem(IDC_EDIT_DEVICE_PASSWORD)->SetWindowTextW(_T("admin172"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
