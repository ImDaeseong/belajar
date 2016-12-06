#pragma once

class CPhotoPictureStatic : public CStatic
{
public:
	void GetPictureRect(CRect& rPos);
	BOOL LoadImage(CString strImagePath);
	BOOL LoadImage(UINT ResourceName, CString ResourceType);
	void ReleaseFreeImage();
	void StaticRoundSize(int nX, int nY);
	void OnInvalidate();
	CPhotoPictureStatic& SetPictureStaticClick(BOOL bClick = FALSE);
	void SetPictureStaticCursor(BOOL bCursor = FALSE);

	bool SleepEx( DWORD dwMilliseconds );
	bool MagicFunstretchUp( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep );

	void SetButtonClick(BOOL bClick);
public:
	CPhotoPictureStatic();
	virtual ~CPhotoPictureStatic();
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void PreSubclassWindow();

	DECLARE_MESSAGE_MAP()
private:
	CResourcBitmapgif m_picImg;
	CRect    m_rPicBg;
	CBitmap  m_bmpMain;
	HBITMAP  m_hMainBmp;
	int      m_nX;
	int      m_nY;
	BOOL     m_bClick;
	BOOL     m_bCursor;
	HCURSOR	 m_hCursor;
	BOOL     m_bButtonClick;
	int m_nBx;
   	int m_nBy;
};
