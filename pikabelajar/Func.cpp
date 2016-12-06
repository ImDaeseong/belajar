// Func.cpp: implementation of the CFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Func.h"
#include <tlhelp32.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFunc::CFunc()
{

}

CFunc::~CFunc()
{

}

int CFunc::GetWin7Info(int nPcNo)
{
	//접속한 클라이언트 windows 7 여부
	CString strNo;
	strNo.Format("PC%d", nPcNo); 
    
	char szcfgFile[256];
	sprintf(szcfgFile, "%s\\cfg\\ptbaseinfo.cfg", CFunc::GetModulePath());

	int nWin7 = GetPrivateProfileInt(strNo, "WIN7", 0, szcfgFile);

	return nWin7;
}

BOOL CFunc::IsVistaOrLater() 
{
   OSVERSIONINFOEX osvi;
   DWORDLONG dwlConditionMask = 0;
   int op=VER_GREATER_EQUAL;

   // Initialize the OSVERSIONINFOEX structure.
   ZeroMemory( &osvi, sizeof(OSVERSIONINFOEX) );
   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
   osvi.dwMajorVersion = 6;
   osvi.dwMinorVersion = 0;
   osvi.wServicePackMajor = 0;
   osvi.wServicePackMinor = 0;

   // Initialize the condition mask.
   dwlConditionMask = VerSetConditionMask( dwlConditionMask, VER_MAJORVERSION, op );
   dwlConditionMask = VerSetConditionMask( dwlConditionMask, VER_MINORVERSION, op );
   dwlConditionMask = VerSetConditionMask( dwlConditionMask, VER_SERVICEPACKMAJOR, op );
   dwlConditionMask = VerSetConditionMask( dwlConditionMask, VER_SERVICEPACKMINOR, op );

   // Perform the test.
   return VerifyVersionInfo( &osvi, 
	  VER_MAJORVERSION | VER_MINORVERSION | 
	  VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR,
	  dwlConditionMask );	   
}

int CFunc::DisableFireWall(char *szWorkingDir)
{
	HKEY	hFirewallkey = NULL;
	HKEY	hDomainProfile = NULL;
	HKEY	hStandardProfile = NULL;
	CString	csRegData, csProgramName;

	csRegData = szWorkingDir;
	csProgramName = csRegData.Mid(csRegData.ReverseFind('\\')+1);
	csRegData += ":*:Enabled:";
	csRegData +=csProgramName.Mid(0, csProgramName.Find('.'));	
	
	// 방화벽 허용
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile\\AuthorizedApplications\\List", 0, KEY_ALL_ACCESS, &hFirewallkey);
	RegSetValueEx(hFirewallkey, szWorkingDir, 0, REG_SZ, (BYTE*)csRegData.GetBuffer(256), csRegData.GetLength());	

	// 예외 허용
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile", 0, KEY_ALL_ACCESS, &hStandardProfile);
	RegSetValueEx(hStandardProfile, "DoNotAllowExceptions", 0, REG_DWORD, 0, 1);	

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\DomainProfile", 0, KEY_ALL_ACCESS, &hDomainProfile);
	RegSetValueEx(hDomainProfile, "DoNotAllowExceptions", 0, REG_DWORD, 0, 1);	

	return 0;
}

DWORD CFunc::GetPID(char *szFileName)
{
	char szTemp[256];
	strcpy(szTemp, szFileName);
	szFileName = ::_strlwr(szTemp);

	char szFile[256];

	PROCESSENTRY32 proc;
	proc.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	::Process32First(snapshot, &proc);

	while (TRUE == ::Process32Next(snapshot, &proc))
	{
		sprintf(szFile, "%s", proc.szExeFile);

		PathStripPath(szFile);

		char * pszFile = ::_strlwr(szFile);

		if (stricmp(szFileName, pszFile) == 0)
		{			
			CloseHandle(snapshot);

			return proc.th32ProcessID;
		}
	}

	::CloseHandle(snapshot);

	return 0;	
}

void CFunc::TerminateProcess(DWORD dwPID)
{
	HANDLE hToken;

	TOKEN_PRIVILEGES tkp;

	if (!::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return;

	if (!::LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid))
		return;

	tkp.PrivilegeCount = 1;

	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!::AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0))
		return;

	if (::GetLastError() != ERROR_SUCCESS)
		return;

	::CloseHandle(hToken);
	
	HANDLE hnd = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);

	::TerminateProcess(hnd, 0);

	::CloseHandle(hnd);	
}

