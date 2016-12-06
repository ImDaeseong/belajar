// PikabelajrInDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pikabelajar.h"
#include "PikabelajrInDlg.h"
#include "pikabelajarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPikabelajrInDlg dialog


CPikabelajrInDlg::CPikabelajrInDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPikabelajrInDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPikabelajrInDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	InitVariables();
}


void CPikabelajrInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPikabelajrInDlg)
	DDX_Control(pDX, IDC_STATIC_BANNER, m_RollingBanner);
	DDX_Control(pDX, IDC_STATIC_DISPICTURE, m_ctrlPictureImg);
	DDX_Control(pDX, IDC_STATIC_SPLASH, m_ctrlSpashImg);
	DDX_Control(pDX, IDC_STATIC_HINTIMAGE, m_PreviewImg);
	//DDX_Control(pDX, IDC_STATIC_HINTIMAGE, m_RollingBannerImg);
	DDX_Control(pDX, IDC_STATIC_TANYA, m_Tanya);
	DDX_Control(pDX, IDC_STATIC_JAWAB1, m_Jawab1);
    DDX_Control(pDX, IDC_STATIC_JAWAB2, m_Jawab2);
	DDX_Control(pDX, IDC_STATIC_JAWAB3, m_Jawab3);
	DDX_Control(pDX, IDC_STATIC_JAWAB4, m_Jawab4);	
	DDX_Control(pDX, IDC_BUTTON_TANYA, m_btnTanya);
	DDX_Control(pDX, IDC_BUTTON_JAWAB1, m_btnJawab1);
	DDX_Control(pDX, IDC_BUTTON_JAWAB2, m_btnJawab2);
	DDX_Control(pDX, IDC_BUTTON_JAWAB3, m_btnJawab3);
	DDX_Control(pDX, IDC_BUTTON_JAWAB4, m_btnJawab4);
	DDX_Control(pDX, IDC_BUTTON_ZOOM, m_btnZoom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPikabelajrInDlg, CDialog)
	//{{AFX_MSG_MAP(CPikabelajrInDlg)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_JAWAB1, OnButtonJawab1)
	ON_BN_CLICKED(IDC_BUTTON_JAWAB2, OnButtonJawab2)
	ON_BN_CLICKED(IDC_BUTTON_JAWAB3, OnButtonJawab3)
	ON_BN_CLICKED(IDC_BUTTON_JAWAB4, OnButtonJawab4)
	ON_BN_CLICKED(IDC_BUTTON_ZOOM, OnButtonZoom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPikabelajrInDlg message handlers

BOOL CPikabelajrInDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadImage();
	
	InitCtrls();

	SetTimer(1, 1000, NULL);

	SetTimer(3, 3000, NULL);

	return TRUE; 
}

void CPikabelajrInDlg::OnPaint() 
{
	CPaintDC dc(this);

	DrawSkin(&dc);
}

void CPikabelajrInDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDialog::OnMouseMove(nFlags, point);
}

void CPikabelajrInDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);

	SAFE_DELETE(m_pbgImage);
}

BOOL CPikabelajrInDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
		
	return CDialog::PreTranslateMessage(pMsg);
}

void CPikabelajrInDlg::LoadImage()
{
	if (!m_pbgImage)
	{
		m_pbgImage = new CGdiPlusBitmapResource;

		if (!m_pbgImage->Load(MAKEINTRESOURCE(IDR_PNG_INBACK), "PNG", AfxGetApp()->m_hInstance))
		{
			return;
		}
	}

	int x = m_pbgImage->m_pBitmap->GetWidth();
	int y = m_pbgImage->m_pBitmap->GetHeight();


	MoveWindow(0, 0, x, y);	
}
void CPikabelajrInDlg::DrawSkin(CDC *pDC)
{
	int x = m_pbgImage->m_pBitmap->GetWidth();
	int y = m_pbgImage->m_pBitmap->GetHeight();

	Graphics gps(pDC->GetSafeHdc());
	gps.DrawImage(m_pbgImage->m_pBitmap, Rect(0, 0, x, y) , 0, 0, x, y, UnitPixel);

	
	if(m_nTutorIndex != 0)
	{
		Color color;
		CRect rcClient;
		GetClientRect(&rcClient);
	
		color.SetFromCOLORREF(RGB(0,224,251));//color.SetFromCOLORREF(RGB(250,118,58));
		Pen pen(color, 1);
		gps.DrawRectangle(&pen, Rect(rcClient.left + 9, rcClient.top + 69, rcClient.Width()/2 - 37, rcClient.Height()/2 + 5));//gps.FillRectangle(&brBrush, Rect(rcClient.left + 9, rcClient.top + 9, rcClient.Width()/2 - 37, rcClient.Height()/2 + 5));
		gps.DrawRectangle(&pen, Rect(rcClient.left + 440, rcClient.top + 69, rcClient.Width()/2 - 37, rcClient.Height()/2 + 5));//gps.FillRectangle(&brBrush, Rect(rcClient.left + 440, rcClient.top + 9, rcClient.Width()/2 - 37, rcClient.Height()/2 + 5));
	}
}

