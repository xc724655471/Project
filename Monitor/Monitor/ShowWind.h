#pragma once


// ShowWind dialog

class ShowWind : public CDialogEx
{
	DECLARE_DYNAMIC(ShowWind)

public:
	ShowWind(CWnd* pParent = NULL);   // standard constructor
	virtual ~ShowWind();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SHOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
