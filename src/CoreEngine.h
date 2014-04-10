/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _CORE_ENGINE_H_
#define _CORE_ENGINE_H_

#include "input.h"
#include "font.h"
#include "camera.h"
#include "timer.h"
#include "sound.h"
#include "music.h"
#include "StaticObjMgr.h"
#include "role.h"
#include "monstersMgr.h"
#include "SceneMgr.h"
#include "GUIMgr.h"
#include "Message.h"
#include "ARMgr.h"

/*! ������*/
class CoreEngine
{
public:
	CoreEngine(void);
	~CoreEngine(void);

	BOOL Init(void);				// ��ʼ��������opengl����ĳ�ʼ��

	void SetProjection(int iFOVAngle,int iHeight);// ���þ���

	void Prepare(void);				// ��Ⱦǰ��׼������

	void Render(void);				// 3D��Ⱦ

	void SwapBuffer(void){::SwapBuffers(m_hDC);}// ����������

	void Close(void);				// �ر�����

	void SetStop(BOOL stop){m_bStop = stop;};

	BOOL GetStop(){return m_bStop;};

	static CoreEngine * GetSysCoreEngine(){return m_cCoreEngine;};

private:

	static CoreEngine * m_cCoreEngine;

	BOOL InitObject(void);			// ��Ϸ�е�ʵ������ĳ�ʼ��

	BOOL SetDCPixelFormat(void);	// ����opengl���ظ�ʽ


	HDC			m_hDC;		// �豸���

	HGLRC		m_hRC;		// ��Ⱦ���

	HZFont*		m_pFont;	// ����

	EGInput*		m_pInput;	// ����ϵͳ

	EGTimer *		m_pTimer;	// ��ʱ��

	EGCamera		camera;		// �����

	EGMusic		m_cMusic;	// ��������

	SceneMgr	m_cSceneMgr;// ��������

	GUIMgr		m_cGUIMgr;	// �������

	Message		m_cMessage;	// ��Ϣ����

	ARMgr	m_arMgr; //��Ƶ����

	BOOL	m_bStop;	//��Ϸ��ͣ
};
#endif 
