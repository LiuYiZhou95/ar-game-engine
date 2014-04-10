/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "aviscene.h"
#include "inifile.h"

AVIScene::AVIScene(void):m_strAVIFile(NULL)
{
}

AVIScene::~AVIScene(void)
{
	m_cAVI.Stop();
	_DELETE(m_strAVIFile);
}


/**\brief
 * �����ĳ�ʼ��
 */
BOOL AVIScene::Init(void)
{
	if(!m_cAVI.Init(EGInput::GetSysHWnd()))return FALSE;

	return TRUE;
}


/**\brief
 * ��INI�ļ���������
 */
BOOL AVIScene::LoadIni(char* _filename,char* _index)
{
	EGCIniFile Ini(_filename);
	m_strAVIFile=Ini.ReadText(_index,"AVIFile");

	return TRUE;
}


/**\brief
 * ���³�������
 */
void AVIScene::UpdateData(void)
{
}


/**\brief
 * ��������Ⱦ
 */
void AVIScene::Render(void)
{
	if(!m_strAVIFile)return;

	m_cAVI.Load(m_strAVIFile);
	m_cAVI.Play();
	if(SYS_KEYBOARD->KeyDown(DIK_ESCAPE)||SYS_MOUSE->ButtonDown(1))m_cAVI.Stop();

}
