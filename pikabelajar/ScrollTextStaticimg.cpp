#include "stdafx.h"
#include "ScrollTextStaticimg.h"
#include "Resource.h"

#define REG_BUFF_SIZE_A  4096
const int CScrollTextStaticimg::nMargin = 3;

IMPLEMENT_DYNAMIC(CScrollTextStaticimg, CStatic)
CScrollTextStaticimg::CScrollTextStaticimg()
{
	m_clrBackground  = RGB(248,246,232);//RGB(255, 255, 255);
	m_clrText        = RGB(0, 0, 0);
	m_nTextHeight    = 0;
	m_nScrollOffset  = 0;
  	m_eState         = PAUSED;
	m_ClientSize     = CSize(0, 0);

	m_nIndex         = -1;
	m_nThemeCount    = 0; 

	m_hMainBmp = NULL;
}

CScrollTextStaticimg::~CScrollTextStaticimg()
{
	m_picImg.FreePictureData();

	if(m_bmpMain.GetSafeHandle() != NULL)
	{
		m_bmpMain.DeleteObject();
	}	

	if(m_hMainBmp != NULL)
	{
		DeleteObject(m_hMainBmp); 
		m_hMainBmp = NULL;
	}

	if(m_FontText.GetSafeHandle())	m_FontText.DeleteObject();
	
	if(m_FontTitle.GetSafeHandle())	m_FontTitle.DeleteObject();	
}

void CScrollTextStaticimg::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();

	if(m_FontText.GetSafeHandle() == NULL)
		SetFontInfo("Arial", 10, FW_NORMAL);//SetFontInfo("Tahoma", 10, FW_NORMAL);
  
	m_eState = PAUSED;
	SetTimer(1, 0, NULL);
	SetTimer(2, 5000, NULL);
	
	ModifyStyle(0,SS_NOTIFY);
}

void CScrollTextStaticimg::SetBackGroundColor(COLORREF clrBackGround)
{
	m_clrBackground = clrBackGround;
	Invalidate(FALSE);
}

void CScrollTextStaticimg::SetTextColor(COLORREF clrText)
{
	m_clrText = clrText;
	Invalidate(FALSE);
}

void CScrollTextStaticimg::SetTitleImage(CString strImagePath)
{
	ReleaseFreeImage();

	m_picImg.Load(strImagePath); 
	m_hMainBmp = (HBITMAP)m_picImg.GetSafeHandle();
	if(m_hMainBmp)
		m_bmpMain.Attach(m_hMainBmp);

	BITMAP bm;
	m_bmpMain.GetObject(sizeof(BITMAP) , &bm);
	m_nBx = bm.bmWidth;
	m_nBy = bm.bmHeight;		
	m_rPicBg = CRect(0, 0, m_nBx, m_nBy);

	Invalidate(FALSE);
}

void CScrollTextStaticimg::ReleaseFreeImage()
{
	m_picImg.FreePictureData();

	if(m_bmpMain.GetSafeHandle() != NULL)
	{
		m_bmpMain.DeleteObject();
	}	

	if(m_hMainBmp != NULL)
	{
		DeleteObject(m_hMainBmp); 
		m_hMainBmp = NULL;
	}
}

BOOL CScrollTextStaticimg::SetTitleImage(UINT ResourceName, CString ResourceType)
{
	ReleaseFreeImage();

	if (!m_picImg.Load(ResourceName, ResourceType))
		return FALSE;

	m_hMainBmp = (HBITMAP)m_picImg.GetSafeHandle();
	if(m_hMainBmp)
		m_bmpMain.Attach(m_hMainBmp);

	BITMAP bm;
	m_bmpMain.GetObject(sizeof(BITMAP) , &bm);
	m_nBx = bm.bmWidth;
	m_nBy = bm.bmHeight;		
	m_rPicBg = CRect(0, 0, m_nBx, m_nBy);

	Invalidate();

	return TRUE;
}

