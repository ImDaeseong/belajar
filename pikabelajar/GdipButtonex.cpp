//
// GdipButton.cpp : Version 1.0 - see article at CodeProject.com
//
// Author:  Darren Sessions
//          
//
// Description:
//     GdipButton is a CButton derived control that uses GDI+ 
//     to support alternate image formats
//
// History
//     Version 1.0 - 2008 June 10
//     - Initial public release
//
// License:
//     This software is released under the Code Project Open License (CPOL),
//     which may be found here:  http://www.codeproject.com/info/eula.aspx
//     You are free to use this software in any way you like, except that you 
//     may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this 
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GdipButtonex.h"
#include "MemDC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGdipButton

#define WM_BTN_PAINT WM_USER + 100

CGdipButtonex::CGdipButtonex()
{
	m_pStdImage = NULL;
	m_pAltImage = NULL;

	m_bHaveBitmaps = FALSE;
	m_bHaveAltImage = FALSE;

	m_pCurBtn = NULL;

	m_bIsDisabled = FALSE;
	m_bIsToggle = FALSE;

	m_bIsHovering = FALSE;
	m_bIsTracking = FALSE;

	m_nCurType = STD_TYPE;

	m_pToolTip = NULL;

	m_nStartX = 0;
	m_nStartY = 0;
	m_bOneButton = FALSE;
}

CGdipButtonex::~CGdipButtonex()
{
	if(m_pStdImage) delete m_pStdImage;
	if(m_pAltImage) delete m_pAltImage;

	if(m_pToolTip)	delete m_pToolTip;
}


BEGIN_MESSAGE_MAP(CGdipButtonex, CButton)
	//{{AFX_MSG_MAP(CGdipButtonex)
	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_MOUSEMOVE()
//	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
//	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//=============================================================================
//
// LoadStdImage()
//
// Purpose:     The LoadStdImage() Loads the image for the button.  This 
//				function must be called at a minimum or the button wont do 
//				anything.
//
// Parameters:  
//		[IN]	id
//				resource id, one of the resources already imported with the 
//				resource editor, usually begins with IDR_  
//
//		[IN]	pType
//				pointer to string describing the resource type
//				
// Returns:     BOOL
//				Non zero if successful, otherwise zero
//
//=============================================================================
BOOL CGdipButtonex::LoadStdImage(UINT id, LPCTSTR pType)
{
	m_pStdImage = new CGdiPlusBitmapResource;
	return m_pStdImage->Load(id, pType);
}


BOOL CGdipButtonex::LoadStdImage(LPCTSTR pName)
{
	m_pStdImage = new CGdiPlusBitmapResource;
	return m_pStdImage->Load(pName);
}

BOOL CGdipButtonex::LoadStdImage(UINT id, LPCTSTR pType, HMODULE hInst, int nStartX, int nStartY)
{
	m_nStartX = nStartX;
	m_nStartY = nStartY;

	m_pStdImage = new CGdiPlusBitmapResource;

	BOOL bResult = m_pStdImage->Load(id, pType, hInst);

	if (bResult)
	{
		int nX = m_pStdImage->m_pBitmap->GetWidth();
		int nY = m_pStdImage->m_pBitmap->GetHeight();
		MoveWindow(m_nStartX, m_nStartY, nX, nY);
	}

	return bResult;
}

//=============================================================================
//
// LoadAltImage()
//
// Purpose:     The LoadAltImage() Loads the altername image for the button.  
//				This function call is optional
// Parameters:  
//		[IN]	id
//				resource id, one of the resources already imported with the 
//				resource editor, usually begins with IDR_  
//
//		[IN]	pType
//				pointer to string describing the resource type
//				
// Returns:     BOOL
//				Non zero if successful, otherwise zero
//
//=============================================================================
BOOL CGdipButtonex::LoadAltImage(UINT id, LPCTSTR pType)
{
	m_bHaveAltImage = TRUE;
	m_pAltImage = new CGdiPlusBitmapResource;

	return (m_pAltImage->Load(id, pType));
}

