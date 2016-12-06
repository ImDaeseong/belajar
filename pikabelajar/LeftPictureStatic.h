#pragma once

class CLeftPictureStatic : public CStatic
{
public:
	void GetPictureRect(CRect& rPos);
	BOOL LoadImage(CString strImagePath);
	BOOL LoadImage(UINT ResourceName, CString ResourceType);
	void ReleaseFreeImage();
	void StaticRoundSize(int nX, int nY);
	void OnInvalidate();
	CLeftPictureStatic& SetPictureStaticClick(BOOL bClick = FALSE);
	void SetPictureStaticCursor(BOOL bCursor = FALSE);

	bool SleepEx( DWORD dwMilliseconds );
	bool MagicFunLeft( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep );
	bool MagicFunRight( HDC hSrcDC , int x , int y , HDC hDestDC , int xd , int yd , int width , int height , int nDelay, int nStep );

	void SetButtonClick(BOOL bClick);
	void SetPictureMoveRight(BOOL bRight = FALSE);

	void SetPhotoResize(int nResizeWidth, int nResizeHeight);
	HBITMAP getResizeBitmap(HBITMAP hBitmap, const unsigned int aW, const unsigned int aH);

public:
	CLeftPictureStatic();
	virtual ~CLeftPictureStatic();
protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void PreSubclassWindow();
	DECLARE_MESSAGE_MAP()
private:
	CResourcBitmap m_Picture;
	CRect    m_rPicBg;
	CBitmap  m_bmpMain;
	HBITMAP  m_hMainBmp;
	int      m_nX;
	int      m_nY;
	BOOL     m_bClick;
	BOOL     m_bCursor;
	HCURSOR	 m_hCursor;
	BOOL     m_bButtonClick;
	BOOL     m_bMoveRight;
	int      m_nResizeWidth;
	int      m_nResizeHeight; 
};
