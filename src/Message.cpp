#include "stdafx.h"
#include "message.h"
#include "sceneMgr.h"
#include "guimgr.h"
#include "music.h"

Message* Message::m_pMessage=NULL;

Message::Message(void)
{
	m_pMessage=this;
}


Message::~Message(void)
{
}

/**\brief
 * ִ�е�ǰ��Ϣ
 */
void Message::Run()
{
	if(GetMsgNum()<=0)return;

	switch(m_dQueue[0].msg)
	{
	case MSG_PLAY_MUSIC:
		if(EGMusic::GetSysMusic()->IsPlay())EGMusic::GetSysMusic()->Stop();
		EGMusic::GetSysMusic()->LoadMusic(m_dQueue[0].str1);
		EGMusic::GetSysMusic()->Play();
		Delete();
		break;
	case MSG_STOP_MUSIC:
		if(EGMusic::GetSysMusic()->IsPlay())EGMusic::GetSysMusic()->Stop();
		Delete();
		break;
	case MSG_PAUSE_MUSIC:
		if(EGMusic::GetSysMusic()->IsPlay())EGMusic::GetSysMusic()->Pause();
		Delete();
		break;
	case MSG_RESUME_MUSIC:
		if(!EGMusic::GetSysMusic()->IsPlay())EGMusic::GetSysMusic()->Resume();
		Delete();
		break;

	case MSG_FADE:
		GUIMgr::GetSysGUIMgr()->BeginFade();
		Delete();
		break;

	case MSG_PLAYAVI:
		SceneMgr::GetSysSceneMgr()->SetScene(SCE_AVI);
		SceneMgr::GetSysSceneMgr()->LoadIni(m_dQueue[0].str1,m_dQueue[0].str2);
		Delete();
		break;

	case MSG_TITLE:
		SceneMgr::GetSysSceneMgr()->SetScene(SCE_TITLE);
		SceneMgr::GetSysSceneMgr()->LoadIni(m_dQueue[0].str1,m_dQueue[0].str2);
		Delete();
		break;

	case MSG_SELCHAR:
		SceneMgr::GetSysSceneMgr()->SetScene(SCE_SELCHAR);
		SceneMgr::GetSysSceneMgr()->LoadIni(m_dQueue[0].str1,m_dQueue[0].str2);
		Delete();
		break;

	case MSG_OPENAIR:
		SceneMgr::GetSysSceneMgr()->SetScene(SCE_OPENAIR);
		SceneMgr::GetSysSceneMgr()->LoadIni(m_dQueue[0].str1,m_dQueue[0].str2);
		Delete();
		break;

	case MSG_EXIT:
		PostQuitMessage(0);
		Delete();
		break;
	}

}
