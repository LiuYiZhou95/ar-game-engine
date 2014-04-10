/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _SCROLL_BAR_H_
#define _SCROLL_BAR_H_

#include "StdAfx.h"
#include "button.h"
#include "IniFile.h"


/**\brief
 * ��������
 */
class EGCScrollBar  
{
public:
	EGCScrollBar();
	~EGCScrollBar();


	// TRUE:ˮƽ��FALSE:��ֱ
	BOOL	style;
	
	//λ�ã����½�����
	int		x,y;
	
	//���������
	int		width;
	
	//�������ĳ���
	int		MaxLength;
	
	//����ĳ���
	int		CellLength;


	/**\brief
	 * ���û���λ��
	 */
	void	SetPos(float p){pos=p;}
	
	
	/**\brief
	 * ��û���λ�ã�posֵ��
	 */
	float	GetPos(){return pos;}
	
	
	/**\brief
	 * ��INI�ļ�����
	 */
	BOOL	LoadIni(char* filename,char* index);
	
	
	/**\brief
	 * ���ƹ�����
	 */
	void	draw(void);
	
	
	/**\brief
	 * �������Ƿ��ڻ״̬��������Ƿ�������
	 */
	BOOL	IsActive(void);


private:
	// �����λ�ã��ðٷ�����ʾ
	float	pos;

	// ����ÿ���ƶ�����С����
	float	MinPos;

	// ���ϣ�ǰ����ť
	EGCButton*	btn1;

	// ���£��󣩰�ť
	EGCButton*	btn2;

	// ����
	EGCButton*	CenBtn;

};


#endif
