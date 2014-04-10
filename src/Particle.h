/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _PATICLE_H_
#define _PATICLE_H_

#include "mathlib.h"


/**\brief
 * ���ӵĽṹ
 */
struct PARTICLE
{
	// ���ӵ�λ��
	vector3d  m_pos;

	// ���ӵ��ٶ�
	vector3d  m_velocity;

	// ���ӵ�������
	float   life;

	// ���ӵĴ�С
	float   m_size;
	
	// ���ٶ�
	vector3d   m_gravity;
	
	// ��ɫ
	float   m_color[3];
};



/**\brief
 * ����ϵͳ��
 */
class EGParticle  
{
public:
	EGParticle();
	virtual ~EGParticle();


	/**\brief
	 * ����ϵͳ�ĳ�ʼ��
	 *
	 *\param	_num	������
	 */
	virtual BOOL Init(int _num);
	
	
	/**\brief
	 * ���ӵ���Ⱦ
	 */
	virtual void Render() = 0;


protected:
	// ��������
	int m_iMaxNum;

	// ���ӵ�ָ��
	PARTICLE *pList_particle;
};


#endif
