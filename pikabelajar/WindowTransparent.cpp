#include "stdafx.h"
#include "WindowTransparent.h"

#define WS_EX_LAYERED	0x80000 
#define LWA_ALPHA		2 
#define LWA_COLORKEY	1 

typedef DWORD (WINAPI *PSLWA)(HWND, DWORD, BYTE, DWORD);

static PSLWA pSetLayeredWindowAttributes = NULL;
static BOOL initialized = FALSE;

BOOL MakeWindowTransparent(HWND hWnd, int nPos)
{
	if (!initialized)
	{
		HMODULE hDLL = LoadLibrary ("user32");

		pSetLayeredWindowAttributes = (PSLWA) GetProcAddress(hDLL, "SetLayeredWindowAttributes");

		initialized = TRUE;
	}

	if (pSetLayeredWindowAttributes == NULL) 
		return FALSE;

	SetLastError(0);

	SetWindowLong(hWnd, GWL_EXSTYLE ,	GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	if (GetLastError())
		return FALSE;

    return pSetLayeredWindowAttributes (hWnd, 0, nPos, LWA_ALPHA);
}

BOOL SetTransparentInitDlg(HWND hWnd)
{
	if (!initialized)
	{
		HMODULE hDLL = LoadLibrary ("user32");

		pSetLayeredWindowAttributes = (PSLWA) GetProcAddress(hDLL, "SetLayeredWindowAttributes");

		initialized = TRUE;
	}

	if (pSetLayeredWindowAttributes == NULL) 
		return FALSE;

	::SetWindowLong(hWnd, GWL_EXSTYLE,::GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	pSetLayeredWindowAttributes(hWnd, 0, 100, LWA_ALPHA); 
	
	::ShowWindow(hWnd, SW_SHOW);
	
	::RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW); 

	pSetLayeredWindowAttributes(hWnd, 0, 100, LWA_ALPHA);

	return TRUE;
}

BOOL SetTransparentDlgSHOW(HWND hWnd)
{
	if (!initialized)
	{
		HMODULE hDLL = LoadLibrary ("user32");

		pSetLayeredWindowAttributes = (PSLWA) GetProcAddress(hDLL, "SetLayeredWindowAttributes");

		initialized = TRUE;
	}

	if (pSetLayeredWindowAttributes == NULL) 
		return FALSE;

   BYTE bTranslucency;
   const BYTE TRANSLUCENCY = 255;
   const BYTE TRANSLUCENCY_STEP = 1;
  
   ::SetWindowLong(hWnd, GWL_EXSTYLE,::GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

   pSetLayeredWindowAttributes(hWnd, 0, 200, LWA_ALPHA); 
   
   ::ShowWindow(hWnd, SW_SHOW);

   ::RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW); 
  
   for (bTranslucency = 200; bTranslucency < TRANSLUCENCY;  bTranslucency+=TRANSLUCENCY_STEP)
   {
   	   pSetLayeredWindowAttributes(hWnd, 0, bTranslucency, LWA_ALPHA);
   }

   pSetLayeredWindowAttributes(hWnd, 0, bTranslucency, LWA_ALPHA);

   return TRUE;
}

BOOL SetTransparentDlgHIDE(HWND hWnd)
{
	if (!initialized)
	{
		HMODULE hDLL = LoadLibrary ("user32");

		pSetLayeredWindowAttributes = (PSLWA) GetProcAddress(hDLL, "SetLayeredWindowAttributes");

		initialized = TRUE;
	}

	if (pSetLayeredWindowAttributes == NULL) 
		return FALSE;

  	::SetWindowLong(hWnd, GWL_EXSTYLE,::GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);

	pSetLayeredWindowAttributes(hWnd, 0, 100, LWA_ALPHA); 
	
	::ShowWindow(hWnd, SW_SHOW);
	
	::RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW); 

 	pSetLayeredWindowAttributes(hWnd, 0, 100, LWA_ALPHA);

 	return TRUE;
}

