#pragma once

class CResourcBitmapgif : public CBitmap  
{
public:
	CResourcBitmapgif();
	virtual ~CResourcBitmapgif();

public:
	BOOL Load(CString sFilePathName);
	BOOL Load(UINT ResourceName, CString ResourceType);
	void FreePictureData();
	BOOL LoadPictureData(BYTE* pBuffer, int nSize);
	BOOL CreatePanoramaBitmap();

private:
	IPicture* m_IPicture; 
	LONG      m_Height; 
	LONG      m_Weight;
	LONG      m_Width;  
};