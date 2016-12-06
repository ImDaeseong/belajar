#pragma once

class CTransparentImage : public CStatic
{
DECLARE_DYNAMIC(CTransparentImage)

public:
	CTransparentImage() ;
	virtual ~CTransparentImage() ;

	CTransparentImage& SetPictureStaticClick(BOOL bClick = FALSE);
	void SetPictureStaticCursor(BOOL bCursor = FALSE);
	void SendMessagePopup(int nClose);

protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	DECLARE_MESSAGE_MAP()
private:
   	BOOL     m_bCursor;
	HCURSOR	 m_hCursor;
	BOOL     m_bClick;
	int      m_nClose;
};
