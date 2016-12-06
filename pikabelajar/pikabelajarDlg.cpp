// pikabelajarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pikabelajar.h"
#include "pikabelajarDlg.h"
#include "PikabelajrInDlg.h"
#include "PreviewDlg.h"
#include "HintviewDlg.h"
#include "NoticeDlg.h"
#include "ResultDlg.h"
#include "MusicPlayLayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPikabelajarDlg dialog

CPikabelajarDlg::CPikabelajarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPikabelajarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPikabelajarDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	InitVariables();
}

void CPikabelajarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPikabelajarDlg)
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_BUTTON_LEFT, m_btnLeft);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, m_btnRight);
	DDX_Control(pDX, IDC_BUTTON_SETTING1, m_btnSetting1);
	DDX_Control(pDX, IDC_BUTTON_SETTING2, m_btnSetting2);
	DDX_Control(pDX, IDC_BUTTON_SETTING3, m_btnSetting3);
	DDX_Control(pDX, IDC_BUTTON_SETTING4, m_btnSetting4);
	DDX_Control(pDX, IDC_BUTTON_SETTING5, m_btnSetting5);
	DDX_Control(pDX, IDC_BUTTON_YM1, m_btnYm1);
	DDX_Control(pDX, IDC_BUTTON_YM2, m_btnYm2);
	DDX_Control(pDX, IDC_BUTTON_YOUTUBE, m_btnYoutube);
	DDX_Control(pDX, IDC_BUTTON_FACEBOOK, m_btnFaceBook);
	DDX_Control(pDX, IDC_BUTTON_MUSIC, m_btnMusic);
	DDX_Control(pDX, IDC_BUTTON_SUARALAKI, m_btnSuaralaki);
	DDX_Control(pDX, IDC_BUTTON_SUARAPUTRI,	m_btnSuaraputri);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPikabelajarDlg, CDialog)
	//{{AFX_MSG_MAP(CPikabelajarDlg)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_WM_MOVE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnButtonRigth)
	ON_BN_CLICKED(IDC_BUTTON_SETTING1, OnButtonSetting1)
	ON_BN_CLICKED(IDC_BUTTON_SETTING2, OnButtonSetting2)
	ON_BN_CLICKED(IDC_BUTTON_SETTING3, OnButtonSetting3)
	ON_BN_CLICKED(IDC_BUTTON_SETTING4, OnButtonSetting4)
	ON_BN_CLICKED(IDC_BUTTON_SETTING5, OnButtonSetting5)
	ON_BN_CLICKED(IDC_BUTTON_YOUTUBE, OnButtonYoutube)
	ON_BN_CLICKED(IDC_BUTTON_FACEBOOK, OnButtonFacebook)
	ON_BN_CLICKED(IDC_BUTTON_YM1, OnButtonYm1)
	ON_BN_CLICKED(IDC_BUTTON_YM2, OnButtonYm2)
	ON_BN_CLICKED(IDC_BUTTON_MUSIC, OnButtonMusic)
	ON_BN_CLICKED(IDC_BUTTON_SUARALAKI, OnButtonSuaralaki)
	ON_BN_CLICKED(IDC_BUTTON_SUARAPUTRI, OnButtonSuaraputri)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DISPLAYCHANGE, OnDisplayChange)
	ON_MESSAGE(WM_PREVIEWIMG_CLOSE, OnPreviewImgClose)
	ON_MESSAGE(WM_HAPUSMESSAGE_SEND, OnHapusMessageSend)
END_MESSAGE_MAP()

LRESULT CPikabelajarDlg::OnPreviewImgClose(WPARAM wParam, LPARAM lParam)
{
	int nStatus = (int)wParam;

	if(nStatus == 1)
		CloseHintviewDlg();
	else if(nStatus == 2)
		ClosePreviewDlg();

	return 0;
}

LRESULT CPikabelajarDlg::OnHapusMessageSend(WPARAM wParam, LPARAM lParam)
{
	m_nHapusMessage = (int)wParam;
	Invalidate();
	return 0;
}

