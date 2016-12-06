// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__9B82FDA5_18BA_453F_8D63_62AFB0EDDBA2__INCLUDED_)
#define AFX_STDAFX_H__9B82FDA5_18BA_453F_8D63_62AFB0EDDBA2__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#define     _WIN32_DCOM  
#endif // _MSC_VER > 1000

#define WINVER 0x500
#define _WIN32_WINNT 0x500



#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
//#define _WIN32_WINNT 0x0501		// Change this to the appropriate value to target other versions of Windows.

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <GdiPlus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")


#pragma warning(disable:4786) 

#include <vector>
using namespace std;

#include <Atlbase.h>


#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib")

//#include <winsock2.h>
//#include <Wininet.h>
//#include "tlhelp32.h"
//#include "AfxSock.h"
//#include "AFXINET.H"

//#include <wininet.h>
#include <shellapi.h>
#include <Shlwapi.h>

//#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "shlwapi.lib")

#include <io.h>
#include <Afxtempl.h> 

#include "CScrollTextStatic.h"
#include "CGdiPlusBitmap.h"
#include "SkinButton.h"
#include "GdipButton.h"
#include "GdipButtonex.h"
#include "Func.h"
#include "ResourcBitmap.h"
#include "LeftPictureStatic.h"
#include "PictureStatic.h"
#include "Label.h"
#include "KbcButton.h"
#include "ResourcBitmapgif.h"
//#include "ScrollTextStaticimg.h"
#include "PreViewImage.h"
#include "PhotoPictureStatic.h"
#include "TransparentStatic.h"
//#include "SplashScreenEx.h"
#include "WindowTransparent.h"
#include "TransparentImage.h"
#include "SkinButtonDuaButton.h"

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }

#define WS_EX_LAYERED	0x80000 

#define IDR_PNG_INTRO                   1000
#define IDR_PNG_INTRO2                  1001
#define IDR_PNG_INTRO3                  1002
#define IDR_PNG_DEFAULT                 1003

#define WM_PREVIEWIMG_CLOSE				WM_USER + 3000
#define WM_HAPUSMESSAGE_SEND			WM_USER + 3001

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9B82FDA5_18BA_453F_8D63_62AFB0EDDBA2__INCLUDED_)
