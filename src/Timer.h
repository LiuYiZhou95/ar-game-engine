/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#include "StdAfx.h"


/**\brief
 * �߷ֱ��ʼ�ʱ����
 */
class EGTimer
{
public:
	EGTimer();
	~EGTimer();

	// ������ʱ�䣬��λ����
	float	m_fTime;

	// ֡��
	float	m_fFPS;


	/**\brief
	 * ��ʱ���ĳ�ʼ��
	 *
	 * ���ϵͳ�и߷ֱ��ʼ�ʱ����������tickƵ�ʣ�����TRUE��
	 * ����������FALSE,����ʹ�øü�ʱ����
	 */
	BOOL Init();


	/**\brief
	 * ��þ�����ʱ��
	 */
	float GetElapsedSeconds();


	/**\brief
	 * ��ȡ֡��
	 */
	float GetFPS(unsigned long elapsedFrames=1);


	/**\beief
	 * ����֡��
	 */
	static float LockFPS(unsigned char targetFPS);


	/**\brief
	 * ˢ�¼�ʱ��
	 */
	void Update(){m_fTime=GetElapsedSeconds();m_fFPS=GetFPS();}


	/**\brief
	 * ȡ�õ�ǰ��ʱ����ָ��
	 */
	static EGTimer* GetSysTimer(){return m_pTimer;}


private:
	LARGE_INTEGER   m_startTime;
	LARGE_INTEGER   m_ticksPerSecond;

	static EGTimer*	m_pTimer;
};

#endif
