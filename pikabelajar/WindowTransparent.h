
#ifndef __WINDOWTRANSPARENT_H
#define __WINDOWTRANSPARENT_H

#define MWT_MIN_FACTOR (0)
#define MWT_MAX_FACTOR (0xFF)

BOOL MakeWindowTransparent(HWND hWnd, int nPos);
BOOL SetTransparentInitDlg(HWND hWnd);
BOOL SetTransparentDlgSHOW(HWND hWnd);
BOOL SetTransparentDlgHIDE(HWND hWnd);
#endif