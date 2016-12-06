#include "stdafx.h"
#include "LeftPictureStatic.h"
#include "Resource.h"
#include "pikabelajar.h"
#include "pikabelajarDlg.h"

CLeftPictureStatic::CLeftPictureStatic()
{	
	m_hMainBmp = NULL;
	m_nX = 0;
	m_nY = 0;	
	m_bClick = FALSE;
	m_bCursor = FALSE;
	m_hCursor = NULL;
	m_bButtonClick = FALSE;
	m_bMoveRight = FALSE;
	m_nResizeWidth = 0;
	m_nResizeHeight = 0; 
}

CLeftPictureStatic::~CLeftPictureStatic()
{
	ReleaseFreeImage();
}

BEGIN_MESSAGE_MAP(CLeftPictureStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

void CLeftPictureStatic::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();
    ModifyStyle(0, SS_OWNERDRAW);
}

void CLeftPictureStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	CStatic::OnLButtonDown(nFlags, point);
}

CLeftPictureStatic& CLeftPictureStatic::SetPictureStaticClick(BOOL bClick)
{
	m_bClick = bClick;

	if (bClick)
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);

	return *this;
}

BOOL CLeftPictureStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(m_bCursor == TRUE)
	{
		if (m_hCursor)
		{
			::SetCursor(m_hCursor);
			return TRUE;
		}
	}

	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CLeftPictureStatic::SetPictureStaticCursor(BOOL bCursor)
{
	m_bCursor = bCursor;
	m_hCursor = AfxGetApp()->LoadCursor(IDC_HAND);
}

BOOL CLeftPictureStatic::LoadImage(CString strImagePath)
{
	if(!m_Picture.Load(strImagePath))
		return FALSE;

	m_hMainBmp = (HBITMAP)m_Picture.GetSafeHandle();
	if(m_hMainBmp)
	{
		if( (m_nResizeWidth > 0) && (m_nResizeHeight > 0) )
			m_hMainBmp = getResizeBitmap(m_hMainBmp, m_nResizeWidth , m_nResizeHeight);

		m_bmpMain.Attach(m_hMainBmp);
	}

	BITMAP bit;
	GetObject(m_hMainBmp, sizeof(BITMAP), &bit);
	int nWidth = bit.bmWidth;
	int nHeight = bit.bmHeight;
	m_rPicBg = CRect(0, 0, nWidth, nHeight);

	Invalidate();
    

	//origial
	/*
	if(!m_Picture.Load(strImagePath))
		return FALSE;

	m_hMainBmp = (HBITMAP)m_Picture.GetSafeHandle();
	if(m_hMainBmp)
		m_bmpMain.Attach(m_hMainBmp);

	BITMAP bit;
	GetObject(m_hMainBmp, sizeof(BITMAP), &bit);
	int nWidth = bit.bmWidth;
	int nHeight = bit.bmHeight;
	m_rPicBg = CRect(0, 0, nWidth, nHeight);

	Invalidate();
	*/

	return TRUE;
}

BOOL CLeftPictureStatic::LoadImage(UINT ResourceName, CString ResourceType)
{
	if (!m_Picture.Load(ResourceName, ResourceType))
		return FALSE;

	m_hMainBmp = (HBITMAP)m_Picture.GetSafeHandle();
	if(m_hMainBmp)
	{
		if( (m_nResizeWidth > 0) && (m_nResizeHeight > 0) )
			m_hMainBmp = getResizeBitmap(m_hMainBmp, m_nResizeWidth , m_nResizeHeight);

		m_bmpMain.Attach(m_hMainBmp);
	}

	BITMAP bit;
	GetObject(m_hMainBmp, sizeof(BITMAP), &bit);
	int nWidth = bit.bmWidth;
	int nHeight = bit.bmHeight;
	m_rPicBg = CRect(0, 0, nWidth, nHeight);

	Invalidate();
	
	//origial
	/*
	if (!m_Picture.Load(ResourceName, ResourceType))
		return FALSE;

	m_hMainBmp = (HBITMAP)m_Picture.GetSafeHandle();
	if(m_hMainBmp)
		m_bmpMain.Attach(m_hMainBmp);

	BITMAP bit;
	GetObject(m_hMainBmp, sizeof(BITMAP), &bit);
	int nWidth = bit.bmWidth;
	int nHeight = bit.bmHeight;
	m_rPicBg = CRect(0, 0, nWidth, nHeight);

	Invalidate();
	*/

	return TRUE;
}

void CLeftPictureStatic::StaticRoundSize(int nX, int nY)
{	
	m_nX = nX;
	m_nY = nY;
}

