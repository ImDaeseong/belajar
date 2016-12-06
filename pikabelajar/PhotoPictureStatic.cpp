#include "stdafx.h"
#include "PhotoPictureStatic.h"
#include "Resource.h"
#include "pikabelajar.h"
#include "pikabelajarDlg.h"

CPhotoPictureStatic::CPhotoPictureStatic()
{	
	m_hMainBmp = NULL;
	m_nX = 0;
	m_nY = 0;	
	m_bClick = FALSE;
	m_bCursor = FALSE;
	m_hCursor = NULL;
	m_bButtonClick = FALSE;
}

CPhotoPictureStatic::~CPhotoPictureStatic()
{
	ReleaseFreeImage();
}

BEGIN_MESSAGE_MAP(CPhotoPictureStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CPhotoPictureStatic::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();
    ModifyStyle(0, SS_OWNERDRAW);

	//SetTimer(1, 5000, NULL);
}

void CPhotoPictureStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//::ShellExecute(NULL, "open", strUrl, NULL, NULL, SW_SHOW);
	CStatic::OnLButtonDown(nFlags, point);
}

CPhotoPictureStatic& CPhotoPictureStatic::SetPictureStaticClick(BOOL bClick)
{
	m_bClick = bClick;

	if (bClick)
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);

	return *this;
}

BOOL CPhotoPictureStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
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

void CPhotoPictureStatic::SetPictureStaticCursor(BOOL bCursor)
{
	m_bCursor = bCursor;
	m_hCursor = AfxGetApp()->LoadCursor(IDC_CURSORZOOM);//m_hCursor = LoadCursor(NULL, IDC_HAND);
}

BOOL CPhotoPictureStatic::LoadImage(CString strImagePath)
{
	if(!m_picImg.Load(strImagePath))
		return FALSE;

	m_hMainBmp = (HBITMAP)m_picImg.GetSafeHandle();
	if(m_hMainBmp)
		m_bmpMain.Attach(m_hMainBmp);

	BITMAP bit;
	GetObject(m_hMainBmp, sizeof(BITMAP), &bit);
	int nWidth = bit.bmWidth;
	int nHeight = bit.bmHeight;
	m_rPicBg = CRect(0, 0, nWidth, nHeight);

	Invalidate();

	return TRUE;
}

BOOL CPhotoPictureStatic::LoadImage(UINT ResourceName, CString ResourceType)
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

void CPhotoPictureStatic::StaticRoundSize(int nX, int nY)
{	
	m_nX = nX;
	m_nY = nY;
}

void CPhotoPictureStatic::GetPictureRect(CRect& rPos)
{
	rPos = m_rPicBg;
}

void CPhotoPictureStatic::ReleaseFreeImage()
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

void CPhotoPictureStatic::OnPaint() 
{
	CPaintDC dc(this);
}

bool CPhotoPictureStatic::SleepEx( DWORD dwMilliseconds )
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

