/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "Button.h"


EGSound EGCButton::m_cSound;


EGCButton::EGCButton():bHasText(FALSE),bEnable(TRUE),
				m_iTextStyle(BTN_TEXT_CENTER),color1(m_sColor)
{
	color2=EGSColor(0.0f,1.0f,0.0f,1.0f);
	m_sTextColor=EGSColor(0.0f,1.0f,0.0f,1.0f);
}


/**\brief
 * ��INI�ļ�����İ�ť����
 */
BOOL EGCButton::LoadIni(char* _filename,char* _index)
{
	EGCIniFile Ini(_filename);
	
	m_sRect.x=Ini.ReadInt(_index,"x");
	m_sRect.y=Ini.ReadInt(_index,"y");
	m_sRect.width=Ini.ReadInt(_index,"width");
	m_sRect.height=Ini.ReadInt(_index,"height");

	color1.r=PERSENT(Ini.ReadInt(_index,"r"));
	color1.g=PERSENT(Ini.ReadInt(_index,"g"));
	color1.b=PERSENT(Ini.ReadInt(_index,"b"));
	color1.a=PERSENT(Ini.ReadInt(_index,"a"));

	m_chBackTexFile =Ini.ReadText(_index,"BackTexFile");

	bHasText	=Ini.ReadInt(_index,"bHasText");
	m_bBlend	=Ini.ReadInt(_index,"bBlend");
	bEnable		=Ini.ReadInt(_index,"bEnable");
	strcpy(m_chText,Ini.ReadText(_index,"text"));

	if(m_chBackTexFile!=NULL)	this->LoadTexture(m_chBackTexFile,1,m_bBlend);
	if(bHasText==TRUE)		this->SetText(m_chText);

	return TRUE;
}



/**\brief
 * ����ѭ��,�麯�������丸��EGWindow��draw()������
 */
void EGCButton::OnDraw(void)
{
	if(bEnable==FALSE)//��ť������ʱΪ��ɫ
	{
		this->SetColor(EGSColor(0.5f,0.5f,0.5f,1.0f));
		if(bHasText==TRUE)
		{
			SYS_FONT->SetColor(EGSColor(0.0f,0.0f,0.0f,1.0f));
		}
		m_iState=BUTTON_DISABLE;
	}
	else if(bEnable==TRUE)//��ť����ʱ
	{
		if(IsActive()==TRUE)//����ڰ�ť��ʱ
		{
			this->SetColor(color2);
			if(bHasText==TRUE)
			{
				SYS_FONT->SetColor(!m_sTextColor);
			}

			if(EGInput::GetSysInput()->FirstMouseDownL())
			{
				if(EGMusic::GetSysMusic()->GetMusic()) m_cSound.LoadSoundFX(DOWNL_SOUND_NAME);
				if(EGMusic::GetSysMusic()->GetMusic()) m_cSound.Play();
			}

			if(EGInput::GetSysInput()->Clicked())	m_iState=BUTTON_CLICK;
			else if(SYS_MOUSE->ButtonDown(0))		m_iState=BUTTON_DOWNL;
			else if(SYS_MOUSE->ButtonDown(1))		m_iState=BUTTON_DOWNR;
			else									m_iState=BUTTON_ACTIVE;
		}
		else//ͨ�����
		{
			this->SetColor(color1);
			if(bHasText==TRUE)
			{
				SYS_FONT->SetColor(m_sTextColor);
			}
			m_iState=BUTTON_NORMAL;
		}
	}
	
	if(bHasText==TRUE)
	{
		SYS_FONT->Format(m_chText);
		if(m_iTextStyle==BTN_TEXT_LEFT)
			SYS_FONT->PrintAt(m_sRect.x+2,m_sRect.y+((m_sRect.height-SYS_FONT->GetHeight())>>1));
		else if(m_iTextStyle==BTN_TEXT_CENTER)
			SYS_FONT->PrintAt(m_sRect.x+((m_sRect.width-SYS_FONT->GetWidth())>>1),m_sRect.y+((m_sRect.height-SYS_FONT->GetHeight())>>1));
		else //if(m_iTextStyle==BTN_TEXT_RIGHT)
			SYS_FONT->PrintAt(m_sRect.x-2+(m_sRect.width-SYS_FONT->GetWidth()),m_sRect.y+((m_sRect.height-SYS_FONT->GetHeight())>>1));
	}

}
