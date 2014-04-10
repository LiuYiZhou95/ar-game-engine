/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "StdAfx.h"
#include "Window.h"
#include "Font.h"
#include "IniFile.h"
#include "Sound.h"
#include "Music.h"


// ��ť������ʱҪ���ŵ������ļ�
#define DOWNL_SOUND_NAME "sound\\click.wav"


/**\brief
 * ��ť��
 */
class EGCButton : public EGWindow
{
public:


public:
	EGCButton();
	virtual ~EGCButton(){}


	/**\brief
	 * ���ð�ť�ϵ���
	 */
	void	SetText(char* str){bHasText=TRUE;strcpy(m_chText,str);}


	/**\brief
	 * ȡ�ð�ť�ϵ���
	 */
	char*	GetText(){return m_chText;}


	/**\brief
	 * ���ð�ť�ϵ��ֵ���ʾ����
	 */
	void	SetTextStyle(int _style){m_iTextStyle=_style;}


	/**\brief
	 * ȡ�ð�ť�ϵ��ֵ���ʾ����
	 */
	int		GetTextStyle(){return m_iTextStyle;}


	/**\brief
	 * ���ð�ť�ڻʱ����ɫ
	 */
	void	SetActiveColor(EGSColor c){color2=c;}


	/**\brief
	 * ȡ�ð�ť�ʱ����ɫ
	 */
	EGSColor	GetActiveColor(){return color2;}


	/**\brief
	 * ���ð�ťƽ������ɫ
	 */
	void	SetNormalColor(EGSColor _color){color1=_color;}


	/**\brief
	 * ȡ�ð�ť�ʱ����ɫ
	 */
	EGSColor	GetNormalColor(){return color1;}


	/**\brief
	 * �����������ɫ
	 */
	void	SetTextColor(EGSColor _color){m_sTextColor=_color;}


	/**\brief
	 * ���ð�ť�Ƿ����
	 */
	void	SetEnable(BOOL _anable){bEnable=_anable;}


	/**\brief
	 * ȡ�ð�ť�Ƿ����
	 */
	BOOL	GetEnable(){return bEnable;}


	/**\brief
	 * ��INI�ļ�����İ�ť����
	 */
	virtual BOOL LoadIni(char* _filename,char* _index);



private:
	// ��ť�ϵ���
	char	m_chText[256];
	
	// ��ť���Ƿ�����
	BOOL	bHasText;

	// ��ť�Ƿ����
	BOOL	bEnable;

	/**\brief
	 * ����ѭ��,�麯�������丸��EGWindow��draw()������
	 */
	virtual void OnDraw(void);


protected:
	// �����ͣ���ȡBTN_TEXT_LEFT,BTN_TEXT_CENTER,BTN_TEXT_RIGHT
	int		m_iTextStyle;

	// ��ťƽʱ����ɫ
	EGSColor	color1;

	// ��ť������ʱ����ɫ
	EGSColor	color2;

	// ������ɫ
	EGSColor	m_sTextColor;
	
	// ��갴��ʱ������
	static	EGSound m_cSound;

};

#endif
