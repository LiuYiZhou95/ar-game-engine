/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _MONSTER_H_
#define _MONSTER_H_

#include "ActiveObj.h"
#include "terrain.h"
#include "MagicSkillMgr.h"
#include "info.h"
#include "sound.h"

extern CInfo ObjectInfo;


/**\brief
 * ��Ϸ�еĹ���
 */
class EGMonster : public EGActiveObj
{
public:
	EGMonster(void);
	~EGMonster(void){_DELETE(property);}

	/**\brief
	 * �����ٶ�
	 */
	void SetSpeed(float s);
	void Render_Pick(void);

	/**\brief
	 * ���ù��������
	 */
	void SetMonsterInfo(SActiveObjPro& info);
	void SetShadow(BOOL b){property->shadow=b;}

	/**\brief
	 * ��Ⱦ����
	 */
	virtual void OnRender(void){EGActiveObj::OnRender();m_magicSkillMgr.Render();}

	/**\brief
	 * ��Ⱦ������ݸ���
	 */
	virtual void EndRender(void);


	/**\brief
	 * ��ʼ��һ������
	 */
	BOOL Init(char* modelname,char* texturename,float scale,float h);


	/**\brief
	 * ��INI�ļ���ʼ��һ������
	 */
	BOOL LoadIni(char* filename,char* index);


private:
	// ħ�����ܹ�����
	MagicSkillMgr m_magicSkillMgr;

	int time_elapse;

	EGSound sound;

	BOOL isDead;

	BOOL tracking;
};

#endif