void CPikabelajrInDlg::SetParent(CPikabelajarDlg * pParent)
{
	m_pParent = pParent;
}

void CPikabelajrInDlg::InitVariables()
{
	m_pbgImage = NULL;

	m_nTutorIndex = 0;

	m_nImgIndex = 0;

	m_bMulaiClick = FALSE;

	m_nSuaraIndex = 0;

	m_nPhotoIndex = 0;

	m_nBenarCount = 0;
	m_nsalahCount = 0;
}

void CPikabelajrInDlg::InitCtrls()
{
	//splash image
	m_ctrlSpashImg.LoadImage(IDR_PNG_INTRO, "PNG");

	CRect rSpalshImgSize;
	m_ctrlSpashImg.GetPictureRect(rSpalshImgSize);
	m_ctrlSpashImg.MoveWindow(0, 0, rSpalshImgSize.Width() , rSpalshImgSize.Height() );


	//rolling
	m_RollingBanner.MoveWindow(-620, -405, 200, 18);
	m_RollingBanner.SetFontInfo("Arial", 10, FW_NORMAL);
	m_RollingBanner.SetTextColor(RGB(255, 123, 52));
	m_RollingBanner.SetBackGroundColor(RGB(248,246,232));
	m_RollingBanner.SetInitRolling();	

	
	//hint
	//m_PreviewImg.LoadImage(IDR_PNG_DEFAULT, "PNG");
	m_PreviewImg.MoveWindow(-443, -70, 372 , 218);
    

    //photo adv
	/*
	m_RollingBannerImg.LoadImage(IDR_GIF2, "GIF");
	CRect rPhotoImgSize;
	m_RollingBannerImg.GetPictureRect(rPhotoImgSize);
	m_RollingBannerImg.MoveWindow(-443, -70, 372 , 218);
	*/


    //default image
	//m_ctrlPictureImg.LoadImage(IDR_PNG_DEFAULT, "PNG");
	//CRect rImgSize;
	//m_ctrlPictureImg.GetPictureRect(rImgSize);
	m_ctrlPictureImg.MoveWindow(-100, -700, 372 , 218);
	
	
	//zoom
	m_btnZoom.LoadStdImage(IDR_PNG_ZOOM, "PNG", AfxGetApp()->m_hInstance, 10, 270);	
	m_btnZoom.MoveWindow(-390, -250, 40, 40);

    
	//tandatanya
	m_btnTanya.LoadStdImage(IDR_PNG_TANYA, "PNG", AfxGetApp()->m_hInstance, 10, 10);	
	m_btnTanya.MoveWindow(-10, -295, 30, 30);
	m_btnTanya.EnableButton(FALSE);
	    
 
    //tanya
	m_Tanya.MoveWindow(-500, -100, 770, 50);
	m_Tanya.SetFontName("Arial");
	m_Tanya.SetFontSize(15);
	m_Tanya.SetFontBold(TRUE);
	m_Tanya.SetBkColor(RGB(248,247,233));
	m_Tanya.SetText("");
	m_Tanya.SetTextColor(RGB(0, 0, 0));


	//m_Jawab1
	m_Jawab1.MoveWindow(-35, -295, 780, 18);
	m_Jawab1.SetFontName("Arial");
	m_Jawab1.SetFontSize(13);
	m_Jawab1.SetFontBold(TRUE);
	m_Jawab1.SetBkColor(RGB(248,247,233));
	m_Jawab1.SetText("");
	m_Jawab1.SetTextColor(RGB(0, 0, 0));
	m_Jawab1.SetLink(TRUE);
	m_Jawab1.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	m_Jawab1.Setjawab(1);

	m_btnJawab1.LoadStdImage(IDR_PNG_AA, "PNG", AfxGetApp()->m_hInstance, 10, 270);	
	m_btnJawab1.MoveWindow(-10, -295, 17, 17);


	//m_Jawab2
	m_Jawab2.MoveWindow(-35, -325, 780, 18);
	m_Jawab2.SetFontName("Arial");
	m_Jawab2.SetFontSize(13);
	m_Jawab2.SetFontBold(TRUE);
	m_Jawab2.SetBkColor(RGB(248,247,233));
	m_Jawab2.SetText("");
	m_Jawab2.SetTextColor(RGB(0, 0, 0));
	m_Jawab2.SetLink(TRUE);
	m_Jawab2.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	m_Jawab2.Setjawab(2);

	m_btnJawab2.LoadStdImage(IDR_PNG_BB, "PNG", AfxGetApp()->m_hInstance, 10, 290);	
	m_btnJawab2.MoveWindow(-10, -325, 17, 17);


	//m_Jawab3
	m_Jawab3.MoveWindow(-35, -355, 780, 18);
	m_Jawab3.SetFontName("Arial");
	m_Jawab3.SetFontSize(13);
	m_Jawab3.SetFontBold(TRUE);
	m_Jawab3.SetBkColor(RGB(248,247,233));
	m_Jawab3.SetText("");
	m_Jawab3.SetTextColor(RGB(0, 0, 0));
	m_Jawab3.SetLink(TRUE);
	m_Jawab3.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	m_Jawab3.Setjawab(3);

	m_btnJawab3.LoadStdImage(IDR_PNG_CC, "PNG", AfxGetApp()->m_hInstance, 10, 310);	
	m_btnJawab3.MoveWindow(-10, -355, 17, 17);


	//m_Jawab4
	m_Jawab4.MoveWindow(-35, -385, 780, 18);
	m_Jawab4.SetFontName("Arial");
	m_Jawab4.SetFontSize(13);
	m_Jawab4.SetFontBold(TRUE);
	m_Jawab4.SetBkColor(RGB(248,247,233));
	m_Jawab4.SetText("");
	m_Jawab4.SetTextColor(RGB(0, 0, 0));
	m_Jawab4.SetLink(TRUE);
	m_Jawab4.SetLinkCursor(AfxGetApp()->LoadCursor(IDC_HAND));
	m_Jawab4.Setjawab(4);

	m_btnJawab4.LoadStdImage(IDR_PNG_DD, "PNG", AfxGetApp()->m_hInstance, 10, 330);	
	m_btnJawab4.MoveWindow(-10, -385, 17, 17);	
}

