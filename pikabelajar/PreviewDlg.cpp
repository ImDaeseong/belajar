// PreviewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pikabelajar.h"
#include "PreviewDlg.h"
#include "pikabelajarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PreviewDlg dialog

static bool IsMouseOverOurWindow( HWND hwnd )
{
	POINT ptMouse;
	::GetCursorPos( &ptMouse );

	RECT rcWindow;
	if( ::GetWindowRect( hwnd, &rcWindow ) && ::PtInRect( &rcWindow, ptMouse ) )
	{
		return true;
	}
	return false;
}

PreviewDlg::PreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PreviewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(PreviewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pbgImage = NULL;
	m_strResource = "";
	m_nCloseCount = 0;
	m_nX = 0;
	m_nY = 0;

	m_bMouseOn = FALSE;
}

void PreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PreviewDlg)
	DDX_Control(pDX, IDC_STATIC_PREVIEW, m_staticimg);
	DDX_Control(pDX, IDC_IMAGE, m_CloseImage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PreviewDlg, CDialog)
	//{{AFX_MSG_MAP(PreviewDlg)
	ON_WM_PAINT()	
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL PreviewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, 0);

	LoadImage();

	m_CloseImage.SendMessagePopup(2);
	m_CloseImage.SetPictureStaticClick(TRUE);
	m_CloseImage.SetPictureStaticCursor(TRUE);
	m_CloseImage.MoveWindow(798, 6, 18, 18);


	m_staticimg.LoadImage(atoi(m_strResource), "GIF");
	m_staticimg.MoveWindow(0, 0, 826, 430 );

	
	m_nCloseCount = 10;
	SetTimer(1, 500, NULL);
	SetTimer(2,1000,NULL);

	return TRUE; 
}

void PreviewDlg::OnPaint() 
{
	CPaintDC dc(this);

	DrawSkin(&dc);	
}

void PreviewDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(1);		
	KillTimer(2);

	SAFE_DELETE(m_pbgImage);
}

BOOL PreviewDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
		
	return CDialog::PreTranslateMessage(pMsg);
}

void PreviewDlg::LoadImage()
{
	if (!m_pbgImage)
	{
		m_pbgImage = new CGdiPlusBitmapResource;

		if (!m_pbgImage->Load(MAKEINTRESOURCE(IDR_PNG_INBACK), "PNG", AfxGetApp()->m_hInstance))
		{
			return;
		}
	}
	//SetTransparentDlgHIDE(GetSafeHwnd());
}

void PreviewDlg::DrawSkin(CDC *pDC)
{
	int x = m_pbgImage->m_pBitmap->GetWidth();
	int y = m_pbgImage->m_pBitmap->GetHeight();

	Graphics gps(pDC->GetSafeHdc());
	gps.DrawImage(m_pbgImage->m_pBitmap, Rect(0, 0, x, y) , 0, 0, x, y, UnitPixel);
}

void PreviewDlg::SetParent(CPikabelajarDlg * pParent)
{
	m_pParent = pParent;
}

void PreviewDlg::SetImgName(CString strResource)
{
	m_strResource = strResource;
}

void PreviewDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION,MAKELPARAM(point.x, point.y)) ;
	
	CDialog::OnLButtonDown(nFlags, point);
}

void PreviewDlg::OnTimer(UINT nIDEvent) 
{	
	if( nIDEvent == 1)
	{
		if (m_bMouseOn)
		{
			CheckCurPos();
		}
	}	
	else if(nIDEvent == 2)
	{
		if( m_nCloseCount > 0)
			--m_nCloseCount;
	
		if(m_nCloseCount == 0)
		{
			m_pParent->ClosePreviewDlg();
		}
	}
}

void PreviewDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect Rect;
	GetClientRect(&Rect);

	if (!m_bMouseOn && Rect.PtInRect(point))
	{
		m_bMouseOn = TRUE;	
		SetTransparentDlgSHOW(GetSafeHwnd());
	}
	
	CDialog::OnMouseMove(nFlags, point);
}

HWND PreviewDlg::GetCurPosHandle(POINT point)
{
	return ::WindowFromPoint(point);
}

void PreviewDlg::CheckCurPos()
{
	POINT point;
	::GetCursorPos(&point);

	HWND hCur = GetCurPosHandle(point);

	if (hCur == GetSafeHwnd())
	{
		if(m_bMouseOn == FALSE)
		{
			m_bMouseOn = TRUE;	
			SetTransparentDlgSHOW(GetSafeHwnd());
		}
	}
	else
	{
		HWND hOwner;
	
		do
		{
			hOwner = ::GetParent(hCur);

			if (hOwner == NULL)
			{
				m_bMouseOn = FALSE;
				SetTransparentDlgHIDE(GetSafeHwnd());
				return;
			}			

			if (hOwner == GetSafeHwnd())
			{
				if(m_bMouseOn == FALSE)
				{
					m_bMouseOn = TRUE;	
					SetTransparentDlgSHOW(GetSafeHwnd());
				}
				return;
			}

			hCur = hOwner;

		}while (hCur);
	}
}