/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "StdAfx.h"
#include <dmusicc.h>
#include <dmusici.h>


/**\brief
 * DMusic�����ֲ�����
 */
class EGMusic
{
public:
	EGMusic();
	~EGMusic();

	static IDirectMusicSegment* LoadMIDISegment(IDirectMusicLoader* pLoader, WCHAR *wszMidiFileName );

	/**\brief
	 * ��ʼ��DMUSIC
	 */
	static BOOL InitMusic();

	/**\brief
	 * ����MIDI�����ļ�
	 */
	BOOL LoadMusic(WCHAR *);
	BOOL LoadMusic(char* filename){return LoadMusic(WChar(filename));}

	/**\brief
	 * ��ʼ����
	 */
	BOOL Play(int start=0);

	/**\brief
	 * ֹͣ����
	 */
	BOOL Stop();

	/**\brief
	 * ��ͣ����
	 */
	BOOL Pause();

	/**\brief
	 * ��ͣ��������������
	 */
	BOOL Resume();

	/**\brief
	 * �Ƿ����ڲ���
	 */
	BOOL IsPlay();

	/**\brief
	 * �õ���ǰ���ֶ����ָ��
	 */
	static EGMusic* GetSysMusic(){return m_pMusic;}

	void	SetMusic(BOOL music){bMusic = music;};
	BOOL	GetMusic(){return bMusic;};

private:
	//�Ƿ�������
	static BOOL bMusic;

	//�������Ƿ��Ѵ���
	static BOOL bExist;
	
	//�Ƿ񲥷�
	static BOOL bPlay;
	static IDirectMusicPerformance* g_pPerf;
	static IDirectMusicLoader* g_pLoader;
	IDirectMusicSegment* g_pMIDISeg;

	//��ͣ��
	MUSIC_TIME PauseTime;

	//�ļ�
	WCHAR MusicFile[MAX_PATH];

	// ����ָ��
	static EGMusic* m_pMusic;

	static IDirectMusicPerformance* CreatePerformance(void);
	static IDirectMusicLoader* CreateLoader(void);
};

#endif
