// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "MyStatic.h"


// MyStatic

IMPLEMENT_DYNAMIC(MyStatic, CStatic)

MyStatic::MyStatic()
	: isCurrentWind(false)
{

}

MyStatic::~MyStatic()
{
}


BEGIN_MESSAGE_MAP(MyStatic, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// MyStatic message handlers




void MyStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CStatic::OnPaint() for painting messages
	CPen pPen;
	CRect rc;
	CPen *pOldPen = NULL;

	if (isCurrentWind)
		pPen.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));//green
	else
		pPen.CreatePen(PS_SOLID, 2, RGB(125, 125, 116));
	GetClientRect(&rc);

	dc.SelectStockObject(NULL_BRUSH);

	pOldPen = dc.SelectObject(&pPen);

	dc.Rectangle(&rc);
	if (pOldPen)
	{
		dc.SelectObject(pOldPen);
	}

}
