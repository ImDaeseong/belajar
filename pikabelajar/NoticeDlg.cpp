// NoticeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pikabelajar.h"
#include "NoticeDlg.h"
#include "pikabelajarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NoticeDlg dialog


NoticeDlg::NoticeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(NoticeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(NoticeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	InitVariables();
}

void NoticeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NoticeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(NoticeDlg, CDialog)
	//{{AFX_MSG_MAP(NoticeDlg)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NoticeDlg message handlers

BOOL NoticeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, 0);

	const DWORD dwExStyle =  WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED;
	ModifyStyleEx(0, dwExStyle );

	LoadImage();

	DrawSkin();

	return TRUE; 
}

void NoticeDlg::OnPaint() 
{
	CPaintDC dc(this);

	DrawSkin();
}

void NoticeDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	

	SAFE_DELETE(m_pbgImage);
}

BOOL NoticeDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void NoticeDlg::LoadImage()
{
	UINT nResourceID = 0;
	if(m_nJawaban == 1)
		nResourceID =IDR_PNG_NOTICEA;	
	else if(m_nJawaban == 2)
		nResourceID =IDR_PNG_NOTICEB;
	else if(m_nJawaban == 3)
		nResourceID =IDR_PNG_NOTICEC;
	else if(m_nJawaban == 4)
		nResourceID =IDR_PNG_NOTICED;

	if (!m_pbgImage)
	{
		m_pbgImage = new CGdiPlusBitmapResource;

		if (!m_pbgImage->Load(nResourceID, "PNG", AfxGetApp()->m_hInstance))
		{
			return;
		}
	}

	int x = m_pbgImage->m_pBitmap->GetWidth();
	int y = m_pbgImage->m_pBitmap->GetHeight();

	MoveWindow(0, 0, x, y);

	const DWORD dwExStyle =  WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED;
	ModifyStyleEx(0, dwExStyle );
}

void NoticeDlg::DrawSkin()
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

	//SetInfoText(gps);

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

void NoticeDlg::InitVariables()
{
	m_pbgImage = NULL;
	m_nJawaban = 0;
}

void NoticeDlg::SetParent(CPikabelajarDlg * pParent)
{
	m_pParent = pParent;
}

void NoticeDlg::SetJawaban(int nJawaban)
{
	m_nJawaban = nJawaban;
}