void CPikabelajrInDlg::ChangeCtrls()
{
	//splash image
	m_ctrlSpashImg.MoveWindow(-10, -10, 0 , 0);


	//rolling
	m_RollingBanner.MoveWindow(620, 407, 200, 18);


	
	//hint	
	m_PreviewImg.MoveWindow(443, 70, 372 , 218);


	//photo adv
	/*
	CRect rPhotoImgSize;
	m_RollingBannerImg.GetPictureRect(rPhotoImgSize);
	m_RollingBannerImg.MoveWindow(443, 70, 372 , 218);// rPhotoImgSize.Width() , rPhotoImgSize.Height());
	*/
	

    //default image
	CRect rImgSize;
	m_ctrlPictureImg.GetPictureRect(rImgSize);
	m_ctrlPictureImg.MoveWindow(10, 70, rImgSize.Width() , rImgSize.Height() );

	
	//zoom
	m_btnZoom.MoveWindow(390, 165, 40, 40);//MoveWindow(390, 250, 28, 30);


	//tandatanya
	m_btnTanya.MoveWindow(10, 10, 30, 30);
	

    //tanya
	m_Tanya.MoveWindow(45, 10, 770, 50);
	

	//m_Jawab1
	m_Jawab1.MoveWindow(35, 308, 780, 18);
	m_btnJawab1.MoveWindow(10, 307, 17, 17);


	//m_Jawab2
	m_Jawab2.MoveWindow(35, 335, 780, 18);	
	m_btnJawab2.MoveWindow(10, 334, 17, 17);


	//m_Jawab3
	m_Jawab3.MoveWindow(35, 363, 780, 18);
	m_btnJawab3.MoveWindow(10, 362, 17, 17);


	//m_Jawab4
	m_Jawab4.MoveWindow(35, 389, 780, 18);	
	m_btnJawab4.MoveWindow(10, 388, 17, 17);
}

void CPikabelajrInDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
	{
		KillTimer(1);

		if(m_bMulaiClick == TRUE)
		{
			m_ctrlSpashImg.MoveWindow(-10, -10, 0, 0);
		}
		else
		{	
			m_ctrlSpashImg.ReleaseFreeImage();
			m_ctrlSpashImg.LoadImage(IDR_PNG_INTRO2, "PNG");		
			
			CRect rSpalshImgSize;
			m_ctrlSpashImg.GetPictureRect(rSpalshImgSize);
			m_ctrlSpashImg.MoveWindow(0, 0, rSpalshImgSize.Width() , rSpalshImgSize.Height() );
					
			SetTimer(2, 3000, NULL);
		}
	}
	else if (nIDEvent == 2)
	{
		KillTimer(2);

		if(m_bMulaiClick == TRUE)
		{	
			m_ctrlSpashImg.MoveWindow(-10, -10, 0, 0);		
		}
		else
		{	
			m_ctrlSpashImg.ReleaseFreeImage();
			m_ctrlSpashImg.LoadImage(IDR_PNG_INTRO3, "PNG");

			CRect rSpalshImgSize;
			m_ctrlSpashImg.GetPictureRect(rSpalshImgSize);
			m_ctrlSpashImg.MoveWindow(0, 0, rSpalshImgSize.Width() , rSpalshImgSize.Height() );
		}
	}
	else if (nIDEvent == 3)
	{
		/*
		if(m_bMulaiClick == TRUE)
		{
			if(m_nPhotoIndex >= 10)//if(m_nPhotoIndex >= 11)
				m_nPhotoIndex = 1;
			else
				m_nPhotoIndex = m_nPhotoIndex + 1;	

			m_RollingBannerImg.SetButtonClick(TRUE);
			m_RollingBannerImg.ReleaseFreeImage();


			if(m_nPhotoIndex == 1)
				m_RollingBannerImg.LoadImage(IDR_GIF1, "GIF");
			//else if(m_nPhotoIndex == 2)
			//	m_RollingBannerImg.LoadImage(IDR_GIF2, "GIF");
			else if(m_nPhotoIndex == 2)
				m_RollingBannerImg.LoadImage(IDR_GIF3, "GIF");
			else if(m_nPhotoIndex == 3)
				m_RollingBannerImg.LoadImage(IDR_GIF4, "GIF");
			else if(m_nPhotoIndex == 4)
				m_RollingBannerImg.LoadImage(IDR_GIF5, "GIF");
			else if(m_nPhotoIndex == 5)
				m_RollingBannerImg.LoadImage(IDR_GIF6, "GIF");
			else if(m_nPhotoIndex == 6)
				m_RollingBannerImg.LoadImage(IDR_GIF7, "GIF");
			else if(m_nPhotoIndex == 7)
				m_RollingBannerImg.LoadImage(IDR_GIF8, "GIF");
			else if(m_nPhotoIndex == 8)
				m_RollingBannerImg.LoadImage(IDR_GIF9, "GIF");
			else if(m_nPhotoIndex == 9)
				m_RollingBannerImg.LoadImage(IDR_GIF10, "GIF");
			else if(m_nPhotoIndex == 10)
				m_RollingBannerImg.LoadImage(IDR_GIF11, "GIF");
			

			m_RollingBannerImg.SetPictureStaticClick(TRUE);
			m_RollingBannerImg.SetPictureStaticCursor(TRUE);
			m_RollingBannerImg.SetButtonClick(TRUE);


			CRect rImgaSize;
			m_RollingBannerImg.GetPictureRect(rImgaSize);
			m_RollingBannerImg.MoveWindow(443, 70, rImgaSize.Width() , rImgaSize.Height() );
			m_RollingBannerImg.InvalidateRect(NULL, TRUE);	
		}
		else
		{
			m_RollingBannerImg.MoveWindow(-443, -70, 372, 218);		
		}
		*/
	}

	CDialog::OnTimer(nIDEvent);
}

void CPikabelajrInDlg::SetImageNext()
{
	if(m_nTutorIndex == 0)
		return;

	//preview check
	m_pParent->ClosePreviewDlg();

	//hintview check
	m_pParent->CloseHintviewDlg();

	//notice
	m_pParent->CloseNoticeDlg();
	
	int nSize = m_ArrayClientInfo.GetSize();

	if(m_nImgIndex >= nSize)
		m_nImgIndex = 1;
	else
		m_nImgIndex = m_nImgIndex + 1;	


	GetClientInfo(m_nImgIndex, m_strTanya, m_strJawab1, m_strJawab2, m_strJawab3, m_strJawab4, m_strBenarJawab, m_strImagekecil, m_strImageBesar, m_strHint);

	CString strTanya;
	strTanya.Format("%s [%ld/%ld]",m_strTanya, m_nImgIndex, nSize);

	m_Tanya.SetText(strTanya);//SetText(m_strTanya);
	
	m_Jawab1.SetText(m_strJawab1);
	m_Jawab1.SetTextColor(RGB(0, 0, 0));
	
	m_Jawab2.SetText(m_strJawab2);
	m_Jawab2.SetTextColor(RGB(0, 0, 0));

	m_Jawab3.SetText(m_strJawab3);
	m_Jawab3.SetTextColor(RGB(0, 0, 0));

	m_Jawab4.SetText(m_strJawab4);	
	m_Jawab4.SetTextColor(RGB(0, 0, 0));

	
	//left photo
	m_ctrlPictureImg.SetButtonClick(TRUE);
	m_ctrlPictureImg.ReleaseFreeImage();
	m_ctrlPictureImg.SetPhotoResize(0, 0);//SetPhotoResize(375, 218);

	if( !m_ctrlPictureImg.LoadImage(atoi(m_strImagekecil), "GIF") )
		return;

	m_ctrlPictureImg.SetPictureStaticClick(TRUE);
	m_ctrlPictureImg.SetPictureStaticCursor(TRUE);
	m_ctrlPictureImg.SetPictureMoveRight(TRUE);

	CRect rImgSize;
	m_ctrlPictureImg.GetPictureRect(rImgSize);
	m_ctrlPictureImg.MoveWindow(10, 70, rImgSize.Width() , rImgSize.Height() );
	m_ctrlPictureImg.InvalidateRect(NULL, TRUE);



	//right photo
	if( !m_PreviewImg.LoadImage(atoi(m_strHint), "HINT") )
		return;

	m_PreviewImg.SetPictureStaticClick(TRUE);
	m_PreviewImg.SetPictureStaticCursor(TRUE);
	m_PreviewImg.MoveWindow(443, 70, 372 , 218 );
	m_PreviewImg.InvalidateRect(NULL, TRUE);


	/*
	CRect rcClient;
	GetClientRect(&rcClient);

	InvalidateRect(CRect(rcClient.left + 9, rcClient.top + 69, rcClient.Width()/2 - 37, rcClient.Height()/2 + 5));       
	//InvalidateRect(CRect(rcClient.left + 440, rcClient.top + 69, rcClient.Width()/2 - 37, rcClient.Height()/2 + 5));
    */
}

