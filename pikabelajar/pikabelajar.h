// pikabelajar.h : main header file for the PIKABELAJAR application
//

#if !defined(AFX_PIKABELAJAR_H__EB8AE674_9741_4B00_8842_07B70B59232F__INCLUDED_)
#define AFX_PIKABELAJAR_H__EB8AE674_9741_4B00_8842_07B70B59232F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPikabelajarApp:
// See pikabelajar.cpp for the implementation of this class
//

class CPikabelajarApp : public CWinApp
{
protected:
	// Implementation
	ULONG_PTR	m_gdiplusToken;

public:
	CPikabelajarApp();

	void RegisterWin();
	
	HINSTANCE m_hResourceDll;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPikabelajarApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPikabelajarApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIKABELAJAR_H__EB8AE674_9741_4B00_8842_07B70B59232F__INCLUDED_)
