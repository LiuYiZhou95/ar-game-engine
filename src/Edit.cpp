/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "edit.h"
#include "timer.h"

Edit::Edit(void)
	:m_bFocus(FALSE),m_iCaret(0),m_bReturn(FALSE),m_sNamePos(EGSPoint2(5,130)),m_bPassword(FALSE),
	m_fDeltaTime(0.f),m_sFontColor(EGSColor(1.f,1.f,1.f,1.f)),m_sCaretColor(EGSColor(1.f,1.f,1.f,1.f))
{
	ZeroMemory(m_szText,256);
	m_sColor=EGSColor(0.f,0.f,0.f,1.f);
	m_sRect=EGSRect(10,20,400,24);
}


/**\brief
 * ���ƿؼ�
 */
void Edit::OnDraw(void)
{
	// ����edit�Ŀ�Ⱥ͸߶�
	m_sRect.height=16;
	if((m_sRect.width)%16!=2)m_sRect.width-=m_sRect.width%16-16-2;


	// ȷ���Ƿ񻹿�������
	if( IsActive()&&EGInput::GetSysInput()->GetMouse()->ButtonDown(0)&&m_bFocus==FALSE)
	{
		m_bFocus=TRUE; EGIme::GetSysIme()->Enable();
	}
	if(!IsActive()&&EGInput::GetSysInput()->GetMouse()->ButtonDown(0))
	{
		m_bFocus=FALSE;//EGIme::GetSysIme()->Disable();
	}

	SYS_FONT->SetColor(EGSColor(1.f,0.f,0.f,1.f)/*m_sFontColor*/);
	SYS_FONT->Format(EGIme::GetSysIme()->GetImeName());
	SYS_FONT->PrintAt(m_sNamePos.x,m_sNamePos.y);
	SYS_FONT->Format(EGIme::GetSysIme()->GetImeInputCompStr());
	SYS_FONT->PrintAt(m_sNamePos.x,m_sNamePos.y-18);

	// ��ʾ����
	if(m_bFocus)
	{
		m_iCaret=EGIme::GetSysIme()->GetWordCaret();
		if(m_iCaret<=(m_sRect.width/16-1))
		{
			EGIme::GetSysIme()->SetReceiveChar(true);
			strcpy(m_szText,EGIme::GetSysIme()->GetImeInputResultStr());
		}
		else
		{
			m_iCaret=m_sRect.width/16-1;
			EGIme::GetSysIme()->SetReceiveChar(false);
		}

		m_fDeltaTime-=SYS_TIMER->m_fTime;
		if(m_fDeltaTime<=0.0f)m_fDeltaTime=1.0f;
		if(m_fDeltaTime<0.5f)
		{
			glColor3f(m_sCaretColor.r,m_sCaretColor.g,m_sCaretColor.b);
			glBegin(GL_LINES);
				glVertex2i(m_sRect.x+1+(m_iCaret+1)*16,m_sRect.y);
				glVertex2i(m_sRect.x+1+(m_iCaret+1)*16,m_sRect.y+m_sRect.height);
			glEnd();
		}

		if(EGIme::GetSysIme()->GetReturnState())
		{
			m_bReturn=TRUE;
			EGIme::GetSysIme()->Disable();
			EGIme::GetSysIme()->Enable();
		}

	}else m_bReturn=FALSE;

	SYS_FONT->SetColor(m_sFontColor);
	if(!m_bPassword)//ƽ������״̬
	{
		SYS_FONT->Format(m_szText);
		SYS_FONT->PrintAt(m_sRect.x,m_sRect.y);
	}
	else	//��������״̬ʱ��ʾ"*"
	{
		char str[256];
		size_t  i=strlen(m_szText);
		memset(str,'*',i);
		str[i]='\0';
		SYS_FONT->Format(str);
		SYS_FONT->PrintAt(m_sRect.x,m_sRect.y);
	}
}