/*
bool SleepEx( DWORD dwMilliseconds )
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

//---------------------------------------------------------------------
//left to right stretch show
//---------------------------------------------------------------------
bool MagicFun11( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep )
{
	HDC hBuffDC = CreateCompatibleDC(hDestDC);
	HBITMAP hBitmap = CreateCompatibleBitmap( hDestDC, width , height );
	SelectObject( hBuffDC , hBitmap );
	
	BitBlt( hBuffDC , 0 , 0 , width , height , hDestDC , xd , yd , SRCCOPY );

	for( int i=0; i< width/nStep+1; i++ )
	{
		
		StretchBlt( hBuffDC , 0 , 0 , (i+1)*nStep , height , hSrcDC , x , y , width , height , SRCCOPY );
		BitBlt( hDestDC , xd , yd , (i+1)*nStep , height , hBuffDC , 0 , 0 , SRCCOPY );
		SleepEx( nDelay );
	}
	BitBlt( hDestDC , xd , yd , width , height , hSrcDC , x , y , SRCCOPY );
	DeleteObject( hBitmap );
	DeleteDC( hBuffDC );
	return TRUE;
}

//---------------------------------------------------------------------
//right to left stretch show
//---------------------------------------------------------------------
bool MagicFun12( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep )
{
	HDC hBuffDC = CreateCompatibleDC(hDestDC);
	HBITMAP hBitmap = CreateCompatibleBitmap( hDestDC, width , height );
	SelectObject( hBuffDC , hBitmap );
	
	BitBlt( hBuffDC , 0 , 0 , width , height , hDestDC , xd , yd , SRCCOPY );

	for( int i=0; i< width/nStep+1; i++ )
	{
		
		StretchBlt( hBuffDC , width - (i+1)*nStep , 0 , (i+1)*nStep , height , hSrcDC , x , y , width , height , SRCCOPY );
		BitBlt( hDestDC , xd+width- (i+1)*nStep , yd , (i+1)*nStep , height , hBuffDC , width - (i+1)*nStep , 0 , SRCCOPY );
		SleepEx( nDelay );
	}
	BitBlt( hDestDC , xd , yd , width , height , hSrcDC , x , y , SRCCOPY );
	DeleteObject( hBitmap );
	DeleteDC( hBuffDC );
	return TRUE;
}

//---------------------------------------------------------------------
//top to bottom stretch show
//---------------------------------------------------------------------
bool MagicFun13( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep )
{
	HDC hBuffDC = CreateCompatibleDC(hDestDC);
	HBITMAP hBitmap = CreateCompatibleBitmap( hDestDC, width , height );
	SelectObject( hBuffDC , hBitmap );
	
	BitBlt( hBuffDC , 0 , 0 , width , height , hDestDC , xd , yd , SRCCOPY );

	for( int i=0; i< height/nStep+1; i++ )
	{
		
		StretchBlt( hBuffDC , 0 , 0 , width , (i+1)*nStep , hSrcDC , x , y , width , height , SRCCOPY );
		
		BitBlt( hDestDC , xd , yd , width , (i+1)*nStep , hBuffDC , 0 ,0 , SRCCOPY );
		SleepEx( nDelay );
	}

	BitBlt( hDestDC , xd , yd , width , height , hSrcDC , x , y , SRCCOPY );
	DeleteObject( hBitmap );
	DeleteDC( hBuffDC );

	return TRUE;
}

//---------------------------------------------------------------------
//from bottom to top stretch show
//---------------------------------------------------------------------
bool MagicFun14( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep )
{
	HDC hBuffDC = CreateCompatibleDC(hDestDC);
	HBITMAP hBitmap = CreateCompatibleBitmap( hDestDC, width , height );
	SelectObject( hBuffDC , hBitmap );
	
	BitBlt( hBuffDC , 0 , 0 , width , height , hDestDC , xd , yd , SRCCOPY );

	for( int i=0; i< height/nStep+1; i++ )
	{
		
		StretchBlt( hBuffDC , 0 , height-(i+1)*nStep , width , (i+1)*nStep , hSrcDC , x , y , width , height , SRCCOPY );
		
		BitBlt( hDestDC , xd , yd+height-(i+1)*nStep , width , (i+1)*nStep , hBuffDC , 0 ,height-(i+1)*nStep , SRCCOPY );
		SleepEx( nDelay );
	}

	BitBlt( hDestDC , xd , yd , width , height , hSrcDC , x , y , SRCCOPY );
	DeleteObject( hBitmap );
	DeleteDC( hBuffDC );
	return TRUE;
}

//---------------------------------------------------------------------
//from top to bottom
//---------------------------------------------------------------------
bool MagicFun17( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep )
{
	for( int i=0; i< height/nStep; i++ )
	{
		BitBlt( hDestDC , xd, yd , width, (i+1)*nStep , hSrcDC , x , y+height-(i+1)*nStep , SRCCOPY );
		SleepEx( nDelay );
	}
	BitBlt( hDestDC , xd , yd , width , height , hSrcDC , x, y , SRCCOPY );
	return TRUE;
}

//---------------------------------------------------------------------
//from bottom to top
//---------------------------------------------------------------------
bool MagicFun18( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep )
{
	for( int i=0; i< height/nStep; i++ )
	{
		BitBlt( hDestDC , xd, yd+height-(i+1)*nStep , width, (i+1)*nStep , hSrcDC , x , y , SRCCOPY );
		SleepEx( nDelay );
	}
	BitBlt( hDestDC , xd , yd , width , height , hSrcDC , x, y , SRCCOPY );
	return TRUE;
}
*/
bool CPhotoPictureStatic::MagicFunstretchUp( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep )
{
	HDC hBuffDC = CreateCompatibleDC(hDestDC);
	HBITMAP hBitmap = CreateCompatibleBitmap( hDestDC, width , height );
	SelectObject( hBuffDC , hBitmap );
	
	BitBlt( hBuffDC , 0 , 0 , width , height , hDestDC , xd , yd , SRCCOPY );

	for( int i=0; i< height/nStep+1; i++ )
	{
		
		StretchBlt( hBuffDC , 0 , height-(i+1)*nStep , width , (i+1)*nStep , hSrcDC , x , y , width , height , SRCCOPY );
		
		BitBlt( hDestDC , xd , yd+height-(i+1)*nStep , width , (i+1)*nStep , hBuffDC , 0 ,height-(i+1)*nStep , SRCCOPY );
		SleepEx( nDelay );
	}

	BitBlt( hDestDC , xd , yd , width , height , hSrcDC , x , y , SRCCOPY );
	DeleteObject( hBitmap );
	DeleteDC( hBuffDC );
	return TRUE;
}

BOOL CPhotoPictureStatic::OnEraseBkgnd(CDC* pDC)
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
		MagicFunstretchUp(MemDC.m_hDC , 0 , 0 , pDC->m_hDC , 0 , 0 , rc.Width() , rc.Height() , 1, 20);

		m_bButtonClick = FALSE; 
	}
	else
		pDC->BitBlt(0, 0, bx, by, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pbmpOld);
	ReleaseDC(pDC);
	return TRUE;
}

void CPhotoPictureStatic::OnInvalidate()
{
	Invalidate();
}

void CPhotoPictureStatic::SetButtonClick(BOOL bClick)
{
	m_bButtonClick = bClick;
}

void CPhotoPictureStatic::OnTimer(UINT nIDEvent)
{	
	if ( nIDEvent == 1 )
	{
	
	}
}