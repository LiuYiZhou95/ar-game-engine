/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "ARMgr.h"
#include "general.h"

ARMgr* ARMgr::m_pARMgr = NULL;

ARMgr::ARMgr(void)
{
	arMgrThread = 0;
	cameState = FALSE;
	m_pARMgr = this;
}

ARMgr::~ARMgr(void)
{}

/** ���ж����̵߳ľ�̬���� */
void ARMgr::runFun(ARMgr vm)
{
	for(;;)
	{
		if(vm.cameState)
		{
			if(!vm.GetVideoCapture()->getRunState())
				vm.GetVideoCapture()->run();
		}
		else
		{
			/*** �ͷ���Դ **/
			if(vm.GetVideoCapture()->getRunState())
			{
				vm.GetVideoCapture()->cleanup();
			}
			/*** ���������ٶ� **/
			Sleep(300);
		}
	}
}

/** ��ǰ��Ƶ�����������̵߳������к��� **/
void ARMgr::Init()
{
	m_pVideoCapture.LoadIni("ini\\ARParam.ini","Camera");
	m_pMotionAnalysis.init();

	if(!arMgrThread)
	{
		/** �����߳�,������ִ�м�������ͷ���� **/
		arMgrThread = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)runFun, ARMgr::m_pARMgr, 0, 0);
	}
}