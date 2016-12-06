#pragma once

class CZipBitmap : public CBitmap
{
public:
	void DrawTrans(HDC hDC, int x, int y,COLORREF colTrans);
    CZipBitmap();
    ~CZipBitmap();
    void Draw(HDC hDC, int x, int y);
	void Draw(HDC hDC, int x, int y,int height,int width);
    void Draw(CDC* pDC, int x, int y);
    void DrawTrans(HDC hDC, int x, int y);
    void DrawTrans(CDC* pDC, int x, int y);
    int GetWidth();
    int GetHeight();

private:
	void CreateMask(HDC hDC,COLORREF colTrans);
    int m_iWidth;
    int m_iHeight;
    HBITMAP m_hbmMask;    
	
    void GetMetrics();
    void CreateMask(HDC hDC);
};