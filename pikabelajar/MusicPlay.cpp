// MusicPlay.cpp : implementation file
//

#include "stdafx.h"
#include "pikabelajar.h"
#include "MusicPlay.h"
#include "pikabelajarDlg.h"
#include "MusicPlayLayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_FINDFILES_CLOSE	WM_USER + 4000

/////////////////////////////////////////////////////////////////////////////
// CMusicPlay dialog


CMusicPlay::CMusicPlay(CWnd* pParent /*=NULL*/)
	: CDialog(CMusicPlay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMusicPlay)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	InitVariables();
}

void CMusicPlay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMusicPlay)
	//DDX_Control(pDX, IDC_VOLUME, m_SVolume);
	DDX_Control(pDX, IDC_SLIDER1, m_sliderRunning);
	DDX_Control(pDX, IDC_STATIC_BANNER, m_banner);
	DDX_Control(pDX, IDC_BUTTON_PLAY, m_btnPlay);
	DDX_Control(pDX, IDC_BUTTON_PLAYLEFT, m_btnLeft);
	DDX_Control(pDX, IDC_BUTTON_PLAYNEXT, m_btnRight);
	DDX_Control(pDX, IDC_BUTTON_SUARAPLUS, m_btnPlus);
	DDX_Control(pDX, IDC_BUTTON_SUARAMIN,  m_btnMin);
	DDX_Control(pDX, IDC_BUTTON_PHILIHFOLDER, m_btnFolder);
	DDX_Control(pDX, IDC_STATIC_TIME, m_Status);
	DDX_Control(pDX, IDC_STATIC_SEARCH, m_SearchFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMusicPlay, CDialog)
	//{{AFX_MSG_MAP(CMusicPlay)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_PHILIHFOLDER, OnButtonPhilihfolder)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_PLAYLEFT, OnButtonPlayleft)
	ON_BN_CLICKED(IDC_BUTTON_PLAYNEXT, OnButtonPlaynext)
	ON_BN_CLICKED(IDC_BUTTON_PLAYSTOP, OnButtonPlaystop)
	ON_BN_CLICKED(IDC_BUTTON_SUARAPLUS, OnButtonSuaraplus)
	ON_BN_CLICKED(IDC_BUTTON_SUARAMIN, OnButtonSuaramin)
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, CMusicPlay::OnCustomdrawSlider1)
	//ON_NOTIFY(NM_CUSTOMDRAW, IDC_VOLUME, CMusicPlay::OnCustomdrawVolume)
	ON_MESSAGE(WM_FINDFILES_CLOSE, OnFindFilesClose)
END_MESSAGE_MAP()

void CMusicPlay::OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
}
/*
void CMusicPlay::OnCustomdrawVolume(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	m_Player.SetVolume(m_SVolume.GetPos());

	*pResult = 0;
}
*/
void CMusicPlay::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if ((CSliderCtrl*)pScrollBar == &m_sliderRunning)
	{
		if(nSBCode == SB_PAGELEFT || nSBCode == SB_PAGERIGHT || SB_THUMBTRACK == nSBCode)
		{
			m_Player.SetPosition(m_sliderRunning.GetPos() * m_Player.GetRunningTime() / 100);
		}
	}
	/*
	else if ((CSliderCtrl*)pScrollBar == &m_SVolume)
	{
		if(nSBCode == SB_PAGELEFT || nSBCode == SB_PAGERIGHT || SB_THUMBTRACK == nSBCode)
		{
			m_Player.SetVolume(m_SVolume.GetPos());
		}		
	}
	*/
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

CColorString CMusicPlay::UpdateStringAppearance(CString strname)
{
   UpdateData(TRUE);
   
   DWORD dwAddStyle = RGB(110, 110, 110);//RGB(231, 231, 231);

   CString m_strAddString = strname;

   CColorString strAddAppearance(m_strAddString, dwAddStyle);
   return (strAddAppearance);
}

