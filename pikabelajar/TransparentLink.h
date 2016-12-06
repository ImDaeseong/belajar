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
	COLORREF	m_clrText;			// ���ڻ�
	CFont       m_FontText;			// ���� ��Ʈ
	int         m_FontArrangeStyle; //��Ʈ ���� ��Ÿ�� 

	//��ũ Ŀ�� 
	CTransparentLink& SetLinkCursor(HCURSOR hCursor);
	HCURSOR		m_hCursor;

	//��ũ ��� ����  
	CTransparentLink& SetLink(BOOL bLink);
	BOOL		m_bLink;
	
	//��ũ ���� url �ּ�
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


