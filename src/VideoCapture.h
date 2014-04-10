/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma onces
#ifndef _VIDEO_CAPTURE_H_
#define _VIDEO_CAPTURE_H_
#include "stdAfx.h"
#include "AR/ar.h"
#include "AR/video.h"
#include <AR/gsub.h>
#include "IniFile.h"

class VideoCapture
{
public:
	VideoCapture(void);
	~VideoCapture(void);
	/** ������ͷ�������ȡͼ�� */
	void run();

	/** ��ʼ������ͷ**/
	BOOL LoadIni(char* _filename,char* _index);
	
	/** ������ͷ��ȡһ֡ͼ�� **/
	ARUint8 * getImgFromCap();
	/** ������ͷ��ȡһ֡ͼ�� **/
	//ARInt16 * getImgFromCap();

	/** ��ȡ��Ƶ�ļ��Ŀ�͸� **/
	int getWidth();
	int getHeight();
		
	/** �������״̬ **/
	BOOL getRunState();

	/** �����Դ **/
	void cleanup();

	/** ��ȡ��¼��Ƭ��Ϣ�Ľṹ���� **/
	OBJECT_T * getObjects();
	
	/** ��֡������ͷ **/
	void setLowSpeedCamera();

	void UpThresh();

	int GetThresh();

	void DownThresh();

private:

	/** �����ȡ����ͷͼ��ܷ���ͼ��������� **/
	void mainLoop();
};
#endif