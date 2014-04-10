/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _SKY_BOX_H_
#define _SKY_BOX_H_

#include "camera.h"
#include "texture.h"


/**\brief
 * ��պ���
 */
class CSkyBox  
{
public:
	CSkyBox();
	~CSkyBox();

	BOOL Init();			// ��յĳ�ʼ��

	void Render();			// ��Ⱦ���


private:
	EGCTexture texture;		// �������

	float yrot;				// Χ��Y�����ת�Ƕ�

	vector3d m_sCameraPos;	// �������λ��
	
	GLuint cameraTexture[1];
};

#endif
