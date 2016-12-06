// ResultDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pikabelajar.h"
#include "ResultDlg.h"
#include "pikabelajarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ResultDlg dialog


ResultDlg::ResultDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ResultDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ResultDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	InitVariables();
}

void ResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ResultDlg)
	//DDX_Control(pDX, IDC_STATIC_MESSAGE, m_staticText);
	//DDX_Control(pDX, IDC_STATIC_MESSAGE2, m_staticText1);
	//DDX_Control(pDX, IDC_STATIC_MESSAGE3, m_staticText2);
	DDX_Control(pDX, IDC_BUTTON_ULANG, m_btnUlang);
	DDX_Control(pDX, IDC_BUTTON_LANGJUT, m_btnLanjuk);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ResultDlg, CDialog)
	//{{AFX_MSG_MAP(ResultDlg)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_ULANG, OnButtonUlang)
	ON_BN_CLICKED(IDC_BUTTON_LANGJUT, OnButtonLangjut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL ResultDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, 0);

	const DWORD dwExStyle =  WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED;
	ModifyStyleEx(0, dwExStyle );

	LoadImage();

	InitButtons();

	DrawSkin();

	m_nCloseCount = 10;
	SetTimer(1, 1000, NULL);

	return TRUE; 
}	

void ResultDlg::OnPaint() 
{
	CPaintDC dc(this);

	DrawSkin();
}

void ResultDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	

	SAFE_DELETE(m_pbgImage);
}

BOOL ResultDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void ResultDlg::LoadImage()
{
	if (!m_pbgImage)
	{
		m_pbgImage = new CGdiPlusBitmapResource;

		if (!m_pbgImage->Load(IDR_PNG_RESULT, "PNG", AfxGetApp()->m_hInstance))
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

void ResultDlg::DrawSkin()
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

	SetInfoText(gps);

	ReDrawButton(gps);

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

void ResultDlg::InitVariables()
{
	m_pbgImage = NULL;
	m_strResult = "";
	m_nTitleIndex = 0;
	m_nSuaraIndex = 0;
	m_nCloseCount = 0;
}

void ResultDlg::SetParent(CPikabelajarDlg * pParent)
{
	m_pParent = pParent;
}

void ResultDlg::SetResultMessage(int nTitleIndex, int nSuaraIndex, CString strResult)
{
	m_nTitleIndex = nTitleIndex;
	m_nSuaraIndex = nSuaraIndex;
	m_strResult = strResult;
}

void ResultDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (nFlags & MK_LBUTTON)
	{	
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE,  0,0);
	}
	else
	{
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE,  0,0);
	}	
					
	CDialog::OnMouseMove(nFlags, point);
}

void ResultDlg::OnTimer(UINT nIDEvent) 
{	
	if(nIDEvent == 1)
	{
		if( m_nCloseCount > 0)
			--m_nCloseCount;
	
		if(m_nCloseCount == 9)
		{		
			if( m_nSuaraIndex == 0)
			{
				::PlaySound(MAKEINTRESOURCE(IDR_WAVE_JUMPA_PUTRI), 0, SND_RESOURCE | SND_ASYNC); 	
			}
			else if( m_nSuaraIndex == 1)//ADI
			{
				::PlaySound(MAKEINTRESOURCE(IDR_WAVE_JUMPA_ADI), 0, SND_RESOURCE | SND_ASYNC); 	
			}
			else if( m_nSuaraIndex == 2)//Desita
			{
				::PlaySound(MAKEINTRESOURCE(IDR_WAVE_JUMPA_DESITA), 0, SND_RESOURCE | SND_ASYNC); 	
			}
			else if( m_nSuaraIndex == 3)//Putri
			{
				::PlaySound(MAKEINTRESOURCE(IDR_WAVE_JUMPA_PUTRI), 0, SND_RESOURCE | SND_ASYNC); 	
			} 
		}

		if(m_nCloseCount == 0)
		{
			m_pParent->CloseResultViewDlg();
			m_pParent->SetNextUgian(m_nTitleIndex, false);
		}
	}
}

void ResultDlg::OnButtonUlang() 
{
	m_pParent->SetNextUgian(m_nTitleIndex, true);
}

void ResultDlg::OnButtonLangjut() 
{
	m_pParent->SetNextUgian(m_nTitleIndex, false);	
}

void ResultDlg::InitButtons()
{
    m_btnUlang.SetImage(MAKEINTRESOURCE(IDR_PNG_ULANG), "PNG", AfxGetApp()->m_hInstance, 70, 100);
	m_btnLanjuk.SetImage(MAKEINTRESOURCE(IDR_PNG_LANJUK), "PNG", AfxGetApp()->m_hInstance, 160, 100);
}

void ResultDlg::ReDrawButton(Graphics &gps)
{
	m_btnUlang.OnDrawWindow(gps);
	m_btnLanjuk.OnDrawWindow(gps);
}

