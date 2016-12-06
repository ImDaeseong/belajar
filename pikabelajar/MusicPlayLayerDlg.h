#if !defined(AFX_MUSICPLAYLAYERDLG_H__60EF50F3_5CF8_49BA_9ADB_2108F96C7660__INCLUDED_)
#define AFX_MUSICPLAYLAYERDLG_H__60EF50F3_5CF8_49BA_9ADB_2108F96C7660__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MusicPlayLayerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMusicPlayLayerDlg dialog
class CPikabelajarDlg;
class CMusicPlay;
class CMusicPlayLayerDlg : public CDialog
{
protected:
	CPikabelajarDlg * m_pParent;
	CMusicPlay * m_pMusic;
	
	void CreateSubDlg();
	void CloseSubDlg();
	void SetChildPos();

// Construction
public:
	CMusicPlayLayerDlg(CWnd* pParent = NULL);   // standard constructor

	void SetParent(CPikabelajarDlg * pParent);
	void CloseMusicAll();

// Dialog Data
	//{{AFX_DATA(CMusicPlayLayerDlg)
	enum { IDD = IDD_DIALOG_PLAYLAYER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMusicPlayLayerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CGdiPlusBitmapResource * m_pbgImage;
	
	void InitVariables();
	void DrawSkin();
	void LoadImage();

	// Generated message map functions
	//{{AFX_MSG(CMusicPlayLayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnDisplayChange(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MUSICPLAYLAYERDLG_H__60EF50F3_5CF8_49BA_9ADB_2108F96C7660__INCLUDED_)