BOOL CGdipButtonex::LoadAltImage(UINT id, LPCTSTR pType, HMODULE hInst, int nStartX, int nStartY)
{
	m_bHaveAltImage = TRUE;
	m_pAltImage = new CGdiPlusBitmapResource;

//	return (m_pAltImage->Load(id, pType));

	BOOL bResult = m_pAltImage->Load(id, pType, hInst);

	if (bResult)
	{
		int nX = m_pStdImage->m_pBitmap->GetWidth();
		int nY = m_pStdImage->m_pBitmap->GetHeight();

		MoveWindow(nStartX, nStartY, nX, nY);
	}

	return bResult;
}

//=============================================================================
//
//	The framework calls this member function when a child control is about to 
//	be drawn.  All the bitmaps are created here on the first call. Every thing
//	is done with a memory DC except the background, which get's it's information 
//	from the parent. The background is needed for transparent portions of PNG 
//	images. An always on top app (such as Task Manager) that is in the way can 
//	cause it to get an incorrect background.  To avoid this, the parent should 
//	call the SetBkGnd function with a memory DC when it creates the background.
//				
//=============================================================================
HBRUSH CGdipButtonex::CtlColor(CDC* pScreenDC, UINT nCtlColor) 
{
	if(!m_bHaveBitmaps)
	{
		if(!m_pStdImage)
		{
			return NULL; // Load the standard image with LoadStdImage()
		}

		CBitmap bmp, *pOldBitmap;

		CRect rect;
		GetClientRect(rect);

		// do everything with mem dc
		CMemDCEx pDC(pScreenDC, rect);

		Gdiplus::Graphics graphics(pDC->m_hDC);

		// background
		if (m_dcBk.m_hDC == NULL)
		{

			CRect rect1;
			CClientDC clDC(GetParent());
			GetWindowRect(rect1);
			GetParent()->ScreenToClient(rect1);

			m_dcBk.CreateCompatibleDC(&clDC);
			bmp.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
			pOldBitmap = m_dcBk.SelectObject(&bmp);
			m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
			bmp.DeleteObject();
		}

		// standard image
		if (m_dcStd.m_hDC == NULL)
		{
			PaintBk(pDC);

			graphics.DrawImage(*m_pStdImage, 0, 0);
		
			m_dcStd.CreateCompatibleDC(pDC);
			bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
			pOldBitmap = m_dcStd.SelectObject(&bmp);
			m_dcStd.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
			bmp.DeleteObject();

			// standard image pressed
			if (m_dcStdP.m_hDC == NULL)
			{
				PaintBk(pDC);

				graphics.DrawImage(*m_pStdImage, 1, 1);

				m_dcStdP.CreateCompatibleDC(pDC);
				bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
				pOldBitmap = m_dcStdP.SelectObject(&bmp);
				m_dcStdP.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
				bmp.DeleteObject();
			}

			// standard image hot
			if(m_dcStdH.m_hDC == NULL)
			{
				PaintBk(pDC);

				ColorMatrix HotMat = {	1.0f, 0.00f, 0.00f, 0.00f, 0.00f,
										0.00f, 1.0f, 0.00f, 0.00f, 0.00f,
										0.00f, 0.00f, 1.0f, 0.00f, 0.00f,
										0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
										0.05f, 0.05f, 0.05f, 0.00f, 1.00f	};

				ImageAttributes ia;
				ia.SetColorMatrix(&HotMat);

				float width = (float)m_pStdImage->m_pBitmap->GetWidth();
				float height = (float)m_pStdImage->m_pBitmap->GetHeight();

				RectF grect; grect.X=0, grect.Y=0; grect.Width = width; grect.Height = height;

				graphics.DrawImage(*m_pStdImage, grect, 0, 0, width, height, UnitPixel, &ia);

				m_dcStdH.CreateCompatibleDC(pDC);
				bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
				pOldBitmap = m_dcStdH.SelectObject(&bmp);
				m_dcStdH.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
				bmp.DeleteObject();
			}

			// grayscale image
			if(m_dcGS.m_hDC == NULL)
			{
				PaintBk(pDC);

				ColorMatrix GrayMat = {	1.0f, 0.00f, 0.00f, 0.00f, 0.00f,
										0.00f, 1.0f, 0.00f, 0.00f, 0.00f,
										0.00f, 0.00f, 1.0f, 0.00f, 0.00f,
										0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
										0.05f, 0.05f, 0.05f, 0.00f, 1.00f	};
/*

				ColorMatrix GrayMat = {	0.40f, 0.40f, 0.40f, 0.00f, 0.00f,
										0.59f, 0.59f, 0.59f, 0.00f, 0.00f,
										0.11f, 0.11f, 0.11f, 0.00f, 0.00f,
										0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
										0.00f, 0.00f, 0.00f, 0.00f, 1.00f	};
										*/
				
				ImageAttributes ia;
				ia.SetColorMatrix(&GrayMat);

				float width = (float)m_pStdImage->m_pBitmap->GetWidth();
				float height = (float)m_pStdImage->m_pBitmap->GetHeight();

				RectF grect; grect.X=0, grect.Y=0; grect.Width = width; grect.Height = height;

				graphics.DrawImage(*m_pStdImage, grect, 0, 0, width, height, UnitPixel, &ia);

				m_dcGS.CreateCompatibleDC(pDC);
				bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
				pOldBitmap = m_dcGS.SelectObject(&bmp);
				m_dcGS.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
				bmp.DeleteObject();
			}
		}

		// alternate image
		if( (m_dcAlt.m_hDC == NULL) && m_bHaveAltImage )
		{
			PaintBk(pDC);

			graphics.DrawImage(*m_pAltImage, 0, 0);
		
			m_dcAlt.CreateCompatibleDC(pDC);
			bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
			pOldBitmap = m_dcAlt.SelectObject(&bmp);
			m_dcAlt.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
			bmp.DeleteObject();

			// alternate image pressed
			if( (m_dcAltP.m_hDC == NULL) && m_bHaveAltImage )
			{
				PaintBk(pDC);

				graphics.DrawImage(*m_pAltImage, 1, 1);
			
				m_dcAltP.CreateCompatibleDC(pDC);
				bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
				pOldBitmap = m_dcAltP.SelectObject(&bmp);
				m_dcAltP.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
				bmp.DeleteObject();
			}

			// alternate image hot
			if(m_dcAltH.m_hDC == NULL)
			{
				PaintBk(pDC);

				ColorMatrix HotMat = {	1.0f, 0.00f, 0.00f, 0.00f, 0.00f,
										0.00f, 1.0f, 0.00f, 0.00f, 0.00f,
										0.00f, 0.00f, 1.0f, 0.00f, 0.00f,
										0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
										0.05f, 0.05f, 0.05f, 0.00f, 1.00f	};
/*
				ColorMatrix HotMat = {	1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
										0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
										0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
										0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
										0.05f, 0.05f, 0.05f, 0.00f, 1.00f	};

*/

				ImageAttributes ia;
				ia.SetColorMatrix(&HotMat);

				float width = (float)m_pStdImage->m_pBitmap->GetWidth();
				float height = (float)m_pStdImage->m_pBitmap->GetHeight();

				RectF grect; grect.X=0, grect.Y=0; grect.Width = width; grect.Height = height;

				graphics.DrawImage(*m_pAltImage, grect, 0, 0, width, height, UnitPixel, &ia);

				m_dcAltH.CreateCompatibleDC(pDC);
				bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
				pOldBitmap = m_dcAltH.SelectObject(&bmp);
				m_dcAltH.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
				bmp.DeleteObject();
			}
		}

		if(m_pCurBtn == NULL)
		{
			m_pCurBtn = &m_dcStd;
		}

		m_bHaveBitmaps = TRUE;
	}

	return NULL;
}

