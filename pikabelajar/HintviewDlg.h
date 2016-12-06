#if !defined(AFX_HINTVIEWDLG_H__A9991EB4_E43F_4C83_B2F8_FBDBD9579D22__INCLUDED_)
#define AFX_HINTVIEWDLG_H__A9991EB4_E43F_4C83_B2F8_FBDBD9579D22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HintviewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// HintviewDlg dialog
class CPikabelajarDlg;
class HintviewDlg : public CDialog
{
// Construction
public:
	HintviewDlg(CWnd* pParent = NULL);   // standard constructor

	void SetParent(CPikabelajarDlg * pParent);
	void DrawSkin(CDC * pDC);
	void LoadImage();
    void SetImgName(CString strResource);

// Dialog Data
	//{{AFX_DATA(HintviewDlg)
	enum { IDD = IDD_DIALOG_HINTVIEW };
	CPreViewImage	m_HintImg;
	CTransparentImage m_CloseImage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HintviewDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CGdiPlusBitmapResource * m_pbgImage;
	CPikabelajarDlg * m_pParent;


	CString m_strResource;
	int m_nCloseCount;

	void CheckCurPos();
	HWND GetCurPosHandle(POINT point);
	BOOL m_bMouseOn;


	// Generated message map functions
	//{{AFX_MSG(PreviewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HINTVIEWDLG_H__A9991EB4_E43F_4C83_B2F8_FBDBD9579D22__INCLUDED_)
