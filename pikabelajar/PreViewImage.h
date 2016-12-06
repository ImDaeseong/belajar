#pragma once

class CPreViewImage : public CStatic
{	
DECLARE_DYNAMIC(CPreViewImage)

public:
	CPreViewImage();
	virtual ~CPreViewImage();

public:
	void Free();
	BOOL GetBoundRect(CRect& rcBound) const;
	BOOL LoadImage(UINT ResourceName, CString ResourceType);
	BOOL IsPictureValid() const;    
    void CheckDimension(const CRect& rcClient, const CRect& rcBound, CRect& rcDim);
    virtual HBRUSH AllocMarginBrush() const;
    virtual void FreeMarginBrush(HBRUSH hBrush) const;
    virtual void OnDraw(CDC& DC, const CRect& rcClient, const CRect& rcBound, const CRect& rcDim);
	CPreViewImage& SetPictureStaticClick(BOOL bClick = FALSE);
	void SetPictureStaticCursor(BOOL bCursor = FALSE);

protected:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual void PreSubclassWindow();
	DECLARE_MESSAGE_MAP()

private:
    Bitmap* m_pBmp;
	BOOL     m_bCursor;
	HCURSOR	 m_hCursor;
	CString m_strResourceImg;
	BOOL     m_bClick;
};

