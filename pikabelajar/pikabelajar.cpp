// pikabelajar.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "pikabelajar.h"
#include "pikabelajarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPikabelajarApp

BEGIN_MESSAGE_MAP(CPikabelajarApp, CWinApp)
	//{{AFX_MSG_MAP(CPikabelajarApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPikabelajarApp construction

CPikabelajarApp::CPikabelajarApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPikabelajarApp object

CPikabelajarApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPikabelajarApp initialization

BOOL CPikabelajarApp::InitInstance()
{
	HANDLE hMutex = ::CreateMutex(NULL, FALSE, "PikabelajarInstance");
	if (ERROR_ALREADY_EXISTS == ::GetLastError())
		return FALSE;
	
	// Initialize GDI+
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	RegisterWin();


	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	CString strResourceDll;
	strResourceDll.Format("%s\\pikabelajarRes.dll", CFunc::GetModulePath());
	//int nInExist = _access(strResourceDll, 0);
	//if(nInExist == -1)
	//{
	//	DownloadPicaResource(lstResourceDll);
	//}
	if((m_hResourceDll = LoadLibrary(strResourceDll)) == NULL)
	{
		return FALSE;
	}



	CPikabelajarDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CPikabelajarApp::RegisterWin()
{
	WNDCLASS wndclass;
	::GetClassInfo(AfxGetInstanceHandle(), "#32770", &wndclass);
	CString strClassName = "Pikabelajarclient";
	wndclass.lpszClassName = strClassName;
	BOOL bSuccess;
	bSuccess = AfxRegisterClass(&wndclass);
}

BOOL CPikabelajarApp::PreTranslateMessage(MSG* pMsg) 
{
	switch (pMsg->message)
	{
/*
	case	WM_KEYDOWN:

		if (pMsg->wParam == VK_RETURN)
		{
			return FALSE;
		}
		else if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
*/
	case	WM_SYSKEYDOWN:
		if (pMsg->wParam == VK_F4)
		{
			return TRUE;
		}
	default:
		break;
	}		
	return CWinApp::PreTranslateMessage(pMsg);
}

int CPikabelajarApp::ExitInstance() 
{
	FreeResource(m_hResourceDll);

	GdiplusShutdown(m_gdiplusToken);
	
	return CWinApp::ExitInstance();
}