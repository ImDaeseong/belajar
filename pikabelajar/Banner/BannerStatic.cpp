#include "stdafx.h"
#include "BannerStatic.h"

const int CBannerStatic::MAXSPEED(1000);  
const int CBannerStatic::MAXSPEED_MODIFIER(CBannerStatic::MAXSPEED*10);
const int CBannerStatic::TIMERRESOLUTION(100);
const int CBannerStatic::STEPHEIGHT(250);

CBannerStatic::CBannerStatic() : CMultiColorStatic()
{
	m_tmScroll = 0;
    m_nTextOut = 0;
    SetWrapText(TRUE);
    SetScrollSpeed(0);
    SetScrollDelay(100);
    SetScrollSize(-1);
    m_hItemCursor = NULL;
    m_hStdCursor = NULL;
    m_pfnItemClick = NULL;
}

CBannerStatic::~CBannerStatic()
{
}

void CBannerStatic::SetScrollSpeed(const int& nSpeed)
{  
	if ((nSpeed < -MAXSPEED) || (nSpeed > MAXSPEED))
    {
		ASSERT(FALSE); // speed must fall in the above range
        return;
    }

    if (nSpeed == 0)
    {
       if (m_tmScroll)
       {
          timeKillEvent(m_tmScroll);
          m_tmScroll = 0;
       }
    }
    else
    {
       m_nBannerSpeed = nSpeed;
       CalculateScrollParameters();
       m_tmScroll = timeSetEvent(GetScrollDelay(), TIMERRESOLUTION, TimerProc, (DWORD)this, TIME_CALLBACK_FUNCTION);
   }
}

int CBannerStatic::GetScrollSpeed(void) const
{
	return (m_nBannerSpeed);
}

void CBannerStatic::SetWrapText(const BOOL& fWrapText)
{
    m_fWrapText = fWrapText;
}

BOOL CBannerStatic::GetWrapText(void) const
{
    return (m_fWrapText);
}

void CBannerStatic::SetItemCursor(const UINT& unItemCursor)
{
    if (m_hItemCursor)
    {
       DestroyCursor(m_hItemCursor);
    }
   
    if (unItemCursor)
    {
       m_hItemCursor = LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(unItemCursor));
    }
    else
    {
       m_hItemCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    }
}

void CBannerStatic::SetItemClickProc(PFNBANNERITEMCLICK pfnItemClick)
{
    m_pfnItemClick = pfnItemClick;
}

void CBannerStatic::SetScrollSize(const int& nScrollSize)
{
    m_nScrollSize = nScrollSize;
}

int CBannerStatic::GetScrollSize(void) const
{
    return (GetScrollSpeed() > 0 ? -1 : 1);
}

void CBannerStatic::SetScrollDelay(const DWORD& dwScrollDelay)
{
    m_dwScrollDelay = dwScrollDelay;
}

DWORD CBannerStatic::GetScrollDelay(void) const
{
    return (m_dwScrollDelay);
}

void CBannerStatic::CalculateScrollParameters(void)
{
    m_dwScrollDelay = abs(MAXSPEED_MODIFIER / m_nBannerSpeed);

    m_nScrollSize = (m_nBannerSpeed >= 0 ? -1 : 1);

    int nStepHeight = STEPHEIGHT;
    m_nScrollSize *= ((m_rcBounds.Height() / nStepHeight)+1);
}

int CBannerStatic::FindStringFromPoint(CPoint point)
{
    for (int i = 0; i < m_vnStrings.size(); i++)
    {
       if (m_vnStrings.at(i) > point.x)
       {
          return (i-1);
       }

       if (i == (m_vnStrings.size() - 1))
       {
          if ((m_vnStrings.at(i) < m_nTextOut + m_nTextLength) && (point.x < (m_nTextOut + m_nTextLength)))
          {
             return (i);
          }
       }
    }
    return (-1);
}

LPARAM CBannerStatic::MakeParentPoint(CPoint point)
{
    LPARAM lReturn = 0;

    CWnd* pParent = GetParent();
    ClientToScreen(&point);
    pParent->ScreenToClient(&point);

    lReturn = ((0x0000FFFF & point.x) | (0xFFFF0000 & (point.y << 16)));

    return (lReturn);
}

void CBannerStatic::ScrollBanner(void)
{
    CPoint ptScroll;
    ptScroll.x = GetScrollSize();
    ptScroll.y = 0;
   
    CDC* pDC = GetDC();
    LPtoDP(pDC->m_hDC, &ptScroll, 1);
    pDC->DPtoLP(&ptScroll, 1);
    ReleaseDC(pDC);
   
    ScrollWindow(ptScroll.x, ptScroll.y, m_rcBounds, m_rcBounds);
}

void CALLBACK CBannerStatic::TimerProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    CBannerStatic* pBanner = (CBannerStatic*)dwUser;

    if (::IsWindow(pBanner->m_hWnd))
    {
       pBanner->PostMessage(WM_TIMER, uID, 0);
    }
}

void CBannerStatic::PreSubclassWindow(void)
{    
	CMultiColorStatic::PreSubclassWindow();

    SetScrollSpeed(0);
    m_hStdCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    m_hItemCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
}

