#include "StdAfx.h"
#include "MultiColorStatic.h"

CMultiColorStatic::CMultiColorStatic()
{
    SetBackColor();
    m_astrData.RemoveAll();
    m_fAutoSize = true;
}

CMultiColorStatic::~CMultiColorStatic()
{
    RemoveAllStrings();
}

BOOL CMultiColorStatic::SetString(const int& nIndex, const CColorString& strData)
{
	CObject* pNewOne;
  	BOOL     fStringRemoved = FALSE;

	if ((nIndex < 0) || (nIndex > m_astrData.GetSize()))
	{
		ASSERT(FALSE);
		return (FALSE);
	}

    if (strData.GetLength() == 0)
    {
       return (FALSE);
    }

    if (nIndex < m_astrData.GetSize())
    {
       RemoveString(nIndex);
       fStringRemoved = TRUE;
    }

	pNewOne = reinterpret_cast<CObject*>(new CColorString(strData));

	if (pNewOne)
	{
    
		if (fStringRemoved)
		{
		    m_astrData.InsertAt(nIndex, pNewOne);
		}
        else
		{          
			m_astrData.SetAtGrow(nIndex, pNewOne);
		}
      	Invalidate();
		return (TRUE);
	}

	return (FALSE);
}

CColorString CMultiColorStatic::GetString(const int& nIndex /* = 0 */) const
{
	CColorString strTemp;	

	if ((nIndex < 0) || (nIndex > m_astrData.GetUpperBound()))
	{
		ASSERT(FALSE);
		return (FALSE);
	}

	strTemp = *(reinterpret_cast<CColorString*>(m_astrData.GetAt(nIndex)));

	return (strTemp);
}

BOOL CMultiColorStatic::AddString(const CColorString& strData)
{
    return (SetString(m_astrData.GetSize(), strData));
}

BOOL CMultiColorStatic::AddString(LPCTSTR lpszText, const DWORD& dwStyle /* = 0x00000000*/, const COLORREF& crBackColor /* = 0xFFFFFFFF */)
{
    return (AddString(CColorString(lpszText, dwStyle, crBackColor)));
}

BOOL CMultiColorStatic::RemoveString(const int& nIndex)
{
   if ((nIndex < 0) || (nIndex > m_astrData.GetUpperBound()))
   {
       ASSERT(FALSE);    // an invalid index was passed in
       return (FALSE);
   }

   CColorString* pstrCurrent = reinterpret_cast<CColorString*>(m_astrData.GetAt(nIndex));
   if (pstrCurrent)
   { 
	   m_astrData.RemoveAt(nIndex);
       delete pstrCurrent;
   }
   
   if (::IsWindow(m_hWnd))
   {
       Invalidate();
   }

   return (TRUE);
}

void CMultiColorStatic::RemoveAllStrings(void)
{
  	while (m_astrData.GetSize() > 0)
	{
   		RemoveString(m_astrData.GetUpperBound());
	}
   
	if (::IsWindow(m_hWnd))
   	{
       Invalidate();
    }
}

DWORD CMultiColorStatic::GetNumStrings(void) const
{
    return (m_astrData.GetSize());
}

void CMultiColorStatic::SetBackColor(const COLORREF& crBackColor /* = 0xFFFFFFFF */)
{
	if (crBackColor == 0xFFFFFFFF)
	{
		m_crBackColor = ::GetSysColor(COLOR_BTNFACE);
	}
	else
	{
		m_crBackColor = crBackColor;
	}

	m_brBackGround.DeleteObject();
	m_brBackGround.CreateSolidBrush(m_crBackColor);

    if (::IsWindow(m_hWnd))
    {
       Invalidate();
    }
}

COLORREF CMultiColorStatic::GetBackColor(void) const
{
	return (m_crBackColor);
}

int CMultiColorStatic::GetWindowText(LPTSTR lpszBuffer, int nMaxCount)
{  
	memset(lpszBuffer, 0, nMaxCount);
   	CalculateWindowText();
   	strncpy(lpszBuffer, m_strWindowText, nMaxCount);

	if (m_strWindowText.GetLength() == nMaxCount)
    {
       lpszBuffer[nMaxCount] = 0;
    }

    return (m_strWindowText.GetLength());
}

