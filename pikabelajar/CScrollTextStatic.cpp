#include "stdafx.h"
#include "CScrollTextStatic.h"

#define REG_BUFF_SIZE_A  4096
const int CScrollTextStatic::nMargin = 3;

IMPLEMENT_DYNAMIC(CScrollTextStatic, CStatic)
CScrollTextStatic::CScrollTextStatic()
{
	m_clrBackground  = RGB(255, 255, 255);
	m_clrText        = RGB(0, 0, 0);
	m_nTextHeight    = 0;
	m_nScrollOffset  = 0;
  	m_eState         = PAUSED;
	m_ClientSize     = CSize(0, 0);

	m_nIndex         = -1;
	m_nThemeCount    = 0; 
}

CScrollTextStatic::~CScrollTextStatic()
{
	if(m_FontText.GetSafeHandle())	m_FontText.DeleteObject();
	
	if(m_FontTitle.GetSafeHandle())	m_FontTitle.DeleteObject();	
}

void CScrollTextStatic::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();

	if(m_FontText.GetSafeHandle() == NULL)
		SetFontInfo("Arial", 10, FW_NORMAL);//SetFontInfo("tahoma", 10, FW_NORMAL);
  
	m_eState = PAUSED;
	SetTimer(1, 0, NULL);
	SetTimer(2, 5000, NULL);
	
	ModifyStyle(0,SS_NOTIFY);
}

void CScrollTextStatic::SetBackGroundColor(COLORREF clrBackGround)
{
	m_clrBackground = clrBackGround;
	Invalidate(FALSE);
}

void CScrollTextStatic::SetTextColor(COLORREF clrText)
{
	m_clrText = clrText;
	Invalidate(FALSE);
}

void CScrollTextStatic::SetFontInfo(const CString& strFontName, int nSize, int nWeight)
{
	if(m_FontText.GetSafeHandle() != NULL)
		m_FontText.DeleteObject();

	LOGFONT logFont;
	memset(&logFont, 0, sizeof(logFont));
	strncpy(logFont.lfFaceName, strFontName, LF_FACESIZE);
	logFont.lfPitchAndFamily = FF_SWISS;
	logFont.lfQuality = ANTIALIASED_QUALITY;
	logFont.lfWeight = nWeight;
	logFont.lfHeight = nSize*10;
	logFont.lfUnderline = TRUE;

	if ( !m_FontText.CreatePointFontIndirect(&logFont) )
		m_FontText.CreateStockObject(SYSTEM_FONT);


	if(m_FontTitle.GetSafeHandle() != NULL)
		m_FontTitle.DeleteObject();

	LOGFONT titleFont;
	memset(&titleFont, 0, sizeof(titleFont));
	strncpy(titleFont.lfFaceName, strFontName, LF_FACESIZE);
	titleFont.lfPitchAndFamily = FF_SWISS;
	titleFont.lfQuality = ANTIALIASED_QUALITY;
	titleFont.lfWeight = FW_BOLD;
	titleFont.lfHeight = nSize*10;

	if ( !m_FontTitle.CreatePointFontIndirect(&titleFont) )
		m_FontTitle.CreateStockObject(SYSTEM_FONT);
}

void CScrollTextStatic::SetInitRolling()
{
	m_nThemeCount = GetThemeCount();

	m_nIndex = 0;
	m_strText = GetThemeString(m_nIndex);
	m_ClientSize = CSize(0, 0);
	Invalidate(FALSE);
}

BEGIN_MESSAGE_MAP(CScrollTextStatic, CStatic)
   ON_WM_ERASEBKGND()
   ON_WM_PAINT()
   ON_WM_TIMER()
   ON_WM_SETCURSOR()
   ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BOOL CScrollTextStatic::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

void CScrollTextStatic::OnPaint()
{
	CPaintDC dc(this);
	CDC dcBackBuffer;
	dcBackBuffer.CreateCompatibleDC(&dc);

	RecalcLayout(&dc);

	CBitmap* pOldBmp = dcBackBuffer.SelectObject(&m_bmpBackBuffer);

	FillBackground(&dcBackBuffer);

	int nOffset = nMargin + m_nScrollOffset;

	nOffset += DrawScrollText(&dcBackBuffer, nOffset) + (nMargin * 2);
	
	dc.BitBlt(0, 0, m_ClientSize.cx, m_ClientSize.cy, &dcBackBuffer, 0, 0, SRCCOPY);

   	dcBackBuffer.SelectObject(pOldBmp);
}