void CPikabelajrInDlg::SetImagePrev()
{	
	if(m_nTutorIndex == 0)
		return;

	//preview check
	m_pParent->ClosePreviewDlg();

	//hintview check
	m_pParent->CloseHintviewDlg();

	//notice
	m_pParent->CloseNoticeDlg();

	int nSize = m_ArrayClientInfo.GetSize();
	int nTempIndex = 0;

	if(m_nImgIndex > 1)
		nTempIndex = m_nImgIndex - 1;	
	else
		nTempIndex = 1;

	if(m_nImgIndex == nTempIndex)
		return;

	m_nImgIndex = nTempIndex;

	
	GetClientInfo(m_nImgIndex, m_strTanya, m_strJawab1, m_strJawab2, m_strJawab3, m_strJawab4, m_strBenarJawab,  m_strImagekecil, m_strImageBesar, m_strHint);


	CString strTanya;
	strTanya.Format("%s [%ld/%ld]",m_strTanya, m_nImgIndex, nSize);

	m_Tanya.SetText(strTanya);//SetText(m_strTanya);
	
	m_Jawab1.SetText(m_strJawab1);
	m_Jawab1.SetTextColor(RGB(0, 0, 0));

	m_Jawab2.SetText(m_strJawab2);
	m_Jawab2.SetTextColor(RGB(0, 0, 0));

	m_Jawab3.SetText(m_strJawab3);
	m_Jawab3.SetTextColor(RGB(0, 0, 0));

	m_Jawab4.SetText(m_strJawab4);
	m_Jawab4.SetTextColor(RGB(0, 0, 0));


	//left photo
	m_ctrlPictureImg.SetButtonClick(TRUE);
	m_ctrlPictureImg.ReleaseFreeImage();
	m_ctrlPictureImg.SetPhotoResize(0, 0);//SetPhotoResize(375, 218);

	if( !m_ctrlPictureImg.LoadImage(atoi(m_strImagekecil), "GIF") )
		return;

	m_ctrlPictureImg.SetPictureStaticClick(TRUE);
	m_ctrlPictureImg.SetPictureStaticCursor(TRUE);
	m_ctrlPictureImg.SetPictureMoveRight(FALSE);

	CRect rImgSize;
	m_ctrlPictureImg.GetPictureRect(rImgSize);
	m_ctrlPictureImg.MoveWindow(10, 70, rImgSize.Width() , rImgSize.Height() );
	m_ctrlPictureImg.InvalidateRect(NULL, TRUE);


	//right photo
	if( !m_PreviewImg.LoadImage(atoi(m_strHint), "HINT") )
		return;

	m_PreviewImg.SetPictureStaticClick(TRUE);
	m_PreviewImg.SetPictureStaticCursor(TRUE);
	m_PreviewImg.MoveWindow(443, 70, 372 , 218 );
	m_PreviewImg.InvalidateRect(NULL, TRUE);


	/*	
	CRect rcClient;
	GetClientRect(&rcClient);

	InvalidateRect(CRect(rcClient.left + 9, rcClient.top + 69, rcClient.Width()/2 - 37, rcClient.Height()/2 + 5));       
	//InvalidateRect(CRect(rcClient.left + 440, rcClient.top + 69, rcClient.Width()/2 - 37, rcClient.Height()/2 + 5));
	*/
}

void CPikabelajrInDlg::SetSuaraIndex(int nSuaraIndex)
{
	m_nSuaraIndex = nSuaraIndex;
}

