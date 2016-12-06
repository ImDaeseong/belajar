#pragma once

class CTransparentLink : public CStatic
{
DECLARE_DYNAMIC(CTransparentLink)
public:
	CTransparentLink();
	virtual ~CTransparentLink();
public:
	void SetNoticeInfo(HWND hNoticeWnd, DWORD dwClickMsg, DWORD dwWndID);
	void ExecuteIE();
	void SetTextColor(COLORREF text)			 {	m_clrText		   = text;			}
	void SetFontArrangeStyle(int nFontArStyle)   {  m_FontArrangeStyle = nFontArStyle;  }
	void SetFontInfo(int size, char *name, int=FW_NORMAL);
	COLORREF	m_clrText;			// 글자색
	CFont       m_FontText;			// 글자 폰트
	int         m_FontArrangeStyle; //폰트 정렬 스타일 

	//링크 커서 
	CTransparentLink& SetLinkCursor(HCURSOR hCursor);
	HCURSOR		m_hCursor;

	//링크 사용 여부  
	CTransparentLink& SetLink(BOOL bLink);
	BOOL		m_bLink;
	
	//링크 사용시 url 주소
	void  SetLinkUrl(CString strUrl);
	CString     m_strUrlLink;

	HWND m_hNoticeWnd;
	DWORD m_dwClickMsg;
	DWORD m_dwWndID;

protected:
   afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg void OnPaint();
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
DECLARE_MESSAGE_MAP()
};


