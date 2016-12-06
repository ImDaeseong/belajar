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
	COLORREF	m_clrText;			// ���ڻ�
	CFont       m_FontText;			// ���� ��Ʈ
	int         m_FontArrangeStyle; //��Ʈ ���� ��Ÿ�� 

protected:
   afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg void OnPaint();
DECLARE_MESSAGE_MAP()
};


