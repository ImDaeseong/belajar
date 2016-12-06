#include "stdafx.h"
#include "AudioPlayer.h"

CAudioPlayer::CAudioPlayer()
{
}

CAudioPlayer::~CAudioPlayer()
{
}

BOOL CAudioPlayer::Play()
{
	mciSendCommand(m_dwDeviceID,MCI_PLAY,MCI_NOTIFY, (DWORD)(LPVOID) &m_mciPlayParms);	
	
	return TRUE;
}

BOOL CAudioPlayer::Stop()
{
	mciSendCommand(m_dwDeviceID, MCI_CLOSE, 0, NULL);
	return TRUE;
}

BOOL CAudioPlayer::Pause()
{
	mciSendCommand(m_dwDeviceID,MCI_PAUSE,MCI_NOTIFY,(DWORD)(LPVOID) &m_mciPlayParms);	
	return TRUE;
}

BOOL CAudioPlayer::Open(CString strFile)
{
	m_mciOpenParms.lpstrElementName = (LPSTR)strFile.operator LPCTSTR();//화일 설정
	m_mciOpenParms.lpstrDeviceType = "MPEGVideo";//디바이스 를 waveaudio로
	mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT|MCI_OPEN_TYPE,(DWORD)(LPVOID)&m_mciOpenParms);//MCI_OPEN 명령을 준다.
	m_dwDeviceID = m_mciOpenParms.wDeviceID;//열린 디바이스 아이디를 받느다.
	
	MCI_STATUS_PARMS mciStatusParms;
	mciStatusParms.dwItem = MCI_STATUS_LENGTH;
	
	mciSendCommand(m_dwDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);
	m_nTotalTime = (LONG)mciStatusParms.dwReturn;

	return TRUE;
}

BOOL CAudioPlayer::Open(char *pFile)
{
	m_mciOpenParms.lpstrElementName = pFile;//화일 설정
	m_mciOpenParms.lpstrDeviceType = "MPEGVideo";//디바이스 를 waveaudio로
	mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT|MCI_OPEN_TYPE,(DWORD)(LPVOID)&m_mciOpenParms);//MCI_OPEN 명령을 준다.
	m_dwDeviceID = m_mciOpenParms.wDeviceID;//열린 디바이스 아이디를 받느다.
	
	MCI_STATUS_PARMS mciStatusParms;
	mciStatusParms.dwItem = MCI_STATUS_LENGTH;
	
	mciSendCommand(m_dwDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);
	m_nTotalTime = (LONG)mciStatusParms.dwReturn;

	return TRUE;
}

DWORD CAudioPlayer::GetRunningTime()
{
	DWORD nTime;
	
	MCI_STATUS_PARMS mciStatusParms;
	mciStatusParms.dwItem = MCI_STATUS_LENGTH;
	
	mciSendCommand(m_dwDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);
	nTime = (LONG)mciStatusParms.dwReturn;
	
	return nTime;
}

DWORD CAudioPlayer::GetMode()
{
	DWORD dwMode;
	
	MCI_STATUS_PARMS mciStatusParms;
	mciStatusParms.dwItem = MCI_STATUS_MODE;
	
	mciSendCommand(m_dwDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);
	dwMode = (LONG)mciStatusParms.dwReturn;	
	
	return dwMode;
}

DWORD CAudioPlayer::GetPosition()
{
	DWORD nTime;
	
	MCI_STATUS_PARMS mciStatusParms;
	mciStatusParms.dwItem = MCI_STATUS_POSITION;
	
	mciSendCommand(m_dwDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms);
	nTime = (LONG)mciStatusParms.dwReturn;	
	
	return nTime;
}

void CAudioPlayer::SetPosition(DWORD dwPosition)
{
	MCI_SEEK_PARMS mciSeekParms;
	mciSeekParms.dwTo = dwPosition;
	
	mciSendCommand(m_dwDeviceID, MCI_SEEK, MCI_TO, (DWORD)(LPVOID)&mciSeekParms);
	Play();
}

void CAudioPlayer::SetVolume(DWORD dwVolume)
{
	MCI_DGV_SETAUDIO_PARMS p; 
	
	if( dwVolume > 100 ) dwVolume = 100; 
	if( dwVolume < 0   ) dwVolume = 0; 
	
	dwVolume *= 10; 
	
	p.dwCallback = 0; 
	p.dwItem     = MCI_DGV_SETAUDIO_VOLUME; 
	p.dwValue    = dwVolume; 
	p.dwOver     = 0; 
	p.lpstrAlgorithm = NULL; 
	p.lpstrQuality   = NULL; 
	
	mciSendCommand( m_dwDeviceID, MCI_SETAUDIO,	MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)&p ); 
}

int CAudioPlayer::GetVolume()
{
	MCI_STATUS_PARMS p; 
	
	p.dwCallback = 0; 
	p.dwItem     = MCI_DGV_STATUS_VOLUME; 
	mciSendCommand( m_dwDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)&p ); 
	
	return (int)(p.dwReturn/10);  // Volume: 0 - 1000  
}
