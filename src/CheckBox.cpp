/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "CHeckBox.h"

/**\brief
 * ��INI�ļ�����
 */
BOOL EGCheckBox::LoadIni(char* filename,char* index)
{
	EGCIniFile Ini(filename);

	m_sRect.x=Ini.ReadInt(index,"x");
	m_sRect.y=Ini.ReadInt(index,"y");
	m_sRect.width=Ini.ReadInt(index,"width");
	m_sRect.height=Ini.ReadInt(index,"height");

	bChecked=Ini.ReadInt(index,"style");

	return TRUE;
}



/**\brief
 *  ����
 */
void EGCheckBox::OnDraw(void)
{
	if(IsActive()==TRUE)//����ڰ�ť��
	{
		this->SetColor(color2);
		
		if(EGInput::GetSysInput()->FirstMouseDownL())
		{
			if(EGMusic::GetSysMusic()->GetMusic())m_cSound.LoadSoundFX(DOWNL_SOUND_NAME);
			if(EGMusic::GetSysMusic()->GetMusic())m_cSound.Play();
		}
		
		if(EGInput::GetSysInput()->Clicked())bChecked=!bChecked;
	}
	else this->SetColor(color1);//��겻�ڰ�ť��


	glLineWidth(2.f);
	////////////////////////////////////
	glColor3f(1.f,0.f,0.f);
	if(bChecked)//���ƶԺ�
	{
		glBegin(GL_LINE_STRIP);
			glVertex2i(m_sRect.x,m_sRect.y+m_sRect.height/2);
			glVertex2i(m_sRect.x+m_sRect.width/2,m_sRect.y);
			glVertex2i(m_sRect.x+m_sRect.width,m_sRect.y+m_sRect.height);
		glEnd();
	}
	else//���ƴ��
	{
		glBegin(GL_LINES);
			glVertex2i(m_sRect.x,m_sRect.y);
			glVertex2i(m_sRect.x+m_sRect.width,m_sRect.y+m_sRect.height);
			glVertex2i(m_sRect.x+m_sRect.width,m_sRect.y);
			glVertex2i(m_sRect.x,m_sRect.y+m_sRect.height);
		glEnd();
	}
	////////////////////////////////////
	glColor3f(1.f,0.f,0.f);	//���Ʊ߿�
	glBegin(GL_LINE_LOOP);
		glVertex2i(m_sRect.x,m_sRect.y);
		glVertex2i(m_sRect.x+m_sRect.width,m_sRect.y);
		glVertex2i(m_sRect.x+m_sRect.width,m_sRect.y+m_sRect.height);
		glVertex2i(m_sRect.x,m_sRect.y+m_sRect.height);
	glEnd();
	////////////////////////////////////
	glLineWidth(1.f);

}
