/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "aviplayer.h"


AVIPlayer::AVIPlayer(void)
{
	m_hWnd=NULL;
	m_hmmWnd=NULL;
}


AVIPlayer::~AVIPlayer(void)
{
	Stop();
	m_hWnd=NULL;
}


BOOL AVIPlayer::Init(HWND _hWnd)
{
	if(_hWnd)
	{
		m_hWnd=_hWnd;
		return TRUE;
	}
	else 
		return FALSE;
}
