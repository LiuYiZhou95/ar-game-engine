/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __GAME_APP_H__
#define __GAME_APP_H__

#include "CoreEngine.h"
#include "Ime.h"
#include "IniFile.h"


/*! Ӧ�ó����� */
class GameApp  
{
public:
	GameApp(void);
	~GameApp(void);

	BOOL	Init(EGSWindowInfo _sWinInfo);	// ��ʼ�����򣬴��ڡ������

	/**\brief
	 * ��������
	 *
	 *\param	_sWinInfo	������Ϣ
	 *\return	BOOL		�����Ƿ�ɹ�
	 */
	BOOL	CreateGLWindow(EGSWindowInfo _sWinInfo);

	/**\brief
	 * ������Ϣ������
	 */
	LRESULT WINAPI MessageHandler(HWND hWnd,UINT message,WPARAM  wParam, LPARAM lParam);

	void Run(void);				// �������ѭ��


private:
	EGSWindowInfo	m_sWinInfo;		// ������Ϣ

	MSG			msg;			// ��Ϣ
	
	BOOL		m_bActive;		// �����Ƿ��ڻ״̬

	CoreEngine	m_coreEngine;		// ��Ϸ������ʵ��

	void KillGLWindow(void);	// ���ٴ���
};


#endif
