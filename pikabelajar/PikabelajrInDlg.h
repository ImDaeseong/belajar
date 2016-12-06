#if !defined(AFX_PIKABELAJRINDLG_H__1F48CE13_39E0_4369_954C_978FB668ABD2__INCLUDED_)
#define AFX_PIKABELAJRINDLG_H__1F48CE13_39E0_4369_954C_978FB668ABD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PikabelajrInDlg.h : header file
//

typedef struct _tagUgianInfo
{
	int     m_nIndex;
	CString m_strImagekecil;
	CString m_strImageBesar;
    CString m_strTanya;
	CString m_strJawab1;
	CString m_strJawab2;
	CString	m_strJawab3;
	CString m_strJawab4;
	CString m_strBenarJawab;
	CString m_strHint;
}UGIAN_INFO, *LPUGIAN_INFO;

class CUgianInfo : public CObject
{
public:
	CUgianInfo()
	{
	}

	CUgianInfo(int nIndex, CString strTanya, CString strJawab1, CString strJawab2, CString strJawab3, CString strJawab4, CString strBenarJawab, CString strImagekecil, CString strImageBesar, CString strHint)
	{	
		m_nIndex = nIndex;		
    	m_strTanya = strTanya;
		m_strJawab1 = strJawab1;
		m_strJawab2 = strJawab2;
		m_strJawab3 = strJawab3;
		m_strJawab4 = strJawab4;
		m_strBenarJawab = strBenarJawab;
		m_strImagekecil = strImagekecil;
		m_strImageBesar = strImageBesar;
		m_strHint = strHint;
	}
	
	int     m_nIndex;	
    CString m_strTanya;
	CString m_strJawab1;
	CString m_strJawab2;
	CString	m_strJawab3;
	CString m_strJawab4;
	CString m_strBenarJawab;
	CString m_strImagekecil;
	CString m_strImageBesar;
	CString m_strHint;
};

/////////////////////////////////////////////////////////////////////////////
// CPikabelajrInDlg dialog
class CPikabelajarDlg;
class CPikabelajrInDlg : public CDialog
{
protected:
//	Image	
	CGdiPlusBitmapResource * m_pbgImage;
	CPikabelajarDlg * m_pParent;


	void RemoveClientInfo();
	void AddClientInfo(int nIndex, CString strTanya, CString strJawab1, CString strJawab2, CString strJawab3, CString strJawab4, CString strBenarJawab,  CString strImagekecil, CString strImageBesar, CString strHint);
    void GetClientInfo(int nIndex, CString& strTanya, CString& strJawab1, CString& strJawab2, CString& strJawab3, CString& strJawab4, CString& strBenarJawab, CString& strImagekecil, CString& strImageBesar, CString& strHint);
	CString GetElementInListFile(int nOpt, CString strData);
	CObArray m_ArrayClientInfo;


// Construction
public:
	void InitCtrls();
	void ChangeCtrls();
	void InitVariables();
	void SetParent(CPikabelajarDlg * pParent);
	void DrawSkin(CDC * pDC);
	void LoadImage();
	CPikabelajrInDlg(CWnd* pParent = NULL);   // standard constructor

public:
	void SetUjianResultMessage();
	void SetLinkJawab(int nJawab);
	void SetImageNext();
	void SetImagePrev();

	void SetTutorIndex(int nTutorIndex);
	void SetSuaraIndex(int nSuaraIndex);

	void CallSuaraBenar();
	void CallSuaraSalah();

// Dialog Data
	//{{AFX_DATA(CPikabelajrInDlg)
	enum { IDD = IDD_PIKABELAJARIN_DIALOG };
	CScrollTextStatic m_RollingBanner;	
	//CPhotoPictureStatic m_RollingBannerImg;
	CPreViewImage m_PreviewImg;
	CLeftPictureStatic  m_ctrlPictureImg;
	CPictureStatic m_ctrlSpashImg;
	CLabel m_Tanya;
	CLabel m_Jawab1;
	CLabel m_Jawab2;
	CLabel m_Jawab3;
	CLabel m_Jawab4;	
	CGdipButtonex m_btnTanya;
	CGdipButton m_btnJawab1;
	CGdipButton	m_btnJawab2;
	CGdipButton	m_btnJawab3;
	CGdipButton	m_btnJawab4;
	CGdipButton m_btnZoom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPikabelajrInDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPikabelajrInDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonJawab1();
	afx_msg void OnButtonJawab2();
	afx_msg void OnButtonJawab3();
	afx_msg void OnButtonJawab4();
	afx_msg void OnButtonZoom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nImgIndex;
	int m_nTutorIndex;
	BOOL m_bMulaiClick;
	int m_nSuaraIndex;

	CString m_strTanya;
	CString m_strJawab1;
	CString m_strJawab2;
	CString m_strJawab3;
	CString m_strJawab4;
	CString m_strBenarJawab;
	CString m_strImagekecil;
	CString m_strImageBesar;
	CString m_strHint;

	int m_nPhotoIndex;


	int m_nBenarCount;
	int m_nsalahCount;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIKABELAJRINDLG_H__1F48CE13_39E0_4369_954C_978FB668ABD2__INCLUDED_)
