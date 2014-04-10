/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _STATIC_OBJ_MGR_H_
#define _STATIC_OBJ_MGR_H_

#include "StaticObj.h"
#include "terrain.h"
#include <vector>
using namespace std;


/**\brief
 * ��̬ʵ����������
 */
class EGStaticObjMgr
{
public:
	EGStaticObjMgr();
	~EGStaticObjMgr();


	/**\brief
	 * ��ö���ĸ���
	 */
	unsigned int GetObjNum(){return m_nObjNum;}
	

	/**\brief
	 * ��ѡ�������õ���Ⱦ
	 */
	void Render_Pick(int id);
	
	
	/**\brief
	 * ��Ⱦ���о�̬����ʵ��
	 */
	void Render();
	

	/**\brief
	 * ��ʼ��
	 */
	BOOL LoadIni(char* filename,char* index);


	static EGStaticObjMgr* GetSysStaticObjMgr(void){return m_pStaticObjMgr;}


	StaticObj* GetStaticObj(unsigned int n){if(n>=m_nObjNum)return NULL;return m_pObjArray+n;}
private:
	// MS3D�ļ�����
	EGMS3DFile ms3d;

	//
	unsigned int m_nObjNum;

	// 
	StaticObj* m_pObjArray;

	static EGStaticObjMgr* m_pStaticObjMgr;
};


////////////////////////////////////////////////////////
//--------------------inline����ʵ��--------------------
/**\brief
 * ��ѡ�������õ���Ⱦ
 */
inline void EGStaticObjMgr::Render_Pick(int id)
{
	(m_pObjArray+id)->Render();
}



/**\brief
 * ��Ⱦ���о�̬����ʵ��
 */
inline void EGStaticObjMgr::Render()
{
	for(unsigned int i=0;i<m_nObjNum;++i)
	{
		(m_pObjArray+i)->Render();
	}
}

#endif