CString CMusicPlay::GetFileInfo()
{
	CMP3Info mp3;

	CString strFileInfo;
	if (mp3.Open(m_strCurrentPath))
	{
		m_strTitle = mp3.GetTitle();
		m_strArtist = mp3.GetArtist();
		m_strAlbum = mp3.GetAlbum();
	}
	else
	{
		m_strTitle = "";
		m_strArtist = "";
		m_strAlbum = "";
	}

	m_strTitle.TrimLeft();
	m_strTitle.TrimRight();
	m_strArtist.TrimLeft();
	m_strArtist.TrimRight();
	m_strAlbum.TrimLeft();
	m_strAlbum.TrimRight();

	strFileInfo = "";
	strFileInfo  = " #Title-" ;
	strFileInfo += m_strTitle ;
	strFileInfo += " #Artist-";
	strFileInfo += m_strArtist;
	strFileInfo += " #Album-";
	strFileInfo += m_strAlbum;

    return  strFileInfo;
}

void CMusicPlay::Play()
{
	if(m_nMaxCount == 0)
		return;

	m_Player.Open(m_strCurrentPath);

	KillTimer(1);
	SetTimer(1, 1000, NULL);

	m_Player.Play();

	m_nlength = m_Player.GetPosition();

	m_sliderRunning.SetPos(0);

	m_Player.SetVolume(m_nVolumnValue);//m_Player.SetVolume(m_SVolume.GetPos());

	m_bClickPlay = TRUE;

	UpdateData(TRUE);
	
	CString strInfo = GetFileInfo();

	int nIndex = m_strCurrentPath.ReverseFind(_T('\\'));
	CString m_filename = "#";
	m_filename += m_strCurrentPath.Mid(nIndex + 1);
	m_filename += " ";
	m_filename += strInfo ;

	m_banner.RemoveAllStrings();
	m_banner.AddString(UpdateStringAppearance(m_filename));
}

void CMusicPlay::Left()
{
	if(m_nMaxCount == 0)
		return;

    m_nCurrentPlay --;

	if(m_nCurrentPlay < 0)
		m_nCurrentPlay = m_nMaxCount - 1;


	m_strCurrentPath = m_FileList.GetAt(m_nCurrentPlay);	
	
	
	Stop();
	Play();	
}

void CMusicPlay::Right()
{
	if(m_nMaxCount == 0)
		return;

    m_nCurrentPlay ++;

	if(m_nCurrentPlay > m_nMaxCount-1)
		m_nCurrentPlay = 0;

	m_strCurrentPath = m_FileList.GetAt(m_nCurrentPlay);
	
	Stop();
	Play();
}

void CMusicPlay::Stop()
{
	if(m_nMaxCount == 0)
		return;

	m_Player.Stop();
		
	m_sliderRunning.SetPos(0);

	m_bClickPlay = FALSE;

	SetDlgItemText(IDC_STATIC_TIME, "00:00\r\n00:00");

	KillTimer(1);
}

void CMusicPlay::Pause() 
{
	m_Player.Pause();

	m_bClickPlay = FALSE;
}

