/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _FONT_H_
#define _FONT_H_

#include "FontBinary.h"


/**\brief
 * ֻ����ʾӢ�ĵ�������
 */
class Font
{
public:
	Font(void):color(EGSColor(0.f,0.f,0.f,1.f)){}
	~Font(void){KillFont();}


	/**\brief
	 * ��ʼ������
	 */
	void InitFont(void);

	
	/**\brief
	 * ����������ɫ
	 */
	void SetColor(EGSColor c){color=c;}


	/**\brief
	 * ȡ��������ɫ
	 */
	EGSColor GetColor(void){return color;}


	/**\brief
	 * ��ʾ��
	 *
	 *\param	x,y		������ʾ��λ��
	 *\param	string	Ҫ��ʾ���ַ���
	 */
	void Print(int x,int y,char *string);


private:
	GLuint	base;

	// ������ɫ
	EGSColor	color;

	/**\brief
	 * �ͷ���Դ
	 */
	void KillFont(void);

};

/////////////////////////////////////////////////////////////

#define SYS_FONT (HZFont::GetSysFont())

/**\brief
 * ���Խ�����Ӣ�Ļ����ʾ��������
 */
class HZFont
{
public:
	HZFont(void);
	~HZFont(void);

	/**\brief
	 * ����������ɫ
	 */
	void SetColor(EGSColor c){color=c;}


	/**\brief
	 * ȡ��������ɫ
	 */
	EGSColor GetColor(void){return color;}


	/**\brief
	 * ��Ҫ������ַ�����ʽ��
	 */
	void Format(char* string){cb.Format(string);}


	/**\brief
	 * ��Ҫ������ַ�����ʽ��
	 */
	void Format(unsigned char* string){cb.Format(string);}


	/**\brief
	 * �õ��ַ����߶�
	 */
	unsigned int GetHeight(void){return cb.GetHigh();}


	/**\brief
	 * �õ��ַ������
	 */
	unsigned int GetWidth(void){return cb.GetWidth();}


	/**\brief
	 * ��ʾ��
	 *
	 *\param	x,y		������ʾ��λ��
	 */
	void PrintAt(int x,int y);

	static HZFont* GetSysFont(){return m_pFont;}

private:
	// ������ɫ
	EGSColor	color;

	static CharacterBinary cb;

	static HZFont* m_pFont;

};


///////////////////////////////////////////////////////
//-------------------inline����ʵ��--------------------

/**\brief
 * ��ʾ��
 *
 *\param	x,y		������ʾ��λ��
 */
inline void HZFont::PrintAt(int x,int y)
{
	glColor3f(color.r,color.g,color.b);
	glRasterPos2i(x,y);
	glBitmap(cb.GetWidth(),cb.GetHigh(),0,0,(GLfloat)cb.GetWidth(),0,cb.GetBinary());
	glFlush();
}


#endif
