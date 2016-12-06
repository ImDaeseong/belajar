#include "stdafx.h"
#include "ResourcBitmapgif.h"

#define HIMETRIC_INCH 2540
#define ERROR_TITLE "CPanoramaBitmap Error" 

CResourcBitmapgif::CResourcBitmapgif()
{
	m_IPicture = NULL;
	m_Height = 0;
	m_Weight = 0;
	m_Width = 0;
}

CResourcBitmapgif::~CResourcBitmapgif()
{
	if(m_IPicture != NULL) FreePictureData(); 
}

//경로에 있는 gif,jpg 이미지를 읽어온다.
BOOL CResourcBitmapgif::Load(CString sFilePathName)
{
	DeleteObject();

	BOOL bResult = FALSE;
	CFile PictureFile;
	CFileException e;
	int	nSize = 0;

	if(m_IPicture != NULL) FreePictureData();
	
	if(PictureFile.Open(sFilePathName, CFile::modeRead | CFile::typeBinary, &e))
	{
		nSize = PictureFile.GetLength();
		BYTE* pBuffer = new BYTE[nSize];
	
		if(PictureFile.Read(pBuffer, nSize) > 0)
		{
			if(LoadPictureData(pBuffer, nSize))	bResult = TRUE;
		}

		PictureFile.Close();
		delete [] pBuffer;
	}
	else
	{
		bResult = FALSE;
	}

	m_Weight = nSize;

	if(m_IPicture != NULL) 
	{ 
		m_IPicture->get_Height(&m_Height);
		m_IPicture->get_Width(&m_Width);
	    m_Height = MulDiv(m_Height, 96, HIMETRIC_INCH);
	    m_Width  = MulDiv(m_Width,  96, HIMETRIC_INCH);
	}
	else 
	{
		m_Height = 0;
		m_Width = 0;
		bResult = FALSE;
	}

	if(bResult) return(CreatePanoramaBitmap());
	else return(bResult);
}

//리소스 DLL에 등록되어 있는 gif,jpg 이미지를 읽어온다.
BOOL CResourcBitmapgif::Load(UINT ResourceName, CString ResourceType)
{
	//DLL의 인스턴스를 가져와야 한다.  
	HINSTANCE hinstLib;
	hinstLib = AfxGetInstanceHandle();
   	
	DeleteObject();

	BOOL bResult = FALSE;

	HGLOBAL		hGlobal = NULL;
	HRSRC		hSource = NULL;
	LPVOID		lpVoid  = NULL;
	int			nSize   = 0;

	if(m_IPicture != NULL) FreePictureData(); 

	if(ResourceType=="BMP")
		return(FALSE);

	if(!hSource) hSource = FindResource(hinstLib, MAKEINTRESOURCE(ResourceName), ResourceType);

	if(hSource == NULL)
	{
		return(FALSE);
	}

	hGlobal = LoadResource(hinstLib, hSource);
	if(hGlobal == NULL)
	{
		return(FALSE);
	}

	lpVoid = LockResource(hGlobal);
	if(lpVoid == NULL)
	{
		return(FALSE);
	}

	nSize = (UINT)SizeofResource(hinstLib, hSource);
	if(LoadPictureData((BYTE*)hGlobal, nSize)) bResult = TRUE;

	UnlockResource(hGlobal); 
	FreeResource(hGlobal);

	m_Weight = nSize; 

	if(m_IPicture != NULL) 
	{ 
		m_IPicture->get_Height(&m_Height);
		m_IPicture->get_Width(&m_Width);
	    
	    m_Height = MulDiv(m_Height, 96, HIMETRIC_INCH);
	    m_Width  = MulDiv(m_Width,  96, HIMETRIC_INCH);
	}
	else 
	{
		m_Height = 0;
		m_Width = 0;
		bResult = FALSE;
	}

	if(bResult) return(CreatePanoramaBitmap());
	else return(bResult);
}

void CResourcBitmapgif::FreePictureData()
{
	if(m_IPicture != NULL)
	{
		m_IPicture->Release();
		m_IPicture = NULL;
		m_Height = 0;
		m_Weight = 0;
		m_Width = 0;
	}
}

