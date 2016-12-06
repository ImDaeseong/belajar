#if !defined(AFX_RESULTDLG_H__6EA6B45B_7D7F_449B_8671_C93463009FFB__INCLUDED_)
#define AFX_RESULTDLG_H__6EA6B45B_7D7F_449B_8671_C93463009FFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ResultDlg dialog
class CPikabelajarDlg;
class ResultDlg : public CDialog
{
protected:
	CPikabelajarDlg * m_pParent;
	CString m_strResult;
	int     m_nTitleIndex;
	int     m_nSuaraIndex; 
	
	CGdiPlusBitmapResource * m_pbgImage;

// Construction
public:
	ResultDlg(CWnd* pParent = NULL);   // standard constructor

	void SetParent(CPikabelajarDlg * pParent);
	void SetResultMessage(int nTitleIndex, int nSuaraIndex, CString strResult);

	void InitVariables();
	void DrawSkin();
	void LoadImage();

	void ReDrawButton(Graphics &gps);
	void SetInfoText(Graphics &gps);
	void InitButtons();



// Dialog Data
	//{{AFX_DATA(ResultDlg)
	enum { IDD = IDD_DIALOG_RESULT };
	//CTransparentStatic	m_staticText;
	//CTransparentStatic	m_staticText1;
	//CTransparentStatic	m_staticText2;
	CSkinButton	m_btnUlang;
	CSkinButton	m_btnLanjuk;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ResultDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_nCloseCount;

	// Generated message map functions
	//{{AFX_MSG(ResultDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonUlang();
	afx_msg void OnButtonLangjut();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTDLG_H__6EA6B45B_7D7F_449B_8671_C93463009FFB__INCLUDED_)
