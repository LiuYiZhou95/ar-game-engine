/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __STATIC_OBJ_H__
#define __STATIC_OBJ_H__

#include "object.h"
#include "MS3DFile.h"
#include "terrain.h"

class StaticObj : public Object
{
public:
	StaticObj(void);
	~StaticObj(void);

	void SetDir(float _dir)		{m_fDir=_dir;}
	float GetDir()				{return m_fDir;}

	BOOL LoadIni(char* filename,char* index);

	virtual void OnRender();

	void SetSelecte(BOOL b)		{m_bSelected=b;}

private:
	EGMS3DFile ms3d;			// MS3D�ļ�����

	float		m_fDir;		// ����

	BOOL		m_bSelected;// �Ƿ�ѡ��
};


#endif
