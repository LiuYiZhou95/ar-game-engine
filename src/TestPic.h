/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#include "Window.h"

/** ��ʾAR���ٵ�С���� */
class TestPic :	public EGWindow
{
public:

	TestPic(void);
	~TestPic(void);
	
	static TestPic * GetTestPic(){return m_p;};

private:
	/**\brief
	 * ͼ��Ļ���
	 */
	static TestPic * m_p;
	
	void OnDraw(void);

	float m_escapeTime;
};