void CScrollTextStaticimg::SetFontInfo(const CString& strFontName, int nSize, int nWeight)
{
	//내용 폰트 
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


	//제목 폰트
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

void CScrollTextStaticimg::SetInitRolling()
{
	m_nThemeCount = GetThemeCount();

	m_nIndex = 0;
	m_strText = "";//GetThemeString(m_nIndex);
	m_ClientSize = CSize(0, 0);
	Invalidate(FALSE);
}

BEGIN_MESSAGE_MAP(CScrollTextStaticimg, CStatic)
   ON_WM_ERASEBKGND()
   ON_WM_PAINT()
   ON_WM_TIMER()
   ON_WM_SETCURSOR()
   ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BOOL CScrollTextStaticimg::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

void CScrollTextStaticimg::OnPaint()
{
	CPaintDC dc(this);
	CDC dcBackBuffer;
	dcBackBuffer.CreateCompatibleDC(&dc);

	RecalcLayout(&dc);

	CBitmap* pOldBmp = dcBackBuffer.SelectObject(&m_bmpBackBuffer);

	FillBackground(&dcBackBuffer);

	int nOffset = nMargin + m_nScrollOffset;

	DrawTitleImage(&dcBackBuffer, nOffset);

	//nOffset += DrawScrollText(&dcBackBuffer, nOffset) + (nMargin * 2);
	
	dc.BitBlt(0, 0, m_ClientSize.cx, m_ClientSize.cy, &dcBackBuffer, 0, 0, SRCCOPY);

   	dcBackBuffer.SelectObject(pOldBmp);
}

void CScrollTextStaticimg::RecalcLayout(CDC* pDC)
{	
	CRect rClient;
	GetClientRect(&rClient);
	if ( m_ClientSize != rClient.Size() )
	{
		m_ClientSize = rClient.Size();
		
		if ( m_bmpBackBuffer.GetSafeHandle() != NULL )
			m_bmpBackBuffer.DeleteObject();
		
		m_bmpBackBuffer.CreateCompatibleBitmap(pDC, m_ClientSize.cx, m_ClientSize.cy);

		DrawTitleImage(pDC, 0, FALSE);
		//m_nTextHeight += DrawScrollText(pDC, 0, FALSE);
	}
}

void CScrollTextStaticimg::FillBackground(CDC* pDC)
{
   	CRect rClient;
   	GetClientRect(&rClient);
   	pDC->FillSolidRect(rClient, m_clrBackground);
}

int CScrollTextStaticimg::DrawTitleImage(CDC* pDC, int nOffset, BOOL bDraw)
{
	CDC MemDC;	
	MemDC.CreateCompatibleDC(pDC);

	CBitmap* pbmpOld = MemDC.SelectObject(&m_bmpMain);	
    
	pDC->BitBlt(0, nOffset, m_nBx, m_nBy, &MemDC, 0, 0, SRCCOPY);

	//왼쪽 정렬일때 - 텍스트가 왼쪽에 있어서 x좌표를 구해야 한다.
	//pDC->BitBlt(350, nOffset, m_nBx, m_nBy, &MemDC, 0, 0, SRCCOPY);

	//오른쪽 정렬일때
	pDC->BitBlt(0, nOffset, m_nBx/4, m_nBy, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pbmpOld);
	return m_nBy;
}

int CScrollTextStaticimg::DrawScrollText(CDC* pDC, int nOffset, BOOL bDraw)
{
	CRect rect(nMargin, nOffset, (m_ClientSize.cx - nMargin), m_ClientSize.cy);
	UINT uFlags = bDraw ? DT_RIGHT|DT_EXPANDTABS|DT_NOPREFIX|DT_WORDBREAK : DT_EXPANDTABS|DT_NOCLIP|DT_CALCRECT|DT_NOPREFIX|DT_WORDBREAK;

	//내용 
	CFont* pOldFont = pDC->SelectObject(&m_FontText);
  	pDC->SetTextColor(m_clrText);
	int nHeight = pDC->DrawText(m_strText, &rect, uFlags);
	CSize cSize = pDC->GetTextExtent(m_strText, _tcslen(m_strText));

	if(m_strText == "")
		return nHeight;	

	//제목
	CRect rTitle;
	CFont* pOldFontTitle = pDC->SelectObject(&m_FontTitle);

	rTitle.left = rect.left;
	rTitle.top = rect.top;
	rTitle.right = (rect.right - rect.left - cSize.cx );
	rTitle.bottom = rect.bottom;
  	pDC->SetTextColor(RGB(0,0,0));
	pDC->DrawText("", &rTitle, uFlags);	
	
	pDC->SetBkMode(TRANSPARENT);

	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldFontTitle);
	
	return nHeight;
}

void CScrollTextStaticimg::OnTimer(UINT nIDEvent)
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
		   {
			   
			   if( nIndex == 0 )
				   SetTitleImage(IDR_GIF1, "GIF");
			   else if( nIndex == 1 )
			   	   SetTitleImage(IDR_GIF2, "GIF");
			   else if( nIndex == 2 )
			   	   SetTitleImage(IDR_GIF3, "GIF");
			   else if( nIndex == 3 )
			   	   SetTitleImage(IDR_GIF4, "GIF");	
			  			  			  
			   m_strText = "";//GetThemeString(nIndex);
		   }
	   }

       if ( 0 == m_nScrollOffset || ( (m_nScrollOffset + m_nTextHeight) == m_ClientSize.cy && m_ClientSize.cy < m_nTextHeight) )
       { 
		   m_eState = PAUSED;
    	   SetTimer(2, 5000, NULL);
	   }
	
	   Invalidate(FALSE);
   }
}

BOOL CScrollTextStaticimg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	HCURSOR	m_hCursor = LoadCursor(NULL, IDC_HAND);
	if(m_hCursor)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CScrollTextStaticimg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(m_nIndex == -1)
		return;
	
	m_strUrl = GetThemeUrl(m_nIndex);
	if(m_strUrl != "")
		::ShellExecute(NULL, "open", m_strUrl, NULL, NULL, SW_SHOW);

	CStatic::OnLButtonDown(nFlags, point);
}

int CScrollTextStaticimg::ClickAdvTab()
{
	if(m_nIndex >= (m_nThemeCount-1) || m_nIndex < 0)
		m_nIndex = 0;
	else 
		m_nIndex = m_nIndex + 1;	 

	return m_nIndex;
}

int CScrollTextStaticimg::GetThemeCount()
{	
	return 4;
}

CString CScrollTextStaticimg::GetThemeString(int nIndex)
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

	return strText;
}

CString CScrollTextStaticimg::GetThemeUrl(int nIndex)
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
	
	return strUrl;
}