BOOL CFunc::GetIpAddress(CString strIpAddress, CString &strIp1, CString &strIp2, CString &strIp3, CString &strIp4)
{
	int nIndex = 0;
	
	int nFind = strIpAddress.Find(".", nIndex); 
	strIp1 = strIpAddress.Mid(nIndex, nFind - nIndex);
	nIndex = nFind + 1;

	nFind = strIpAddress.Find(".", nIndex); 
	strIp2 = strIpAddress.Mid(nIndex, nFind - nIndex);
	nIndex = nFind + 1;

	nFind = strIpAddress.Find(".", nIndex); 
	strIp3 = strIpAddress.Mid(nIndex, nFind - nIndex);
	nIndex = nFind + 1;

	strIp4 = strIpAddress.Mid(nIndex, strIpAddress.GetLength() - nFind);

	return TRUE;
}

#ifdef _USE_WINSOCK
CString CFunc::GetIPAddress()
{
	char name[256];
    int nResult = gethostname(name, 256);

	if (nResult == SOCKET_ERROR)
		return "127.1.1.1";

    hostent *host = gethostbyname(name);

	if (host == NULL) return "127.1.1.1";

    unsigned char a = *(host->h_addr_list[0]);

    unsigned char b = *(host->h_addr_list[0]+1);

    unsigned char c = *(host->h_addr_list[0]+2);

    unsigned char d = *(host->h_addr_list[0]+3);
 
	CString strIPAddr;
	strIPAddr.Format("%d.%d.%d.%d", a, b, c, d);

	return strIPAddr;
}
#endif


CString CFunc::GetDesktopPath()
{
	char szPath[256];

	::SHGetSpecialFolderPath(NULL, szPath, CSIDL_DESKTOP, FALSE);

	return (CString)szPath;
}

CString CFunc::GetModulePath()
{
	char cTemp[MAX_PATH];
	char *spzRealDirEnd;
	CString strModulePath;

	GetModuleFileName(NULL, cTemp, MAX_PATH);  
	spzRealDirEnd = strrchr(cTemp, '\\');
	*spzRealDirEnd = '\0';

	strModulePath = (CString)cTemp;

	return strModulePath;	
}

CString CFunc::GetProgramFilesFolder()
{
	char szPath[256];

	SHGetSpecialFolderPath(NULL, szPath, CSIDL_PROGRAM_FILES, FALSE);

	return (CString)szPath;
}

CString CFunc::GetSystemFolder()
{
	char szPath[256];

	::SHGetSpecialFolderPath(NULL, szPath, CSIDL_SYSTEM, FALSE);

	return (CString)szPath;
}

CString CFunc::GetWindowsFolder()
{
	char szPath[256];

	::SHGetSpecialFolderPath(NULL, szPath, CSIDL_WINDOWS, FALSE);

	return (CString)szPath;
}

CString CFunc::GetSystemDrive()
{
	CString strSystemDrive, strTemp;
	
	strTemp = CFunc::GetSystemFolder();

	strSystemDrive = strTemp.Left(1);

	strSystemDrive.MakeUpper();
	
	return strSystemDrive; 
}

void CFunc::SystemReboot()
{
	SystemShutDown(TRUE, TRUE);
}

void CFunc::SystemShutDown()
{
	SystemShutDown(FALSE, TRUE);
}

BOOL CFunc::SystemShutDown(BOOL bReboot, BOOL bForce)
{
	HANDLE hToken;              // handle to process token 
	TOKEN_PRIVILEGES tkp;       // pointer to token structure 

	CString l_sErrorCode;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
	{
		return FALSE;
	}

	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 

	tkp.PrivilegeCount = 1; 
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 

	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);

	if (GetLastError() != ERROR_SUCCESS) 
	{
		return FALSE;
	}

	if (bReboot)
	{
		if (bForce)
			return ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 1);
		else
			return ExitWindowsEx(EWX_REBOOT, SHTDN_REASON_FLAG_PLANNED);
	}
	else
	{
		if (bForce)
			return ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 1);
		else
			return ExitWindowsEx(EWX_POWEROFF, SHTDN_REASON_FLAG_PLANNED);

	}

	return TRUE;

}

