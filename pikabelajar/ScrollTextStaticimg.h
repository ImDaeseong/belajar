#pragma once

class CScrollTextStaticimg : public CStatic
{
	DECLARE_DYNAMIC(CScrollTextStaticimg)

public:
	CScrollTextStaticimg();
	virtual ~CScrollTextStaticimg();

public:
	void SetBackGroundColor(COLORREF clrBackGround);
   	void SetTextColor(COLORREF clrText);
   	void SetFontInfo(const CString& strFontName, int nSize, int nWeight);
   	void SetInitRolling();
	void SetTitleImage(CString strImagePath);
	BOOL SetTitleImage(UINT ResourceName, CString ResourceType);	
	void ReleaseFreeImage();
	
protected:
    virtual void RecalcLayout(CDC* pDC);
	virtual void FillBackground(CDC* pDC);
	virtual int  DrawTitleImage(CDC* pDC, int nOffset, BOOL bDraw = TRUE);
	virtual int  DrawScrollText(CDC* pDC, int nOffset, BOOL bDraw = TRUE);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void PreSubclassWindow();
DECLARE_MESSAGE_MAP()

private:
   static const int   nMargin;
   
   enum { SCROLLING, PAUSED } m_eState;

   COLORREF m_clrBackground;
   COLORREF m_clrText;
   CFont    m_FontText;
   CFont    m_FontTitle;
   CString  m_strText;
   CString  m_strUrl;

   CBitmap  m_bmpBackBuffer;
   CSize    m_ClientSize;
   int      m_nTextHeight;
   int      m_nScrollOffset;

   CString  GetThemeString(int nIndex);
   CString  GetThemeUrl(int nIndex);
   int      GetThemeCount();
   int      ClickAdvTab();
   int      m_nThemeCount;
   int      m_nIndex; 

   CResourcBitmapgif m_picImg;
   CBitmap        m_bmpMain;
   HBITMAP        m_hMainBmp;
   int m_nBx;
   int m_nBy;
   CRect m_rPicBg;
};
