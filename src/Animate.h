/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _ANIMATE_H_
#define _ANIMATE_H_

#include "StdAfx.h"
#include "Texture.h"
#include "IniFile.h"


/**\brief
 * 2Dƽ�涯����
 */
class EGAnimate  
{
public:
	// ����֡��֮֡�����ʱ
	float	DeltaTime;

	// ��ɫ
	EGSColor	color;

	// ���ھ���
	EGSRect	rect;


	EGAnimate();
	~EGAnimate(){}


	/**\brief
	 * �Ƿ�͸������
	 */
	BOOL GetBlendState(){return bBlend;}


	/**\brief
	 * ��������
	 *
	 *\param	filename	�����ļ���
	 *\param	nFrameNum	��֡��
	 *\param	_bBlend		�Ƿ�͸������
	 *\return	BOOL		�Ƿ�ɹ���������
	 */
	BOOL LoadTexture(char* filename,int nFrameNum,BOOL _bBlend);


	/**\brief
	 * ͨ��INI�ļ���ʼ��
	 */
	virtual BOOL LoadIni(char* filename,char* index);
	

	/**\brief
	 * ��Ⱦ����
	 */
	void draw(void);


	/**\brief
	 * �ƶ�����
	 *
	 *\param	_dx	x��ƫ��
	 *\param	_dx	y��ƫ��
	 */
	void move(int _dx,int _dy){rect.x+=_dx;rect.y+=_dy;}



private:
	// ������֡��
	unsigned int FrameNum;
	
	// �Ƿ�͸������
	BOOL		bBlend;

	// �������õ�����
	EGCTexture	texture;
	
	// ���ڲ��ŵ�n֡����0��ʼ��
	unsigned int n;

	// ��֡��ļ��ʱ��
	float		m_fDeltaTime;
};


#endif
