/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "texture.h"
#include "camera.h"


/**\brief
 * ������
 */
class EGTerrain
{
public:
	EGTerrain();
	~EGTerrain(){delete [] heightMap; }
	
	BOOL Init(int _width,char* TexFile);
	BOOL Load(char* filename);

	static EGTerrain* GetSysTerrain(){return m_pTerrain;}
	
	/**\brief
	 * ȡ�õ��εĿ�
	 */
	int GetWidth(){return m_nWidth;}

	int GetCellWidth(){return m_nCellWidth;}

	void Render(void);

	int GetMapWidth(){return m_nWidth * m_nCellWidth;};

	float GetHeight(float x, float z);

private:
	// ���δ�СΪm_iWidth*m_iWidth�������2^n
	unsigned int m_nWidth;

	// ��̬�߳�ӳ��
	short*        heightMap;

	// ÿ�����ӵĿ��
	unsigned int m_nCellWidth;

	// �����ϵĶ�������
	EGCTexture terrainTex;

	// �����ɫ
	float fogColor[4];

	float scanDepth;
	
	static EGTerrain* m_pTerrain;
};


#endif
