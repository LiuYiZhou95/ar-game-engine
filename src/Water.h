/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _WATER_H_
#define _WATER_H_

#include "texture.h"


/**\brief
 * ˮ����Ⱦ��
 */
class CWater  
{
public:
	CWater();
	~CWater();

	/**\brief
	 * ��ʼ��,��Ҫ�����������
	 */
	BOOL Init();
	

	/**\brief
	 *  ˮ����Ⱦ
	 */
	void Render();



private:
	// ����
	EGCTexture texture;
	
	// �����ƶ�����С��λ
	float delta;

};

#endif
