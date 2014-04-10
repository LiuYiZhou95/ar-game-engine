/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _SOUND_H_
#define _SOUND_H_

#include "StdAfx.h"

#define DIRECTSOUND_VERSION 0x0800
#include <dmusicc.h>
#include <dmusici.h>
#include <d3d8types.h>


/**\brief
 *  ��Ч��
 */
class EGSound
{
public:
	// ��̨������
	LPDIRECTSOUNDBUFFER DSSoundFX;

public:
	EGSound();
	~EGSound();

	
	/**\brief
	 * ��ʼ�������豸
	 *
	 *\param	_hWnd	���ھ��
	 *\return	BOOL	��ʼ���Ƿ�ɹ�
	 */
	static BOOL InitDirectSound(HWND _hWnd);


	/**\brief
	 * ����������������
	 */
	static BOOL CreatePrimarySoundBuffer();


	/**\brief
	 * �ͷ������豸
	 */
	static void ReleaseDirectSound(void);


	/**\brief
	 * ��Ч����
	 */
	static void EnableSound(BOOL sw){EGSound::bEnable=sw;}


	/**\brief
	 * װ������
	 *
	 *\param	filename	�����ļ���
	 *\return	BOOL		�����Ƿ�ɹ�
	 */
	BOOL LoadSoundFX(char *filename);


	/**\brief
	 * ��������
	 *
	 *\param	loop	Ϊ-1ʱ����ѭ������
	 */
	void Play(DWORD loop=0);


	/**\brief
	 * ֹͣ����
	 */
	void Stop();


	/**\brief
	 * �������Ƿ����ڲ���
	 */
	BOOL IsPlaying();


	/**\brief
	 * ���һ��WAV����������
	 *
	 *\param	lpSoundBuffer	����������
	 *\param	filename		�����ļ���
	 *\return	BOOL			����Ƿ�ɹ�
	 */
	BOOL LoadSoundBuffer(LPDIRECTSOUNDBUFFER lpSoundBuffer,char *filename);


private:
	// ������Ч
	static BOOL bEnable;

	// �Ƿ��Ѿ���ʼ��
	static BOOL bExist;

	// �豸
	static LPDIRECTSOUND lpDSound;

	// ��������
	static LPDIRECTSOUNDBUFFER lpPrimarySoundBuffer;
};


#endif
