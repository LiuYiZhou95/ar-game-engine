/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "GameApp.h"
#include "resource.h"
#include "main.h"


// ���뷨
EGIme	m_cIme;

GameApp::GameApp(void){}

GameApp::~GameApp(void)
{
	m_coreEngine.Close();
	KillGLWindow();
}



/*! �������ѭ�� */
void GameApp::Run(void)
{
	while(TRUE)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
		{
			if(msg.message == WM_QUIT)break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_coreEngine.Prepare();
			m_coreEngine.Render();
			m_coreEngine.SwapBuffer();
		}
	}
}


/**\brief
 * ��������
 *
 *\param	_sWinInfo	������Ϣ
 *\return	BOOL		�����Ƿ�ɹ�
 */
BOOL GameApp::CreateGLWindow(EGSWindowInfo _sWinInfo)
{
	m_sWinInfo=_sWinInfo;
	m_sWinInfo.m_hInstance=GetModuleHandle(NULL);

	WNDCLASS	wc;
	DWORD		dwExStyle;
	DWORD		dwStyle;
	RECT		WindowRect;
	WindowRect.left=(long)0;
	WindowRect.right=(long)m_sWinInfo.m_iWidth;
	WindowRect.top=(long)0;
	WindowRect.bottom=(long)m_sWinInfo.m_iHeight;


	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= m_sWinInfo.m_hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor			= NULL;//LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= "OpenGL";

	if (!RegisterClass(&wc))return FALSE;
	
	if (m_sWinInfo.m_bFullScreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth	= m_sWinInfo.m_iWidth;
		dmScreenSettings.dmPelsHeight	= m_sWinInfo.m_iHeight;
		dmScreenSettings.dmBitsPerPel	= m_sWinInfo.m_iBits;
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!= DISP_CHANGE_SUCCESSFUL)
		{
			
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				m_sWinInfo.m_bFullScreen=FALSE;
			}
			else
			{
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (m_sWinInfo.m_bFullScreen)
	{
		dwExStyle=WS_EX_APPWINDOW;
		dwStyle=WS_POPUP;
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle=WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	if (!(m_sWinInfo.m_hWnd=CreateWindowEx(dwExStyle,
								"OpenGL",
								m_sWinInfo.m_strWinName,
								dwStyle|
								WS_CLIPSIBLINGS|
								WS_CLIPCHILDREN,
								0, 0,
								WindowRect.right-WindowRect.left,
								WindowRect.bottom-WindowRect.top,
								NULL,NULL,
								m_sWinInfo.m_hInstance,
								NULL)))
	{
		KillGLWindow();
		return FALSE;
	}
	ShowWindow(m_sWinInfo.m_hWnd,SW_SHOW);
	SetForegroundWindow(m_sWinInfo.m_hWnd);
	SetFocus(m_sWinInfo.m_hWnd);
	
	return TRUE;
}


/*! ������Ϣ������ */
LRESULT WINAPI GameApp::MessageHandler(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
		case WM_ACTIVATE:  
		{
			if (!HIWORD(wParam))
				m_bActive = TRUE;
			else
				m_bActive=FALSE;
		
			return 0;
	    }

		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);return 0;

		case WM_CREATE:return 0;

		case WM_SIZE:
		{
			m_coreEngine.SetProjection(45,1);
			return 0;
		}
		///////////////////////////////////
		//-----����������������뷨--------
		case WM_KEYDOWN:
			switch( wParam )
			{
				case VK_LEFT:	m_cIme.LeftKey();break;
				case VK_RIGHT:	m_cIme.RightKey();break;
				case VK_DELETE:	m_cIme.DeleteKey();break;
				case VK_RETURN:	m_cIme.ReturnKey();break;
				default:break;
			}
			break;

		case WM_CHAR:		//IME��Ϣ
			m_cIme.ReceiveChar(wParam);
			break;

		//case WM_IME_SETCONTEXT:
		//	return m_cIme.OnWM_IME_SETCONTEXT()? 0 : DefWindowProc(hWnd, message, wParam, lParam);

		case WM_INPUTLANGCHANGEREQUEST:
			return m_cIme.OnWM_INPUTLANGCHANGEREQUEST()? 0 : DefWindowProc(hWnd, message, wParam, lParam);

		case WM_IME_STARTCOMPOSITION:
			return m_cIme.OnWM_IME_STARTCOMPOSITION()? 0 : DefWindowProc(hWnd, message, wParam, lParam);

		case WM_IME_ENDCOMPOSITION:
			return m_cIme.OnWM_IME_ENDCOMPOSITION()? 0 : DefWindowProc(hWnd, message, wParam, lParam);

		//case WM_IME_NOTIFY:
		//	return m_cIme.OnWM_IME_NOTIFY( m_sWinInfo.m_hWnd, wParam )? 0 : DefWindowProc(hWnd, message, wParam, lParam);
	
		case WM_IME_COMPOSITION:
			return m_cIme.OnWM_IME_COMPOSITION( m_sWinInfo.m_hWnd, lParam )? 0 : DefWindowProc(hWnd, message, wParam, lParam);

		case WM_INPUTLANGCHANGE:
			return m_cIme.OnWM_INPUTLANGCHANGE( m_sWinInfo.m_hWnd )? 0 : DefWindowProc(hWnd, message, wParam, lParam);

		case WM_SYSCOMMAND:
			return ( wParam == SC_KEYMENU )? 0 : DefWindowProc(hWnd, message, wParam, lParam);
	}

	return  DefWindowProc(hWnd, message, wParam, lParam);
}



/*! ��ʼ�����򣬴��ڡ������ */
BOOL GameApp::Init(EGSWindowInfo _sWinInfo)
{
	if(!CreateGLWindow(_sWinInfo))
	{
		_ERROR("��������ʧ��!");
		return FALSE;
	}

	if(!m_coreEngine.Init())
	{
		_ERROR("��ʼ��Openglʧ��!");
		return FALSE;
	}

	return TRUE;
}

/*! ���ٴ��� */
void GameApp::KillGLWindow(void)
{
	if (m_sWinInfo.m_bFullScreen)ChangeDisplaySettings(NULL,0);

	if (m_sWinInfo.m_hWnd && !DestroyWindow(m_sWinInfo.m_hWnd))m_sWinInfo.m_hWnd=NULL;

	if (!UnregisterClass("OpenGL",m_sWinInfo.m_hInstance))m_sWinInfo.m_hInstance=NULL;
}