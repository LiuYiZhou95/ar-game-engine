/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "ScrollBar.h"


EGCScrollBar::EGCScrollBar()
{
	btn1=new EGCButton;
	btn2=new EGCButton;
	CenBtn=new EGCButton;

	x=100; y=100; width=21;//25;
	style=TRUE;
	pos=0.0f;

	MaxLength=200; MinPos=0.05f;
	CellLength=width;
}


EGCScrollBar::~EGCScrollBar()
{
	_DELETE(btn1);
	_DELETE(btn2);
	_DELETE(CenBtn);
}


/**\brief
 * ��INI�ļ�����
 */
BOOL EGCScrollBar::LoadIni(char* filename,char* index)
{
	EGCIniFile Ini(filename);
	x			=Ini.ReadInt(index,"x");
	y			=Ini.ReadInt(index,"y");
	width		=Ini.ReadInt(index,"width");
	MaxLength	=Ini.ReadInt(index,"MaxLength");
	CellLength	=Ini.ReadInt(index,"CellLength");
	style		=Ini.ReadInt(index,"style");
	pos			=PERSENT( Ini.ReadInt(index,"pos") );

	return TRUE;
}


/**\brief
 * �������Ƿ��ڻ״̬��������Ƿ�������
 */
BOOL EGCScrollBar::IsActive(void)
{
	EGSPoint2 p=SYS_MOUSE->GetMousePos();

	if(style==TRUE)
	{
		if(		p.x>=x&&p.x<=x+MaxLength
			&&	p.y>=y&&p.y<=y+width)
			return TRUE;
		else return FALSE;
	}
	else
	{
		if(		p.y>=y&&p.x<=y+MaxLength
			&&	p.x>=x&&p.x<=x+width)
			return TRUE;
		else return FALSE;
	}
}


/**\brief
 * ���ƹ�����
 */
void EGCScrollBar::draw(void)
{
	//������¼������ť���ڵ�λ��
	EGSRect r1;	r1=btn1->GetRect();
	EGSRect r2;	r2=btn2->GetRect();
	EGSRect r3;	r3=CenBtn->GetRect();

	//�����ƶ�����
	if(btn1->GetState()==BUTTON_DOWNL&&pos>0.0f)pos=pos-MinPos;
	if(btn2->GetState()==BUTTON_DOWNL&&pos<1.0f)pos=pos+MinPos;

	if(CenBtn->GetState()==BUTTON_DOWNL&&pos>=0.0f&&pos<=1.0f)
	{
		EGSPoint2 p=SYS_MOUSE->GetMousePos();
		if(style==TRUE)
		{
			static float bx=(float)p.x;
			pos=pos-(p.x-bx)/(MaxLength-r1.width-r2.width-CellLength);
			bx=(float)p.x;
		}
		else
		{
			static float by=(float)p.y;
			pos=pos-(p.y-by)/(MaxLength-r1.height-r2.height-CellLength);
			by=(float)p.y;
		}
	}
	if(pos<0)pos=0;
	if(pos>1)pos=1;


	//�������ƹ�����
	if(style==TRUE)	//����ˮƽ������
	{
		//����
		r3.x=x+r1.width+(int)(pos*(MaxLength-r1.width-r2.width-CellLength));
		r3.y=y;
		r3.width=CellLength;
		r3.height=width;
		CenBtn->SetRect(r3);
		CenBtn->draw();


		//��ť
		r1.x=x;
		r1.y=y;
		r1.width=width;
		r1.height=width;
		btn1->SetRect(r1);
		btn1->draw();

		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_TRIANGLES);
			glVertex2i(r1.x,			r1.y+r1.height/2);
			glVertex2i(r1.x+r1.width,	r1.y			);
			glVertex2i(r1.x+r1.width,	r1.y+r1.height	);
		glEnd();


		//�Ұ�ť
		r2.x=x+MaxLength-width;
		r2.y=y;
		r2.width=width;
		r2.height=width;
		btn2->SetRect(r2);
		btn2->draw();

		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_TRIANGLES);
			glVertex2i(r2.x+r2.width,	r2.y+r2.height/2);
			glVertex2i(r2.x,			r2.y+r2.height	);
			glVertex2i(r2.x,			r2.y			);
		glEnd();

		//����
		glColor3f(0.0f,0.0f,0.0f);
		glLineWidth(2.f);
		glBegin(GL_LINES);
			glVertex2i(r1.x,			r1.y);
			glVertex2i(r2.x+r2.width,	r2.y);

			glVertex2i(r1.x,			r1.y+r1.height);
			glVertex2i(r2.x+r2.width,	r2.y+r2.height);
		glEnd();
		glLineWidth(1.f);
	}
	else					//������ֱ������
	{
		//����
		r3.x=r1.x;
		r3.y=r1.y-CellLength-(int)(pos*(MaxLength-r1.height-r2.height-CellLength));
		r3.width=width;
		r3.height=CellLength;
		CenBtn->SetRect(r3);
		CenBtn->draw();


		//�ϰ�ť
		r1.x=x;
		r1.y=y+MaxLength-width;
		r1.width=width;
		r1.height=width;
		btn1->SetRect(r1);
		btn1->draw();

		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_TRIANGLES);
			glVertex2i(r1.x+r1.width/2,	r1.y+r1.height	);
			glVertex2i(r1.x,			r1.y			);
			glVertex2i(r1.x+r1.width,	r1.y			);
		glEnd();


		//�°�ť
		r2.x=x;
		r2.y=y;
		r2.width=width;
		r2.height=width;
		btn2->SetRect(r2);
		btn2->draw();

		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_TRIANGLES);
			glVertex2i(r2.x+r2.width/2,	r2.y			);
			glVertex2i(r2.x+r2.width,	r2.y+r2.height	);
			glVertex2i(r2.x,			r2.y+r2.height	);
		glEnd();


		//����
		glColor3f(0.0f,0.0f,0.0f);
		glLineWidth(2.f);
		glBegin(GL_LINES);
			glVertex2i(r1.x,			r1.y+r2.height	);
			glVertex2i(r2.x,			r2.y			);

			glVertex2i(r1.x+r1.width,	r1.y+r2.height	);
			glVertex2i(r2.x+r2.width,	r2.y			);
		glEnd();
		glLineWidth(1.f);
	}
}
