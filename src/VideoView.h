/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#include "Window.h"

/** ��ʾAR���ٵ�С���� */
class VideoView :	public EGWindow
{
public:
	VideoView(void);
	~VideoView(void);
	
	/**\brief
	 * ��INI�ļ�����������Ƶͼ�����
	 */
	BOOL LoadIni(char* _filename,char* _index);


private:
	/**\brief
	 * ͼ��Ļ���
	 */
	void OnDraw(void);
};