BOOL CPikabelajarDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	/*
	CSplashScreenEx *pSplash=new CSplashScreenEx();
	pSplash->Create(this,NULL,2000,CSS_FADE | CSS_CENTERSCREEN | CSS_SHADOW);
	pSplash->SetBitmap(IDB_SPLASH,255,0,255);
	pSplash->Show();
	*/

	/*
	CSplashScreenEx *pSplash=new CSplashScreenEx();
	pSplash->Create(this,"Pika tutorial",0,CSS_FADE | CSS_CENTERSCREEN | CSS_SHADOW);
	pSplash->SetBitmap(IDB_SPLASH,255,0,255);
	pSplash->SetTextFont("Arial",100,CSS_TEXT_NORMAL);
	pSplash->SetTextRect(CRect(125,60,291,104));
	pSplash->SetTextColor(RGB(255,255,255));
	pSplash->SetTextFormat(DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pSplash->Show();

	Sleep(100);
	pSplash->SetText("PIKA Support (021) 5292 1927");

	Sleep(100);
	pSplash->SetText("PIKA Billing Gratis seumur hidup");

	Sleep(100);
	pSplash->SetText("Update Game mudah dengan PIKASoftware");
	
	Sleep(100);
	pSplash->SetText("PIKA Support (021) 5292 1927");
	Sleep(150);

	pSplash->Hide();
	*/


	LoadImage();

	InitButtons();

	CenterWindow(GetDesktopWindow());
	
	CreatePanelDlg();

	DrawSkin();

	//selamat datang
	srand(time(NULL)); 
    int nSuara = rand() % 3 + 1;
	if(nSuara == 1)
	{
		::PlaySound(MAKEINTRESOURCE(IDR_WAVE_DATANG_ADI), 0, SND_RESOURCE | SND_ASYNC);	
	}
	else if(nSuara == 2)
	{
		::PlaySound(MAKEINTRESOURCE(IDR_WAVE_DATANG_DESITA), 0, SND_RESOURCE | SND_ASYNC);	
	}
	else if(nSuara == 3)
	{
		::PlaySound(MAKEINTRESOURCE(IDR_WAVE_DATANG_PUTRI), 0, SND_RESOURCE | SND_ASYNC);	
	}

	return TRUE; 
}

void CPikabelajarDlg::OnPaint() 
{
	CPaintDC dc(this);

	DrawSkin();
}

void CPikabelajarDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_bDrag)
	{
		if(nFlags & MK_LBUTTON)
		{
			PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
			SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE,  0,0);
		}
		else
		{
			SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, m_bDragShowFlag,  0,0);
			m_bDrag = FALSE;
		}
	}
				
	CDialog::OnMouseMove(nFlags, point);
}

void CPikabelajarDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	ClosePanelDlg();
	ClosePreviewDlg();
	CloseHintviewDlg();
	CloseNoticeDlg();
	CloseResultViewDlg();
	CloseMusicDlg();

	SAFE_DELETE(m_pbgImage);
}