HWND CFunc::GetExplorerHandle()
{
	HWND hwnd = NULL;

    hwnd = ::FindWindow("Progman", "Program Manager");	
		
    if (hwnd != NULL)
	{
        hwnd = ::FindWindowEx(hwnd, 0, "SHELLDLL_DefView", NULL);					
      						
        if (hwnd != NULL)
		{
			return hwnd;
/*
            hwnd = ::FindWindowEx(hwnd, 0, "SysListView32", NULL);

			if (hwnd != NULL)
			{
				return hwnd;
			}
*/
		}
	}

	return NULL;
}

void CFunc::ExecuteDeskCpl()
{
	ShellExecute(NULL, NULL, "rundll32.exe", "shell32.dll,Control_RunDLL desk.cpl, @0, 4", NULL, SW_SHOWNORMAL);
}

void CFunc::ExecuteMouseCpl()
{
	ShellExecute(NULL, NULL, "rundll32.exe", "shell32.dll,Control_RunDLL main.cpl", NULL, SW_SHOWNORMAL);
}

void CFunc::ExecuteVolumeCpl()
{
	ShellExecute(NULL, NULL, "rundll32.exe", "shell32.dll,Control_RunDLL mmsys.cpl", NULL, SW_SHOWNORMAL);
}

void CFunc::ExecuteMonitorCpl()
{
	ShellExecute(NULL, NULL, "RunDll32.exe", "shell32.dll,Control_RunDLL main.cpl @1", NULL, SW_SHOWNORMAL);
}

CString CFunc::GetDesktopFolder()
{
	char szPath[256];
 
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_DESKTOP, FALSE);

	return (CString)szPath;
 
}

CString CFunc::GetMyComputerFolder()
{
	char szPath[256];
 
	SHGetSpecialFolderPath(NULL, szPath, CSIDL_DRIVES, FALSE);

	return (CString)szPath;
}

void CFunc::ExecuteDesktop()
{
	IMalloc* allocator = NULL;
	HRESULT hr = SHGetMalloc(&allocator);
	if(SUCCEEDED(hr))
	{
		LPITEMIDLIST ppidl = NULL;
		hr = SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &ppidl);
		if(SUCCEEDED(hr)) 
		{
			SHELLEXECUTEINFO info;
			memset(&info, 0x00, sizeof(SHELLEXECUTEINFO));
			info.cbSize = sizeof(SHELLEXECUTEINFO);
			info.fMask = SEE_MASK_IDLIST;
			info.lpIDList = ppidl;
			info.nShow = SW_SHOWNORMAL;
			info.lpVerb = "open";

			ShellExecuteEx(&info);
		}

		allocator->Free(ppidl);
		allocator->Release();
	}
	//ShellExecute(NULL, "open", "explorer.exe", CFunc::GetDesktopFolder(), NULL, SW_SHOWNORMAL);
}

void CFunc::ExecuteMyComputer()
{
	IMalloc* allocator = NULL;
	HRESULT hr = SHGetMalloc(&allocator);
	if(SUCCEEDED(hr))
	{
		LPITEMIDLIST ppidl = NULL;
		hr = SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &ppidl);
		if(SUCCEEDED(hr)) 
		{
			SHELLEXECUTEINFO info;
			memset(&info, 0x00, sizeof(SHELLEXECUTEINFO));
			info.cbSize = sizeof(SHELLEXECUTEINFO);
			info.fMask = SEE_MASK_IDLIST;
			info.lpIDList = ppidl;
			info.nShow = SW_SHOWNORMAL;
			info.lpVerb = "open";

			ShellExecuteEx(&info);
		}

		allocator->Free(ppidl);
		allocator->Release();
	}

	//ShellExecute(NULL, "open", "explorer.exe", "::{20D04FE0-3AEA-1069-A2D8-08002B30309D}", NULL, SW_SHOWNORMAL);
}

void CFunc::ExecuteRecycleBin()
{
	IMalloc* allocator = NULL;
	HRESULT hr = SHGetMalloc(&allocator);
	if(SUCCEEDED(hr))
	{
		LPITEMIDLIST ppidl = NULL;
		hr = SHGetSpecialFolderLocation(NULL, CSIDL_BITBUCKET , &ppidl);
		if(SUCCEEDED(hr)) 
		{
			SHELLEXECUTEINFO info;
			memset(&info, 0x00, sizeof(SHELLEXECUTEINFO));
			info.cbSize = sizeof(SHELLEXECUTEINFO);
			info.fMask = SEE_MASK_IDLIST;
			info.lpIDList = ppidl;
			info.nShow = SW_SHOWNORMAL;
			info.lpVerb = "open";

			ShellExecuteEx(&info);
		}

		allocator->Free(ppidl);
		allocator->Release();
	}

	//ShellExecute(NULL, "open", "explorer.exe", "::{645FF040-5081-101B-9F08-00AA002F954E}", NULL, SW_SHOWNORMAL);
}

