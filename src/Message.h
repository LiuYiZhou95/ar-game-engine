/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <deque>
using namespace std;


#define SYS_MESSAGE (Message::GetSysMessage())

/*\brief
 * ��Ϣ���͵Ķ���
 */
typedef enum MESSAGE_
{
	MSG_NULL=0,			//����Ϣ

	MSG_PLAYAVI,		//������Ƶ����(str1=filename,str2=index)
	MSG_TITLE,			//������Ļ����(str1=filename,str2=index)
	MSG_SELCHAR,		//�����ɫѡ�񳡾�
	MSG_OPENAIR,		//�������ⳡ��(str1=filename,str2=index)
	MSG_EXIT,			//�˳�

	MSG_LOADMAP,		//�����ͼ
	MSG_SAVEMAP,		//�洢��ͼ

	MSG_MOVE,			//����			(p1=x, p2=y)
	MSG_SETDIR,			//�������﷽��	(p1=����)
	MSG_SETPOSITION,	//��������λ��	(p1=x, p2=y)
	MSG_PLAYERSHOW,		//����������ʾ��� (p1=bShow)
	MSG_LOADPLAYER,		//��ini�ļ���������(p1=rolenum s1=filename s2=index)

	MSG_ADDMONEY,		//�ı��Ǯ		(p1=money)
	MSG_ADDOBJECT,		//��������		(s1=������ p1=num)
	MSG_DELOBJECT,		//ɾ������		(s1=������ p1=num)
	MSG_ADDMAGIC,		//����ħ��		(s1=ħ����)
	MSG_DELMAGIC,		//ɾ��ħ��      (s1=ħ����)

	MSG_MOVENPCTO,		//NPC�ƶ���		(s1=Npc����, p1=x, p2=y)
	MSG_MOVENPC,		//NPC�ƶ�		(s1=Npc����, p1=x, p2=y)
	MSG_SETNPCPOS,		//����NPCλ��	(p1=x, p2=y)
	MSG_SETNPCDIR,		//����NPC����	(p1=����);
	MSG_SETNPCSTEP,		//����NPC����	(p1=����);
	MSG_ADDNPC,			//����NPC		(s1=filename p1=id, p2=x, p3=y)
	MSG_DELNPC,			//ɾ��NPC		(s1=Npc����)
	MSG_SETNPCACTIVE,	//����NPC����	(s1=Npc����, p1=bActive)
	MSG_SETNPCSHOW,		//����NPC��ʾ���	(s1=Npc����, p1=bShow)
	MSG_SETNPCSCRIPT,	//����NPC�ű�		(s1=Npc����, s2=�ű��ļ�)

	MSG_DELAY,			//��ʱ			(p1=time)
	MSG_FADE,			//���뵭��		(p1=1������p1=0����)
	MSG_PLAYSOUND,		//������Ч		(s1=File)
	MSG_STOPSOUND,		//ֹͣ����
	MSG_PLAY_MUSIC,		//��������		(s1=filename)
	MSG_STOP_MUSIC,		//ֹͣ��������
	MSG_PAUSE_MUSIC,	//��ͣ����
	MSG_RESUME_MUSIC,	//��������
	MSG_BREAK,			//���β�ִ��

} MESSAGE;


/**\brief
 * ��Ϣ��������
 */
struct SMessage
{
	// ��Ϣ����
	MESSAGE msg;

	// ����
	int param1,param2;

	// �ַ�ָ�����
	char *str1,*str2,*str3;

	SMessage():param1(0),param2(0),str1(NULL),str2(NULL),str3(NULL){}
	SMessage(MESSAGE _msg,int p1,int p2,char* s1,char* s2,char* s3)
		:msg(_msg),param1(p1),param2(p2),str1(s1),str2(s2),str3(s3){}
	~SMessage(){}
};


/**\brief
 * ��Ϣ������
 */
class Message
{
public:
	Message(void);
	~Message(void);


	/**\brief
	 * �ڶ�β����һ����Ϣ
	 */
	BOOL Insert(SMessage _msg){m_dQueue.push_back(_msg);return TRUE;}


	/**\brief
	 * �ڶ�ͷɾ��һ����Ϣ
	 */
	BOOL Delete(){if(m_dQueue.size()<=0)return FALSE;else{m_dQueue.pop_front();return TRUE;}}


	/**\brief
	 * �����Ϣ����
	 */
	void Clear(){m_dQueue.clear();}


	/**\brief
	 * ��Ϣ��������Ϣ�ĸ���
	 */
	unsigned int GetMsgNum(){return m_dQueue.size();}


	/**\brief
	 * ִ�е�ǰ��Ϣ
	 */
	void Run();


	/**\brief
	 * ȡ�õ�ǰ����Ϣ�������
	 */
	static Message* GetSysMessage(){return m_pMessage;}


private:
	// ��Ϣ����
	deque<SMessage> m_dQueue;

	// ��Ϣ��������ָ��
	static Message* m_pMessage;

};



#endif
