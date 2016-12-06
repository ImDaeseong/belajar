#if !defined(AFX_MUSICPLAY_H__ABC6E732_4D02_4536_97D0_3555197E859D__INCLUDED_)
#define AFX_MUSICPLAY_H__ABC6E732_4D02_4536_97D0_3555197E859D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MusicPlay.h : header file
//

#include "./play/AudioPlayer.h"
#include "./play/MP3Info.h"

#include "./Banner/BannerStatic.h"
#include "./Banner/ColorString.h"
#include "./Banner/MultiColorStatic.h"
//#include "./zsliderctrl/ZipSliderCtl.h"

/////////////////////////////////////////////////////////////////////////////
// CMusicPlay dialog
class CPikabelajarDlg;
class CMusicPlayLayerDlg;
class CMusicPlay : public CDialog
{
// Construction
public:
	CMusicPlay(CWnd* pParent = NULL);   // standard constructor

	void SetParent(CMusicPlayLayerDlg* pLayerDlg, CPikabelajarDlg * pParent);
	
	void InitVariables();
	void DrawSkin(CDC * pDC);
	void LoadImage();

// Dialog Data
	//{{AFX_DATA(CMusicPlay)
	enum { IDD = IDD_DIALOG_PLAY };
	//CSliderCtrl m_SVolume;//CZipSliderCtl m_SVolume;
	CSliderCtrl	m_sliderRunning;
	CBannerStatic	m_banner;
	CGdipButton m_btnPlay;
	CGdipButton m_btnLeft;
	CGdipButton m_btnRight;
	CGdipButton m_btnPlus;
	CGdipButton m_btnMin;
	CGdipButton m_btnFolder;
	CLabel m_Status;
	CLabel m_SearchFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusicPlay)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CGdiPlusBitmapResource * m_pbgImage;
	CPikabelajarDlg * m_pParent;
	CMusicPlayLayerDlg * m_pLayerDlg;


	CAudioPlayer m_Player;

	CString	m_strTimer;
	CString	m_strTitle;
	CString	m_strArtist;
	CString	m_strAlbum;
	CString m_strCurrentPath;

	int m_nlength;
	int m_nVolume;

	int m_nCurrentPlay;
	int m_nMaxCount;

	CStringArray m_FileList;

	BOOL m_bClickPlay;

	int m_nVolumnValue;

	CString m_strSelectPath;


	void Play();
	void Left();
	void Right();
	void Stop();
	void Pause();


	CString GetFileInfo();
    CColorString UpdateStringAppearance(CString strname);
	void SetFileInfo(CString strPath);


	static UINT FindMp3ThreadFunc(LPVOID pParam);
	void ThreadCaryMp3Files();

	// Generated message map functions
	//{{AFX_MSG(CMusicPlay)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnCustomdrawVolume(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnButtonPhilihfolder();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonPlayleft();
	afx_msg void OnButtonPlaynext();
	afx_msg void OnButtonPlaystop();
	afx_msg void OnButtonSuaraplus();
	afx_msg void OnButtonSuaramin();
	//}}AFX_MSG
	afx_msg LRESULT OnFindFilesClose(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICPLAY_H__ABC6E732_4D02_4536_97D0_3555197E859D__INCLUDED_)