void ResultDlg::SetInfoText(Graphics &gps)
{
	USES_CONVERSION;

	//title
	if(m_nTitleIndex == 1)
	{
		gps.SetSmoothingMode(SmoothingModeAntiAlias);
		gps.SetInterpolationMode(InterpolationModeHighQualityBicubic);

		FontFamily fontFamily(L"Arial");
		StringFormat strformat;
		wchar_t pszbuf[] = L"SERVER MANAJEMEN";

		GraphicsPath path;
		path.AddString(pszbuf, wcslen(pszbuf), &fontFamily, 
		FontStyleBold, 14, Gdiplus::Point(60, 15), &strformat );
		Pen pen(Color(255, 123, 52), 5);
		pen.SetLineJoin(LineJoinRound);
		gps.DrawPath(&pen, &path);
		LinearGradientBrush brush(Gdiplus::Rect(10, 10, 30, 60), Color(255, 0, 0), Color(255, 123, 52), LinearGradientModeVertical);
		gps.FillPath(&brush, &path);
	}
	else if(m_nTitleIndex == 2)
	{
		gps.SetSmoothingMode(SmoothingModeAntiAlias);
		gps.SetInterpolationMode(InterpolationModeHighQualityBicubic);

		FontFamily fontFamily(L"Arial");
		StringFormat strformat;
		wchar_t pszbuf[] = L"HARGA";

		GraphicsPath path;
		path.AddString(pszbuf, wcslen(pszbuf), &fontFamily, 
		FontStyleBold, 14, Gdiplus::Point(104, 15), &strformat );
		Pen pen(Color(255, 123, 52), 5);
		pen.SetLineJoin(LineJoinRound);
		gps.DrawPath(&pen, &path);
		LinearGradientBrush brush(Gdiplus::Rect(10, 10, 30, 60), Color(255, 0, 0), Color(255, 123, 52), LinearGradientModeVertical);
		gps.FillPath(&brush, &path);
	}
	else if(m_nTitleIndex == 3)
	{
		gps.SetSmoothingMode(SmoothingModeAntiAlias);
		gps.SetInterpolationMode(InterpolationModeHighQualityBicubic);

		FontFamily fontFamily(L"Arial");
		StringFormat strformat;
		wchar_t pszbuf[] = L"MANAJEMEN WARNET";

		GraphicsPath path;
		path.AddString(pszbuf, wcslen(pszbuf), &fontFamily, 
		FontStyleBold, 14, Gdiplus::Point(58, 15), &strformat );
		Pen pen(Color(255, 123, 52), 5);
		pen.SetLineJoin(LineJoinRound);
		gps.DrawPath(&pen, &path);
		LinearGradientBrush brush(Gdiplus::Rect(10, 10, 30, 60), Color(255, 0, 0), Color(255, 123, 52), LinearGradientModeVertical);
		gps.FillPath(&brush, &path);
	}
	else if(m_nTitleIndex == 4)
	{
		gps.SetSmoothingMode(SmoothingModeAntiAlias);
		gps.SetInterpolationMode(InterpolationModeHighQualityBicubic);

		FontFamily fontFamily(L"Arial");
		StringFormat strformat;
		wchar_t pszbuf[] = L"CLIENT";

		GraphicsPath path;
		path.AddString(pszbuf, wcslen(pszbuf), &fontFamily, 
		FontStyleBold, 14, Gdiplus::Point(104, 15), &strformat );
		Pen pen(Color(255, 123, 52), 5);
		pen.SetLineJoin(LineJoinRound);
		gps.DrawPath(&pen, &path);
		LinearGradientBrush brush(Gdiplus::Rect(10, 10, 30, 60), Color(255, 0, 0), Color(255, 123, 52), LinearGradientModeVertical);
		gps.FillPath(&brush, &path);
	}
	else if(m_nTitleIndex == 5)
	{
		gps.SetSmoothingMode(SmoothingModeAntiAlias);
		gps.SetInterpolationMode(InterpolationModeHighQualityBicubic);

		FontFamily fontFamily(L"Arial");
		StringFormat strformat;
		wchar_t pszbuf[] = L"ATUR PC";

		GraphicsPath path;
		path.AddString(pszbuf, wcslen(pszbuf), &fontFamily, 
		FontStyleBold, 14, Gdiplus::Point(101, 15), &strformat );
		Pen pen(Color(255, 123, 52), 5);
		pen.SetLineJoin(LineJoinRound);
		gps.DrawPath(&pen, &path);
		LinearGradientBrush brush(Gdiplus::Rect(10, 10, 30, 60), Color(255, 0, 0), Color(255, 123, 52), LinearGradientModeVertical);
		gps.FillPath(&brush, &path);
	}


	//result
	Font F2(L"Arial", 11, FontStyleBold, UnitPoint);
	SolidBrush tulis(Color(255, 123, 52));
	
	StringFormat SF(StringFormatFlagsNoWrap | StringFormatFlagsLineLimit);
	SF.SetAlignment(StringAlignmentNear);
	SF.SetLineAlignment(StringAlignmentCenter);
	SF.SetTrimming(StringTrimmingEllipsisCharacter);
	
	RectF rect(69, 35, 160, 70);

	WCHAR wstring[1024]={0};
	wsprintfW ( wstring, L"%S", m_strResult );
    gps.DrawString(wstring, -1, &F2, rect, &SF, &tulis);
}