void CMusicPlay::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == 1)
	{
		int nCurTime = int( m_Player.GetPosition() / 1000 );
		int nLength = int( m_Player.GetRunningTime() / 1000 );
			
		if( nLength > 0 )
		{
			int nCur2 = nCurTime%60;
			CString szCur2;
			if( nCur2 < 10 )
				szCur2.Format("0%d", nCur2);
			else
				szCur2.Format("%d", nCur2);
				
			int nLen2 = nLength%60;
			CString szLen2;
			if( nLen2 < 10 )
				szLen2.Format("0%d", nLen2);
			else
				szLen2.Format("%d", nLen2);
				
			m_strTimer.Format("%2d:%s\r\n%2d:%s", nCurTime/60, szCur2, nLength/60, szLen2);		
			int nPer = nCurTime*100/nLength;		
				
			m_sliderRunning.SetPos(nPer);
			SetDlgItemText(IDC_STATIC_TIME, m_strTimer);

			UpdateData(FALSE);
				
			if( nPer == 100 )
			{
				KillTimer(1);
				Right();
			}		
		}
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CMusicPlay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadImage();

	m_nVolumnValue = 100;
	/*
	m_SVolume.SetSkin(IDB_VOL_FILL,IDB_VOL_KNOB);
	m_SVolume.SetRange(0,1000);
	m_SVolume.SetPos(1000);
	*/

	m_sliderRunning.ShowWindow(SW_HIDE);


	m_banner.SetBackColor(RGB(243,243,243));//RGB(76,85,118));
	m_banner.SetScrollSpeed(200);  
	m_banner.AddString(UpdateStringAppearance("PIKA Support (021) 5292 1927.^^"));

    //time
	//m_Status.MoveWindow(-35, -385, 780, 18);
	m_Status.SetFontName("Arial");
	m_Status.SetFontSize(12);
	m_Status.SetFontBold(TRUE);
	m_Status.SetBkColor(RGB(243,243,243));
	m_Status.SetText("");
	m_Status.SetTextColor(RGB(0, 0, 0));
	m_Status.SetLink(FALSE);

    //cari mp3
	m_SearchFile.SetFontName("Arial");
	m_SearchFile.SetFontSize(12);
	m_SearchFile.SetFontBold(TRUE);
	m_SearchFile.SetBkColor(RGB(243,243,243));
	m_SearchFile.SetText("");
	m_SearchFile.SetTextColor(RGB(0, 0, 0));
	m_SearchFile.SetLink(FALSE);


	m_btnPlay.LoadStdImage(IDR_PNG_PLAY, "PNG", AfxGetApp()->m_hInstance, 72, 76);	
	
	m_btnLeft.LoadStdImage(IDR_PNG_MUSIC_LEFT, "PNG", AfxGetApp()->m_hInstance, 16, 76);	
	m_btnRight.LoadStdImage(IDR_PNG_MUSIC_RIGHT, "PNG", AfxGetApp()->m_hInstance, 127, 76);	

	m_btnPlus.LoadStdImage(IDR_PNG_SUARAPLUS, "PNG", AfxGetApp()->m_hInstance, 72, 21);
	m_btnMin.LoadStdImage(IDR_PNG_SUARAMIN, "PNG", AfxGetApp()->m_hInstance, 72, 131);

	m_btnFolder.LoadStdImage(IDR_PNG_ADDFOLDER, "PNG", AfxGetApp()->m_hInstance, 56, 186);


	return TRUE; 
}

HBRUSH CMusicPlay::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr;
    if (pWnd->GetDlgCtrlID() == IDC_SLIDER1 )
	{
        hbr = CreateSolidBrush(RGB(243,243,243));
        pDC->SetBkColor(RGB(243,243,243));
        pDC->SetTextColor(RGB(0,0,0));
    }
    else
        hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

void CMusicPlay::OnPaint() 
{
	CPaintDC dc(this);
	DrawSkin(&dc);
}

void CMusicPlay::OnDestroy() 
{
	CDialog::OnDestroy();

	m_FileList.RemoveAll();

	Stop();
	
	SAFE_DELETE(m_pbgImage);
}

BOOL CMusicPlay::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMusicPlay::LoadImage()
{
	if (!m_pbgImage)
	{
		m_pbgImage = new CGdiPlusBitmapResource;

		if (!m_pbgImage->Load(IDR_PNG_SKININ, "PNG", AfxGetApp()->m_hInstance))
		{
			return;
		}
	}

	int x = m_pbgImage->m_pBitmap->GetWidth();
	int y = m_pbgImage->m_pBitmap->GetHeight();

	MoveWindow(0, 0, x, y);		
}

void CMusicPlay::DrawSkin(CDC *pDC)
{
	int x = m_pbgImage->m_pBitmap->GetWidth();
	int y = m_pbgImage->m_pBitmap->GetHeight();

	Graphics gps(pDC->GetSafeHdc());
	gps.DrawImage(m_pbgImage->m_pBitmap, Rect(0, 0, x, y) , 0, 0, x, y, UnitPixel);	

	m_btnPlay.SetBkGnd(pDC);
	m_btnLeft.SetBkGnd(pDC);
	m_btnRight.SetBkGnd(pDC);
	m_btnPlus.SetBkGnd(pDC);
	m_btnMin.SetBkGnd(pDC);
	m_btnFolder.SetBkGnd(pDC);
}

void CMusicPlay::InitVariables()
{
	m_pbgImage = NULL;

	m_strTimer = "";
	m_strTitle = "";
	m_strArtist = "";
	m_strAlbum = "";
	m_strCurrentPath = "";

	m_nlength = 0;
	m_nVolume = 0;

	m_nCurrentPlay = 0;
	m_nMaxCount = 0;

	m_bClickPlay = FALSE;

	m_nVolumnValue = 0;
	m_strSelectPath = "";
}

void CMusicPlay::SetParent(CMusicPlayLayerDlg* pLayerDlg, CPikabelajarDlg * pParent)
{
	m_pLayerDlg = pLayerDlg;

	m_pParent = pParent;
}

