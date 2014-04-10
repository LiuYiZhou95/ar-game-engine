/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "stdafx.h"
#include "texture.h"
#include "Input.h"
#include "IniFile.h"


/**\brief
 *  ������
 */
class EGWindow  
{
public:
	EGWindow(void);
	EGWindow(EGSRect _rect);
	virtual ~EGWindow(void){}

	/**\brief
	 * ȡ�ô����˳�ʱ���ص�ֵ
	 */
	int GetState(void){return m_iState;}


	/**\brief
	 * �������״̬
	 */
	void ClearState(void){m_iState=0;}

	/**\brief
	 * �����Ƿ���ʾ
	 */
	void SetVisible(BOOL _visible){m_bVisible=_visible;}


	/**\brief
	 * ȡ���Ƿ���ʾ
	 */
	BOOL GetVisible(void){return m_bVisible;}


	/**\brief
	 * �����Ƿ�͸��
	 */
	void SetBlend(BOOL _blend){m_bBlend=_blend;}


	/**\brief
	 * �Ƿ�͸������
	 */
	BOOL GetBlend(){return m_bBlend;}


	/**\brief
	 * ���ô�����ɫ,������color.a�����ƴ��ڵ�͸����
	 */
	void SetColor(EGSColor _color){m_sColor=_color;}


	/**\brief
	 * ���ô������ھ���
	 */
	void SetRect(EGSRect _rect){m_sRect=_rect;}


	/**\brief
	 * ��ñ�����ɫ
	 */
	EGSColor GetColor(void){return m_sColor;}


	/**\brief
	 * ��ô������ھ���
	 */
	EGSRect GetRect(void){return m_sRect;}


	/**\brief
	 * �����Ƿ��ڻ״̬
	 */
	BOOL IsActive(void);
	


	/**\brief
	 * �ƶ�����
	 */
	void move(int _dx,int _dy){m_sRect.x+=_dx;m_sRect.y+=_dy;}


	/**\brief
	 * ��������
	 *
	 *\param	_filename	�����ļ���
	 *\param	_num		�ذ�ש����ÿ��ש�Ŀ���
	 *\param	_bBlend		�Ƿ�͸������
	 */
	void LoadTexture(char* _filename,int _num,BOOL _bBlend);


	/**\brief
	 * ���ƴ���
	 */
	void draw(void);


	/**\brief
	 * ��INI�ļ����봰������
	 */
	virtual BOOL LoadIni(char* _filename,char* _index);


private:
	// �Ƿ���������
	BOOL	m_bBmpBack;

	// �ذ�ש����ÿ��ש�Ŀ���
	int		m_nNum;
	
	// ���ڵ�����
	EGCTexture m_cTexture;
	
	
	/**\brief
	 * ���ⵣ���Ż��ƴ��ڵ����Σ����д��ڵ���ѭ��
	 */
	virtual void OnDraw(void){}

protected:
	// ���ڱ�����ɫ
	EGSColor	m_sColor;

	// �������ھ���
	EGSRect	m_sRect;

	// �Ƿ�͸������ʹ��ɫ����͸����
	BOOL	m_bBlend;

	// �Ƿ���ʾ
	BOOL	m_bVisible;

	// �����ļ���
	char*	m_chBackTexFile;

	// ���ڵ�״̬�����Դ���һ��ֵ
	int m_iState;

};


#endif
