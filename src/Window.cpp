/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "Window.h" 

EGWindow::EGWindow(void):m_nNum(1),m_bBlend(FALSE),m_chBackTexFile(NULL),
					m_bVisible(TRUE),m_bBmpBack(FALSE)
{
	m_sRect=EGSRect(0,0,100,100);
	m_sColor=EGSColor(1.0f,1.0f,1.0f,1.0f);
}


EGWindow::EGWindow(EGSRect _rect):m_nNum(1),m_bBlend(FALSE),m_chBackTexFile(NULL),
					m_bVisible(TRUE),m_bBmpBack(FALSE)
{
	m_sRect=_rect;
	m_sColor=EGSColor(1.0f,1.0f,1.0f,1.0f);
}


/**\brief
 * ��������
 *
 *\param	_filename	�����ļ���
 *\param	_num		�ذ�ש����ÿ��ש�Ŀ���
 *\param	_bBlend		�Ƿ�͸������
 */
void EGWindow::LoadTexture(char* _filename,int _num,BOOL _bBlend)
{
	m_nNum=_num;
	m_bBmpBack=TRUE;
	m_chBackTexFile=_filename;
	m_bBlend=_bBlend;

	m_cTexture.InitTexture(_filename,m_bBlend);	//װ������
}


/**\brief
 * �����Ƿ��ڻ״̬
 */
BOOL EGWindow::IsActive(void)
{
	EGSPoint2 p=SYS_MOUSE->GetMousePos();

	if(		p.x>=m_sRect.x&&p.x<=m_sRect.x+m_sRect.width
		&&	p.y>=m_sRect.y&&p.y<=m_sRect.y+m_sRect.height)
		return TRUE;
	else return FALSE;
}


/**\brief
 * ��INI�ļ����봰������
 */
BOOL EGWindow::LoadIni(char* _filename,char* _index)
{
	EGCIniFile Ini(_filename);
	
	m_sRect.x=Ini.ReadInt(_index,"x");
	m_sRect.y=Ini.ReadInt(_index,"y");
	m_sRect.width=Ini.ReadInt(_index,"width");
	m_sRect.height=Ini.ReadInt(_index,"height");

	m_sColor.r=PERSENT(Ini.ReadInt(_index,"r"));
	m_sColor.g=PERSENT(Ini.ReadInt(_index,"g"));
	m_sColor.b=PERSENT(Ini.ReadInt(_index,"b"));
	m_sColor.a=PERSENT(Ini.ReadInt(_index,"a"));

	m_chBackTexFile =Ini.ReadText(_index,"BackTexFile");
	m_bBlend=Ini.ReadInt(_index,"bBlend");

	if(m_chBackTexFile==NULL)return FALSE;
	this->LoadTexture(m_chBackTexFile,1,m_bBlend);

	return TRUE;
}


/**\brief
 * ���ƴ���
 */
void EGWindow::draw()
{
	if(m_bVisible==FALSE)return;

	if(m_bBmpBack)
	{
		glEnable(GL_TEXTURE_2D);
		m_cTexture.Bind(0);

		if(m_bBlend==TRUE)
		{
			glEnable(GL_BLEND);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER , 0.0f);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		}

		glBegin(GL_QUADS);
		glColor4f(m_sColor.r,m_sColor.g,m_sColor.b,m_sColor.a);
			glTexCoord2f(0.0f,0.0f);
			glVertex2i(m_sRect.x,m_sRect.y);

			glTexCoord2f((float)m_nNum,0.0f);
			glVertex2i(m_sRect.x+m_sRect.width,m_sRect.y);

			glTexCoord2f((float)m_nNum,(float)m_nNum);
			glVertex2i(m_sRect.x+m_sRect.width,m_sRect.y+m_sRect.height);

			glTexCoord2f(0.0f,(float)m_nNum);
			glVertex2i(m_sRect.x,m_sRect.y+m_sRect.height);
		glEnd();


		if(m_bBlend==TRUE)
		{
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);
		}
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		if(m_bBlend==TRUE)glEnable(GL_BLEND);
		glBegin(GL_QUADS);
		glColor4f(m_sColor.r,m_sColor.g,m_sColor.b,m_sColor.a);
			glVertex2i(m_sRect.x,m_sRect.y);
			glVertex2i(m_sRect.x+m_sRect.width,m_sRect.y);
			glVertex2i(m_sRect.x+m_sRect.width,m_sRect.y+m_sRect.height);
			glVertex2i(m_sRect.x,m_sRect.y+m_sRect.height);
		glEnd();
		if(m_bBlend==TRUE)glDisable(GL_BLEND);
	}

	OnDraw();
}