//=============================================================================
// paint the background
//=============================================================================
void CGdipButtonex::PaintBk(CDC *pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
}

//=============================================================================
// paint the bitmap currently pointed to with m_pCurBtn
//=============================================================================
void CGdipButtonex::PaintBtn(CDC *pDC)
{
	CRect rect;
	GetClientRect(rect);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), m_pCurBtn, 0, 0, SRCCOPY);
}

//=============================================================================
// enables the toggle mode
// returns if it doesn't have the alternate image
//=============================================================================
void CGdipButtonex::EnableToggle(BOOL bEnable)
{
	if(!m_bHaveAltImage) return;

	m_bIsToggle = bEnable; 

	// this actually makes it start in the std state since toggle is called before paint
	if(bEnable)	m_pCurBtn = &m_dcAlt;
	else		m_pCurBtn = &m_dcStd;

}

//=============================================================================
// sets the image type and disabled state then repaints
//=============================================================================
void CGdipButtonex::SetImage(int type)
{
	m_nCurType = type;

	(type == DIS_TYPE) ? m_bIsDisabled = TRUE : m_bIsDisabled = FALSE;

	Invalidate();
}

//=============================================================================
// set the control to owner draw
//=============================================================================
void CGdipButtonex::PreSubclassWindow()
{
	// Set control to owner draw
	ModifyStyle(0, BS_OWNERDRAW, SWP_FRAMECHANGED);

	CButton::PreSubclassWindow();
}

