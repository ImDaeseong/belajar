
#include "stdafx.h"
#include "TransparentLink.h"
#include "Resource.h"

IMPLEMENT_DYNAMIC(CTransparentLink, CStatic)
CTransparentLink::CTransparentLink()
{
	m_FontArrangeStyle = 0;

	m_clrText = GetSysColor(COLOR_CAPTIONTEXT);

	SetFontInfo(12, "Arial", FW_NORMAL);//SetFontInfo(12, "Tahoma", FW_NORMAL);

	m_strUrlLink = "";

	m_bLink = FALSE;

	m_hCursor = NULL;

	m_hNoticeWnd = NULL;
	m_dwClickMsg = 0;
	m_dwWndID = 0;
}

CTransparentLink::~CTransparentLink()
{
	if(m_FontText.GetSafeHandle())	m_FontText.DeleteObject();
}

BEGIN_MESSAGE_MAP(CTransparentLink, CStatic)
   ON_WM_CTLCOLOR_REFLECT()
   ON_WM_ERASEBKGND()
   ON_WM_PAINT()
   ON_WM_LBUTTONDOWN()
   ON_WM_SETCURSOR()
END_MESSAGE_MAP()

HBRUSH CTransparentLink::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
   pDC->SetBkMode(TRANSPARENT);
   return (HBRUSH)GetStockObject(NULL_BRUSH);
}

void CTransparentLink::SetFontInfo(int size, char *name, int bold)
{
	if(m_FontText.GetSafeHandle())	m_FontText.DeleteObject();

    m_FontText.CreateFont(
					size,						// 글자 크기
					0,							// nWidth
					0,							// nEscapement
					0,							// nOrientation
					bold,						// nWeight
					FALSE,						// bItalic
					FALSE,						// bUnderline
					0,							// cStrikeOut
					DEFAULT_CHARSET,			// nCharSet
					OUT_DEFAULT_PRECIS,			// nOutPrecision
					CLIP_DEFAULT_PRECIS,		// nClipPrecision
					DEFAULT_QUALITY,			// nQuality
					DEFAULT_PITCH | FF_SWISS,	// nPitchAndFamily
					name);						// 폰트 이름
}

void CTransparentLink::OnPaint()
{
	CPaintDC dc(this); 

	CRect rClient;
	GetClientRect(rClient);


	//영역 안에 들어간 문자
	CString szText;
	GetWindowText(szText);

	// Map "Static Styles" to "Text Styles"
    #define MAP_STYLE(src, dest)	if(dwStyle & (src)) dwText |= (dest)
    #define NMAP_STYLE(src, dest)	if(!(dwStyle & (src))) dwText |= (dest)

	//폰트 정렬방식  
	DWORD dwStyle = GetStyle(), dwText = m_FontArrangeStyle; 
	
	MAP_STYLE(	SS_RIGHT,			DT_RIGHT					);
	MAP_STYLE(	SS_CENTER,			DT_CENTER					);
	MAP_STYLE(	SS_CENTERIMAGE,		DT_VCENTER | DT_SINGLELINE	);
	MAP_STYLE(	SS_NOPREFIX,		DT_NOPREFIX					);
	MAP_STYLE(	SS_WORDELLIPSIS,	DT_WORD_ELLIPSIS			);
	MAP_STYLE(	SS_ENDELLIPSIS,		DT_END_ELLIPSIS				);
	MAP_STYLE(	SS_PATHELLIPSIS,	DT_PATH_ELLIPSIS			);

	NMAP_STYLE(	SS_LEFTNOWORDWRAP | SS_CENTERIMAGE | SS_WORDELLIPSIS |
				SS_ENDELLIPSIS | SS_PATHELLIPSIS, DT_WORDBREAK);

	HFONT hFont;
	if(m_FontText.GetSafeHandle())
	{
		hFont = (HFONT)SelectObject(dc.m_hDC, (HFONT)m_FontText.m_hObject);
	}

	if(szText.GetLength() > 0)	
	{
		int iPrvMode = dc.SetBkMode(TRANSPARENT);	// 윈도 배경 투명하게
		dc.SetTextColor(m_clrText);		// 글자색 설정
		dc.DrawText(szText, rClient, dwText);		// 글자 뿌리기
		dc.SetBkMode(iPrvMode);
	}

	if(m_FontText.GetSafeHandle())	::SelectObject(dc.m_hDC, hFont);
}

BOOL CTransparentLink::OnEraseBkgnd(CDC* pDC)
{
   return TRUE;
}

BOOL CTransparentLink::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (m_hCursor)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

CTransparentLink& CTransparentLink::SetLinkCursor(HCURSOR hCursor)
{
	m_hCursor = hCursor;
	return *this;
}

void CTransparentLink::SetLinkUrl(CString strUrl)
{
	m_strUrlLink = strUrl;
}

CTransparentLink& CTransparentLink::SetLink(BOOL bLink)
{
	m_bLink = bLink;

	if (bLink)
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);

	return *this;
}

void CTransparentLink::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bLink == TRUE)
	{
		if (m_hNoticeWnd)
			::PostMessage(m_hNoticeWnd, m_dwClickMsg, (WPARAM)m_dwWndID, 0);
	}		
		
	CStatic::OnLButtonDown(nFlags, point);
}

void CTransparentLink::ExecuteIE()
{
	CString strIEPath;
	strIEPath.Format("%s\\Internet Explorer\\iexplore.exe", CFunc::GetProgramFilesFolder());
	
	::ShellExecute(NULL, "open", strIEPath, m_strUrlLink, NULL, SW_SHOWNORMAL);		
}

void CTransparentLink::SetNoticeInfo(HWND hNoticeWnd, DWORD dwClickMsg, DWORD dwWndID)
{
	m_hNoticeWnd = hNoticeWnd;
	m_dwClickMsg = dwClickMsg;
	m_dwWndID = dwWndID;
}
