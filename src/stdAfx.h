/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
/**  
*   @file   stdafx.h
*/
#pragma once
#include <afxmt.h>
#ifndef _STDAFX_H_
#define _STDAFX_H_

#define WIN32_LEAN_AND_MEAN	

/** Ϊ����WM_MOUSEWHEEL��Ϣ���ӵ� */
#define _WIN32_WINDOWS 0x0400

/** ����ͳ�е�ͷ�ļ� */
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <iostream>

/** ����OpenGLͷ�ļ� */
#include "gl/glut.h"
//#include <gl\glaux.h>
//#include <gl\glext.h>

/** �����Զ���ͷ�ļ� */
#include "general.h"
#include "structdef.h"


/** Ҫ�õ������ӿ� */
#pragma comment(lib, "opengl32.lib")		
#pragma comment(lib, "glut32.lib")							
#pragma comment(lib, "glaux.lib")	
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"XInput.lib")
//////////////AR������////////////
#pragma comment(lib,"libAR.lib")
#pragma comment(lib,"libARvideo.lib")
#pragma comment(lib,"libARgsub.lib")

/** ��ֹ��������������ת���ľ��� */
#pragma warning(disable: 4311)                                 
#pragma warning(disable: 4312)
#pragma warning(disable: 4244)
#pragma warning(disable: 4018)
#pragma warning(disable: 4267)
#pragma warning(disable: 4996)

#endif