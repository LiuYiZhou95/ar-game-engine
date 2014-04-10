#include "stdafx.h"
#include "openairscene.h"

OpenAirScene::OpenAirScene(void)
{
}

OpenAirScene::~OpenAirScene(void)
{
}

/**\brief
 * �����ĳ�ʼ��
 */
BOOL OpenAirScene::Init(void)
{
	if(!m_cSnow.Init())	return FALSE;
	if(!trees.LoadIni("ini/plants.ini","plants"))	return FALSE;
	if(!skybox.Init())	return FALSE;
	if(!water.Init())	return FALSE;

	return TRUE;
}


/**\brief
 * ��INI�ļ���������
 */
BOOL OpenAirScene::LoadIni(char* _filename,char* _index)
{
	return TRUE;
}


/**\brief
 * ���³���������
 */
void OpenAirScene::UpdateData(void)
{
}


/**\brief
 * ��������Ⱦ
 */
void OpenAirScene::Render(void)
{	
	water.Render();
	skybox.Render();
	m_cSnow.Render();
	trees.Render();
}
