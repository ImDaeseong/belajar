#pragma once

class CTransparentStatic : public CStatic
{
DECLARE_DYNAMIC(CTransparentStatic)
public:
	CTransparentStatic();
	virtual ~CTransparentStatic();
public:
	void SetTextColor(COLORREF text)			 {	m_clrText		   = text;			}
	void SetFontArrangeStyle(int nFontArStyle)   {  m_FontArrangeStyle = nFontArStyle;  }
	void SetFontInfo(int size, char *name, int=FW_NORMAL);
	COLORREF	m_clrText;			// 글자색
	CFont       m_FontText;			// 글자 폰트
	int         m_FontArrangeStyle; //폰트 정렬 스타일 

protected:
   afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg void OnPaint();
DECLARE_MESSAGE_MAP()
};


