// ShowWind.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "ShowWind.h"
#include "afxdialogex.h"


// ShowWind dialog

IMPLEMENT_DYNAMIC(ShowWind, CDialogEx)

ShowWind::ShowWind(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SHOW, pParent)
{

}

ShowWind::~ShowWind()
{
}

void ShowWind::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ShowWind, CDialogEx)
END_MESSAGE_MAP()


// ShowWind message handlers
