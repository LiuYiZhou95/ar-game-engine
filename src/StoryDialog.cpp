/**
 *���ߣ��ӻ�ͥ
 *2011��10��30��
 */
#include "StoryDialog.h"
#include "Font.h"
#include "ARMgr.h"
#include "CoreEngine.h"

StoryDialog::StoryDialog(void):m_pButton(NULL),m_nButtonNum(0),m_escapeTime(12.0f){}

StoryDialog::~StoryDialog(void){}

BOOL StoryDialog::LoadIni(char* _filename,char* _index)
{
	EGCIniFile Ini(_filename);

	m_sRect.width=Ini.ReadInt(_index,"width");
	m_sRect.height=Ini.ReadInt(_index,"height");

	m_chBackTexFile =Ini.ReadText(_index,"BackTexFile");
	
	m_bBlend=TRUE;
	m_sColor=EGSColor(1.f,1.f,1.f,1.0f);
	m_sRect.x = Ini.ReadInt(_index,"x");
	m_sRect.y = Ini.ReadInt(_index,"y");
	m_sColor.r=PERSENT(Ini.ReadInt(_index,"r"));
	m_sColor.g=PERSENT(Ini.ReadInt(_index,"g"));
	m_sColor.b=PERSENT(Ini.ReadInt(_index,"b"));
	m_sColor.a=PERSENT(Ini.ReadInt(_index,"a"));
	if(m_chBackTexFile==NULL)return FALSE;
	this->LoadTexture(m_chBackTexFile,1,m_bBlend);

	m_nButtonNum=Ini.ReadInt(_index, "ButtonNum");
	m_pButton=new EGCButton[m_nButtonNum];

	//��ʼ����ť
	char* strFile;
	char* strIndex;
	for(unsigned int i=0; i<m_nButtonNum; ++i)
	{
		strFile = Ini.ReadText(_index, i);
		strIndex = Ini.ReadData(_index,i);
		m_pButton[i].LoadIni(strFile, strIndex);
		_FREE(strFile);
		_FREE(strIndex);
	}
	return TRUE;
}


char story[][256]={
	"ͨ����ʿ���ݵ�ͨ��֮�ۼ�ͨ��֮��",
	"��ͨ���½��ʥ������ԴȪ,Ҳ��ͨ���½������ʵ��½�ķ�����",
	"��ȡһ��������ͨ�鷨�����Դ�ͨ���½����ʵ��½�Ĵ�����",
	"����ͨ���½����ħ���ڴ�������,��������ʵ��½......",
	"����������ɱͨ��սʿ,�ռ��㹻������ͨ�鱦��...",
	"ħ�С�ӹԹԵĽ������ϵķ������������ǾͲ������ˣ�",
	"Ӣ�ۣ�ͨ��֮��������������ɣ����ǲ�����������ȺС�������ģ�"};

/**\brief
 * ������ͼ����
 */
void StoryDialog::OnDraw(void)
{
	EGSColor cc;	
	cc.r = 1.0f;
	cc.g = 0.0f;
	cc.b = 0.0f;
	cc.a = 1.0f;

	m_escapeTime -= SYS_TIMER->m_fTime;
	
	if(m_escapeTime >= 6.001f)
	{
		for(int i = 0; i < 5; i++)
		{
			SYS_FONT->SetColor(cc);
			SYS_FONT->Format(story[i]);
			SYS_FONT->PrintAt(200,100 - i * 20);
		}
	}
	else if(m_escapeTime >= 3.001f)
	{
		SYS_FONT->SetColor(cc);
		SYS_FONT->Format(story[5]);
		SYS_FONT->PrintAt(500,100);
	}
	else
	{
		cc.r = 0.0f;
		cc.b = 1.0f;
		cc.g = 1.0f;
		SYS_FONT->SetColor(cc);
		SYS_FONT->Format(story[6]);
		SYS_FONT->PrintAt(200,100);
	}
	
	
	if(m_escapeTime <= 0.001f)
	{
		SetVisible(FALSE);
		m_escapeTime = 12.0f;
		SYS_COEG->SetStop(FALSE);
		return;
	}
	else
	{
		SYS_COEG->SetStop(TRUE);
	}
	//���ư�ť
	for(unsigned int i=0;i<m_nButtonNum;++i)m_pButton[i].draw();

	for(unsigned int i=0;i<m_nButtonNum;++i)
	{
		if(m_pButton[i].GetState()==BUTTON_DOWNL)this->m_iState=-1*(i+1);
		if(m_pButton[i].GetState()==BUTTON_CLICK)this->m_iState=i+1;
	}
	if(m_pButton[0].GetState()==BUTTON_DOWNL)
	{
	    SetVisible(FALSE);
		m_escapeTime = 12.0f;
		SYS_COEG->SetStop(FALSE);
	}
}