void CPikabelajrInDlg::SetTutorIndex(int nTutorIndex)
{ 
	m_bMulaiClick = TRUE;

	m_nImgIndex = 0;

	m_nBenarCount = 0;
	m_nsalahCount = 0;

	m_nTutorIndex = nTutorIndex;


	CString strlstfileName = "";


	if(m_nTutorIndex == 1)
	{
		strlstfileName.Format("%s\\servermanajemen.lst", CFunc::GetModulePath());
	}
	else if(m_nTutorIndex == 2)
	{
		strlstfileName.Format("%s\\harga.lst", CFunc::GetModulePath());
	}
	else if(m_nTutorIndex == 3)
	{
		strlstfileName.Format("%s\\manajemenwarnet.lst", CFunc::GetModulePath());
	}
	else if(m_nTutorIndex == 4)
	{
		strlstfileName.Format("%s\\client.lst", CFunc::GetModulePath());
	}
	else if(m_nTutorIndex == 5)
	{
		strlstfileName.Format("%s\\ATURPC.lst", CFunc::GetModulePath());
	}


	if(strlstfileName == "")
		return;


	//preview check
	m_pParent->ClosePreviewDlg();

	//hintview check
	m_pParent->CloseHintviewDlg();

	//notice
	m_pParent->CloseNoticeDlg();

	//Result view
	m_pParent->CloseResultViewDlg();

	ChangeCtrls();

	RemoveClientInfo();

   	CStdioFile stdioFile;
	if(!stdioFile.Open(strlstfileName, CStdioFile::modeRead | CStdioFile::typeText, NULL))
 	{
		return;
 	}
 	else
 	{
		int nIndex = 1;
 		CString str;
 		while(stdioFile.ReadString(str))
 		{			
			CString strTanya = GetElementInListFile(0, CString(str));
			CString strJawab1 = GetElementInListFile(1, CString(str));
			CString strJawab2 = GetElementInListFile(2, CString(str));
			CString strJawab3 = GetElementInListFile(3, CString(str));
			CString strJawab4 = GetElementInListFile(4, CString(str));
			CString strBenarJawab = GetElementInListFile(5, CString(str));
			CString strImagekecil = GetElementInListFile(6, CString(str));
			CString strImageBesar = GetElementInListFile(7, CString(str));
			CString strHint = GetElementInListFile(8, CString(str));

			AddClientInfo(nIndex, strTanya, strJawab1, strJawab2, strJawab3, strJawab4, strBenarJawab, strImagekecil, strImageBesar, strHint);
			nIndex++;
 		}
	}
	stdioFile.Close(); 

	SetImageNext();
}

CString CPikabelajrInDlg::GetElementInListFile(int nOpt, CString strData)
{
	CString strTanya;
	CString strJawab1;
	CString strJawab2;
	CString	strJawab3;
	CString strJawab4;
	CString strBenarJawab;
	CString strImagekecil;
	CString strImageBesar;
	CString strHint;
    int nFindIndexOfStr;
	

	//strTanya 
	nFindIndexOfStr = strData.Find("|");
	if(nFindIndexOfStr == -1)
		return "";

	strTanya = strData.Mid(0, nFindIndexOfStr);
	strData = strData.Right(strData.GetLength() - nFindIndexOfStr - 1);


	//strJawab1
	nFindIndexOfStr = strData.Find("|");
	if(nFindIndexOfStr == -1)
		return "";

	strJawab1 = strData.Mid(0, nFindIndexOfStr);
	strData = strData.Right(strData.GetLength() - nFindIndexOfStr - 1);


	//strJawab2
	nFindIndexOfStr = strData.Find("|");
	if(nFindIndexOfStr == -1)
		return "";

	strJawab2 = strData.Mid(0, nFindIndexOfStr);
	strData = strData.Right(strData.GetLength() - nFindIndexOfStr - 1);


	//strJawab3
	nFindIndexOfStr = strData.Find("|");
	if(nFindIndexOfStr == -1)
		return "";

	strJawab3 = strData.Mid(0, nFindIndexOfStr);
	strData = strData.Right(strData.GetLength() - nFindIndexOfStr - 1);


	//strJawab4
	nFindIndexOfStr = strData.Find("|");
	if(nFindIndexOfStr == -1)
		return "";

	strJawab4 = strData.Mid(0, nFindIndexOfStr);
	strData = strData.Right(strData.GetLength() - nFindIndexOfStr - 1);


	//strBenarJawab
	nFindIndexOfStr = strData.Find("|");
	if(nFindIndexOfStr == -1)
		return "";

	strBenarJawab = strData.Mid(0, nFindIndexOfStr);
	strData = strData.Right(strData.GetLength() - nFindIndexOfStr - 1);


	//strImagekecil
	nFindIndexOfStr = strData.Find("|");
	if(nFindIndexOfStr == -1)
		return "";

	strImagekecil = strData.Mid(0, nFindIndexOfStr);
	strData = strData.Right(strData.GetLength() - nFindIndexOfStr - 1);


	//strImageBesar
	nFindIndexOfStr = strData.Find("|");
	if(nFindIndexOfStr == -1)
		return "";

	strImageBesar = strData.Mid(0, nFindIndexOfStr);
	strData = strData.Right(strData.GetLength() - nFindIndexOfStr - 1);


	//strHint
	strHint = strData;

	
	if(nOpt == 0)
		return strTanya;	
	else if(nOpt == 1)
		return strJawab1;
	else if(nOpt == 2)
		return strJawab2;
	else if(nOpt == 3)
		return strJawab3;
	else if(nOpt == 4)
		return strJawab4;
	else if(nOpt == 5)
		return strBenarJawab;
	else if(nOpt == 6)
		return strImagekecil;
	else if(nOpt == 7)
		return strImageBesar;
	else if(nOpt == 8)
		return strHint;

	return CString("");
}

