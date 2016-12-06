#include "stdafx.h"
#include "PreViewImage.h"
#include "Resource.h"
#include "pikabelajar.h"
#include "pikabelajarDlg.h"

IMPLEMENT_DYNAMIC(CPreViewImage, CStatic)
CPreViewImage::CPreViewImage()
{
	m_bCursor = FALSE;
	m_hCursor = NULL;
    m_pBmp = NULL;
	m_strResourceImg = "";
	m_bClick = FALSE;
}

CPreViewImage::~CPreViewImage()
{
	Free();
}

void CPreViewImage::Free()
{
    if (m_pBmp) 
	{
        delete m_pBmp;
        m_pBmp = NULL;
    }

	m_strResourceImg = "";
}

BEGIN_MESSAGE_MAP(CPreViewImage, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

void CPreViewImage::SetPictureStaticCursor(BOOL bCursor)
{
	m_bCursor = bCursor;
	m_hCursor = AfxGetApp()->LoadCursor(IDC_CURSORZOOM);//m_hCursor = LoadCursor(NULL, IDC_HAND);
}

BOOL CPreViewImage::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
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

void CPreViewImage::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();
	ModifyStyle(0, SS_OWNERDRAW);
}

CPreViewImage& CPreViewImage::SetPictureStaticClick(BOOL bClick)
{
	m_bClick = bClick;

	if (bClick)
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);

	return *this;
}

void CPreViewImage::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CPikabelajarDlg* pDlg = (CPikabelajarDlg*)AfxGetMainWnd();
	if(pDlg)
	{
		pDlg->CreateHintviewDlg(m_strResourceImg);
	}

	CStatic::OnLButtonDown(nFlags, point);
}

BOOL CPreViewImage::LoadImage(UINT ResourceName, CString ResourceType)
{
	Free();

	m_strResourceImg.Format("%d", ResourceName);

	//resource dll
	HINSTANCE hinstLib;
	hinstLib = ((CPikabelajarApp*)AfxGetApp())->m_hResourceDll;
    if (hinstLib == NULL)
		return FALSE;
    
    /*
	//local
	HINSTANCE hinstLib;
	hinstLib = AfxGetInstanceHandle();
	if (hinstLib == NULL)
		return FALSE;
    */

	HRSRC hrsrc=FindResource(hinstLib, MAKEINTRESOURCE(ResourceName), ResourceType);
    if(!hrsrc) return FALSE;
    HGLOBAL hg1=LoadResource(hinstLib, hrsrc);
    DWORD sz=SizeofResource(hinstLib, hrsrc);
    void* ptr1=LockResource(hg1);
    HGLOBAL hg2=GlobalAlloc(GMEM_FIXED, sz);
    CopyMemory(LPVOID(hg2), ptr1, sz);
    IStream *pStream;
    HRESULT hr=CreateStreamOnHGlobal(hg2, TRUE, &pStream);
    if(FAILED(hr)) return FALSE;
    m_pBmp=Bitmap::FromStream(pStream);

    pStream->Release();
	return TRUE;
}

BOOL CPreViewImage::IsPictureValid() const
{
	if(m_pBmp)
		return TRUE;

    return FALSE;
}

void CPreViewImage::CheckDimension(const CRect& rcClient, const CRect& rcBound, CRect& rcDim)
{
    ASSERT(!rcClient.IsRectEmpty());
    ASSERT(!rcBound.IsRectEmpty());

    rcDim = rcClient;
    if( (rcClient.Height() * rcBound.Width()) / (rcClient.Width() * rcBound.Height()) >= 1 )
	{
        int nHeight = (rcClient.Width() * rcBound.Height()) / rcBound.Width();
        rcDim.top = rcClient.top + (rcClient.Height() - nHeight) / 2;
        rcDim.bottom = rcDim.top + nHeight;
    }
	else
	{
        int nWidth = (rcClient.Height() * rcBound.Width()) / rcBound.Height();
        rcDim.left = rcClient.top + (rcClient.Width() - nWidth) / 2;
        rcDim.right = rcDim.left + nWidth;
    }
}

HBRUSH CPreViewImage::AllocMarginBrush() const
{
    return (HBRUSH)::GetStockObject(LTGRAY_BRUSH);
}

void CPreViewImage::FreeMarginBrush(HBRUSH hBrush) const
{
    UNUSED_ALWAYS(hBrush);
}

void CPreViewImage::OnDraw(CDC& DC, const CRect& rcClient, const CRect& rcBound, const CRect& rcDim)
{
    UNUSED_ALWAYS(rcBound);

    if (!rcClient.EqualRect(&rcDim))
	{
        HBRUSH hBrush = ::CreateSolidBrush(RGB(248,247,233));//AllocMarginBrush();
        if (m_pBmp)
		{
            if (rcClient.left < rcDim.left)
			{
                CRect rc(rcClient);
                rc.right = rcDim.left;
                ::FillRect(DC, &rc, hBrush);
            }
            
			if (rcClient.top < rcDim.top) 
			{
                CRect rc(rcDim.left, rcClient.top, rcDim.right, rcDim.top);
                ::FillRect(DC, &rc, hBrush);
            }
            
			if (rcDim.right < rcClient.right) 
			{
                CRect rc(rcClient);
                rc.left = rcDim.right;
                ::FillRect(DC, &rc, hBrush);
            }
            
			if (rcDim.bottom < rcClient.bottom)
			{
                CRect rc(rcDim.left, rcDim.bottom, rcDim.right, rcClient.bottom);
                ::FillRect(DC, &rc, hBrush);
            }
        } 
		else 
		{
            ::FillRect(DC, &rcClient, hBrush);
        }
        FreeMarginBrush(hBrush);
    }
  
	if (m_pBmp)
	{
	    Gdiplus::Graphics graphics(DC);
        Gdiplus::Rect rc(rcDim.left, rcDim.top, rcDim.Width(), rcDim.Height());
	    graphics.DrawImage(m_pBmp, rc);
    }
}

BOOL CPreViewImage::GetBoundRect(CRect& rcBound) const
{
    if (m_pBmp) 
	{
        rcBound.SetRect(0, 0, m_pBmp->GetWidth(), m_pBmp->GetHeight());

        return rcBound.IsRectEmpty() ? FALSE: TRUE;
    } 
	else 
	{
        rcBound.SetRectEmpty();
        return FALSE;
    }
}

void CPreViewImage::OnPaint() 
{
    if (IsPictureValid())
	{
	    CPaintDC dc(this); 

        CRect rcClient, rcBound;
        GetClientRect(&rcClient);

        if (!rcClient.IsRectEmpty() && GetBoundRect(rcBound))
		{
            CRect rcDim;
            CheckDimension(rcClient, rcBound, rcDim);
            OnDraw(dc, rcClient, rcBound, rcDim);
        }
    }
	else
	{
    	CStatic::OnPaint();
    }
}

BOOL CPreViewImage::OnEraseBkgnd(CDC* pDC) 
{
	UNUSED_ALWAYS(pDC);

	return IsPictureValid(); // CStatic::OnEraseBkgnd(pDC);
}