BEGIN_MESSAGE_MAP(CBannerStatic, CMultiColorStatic)
    ON_WM_TIMER()
    ON_WM_PAINT()
    ON_WM_SIZE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MBUTTONDOWN()
    ON_WM_MBUTTONUP()
    ON_WM_RBUTTONDOWN()
    ON_WM_RBUTTONUP()
    ON_WM_SETCURSOR()
    ON_WM_MOUSEMOVE()
    ON_WM_DESTROY()
END_MESSAGE_MAP()

void CBannerStatic::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == m_tmScroll)
 	{
 		if (GetNumStrings() > 0)
 		{
 			if (GetWrapText())
 			{
 				if (GetScrollSpeed() > 0)
 				{
 					if ((--m_nTextOut + m_nTextLength) < m_rcBounds.left)
 					{
 						m_nTextOut = m_rcBounds.right;
 					}
 				}
 				else if (GetScrollSpeed() < 0)
 				{
 					if ((++m_nTextOut) > m_rcBounds.right)
 					{
 						m_nTextOut = m_rcBounds.left - m_nTextLength;
 						Invalidate();
 					}
 				}
 			}
			ScrollBanner();
		}
		m_tmScroll = timeSetEvent(GetScrollDelay(), TIMERRESOLUTION, TimerProc, (DWORD)this, TIME_CALLBACK_FUNCTION);
	}
	else
	{
		CMultiColorStatic::OnTimer(nIDEvent);
	}
}

void CBannerStatic::OnPaint()
{
	CPaintDC dc(this);
      
    CRect rcBounds = m_rcBounds;      
    rcBounds.left = m_nTextOut;

    dc.FillRect(m_rcBounds, &m_brBackGround);
    dc.IntersectClipRect(m_rcBounds); 

    m_nTextLength = 0;
    m_vnStrings.clear();

    for (int i = 0; i < m_astrData.GetSize(); i++)
   	{
   		CColorString* pstrCurrent = reinterpret_cast<CColorString*>(m_astrData.GetAt(i));
        TEXTMETRIC    stFontMetrics;
     	SIZE          stSize;

     	DetermineFont(pstrCurrent);

	
		dc.SelectObject(&m_ftText)->DeleteObject();
		
		if (pstrCurrent->GetBackColor() == ::GetSysColor(COLOR_BTNFACE))
     	{
     		dc.SetBkColor(m_crBackColor);
     	}
     	else
     	{
     		dc.SetBkColor(pstrCurrent->GetBackColor());
     	}
	
		dc.SetTextColor(pstrCurrent->GetColor());
		dc.GetOutputTextMetrics(&stFontMetrics);

      
		GetTextExtentPoint32(dc.GetSafeHdc(), *pstrCurrent, pstrCurrent->GetLength(), &stSize);
				
	    dc.DrawText(*pstrCurrent, rcBounds, DT_LEFT);
    	rcBounds.left += stSize.cx + stFontMetrics.tmOverhang;
    	m_vnStrings.push_back(m_nTextOut + m_nTextLength);
    	m_nTextLength += stSize.cx + stFontMetrics.tmOverhang;
   	}
}

void CBannerStatic::OnSize(UINT nType, int cx, int cy)
{
	CMultiColorStatic::OnSize(nType, cx, cy);
   	CalculateScrollParameters();
   	Invalidate();
}

void CBannerStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
	int nString = FindStringFromPoint(point);
    if (nString != -1)
    {
    
		if (m_pfnItemClick)
		{
			m_pfnItemClick(GetParent()->GetSafeHwnd(), nString, GetSafeHwnd());
         	return;
		}
    }

	GetParent()->PostMessage(WM_LBUTTONDOWN, nFlags, MakeParentPoint(point));
}

void CBannerStatic::OnLButtonUp(UINT nFlags, CPoint point)
{
    GetParent()->PostMessage(WM_LBUTTONUP, nFlags, MakeParentPoint(point));
}

void CBannerStatic::OnMButtonDown(UINT nFlags, CPoint point)
{
    GetParent()->PostMessage(WM_MBUTTONDOWN, nFlags, MakeParentPoint(point));
}

void CBannerStatic::OnMButtonUp(UINT nFlags, CPoint point)
{
    GetParent()->PostMessage(WM_MBUTTONUP, nFlags, MakeParentPoint(point));
}

void CBannerStatic::OnRButtonDown(UINT nFlags, CPoint point)
{
    GetParent()->PostMessage(WM_RBUTTONDOWN, nFlags, MakeParentPoint(point));
}

void CBannerStatic::OnRButtonUp(UINT nFlags, CPoint point)
{
    GetParent()->PostMessage(WM_RBUTTONUP, nFlags, MakeParentPoint(point));
}

BOOL CBannerStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (FindStringFromPoint(m_ptCursor) != -1)
    {
       ::SetCursor(m_hItemCursor);
       return (TRUE);
    }
    else
    {
       ::SetCursor(m_hStdCursor);
       return (TRUE);
    }
}

void CBannerStatic::OnMouseMove(UINT nFlags, CPoint point)
{
    m_ptCursor = point;
}

void CBannerStatic::OnDestroy()
{
	if (m_hItemCursor)
    {
       DestroyCursor(m_hItemCursor);
    }

    if (m_hStdCursor)
    {
       DestroyCursor(m_hStdCursor);
    }
}