#pragma once
#include "afxwin.h"

#include"ShowWind.h"
#include"Message.h"
#include"MyStatic.h"

// PreviewWind dialog

class PreviewWind : public CDialogEx
{
	DECLARE_DYNAMIC(PreviewWind)

public:
	PreviewWind(CWnd* pParent = NULL);   // standard constructor
	virtual ~PreviewWind();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VIDEOSHOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	CStatic m_show1;
//	CStatic m_show2;
	void CreateShowWind(CRect rect,int num);


	//CStatic m_wndShow[WIND_MAX_NUM];


	MyStatic m_wind[WIND_MAX_NUM];
	//ShowWind m_wind[WIND_MAX_NUM];
	//CSplitterWnd m_splitterwnd1;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	int m_width;//�������ڿ��
	int m_height;//�������ڸ߶�
	int m_num;//һ�д��ڸ���
	virtual BOOL OnInitDialog();
	void DrawFrame( );
	void DrawFrame(bool);
	int m_allwindnum;//���д��ڸ���
	afx_msg void OnPaint();
	int m_currentwindnum;//��ǰ����id
};
