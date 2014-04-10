/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#include "Window.h"
#include "button.h"
/** ��ʾAR���ٵ�С���� */
class StoryDialog :	public EGWindow
{
public:
	StoryDialog(void);
	~StoryDialog(void);

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

	BOOL LoadIni(char* _filename,char* _index);

private:
	// �˵��ϵİ�ť��Ŀ
	unsigned int m_nButtonNum;

	// ��ťָ��
	EGCButton*	m_pButton;

	void OnDraw(void);

	float m_escapeTime;
};