void CPikabelajrInDlg::RemoveClientInfo()
{	
	int lc_nIndex = m_ArrayClientInfo.GetSize();

	while (lc_nIndex--)
	{
		delete m_ArrayClientInfo.GetAt(lc_nIndex);
	}

    m_ArrayClientInfo.RemoveAll();
}

void CPikabelajrInDlg::AddClientInfo(int nIndex, CString strTanya, CString strJawab1, CString strJawab2, CString strJawab3, CString strJawab4, CString strBenarJawab,  CString strImagekecil, CString strImageBesar, CString strHint)
{
	CUgianInfo* pIndex = new CUgianInfo(nIndex, strTanya, strJawab1, strJawab2, strJawab3, strJawab4, strBenarJawab, strImagekecil, strImageBesar, strHint);

	m_ArrayClientInfo.Add(pIndex);
}

void CPikabelajrInDlg::GetClientInfo(int nIndex, CString& strTanya, CString& strJawab1, CString& strJawab2, CString& strJawab3, CString& strJawab4, CString& strBenarJawab, CString& strImagekecil, CString& strImageBesar, CString& strHint)
{		
	int nSize = m_ArrayClientInfo.GetSize(); 
	for(int i=0; i < nSize; i++)
	{
		CUgianInfo* pIndex = (CUgianInfo*)m_ArrayClientInfo.GetAt(i);

		if( pIndex->m_nIndex == nIndex)
		{
			strTanya = pIndex->m_strTanya;
			strJawab1 = pIndex->m_strJawab1;
			strJawab2 = pIndex->m_strJawab2;
			strJawab3 = pIndex->m_strJawab3;
			strJawab4 = pIndex->m_strJawab4;
			strBenarJawab = pIndex->m_strBenarJawab;
            strImagekecil = pIndex->m_strImagekecil;
			strImageBesar = pIndex->m_strImageBesar;
			strHint = pIndex->m_strHint; 
			
			break;
		}
	}
}

void CPikabelajrInDlg::CallSuaraBenar()
{
	if( m_nSuaraIndex == 0)
	{
		::PlaySound(MAKEINTRESOURCE(IDR_WAVE_BENAR_PUTRI), 0, SND_RESOURCE | SND_ASYNC); 	
	}
	else if( m_nSuaraIndex == 1)//ADI
	{
		::PlaySound(MAKEINTRESOURCE(IDR_WAVE_BENAR_ADI), 0, SND_RESOURCE | SND_ASYNC); 	
	}
	else if( m_nSuaraIndex == 2)//Desita
	{
		::PlaySound(MAKEINTRESOURCE(IDR_WAVE_BENAR_DESITA), 0, SND_RESOURCE | SND_ASYNC); 	
	}
	else if( m_nSuaraIndex == 3)//Putri
	{
		::PlaySound(MAKEINTRESOURCE(IDR_WAVE_BENAR_PUTRI), 0, SND_RESOURCE | SND_ASYNC); 	
	}
}

void CPikabelajrInDlg::CallSuaraSalah()
{
	if( m_nSuaraIndex == 0)
	{
		::PlaySound(MAKEINTRESOURCE(IDR_WAVE_SALAH_PUTRI), 0, SND_RESOURCE | SND_ASYNC); 	
	}
	else if( m_nSuaraIndex == 1)//ADI
	{
		::PlaySound(MAKEINTRESOURCE(IDR_WAVE_SALAH_ADI), 0, SND_RESOURCE | SND_ASYNC); 	
	}
	else if( m_nSuaraIndex == 2)//Desita
	{
		::PlaySound(MAKEINTRESOURCE(IDR_WAVE_SALAH_DESITA), 0, SND_RESOURCE | SND_ASYNC); 	
	}
	else if( m_nSuaraIndex == 3)//Putri
	{
		::PlaySound(MAKEINTRESOURCE(IDR_WAVE_SALAH_PUTRI), 0, SND_RESOURCE | SND_ASYNC); 	
	}
}

void CPikabelajrInDlg::OnButtonJawab1() 
{
	if(m_nTutorIndex == 0)
		return;

	if(lstrcmpi(m_strBenarJawab, "A") == 0)
	{
		m_Jawab1.SetTextColor(RGB(0, 255, 0));

		m_pParent->CreateNoticeDlg(1);

		CallSuaraBenar(); 

		m_nBenarCount ++;

		Sleep(1000);

		//SetImageNext();
		
		int nSize = m_ArrayClientInfo.GetSize();
		if(m_nImgIndex == nSize)
		{
			//notice
			m_pParent->CloseNoticeDlg();

			SetUjianResultMessage();
		}
		else
			SetImageNext();
	}
	else
	{
		m_Jawab1.SetTextColor(RGB(255, 0, 0));

		CallSuaraSalah(); 

		m_nsalahCount++;
	}

    m_Jawab2.SetTextColor(RGB(0, 0, 0));
	m_Jawab3.SetTextColor(RGB(0, 0, 0));
	m_Jawab4.SetTextColor(RGB(0, 0, 0));
}

