#include "stdafx.h"
#include "PictureStatic.h"

CPictureStatic::CPictureStatic()
{	
	m_hMainBmp = NULL;
	m_nX = 0;
	m_nY = 0;
}

CPictureStatic::~CPictureStatic()
{
	ReleaseFreeImage();
}

BEGIN_MESSAGE_MAP(CPictureStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CPictureStatic::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();
    ModifyStyle(0, SS_OWNERDRAW);
}

BOOL CPictureStatic::LoadImage(CString strImagePath)
{
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

	return TRUE;
}

BOOL CPictureStatic::LoadImage(UINT ResourceName, CString ResourceType)
{
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

	return TRUE;
}

void CPictureStatic::StaticRoundSize(int nX, int nY)
{	
	m_nX = nX;
	m_nY = nY;
}

void CPictureStatic::GetPictureRect(CRect& rPos)
{
	rPos = m_rPicBg;
}

void CPictureStatic::ReleaseFreeImage()
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

void CPictureStatic::OnPaint() 
{
	CPaintDC dc(this);
}

BOOL CPictureStatic::OnEraseBkgnd(CDC* pDC)
{
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, m_rPicBg.right, m_rPicBg.bottom, m_nX,  m_nY);
	int iMode = pDC->SelectObject(&rgn);

	CDC MemDC;	
	MemDC.CreateCompatibleDC(pDC);

	BITMAP bit;
	int bx, by;
	GetObject(m_hMainBmp, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	CBitmap* pbmpOld = MemDC.SelectObject(&m_bmpMain);	

	pDC->BitBlt(0, 0, bx, by, &MemDC, 0, 0, SRCCOPY);

	//pDC->SetStretchBltMode(COLORONCOLOR);
	//pDC->StretchBlt(0, 0, 806, 378, &MemDC, 0, 0, bx, by, SRCCOPY);

	MemDC.SelectObject(pbmpOld);

	ReleaseDC(pDC);
    
	return TRUE;
}

