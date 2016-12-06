
#include "stdafx.h"
#include "TransparentStatic.h"

IMPLEMENT_DYNAMIC(CTransparentStatic, CStatic)
CTransparentStatic::CTransparentStatic()
{
	m_FontArrangeStyle = 0;

	m_clrText = GetSysColor(COLOR_CAPTIONTEXT);

	SetFontInfo(12, "Arial", FW_NORMAL);//SetFontInfo(12, "Tahoma", FW_NORMAL);
}

CTransparentStatic::~CTransparentStatic()
{
	if(m_FontText.GetSafeHandle())	m_FontText.DeleteObject();
}

BEGIN_MESSAGE_MAP(CTransparentStatic, CStatic)
   ON_WM_CTLCOLOR_REFLECT()
   ON_WM_ERASEBKGND()
   ON_WM_PAINT()
END_MESSAGE_MAP()

HBRUSH CTransparentStatic::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
   pDC->SetBkMode(TRANSPARENT);
   return (HBRUSH)GetStockObject(NULL_BRUSH);
}

void CTransparentStatic::SetFontInfo(int size, char *name, int bold)
{
	if(m_FontText.GetSafeHandle())	m_FontText.DeleteObject();

    m_FontText.CreateFont(
					size,						// ���� ũ��
					0,							// nWidth
					0,							// nEscapement
					0,							// nOrientation
					bold,						// nWeight
					FALSE,						// bItalic
					FALSE,						// bUnderline
					0,							// cStrikeOut
					DEFAULT_CHARSET,			// nCharSet
					OUT_DEFAULT_PRECIS,			// nOutPrecision
					CLIP_DEFAULT_PRECIS,		// nClipPrecision
					DEFAULT_QUALITY,			// nQuality
					DEFAULT_PITCH | FF_SWISS,	// nPitchAndFamily
					name);						// ��Ʈ �̸�
}
/*
////////////////////////////////////////////////////////////////////////////////////////////////////
///         �ؽ�Ʈ�� dc �� ����� ����ϱ�. �������� ��쿡�� ���� �۵��ϵ��� �Ǿ���. 
///         �Ϲ����� ��� format ���� DT_LEFT | DT_WORDBREAK �� �����ϴ�.
/// @param  
/// @return 
/// @date   Tuesday, March 26, 2013  3:57:07 PM
////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawTextCenter(HDC dc, LPCWSTR text, int cchText, LPCRECT lprc, UINT format)
{
   if(dc==NULL || lprc==NULL) return;

   RECT rect = *lprc;
   RECT rectResult = *lprc;

   // ���ڰ� �����ϴ� �簢�� ���
   DrawText(dc, text, cchText, &rect, format | DT_CALCRECT );

   // ����, ���η� ����
   int marginH = max(0, ((lprc->bottom-lprc->top) - (rect.bottom-rect.top))/2);
   int marginW= max(0, ((lprc->right-lprc->left) - (rect.right-rect.left))/2);
   rectResult.top    += marginH;
   rectResult.bottom -= marginH;
   rectResult.left     += marginW;
   rectResult.right  -= marginW;

   // ���� �׸���
   DrawText(dc, text, cchText, &rectResult, format);
}
*/

void CTransparentStatic::OnPaint()
{
	CPaintDC dc(this); 

	CRect rClient;
	GetClientRect(rClient);


	//���� �ȿ� �� ����
	CString szText;
	GetWindowText(szText);

	// Map "Static Styles" to "Text Styles"
    #define MAP_STYLE(src, dest)	if(dwStyle & (src)) dwText |= (dest)
    #define NMAP_STYLE(src, dest)	if(!(dwStyle & (src))) dwText |= (dest)

	//��Ʈ ���Ĺ��  
	DWORD dwStyle = GetStyle(), dwText = m_FontArrangeStyle; 
	
	MAP_STYLE(	SS_RIGHT,			DT_RIGHT					);
	MAP_STYLE(	SS_CENTER,			DT_CENTER					);
	MAP_STYLE(	SS_CENTERIMAGE,		DT_VCENTER | DT_SINGLELINE	);
	MAP_STYLE(	SS_NOPREFIX,		DT_NOPREFIX					);
	MAP_STYLE(	SS_WORDELLIPSIS,	DT_WORD_ELLIPSIS			);
	MAP_STYLE(	SS_ENDELLIPSIS,		DT_END_ELLIPSIS				);
	MAP_STYLE(	SS_PATHELLIPSIS,	DT_PATH_ELLIPSIS			);

	NMAP_STYLE(	SS_LEFTNOWORDWRAP | SS_CENTERIMAGE | SS_WORDELLIPSIS |
				SS_ENDELLIPSIS | SS_PATHELLIPSIS, DT_WORDBREAK);

	HFONT hFont;
	if(m_FontText.GetSafeHandle())
	{
		hFont = (HFONT)SelectObject(dc.m_hDC, (HFONT)m_FontText.m_hObject);
	}

	if(szText.GetLength() > 0)	
	{
		int iPrvMode = dc.SetBkMode(TRANSPARENT);	// ���� ��� �����ϰ�
		dc.SetTextColor(m_clrText);	            	// ���ڻ� ����
		dc.DrawText(szText, rClient, dwText);		// ���� �Ѹ���		
		dc.SetBkMode(iPrvMode);		
	}

	if(m_FontText.GetSafeHandle())	::SelectObject(dc.m_hDC, hFont);
	
}

BOOL CTransparentStatic::OnEraseBkgnd(CDC* pDC)
{
   return TRUE;
}

