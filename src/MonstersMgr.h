/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _MONSTERS_MGR_H_
#define _MONSTERS_MGR_H_

#include "monster.h"
#include "mathlib.h"
#include "Info.h"


/**\brief
 * ������������
 */
class EGMonstersMgr
{
public:
	EGMonstersMgr();
	~EGMonstersMgr();


	/**\brief
	 * �õ�ĳ�������״̬
	 */
	OBJ_STATE GetMonsterState(int id){return m_pMonster[id].GetObjectState();}


	/**\brief
	 * �õ�ĳ�������λ��
	 */
	vector3d GetMonsterPos(int id){return m_pMonster[id].GetPos();}


	/**\brief
	 * �����Ƿ���ʾ��Ӱ
	 */
	void SetShadow(BOOL b);


	/**\brief
	 * ��ѡ��ģʽ����Ⱦ����
	 */
	void Render_Pick(int id){m_pMonster[id].Render_Pick();}


	/**\brief
	 * ȡ�ù��������
	 */
	unsigned int GetMonsterNum(){return m_nNumMonsters;}


	/**\brief
	 * ȡ�õ�ǰ�����������ָ��
	 */
	static EGMonstersMgr* GetSysMonstersMgr(){return m_pMonstersMgr;}


	/**\brief
	 * ��Ⱦ����
	 */
	void Render();


	/**\brief
	 * ��ʼ������
	 */
	BOOL LoadIni(char* filename,char* index);

	/**\brief
	 *��ȡĳ�����������
	 */
	EGMonster * getMonster(unsigned int n){if(n >= m_nNumMonsters)return NULL; return m_pMonster + n;};


private:
	// ���������
	unsigned int m_nNumMonsters;

	// ��Ź������ݵ�ָ��
	EGMonster* m_pMonster;

	// �����������ָ��
	static EGMonstersMgr* m_pMonstersMgr;
};



////////////////////////////////////////////////////
//----------------inline����ʵ��--------------------
inline void EGMonstersMgr::Render()
{
	for(unsigned int i=0;i<m_nNumMonsters;++i)m_pMonster[i].Render();
}


#endif