void CMultiColorStatic::GetWindowText(CString& strData)
{
  	CalculateWindowText();
  	strData = m_strWindowText;
  	return;
}

void CMultiColorStatic::SetWindowText(LPCTSTR lpszValue)
{
	RemoveAllStrings();
    AddString(lpszValue);
}

void CMultiColorStatic::SetAutoSize(const bool& fAutoSize)
{  
	m_fAutoSize = fAutoSize;
}

bool CMultiColorStatic::GetAutoSize(void) const
{
  	return (m_fAutoSize);
}

void CMultiColorStatic::DetermineFont(const CColorString* const pstrData)
{
	LOGFONT stFont;

 	m_ftText.DeleteObject();

	if (!GetFont()->GetLogFont(&stFont))
   	{		
		memset(&stFont, 0, sizeof(stFont));

		stFont.lfWidth = ((stFont.lfHeight * 7) / 16);
		stFont.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	}

	if (m_fAutoSize)
	{
		stFont.lfHeight = m_rcBounds.Height();
	}

	stFont.lfWeight = (pstrData->GetBold() ? FW_HEAVY : FW_NORMAL);
	stFont.lfUnderline = pstrData->GetUnderlined();
	stFont.lfItalic = pstrData->GetItalic();
	stFont.lfQuality = PROOF_QUALITY;
	m_ftText.CreateFontIndirect(&stFont);
}

void CMultiColorStatic::CalculateWindowText(void)
{
	m_strWindowText.Empty();

	for (int i = 0; i < m_astrData.GetSize(); i++)
	{
		CColorString* pCurrent = (CColorString*)m_astrData.GetAt(i);
		if (pCurrent)
		{
			m_strWindowText += *pCurrent;
		}
	}
}

void CMultiColorStatic::PreSubclassWindow(void)
{
	GetClientRect(m_rcBounds);

   	CDC* pDC = GetDC();
   	pDC->FillRect(m_rcBounds, &m_brBackGround);
   	ReleaseDC(pDC);

   	ModifyStyle(0, SS_NOTIFY);
}

BEGIN_MESSAGE_MAP(CMultiColorStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CMultiColorStatic::OnPaint() 
{  
	CPaintDC dc(this);
      
 	CRect rcBounds = m_rcBounds;
 	dc.FillRect(m_rcBounds, &m_brBackGround);

	for (int i = 0; i < m_astrData.GetSize(); i++)
   	{
   		CColorString* pstrCurrent = reinterpret_cast<CColorString*>(m_astrData.GetAt(i));
   		TEXTMETRIC    stFontMetrics;
   		SIZE          stSize;

		DetermineFont(pstrCurrent);
		dc.SelectObject(&m_ftText)->DeleteObject(); 

		if (pstrCurrent->GetBackColor() == ::GetSysColor(COLOR_BTNFACE))
      	{
      		dc.SetBkColor(m_crBackColor);
      	}
      	else
      	{
      		dc.SetBkColor(pstrCurrent->GetBackColor());
      	}
		dc.SetTextColor(pstrCurrent->GetColor());
		dc.GetOutputTextMetrics(&stFontMetrics);

		GetTextExtentPoint32(dc.GetSafeHdc(), *pstrCurrent, pstrCurrent->GetLength(), &stSize);
	
		dc.DrawText(*pstrCurrent, rcBounds, DT_LEFT);
      	rcBounds.left += stSize.cx + stFontMetrics.tmOverhang;
   	}
}

void CMultiColorStatic::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	GetClientRect(m_rcBounds);
}

void CMultiColorStatic::OnDestroy() 
{
	CStatic::OnDestroy();
	m_ftText.DeleteObject();
	m_brBackGround.DeleteObject();
}

BOOL CMultiColorStatic::OnEraseBkgnd(CDC* pDC) 
{	
	return (TRUE);
}