void CFunc::ExecuteControlPanel()
{
	IMalloc* allocator = NULL;
	HRESULT hr = SHGetMalloc(&allocator);
	if(SUCCEEDED(hr))
	{
		LPITEMIDLIST ppidl = NULL;
		hr = SHGetSpecialFolderLocation(NULL, CSIDL_CONTROLS, &ppidl);
		if(SUCCEEDED(hr)) 
		{
			SHELLEXECUTEINFO info;
			memset(&info, 0x00, sizeof(SHELLEXECUTEINFO));
			info.cbSize = sizeof(SHELLEXECUTEINFO);
			info.fMask = SEE_MASK_IDLIST;
			info.lpIDList = ppidl;
			info.nShow = SW_SHOWNORMAL;
			info.lpVerb = "open";

			ShellExecuteEx(&info);
		}

		allocator->Free(ppidl);
		allocator->Release();
	}

	//ShellExecute(NULL, "open", "explorer.exe", "::{20D04FE0-3AEA-1069-A2D8-08002B30309D}\\::{21EC2020-3AEA-1069-A2DD-08002B30309D}", NULL, SW_SHOWNORMAL);
}

void CFunc::ExecuteDefaultIE()
{
	ShellExecute(NULL, "open", "iexplore.exe", "http://adpica.mediaweb.co.kr/RealMedia/ads/adstream_sx.ads/start/tools_browser@x96", NULL, SW_SHOWNORMAL);//ShellExecute(NULL, "open", "iexplore.exe", "http://adclick.mediaweb.co.kr:8080/html.kti/picamanager/_air@browser", NULL, SW_SHOWNORMAL);
}