void CScrollTextStatic::RecalcLayout(CDC* pDC)
{	
	CRect rClient;
	GetClientRect(&rClient);
	if ( m_ClientSize != rClient.Size() )
	{
		m_ClientSize = rClient.Size();
		
		if ( m_bmpBackBuffer.GetSafeHandle() != NULL )
			m_bmpBackBuffer.DeleteObject();
		
		m_bmpBackBuffer.CreateCompatibleBitmap(pDC, m_ClientSize.cx, m_ClientSize.cy);

		m_nTextHeight += DrawScrollText(pDC, 0, FALSE);
	}
}

void CScrollTextStatic::FillBackground(CDC* pDC)
{
   	CRect rClient;
   	GetClientRect(&rClient);
   	pDC->FillSolidRect(rClient, m_clrBackground);
}

int CScrollTextStatic::DrawScrollText(CDC* pDC, int nOffset, BOOL bDraw)
{
	CRect rect(nMargin, nOffset, (m_ClientSize.cx - nMargin), m_ClientSize.cy);
	UINT uFlags = bDraw ? DT_RIGHT|DT_EXPANDTABS|DT_NOPREFIX|DT_WORDBREAK : DT_EXPANDTABS|DT_NOCLIP|DT_CALCRECT|DT_NOPREFIX|DT_WORDBREAK;

	CFont* pOldFont = pDC->SelectObject(&m_FontText);
  	pDC->SetTextColor(m_clrText);
	int nHeight = pDC->DrawText(m_strText, &rect, uFlags);
	CSize cSize = pDC->GetTextExtent(m_strText, _tcslen(m_strText));

	if(m_strText == "")
		return nHeight;	

	CRect rTitle;
	CFont* pOldFontTitle = pDC->SelectObject(&m_FontTitle);

	rTitle.left = rect.left;
	rTitle.top = rect.top;
	rTitle.right = (rect.right - rect.left - cSize.cx );
	rTitle.bottom = rect.bottom;
  	pDC->SetTextColor(RGB(0,0,0));
	pDC->DrawText("[Tautan]", &rTitle, uFlags);	
		
	pDC->SetBkMode(TRANSPARENT);

	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldFontTitle);
	
	return nHeight;
}

void CScrollTextStatic::OnTimer(UINT nIDEvent)
{
   if(this == GetCapture())
	   return;
  
   CRect rClient;
   GetClientRect(&rClient);
   
   CPoint ptCursor;
   ::GetCursorPos(&ptCursor);
   	 
   if ( m_ClientSize.cy < m_nTextHeight && 
	    GetTopLevelParent() == GetActiveWindow() && 
		rClient.PtInRect(ptCursor) )
   {      	 
	   SetScrollRange(SB_VERT, 0, (m_nTextHeight - m_ClientSize.cy), FALSE);
       SetScrollPos(SB_VERT, -m_nScrollOffset, TRUE);
       ShowScrollBar(SB_VERT, TRUE);
   }
   else if ( this != GetCapture() )
   {   
   	   ShowScrollBar(SB_VERT, FALSE);
   }

   if ( nIDEvent == 2 )
   {
	   m_eState = SCROLLING;
	   KillTimer(2);
   }

   if ( m_eState == SCROLLING )
   {
	   --m_nScrollOffset;
	  
	   if( (m_nTextHeight + m_nScrollOffset) < 0 )
       {
      	   m_nScrollOffset = m_ClientSize.cy;

		   int nIndex = ClickAdvTab();
		   if(nIndex != -1)
		      m_strText = GetThemeString(nIndex);
	   }

       if ( 0 == m_nScrollOffset || ( (m_nScrollOffset + m_nTextHeight) == m_ClientSize.cy && m_ClientSize.cy < m_nTextHeight) )
       { 
		   m_eState = PAUSED;
    	   SetTimer(2, 5000, NULL);
	   }
	
	   Invalidate(FALSE);
   }
}

BOOL CScrollTextStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	HCURSOR	m_hCursor = LoadCursor(NULL, IDC_HAND);
	if(m_hCursor)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}
	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CScrollTextStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(m_nIndex == -1)
		return;
	
	m_strUrl = GetThemeUrl(m_nIndex);
	if(m_strUrl != "")
		::ShellExecute(NULL, "open", m_strUrl, NULL, NULL, SW_SHOW);

	CStatic::OnLButtonDown(nFlags, point);
}

int CScrollTextStatic::ClickAdvTab()
{
	if(m_nIndex >= (m_nThemeCount-1) || m_nIndex < 0)
		m_nIndex = 0;
	else 
		m_nIndex = m_nIndex + 1;	 

	return m_nIndex;
}

