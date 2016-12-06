#include "stdafx.h"
#include "ZipBitmap.h"

COLORREF rgbWhite = RGB(255,255,255);

CZipBitmap::CZipBitmap()
{
    m_iWidth = 0;
    m_iHeight = 0;
    m_hbmMask = NULL;
}

CZipBitmap::~CZipBitmap()
{
}

void CZipBitmap::GetMetrics()
{
    BITMAP bm;
    GetObject(sizeof(bm), &bm);
    m_iWidth = bm.bmWidth;
    m_iHeight = bm.bmHeight;
}

int CZipBitmap::GetWidth()
{
    if ((m_iWidth == 0) || (m_iHeight == 0))
	{
        GetMetrics();
    }
    return m_iWidth;
}

int CZipBitmap::GetHeight()
{
    if ((m_iWidth == 0) || (m_iHeight == 0))
	{
        GetMetrics();
    }
    return m_iHeight;
}

void CZipBitmap::Draw(HDC hDC, int x, int y)
{
    ASSERT(hDC);
    
    HDC hdcMem = ::CreateCompatibleDC(hDC);
    
    HBITMAP hbmold = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)(m_hObject));
    
    ::BitBlt(hDC, x, y, GetWidth(), GetHeight(), hdcMem, 0, 0, SRCCOPY);
    ::SelectObject(hdcMem, hbmold);
    ::DeleteDC(hdcMem); 
}

void CZipBitmap::Draw(HDC hDC, int x, int y,int height,int width)
{
    ASSERT(hDC);
    
    HDC hdcMem = ::CreateCompatibleDC(hDC);
    
    HBITMAP hbmold = (HBITMAP)::SelectObject(hdcMem, (HBITMAP)(m_hObject));
    
	::StretchBlt(hDC, x, y, width, height, hdcMem, 0, 0,GetWidth(),GetHeight(), SRCCOPY);

    ::SelectObject(hdcMem, hbmold);
    ::DeleteDC(hdcMem); 
}

void CZipBitmap::CreateMask(HDC hDC)
{
    if (m_hbmMask)
	{
        ::DeleteObject(m_hbmMask);
    }

    
    HDC hdcMask = ::CreateCompatibleDC(hDC);
    HDC hdcImage = ::CreateCompatibleDC(hDC);
    
    m_hbmMask = ::CreateBitmap(GetWidth(), GetHeight(), 1, 1, NULL);
    
    HBITMAP hbmOldMask = (HBITMAP)::SelectObject(hdcMask, m_hbmMask);
    
    HBITMAP hbmOldImage = (HBITMAP)::SelectObject(hdcImage, m_hObject);
    
    ::SetBkColor(hdcImage, ::GetPixel(hdcImage, 0, 0));
    
    ::BitBlt(hdcMask, 0, 0, GetWidth(), GetHeight(), hdcImage, 0, 0, SRCCOPY);
    
    ::SelectObject(hdcMask, hbmOldMask);
    ::SelectObject(hdcImage, hbmOldImage);
    ::DeleteDC(hdcMask);
    ::DeleteDC(hdcImage);
}
void CZipBitmap::DrawTrans(HDC hDC, int x, int y)
{
    ASSERT(hDC);
    if (!m_hbmMask) CreateMask(hDC);
    ASSERT(m_hbmMask);
    int dx = GetWidth();
    int dy = GetHeight();

    
    HDC hdcOffScr = ::CreateCompatibleDC(hDC);
    
    HBITMAP hbmOffScr = ::CreateBitmap(dx, dy, (BYTE)GetDeviceCaps(hDC, PLANES), (BYTE)GetDeviceCaps(hDC, BITSPIXEL), NULL);
    
    HBITMAP hbmOldOffScr = (HBITMAP)::SelectObject(hdcOffScr, hbmOffScr);

    
    ::BitBlt(hdcOffScr, 0, 0, dx, dy, hDC, x, y, SRCCOPY);

    
    HDC hdcImage = ::CreateCompatibleDC(hDC); 
    HBITMAP hbmOldImage = (HBITMAP)::SelectObject(hdcImage, m_hObject);

    
    HDC hdcMask = ::CreateCompatibleDC(hDC);
    HBITMAP hbmOldMask = (HBITMAP)::SelectObject(hdcMask, m_hbmMask);

	DWORD DSx = SRCINVERT,DSa = SRCAND;

   
    ::SetBkColor(hdcOffScr,rgbWhite);
    ::BitBlt(hdcOffScr, 0, 0, dx, dy ,hdcImage, 0, 0, DSx);
    
    ::BitBlt(hdcOffScr, 0, 0, dx, dy, hdcMask, 0,0, DSa);
   
    ::BitBlt(hdcOffScr, 0, 0, dx, dy, hdcImage, 0, 0, DSx);

    
    ::BitBlt(hDC, x, y, dx, dy, hdcOffScr, 0, 0, SRCCOPY);
    
    ::SelectObject(hdcOffScr, hbmOldOffScr);
    ::SelectObject(hdcImage, hbmOldImage);
    ::SelectObject(hdcMask, hbmOldMask);
    ::DeleteObject(hbmOffScr);
    ::DeleteDC(hdcOffScr);
    ::DeleteDC(hdcImage);
    ::DeleteDC(hdcMask);
}

