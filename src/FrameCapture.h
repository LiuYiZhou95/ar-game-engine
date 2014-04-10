/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#include "stdAfx.h"
#include "MotionAnalysis.h"


class FrameCapture
{
public:
	FrameCapture(void);
	~FrameCapture(void);
	/** ������ͷ��ȡһ֡ͼ�� */
	void run();

	/** ������ͷ */
	void openCamera(){cameraIsOpen = TRUE;};
	/** �ر�����ͷ **/
	void closeCamera(){cameraIsOpen = FALSE;};

	/** �򿪷���ͼ�� */
	void openView(){viewWindowIsOpen = TRUE;};
	/** �رշ���ͼ�� **/
	void closeView();

	/** �򿪴�����ͼ�� **/
	void openResult(){showResult = TRUE;};
	/** �رմ�����ͼ�� **/
	void closeResult(){showResult = FALSE;};
	BOOL showOrNot(){return showResult;};

private:
	
	/** ������ͷ **/
	BOOL cameraIsOpen;
	/** ��Ӱ�񴰿� **/
	BOOL viewWindowIsOpen;

	/** �Ƿ���Ƽ���� **/
	BOOL showResult;
};
