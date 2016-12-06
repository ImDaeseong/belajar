#ifndef BANNERSTATIC_H_
#define BANNERSTATIC_H_

#pragma comment(lib, "winmm.lib")

//#include "StdAfx.h"
#include "MultiColorStatic.h"
#include "Mmsystem.h"
#include "vector"
using std::vector;

typedef void (WINAPI* PFNBANNERITEMCLICK)(HWND, int, HWND);

class CBannerStatic : public CMultiColorStatic
{
public: 
   CBannerStatic();
   virtual ~CBannerStatic();
   
private:
   CBannerStatic(const CBannerStatic& cSource);
   CBannerStatic& operator=(const CBannerStatic& cRight);

public:
   void SetScrollSpeed(const int& nSpeed);
   int GetScrollSpeed(void) const;
   void SetWrapText(const BOOL& fWrapText);
   BOOL GetWrapText(void) const;

   void SetItemCursor(const UINT& unItemCursor);
   void SetItemClickProc(PFNBANNERITEMCLICK pfnItemClick);

protected:
   void ScrollBanner(void);
   static void CALLBACK TimerProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
   
   void SetScrollSize(const int& nScrollSize);
   int  GetScrollSize(void) const;
   void SetScrollDelay(const DWORD& dwScrollDelay);
   DWORD GetScrollDelay(void) const;
   void CalculateScrollParameters(void);
   int FindStringFromPoint(CPoint point);
   LPARAM MakeParentPoint(CPoint point);

private:
   int   m_nBannerSpeed;   // -MAXSPEED <= m_nBannerSpeed <= MAXSPEED
   BOOL  m_fWrapText;      // should text wrap?
   UINT  m_tmScroll;       // timer identifier
   int   m_nTextOut;       // pixel to begin drawing text
   int   m_nTextLength;    // when text scrolls out of client rect, start over from the right
   int   m_nScrollSize;    // amount of pixels to move when scrolling
   DWORD m_dwScrollDelay;  // delay, in ms, for scrolling -- indirectly set by SetScrollSpeed

   vector<int> m_vnStrings;// beginning x-coordinates for each string
   HCURSOR m_hItemCursor;  // cursor for when you're over a string
   HCURSOR m_hStdCursor;   // standard cursor
   CPoint  m_ptCursor;     // so we know if we're over a string or not
   
   PFNBANNERITEMCLICK m_pfnItemClick;     // when an item is clicked, this function will be called
   
   static const int MAXSPEED;             // maxiumum speed the client is allowed
   static const int MAXSPEED_MODIFIER;    // used for determining scroll parameters
   static const int TIMERRESOLUTION;      // default for timeSetEvent function
   static const int STEPHEIGHT;           // when should we scroll by more than one pixel?

protected:
   virtual void PreSubclassWindow(void);

   afx_msg void OnTimer(UINT nIDEvent);
   afx_msg void OnPaint(void);
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
   afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg void OnDestroy();

   DECLARE_MESSAGE_MAP()
};

#endif