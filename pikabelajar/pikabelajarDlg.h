// pikabelajarDlg.h : header file
//

#if !defined(AFX_PIKABELAJARDLG_H__AFBA5EEE_509F_400E_9822_B9375A36C70C__INCLUDED_)
#define AFX_PIKABELAJARDLG_H__AFBA5EEE_509F_400E_9822_B9375A36C70C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CPikabelajarDlg dialog
class CMusicPlayLayerDlg;
class ResultDlg;
class NoticeDlg;
class HintviewDlg;
class PreviewDlg; 
class CPikabelajrInDlg;
class CPikabelajarDlg : public CDialog
{
protected:
//	Image	
	CGdiPlusBitmapResource * m_pbgImage;
	CPikabelajrInDlg * m_pPanel;
	PreviewDlg * m_pPreview;
	HintviewDlg * m_pHintview;
	NoticeDlg * m_pNotice;
	ResultDlg * m_pResultView;
	CMusicPlayLayerDlg * m_pMusicLayer;

	BOOL m_bDragShowFlag;
	BOOL m_bDrag;

	int m_nTutorIndex;
    
	int m_nSuaraIndex;

	BOOL m_bMusicBuka;

	int m_nHapusMessage;

// Construction
public:
	void SetNextUgian(int nTutorIndex, BOOL bUlang = TRUE);
	void SetLinkJawab(int nJawab);
	
	void ReDrawButton(Graphics &gps);
	void SetInfoText(Graphics &gps);
	void InitButtons();
	void InitVariables();
	void DrawSkin();
	void LoadImage();
	CPikabelajarDlg(CWnd* pParent = NULL);	// standard constructor

	
	void CreatePanelDlg();
	void ClosePanelDlg();
	void SetChildPos();
	
	void CreatePreviewDlg(CString strResource);
	void ClosePreviewDlg();

	void CreateHintviewDlg(CString strResource);
	void CloseHintviewDlg();

	void CreateNoticeDlg(int nJawaban);
	void CloseNoticeDlg(); 

	void CreateResultViewDlg(int nTitleIndex, int nSuaraIndex, CString strResult);
	void CloseResultViewDlg(); 

	void CreateMusicDlg();
	void CloseMusicDlg(); 



// Dialog Data
	//{{AFX_DATA(CPikabelajarDlg)
	enum { IDD = IDD_PIKABELAJAR_DIALOG };
	CSkinButton	m_btnClose;
	CSkinButton	m_btnLeft;
	CSkinButton	m_btnRight;
	CSkinButton	m_btnSetting1;
	CSkinButton	m_btnSetting2;
	CSkinButton	m_btnSetting3;
	CSkinButton	m_btnSetting4;
	CSkinButton	m_btnSetting5;
	CSkinButton	m_btnYm1;
	CSkinButton	m_btnYm2;
	CSkinButton	m_btnYoutube;
	CSkinButton	m_btnFaceBook;
	CSkinButton	m_btnMusic;
	CSkinButton	m_btnSuaralaki;
	CSkinButton	m_btnSuaraputri;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPikabelajarDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CPikabelajarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonClose();
	afx_msg void OnButtonLeft();
	afx_msg void OnButtonRigth();	
	afx_msg void OnButtonSetting1();
	afx_msg void OnButtonSetting2();
	afx_msg void OnButtonSetting3();
	afx_msg void OnButtonSetting4();
	afx_msg void OnButtonSetting5();
	afx_msg void OnButtonYoutube();
	afx_msg void OnButtonFacebook();
	afx_msg void OnButtonYm1();
	afx_msg void OnButtonYm2();
	afx_msg void OnButtonMusic();
	afx_msg void OnButtonSuaralaki();
	afx_msg void OnButtonSuaraputri();
	//}}AFX_MSG
	afx_msg LRESULT OnDisplayChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPreviewImgClose(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHapusMessageSend(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIKABELAJARDLG_H__AFBA5EEE_509F_400E_9822_B9375A36C70C__INCLUDED_)
