#pragma once

class CPictureStatic : public CStatic
{
public:
	void GetPictureRect(CRect& rPos);
	BOOL LoadImage(CString strImagePath);
	BOOL LoadImage(UINT ResourceName, CString ResourceType);
	void ReleaseFreeImage();
	void StaticRoundSize(int nX, int nY);

public:
	CPictureStatic();
	virtual ~CPictureStatic();
protected:
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
};