void CLeftPictureStatic::GetPictureRect(CRect& rPos)
{
	rPos = m_rPicBg;
}

void CLeftPictureStatic::ReleaseFreeImage()
{
	m_Picture.FreePictureData();

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

void CLeftPictureStatic::OnPaint() 
{
	CPaintDC dc(this);
}

bool CLeftPictureStatic::SleepEx( DWORD dwMilliseconds )
{
	if( dwMilliseconds == 0 ) return TRUE;

	DWORD t1 = GetTickCount();
	while(1)
	{
		DWORD t2 = GetTickCount();
		if( t2 < t1 || (t2 - t1) > dwMilliseconds )break;
		
		MSG msg;
		if( PeekMessage(&msg, NULL,  0, 0, PM_NOREMOVE) ) 
		{
			GetMessage( &msg, NULL,  0, 0 );
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
		else
		{
			Sleep(1);
		}
	}
	return TRUE;
}

bool CLeftPictureStatic::MagicFunLeft( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep )
{
	for( int i=0; i< width/nStep; i++ )
	{
		BitBlt( hDestDC , xd+width-(i+1)*nStep , yd , (i+1)*nStep , height , hSrcDC , x , y , SRCCOPY );
		SleepEx( nDelay );
	}
	BitBlt( hDestDC , xd , yd , width , height , hSrcDC , x, y , SRCCOPY );
	return TRUE;
}

bool CLeftPictureStatic::MagicFunRight( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep )
{
	for( int i=0; i< width/nStep; i++ )
	{
		BitBlt( hDestDC , xd , yd , (i+1)*nStep , height , hSrcDC , x+width-(i+1)*nStep , y , SRCCOPY );
		SleepEx( nDelay );
	}
	BitBlt( hDestDC , xd , yd , width , height , hSrcDC , x , y , SRCCOPY );
	return TRUE;
}

BOOL CLeftPictureStatic::OnEraseBkgnd(CDC* pDC)
{
	CDC MemDC;	
	MemDC.CreateCompatibleDC(pDC);

	BITMAP bit;
	int bx, by;
	GetObject(m_hMainBmp, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	CBitmap* pbmpOld = MemDC.SelectObject(&m_bmpMain);	
	
	CRect rc;
	GetClientRect(rc);

	if(m_bButtonClick)
	{
		if(m_bMoveRight)
			MagicFunRight(MemDC.m_hDC , 0 , 0 , pDC->m_hDC , 0 , 0 , rc.Width() , rc.Height() , 1, 20);
		else
			MagicFunLeft(MemDC.m_hDC , 0 , 0 , pDC->m_hDC , 0 , 0 , rc.Width() , rc.Height() , 1, 20);

		m_bButtonClick = FALSE; 
	}
	else
		pDC->BitBlt(0, 0, bx, by, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pbmpOld);
	ReleaseDC(pDC);
	return TRUE;
}

void CLeftPictureStatic::OnInvalidate()
{
	Invalidate();
}

void CLeftPictureStatic::SetButtonClick(BOOL bClick)
{
	m_bButtonClick = bClick;
}

void CLeftPictureStatic::SetPictureMoveRight(BOOL bRight)
{
	m_bMoveRight = bRight;
}

void CLeftPictureStatic::SetPhotoResize(int nResizeWidth, int nResizeHeight)
{
	m_nResizeWidth = nResizeWidth;
	m_nResizeHeight = nResizeHeight; 
}

HBITMAP CLeftPictureStatic::getResizeBitmap(HBITMAP hBitmap, const unsigned int aW, const unsigned int aH)
{
	// Create a memory DC compatible with the display
	CDC sourceDC, destDC;
	sourceDC.CreateCompatibleDC( NULL );
	destDC.CreateCompatibleDC( NULL );
	// Get logical coordinates
	BITMAP bm;
	::GetObject( hBitmap, sizeof( bm ), &bm );
	// Create a bitmap to hold the result
	HBITMAP hbmResult = ::CreateCompatibleBitmap(CClientDC(NULL), aW, aH);
	// Select bitmaps into the DCs
	HBITMAP hbmOldSource = (HBITMAP)::SelectObject( sourceDC.m_hDC, hBitmap );
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject( destDC.m_hDC, hbmResult );
	
	destDC.SetStretchBltMode( HALFTONE);//for better output
	destDC.StretchBlt(0,0,aW,aH,&sourceDC,0,0,bm.bmWidth, bm.bmHeight,SRCCOPY);
	// Reselect the old bitmaps
	::SelectObject( sourceDC.m_hDC, hbmOldSource );
	::SelectObject( destDC.m_hDC, hbmOldDest );
	return hbmResult;
}