// SkinButtonDuaButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "SkinButtonDuaButton.h"
#include ".\SkinButtonDuaButton.h"

#include "memory"
using namespace std;
// CSkinButton
#define WM_BTN_PAINT WM_USER + 100
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }

IMPLEMENT_DYNAMIC(CSkinButtonDuaButton, CButton)
CSkinButtonDuaButton::CSkinButtonDuaButton():
m_bHover(FALSE),
m_bTracking(FALSE),
m_Clicked(FALSE),
m_Status(0)
{
	m_nStartX = 0;
	m_nStartY = 0;

	m_pBGImage = NULL;

	m_pBGImageSecond = NULL;

	m_nDivide = 4;

	m_bDisable = FALSE;
}

CSkinButtonDuaButton::~CSkinButtonDuaButton()
{
	SAFE_DELETE(m_pBGImage);
	SAFE_DELETE(m_pBGImageSecond);
}

BEGIN_MESSAGE_MAP(CSkinButtonDuaButton, CButton)	
	ON_CONTROL_REFLECT_EX(BN_CLICKED, OnBnClicked)
END_MESSAGE_MAP()

// CSkinButton 메시지 처리기입니다.
void CSkinButtonDuaButton::PreSubclassWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ModifyStyle(0, BS_OWNERDRAW);
	
	CButton::PreSubclassWindow();
}

void CSkinButtonDuaButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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

LRESULT CSkinButtonDuaButton::WindowProc(UINT nMessage, WPARAM wParam, LPARAM lParam)
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

BOOL CSkinButtonDuaButton::OnBnClicked()
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

void CSkinButtonDuaButton::OnHover()
{
	RedrawWindow();

	if (!m_bDisable)
		::SetCursor(LoadCursor(NULL, IDC_HAND));
}

void CSkinButtonDuaButton::DrawButton(int id)
{
	m_Status = id;
	GetOwner()->SendMessage(WM_PAINT , 0 , 0 );
}

void CSkinButtonDuaButton::OnDrawWindow(Graphics& gps)
{
	CRect rc;
	GetWindowRect(rc);
	GetOwner()->ScreenToClient(rc);

	int nfirstX = m_pBGImage->m_pBitmap->GetWidth() / m_nDivide;
	int nfirstY = m_pBGImage->m_pBitmap->GetHeight();

	int nSecondX = m_pBGImageSecond->m_pBitmap->GetWidth() / m_nDivide;
	int nSecondY = m_pBGImageSecond->m_pBitmap->GetHeight();

	gps.DrawImage(m_pBGImage->m_pBitmap , 
			Rect(rc.left, rc.top, nfirstX, nfirstX),
			nfirstX * m_Status, 0, nfirstX, nfirstX,
			UnitPixel);

	gps.DrawImage(m_pBGImageSecond->m_pBitmap , 
			Rect(rc.left, rc.top + nfirstX , nSecondX, nSecondY),
			nSecondX * m_Status, 0, nSecondX, nSecondY,
			UnitPixel);
}

void CSkinButtonDuaButton::SetImage(LPCTSTR pName, LPCTSTR pNameSecond, LPCTSTR pType, HMODULE hInst, int nStartX, int nStartY, int nDivide)
{
	if (!m_pBGImage)
	{
		m_pBGImage = new CGdiPlusBitmapResource;

		if (!m_pBGImage->Load(pName, pType, hInst))
		{
			return;
		}
	}

	if (!m_pBGImageSecond)
	{
		m_pBGImageSecond = new CGdiPlusBitmapResource;

		if (!m_pBGImageSecond->Load(pNameSecond, pType, hInst))
		{
			return;
		}
	}

	m_nDivide = nDivide;
	m_nStartX = nStartX;
	m_nStartY = nStartY;

	
	int nfirstX = m_pBGImage->m_pBitmap->GetWidth() / m_nDivide;
	int nfirstY = m_pBGImage->m_pBitmap->GetHeight();

	int nSecondX = m_pBGImageSecond->m_pBitmap->GetWidth() / m_nDivide;
	int nSecondY = m_pBGImageSecond->m_pBitmap->GetHeight();
	
	MoveWindow(m_nStartX, nStartY, nfirstX, nfirstY);	
	MoveWindow(m_nStartX, nStartY + nfirstY, nSecondX, nSecondY);	
}

void CSkinButtonDuaButton::SetImage(UINT uid, UINT uidSecond, LPCTSTR pType, HMODULE hInst, int nStartX, int nStartY, int nDivide)
{
	if (!m_pBGImage)
	{
		m_pBGImage = new CGdiPlusBitmapResource;

		if (!m_pBGImage->Load(uid, pType, hInst))
		{
			return;
		}
	}

	if (!m_pBGImageSecond)
	{
		m_pBGImageSecond = new CGdiPlusBitmapResource;

		if (!m_pBGImageSecond->Load(uidSecond, pType, hInst))
		{
			return;
		}
	}
	

	m_nDivide = nDivide;
	m_nStartX = nStartX;
	m_nStartY = nStartY;

	int nfirstX = m_pBGImage->m_pBitmap->GetWidth() / m_nDivide;
	int nfirstY = m_pBGImage->m_pBitmap->GetHeight();

	int nSecondX = m_pBGImageSecond->m_pBitmap->GetWidth() / m_nDivide;
	int nSecondY = m_pBGImageSecond->m_pBitmap->GetHeight();
	
	MoveWindow(m_nStartX, nStartY, nfirstX, nfirstY);	
	MoveWindow(m_nStartX, nStartY + nfirstY, nSecondX, nSecondY);	
}

void CSkinButtonDuaButton::SetDisableButton()
{
	m_bDisable = TRUE;

	RedrawWindow();

//	Invalidate();
}

void CSkinButtonDuaButton::SetEnableButton()
{
	m_bDisable = FALSE;

	RedrawWindow();

//	Invalidate();
}

void CSkinButtonDuaButton::Free()
{
	SAFE_DELETE(m_pBGImage);
	SAFE_DELETE(m_pBGImageSecond);
}
