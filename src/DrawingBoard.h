/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _BILL_BORAD_H_
#define _BILL_BORAD_H_

#include "mathlib.h"


/**\brief
 * �����������
 */
class EGCDrawingBoard  
{
public:
	EGCDrawingBoard():rotate(0.f),bRotate(TRUE){}
	~EGCDrawingBoard(){}

	void SetRotate(BOOL isRotate){bRotate = isRotate;}
	void Render(vector3d vpos,float m_iSize);
	void Update();


private:
	vector3d	right;
	vector3d	up;
	float		rotate;
	BOOL		bRotate;
};


#endif