//=============================================================================
// disable double click 
//=============================================================================
BOOL CGdipButtonex::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_LBUTTONDBLCLK)
		pMsg->message = WM_LBUTTONDOWN;

	if (m_pToolTip != NULL)
	{
		if (::IsWindow(m_pToolTip->m_hWnd))
		{
			m_pToolTip->RelayEvent(pMsg);		
		}
	}

	return CButton::PreTranslateMessage(pMsg);
}


//=============================================================================
// overide the erase function
//=============================================================================
BOOL CGdipButtonex::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

//=============================================================================
// Paint the button depending on the state of the mouse
//=============================================================================
void CGdipButtonex::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

	// handle disabled state
	if(m_bIsDisabled)
	{
		m_pCurBtn = &m_dcGS;
		PaintBtn(pDC);
		return;
	}

	BOOL bIsPressed = (lpDIS->itemState & ODS_SELECTED);

	// handle toggle button
	if(m_bIsToggle && bIsPressed)
	{
		(m_nCurType == STD_TYPE) ? m_nCurType = ALT_TYPE : m_nCurType = STD_TYPE;
	}

	if(bIsPressed)
	{
		if (!m_bOneButton)
		{
			if(m_nCurType == STD_TYPE)
				m_pCurBtn = &m_dcStdP;
			else
				m_pCurBtn = &m_dcAltP;
		}
	}
	else if(m_bIsHovering)
	{
		if (!m_bOneButton)
		{
			if(m_nCurType == STD_TYPE)
				m_pCurBtn = &m_dcStdH;
			else
				m_pCurBtn = &m_dcAltH;
		}
	}
	else
	{

		if(m_nCurType == STD_TYPE)
			m_pCurBtn = &m_dcStd;
		else
			m_pCurBtn = &m_dcAlt;
	
	}

	// paint the button
	PaintBtn(pDC);

//	GetOwner()->SendMessage(WM_BTN_PAINT , 0 , 0 );

}

//=============================================================================
LRESULT CGdipButtonex::OnMouseHover(WPARAM wparam, LPARAM lparam) 
//=============================================================================
{
	m_bIsHovering = TRUE;
	Invalidate();
	DeleteToolTip();

	// Create a new Tooltip with new Button Size and Location
	SetToolTipText(m_tooltext);

	if (m_pToolTip != NULL)
	{
		if (::IsWindow(m_pToolTip->m_hWnd))
		{
			//Display ToolTip
			m_pToolTip->Update();
		}
	}

	return 0;
}


//=============================================================================
LRESULT CGdipButtonex::OnMouseLeave(WPARAM wparam, LPARAM lparam)
//=============================================================================
{
	m_bIsTracking = FALSE;
	m_bIsHovering = FALSE;
	Invalidate();
	return 0;
}

//=============================================================================
void CGdipButtonex::OnMouseMove(UINT nFlags, CPoint point) 
//=============================================================================
{
	if (!m_bIsTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = 1;
		m_bIsTracking = _TrackMouseEvent(&tme);
/*
		CRect rect;
		GetClientRect(rect);

		MoveWindow(rect.left, rect.top, rect.right + 20, rect.bottom + 20);
*/
	}
	
	CButton::OnMouseMove(nFlags, point);
}


//=============================================================================
//	
//	Call this member function with a memory DC from the code that paints 
//	the parents background.  Passing the screen DC defeats the purpose of 
//  using this function.
//
//=============================================================================
void CGdipButtonex::SetBkGnd(CDC* pDC)
{
	CRect rect, rectS;
	CBitmap bmp, *pOldBitmap;

	GetClientRect(rect);
	GetWindowRect(rectS);
	GetParent()->ScreenToClient(rectS);

	m_dcBk.DeleteDC();

	m_dcBk.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pOldBitmap = m_dcBk.SelectObject(&bmp);
	m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, rectS.left, rectS.top, SRCCOPY);
	bmp.DeleteObject();
}


