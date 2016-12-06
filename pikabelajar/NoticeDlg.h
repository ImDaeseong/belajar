#if !defined(AFX_NOTICEDLG_H__F117FB60_A51E_4F5F_9185_0EB7F13970DC__INCLUDED_)
#define AFX_NOTICEDLG_H__F117FB60_A51E_4F5F_9185_0EB7F13970DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NoticeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NoticeDlg dialog
class CPikabelajarDlg;
class NoticeDlg : public CDialog
{
protected:
	CPikabelajarDlg * m_pParent;
	
	CGdiPlusBitmapResource * m_pbgImage;

	int  m_nJawaban;
	
// Construction
public:
	NoticeDlg(CWnd* pParent = NULL);   // standard constructor

	void SetParent(CPikabelajarDlg * pParent);
	void SetJawaban(int nJawaban);

	void InitVariables();
	void DrawSkin();
	void LoadImage();


// Dialog Data
	//{{AFX_DATA(NoticeDlg)
	enum { IDD = IDD_DIALOG_NOTICE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NoticeDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(NoticeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTICEDLG_H__F117FB60_A51E_4F5F_9185_0EB7F13970DC__INCLUDED_)
