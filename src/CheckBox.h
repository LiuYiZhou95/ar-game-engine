/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _CHECK_BOX_H_
#define _CHECK_BOX_H_

#include "StdAfx.h"
#include "Button.h"


/**\brief
 * ��ѡ����
 */
class EGCheckBox : public EGCButton  
{
public:
	EGCheckBox(){bChecked=FALSE;}
	~EGCheckBox(){}


	/**\brief
	 * ��INI�ļ�����
	 */
	virtual BOOL LoadIni(char* filename,char* index);


	/**\brief
	 * �Ƿ�ѡ��
	 */
	BOOL	GetState(){return bChecked;}


	/**\brief
	 * ���ø�ѡ���״̬
	 */
	void	SetState(BOOL _bChecked){bChecked=_bChecked;}

private:
	// �Ƿ�ѡ
	BOOL bChecked;


	/**\brief
	 *  ����
	 */
	virtual void OnDraw(void);

};

#endif
