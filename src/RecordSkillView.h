/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#include "Window.h"

/** ��ʾAR���ٵ�С���� */
class RecordSkillView :	public EGWindow
{
public:
	RecordSkillView(void);
	~RecordSkillView(void);
	
	/**\brief
	 * ��INI�ļ�����������Ƶͼ�����
	 */
	BOOL LoadIni(char* _filename,char* _index);

	void draw(void);

private:
	/**\brief
	 * ͼ��Ļ���
	 */
	void OnDraw(void);

	float m_escapeTime;
};

