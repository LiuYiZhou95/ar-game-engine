#include "stdafx.h"
#include "ProgressBar.h"


EGProgressBar::EGProgressBar():pos(0.0f),border(3)
{
	BarColor=EGSColor(0.0f,1.0f,1.0f,0.0f);
	m_sRect=EGSRect(0,0,100,20);
}



/**\brief
 * ���ƽ�����
 *
 * �麯�������丸��EGWindow��draw()������
 */
void EGProgressBar::OnDraw(void)
{
	if(pos>1.0f)pos=1.0f;
	if(pos<0.0f)pos=0.0f;

	glColor4f(BarColor.r,BarColor.g,BarColor.b,BarColor.a);
	glBegin(GL_QUADS);
		glVertex2i(m_sRect.x+border,m_sRect.y+m_sRect.height-border);
		glVertex2i(m_sRect.x+border,m_sRect.y+border);
		glVertex2i(m_sRect.x+border+(int)(pos*(m_sRect.width-2.0f*border)),m_sRect.y+border);
		glVertex2i(m_sRect.x+border+(int)(pos*(m_sRect.width-2.0f*border)),m_sRect.y+m_sRect.height-border);
	glEnd();
}


/**\brief
 * ��INI�ļ����봰������
 */
BOOL EGProgressBar::LoadIni(char* filename,char* index)
{
	EGCIniFile Ini(filename);
	
	m_sRect.x=Ini.ReadInt(index,"x");
	m_sRect.y=Ini.ReadInt(index,"y");
	m_sRect.width=Ini.ReadInt(index,"width");
	m_sRect.height=Ini.ReadInt(index,"height");

	//����ɫ
	m_sColor.r	=PERSENT(Ini.ReadInt(index,"c1r"));
	m_sColor.g	=PERSENT(Ini.ReadInt(index,"c1g"));
	m_sColor.b	=PERSENT(Ini.ReadInt(index,"c1b"));
	m_sColor.a	=PERSENT(Ini.ReadInt(index,"c1a"));
	//������ɫ
	BarColor.r	=PERSENT(Ini.ReadInt(index,"c2r"));
	BarColor.g	=PERSENT(Ini.ReadInt(index,"c2g"));
	BarColor.b	=PERSENT(Ini.ReadInt(index,"c2b"));
	BarColor.a	=PERSENT(Ini.ReadInt(index,"c2a"));

	border=Ini.ReadInt(index,"border");
	pos=PERSENT(Ini.ReadInt(index,"pos"));

	return TRUE;
}

