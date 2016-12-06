// MySliderCtl.cpp : implementation file
//

#include "stdafx.h"
#include "ZipSliderCtl.h"
#include "../resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



CZipSliderCtl::CZipSliderCtl()
{
	m_bDragging = FALSE;
}

CZipSliderCtl::~CZipSliderCtl()
{
}

BEGIN_MESSAGE_MAP(CZipSliderCtl, CSliderCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

void CZipSliderCtl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( m_bDragging )
		Invalidate(FALSE);
	CSliderCtrl::OnMouseMove(nFlags, point);
}

void CZipSliderCtl::OnPaint() 
{
	CPaintDC dc(this); 
	int iMax,iMin,iTickWidth=10,iMarginWidth=10;
	GetRange(iMin,iMax);
	RECT rcBack,rcTick;
	GetClientRect(&rcBack);
	rcTick = rcBack;
	TRACE("%d\n",GetPos());
	rcTick.left = ((rcBack.right-iMarginWidth)*(GetPos()))/((iMax - iMin)+iMarginWidth/2);
	rcTick.right = rcTick.left + iTickWidth;

	m_bmpBack->Draw(dc,0,0);
	m_bmTrans->DrawTrans(dc,rcTick.left, -2);
}

void CZipSliderCtl::OnTimer(UINT nIDEvent) 
{
	//Invalidate(FALSE);
	CSliderCtrl::OnTimer(nIDEvent);
}

void CZipSliderCtl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bDragging = FALSE;
	Invalidate(FALSE);
	CSliderCtrl::OnLButtonUp(nFlags, point);
}

void CZipSliderCtl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bDragging =TRUE;
	Invalidate(FALSE);
	CSliderCtrl::OnLButtonUp(nFlags, point);
}

void CZipSliderCtl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
//	Invalidate(FALSE);
//	CSliderCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CZipSliderCtl::SetRange(int nMin, int nMax, BOOL bRedraw)
{
	CSliderCtrl::SetRange(nMin,nMax,bRedraw);
	SetPos(nMin);
}

void CZipSliderCtl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
//	CSliderCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CZipSliderCtl::SetSkin(UINT uiBackGround, UINT uiTickImage)//,short nCursor)
{
	m_hCursor = LoadCursor(NULL, IDC_HAND);//LoadCursor(AfxGetInstanceHandle(),MAKEINTRESOURCE(nCursor));
	m_bmpBack = new CZipBitmap();
	m_bmpBack->LoadBitmap(uiBackGround);

	m_bmTrans = new CZipBitmap();
	m_bmTrans->LoadBitmap(uiTickImage);
}

BOOL CZipSliderCtl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	::SetCursor(m_hCursor);
	return TRUE;
}

