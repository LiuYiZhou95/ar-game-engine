/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "resource.h"
#include "main.h"

//////////////////////////////////////////////////////////
//-----------------������ȫ�ֱ����Ķ���-------------------
// ������Ϣ�ṹ
EGSWindowInfo* g_sWindowInfo;

// Ӧ�ó���
GameApp*	 g_cGameApp;



//////////////////////////////////////////////////////////
//-----------------������ȫ�ֺ�����ʵ��-------------------

/**\brief
 * ����������������
 */
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	/*�����������*/
	srand(36);

	g_cGameApp		= new GameApp();
	g_sWindowInfo	= new EGSWindowInfo;

	if(!g_sWindowInfo->LoadIni("ini\\init.ini","window"))
	{
		_ERROR("���ڳ�ʼ��ʧ��!");
		_DELETE(g_cGameApp);
		return 0;
	}

	if(!g_cGameApp->Init(*g_sWindowInfo))
	{
		_ERROR("�����ʼ��ʧ��!");
		_DELETE(g_cGameApp);
		return 0;
	}

	g_cGameApp->Run();

	_DELETE(g_cGameApp);
	_DELETE(g_sWindowInfo);

	return 0;
}



/**\brief
 * ������Ϣ������
 */
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	return g_cGameApp->MessageHandler(hWnd,message,wParam,lParam);
}

