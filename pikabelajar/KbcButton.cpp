// KbcButton.cpp : implementation file
//

#include "stdafx.h"
#include "KbcButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKbcButton

CKbcButton::CKbcButton()
{	
	m_bDisable			= FALSE;
	m_bCursorOnButton	= FALSE;
	m_bHover			= FALSE;
	m_bSetCursor		= FALSE;
}

CKbcButton::~CKbcButton()
{
}


BEGIN_MESSAGE_MAP(CKbcButton, CButton)
	//{{AFX_MSG_MAP(CKbcButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_MESSAGE(WM_MOUSEHOVER,OnMouseHover)
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKbcButton message handlers

void CKbcButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// get DC from LPDRAWITEMSTRUCT..
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	// disable state...
	if( m_bDisable == TRUE )
		m_bmpImage.Draw(pDC,BUTTON_DISABLE,0,0,m_nMask);

	else
	{
		// click state
		if( lpDrawItemStruct->itemState & ODS_SELECTED )
			m_bmpImage.Draw(pDC,BUTTON_CLICK,0,0,m_nMask);

		// hover state
		else if ( m_bHover)
			m_bmpImage.Draw(pDC,BUTTON_HOVER,0,0,m_nMask);

		// enable state
		else
			m_bmpImage.Draw(pDC,BUTTON_ENABLE,0,0,m_nMask);
	}
	
}

//리소스에 등록되어 있는 버튼 이미지를 읽어온다.
void CKbcButton::SetButtonImage(UINT ResourceName, UINT nMask)
{
	m_bmpImage.LoadBitmap(ResourceName);
	m_nMask = nMask;
	
	// get button info..
	m_rectButton.left	= 0;
	m_rectButton.top	= 0;
	m_rectButton.right	= m_bmpImage.GetSliceWidth();
	m_rectButton.bottom	= m_bmpImage.GetHeight();
	////////////////////////////////////////////////////////////////


	// resize button size.
	// if button size is smaller than button image then we enlarge button size..
	CWnd *pWnd = this->GetParent();
	GetWindowRect(&m_rectButtonPos);
	pWnd->ScreenToClient(m_rectButtonPos);
	m_rectButtonPos.right	= m_rectButtonPos.left + m_bmpImage.GetSliceWidth();
	m_rectButtonPos.bottom	= m_rectButtonPos.top  + m_bmpImage.GetHeight();
	MoveWindow(m_rectButtonPos);
	////////////////////////////////////////////////////////////////
}


void CKbcButton::SetButtonImage(CString strFileName,UINT nMask)
{
	m_bmpImage.LoadBitmap(strFileName);
	m_nMask = nMask;
	
	// get button info..
	m_rectButton.left	= 0;
	m_rectButton.top	= 0;
	m_rectButton.right	= m_bmpImage.GetSliceWidth();
	m_rectButton.bottom	= m_bmpImage.GetHeight();
	////////////////////////////////////////////////////////////////


	// resize button size.
	// if button size is smaller than button image then we enlarge button size..
	CWnd *pWnd = this->GetParent();
	GetWindowRect(&m_rectButtonPos);
	pWnd->ScreenToClient(m_rectButtonPos);
	m_rectButtonPos.right	= m_rectButtonPos.left + m_bmpImage.GetSliceWidth();
	m_rectButtonPos.bottom	= m_rectButtonPos.top  + m_bmpImage.GetHeight();
	MoveWindow(m_rectButtonPos);
	////////////////////////////////////////////////////////////////
}


void CKbcButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// we wanna get WM_MOUSEHOVER,WM_MOUSELEAVE message, so we call _TrackMouseEvent
	if( m_bCursorOnButton == FALSE )
	{
		TRACKMOUSEEVENT tme;
		ZeroMemory(&tme,sizeof(TRACKMOUSEEVENT));
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = 1;
		m_bCursorOnButton = _TrackMouseEvent(&tme);
	}
	
	CButton::OnMouseMove(nFlags, point);
}


LRESULT CKbcButton::OnMouseHover(WPARAM wparam, LPARAM lparam)
{
	m_bHover = TRUE;
	
	Invalidate();
	return 0L;
}

LRESULT CKbcButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bCursorOnButton	= FALSE;
	m_bHover			= FALSE;
	
	Invalidate();
	return 0L;
}

void CKbcButton::SetButtonEnable()
{
	m_bDisable = FALSE;
	
	Invalidate();
}

void CKbcButton::SetButtonDisable()
{
	m_bDisable = TRUE;
	
	Invalidate();
}

void CKbcButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// if button state is disable we do not call CButton::OnLButtonDown funtion..
	if( !m_bDisable )
		CButton::OnLButtonDown(nFlags, point);
}

BOOL CKbcButton::PreTranslateMessage(MSG* pMsg) 
{
	// to showing a tooltip message, call RelayEvent if m_ToolTip has created.
	if( m_ToolTip.GetSafeHwnd() != NULL )
		m_ToolTip.RelayEvent(pMsg);
	
	return CButton::PreTranslateMessage(pMsg);
}

void CKbcButton::SetToolTipText(CString strText)
{
	m_ToolTip.Create(this);
	m_ToolTip.Activate(TRUE);
	m_ToolTip.AddTool(this,(LPCTSTR)strText);
}

BOOL CKbcButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if( m_bSetCursor )
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}
	else
		return CButton::OnSetCursor(pWnd,nHitTest,message);
}

void CKbcButton::SetCursor(HCURSOR hCursor)
{
	m_bSetCursor	= TRUE;
	m_hCursor		= hCursor;
}

BOOL CKbcButton::OnEraseBkgnd(CDC* pDC) 
{
	// do not draw back ground. just return here, so we can see the background.
	// if you have curiosity about this, then remove ON_WM_ERASEBKGND() and test..
	return TRUE;
}

BOOL CKbcButton::Unload()
{
	m_bmpImage.UnLoad();

	return TRUE;
}