BOOL CPikabelajarDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CPikabelajarDlg::LoadImage()
{
	if (!m_pbgImage)
	{
		m_pbgImage = new CGdiPlusBitmapResource;

		if (!m_pbgImage->Load(IDR_PNG_OUTBACK, "PNG", AfxGetApp()->m_hInstance))
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

void CPikabelajarDlg::DrawSkin()
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

void CPikabelajarDlg::InitVariables()
{
	m_pbgImage = NULL;
	m_pPanel = NULL;
	m_pPreview = NULL;
	m_pHintview = NULL;
	m_pNotice = NULL;
	m_pResultView = NULL;
	m_pMusicLayer = NULL;
	m_bDrag = FALSE;
	m_bDragShowFlag = FALSE;

	m_bMusicBuka = FALSE;

	m_nSuaraIndex = 3;

	m_nHapusMessage = 0;
}

void CPikabelajarDlg::CreatePanelDlg()
{
	if (!m_pPanel)
	{
		m_pPanel = new CPikabelajrInDlg();
		m_pPanel->SetParent(this);
		m_pPanel->Create(IDD_PIKABELAJARIN_DIALOG, this);
		SetChildPos();
		m_pPanel->ShowWindow(SW_SHOW);	
	}		
}

void CPikabelajarDlg::ClosePanelDlg()
{
	if (m_pPanel)
	{
		m_pPanel->DestroyWindow();
		SAFE_DELETE(m_pPanel);
	}
}

void CPikabelajarDlg::CreatePreviewDlg(CString strResource)
{
	ClosePreviewDlg();

	if (!m_pPreview)
	{
		m_pPreview = new PreviewDlg();
		m_pPreview->SetParent(this);
		m_pPreview->SetImgName(strResource);
		m_pPreview->Create(IDD_DIALOG_PREVIEW, this);
		SetChildPos();
		m_pPreview->ShowWindow(SW_SHOW);	

		AfxGetMainWnd()->PostMessage(WM_HAPUSMESSAGE_SEND, 1, 1); 
	}		
}

void CPikabelajarDlg::ClosePreviewDlg()
{
	if (m_pPreview)
	{
		m_pPreview->DestroyWindow();
		SAFE_DELETE(m_pPreview);

		AfxGetMainWnd()->PostMessage(WM_HAPUSMESSAGE_SEND, 0, 0); 
	}
}

void CPikabelajarDlg::CreateHintviewDlg(CString strResource)
{
	CloseHintviewDlg();

	if (!m_pHintview)
	{
		m_pHintview = new HintviewDlg();
		m_pHintview->SetParent(this);
		m_pHintview->SetImgName(strResource);
		m_pHintview->Create(IDD_DIALOG_HINTVIEW, this);
		SetChildPos();
		m_pHintview->ShowWindow(SW_SHOW);	

		AfxGetMainWnd()->PostMessage(WM_HAPUSMESSAGE_SEND, 1, 1); 
	}
}

void CPikabelajarDlg::CloseHintviewDlg()
{
	if (m_pHintview)
	{
		m_pHintview->DestroyWindow();
		SAFE_DELETE(m_pHintview);

		AfxGetMainWnd()->PostMessage(WM_HAPUSMESSAGE_SEND, 0, 0);
	}
}

void CPikabelajarDlg::CreateNoticeDlg(int nJawaban)
{
	CloseNoticeDlg();

	if (!m_pNotice)
	{
		m_pNotice = new NoticeDlg();
		m_pNotice->SetParent(this);
		m_pNotice->SetJawaban(nJawaban);
		m_pNotice->Create(IDD_DIALOG_NOTICE, this);
		SetChildPos();	
		m_pNotice->ShowWindow(SW_SHOW);	
	}
}

void CPikabelajarDlg::CloseNoticeDlg()
{
	if (m_pNotice)
	{
		m_pNotice->DestroyWindow();
		SAFE_DELETE(m_pNotice);
	}
}

void CPikabelajarDlg::CreateResultViewDlg(int nTitleIndex, int nSuaraIndex, CString strResult)
{
	CloseResultViewDlg();

	if (!m_pResultView)
	{
		m_pResultView = new ResultDlg();
		m_pResultView->SetParent(this);
		m_pResultView->SetResultMessage(nTitleIndex, nSuaraIndex, strResult);
		m_pResultView->Create(IDD_DIALOG_RESULT, this);
		SetChildPos();	
		m_pResultView->ShowWindow(SW_SHOW);	
	}
}

void CPikabelajarDlg::CloseResultViewDlg()
{
	if (m_pResultView)
	{
		m_pResultView->DestroyWindow();
		SAFE_DELETE(m_pResultView);
	}	
}

void CPikabelajarDlg::CreateMusicDlg()
{
	if (!m_pMusicLayer)
	{
		m_pMusicLayer = new CMusicPlayLayerDlg();
		m_pMusicLayer->SetParent(this);
		m_pMusicLayer->Create(IDD_DIALOG_PLAYLAYER, this);
		SetChildPos();	
		::AnimateWindow(m_pMusicLayer->GetSafeHwnd(), 400, AW_SLIDE | AW_HOR_POSITIVE);//m_pMusicLayer->ShowWindow(SW_SHOW);
	}
}

void CPikabelajarDlg::CloseMusicDlg() 
{
	if (m_pMusicLayer)
	{
		::AnimateWindow(m_pMusicLayer->GetSafeHwnd(), 400, AW_HIDE | AW_SLIDE | AW_HOR_NEGATIVE);
		m_pMusicLayer->DestroyWindow();
		SAFE_DELETE(m_pMusicLayer);
	}
}

void CPikabelajarDlg::InitButtons()
{
	m_btnClose.SetImage(MAKEINTRESOURCE(IDR_PNG_CLOSE_DLG), "PNG", AfxGetApp()->m_hInstance, 809, 523);	//805, 531);	
    m_btnLeft.SetImage(MAKEINTRESOURCE(IDR_PNG_LEFT), "PNG", AfxGetApp()->m_hInstance, 352, 479);
	m_btnRight.SetImage(MAKEINTRESOURCE(IDR_PNG_RIGHT), "PNG", AfxGetApp()->m_hInstance, 452, 479);
		
	m_btnYoutube.SetImage(MAKEINTRESOURCE(IDR_PNG_YOUTUBE), "PNG", AfxGetApp()->m_hInstance, 506, 521);
	m_btnFaceBook.SetImage(MAKEINTRESOURCE(IDR_PNG_FACEBOOK), "PNG", AfxGetApp()->m_hInstance, 548, 521);
	m_btnYm1.SetImage(MAKEINTRESOURCE(IDR_PNG_YM1), "PNG", AfxGetApp()->m_hInstance, 591, 521);
	m_btnYm2.SetImage(MAKEINTRESOURCE(IDR_PNG_YM2), "PNG", AfxGetApp()->m_hInstance, 634, 521);
	m_btnMusic.SetImage(MAKEINTRESOURCE(IDR_PNG_PLAYMUSIC), "PNG", AfxGetApp()->m_hInstance, 678, 521);

	m_btnSetting1.SetImage(MAKEINTRESOURCE(IDR_PNG_SERVERMANAGER), "PNG", AfxGetApp()->m_hInstance, 11, 511);
	m_btnSetting2.SetImage(MAKEINTRESOURCE(IDR_PNG_HARGA), "PNG", AfxGetApp()->m_hInstance, 79, 511);
	m_btnSetting3.SetImage(MAKEINTRESOURCE(IDR_PNG_MANAGERWARNET), "PNG", AfxGetApp()->m_hInstance, 147, 511);
	m_btnSetting4.SetImage(MAKEINTRESOURCE(IDR_PNG_CLIENT), "PNG", AfxGetApp()->m_hInstance, 215, 511);
	m_btnSetting5.SetImage(MAKEINTRESOURCE(IDR_PNG_ATURPC), "PNG", AfxGetApp()->m_hInstance, 283, 511);

	m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, -10, -497);
	m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, -40, -497);
}

