#pragma once


// CSkinButton

class CSkinButton : public CButton
{
	DECLARE_DYNAMIC(CSkinButton)

public:
	CSkinButton();
	virtual ~CSkinButton();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	
public:
	void Free();
	void SetEnableButton();
	void SetDisableButton();

	void SetImage(UINT uid, LPCTSTR pType, HMODULE hInst, int nStartX, int nStartY, int nDivide = 4);
	void SetImage(LPCTSTR pName, LPCTSTR pType, HMODULE hInst, int nStartX, int nStartY, int nDivide = 4);
	LRESULT WindowProc(UINT nMessage, WPARAM wParam, LPARAM lParam);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

	BOOL IsHover(){
return m_bHover;}
	afx_msg BOOL OnBnClicked();
	void OnHover();
	void DrawButton(int id);
	void OnDrawWindow(Graphics& Gps);
private:
	BOOL m_bHover;
	BOOL m_bTracking;
	BOOL m_Clicked;
	int m_Status;
	CGdiPlusBitmapResource * m_pBGImage;

	int m_nStartX;
	int m_nStartY;
	int m_nDivide;
	BOOL m_bDisable;
};