BOOL CResourcBitmapgif::LoadPictureData(BYTE *pBuffer, int nSize)
{
	BOOL bResult = FALSE;

	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nSize);

	if(hGlobal == NULL)
	{
		return(FALSE);
	}

	void* pData = GlobalLock(hGlobal);
	memcpy(pData, pBuffer, nSize);
	GlobalUnlock(hGlobal);

	IStream* pStream = NULL;

	if(CreateStreamOnHGlobal(hGlobal, TRUE, &pStream) == S_OK)
	{
		HRESULT hr;
		if((hr = OleLoadPicture(pStream, nSize, FALSE, IID_IPicture, (LPVOID *)&m_IPicture)) == E_NOINTERFACE)
		{
			return(FALSE);
		}
		else 
		{
			pStream->Release();
			pStream = NULL;
			bResult = TRUE;
		}
	}

	GlobalFree(hGlobal);//FreeResource(hGlobal); //메모리 해제 않됨
	
	return(bResult);
}

BOOL CResourcBitmapgif::CreatePanoramaBitmap()
{
	BOOL bResult = FALSE;
	ILockBytes *Buffer = 0;
	IStorage   *pStorage = 0;
	IStream    *FileStream = 0;
	BYTE	   *BufferBytes;
	BYTE	   *pBufferBytes;
	STATSTG		BytesStatistics;
	DWORD		OutData;
	long		OutStream;
	CFile		BitmapFile;	CFileException e;
	double		SkipFloat = 0;
	DWORD		ByteSkip = 0;
	_ULARGE_INTEGER RealData;

	CreateILockBytesOnHGlobal(NULL, TRUE, &Buffer); 

	HRESULT hr = ::StgCreateDocfileOnILockBytes(Buffer,
				 STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, &pStorage);

	hr = pStorage->CreateStream(L"PICTURE",
		 STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, 0, &FileStream);

	m_IPicture->SaveAsFile(FileStream, TRUE, &OutStream); 
	FileStream->Release();
	pStorage->Release();
	Buffer->Flush(); 

	Buffer->Stat(&BytesStatistics, STATFLAG_NONAME);

	SkipFloat = (double(OutStream) / 512); 
	if(SkipFloat > DWORD(SkipFloat)) ByteSkip = (DWORD)SkipFloat + 1;
	else ByteSkip = (DWORD)SkipFloat;
	ByteSkip = ByteSkip * 512; 

	ByteSkip = (DWORD)(BytesStatistics.cbSize.QuadPart - ByteSkip);

	RealData.LowPart = 0;
	RealData.HighPart = 0;
	RealData.QuadPart = ByteSkip;
	BufferBytes = (BYTE*)malloc(OutStream);
	pBufferBytes = BufferBytes;
	if(BufferBytes == NULL)
	{
		Buffer->Release();
	}

	Buffer->ReadAt(RealData, BufferBytes, OutStream, &OutData);

	BITMAPFILEHEADER  bmfHeader;
	memcpy(&bmfHeader,BufferBytes,sizeof(bmfHeader));


	DWORD bmfHeaderSize = sizeof(BITMAPFILEHEADER);
	BufferBytes += bmfHeaderSize;

	
	BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)BufferBytes ;
	BITMAPINFO &bmInfo = *(LPBITMAPINFO)BufferBytes ;


	int nColors = bmiHeader.biClrUsed ? bmiHeader.biClrUsed : 
						1 << bmiHeader.biBitCount;

	LPVOID lpDIBBits;
	if( bmInfo.bmiHeader.biBitCount > 8 )
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) + 
			((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);

	CClientDC dc(NULL);

	HBITMAP hBmp = CreateDIBitmap(dc.m_hDC,	
				&bmiHeader,			
				CBM_INIT,			
				lpDIBBits,			
				&bmInfo,			
				DIB_RGB_COLORS);	


	Attach(hBmp);
	Buffer->Release();

	if (pBufferBytes)
	{
		free(pBufferBytes);
	}

	FreePictureData();

	return TRUE;
}
