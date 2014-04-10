/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _MAGIC_SKILL_MGR_H_
#define _MAGIC_SKILL_MGR_H_

#include "MagicSkill.h"

enum
{
	AITRIGGER = 0,	//�Զ���׼���ͷż���
	AUTOAIM,		//�Զ���׼�ֶ��ͷ�
	MANUAL,			//�ֶ���׼���ֶ��ͷ�
};

/**\breif
 *Ϊ��ǰ�Ķ�������ܵ��ͷ�
 */
class MagicSkillMgr
{
public:
	MagicSkillMgr(void);
	~MagicSkillMgr(void);

	BOOL CanReduceLife();
	void SetTriggerType(int _type){triggerType = _type;};
	void SetCurrSkillIndex(int index);
	BOOL Init(char * filename, char * _index);
	void Render();
	MagicSkill * CurrentSkill(){return &m_magicSkills[curr_skill_index];};

private:
	MagicSkill * m_magicSkills;
	int totalSkillNum;
	int curr_skill_index,new_skill_index;
	int triggerType;
};
#endif