/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "Timer.h"

EGTimer* EGTimer::m_pTimer=NULL;

EGTimer::EGTimer(){m_pTimer=this;}
EGTimer::~EGTimer(){}

/**\brief
 * ��ʱ���ĳ�ʼ��
 *
 * ���ϵͳ�и߷ֱ��ʼ�ʱ����������tickƵ�ʣ�����TRUE��
 * ����������FALSE,����ʹ�øü�ʱ����
 */
BOOL EGTimer::Init()
{
	if (!QueryPerformanceFrequency(&m_ticksPerSecond))
	{
		return FALSE;// ϵͳ��֧�ָ߷ֱ��ʼ�ʱ��
	}

	else
	{
		QueryPerformanceCounter(&m_startTime);
		return TRUE;
	}
}



/**\brief
 * ��þ�����ʱ��
 */
float EGTimer::GetElapsedSeconds()
{
	static LARGE_INTEGER s_lastTime = m_startTime;
	LARGE_INTEGER currentTime;

	QueryPerformanceCounter(&currentTime);

	float seconds=(float)(currentTime.QuadPart-s_lastTime.QuadPart)/(float)m_ticksPerSecond.QuadPart;

	// ��ʱ����λ
	s_lastTime = currentTime;

	return seconds;
}


/**\brief
 * ��ȡ֡��
 */
float EGTimer::GetFPS(unsigned long elapsedFrames)
{
	static LARGE_INTEGER s_lastTime = m_startTime;
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	float fps = (float)elapsedFrames * (float)m_ticksPerSecond.QuadPart / ((float)currentTime.QuadPart - (float)s_lastTime.QuadPart);
	// ���ö�ʱ��
	s_lastTime = currentTime;
	return fps;
} 


/**\beief
 * ����֡��
 */
float EGTimer::LockFPS(unsigned char targetFPS)
{
	if (targetFPS <= 0)targetFPS = 1;

	static LARGE_INTEGER s_lastTime = m_pTimer->m_startTime;
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	float   fps = m_pTimer->GetFPS();

	// ��ʱ�Ա�֤�̶���֡��
	while (fps > (float)targetFPS)
	{
		Sleep(1);
		QueryPerformanceCounter(&currentTime);
		fps=(float)m_pTimer->m_ticksPerSecond.QuadPart/((float)(currentTime.QuadPart-s_lastTime.QuadPart));
	}
	// ���ö�ʱ��
	s_lastTime = currentTime;

	return fps;
}