void CMusicPlay::OnButtonPhilihfolder() 
{
	LPMALLOC	pMalloc;

    if (::SHGetMalloc(&pMalloc) == NOERROR)
    {
        BROWSEINFO bi;
        char pszBuffer[MAX_PATH];
        LPITEMIDLIST pidl;
		
        bi.hwndOwner = GetSafeHwnd();
        bi.pidlRoot = NULL;//pidl;
        bi.pszDisplayName = pszBuffer;
        bi.lpszTitle = _T("pilih Mp3");
        bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
        bi.lpfn = NULL;
        bi.lParam = 0;

        if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
        {
            if (::SHGetPathFromIDList(pidl, pszBuffer))
            { 
				m_strSelectPath = pszBuffer;
            }

            pMalloc->Free(pidl);
        }
        pMalloc->Release();
    }

	if(m_strSelectPath== "")
		return;

	Stop();	

	m_SearchFile.SetText("Sedang cari mp3");

	m_btnFolder.EnableWindow(FALSE);

	AfxBeginThread(FindMp3ThreadFunc, this);

	/*
	SetFileInfo(m_strSelectPath);
	
	m_strCurrentPath = m_FileList.GetAt(0);
	m_nMaxCount = m_FileList.GetSize();

	if(m_nMaxCount > 0)
		m_sliderRunning.ShowWindow(SW_SHOW);

	m_nCurrentPlay = 0;
	Play();	
	*/
}

void CMusicPlay::SetFileInfo(CString strPath)
{
   CFileFind finder;

   CString strWildcard = strPath;
   strWildcard += _T("\\*.*");

   CString strFullPath;
   
   BOOL bWorking = finder.FindFile(strWildcard);
   while (bWorking)
   {
      bWorking = finder.FindNextFile();
   
      if (finder.IsDots())
         continue;

      if (finder.IsDirectory())
      {
		  strFullPath = finder.GetFilePath();
          SetFileInfo(strFullPath);
      }
	  else
	  {
		  CString strFullPath = finder.GetFilePath();
		  CString strFileName = finder.GetFileName();
		  CString strExtention = strFileName.Mid(strFileName.ReverseFind('.')+1); 

		  if(lstrcmpi(strExtention, "mp3") != 0 )
		  	  continue;
		 
		  m_FileList.Add(strFullPath);		 
	  }
   }

   finder.Close();
}

void CMusicPlay::OnButtonPlay() 
{
	if( m_bClickPlay == FALSE)
	{
		Play();
	}
	else
	{
		Pause();	
	}
}

void CMusicPlay::OnButtonPlayleft() 
{
	Left();	
}

void CMusicPlay::OnButtonPlaynext() 
{
	Right();	
}

void CMusicPlay::OnButtonPlaystop() 
{
	Stop();	
}

void CMusicPlay::OnButtonSuaraplus() 
{
	int nValue =0;
	if( m_nVolumnValue < 100 )
	{
		 nValue = m_nVolumnValue + 10;	
		 m_Player.SetVolume(nValue);
         m_nVolumnValue = nValue;
	}	
 }

void CMusicPlay::OnButtonSuaramin() 
{
	int nValue = 0;
	if( m_nVolumnValue > 0 )
	{
		 nValue = m_nVolumnValue - 10;	
		 m_Player.SetVolume(nValue);
         m_nVolumnValue = nValue;
	}	
}

UINT CMusicPlay::FindMp3ThreadFunc(LPVOID pParam)
{
	CMusicPlay * pManager = (CMusicPlay *)pParam;

	pManager->ThreadCaryMp3Files();

	pManager->PostMessage(WM_FINDFILES_CLOSE, 0, 0);

	return 0;  
}

void CMusicPlay::ThreadCaryMp3Files()
{
	SetFileInfo(m_strSelectPath);
}

LRESULT CMusicPlay::OnFindFilesClose(WPARAM wParam, LPARAM lParam)
{
	m_strCurrentPath = m_FileList.GetAt(0);
	m_nMaxCount = m_FileList.GetSize();

	if(m_nMaxCount > 0)
		m_sliderRunning.ShowWindow(SW_SHOW);

	m_nCurrentPlay = 0;
	Play();	

	m_btnFolder.EnableWindow(TRUE);

	m_SearchFile.SetText("");

	return 0;
}