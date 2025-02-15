/**
 *作者：范修盛
 *2011年10月30日
 */
#pragma once
#ifndef _FONT_H_
#define _FONT_H_

#include "FontBinary.h"


/**\brief
 * 只能显示英文的字体类
 */
class Font
{
public:
	Font(void):color(EGSColor(0.f,0.f,0.f,1.f)){}
	~Font(void){KillFont();}


	/**\brief
	 * 初始化字体
	 */
	void InitFont(void);

	
	/**\brief
	 * 设置字体颜色
	 */
	void SetColor(EGSColor c){color=c;}


	/**\brief
	 * 取得字体颜色
	 */
	EGSColor GetColor(void){return color;}


	/**\brief
	 * 显示字
	 *
	 *\param	x,y		字所显示的位置
	 *\param	string	要显示的字符串
	 */
	void Print(int x,int y,char *string);


private:
	GLuint	base;

	// 字体颜色
	EGSColor	color;

	/**\brief
	 * 释放资源
	 */
	void KillFont(void);

};

/////////////////////////////////////////////////////////////

#define SYS_FONT (HZFont::GetSysFont())

/**\brief
 * 可以进行中英文混合显示的字体类
 */
class HZFont
{
public:
	HZFont(void);
	~HZFont(void);

	/**\brief
	 * 设置字体颜色
	 */
	void SetColor(EGSColor c){color=c;}


	/**\brief
	 * 取得字体颜色
	 */
	EGSColor GetColor(void){return color;}


	/**\brief
	 * 将要输出的字符串格式化
	 */
	void Format(char* string){cb.Format(string);}


	/**\brief
	 * 将要输出的字符串格式化
	 */
	void Format(unsigned char* string){cb.Format(string);}


	/**\brief
	 * 得到字符串高度
	 */
	unsigned int GetHeight(void){return cb.GetHigh();}


	/**\brief
	 * 得到字符串宽度
	 */
	unsigned int GetWidth(void){return cb.GetWidth();}


	/**\brief
	 * 显示字
	 *
	 *\param	x,y		字所显示的位置
	 */
	void PrintAt(int x,int y);

	static HZFont* GetSysFont(){return m_pFont;}

private:
	// 字体颜色
	EGSColor	color;

	static CharacterBinary cb;

	static HZFont* m_pFont;

};


///////////////////////////////////////////////////////
//-------------------inline函数实现--------------------

/**\brief
 * 显示字
 *
 *\param	x,y		字所显示的位置
 */
inline void HZFont::PrintAt(int x,int y)
{
	glColor3f(color.r,color.g,color.b);
	glRasterPos2i(x,y);
	glBitmap(cb.GetWidth(),cb.GetHigh(),0,0,(GLfloat)cb.GetWidth(),0,cb.GetBinary());
	glFlush();
}


#endif
