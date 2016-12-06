#if !defined(AFX_PREVIEWDLG_H__3A6D3E2F_F740_40B5_877D_4C44FCCF6471__INCLUDED_)
#define AFX_PREVIEWDLG_H__3A6D3E2F_F740_40B5_877D_4C44FCCF6471__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreviewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PreviewDlg dialog
class CPikabelajarDlg;
class PreviewDlg : public CDialog
{
// Construction
public:
	PreviewDlg(CWnd* pParent = NULL);   // standard constructor

	void SetParent(CPikabelajarDlg * pParent);
	void DrawSkin(CDC * pDC);
	void LoadImage();
    void SetImgName(CString strResource);


// Dialog Data
	//{{AFX_DATA(PreviewDlg)
	enum { IDD = IDD_DIALOG_PREVIEW };
	CPictureStatic	m_staticimg;
	CTransparentImage m_CloseImage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PreviewDlg)
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
	int m_nX, m_nY;

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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEWDLG_H__3A6D3E2F_F740_40B5_877D_4C44FCCF6471__INCLUDED_)