void CZipBitmap::DrawTrans(HDC hDC, int x, int y, COLORREF colTrans)
{
    ASSERT(hDC);
    if (!m_hbmMask) CreateMask(hDC,colTrans);
    ASSERT(m_hbmMask);
    int dx = GetWidth();
    int dy = GetHeight();

    
    HDC hdcOffScr = ::CreateCompatibleDC(hDC);
    
    HBITMAP hbmOffScr = ::CreateBitmap(dx, dy, (BYTE)GetDeviceCaps(hDC, PLANES), (BYTE)GetDeviceCaps(hDC, BITSPIXEL), NULL);
    
    HBITMAP hbmOldOffScr = (HBITMAP)::SelectObject(hdcOffScr, hbmOffScr);
   
    ::BitBlt(hdcOffScr, 0, 0, dx, dy, hDC, x, y, SRCCOPY);
   
    HDC hdcImage = ::CreateCompatibleDC(hDC); 
    HBITMAP hbmOldImage = (HBITMAP)::SelectObject(hdcImage, m_hObject);

    
    HDC hdcMask = ::CreateCompatibleDC(hDC);
    HBITMAP hbmOldMask = (HBITMAP)::SelectObject(hdcMask, m_hbmMask);

	DWORD DSx = SRCINVERT,DSa = SRCAND;

   
    ::SetBkColor(hdcOffScr,rgbWhite);
    ::BitBlt(hdcOffScr, 0, 0, dx, dy ,hdcImage, 0, 0, DSx);
    
    ::BitBlt(hdcOffScr, 0, 0, dx, dy, hdcMask, 0,0, DSa);
   
    ::BitBlt(hdcOffScr, 0, 0, dx, dy, hdcImage, 0, 0, DSx);

    
    ::BitBlt(hDC, x, y, dx, dy, hdcOffScr, 0, 0, SRCCOPY);
    
    ::SelectObject(hdcOffScr, hbmOldOffScr);
    ::SelectObject(hdcImage, hbmOldImage);
    ::SelectObject(hdcMask, hbmOldMask);
    ::DeleteObject(hbmOffScr);
    ::DeleteDC(hdcOffScr);
    ::DeleteDC(hdcImage);
    ::DeleteDC(hdcMask);
}
void CZipBitmap::CreateMask(HDC hDC, COLORREF colTrans)
{
    if (m_hbmMask) 
	{
        ::DeleteObject(m_hbmMask);
    }
    
    HDC hdcMask = ::CreateCompatibleDC(hDC);
    HDC hdcImage = ::CreateCompatibleDC(hDC);
   
    m_hbmMask = ::CreateBitmap(GetWidth(), GetHeight(), 1, 1, NULL);
   
    HBITMAP hbmOldMask = (HBITMAP)::SelectObject(hdcMask, m_hbmMask);
    
    HBITMAP hbmOldImage = (HBITMAP)::SelectObject(hdcImage, m_hObject);
    
    ::SetBkColor(hdcImage,colTrans);
    
    ::BitBlt(hdcMask, 0, 0, GetWidth(), GetHeight(), hdcImage, 0, 0, SRCCOPY);
    
    ::SelectObject(hdcMask, hbmOldMask);
    ::SelectObject(hdcImage, hbmOldImage);
    ::DeleteDC(hdcMask);
    ::DeleteDC(hdcImage);
}
