#include "stdafx.h"
#include "SplashScreenEx.h"

#ifndef AW_HIDE
	#define AW_HIDE 0x00010000
	#define AW_BLEND 0x00080000
#endif

#ifndef CS_DROPSHADOW
	#define CS_DROPSHADOW   0x00020000
#endif


IMPLEMENT_DYNAMIC(CSplashScreenEx, CWnd)
CSplashScreenEx::CSplashScreenEx()
{
	m_pWndParent=NULL;
	m_strText="";
	m_hRegion=0;
	m_nBitmapWidth=0;
	m_nBitmapHeight=0;
	m_nxPos=0;
	m_nyPos=0;
	m_dwTimeout=2000;
	m_dwStyle=0;
	m_rcText.SetRect(0,0,0,0);
	m_crTextColor=RGB(0,0,0);
	m_uTextFormat=DT_CENTER | DT_VCENTER | DT_WORDBREAK;

	HMODULE hUser32 = GetModuleHandle(_T("USER32.DLL"));
	if (hUser32!=NULL)
		m_fnAnimateWindow = (FN_ANIMATE_WINDOW)GetProcAddress(hUser32, _T("AnimateWindow"));
	else
		m_fnAnimateWindow = NULL;

	SetTextDefaultFont();
}

CSplashScreenEx::~CSplashScreenEx()
{
}

BOOL CSplashScreenEx::Create(CWnd *pWndParent,LPCTSTR szText,DWORD dwTimeout,DWORD dwStyle)
{
	ASSERT(pWndParent!=NULL);
	m_pWndParent = pWndParent;
	
	if (szText!=NULL)
		m_strText = szText;
	else
		m_strText="";

	m_dwTimeout = dwTimeout;
	m_dwStyle = dwStyle;
	
	WNDCLASSEX wcx; 

	wcx.cbSize = sizeof(wcx);
	wcx.lpfnWndProc = AfxWndProc;
	wcx.style = CS_DBLCLKS|CS_SAVEBITS;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = AfxGetInstanceHandle();
	wcx.hIcon = NULL;
	wcx.hCursor = LoadCursor(NULL,IDC_ARROW);
	wcx.hbrBackground=::GetSysColorBrush(COLOR_WINDOW);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = "SplashScreenExClass";
	wcx.hIconSm = NULL;

	if (m_dwStyle & CSS_SHADOW)
		wcx.style|=CS_DROPSHADOW;

	ATOM classAtom = RegisterClassEx(&wcx);
      
	if (classAtom==NULL)
	{
		if (m_dwStyle & CSS_SHADOW)
		{
			wcx.style &= ~CS_DROPSHADOW;
			classAtom = RegisterClassEx(&wcx);
		}
		else
			return FALSE;
	}

	if (!CreateEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST,"SplashScreenExClass",NULL,WS_POPUP,0,0,0,0,pWndParent->m_hWnd,NULL))
		return FALSE;

	return TRUE;
}

BOOL CSplashScreenEx::SetBitmap(UINT nBitmapID,short red,short green,short blue)
{
	BITMAP bm;

	m_bitmap.DeleteObject();
	if (!m_bitmap.LoadBitmap(nBitmapID))
		return FALSE;
	
	GetObject(m_bitmap.GetSafeHandle(), sizeof(bm), &bm);
	m_nBitmapWidth=bm.bmWidth;
	m_nBitmapHeight=bm.bmHeight;
	m_rcText.SetRect(0,0,bm.bmWidth,bm.bmHeight);
	
	if (m_dwStyle & CSS_CENTERSCREEN)
	{
		m_nxPos=(GetSystemMetrics(SM_CXFULLSCREEN)-bm.bmWidth)/2;
		m_nyPos=(GetSystemMetrics(SM_CYFULLSCREEN)-bm.bmHeight)/2;
	}
	else if (m_dwStyle & CSS_CENTERAPP)
	{
		CRect rcParentWindow;
		ASSERT(m_pWndParent!=NULL);
		m_pWndParent->GetWindowRect(&rcParentWindow);
		m_nxPos=rcParentWindow.left+(rcParentWindow.right-rcParentWindow.left-bm.bmWidth)/2;
		m_nyPos=rcParentWindow.top+(rcParentWindow.bottom-rcParentWindow.top-bm.bmHeight)/2;
	}

	if (red!=-1 && green!=-1 && blue!=-1)
	{
		m_hRegion=CreateRgnFromBitmap((HBITMAP)m_bitmap.GetSafeHandle(),RGB(red,green,blue));
		SetWindowRgn(m_hRegion, TRUE);
	}

	return TRUE;
}