void CPikabelajarDlg::ReDrawButton(Graphics &gps)
{
	m_btnClose.OnDrawWindow(gps);
	m_btnLeft.OnDrawWindow(gps);
	m_btnRight.OnDrawWindow(gps);
	m_btnSetting1.OnDrawWindow(gps);
	m_btnSetting2.OnDrawWindow(gps);
	m_btnSetting3.OnDrawWindow(gps);
	m_btnSetting4.OnDrawWindow(gps);
	m_btnSetting5.OnDrawWindow(gps);
	m_btnYoutube.OnDrawWindow(gps);
	m_btnFaceBook.OnDrawWindow(gps);
	m_btnYm1.OnDrawWindow(gps);
	m_btnYm2.OnDrawWindow(gps);
	m_btnMusic.OnDrawWindow(gps);
	m_btnSuaralaki.OnDrawWindow(gps);
	m_btnSuaraputri.OnDrawWindow(gps);
}

void CPikabelajarDlg::SetInfoText(Graphics &gps)
{
	USES_CONVERSION;

	char szDesc[255];

	SolidBrush tulis(Color(0, 224, 251));//tulis(Color(223, 146, 146));

	Font F2(L"Arial", 10, FontStyleBold, UnitPoint);

	if( m_nHapusMessage == 1)
	{
		sprintf(szDesc, "Otomatis tutup setelah 10 detik");
		gps.DrawString(A2W(szDesc), -1, &F2, PointF(639, 499), &tulis);
	}
	else
	{
		if(m_nTutorIndex == 1)
		{
			sprintf(szDesc, "PIKA Support (021) 5292 1927");
			gps.DrawString(A2W(szDesc), -1, &F2, PointF(655, 499), &tulis);
		}
		else if(m_nTutorIndex == 2)
		{
			sprintf(szDesc, "Klik Tautan untuk informasi PIKABilling");
			gps.DrawString(A2W(szDesc), -1, &F2, PointF(586, 499), &tulis);
		}
		else if(m_nTutorIndex == 3)
		{
			sprintf(szDesc, "PIKA Support (021) 5292 1927");
			gps.DrawString(A2W(szDesc), -1, &F2, PointF(655, 499), &tulis);
		}
		else if(m_nTutorIndex == 4)
		{
			sprintf(szDesc, "PIKA Billing Gratis seumur hidup");
			gps.DrawString(A2W(szDesc), -1, &F2, PointF(629, 499), &tulis);
		}
		else if(m_nTutorIndex == 5)
		{
			sprintf(szDesc, "Update Game mudah dengan PIKASoftware");
			gps.DrawString(A2W(szDesc), -1, &F2, PointF(557, 499), &tulis);
		}
		else
		{
			sprintf(szDesc, "PIKA Support (021) 5292 1927");
			gps.DrawString(A2W(szDesc), -1, &F2, PointF(655, 499), &tulis);
		}
	}
}