int CScrollTextStatic::GetThemeCount()
{	
	return 22;
}

CString CScrollTextStatic::GetThemeString(int nIndex)
{	
	CString strText = "";

	if(nIndex == 0)
		strText = "Website Pikawarnet";
	else if(nIndex == 1)
		strText = "Info Pikawarnet";
	else if(nIndex == 2)
		strText = "Pika Patch";
	else if(nIndex == 3)
		strText = "Facebook Pikawarnet";
	else if(nIndex == 4)
		strText = "Daftar Pikawarnet";
	else if(nIndex == 5)
		strText = "Lupa Password";
	else if(nIndex == 6)
		strText = "About US";
	else if(nIndex == 7)
		strText = "Pika support";
	else if(nIndex == 8)
		strText = "Server Download";
	else if(nIndex == 9)
		strText = "Client Download";
	else if(nIndex == 10)
		strText = "Manual Update";
	else if(nIndex == 11)
		strText = "Status Warnet";
	else if(nIndex == 12)
		strText = "FAQ Pikawarnet";
	else if(nIndex == 13)
		strText = "Informasi Update";
	else if(nIndex == 14)
		strText = "Pika Mobile";
	else if(nIndex == 15)
		strText = "YM CS 1 Pikawarnet";
	else if(nIndex == 16)
		strText = "YM CS 2 Pikawarnet";
	else if(nIndex == 17)
		strText = "komunitas Pikabilling";
	else if(nIndex == 18)
		strText = "Pika Teknisi";
	else if(nIndex == 19)
		strText = "Teamviewer";
	else if(nIndex == 20)
		strText = "Wordpress Pikabilling";
	else if(nIndex == 21)
		strText = "Video tutorial Pikabilling";

	return strText;
}

CString CScrollTextStatic::GetThemeUrl(int nIndex)
{		
	CString strUrl = "";
	
	if(nIndex == 0)
		strUrl = "http://pikawarnet.com/";
	else if(nIndex == 1)
		strUrl = "http://pikawarnet.com/_billing/main.jsp";
	else if(nIndex == 2)
		strUrl = "http://pikawarnet.com/_gamepatch/main.jsp";
	else if(nIndex == 3)
		strUrl = "https://www.facebook.com/pikawarnet";
	else if(nIndex == 4)
		strUrl = "http://pikawarnet.com/_member/join.jsp";
	else if(nIndex == 5)
		strUrl = "http://pikawarnet.com/_member/search.jsp";
	else if(nIndex == 6)
		strUrl = "http://pikawarnet.com/_etc/aboutus.jsp";
	else if(nIndex == 7)
		strUrl = "http://pikawarnet.com/_laynanpelanggan/cs.jsp";
	else if(nIndex == 8)
		strUrl = "http://pikadown.pikawarnet.com/downpackage/pikaManager.exe";
	else if(nIndex == 9)
		strUrl = "http://pikadown.pikawarnet.com/downpackage/pikaclient.exe";
	else if(nIndex == 10)
		strUrl = "http://pikadown.pikawarnet.com/downpackage/updatefile.exe";
	else if(nIndex == 11)
		strUrl = "http://www.pikawarnet.com/_member/pop_login.jsp?actionURI=/_statusWarnet/laporanHariIni.jsp";
	else if(nIndex == 12)
		strUrl = "http://pikawarnet.com/_laynanpelanggan/faq.jsp";
	else if(nIndex == 13)
		strUrl = "http://pikawarnet.com/_laynanpelanggan/notice_list.jsp?section=NOTICE";
	else if(nIndex == 14)
		strUrl = "http://pikawarnet.com/_mobile/information.jsp";
	else if(nIndex == 15)
		strUrl = "ymsgr:sendIM?cs1.pika";
	else if(nIndex == 16)
		strUrl = "ymsgr:sendIM?cs2.pika";
	else if(nIndex == 17)
		strUrl = "https://www.facebook.com/groups/pikabilling/";
	else if(nIndex == 18)
		strUrl = "https://www.facebook.com/pika.teknisi?fref=ts";
	else if(nIndex == 19)
		strUrl = "http://downloadus1.teamviewer.com/download/TeamViewer_Setup.exe";
	else if(nIndex == 20)
		strUrl = "http://pikabilling.wordpress.com/";
	else if(nIndex == 21)
		strUrl = "http://www.youtube.com/user/PIKAWarnet?feature=watch";

	return strUrl;
}