BOOL CSplashScreenEx::SetBitmap(LPCTSTR szFileName,short red,short green,short blue)
{
	BITMAP bm;
	HBITMAP hBmp;

	hBmp=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),szFileName,IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
	if (!hBmp)
		return FALSE;

	m_bitmap.DeleteObject();
	m_bitmap.Attach(hBmp);
	
	GetObject(m_bitmap.GetSafeHandle(), sizeof(bm), &bm);
	m_nBitmapWidth=bm.bmWidth;
	m_nBitmapHeight=bm.bmHeight;
	m_rcText.SetRect(0,0,bm.bmWidth,bm.bmHeight);
	
	if (m_dwStyle & CSS_CENTERSCREEN)
	{
		m_nxPos=(GetSystemMetrics(SM_CXFULLSCREEN)-bm.bmWidth)/2;
		m_nyPos=(GetSystemMetrics(SM_CYFULLSCREEN)-bm.bmHeight)/2;
	}
	else if (m_dwStyle & CSS_CENTERAPP)
	{
		CRect rcParentWindow;
		ASSERT(m_pWndParent!=NULL);
		m_pWndParent->GetWindowRect(&rcParentWindow);
		m_nxPos=rcParentWindow.left+(rcParentWindow.right-rcParentWindow.left-bm.bmWidth)/2;
		m_nyPos=rcParentWindow.top+(rcParentWindow.bottom-rcParentWindow.top-bm.bmHeight)/2;
	}

	if (red!=-1 && green!=-1 && blue!=-1)
	{
		m_hRegion=CreateRgnFromBitmap((HBITMAP)m_bitmap.GetSafeHandle(),RGB(red,green,blue));
		SetWindowRgn(m_hRegion,TRUE);
	}

	return TRUE;
}

void CSplashScreenEx::SetTextFont(LPCTSTR szFont,int nSize,int nStyle)
{
	LOGFONT lf;
	m_myFont.DeleteObject();
	m_myFont.CreatePointFont(nSize,szFont);
	m_myFont.GetLogFont(&lf);
	
	if (nStyle & CSS_TEXT_BOLD)
		lf.lfWeight = FW_BOLD;
	else
		lf.lfWeight = FW_NORMAL;
	
	if (nStyle & CSS_TEXT_ITALIC)
		lf.lfItalic=TRUE;
	else
		lf.lfItalic=FALSE;
	
	if (nStyle & CSS_TEXT_UNDERLINE)
		lf.lfUnderline=TRUE;
	else
		lf.lfUnderline=FALSE;

	m_myFont.DeleteObject();
	m_myFont.CreateFontIndirect(&lf);
}

void CSplashScreenEx::SetTextDefaultFont()
{
	LOGFONT lf;
	CFont *myFont=CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	myFont->GetLogFont(&lf);
	m_myFont.DeleteObject();
	m_myFont.CreateFontIndirect(&lf);
}

void CSplashScreenEx::SetText(LPCTSTR szText)
{
	m_strText=szText;
	RedrawWindow();
}

void CSplashScreenEx::SetTextColor(COLORREF crTextColor)
{
	m_crTextColor=crTextColor;
	RedrawWindow();
}

void CSplashScreenEx::SetTextRect(CRect& rcText)
{
	m_rcText=rcText;
	RedrawWindow();
}

void CSplashScreenEx::SetTextFormat(UINT uTextFormat)
{
	m_uTextFormat=uTextFormat;
}

void CSplashScreenEx::Show()
{
	SetWindowPos(NULL,m_nxPos,m_nyPos,m_nBitmapWidth,m_nBitmapHeight,SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_NOACTIVATE);

	if ((m_dwStyle & CSS_FADEIN) && (m_fnAnimateWindow!=NULL))
	{
		m_fnAnimateWindow(m_hWnd,500,AW_BLEND);
	}
	else
		ShowWindow(SW_SHOW);
	
	if (m_dwTimeout!=0)
		SetTimer(0,m_dwTimeout,NULL);
}

void CSplashScreenEx::Hide()
{
	if ((m_dwStyle & CSS_FADEOUT) && (m_fnAnimateWindow!=NULL))
		m_fnAnimateWindow(m_hWnd,200,AW_HIDE | AW_BLEND);
	else
		ShowWindow(SW_HIDE);

	DestroyWindow();
}