void CPikabelajarDlg::SetChildPos()
{
	if (m_pPanel)
	{
		CRect rInfoWnd;
		GetWindowRect(rInfoWnd);

		int nX = rInfoWnd.left + 15;
		int nY = rInfoWnd.top + 69;
		m_pPanel->MoveWindow(nX, nY, 826, 430);
	}

	if (m_pPreview)
	{
		CRect rInfoWnd;
		GetWindowRect(rInfoWnd);

		int nX = rInfoWnd.left + 15;
		int nY = rInfoWnd.top + 69;
		m_pPreview->MoveWindow(nX, nY, 826, 430);
	}

	if (m_pHintview)
	{
		CRect rInfoWnd;
		GetWindowRect(rInfoWnd);

		int nX = rInfoWnd.left + 15;
		int nY = rInfoWnd.top + 69;
		m_pHintview->MoveWindow(nX, nY, 826, 430);
	}	

	if (m_pNotice)
	{
		CRect rInfoWnd;
		GetWindowRect(rInfoWnd);

		int nX = rInfoWnd.left + 270;
		int nY = rInfoWnd.top + 440;
		m_pNotice->MoveWindow(nX, nY, 350, 52);
	}

	if (m_pResultView)
	{
		CRect rInfoWnd;
		GetWindowRect(rInfoWnd);

		int nX = rInfoWnd.left + 564;
		int nY = rInfoWnd.top + 344;
		m_pResultView->MoveWindow(nX, nY, 268, 150);
	}

	if( m_pMusicLayer )
	{
		CRect rInfoWnd;
		GetWindowRect(rInfoWnd);

		int nX = rInfoWnd.left + 860;
		int nY = rInfoWnd.top + 59;
		m_pMusicLayer->MoveWindow(nX, nY, 185, 450);	
	}
}

void CPikabelajarDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	SetChildPos();	
}

LRESULT CPikabelajarDlg::OnDisplayChange(WPARAM wParam, LPARAM lParam)
{
	SetChildPos();
	return 0;
}

void CPikabelajarDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bDrag = TRUE;
	m_bDragShowFlag = FALSE;
	SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &m_bDragShowFlag, 0);

	CDialog::OnLButtonDown(nFlags, point);
}

void CPikabelajarDlg::OnButtonClose() 
{
	ClosePanelDlg();
	ClosePreviewDlg();
	CloseHintviewDlg();
	CloseNoticeDlg();

	CDialog::OnOK();
}

void CPikabelajarDlg::OnButtonLeft() 
{	
	m_pPanel->SetImagePrev();
}

void CPikabelajarDlg::OnButtonRigth() 
{
	m_pPanel->SetImageNext();
}

void CPikabelajarDlg::OnButtonSetting1() 
{
	m_pPanel->SetTutorIndex(1);
	m_nTutorIndex = 1;

	m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, 14, 497);
	m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, 42, 497);
}

void CPikabelajarDlg::OnButtonSetting2() 
{
	m_pPanel->SetTutorIndex(2);
	m_nTutorIndex = 2;

	m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, 82, 497);
	m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, 112, 497);
}