//=============================================================================
// Set the tooltip with a string resource
//=============================================================================
void CGdipButtonex::SetToolTipText(UINT nId, BOOL bActivate)
{
	// load string resource
	m_tooltext.LoadString(nId);

	// If string resource is not empty
	if (m_tooltext.IsEmpty() == FALSE)
	{
		SetToolTipText(m_tooltext, bActivate);
	}

}

//=============================================================================
// Set the tooltip with a CString
//=============================================================================
void CGdipButtonex::SetToolTipText(CString spText, BOOL bActivate)
{
	// We cannot accept NULL pointer
	if (spText.IsEmpty()) return;

	// Initialize ToolTip
	InitToolTip();
	m_tooltext = spText;

	// If there is no tooltip defined then add it
	if (m_pToolTip->GetToolCount() == 0)
	{
		CRect rectBtn; 
		GetClientRect(rectBtn);
		m_pToolTip->AddTool(this, m_tooltext, rectBtn, 1);
	}

	// Set text for tooltip
	m_pToolTip->UpdateTipText(m_tooltext, this, 1);
	m_pToolTip->SetDelayTime(2000);
	m_pToolTip->Activate(bActivate);
}

//=============================================================================
void CGdipButtonex::InitToolTip()
//=============================================================================
{
	if (m_pToolTip == NULL)
	{
		m_pToolTip = new CToolTipCtrl;
		// Create ToolTip control
		m_pToolTip->Create(this);
		m_pToolTip->Activate(TRUE);
	}
} 

//=============================================================================
void CGdipButtonex::DeleteToolTip()
//=============================================================================
{
	// Destroy Tooltip incase the size of the button has changed.
	if (m_pToolTip != NULL)
	{
		delete m_pToolTip;
		m_pToolTip = NULL;
	}
}


void CGdipButtonex::OnDrawWindow(Graphics &Gps)
{

	CRect rc;
	GetWindowRect(rc);
	GetOwner()->ScreenToClient(rc);

	int nX = m_pStdImage->m_pBitmap->GetWidth();
	int nY = m_pStdImage->m_pBitmap->GetHeight();

	Gps.DrawImage(m_pStdImage->m_pBitmap , 
		Rect(rc.left, rc.top, nX, nY),
		0, 0, nX, nY,
		UnitPixel);

//	MoveWindow(m_nStartX, m_nStartY, nX, nY);

//	RedrawWindow();
}

void CGdipButtonex::SetImagePos(int nStartX, int nStartY)
{
	m_nStartX = nStartX;
	m_nStartY = nStartY;	
}

LRESULT CGdipButtonex::WindowProc(UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	LRESULT nResult = CWnd::WindowProc(nMessage,wParam,lParam);
	switch(nMessage)
	{
	case WM_MOUSEMOVE:
		{
			if (!m_bIsTracking)
			{
				TRACKMOUSEEVENT tme;
				tme.cbSize = sizeof(tme);
				tme.hwndTrack = m_hWnd;
				tme.dwFlags = TME_LEAVE|TME_HOVER;
				tme.dwHoverTime = 1;
				m_bIsTracking = _TrackMouseEvent(&tme);
			}

			//if (!m_bOneButton)
			//	::SetCursor(LoadCursor(NULL, IDC_HAND));

			break;				
		}
	case	WM_LBUTTONDOWN:
	case	WM_RBUTTONDOWN:
	case	WM_LBUTTONUP:
	case	WM_RBUTTONUP:
		{		
			//if (!m_bOneButton)
			//	::SetCursor(LoadCursor(NULL, IDC_HAND));

			break;
		}
	case WM_MOUSEHOVER:
		m_bIsHovering = TRUE;
		Invalidate();
		DeleteToolTip();

		// Create a new Tooltip with new Button Size and Location
		SetToolTipText(m_tooltext);

		if (m_pToolTip != NULL)
		{
			if (::IsWindow(m_pToolTip->m_hWnd))
			{
				//Display ToolTip
				m_pToolTip->Update();
			}
		}

		break;
	case WM_MOUSELEAVE:
		m_bIsTracking = FALSE;
		m_bIsHovering = FALSE;
		Invalidate();
		break;
	}

	return nResult;
}

void CGdipButtonex::SetOneButton(BOOL bOneButton)
{
	m_bOneButton = bOneButton;
}