HRGN CSplashScreenEx::CreateRgnFromBitmap(HBITMAP hBmp, COLORREF color)
{
	if (!hBmp) return NULL;

	BITMAP bm;
	GetObject( hBmp, sizeof(BITMAP), &bm );	

	CDC dcBmp;
	dcBmp.CreateCompatibleDC(GetDC());
	dcBmp.SelectObject(hBmp);		

	const DWORD RDHDR = sizeof(RGNDATAHEADER);
	const DWORD MAXBUF = 40;	
	LPRECT	pRects;								
	DWORD	cBlocks = 0;			

	INT		i, j;				
	INT		first = 0;			

	bool	wasfirst = false;	
	bool	ismask;				


	RGNDATAHEADER* pRgnData = (RGNDATAHEADER*)new BYTE[ RDHDR + ++cBlocks * MAXBUF * sizeof(RECT) ];
	memset( pRgnData, 0, RDHDR + cBlocks * MAXBUF * sizeof(RECT) );

	pRgnData->dwSize	= RDHDR;
	pRgnData->iType		= RDH_RECTANGLES;
	pRgnData->nCount	= 0;
	for ( i = 0; i < bm.bmHeight; i++ )
		for ( j = 0; j < bm.bmWidth; j++ ){
			
			ismask=(dcBmp.GetPixel(j,bm.bmHeight-i-1)!=color);
		
			if (wasfirst && ((ismask && (j==(bm.bmWidth-1)))||(ismask ^ (j<bm.bmWidth)))){
				
				pRects = (LPRECT)((LPBYTE)pRgnData + RDHDR);
			
				pRects[ pRgnData->nCount++ ] = CRect( first, bm.bmHeight - i - 1, j+(j==(bm.bmWidth-1)), bm.bmHeight - i );
			
				if ( pRgnData->nCount >= cBlocks * MAXBUF ){
					LPBYTE pRgnDataNew = new BYTE[ RDHDR + ++cBlocks * MAXBUF * sizeof(RECT) ];
					memcpy( pRgnDataNew, pRgnData, RDHDR + (cBlocks - 1) * MAXBUF * sizeof(RECT) );
					delete pRgnData;
					pRgnData = (RGNDATAHEADER*)pRgnDataNew;
				}
				wasfirst = false;
			} else if ( !wasfirst && ismask ){	
				first = j;
				wasfirst = true;
			}
		}
		dcBmp.DeleteDC();
	
		HRGN hRgn=CreateRectRgn(0, 0, 0, 0);
		ASSERT( hRgn!=NULL );
		pRects = (LPRECT)((LPBYTE)pRgnData + RDHDR);
		for(i=0;i<(int)pRgnData->nCount;i++)
		{
			HRGN hr=CreateRectRgn(pRects[i].left, pRects[i].top, pRects[i].right, pRects[i].bottom);
			VERIFY(CombineRgn(hRgn, hRgn, hr, RGN_OR)!=ERROR);
			if (hr) DeleteObject(hr);
		}
		ASSERT( hRgn!=NULL );
	
		delete pRgnData;
		return hRgn;
}

void CSplashScreenEx::DrawWindow(CDC *pDC)
{
	CDC memDC;
	CBitmap *pOldBitmap;
	
	memDC.CreateCompatibleDC(pDC);
	pOldBitmap=memDC.SelectObject(&m_bitmap);
	pDC->BitBlt(0,0,m_nBitmapWidth,m_nBitmapHeight,&memDC,0,0,SRCCOPY);
	memDC.SelectObject(pOldBitmap);

	CFont *pOldFont;
	pOldFont=pDC->SelectObject(&m_myFont);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_crTextColor);

	pDC->DrawText(m_strText,-1,m_rcText,m_uTextFormat);

	pDC->SelectObject(pOldFont);

}
BEGIN_MESSAGE_MAP(CSplashScreenEx, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_MESSAGE(WM_PRINTCLIENT, OnPrintClient)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CSplashScreenEx::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CSplashScreenEx::OnPaint()
{
	CPaintDC dc(this); 
	DrawWindow(&dc);
}

LRESULT CSplashScreenEx::OnPrintClient(WPARAM wParam, LPARAM lParam)
{
	CDC* pDC = CDC::FromHandle((HDC)wParam);
	DrawWindow(pDC);
	return 1;
}

BOOL CSplashScreenEx::PreTranslateMessage(MSG* pMsg)
{
	if (m_dwStyle & CSS_HIDEONCLICK)
	{
		if (pMsg->message == WM_KEYDOWN ||
			pMsg->message == WM_SYSKEYDOWN ||
			pMsg->message == WM_LBUTTONDOWN ||
			pMsg->message == WM_RBUTTONDOWN ||
			pMsg->message == WM_MBUTTONDOWN ||
			pMsg->message == WM_NCLBUTTONDOWN ||
			pMsg->message == WM_NCRBUTTONDOWN ||
			pMsg->message == WM_NCMBUTTONDOWN)
		{
			Hide();
			return TRUE;
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

void CSplashScreenEx::OnTimer(UINT nIDEvent)
{
	KillTimer(0);
	Hide();
}

void CSplashScreenEx::PostNcDestroy()
{
	CWnd::PostNcDestroy();
	delete this;
}