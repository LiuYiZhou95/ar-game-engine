/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _PROGRESS_BAR_H_
#define _PROGRESS_BAR_H_

#include "StdAfx.h"
#include "Window.h"


/**\brief
 * ��������
 */
class EGProgressBar : public EGWindow
{
public:
	EGProgressBar();
	~EGProgressBar(){}


	/**\brief
	 * ��INI�ļ����봰������
	 */
	virtual BOOL LoadIni(char* filename,char* index);


	/**\brief
	 * ���ý������Ľ���
	 */
	void	SetPos(float p){pos=p;}


	/**\brief
	 * ���ý������߿�Ŀ��
	 */
	void	SetBorderWidth(int b){border=b;}


	/**\brief
	 * ���ý���������ɫ
	 */
	void	SetBarColor(EGSColor c){BarColor=c;}
	

	/**\brief
	 * ��ý������Ľ���
	 */
	float	GetPos(){return pos;}
	
	
	/**\brief
	 * ȡ�ñ߿�Ŀ��
	 */
	int		GetBorderWidth(){return border;}
	
	
	/**\brief
	 * ȡ�ý���������ɫ
	 */
	EGSColor	GetBarColor(){return BarColor;}



private:
	// ������¼�����ý������Ľ���
	float	pos;
	
	//�߿���
	int		border;
	
	//������ɫ
	EGSColor	BarColor;
	
	
	/**\brief
	 * ���ƽ�����
	 *
	 * �麯�������丸��EGWindow��draw()������
	 */
	virtual void OnDraw(void);
};


#endif
