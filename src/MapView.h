/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __MAP_VIEW_H__
#define __MAP_VIEW_H__

#include "window.h"
#include "texture.h"
#include "MonstersMgr.h"
#include "role.h"

/**\brief
 * С��ͼ��
 */
class MapView : public EGWindow
{
public:
	MapView(void);
	~MapView(void);

	/**\brief
	 * ��INI�ļ�����С��ͼ����
	 */
	BOOL LoadIni(char* _filename,char* _index, char* _videoFilename,char* _videoIndex);

private:
	/**\brief
	 * С��ͼ�Ļ���
	 */
	void OnDraw(void);
};


#endif
