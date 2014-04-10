/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _GENERAL_H_
#define _GENERAL_H_

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>

#pragma warning(disable: 4267)

/** ����֡�� **/
#define LOCKFPS 90

/** ���� **/
#define DEPTHOFFIELD 450

/** һЩ���� */
#define F3D_DEPTH	800.f
#define SYS_HWND	(EGSWindowInfo::GetSysWinInfo()->m_hWnd)
#define SYS_WIDTH	(EGSWindowInfo::GetSysWinInfo()->m_iWidth)
#define SYS_HEIGHT	(EGSWindowInfo::GetSysWinInfo()->m_iHeight)
#define SYS_COEG	(CoreEngine::GetSysCoreEngine())

#define SYS_KEYBOARD (EGInput::GetSysInput()->GetKeyboard())
#define SYS_MOUSE	(EGInput::GetSysInput()->GetMouse())
#define SYS_TIMER	(EGTimer::GetSysTimer())
#define SYS_VIDEO	(ARMgr::GetSysARMgr()->GetVideoCapture())	//����ͷ
#define SYS_ARML	(ARMgr::GetSysARMgr()->GetMotionAnalysis())	//��������
const int DISTANCE_TO_X_SIDE = 100;
const int DISTANCE_TO_Y_SIDE = 100;


/** ��ť��״̬ */
#define BUTTON_NORMAL	0
#define BUTTON_ACTIVE	1
#define BUTTON_DISABLE	2
#define BUTTON_DOWNL	3
#define BUTTON_DOWNR	4
#define BUTTON_CLICK	5


/** ��ť���ֵ����� */
#define BTN_TEXT_LEFT	0
#define BTN_TEXT_CENTER	1
#define BTN_TEXT_RIGHT	2


/**  ��Ϸ���� */
#define GAME_INIT		0
#define GAME_TITLE		1
#define GAME_CG			2
#define GAME_MENU		3
#define GAME_SETTING	4
#define GAME_MAIN		5
#define GAME_END		6


/** ���ú� */
#define _ERROR(info)	MessageBox(NULL,info,"error",MB_OK)

#define _DELETE(X)		try{ if((X)!=NULL){delete (X); (X) = NULL; } } catch(...) { _ERROR("error delete!"); }
#define _DELETE_ARRAY(X)try{ if((X)!=NULL){delete[] (X); (X) = NULL; } } catch(...) { _ERROR("error delete[]!"); }
#define _FREE(X)		try{ if((X)!=NULL){free(X);(X)=NULL; } } catch(...) { _ERROR("error free()!"); }
#define _RELEASE(A)		try{ if((A)!=NULL){(A)->Release(); (A) = NULL; } } catch(...) { _ERROR("error ->Release!"); }


/** ������ɫ������ */
typedef DWORD DWCOLOR;


/** ����� */
#define _RANDOM(nMax) (rand()*nMax/RAND_MAX)


/** ��INI�ļ��е�int����ת��Ϊfloat�� */
#define PERSENT(iNum) ((float)(iNum)*0.01f)



/**\brief
 * ��v1��v2֮���������һ����
 */
template<class T>
inline static T RangedRandom(T v1,T v2)
{
	return v1 + (v2-v1)*((T)rand())/((T)RAND_MAX);
}



/**\brief
 * ��ȡ�ļ�����
 */
static int GetFileLength(char *name)
{
	int fh, nbytes;

	fh = _open( name, _O_RDONLY );//ֻ��ģʽ
	if( fh== -1 ){return -1;}
	nbytes=_filelength(fh);
	_close(fh);

	return nbytes;
}



/**\brief
 * �ж��ļ��Ƿ����
 */
static BOOL CheckFile(char *name)
{
	//�����ļ�
	WIN32_FIND_DATA fdt;
	HANDLE hFile = FindFirstFile(name,&fdt);
	if( hFile ==INVALID_HANDLE_VALUE )
		return FALSE;
	else 
	{
		FindClose(hFile);
		return TRUE;
	}
}



/**\brief
 * ���ļ�����ȡ�ļ�·��
 */
static char* GetFilePath(char *filename)
{
	char *Ret;
	int Len=strlen(filename);
	Ret=(char *)malloc(Len+1);
	strcpy(Ret, filename);
	for(int i=Len-1; i>=0; i--)
	{
		if( Ret[i] == '\\' )//�Ӻ���ǰ��'\'
			break;
		Ret[i]=0;			//���óɽ�����
	}

	return Ret;
}



/**\brief
 * ���ļ�����·��������ļ�������·��
 */
static char* GetFileName(char* filename)
{
	char * szTemp = strrchr(filename,'\\'); //�����һ��'\'
	++szTemp;								//����'\'
	char *Ret = (char*)malloc(strlen(szTemp)+1);
	strcpy(Ret,szTemp);

	return Ret;
}



/**\brief
 * ��ʾ������Ϣ
 */
static void ShowMessage(char *msg,...)
{
	va_list va;
	char str[256];

	va_start(va,msg);
	vsprintf(str,msg,va);
	va_end(va);

	MessageBox(NULL,str,"Message",MB_OK);
}



/**\brief
 * char to wchar
 */
static WCHAR* WChar(char *str)
{
	WCHAR *wchr;
	//���������������ó�NULL��0
	//�õ���Ҫ�Ļ���������
	int wsize=MultiByteToWideChar(CP_ACP, NULL, str, strlen(str), NULL, 0);

	wchr=new WCHAR[wsize+1];		//���һ����0
	MultiByteToWideChar(CP_ACP, NULL, str, strlen(str), wchr, wsize);
	wchr[wsize]=0;

	return wchr;
}




/**\brief
 * wchar to char
 */
static char* Char(WCHAR *str)
{
	char *chr;
	chr=new char[wcslen(str)+1];
	memset(chr, 0, wcslen(str)+1);

	for(unsigned int i=0;i<wcslen(str);++i)
	{
		chr[i]=(unsigned char)str[i];
	}

	return chr;
}


/**\brief
 * ��ʼ2D��Ⱦ
 */
static void BeginOrtho(int _width,int _height)
{
	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,_width,0,_height,-1,F3D_DEPTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/**\brief
 * ����2D��Ⱦ
 */
static void EndOrtho()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
}

#endif
