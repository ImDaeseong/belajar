// HintviewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pikabelajar.h"
#include "HintviewDlg.h"
#include "pikabelajarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HintviewDlg dialog

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

HintviewDlg::HintviewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(HintviewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(HintviewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pbgImage = NULL;
	m_strResource = "";
	m_nCloseCount = 0;

	m_bMouseOn = FALSE;
}

void HintviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HintviewDlg)
	DDX_Control(pDX, IDC_STATIC_PREVIEW, m_HintImg);
	DDX_Control(pDX, IDC_IMAGE, m_CloseImage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(HintviewDlg, CDialog)
	//{{AFX_MSG_MAP(HintviewDlg)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()	
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HintviewDlg message handlers

BOOL HintviewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, 0);

	LoadImage();


	m_HintImg.LoadImage(atoi(m_strResource), "HINT");
	m_HintImg.SetPictureStaticClick(FALSE);	
	m_HintImg.SetPictureStaticCursor(FALSE);
	m_HintImg.MoveWindow(0, 0, 826, 430);


	m_CloseImage.SendMessagePopup(1);
	m_CloseImage.SetPictureStaticClick(TRUE);
	m_CloseImage.SetPictureStaticCursor(TRUE);
	m_CloseImage.MoveWindow(798, 6, 18, 18);


	m_nCloseCount = 10;
	SetTimer(1, 1000, NULL);
	SetTimer(2, 500,NULL);

	return TRUE; 
}

void HintviewDlg::OnPaint() 
{
	CPaintDC dc(this);

	DrawSkin(&dc);
}

void HintviewDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(1);		
	KillTimer(2);

	SAFE_DELETE(m_pbgImage);
}

BOOL HintviewDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
		
	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH HintviewDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);	
    return hbr;
}

void HintviewDlg::LoadImage()
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

void HintviewDlg::DrawSkin(CDC *pDC)
{
	int x = m_pbgImage->m_pBitmap->GetWidth();
	int y = m_pbgImage->m_pBitmap->GetHeight();

	Graphics gps(pDC->GetSafeHdc());
	gps.DrawImage(m_pbgImage->m_pBitmap, Rect(0, 0, x, y) , 0, 0, x, y, UnitPixel);	
}

void HintviewDlg::SetParent(CPikabelajarDlg * pParent)
{
	m_pParent = pParent;
}

void HintviewDlg::SetImgName(CString strResource)
{
	m_strResource = strResource;
}

void HintviewDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION,MAKELPARAM(point.x, point.y)) ;
	
	CDialog::OnLButtonDown(nFlags, point);
}

void HintviewDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
}

void HintviewDlg::OnTimer(UINT nIDEvent) 
{	
	if(nIDEvent == 1)
	{
		if( m_nCloseCount > 0)
			--m_nCloseCount;
	
		if(m_nCloseCount == 0)
		{
			m_pParent->CloseHintviewDlg();
		}
	}
	else if( nIDEvent == 2)
	{		
		if (m_bMouseOn)
		{
			CheckCurPos();
		}
	}
}

void HintviewDlg::OnMouseMove(UINT nFlags, CPoint point) 
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

HWND HintviewDlg::GetCurPosHandle(POINT point)
{
	return ::WindowFromPoint(point);
}

void HintviewDlg::CheckCurPos()
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
