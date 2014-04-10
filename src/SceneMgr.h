/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __SCENE_MGR_H__
#define __SCENE_MGR_H__

#include "iscene.h"
#include "aviscene.h"
//#include "titlescene.h"
//#include "selcharscene.h"
#include "openairscene.h"
#include "role.h"
#include "monstersMgr.h"
#include "staticObjMgr.h"
#include "timer.h"
#include "mathlib.h"


/**\brief
 * ����������
 */
class SceneMgr
{
public:
	SceneMgr(void);
	~SceneMgr(void);


	/**\brief
	 * ��ʼ��
	 */
	BOOL Init();


	/**\brief
	 * ��INI���볡������
	 */
	BOOL LoadIni(char* _filename,char* _index);


	/**\brief
	 * ���õ�ǰ����
	 */
	void SetScene(GAME_SCENE _scene);


	/**\brief
	 * ��õ�ǰ���е������ೡ��
	 */
	GAME_SCENE GetScene(void){return m_eSceneType;}


	/**\brief
	 * ��������Ⱦ
	 */
	void Render(void);

	/**\brief
	 * ȡ�õ�ǰ������������ָ��
	 */
	static SceneMgr* GetSysSceneMgr(void){return m_psceneMgr;}

private:
	
	// ��ǰ����ָ��
	IScene* m_pScene;

	// ��ǰ�ĳ�������
	GAME_SCENE m_eSceneType;

	// ������������ָ��
	static SceneMgr* m_psceneMgr;

	/////////////////////////////////////////////
	// ����
	EGTerrain Terrain;

	// ��ѡ���ݻ�����
	GLuint selectBuff[512];

	// ��̬ʵ��
	EGStaticObjMgr m_cStaticObj;

	// ����
	EGMonstersMgr m_cMonsters;

	// Ӣ��
	EGRole role;

	/**\brief
	 * ��ʼ����ѡ����
	 */
	void StartPick(void);

	/**\brief
	 * ��������ѡ����
	 */
	void EndPick(void);

	/**\brief
	 * �������ж����ѡ
	 */
	void Pick(void);
	BOOL PickModel(int&type ,unsigned int &id);

	/**\brief
	 *��ײ���
	 */
	//vector<EGActiveObj> all_objs;
	//void CollisionDetection();
	//void Collision(vector<EGActiveObj> & objs,float halfx,float halfz);
};


#endif