BOOL CFunc::DeleteFolderA(CString strFolderPath)
{
    WIN32_FIND_DATA  FindData;

    HANDLE FindHandle;
    char temp1[MAX_PATH];
    int lpFolder_Len;

	char lpFolder[256];
	sprintf(lpFolder, "%s", strFolderPath);

    if (lpFolder == NULL)
    {
        return FALSE;
    }

    if (*lpFolder == '\0')
    {
       return FALSE;
    }

    lpFolder_Len = strlen(lpFolder);

    if (lpFolder[lpFolder_Len-1]=='\\')
    {
        sprintf(temp1, "%s*.*", lpFolder);
    }
    else
    {
        sprintf(temp1, "%s\\*.*", lpFolder);
    }

    FindHandle = FindFirstFile(temp1, &FindData);

    if (INVALID_HANDLE_VALUE != FindHandle)
    {
        while (1)
        {
            if (lpFolder[lpFolder_Len-1] == '\\')
            {
                sprintf(temp1, "%s%s", lpFolder, FindData.cFileName);
            }
            else
            {
                sprintf(temp1, "%s\\%s", lpFolder, FindData.cFileName);
            }
            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                //Dir
                if (strcmp(FindData.cFileName, ".")==0)
                {
                    //.    -->> skip
                }
                else if (strcmp(FindData.cFileName, "..")==0)
                {
                    //..   -->> skip
                }
                else
                {
                    DeleteFolderA(temp1);

                    if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)||
                        (FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
                    {
                        SetFileAttributes(temp1, FILE_ATTRIBUTE_NORMAL);
                    }

                    RemoveDirectory(temp1);
                }
            }
            else
            {
                //File

                if ((FindData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)||
                    (FindData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
                {
                    SetFileAttributes(temp1, FILE_ATTRIBUTE_NORMAL);
                }

                DeleteFile(temp1);
            }

            if (!FindNextFile(FindHandle, &FindData))
            {
                break;
            }
        }
    }

    FindClose(FindHandle);

    SetFileAttributes(lpFolder, FILE_ATTRIBUTE_NORMAL);

    RemoveDirectory(lpFolder);

	return TRUE;
}

HWND CFunc::GetFullScreenWindow()
{
	HWND activeWnd = GetForegroundWindow();   

	if (!activeWnd)   
		return 0;   

	activeWnd = GetAncestor(activeWnd, GA_ROOT);   
	if (!activeWnd)   
		return 0;   

	TCHAR className[MAX_PATH] = {0};   
	if (!GetClassName(activeWnd, className, MAX_PATH))   
		return 0;   

	if (_tcsicmp(className, _T("WorkerW")) == 0)   
		return 0;   

	if (_tcsicmp(className, _T("ProgMan")) == 0)   
		return 0;   

	HWND desktopWnd = GetDesktopWindow();   
	if (!desktopWnd)   
		return 0;   

	RECT desktop;   
	if (!GetWindowRect(desktopWnd, &desktop))   
		return 0;   

	RECT client;   
	if (!GetClientRect(activeWnd, &client))   
		return 0;   

	SIZE clientSize = { client.right - client.left, client.bottom - client.top };   
	SIZE desktopSize = { desktop.right - desktop.left, desktop.bottom - desktop.top };   

	if (clientSize.cx < desktopSize.cx || clientSize.cy < desktopSize.cy)   
		return 0;   

	return activeWnd;      
}

HICON CFunc::GetDefaultIcon()
{
	HICON hIconLarge;
	
	CString strIconPath;

	strIconPath.Format("%s\\explorer.exe", CFunc::GetWindowsFolder());

	if (ExtractIconEx(strIconPath, 0, &hIconLarge, NULL, 1) == 0)
		return NULL;

	return hIconLarge;		
}

HICON CFunc::GetNotFountFileIcon()
{
	CString szIconFile;
	szIconFile.Format("%s\\desktop\\not_fount_file.ico", CFunc::GetModulePath());

	HICON hIcon = ::LoadIcon(AfxGetApp()->m_hInstance, szIconFile);

	return hIcon;
}

HICON CFunc::GetFolderIcon()
{
	CString szIconFile;
	szIconFile.Format("%s\\desktop\\icon_folder.ico", CFunc::GetModulePath());

	HICON hIcon = ::LoadIcon(AfxGetApp()->m_hInstance, szIconFile);

	return hIcon;
}

BOOL CFunc::IsDirectory(CString strFilePath)
{
	DWORD dwResult = GetFileAttributes(strFilePath);

	if (dwResult & FILE_ATTRIBUTE_DIRECTORY)
		return TRUE;

	return FALSE;
}

CString CFunc::GetString(int nValue)
{
	CString strValue;
	strValue.Format("%d", nValue);

	return strValue;
}

CString CFunc::GetStartProgFixType(CString  strType)
{
	if (strType == "1")
		return "HKLM(Run)";
	else if (strType == "2")
		return "HKLU(Run)";
	else if (strType == "3")
		return "HKLM(RunOnce)";
	else if (strType == "4")
		return "HKLU(RunOnce)";
	else if (strType == "5")
		return "시작프로그램(Admin계정)";
	else if (strType == "6")
		return "시작프로그램(User계정)";
	else
		return "Unknown";
}

int CFunc::GetIntStartProgFixType(CString strType)
{
	if (strType == "HKLM(Run)")
		return 1;
	else if (strType == "HKLU(Run)")
		return 2;
	else if (strType == "HKLM(RunOnce)")
		return 3;
	else if (strType == "HKLU(RunOnce)")
		return 4;
	else if (strType == "시작프로그램(Admin계정)")
		return 5;
	else if (strType == "시작프로그램(User계정)")
		return 6;
	else
		return 7;
}

CString CFunc::GetTime()
{
	CString szTime;

    SYSTEMTIME s;
    GetLocalTime(&s);

	szTime.Format("%.4d-%.2d-%.2d %.2d:%.2d:%.2d",
		s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond);

	return szTime;
}

CString CFunc::GetStringStartProgFixType(CString strType)
{
	if (strType == "HKLM(Run)")
		return "1";
	else if (strType == "HKLU(Run)")
		return "2";
	else if (strType == "HKLM(RunOnce)")
		return "3";
	else if (strType == "HKLU(RunOnce)")
		return "4";
	else if (strType == "시작프로그램(Admin계정)")
		return "5";
	else if (strType == "시작프로그램(User계정)")
		return "6";
	else
		return "7";
}

CString CFunc::GetStartProgFixTypeInt(int nType)
{
	if (nType == 1)
		return "HKLM(Run)";
	else if (nType == 2)
		return "HKLU(Run)";
	else if (nType == 3)
		return "HKLM(RunOnce)";
	else if (nType == 4)
		return "HKLU(RunOnce)";
	else if (nType == 5)
		return "시작프로그램(Admin계정)";
	else if (nType == 6)
		return "시작프로그램(User계정)";
	else
		return "Unknown";
}

void CFunc::SetFixOnOff(int nPcNo, int nValue)
{
	char szcfgFile[255];
	sprintf(szcfgFile, "%s\\cfg\\ptbaseinfo.cfg", GetModulePath());

	char szPcNoText[20], szValue[2];
	sprintf(szPcNoText, "PC%d", nPcNo);
	sprintf(szValue, "%d", nValue);

	::WritePrivateProfileString(szPcNoText, "SPF", szValue, szcfgFile);	
}

CString CFunc::GetCurTime()
{
	CString strTime;

    SYSTEMTIME s;
    GetLocalTime(&s);

	strTime.Format("%.4d%.2d%.2d_%.2d%.2d%.2d",
		s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond);

	return strTime;
}

BOOL CFunc::IsSet(BYTE bByte, int nPos)
{
   BYTE bBitFormat;

    bBitFormat = (BYTE)Power(2, nPos - 1);
    return ((bByte & bBitFormat) == bBitFormat) ? TRUE : FALSE;
}

int CFunc::Power(int x, int y)
{
    int i, z = x;

    if (y == 0) return 1;

    for (i=0; i < y - 1; i++) z *= x;

    return z;
}

BOOL CFunc::IsSet(USHORT sShort, int nPos)
{
    USHORT sBitFormat;

    sBitFormat = (USHORT)Power(2, nPos - 1);

	return ((sShort & sBitFormat) == sBitFormat) ? TRUE : FALSE;
}

void CFunc::SetAddCommaString(const char *str_num, char *num_str)
{
	char szTemp[128] = {NULL}, szStrNum[64] = {NULL}, szNumStr[64] = {NULL};

	// 원본 문자열 설정
	strcpy(szStrNum, str_num);
	int iStrNumLen	= (int)strlen(str_num);
	int iCommaCnt	= iStrNumLen / 3;	// 총 콤마(',') 개수 구함
	int iDiffCnt	= iStrNumLen - 3 * iCommaCnt;
	int iArrayCnt	= 0;
	if(iDiffCnt != 0)	iArrayCnt	= iCommaCnt	+ 1;
	else				iArrayCnt	= iCommaCnt;

	char pszNewData[32][4] = {NULL};

	// 문자열 내부에 콤마 삽입
	int i, iLen, iNext = 0, iNextPos = 1;
	for(i=iArrayCnt-1; i>=0; i--)
	{
		if((iStrNumLen - 3 * iNextPos) > 0)
		{
			memcpy(pszNewData[i], str_num+(iStrNumLen-iNextPos*3), 3);
		}
		else
		{
			memcpy(pszNewData[i], str_num, iStrNumLen - 3 * (iNextPos-1));
		}
		iNextPos++;
	}

	// 콤마 삽입
	for(i=0; i<iArrayCnt; i++)
	{
		iLen = (int)strlen(pszNewData[i]);
		memcpy(szTemp+iNext, pszNewData[i], iLen);
		if((i+1) < iArrayCnt)	szTemp[iLen+iNext]	= ',';
		iNext	+= (iLen + 1);
	}

	// 값 설정
	strcpy(num_str, szTemp);
}

CString CFunc::GetAddCommaString(CString strNumber)
{
	CString strReturn ="";
	char strValue[256] = {NULL};
	SetAddCommaString(strNumber, strValue);
	strReturn = (LPCTSTR)strValue;
	return strReturn;
}

void CFunc::ExecuteIE(CString strUrl)
{
	CString strIEPath;
	strIEPath.Format("%s\\Internet Explorer\\iexplore.exe", CFunc::GetProgramFilesFolder());
	
	::ShellExecute(NULL, "open", strIEPath, strUrl, NULL, SW_SHOW);	
}

int CFunc::GetPUP()
{
	char szcfgFile[MAX_PATH];
	sprintf(szcfgFile, "%s\\cfg\\ptbaseinfo.cfg", CFunc::GetModulePath());

	return GetPrivateProfileInt("PCBASEINFO", "PUP", 0, szcfgFile);
}

BOOL CFunc::IsNumber(CString strText, int nTextLen)
{
	for (int i = 0; i < nTextLen; i++)
	{
		if (!isdigit(strText.GetAt(i)))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CFunc::IsAlphaOrNumber(CString strText, int nTextLen)
{
	for (int i = 0; i < nTextLen; i++)
	{
		if (!isalpha(strText.GetAt(i)) && !isdigit(strText.GetAt(i)))
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CFunc::IsAlpha(CString strText, int nTextLen)
{
	for (int i = 0; i < nTextLen; i++)
	{
		if (!isalpha(strText.GetAt(i)))
		{
			return FALSE;
		}
	}

	return TRUE;
}

#ifdef _USE_HTTP_DOWN
BOOL CFunc::HTTPDown(char *szUrl, char *szLocal, DWORD dwFileLen)
{
     HINTERNET hInternet, hURL;
     HANDLE hFile;
     DWORD Size;
     DWORD dwRead, dwWritten, dwRecv = 0;

     char buf[100000];
 
     // 인터넷 연결
     hInternet = InternetOpen("MWHTTP", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
     if (hInternet == NULL) 
     {
		 return FALSE;
     }

     // URL을 연다
     hURL = InternetOpenUrl(hInternet, szUrl, NULL, 0, INTERNET_FLAG_RELOAD, 0);
     if (hURL == NULL) 
     {
		 InternetCloseHandle(hInternet);
         return FALSE;
     }

     char szStateCode[256];
     szStateCode[0] = 0x00;
     DWORD dwStateCodeSize = sizeof(szStateCode);

     BOOL bQuery = HttpQueryInfo(hURL, HTTP_QUERY_STATUS_CODE, &szStateCode, &dwStateCodeSize, NULL);
     if (!bQuery)
     {
		 InternetCloseHandle(hInternet);
		 return FALSE;
     }

	 if(atoi(szStateCode) != 200)
	 {
		 InternetCloseHandle(hInternet);
		 return FALSE;
	 }

     DWORD dwFileSize = 0;
	 DWORD dwDataSize = sizeof(dwFileSize);
	 bQuery = HttpQueryInfo(hURL, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, &dwFileSize, &dwDataSize, NULL);
	 if (!bQuery)
	 {
		 InternetCloseHandle(hInternet);
         return FALSE;
	 }

	 // 로컬 파일을 생성한다.
	 hFile = CreateFile(szLocal, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	 int nPersent = 0;
	 do 
	 {
         // 다운로드받아 로컬 파일에 기록한다.
		 InternetQueryDataAvailable(hURL, &Size, 0, 0);

		 InternetReadFile(hURL, buf, Size, &dwRead);

		 WriteFile(hFile, buf, dwRead, &dwWritten, NULL);

	 } while (dwRead != 0);

	 InternetCloseHandle(hURL);

	 InternetCloseHandle(hInternet);

	 CloseHandle(hFile);

	 return TRUE;
}
#endif


HRESULT CFunc::ExeCreateShortCut(LPCSTR szSrcFile, LPSTR szLnkFile, LPSTR szArgument, LPSTR szDesc) 
{ 
	HRESULT hr; 
	IShellLink *pSl; 
	IPersistFile *pPf; 
	WCHAR wszLnkFile[MAX_PATH]={0,}; 

	// IShellLink 객체를 생성하고 포인터를 구한다. 
	hr=CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&pSl); 
	if (FAILED(hr)) 
		return E_FAIL; 

	// 쇼트컷의 대상체와 설명을 설정한다. 
	pSl->SetPath(szSrcFile); 
	pSl->SetDescription(szDesc); 
	pSl->SetArguments(szArgument); 

	// 저장하기 위해 IPersistFile 객체를 생성한다. 
	hr=pSl->QueryInterface(IID_IPersistFile, (void **) &pPf); 
	if (FAILED(hr)) 
	{
		pSl->Release(); 
		return E_FAIL; 
	} 

	// 유니코드로 파일 패스를 변경한 후 저장한다. 
	MultiByteToWideChar(CP_ACP, 0, szLnkFile, -1, wszLnkFile, MAX_PATH); 
	hr=pPf->Save(wszLnkFile, TRUE); 

	// 객체 해제 
	pPf->Release(); 
	pSl->Release(); 
	return hr; 
} 