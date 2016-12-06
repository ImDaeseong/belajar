#pragma once

#include "ZipBitmap.h"

class CZipSliderCtl : public CSliderCtrl
{
public:
	CZipSliderCtl();

private:
	CZipBitmap *m_bmpBack;
	CZipBitmap *m_bmTrans;
	BOOL		 m_bDragging;
	HCURSOR		 m_hCursor;

public:
	void SetSkin(UINT uiBackGround, UINT uiTickImage);//,short nCursor);
	void SetRange(int nMin, int nMax, BOOL bRedraw = FALSE);
	virtual ~CZipSliderCtl();

protected:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	DECLARE_MESSAGE_MAP()
};