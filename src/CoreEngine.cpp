/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "CoreEngine.h"
#include "stdio.h"
#include "GameApp.h"

CoreEngine * CoreEngine::m_cCoreEngine = NULL;

CoreEngine::CoreEngine(void)
	:m_bStop(FALSE)
{
	m_cCoreEngine = this;
}

CoreEngine::~CoreEngine(void)
{
	_DELETE(m_pTimer);
	_DELETE(m_pInput);
	_DELETE(m_pFont);
}


/*! ��ʼ������Ҫ��opengl����ĳ�ʼ��*/
BOOL CoreEngine::Init(void)
{
	m_hDC=::GetDC(SYS_HWND);
	if(!m_hDC)return FALSE;

	if(!SetDCPixelFormat()){return FALSE;}

	m_hRC= wglCreateContext(m_hDC);
	if (!m_hRC)return FALSE;

	if (!wglMakeCurrent(m_hDC,m_hRC))return FALSE;

	//--------------------------------------
	m_pFont=new HZFont;

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	SetProjection(45,1);
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
	glClearDepth(1.0);
	glClearStencil(0);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

	char str[50] = {"�װ�����ʿ����ӭ����ͨ������......"};
	BeginOrtho(800,600);
    m_pFont->Format(str);
	m_pFont->SetColor(EGSColor(1.0,0.0,0.0,0.0));
	m_pFont->PrintAt(300,300);
	EndOrtho();

	SwapBuffer();
	//--------------------------------------

	if(!InitObject())return FALSE;
	
	Sleep(10);
	
	return TRUE;
}


/*! ����opengl���ظ�ʽ */
BOOL CoreEngine::SetDCPixelFormat(void)
{
	int nPixelFormat;
	PIXELFORMATDESCRIPTOR pfd;

	memset(&pfd,sizeof(PIXELFORMATDESCRIPTOR),0);
	pfd.nSize		=sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion	=1;
	pfd.dwFlags		=PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
	pfd.cColorBits	=24;
	pfd.cDepthBits	=16;
	pfd.cStencilBits=1;
	pfd.iLayerType	=PFD_MAIN_PLANE;
	pfd.iPixelType	=PFD_TYPE_RGBA;

	nPixelFormat	=ChoosePixelFormat(m_hDC, &pfd);

	if(!nPixelFormat)return FALSE;
	if(!SetPixelFormat(m_hDC,nPixelFormat,&pfd))return FALSE;

	return TRUE;
}

/*! ��Ϸ�е�ʵ������ĳ�ʼ�� */
BOOL CoreEngine::InitObject(void)
{

	m_pTimer = new EGTimer;// ��ʱ����ʼ��
	m_pTimer->Init();

	
	m_pInput=new EGInput;
	m_pInput->Init(SYS_HWND,(HINSTANCE)GetModuleHandle(NULL),true,IS_USEKEYBOARD|IS_USEMOUSE);

	//dsound��ʼ��
	EGSound::InitDirectSound(SYS_HWND);
	EGMusic::InitMusic();
	m_cMusic.LoadMusic("sound/scene.mid");

	m_cGUIMgr.LoadCurIni("ini\\cursor.ini","normal");

	if(!m_cSceneMgr.Init())return FALSE;
	m_cMessage.Clear();
	//SYS_MESSAGE->Insert(SMessage(MSG_PLAYAVI,0,0,"ini\\AVI.ini","CG",NULL));
	SYS_MESSAGE->Insert(SMessage(MSG_OPENAIR,0,0,"ini\\OpenAir.ini","scene01",NULL));

	m_arMgr.Init();

	return TRUE;
}


/*! ��Ⱦǰ��׼������ */
void CoreEngine::Prepare(void)
{
	m_pTimer->Update();
	m_pInput->Update();
	m_cMessage.Run();
	SYS_ARML->update();

	// �ı���Ⱦģʽ
	if(m_pInput->GetKeyboard()->KeyDown(DIK_F9)) 
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);// �߿�ģʽ
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);// ����ģʽ

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}


/*! 3D��Ⱦ */
void CoreEngine::Render(void)
{
	///////////////3D��������Ⱦ//////////////////
	glEnable(GL_DEPTH_TEST);
	if(SceneMgr::GetSysSceneMgr()->GetScene()==SCE_OPENAIR)camera.Update();

	if(EGMusic::GetSysMusic()->GetMusic())
	{
		if(!m_cMusic.IsPlay()) m_cMusic.Play();
	}
	else
	{
		if(m_cMusic.IsPlay())m_cMusic.Pause();
	}

	m_cSceneMgr.Render();

	if(SceneMgr::GetSysSceneMgr()->GetScene()==SCE_AVI)
	{
		if(SYS_KEYBOARD->KeyDown(DIK_F1)||SYS_MOUSE->ButtonDown(1))
		{
			SYS_MESSAGE->Insert(SMessage(MSG_TITLE,0,0,"ini\\title.ini","menu",NULL));
			SYS_MESSAGE->Insert(SMessage(MSG_FADE,0,0,NULL,NULL,NULL));
			SYS_MESSAGE->Insert(SMessage(MSG_PLAY_MUSIC,0,0,"sound\\title.mid",NULL,NULL));
		}
	}

	////////////////����֡��///////////////////////
	m_pTimer->LockFPS(LOCKFPS);

	///////////////2D����Ļ���/////////////////
	glDisable(GL_DEPTH_TEST);
	m_cGUIMgr.Render();
	
}


/*! �ر����� */
void CoreEngine::Close(void)
{
	if(m_hRC)
	{
		if(!wglMakeCurrent(NULL,NULL))_ERROR("release  rc failed!");
		if(!wglDeleteContext(m_hRC))_ERROR("release rendering context failed!");
		m_hRC = NULL;
	}

	if(m_hDC)
	{
		if(!ReleaseDC(SYS_HWND,m_hDC))_ERROR("release dc failed!"); 
		m_hDC = NULL;
	}
}


/*! ���þ��� */
void CoreEngine::SetProjection(int iFOVAngle, int iHeight)
{
	double Aspect;
	int t_iFOV=iFOVAngle;

	if(t_iFOV>90)t_iFOV=45;

	if (iHeight == 0) Aspect = 1.0;
	else Aspect = (double)SYS_WIDTH/(double)SYS_HEIGHT;

	glViewport(0, 0,SYS_WIDTH,SYS_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(t_iFOV,Aspect,0.001f,F3D_DEPTH);
}
