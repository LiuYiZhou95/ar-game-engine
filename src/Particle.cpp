#include "stdafx.h"
#include "Particle.h"
#include "time.h"


EGParticle::EGParticle()
{
	pList_particle = NULL;	
}

EGParticle::~EGParticle()
{
	if(pList_particle != NULL)
	{
		delete [] pList_particle;
		pList_particle = NULL;
	}
}


/**\brief
 * ����ϵͳ�ĳ�ʼ��
 *
 *\param	_num	������
 */
BOOL EGParticle::Init(int _num)
{
	m_iMaxNum = _num;
	pList_particle = new PARTICLE[m_iMaxNum];
	if(pList_particle == NULL)
		return FALSE;
	return TRUE;
}


/**\brief
 * ���ӵ���Ⱦ
 */
void EGParticle::Render()
{	
}