void CPikabelajrInDlg::OnButtonJawab2() 
{
	if(m_nTutorIndex == 0)
		return;

	if(lstrcmpi(m_strBenarJawab, "B") == 0)
	{
		m_Jawab2.SetTextColor(RGB(0, 255, 0));

		m_pParent->CreateNoticeDlg(2);

		CallSuaraBenar(); 

		m_nBenarCount ++;

		Sleep(1000);

		//SetImageNext();

		int nSize = m_ArrayClientInfo.GetSize();
		if(m_nImgIndex == nSize)
		{
			//notice
			m_pParent->CloseNoticeDlg();

			SetUjianResultMessage();
		}
		else
			SetImageNext();
	}
	else
	{
		m_Jawab2.SetTextColor(RGB(255, 0, 0));

		CallSuaraSalah();

		m_nsalahCount++;
	}

	m_Jawab1.SetTextColor(RGB(0, 0, 0));
	m_Jawab3.SetTextColor(RGB(0, 0, 0));
	m_Jawab4.SetTextColor(RGB(0, 0, 0));
}

void CPikabelajrInDlg::OnButtonJawab3() 
{
	if(m_nTutorIndex == 0)
		return;

	if(lstrcmpi(m_strBenarJawab, "C") == 0)
	{
		m_Jawab3.SetTextColor(RGB(0, 255, 0));

		m_pParent->CreateNoticeDlg(3);

		CallSuaraBenar();

		m_nBenarCount ++;

		Sleep(1000);

		//SetImageNext();

		int nSize = m_ArrayClientInfo.GetSize();
		if(m_nImgIndex == nSize)
		{
			//notice
			m_pParent->CloseNoticeDlg();

			SetUjianResultMessage();
		}
		else
			SetImageNext();
	}
	else
	{
		m_Jawab3.SetTextColor(RGB(255, 0, 0));

		CallSuaraSalah(); 

		m_nsalahCount++;
	}

	m_Jawab1.SetTextColor(RGB(0, 0, 0));
	m_Jawab2.SetTextColor(RGB(0, 0, 0));
	m_Jawab4.SetTextColor(RGB(0, 0, 0));	
}

void CPikabelajrInDlg::OnButtonJawab4() 
{
	if(m_nTutorIndex == 0)
		return;

	if(lstrcmpi(m_strBenarJawab, "D") == 0)
	{
		m_Jawab4.SetTextColor(RGB(0, 255, 0));

		m_pParent->CreateNoticeDlg(4);

		CallSuaraBenar();

		m_nBenarCount ++;

		Sleep(1000);

		//SetImageNext();

		int nSize = m_ArrayClientInfo.GetSize();
		if(m_nImgIndex == nSize)
		{
			//notice
			m_pParent->CloseNoticeDlg();

			SetUjianResultMessage();
		}
		else
			SetImageNext();
	}
	else
	{
		m_Jawab4.SetTextColor(RGB(255, 0, 0));

		CallSuaraSalah();

		m_nsalahCount++;
	}

	m_Jawab1.SetTextColor(RGB(0, 0, 0));
	m_Jawab2.SetTextColor(RGB(0, 0, 0));
	m_Jawab3.SetTextColor(RGB(0, 0, 0));	
}

void CPikabelajrInDlg::SetLinkJawab(int nJawab)
{
	if(nJawab == 1)
		OnButtonJawab1();	
	else if(nJawab == 2)
		OnButtonJawab2();	
	else if(nJawab == 3)
		OnButtonJawab3();	
	else if(nJawab == 4)
		OnButtonJawab4();	
}

void CPikabelajrInDlg::SetUjianResultMessage()
{	
	int nSumCount = m_nBenarCount + m_nsalahCount;
		
	float nSuccessPercent =  ((float)m_nBenarCount / (float)nSumCount) *100;
	float nSalahPercent =  ((float)m_nsalahCount / (float)nSumCount) *100;

	CString strPersent;
	strPersent.Format("Benar: %ld (%.1f%%)\r\nSalah: %ld (%.1f%%)", m_nBenarCount, nSuccessPercent, m_nsalahCount, nSalahPercent);
	//strPersent.Format("Benar:%.1f%% Salah:%.1f%%", nSuccessPercent, nSalahPercent);
	
	m_pParent->CreateResultViewDlg(m_nTutorIndex, m_nSuaraIndex, strPersent);		
}

void CPikabelajrInDlg::OnButtonZoom() 
{	
	m_pParent->CreatePreviewDlg(m_strImageBesar);
}
