// MusicPlayLayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pikabelajar.h"
#include "MusicPlayLayerDlg.h"
#include "MusicPlay.h"
#include "pikabelajarDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMusicPlayLayerDlg dialog


CMusicPlayLayerDlg::CMusicPlayLayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMusicPlayLayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMusicPlayLayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	InitVariables();
}

void CMusicPlayLayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMusicPlayLayerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMusicPlayLayerDlg, CDialog)
	//{{AFX_MSG_MAP(CMusicPlayLayerDlg)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_MOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DISPLAYCHANGE, OnDisplayChange)
END_MESSAGE_MAP()

void CMusicPlayLayerDlg::OnTimer(UINT nIDEvent) 
{	
	if(nIDEvent == 1)
	{
		if(m_pMusic)
			m_pMusic->ShowWindow(SW_SHOW);	
		
		KillTimer(1);
	}
}

BOOL CMusicPlayLayerDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CMusicPlayLayerDlg::OnDisplayChange(WPARAM wParam, LPARAM lParam)
{
	SetChildPos();
	return 0;
}

void CMusicPlayLayerDlg::InitVariables()
{
	m_pbgImage = NULL;

	m_pMusic = NULL;
}

void CMusicPlayLayerDlg::CreateSubDlg()
{
	if (!m_pMusic)
	{
		m_pMusic = new CMusicPlay();

		m_pMusic->SetParent(this, m_pParent);

		m_pMusic->Create(IDD_DIALOG_PLAY, this);

		SetChildPos();

		//m_pMusic->ShowWindow(SW_SHOW);	
	}
}

void CMusicPlayLayerDlg::CloseSubDlg()
{
	if (m_pMusic)
	{
		m_pMusic->DestroyWindow();

		SAFE_DELETE(m_pMusic);
	}
}

void CMusicPlayLayerDlg::SetChildPos()
{
	if (m_pMusic)
	{
		CRect rInfoWnd;
		GetWindowRect(rInfoWnd);

		int nX = rInfoWnd.left + 12;
		int nY = rInfoWnd.top + 39;

		m_pMusic->MoveWindow(nX, nY, 160, 390);
	}
}

void CMusicPlayLayerDlg::SetParent(CPikabelajarDlg * pParent)
{
	m_pParent = pParent;
}

BOOL CMusicPlayLayerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadImage();

	CreateSubDlg();

	DrawSkin();

	SetTimer(1, 1000, NULL);

	return TRUE;  
}

void CMusicPlayLayerDlg::OnPaint() 
{
	CPaintDC dc(this);

	DrawSkin();
}

void CMusicPlayLayerDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
		
	SetChildPos();
}

void CMusicPlayLayerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(1);

	CloseSubDlg();

	SAFE_DELETE(m_pbgImage);
}

void CMusicPlayLayerDlg::LoadImage()
{
	if (!m_pbgImage)
	{
		m_pbgImage = new CGdiPlusBitmapResource;

		if (!m_pbgImage->Load(IDR_PNG_SKINLAYER, "PNG", AfxGetApp()->m_hInstance))
		{
			return;
		}
	}

	int x = m_pbgImage->m_pBitmap->GetWidth();
	int y = m_pbgImage->m_pBitmap->GetHeight();


	const DWORD dwExStyle =  WS_EX_TOOLWINDOW | WS_EX_LAYERED;
	ModifyStyleEx(0, dwExStyle );

	MoveWindow(0, 0, x, y);
}

void CMusicPlayLayerDlg::DrawSkin()
{
	int x = m_pbgImage->m_pBitmap->GetWidth();
	int y = m_pbgImage->m_pBitmap->GetHeight();

	CDC * pDC = GetDC();
	CDC memDC;
	CBitmap bmp;
	CBitmap *bmp_old;
	
	memDC.CreateCompatibleDC(pDC);

	BITMAPINFO bmInfo;
	memset(&bmInfo, 0x00, sizeof(BITMAPINFO));
	bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmInfo.bmiHeader.biWidth = x;
	bmInfo.bmiHeader.biHeight = y;
	bmInfo.bmiHeader.biPlanes = 1;
	bmInfo.bmiHeader.biBitCount = 32;
	bmInfo.bmiHeader.biCompression = BI_RGB;
	bmInfo.bmiHeader.biSizeImage = 0;
	bmInfo.bmiHeader.biClrUsed = 0;
	bmInfo.bmiHeader.biClrImportant = 0;
	
	LPBYTE pbmpBits = NULL;
	HBITMAP hBitmap = ::CreateDIBSection(pDC->GetSafeHdc(), (LPBITMAPINFO)&bmInfo, DIB_RGB_COLORS, (void **)&pbmpBits, NULL, 0);
	if(hBitmap == NULL)
		bmp.CreateCompatibleBitmap(pDC, x, y);
	else
		bmp.Attach(hBitmap);

	bmp_old = memDC.SelectObject(&bmp);

	Graphics gps(memDC.GetSafeHdc());
	gps.DrawImage(m_pbgImage->m_pBitmap, Rect(0, 0, x, y) , 0, 0, x, y, UnitPixel);

	//ReDrawButton(gps);
	//SetText(gps);

	CRect rc;
	GetWindowRect(rc);
	CPoint ptWindowScreenPosition(rc.TopLeft());
	CSize szWindow(x,y);

	BLENDFUNCTION blendPixelFunction= { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	CPoint ptSrc(0,0); 

	HDC hdc = gps.GetHDC();

	BOOL bRet= ::UpdateLayeredWindow(GetSafeHwnd(), 
		pDC->GetSafeHdc(),
		&ptWindowScreenPosition,
		&szWindow,
		hdc,
		&ptSrc,
		0, 
		&blendPixelFunction,
		ULW_ALPHA);

	gps.ReleaseHDC(hdc);
	memDC.DeleteDC();
	bmp.DeleteObject();

	ReleaseDC(pDC);
}

void CMusicPlayLayerDlg::CloseMusicAll()
{
	m_pParent->CloseMusicDlg(); 
}