void CPikabelajarDlg::OnButtonSetting3() 
{
	m_pPanel->SetTutorIndex(3);
	m_nTutorIndex = 3;

	m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, 152, 497);
	m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, 180, 497);
}

void CPikabelajarDlg::OnButtonSetting4() 
{
	m_pPanel->SetTutorIndex(4);
	m_nTutorIndex = 4;

	m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, 220, 497);
	m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, 248, 497);
}

void CPikabelajarDlg::OnButtonSetting5() 
{
	m_pPanel->SetTutorIndex(5);
	m_nTutorIndex = 5;

	m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, 288, 497);
	m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, 315, 497);
}

void CPikabelajarDlg::SetLinkJawab(int nJawab)
{
	m_pPanel->SetLinkJawab(nJawab);
}

void CPikabelajarDlg::SetNextUgian(int nTutorIndex, BOOL bUlang)
{
	if(bUlang == TRUE)
	{
		m_pPanel->SetTutorIndex(nTutorIndex);
		m_nTutorIndex = nTutorIndex;
	}
	else
	{
		if(nTutorIndex >= 5)
			nTutorIndex = 1;
		else
			nTutorIndex = nTutorIndex + 1;	

		m_pPanel->SetTutorIndex(nTutorIndex);
		m_nTutorIndex = nTutorIndex;
	}

	if(m_nTutorIndex == 1)
	{
		m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, 14, 497);	
		m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, 42, 497);
	}
	else if(m_nTutorIndex == 2)
	{
		m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, 82, 497);	
		m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, 112, 497);	
	}
	else if(m_nTutorIndex == 3)
	{
		m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, 152, 497);
	    m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, 180, 497);	
	}
	else if(m_nTutorIndex == 4)
	{
		m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, 220, 497);
	    m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, 248, 497);	
	}
	else if(m_nTutorIndex == 5)
	{
		m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, 288, 497);
	    m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, 315, 497);	
	}
}

void CPikabelajarDlg::OnButtonYoutube() 
{
	::ShellExecute(NULL, "open", "http://www.youtube.com/user/PIKAWarnet", NULL, NULL, SW_SHOW);	
}

void CPikabelajarDlg::OnButtonFacebook() 
{
	::ShellExecute(NULL, "open", "https://www.facebook.com/pikawarnet", NULL, NULL, SW_SHOW);	
}

void CPikabelajarDlg::OnButtonYm1() 
{
	::ShellExecute(NULL, "open", "ymsgr:sendIM?cs1.pika", NULL, NULL, SW_SHOW);	
}

void CPikabelajarDlg::OnButtonYm2() 
{
	::ShellExecute(NULL, "open", "ymsgr:sendIM?cs2.pika", NULL, NULL, SW_SHOW);	
}

void CPikabelajarDlg::OnButtonMusic() 
{
	if(m_bMusicBuka == FALSE)
	{
		CreateMusicDlg();
		m_bMusicBuka = TRUE;

		m_btnMusic.Free();
		m_btnMusic.SetImage(MAKEINTRESOURCE(IDR_PNG_PLAYMUSIC_STOP), "PNG", AfxGetApp()->m_hInstance, 678, 521);
		
	}
	else
	{
		CloseMusicDlg(); 
		m_bMusicBuka = FALSE;

		m_btnMusic.Free();
		m_btnMusic.SetImage(MAKEINTRESOURCE(IDR_PNG_PLAYMUSIC), "PNG", AfxGetApp()->m_hInstance, 678, 521);
	}
}

void CPikabelajarDlg::OnButtonSuaralaki() 
{
	m_pPanel->SetSuaraIndex(1);

	//m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, -10, -497);
	//m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, -40, -497);
}

void CPikabelajarDlg::OnButtonSuaraputri() 
{
	if( m_nSuaraIndex == 2)
		m_nSuaraIndex = 3;
	else
		m_nSuaraIndex = 2;

	m_pPanel->SetSuaraIndex(m_nSuaraIndex);

	//m_btnSuaralaki.SetImage(MAKEINTRESOURCE(IDR_PNG_MAN), "PNG", AfxGetApp()->m_hInstance, -10, -497);
	//m_btnSuaraputri.SetImage(MAKEINTRESOURCE(IDR_PNG_WOMAN), "PNG", AfxGetApp()->m_hInstance, -40, -497);
}
