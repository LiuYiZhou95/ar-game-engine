/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _ARMGR_H_
#define _ARMGR_H_
#include "VideoCapture.h"
#include "MotionAnalysis.h"

/**�Ӿ�����������*/
class ARMgr
{
public:
	ARMgr(void);
	~ARMgr(void);


	/** ��������ͷ״̬ **/
	void setCameraState(BOOL state)	{	cameState = state;}

	/** ��ȡ����ͷ״̬ **/
	BOOL getCameraState(){	return cameState;	}
		
	/** ������Ƶ�������߳� */
	void Init();

	/** ������Ƶ������ */
	static ARMgr * GetSysARMgr(){return m_pARMgr;};
	
	/** ��������ͷ��׽�ӿ� */
	VideoCapture * GetVideoCapture(){return &m_pVideoCapture;};

	/** ��������ͷ��׽�ӿ� */
	MotionAnalysis * GetMotionAnalysis(){return &m_pMotionAnalysis;};

private:

	BOOL cameState;
	
	static ARMgr * m_pARMgr;

	/** ֡��������Ҫ����������ͷ��ȡͼƬ���ݴ���Ķ������� */
	MotionAnalysis m_pMotionAnalysis;

	/** ֡��׽����Ҫ���������ͷ��ȡͼƬ���� */
	VideoCapture m_pVideoCapture;

	/** �Ӿ���������ϵͳ�߳� */
	HANDLE arMgrThread;

	/** �Ӿ���������ϵͳ�߳�ID **/
	LPDWORD * lpThreadId;

	/** ���ж����̵߳ľ�̬���� **/
	static void runFun(ARMgr vm);
};
#endif