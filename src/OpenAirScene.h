/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __OPEN_AIR_SCENE_H__
#define __OPEN_AIR_SCENE_H__

#include "iscene.h"
#include "snow.h"
#include "plantmgr.h"
#include "SkyBox.h"
#include "water.h"

/**\brief
 * ��Ϸ��������
 */
class OpenAirScene : public IScene
{
public:
	OpenAirScene(void);
	~OpenAirScene(void);


	/**\brief
	 * �����ĳ�ʼ��
	 */
	BOOL Init(void);


	/**\brief
	 * ��INI�ļ���������
	 */
	BOOL LoadIni(char* _filename,char* _index);


	/**\brief
	 * ���³���������
	 */
	void UpdateData(void);


	/**\brief
	 * ��������Ⱦ
	 */
	void Render(void);


	CTreeMgr* GetTreeMgr(){return &trees;}

private:
	// ѩ����Ⱦ����
	EGSnow m_cSnow;

	// ���
	CSkyBox skybox;
	
	// ��
	CTreeMgr trees;

	// ˮ
	CWater water;
};


#endif
