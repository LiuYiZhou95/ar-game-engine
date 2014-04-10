/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _CGW_DIALOG_H__
#define _CGW_DIALOG_H__

#include "window.h"
#include "button.h"


/**\brief
 * �Ի�����
 */
class Dialog : public EGWindow
{
public:
	Dialog(void);
	~Dialog(void);
	
	/**\brief
	 * ��ð�ť��Ŀ
	 */
	unsigned int GetButtonNum(){return m_nButtonNum;}
	/**\brief
	 * ���ָ���İ�ť
	 */
	EGCButton* getButton(unsigned int index)
	{
		if(m_nButtonNum >= index && index >=1)
			return & m_pButton[index - 1];
	}

	/**\brief
	 * ��INI�ļ�����Ի���
	 */
	BOOL LoadIni(char* _filename,char* _index);


private:
	// �˵��ϵİ�ť��Ŀ
	unsigned int m_nButtonNum;

	// ��ťָ��
	EGCButton*	m_pButton;


	/**\brief
	 * �Ի�����Ⱦ
	 */
	void OnDraw();
};

#endif
