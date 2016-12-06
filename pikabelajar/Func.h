// Func.h: interface for the CFunc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNC_H__CA2DB6EB_B29D_4555_AF48_345BD29106E2__INCLUDED_)
#define AFX_FUNC_H__CA2DB6EB_B29D_4555_AF48_345BD29106E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFunc  
{
public:
	static BOOL IsDirectory(CString strFilePath);
	static BOOL DeleteFolderA(CString strFolderPath);

	static HICON GetFolderIcon();
	static HICON GetNotFountFileIcon();
	static HICON GetDefaultIcon();

	static HWND GetFullScreenWindow();
	static HWND GetExplorerHandle();
	
	static DWORD GetPID(char * szFileName);
	static void TerminateProcess(DWORD dwPID);
				
	static void ExecuteDefaultIE();
	static void ExecuteControlPanel();
	static void ExecuteMyComputer();
	static void ExecuteDesktop();
	static void ExecuteMonitorCpl();
	static void ExecuteVolumeCpl();
	static void ExecuteMouseCpl();
	static void ExecuteDeskCpl();
	static void ExecuteRecycleBin();
	static void ExecuteIE(CString strUrl);

	static CString GetMyComputerFolder();
	static CString GetDesktopFolder();
	static CString GetSystemDrive();
	static CString GetWindowsFolder();
	static CString GetSystemFolder();
	static CString GetProgramFilesFolder();
	static CString GetModulePath();
	static CString GetDesktopPath();

#ifdef _USE_WINSOCK
	static CString GetIPAddress();
#endif
	static BOOL GetIpAddress(CString strIpAddress, CString &strIp1, CString &strIp2, CString &strIp3, CString &strIp4);
    	
	static int  GetWin7Info(int nPcNo);
	static BOOL IsVistaOrLater(); 
	static int DisableFireWall(char * szWorkingDir);
	static BOOL SystemShutDown(BOOL bReboot, BOOL bForce = FALSE);
	static void SystemShutDown();
	static void SystemReboot();

	static int GetIntStartProgFixType(CString strType);
	static CString GetStartProgFixTypeInt(int nType);
	static CString GetStringStartProgFixType(CString strType);
	static CString GetStartProgFixType(CString strType);
	static CString GetString(int nValue);

	static CString GetTime();
	static CString GetCurTime();

	static BOOL IsAlpha(CString strText, int nTextLen);
	static BOOL IsAlphaOrNumber(CString strText, int nTextLen);
	static BOOL IsNumber(CString strText, int nTextLen);

	static int GetPUP();
	static int Power(int x, int y);
	
	static CString GetAddCommaString(CString strNumber);
	static void SetAddCommaString(const char *str_num, char *num_str);

	static BOOL IsSet(USHORT sShort, int nPos);
	static BOOL IsSet(BYTE bByte, int nPos);
	
	static void SetFixOnOff(int nPcNo, int nValue);

#ifdef _USE_HTTP_DOWN
	static BOOL HTTPDown(char *szUrl, char *szLocal, DWORD dwFileLen = 0);
#endif

	static HRESULT ExeCreateShortCut(LPCSTR szSrcFile, LPSTR szLnkFile, LPSTR szArgument, LPSTR szDesc);

	CFunc();
	virtual ~CFunc();

};

#endif // !defined(AFX_FUNC_H__CA2DB6EB_B29D_4555_AF48_345BD29106E2__INCLUDED_)
