/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __CGW_OBJECT_H__
#define __CGW_OBJECT_H__

#include "mathlib.h"
#include "terrain.h"

/**\brief
 * ������Ϸʵ����Ļ���
 */
class Object
{
public:
	Object(void);
	~Object(void);

	float	rx,ry;		// ��Χ�еİ뾶,�ֱ���x,y�ϵķ���

	void Render();

	void SetPos(vector3d v)		{m_sPos=v;m_sPos.y = EGTerrain::GetSysTerrain()->GetHeight(m_sPos.x ,m_sPos.z);}

	vector3d GetPos(void)		{return m_sPos;}

	void SetHeightAt(float _h)	{m_sPos.y=_h;}


private:
	virtual void OnRender(){}


protected:
	vector3d   m_sPos;

};

#endif
