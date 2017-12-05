// PreviewWind.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "PreviewWind.h"
#include "afxdialogex.h"


// PreviewWind dialog

IMPLEMENT_DYNAMIC(PreviewWind, CDialogEx)

PreviewWind::PreviewWind(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VIDEOSHOW, pParent)
	, m_width(0)//198
	, m_height(0)//251
	, m_allwindnum(0)//4
	, m_currentwindnum(0)
{

}

PreviewWind::~PreviewWind()
{
}

void PreviewWind::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_STATIC_SHOW1, m_show1);
	//  DDX_Control(pDX, IDC_STATIC_SHOW2, m_show2);
}


BEGIN_MESSAGE_MAP(PreviewWind, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// PreviewWind message handlers

/*************************************************
Function:CreateShowWind
Description:创建显示窗口
Input:	CRect rect  显示窗口区域
		int windnum  显示窗口个数
Output:
Return:
Others:
*************************************************/
void PreviewWind::CreateShowWind(CRect rect,int windnum)
{

	for (int i = 0; i < WIND_MAX_NUM; i++)
		//m_w
		//		m_wndShow[i].ShowWindow(false);
		m_wind[i].ShowWindow(false);
	int num = sqrt(windnum);
	int allwidth = rect.Width();
	int allheight = rect.Height();
	int width = allwidth / num;
	int height = allheight / num;
	m_width = width;
	m_height = height;
	m_num = num;
	m_allwindnum = windnum;
	m_currentwindnum = 0;

	for (int i = 0; i < windnum; i++)
	{
		int x = i % num;
		int y = i / num;
		RECT rc;
		rc.left = x * width;
		rc.right = x * width + width-3;
		rc.top = y * height;
		rc.bottom = y * height + height-3;
		CString text;
		text.Format(_T("%d"), i);
		//MessageBox(text);


		m_wind[i].SetWindowTextW(text);//编号
		m_wind[i].MoveWindow(&rc);//移动
		m_wind[i].ShowWindow(true);//显示
	}
	DrawFrame();//

}

/*************************************************
Function:OnLButtonDown
Description:鼠标左键点击确定当前选中窗口
Input:	

Output:
Return:
Others:
*************************************************/
void PreviewWind::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default


	//int x = point.x;
	//int y = point.y;

	int numx = point.x / m_width;
	int numy = point.y / m_height;
	 m_currentwindnum = numx + numy * m_num;
	// MessageBox(_T("ok"));



		//HWND hwnd = ::GetParent(m_hWnd);
		//HWND * hwnd = this->GetParent()->GetParent();
		HWND hwnd=this->GetParent()->GetParent()->GetSafeHwnd();

		::SendMessage(hwnd, WM_CURRENT_WIND_NUM, (WPARAM)m_currentwindnum, 0);
		//m_wind[m_currentwindnum].isCurrentWind = true;
		DrawFrame();

	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL PreviewWind::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	for (int i = 0; i < WIND_MAX_NUM; i++)
	{

		RECT rc;

		CString text;

		m_wind[i].Create(text, WS_VISIBLE | WS_CHILD, rc, this, IDD_DIALOG_VIDEOSHOW + i);
		m_wind[i].ShowWindow(false);

	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

/*************************************************
Function:DrawFrame
Description:绘制窗口边框函数
Input:

Output:
Return:
Others:
*************************************************/
void PreviewWind::DrawFrame( )
{

	//if (!IsWindowVisible())
	//{
	//	return;
	//}

	for (int i = 0; i < m_allwindnum; i++)
	{
		if (i == m_currentwindnum)
			m_wind[i].isCurrentWind = true;
		else
			m_wind[i].isCurrentWind = false;
			//pPen.CreatePen(PS_SOLID, 2, RGB(125, 125, 116));
//		m_wndShow[i].GetClientRect(&rc);
//
//
////		m_wndShow[i].GetSafeHwnd.Invalidate(false);
//
//		CDC *pDC = m_wndShow[i].GetDC();
//		
//		//CWindowDC*pDC= m_wndShow[i].dc;
//		//CPaintDC *pDC = this->m_wndShow[i].GetDC();
//
//		//this->m_wndShow[i].GetDC();
//
//
//		pDC->SelectStockObject(NULL_BRUSH);
//
//		pOldPen = pDC->SelectObject(&pPen);
//		pDC->Rectangle(&rc);
//		if (pOldPen)
//		{
//			pDC->SelectObject(pOldPen);
//		}
//
//		ReleaseDC(pDC);



		m_wind[i].Invalidate();



	}
	//m_wind

}


void PreviewWind::DrawFrame(bool i)
{
	if (i)
	{

	for (int i = 0; i < m_allwindnum; i++)
	{
		CPen pPen;
		CRect rc;
		CPen *pOldPen = NULL;

		if (i == m_currentwindnum)
			pPen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));//green
		else
			pPen.CreatePen(PS_SOLID, 2, RGB(125, 125, 116));




		//m_wndShow[i].GetClientRect(&rc);
		///*m_wndShow[i].GetSafeHwnd.Invalidate(false);*/

		//CDC *pDC = m_wndShow[i].GetDC();
		////CWindowDC*pDC= m_wndShow[i].dc;
		////CPaintDC *pDC = this->m_wndShow[i].GetDC();

		////this->m_wndShow[i].GetDC();
		//pDC->MoveTo(rc.left,rc.top);
		//pDC->LineTo(rc.right,rc.bottom);

		//pDC->SelectStockObject(NULL_BRUSH);

		//pDC->SelectObject(&pPen);
		//pDC->MoveTo(rc.left, rc.top);
		//pDC->LineTo(rc.right, rc.bottom);
		////pDC->Rectangle(&rc);

		//ReleaseDC(pDC);
		}
	}

	//if (!IsWindowVisible())
	//{
	//	return;
	//}
	//CPen pPen;
	//CRect rc;
	//CPen *pOldPen = NULL;
	//CDC *pDC  = m_wndShow[num].GetDC();


}


void PreviewWind::OnPaint()
{

	
	
	CPaintDC dc(this); // device context for painting
					    //TODO: Add your message handler code here
					    //Do not call CDialogEx::OnPaint() for painting message

	//DrawFrame();




	//dc.MoveTo(0, 0);
	//dc.LineTo(150, 150);

	//CDC *pDC = GetDC();
	////我的绘制代码  
	//DrawFrame();
	//ReleaseDC(pDC);
//CDialog::OnPaint();  //最后才调用 
//	DrawFrame();
	 
}
