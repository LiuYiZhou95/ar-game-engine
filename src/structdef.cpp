/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "structdef.h"
#include "IniFile.h"



/** ������EGSWindowInfo�ṹ��ʵ��  */

// EGSWindowInfo�ṹ�ľ�̬������ʼ��
EGSWindowInfo*	EGSWindowInfo::m_pInfo=NULL;
BOOL			EGSWindowInfo::m_bFullScreen=FALSE;
int				EGSWindowInfo::m_iWidth=640;
int				EGSWindowInfo::m_iHeight=480;
int				EGSWindowInfo::m_iBits=32;
HINSTANCE		EGSWindowInfo::m_hInstance=NULL;
HWND			EGSWindowInfo::m_hWnd=NULL;
char*			EGSWindowInfo::m_strWinName=NULL;

/**\brief
 * ��INI�ļ����봰����Ϣ
 */
BOOL EGSWindowInfo::LoadIni(char* _filename,char* _index)
{
	EGCIniFile t_cIni(_filename);
	m_iWidth		=t_cIni.ReadInt(_index,"width");
	m_iHeight		=t_cIni.ReadInt(_index,"height");
	m_iBits			=t_cIni.ReadInt(_index,"bits");
	m_bFullScreen	=t_cIni.ReadInt(_index,"FullScreen");
	m_strWinName	=t_cIni.ReadText(_index,"WindowName");

	m_hInstance = GetModuleHandle(NULL);

	return TRUE;
}

