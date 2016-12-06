// SkinButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SkinButton.h"
#include ".\skinbutton.h"

#include "memory"
using namespace std;
// CSkinButton
#define WM_BTN_PAINT WM_USER + 100
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }

IMPLEMENT_DYNAMIC(CSkinButton, CButton)
CSkinButton::CSkinButton():
m_bHover(FALSE),
m_bTracking(FALSE),
m_Clicked(FALSE),
m_Status(0)
{
	m_nStartX = 0;
	m_nStartY = 0;

	m_pBGImage = NULL;

	m_nDivide = 4;

	m_bDisable = FALSE;
}

CSkinButton::~CSkinButton()
{
	SAFE_DELETE(m_pBGImage);
}


BEGIN_MESSAGE_MAP(CSkinButton, CButton)
	
	ON_CONTROL_REFLECT_EX(BN_CLICKED, OnBnClicked)
END_MESSAGE_MAP()



// CSkinButton 메시지 처리기입니다.


void CSkinButton::PreSubclassWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ModifyStyle(0, BS_OWNERDRAW);
	
	CButton::PreSubclassWindow();
}


void CSkinButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	UINT state = lpDrawItemStruct->itemState;
	int DrawID;

	if (m_bDisable)
	{
		DrawID = 3;
	}
	else
	{
		if (state & ODS_DISABLED) 
		{
			DrawID = 3;
		}	
		else
		{	
			if (state & ODS_SELECTED) 
			{
				DrawID = 2;
			}
			else
			{
				DrawID = IsHover() ? 1: 0;
			}
		}	
	}

	DrawButton(DrawID);
}


LRESULT CSkinButton::WindowProc(UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	LRESULT nResult = CWnd::WindowProc(nMessage,wParam,lParam);
	switch(nMessage)
	{
	case WM_MOUSEMOVE:
		{
			if (!m_bTracking)
			{
				TRACKMOUSEEVENT Tme;
				Tme.cbSize = sizeof(Tme);
				Tme.hwndTrack = GetSafeHwnd();
				Tme.dwFlags = TME_LEAVE|TME_HOVER;
				Tme.dwHoverTime = 1;
				if (_TrackMouseEvent(&Tme))		
					m_bTracking=TRUE;
			}

			if (!m_bDisable)
				::SetCursor(LoadCursor(NULL, IDC_HAND));

			break;				
		}
	case	WM_LBUTTONDOWN:
	case	WM_RBUTTONDOWN:
	case	WM_LBUTTONUP:
	case	WM_RBUTTONUP:
		{

			if (!m_bDisable)
				::SetCursor(LoadCursor(NULL, IDC_HAND));

			break;
		}
	case WM_MOUSEHOVER:
		m_bHover = TRUE;	
		OnHover();
		
		break;
	case WM_MOUSELEAVE:
		m_bTracking = m_bHover = FALSE;
		OnHover();
		break;
	}

	return nResult;
}

BOOL CSkinButton::OnBnClicked()
{
	if(m_Clicked)
	{
		m_Clicked = FALSE;
	}
	else
	{
		m_Clicked = TRUE;
	}

	RedrawWindow();
	return FALSE;
}


void CSkinButton::OnHover()
{
	RedrawWindow();

	if (!m_bDisable)
		::SetCursor(LoadCursor(NULL, IDC_HAND));

}

void CSkinButton::DrawButton(int id)
{
	m_Status = id;
	GetOwner()->SendMessage(WM_PAINT , 0 , 0 );
}

void CSkinButton::OnDrawWindow(Graphics& gps)
{
	CRect rc;
	GetWindowRect(rc);
	GetOwner()->ScreenToClient(rc);

	int nX = m_pBGImage->m_pBitmap->GetWidth() / m_nDivide;
	int nY = m_pBGImage->m_pBitmap->GetHeight();

	gps.DrawImage(m_pBGImage->m_pBitmap , 
			Rect(rc.left, rc.top, nX, nY),
			nX * m_Status, 0, nX, nY,
			UnitPixel);

}

void CSkinButton::SetImage(LPCTSTR pName, LPCTSTR pType, HMODULE hInst, int nStartX, int nStartY, int nDivide)
{
	if (!m_pBGImage)
	{
		m_pBGImage = new CGdiPlusBitmapResource;

		if (!m_pBGImage->Load(pName, pType, hInst))
		{
			return;
		}
	}

	m_nDivide = nDivide;
	m_nStartX = nStartX;
	m_nStartY = nStartY;

	int nX = m_pBGImage->m_pBitmap->GetWidth() / m_nDivide;
	int nY = m_pBGImage->m_pBitmap->GetHeight();

	MoveWindow(m_nStartX, nStartY, nX, nY);	
}


void CSkinButton::SetImage(UINT uid, LPCTSTR pType, HMODULE hInst, int nStartX, int nStartY, int nDivide)
{
	if (!m_pBGImage)
	{
		m_pBGImage = new CGdiPlusBitmapResource;

		if (!m_pBGImage->Load(uid, pType, hInst))
		{
			return;
		}
	}

	m_nDivide = nDivide;
	m_nStartX = nStartX;
	m_nStartY = nStartY;

	int nX = m_pBGImage->m_pBitmap->GetWidth() / m_nDivide;
	int nY = m_pBGImage->m_pBitmap->GetHeight();

	MoveWindow(m_nStartX, nStartY, nX, nY);	
}

void CSkinButton::SetDisableButton()
{
	m_bDisable = TRUE;

	RedrawWindow();

//	Invalidate();
}

void CSkinButton::SetEnableButton()
{
	m_bDisable = FALSE;

	RedrawWindow();

//	Invalidate();
}

void CSkinButton::Free()
{
	SAFE_DELETE(m_pBGImage);
}
