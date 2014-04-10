/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __EDIT_H__
#define __EDIT_H__

#include "stdafx.h"
#include "window.h"
#include "ime.h"
#include "font.h"


/**\brief
 * edit�༭����
 */
class Edit : public EGWindow
{
public:
	Edit(void);
	~Edit(void){}


	/**\brief
	 * �Ƿ��������ַ�
	 */
	BOOL IsFocus(){return m_bFocus;}


	/**\brief
	 * ���ý���
	 */
	void SetFocus(BOOL _focus){m_bFocus=_focus;}


	/**\brief
	 * ȡ�ñ༭���е��ַ���
	 */
	char* GetText(){return m_szText;}


	/**\brief
	 * �Ƿ������˻س�
	 */
	BOOL GetReturnState(){return m_bReturn;}
	void SetReturnState(BOOL _b){m_bReturn=_b;}


	/**\brief
	 * ������ʾ���뷨���Ƶ�λ��
	 */
	void SetInputNamePos(EGSPoint2 _point){m_sNamePos=_point;}


	/**\brief
	 * ����������ɫ
	 */
	void SetFontColor(EGSColor _color){m_sFontColor=_color;}


	/**\brief
	 * ȡ��������ɫ
	 */
	EGSColor GetFontColor(){return m_sFontColor;}


	/**\brief
	 * ���ò������ɫ
	 */
	void SetCaretColor(EGSColor _color){m_sCaretColor=_color;}


	/**\brief
	 * ȡ�ò������ɫ
	 */
	EGSColor GetCaretColor(){return m_sCaretColor;}


	/**\brief
	 * �����Ƿ�Ϊ��������
	 */
	void SetPasswordState(BOOL _b){m_bPassword=_b;}


private:
	/**\brief
	 * ���ƿؼ�
	 */
	virtual void OnDraw(void);


	// �Ƿ�������
	BOOL	m_bFocus;

	// �Ƿ��˻س�
	BOOL	m_bReturn;

	// �Ƿ�����������
	BOOL	m_bPassword;

	// ������ַ���
	char	m_szText[256];

	// ���뷨����ʾ��λ��
	EGSPoint2	m_sNamePos;

	// ������λ��
	int		m_iCaret;

	// ������ɫ
	EGSColor	m_sFontColor;

	// �������ɫ
	EGSColor	m_sCaretColor;

	// һ���м���������ڲ��������˸��
	float	m_fDeltaTime;
};


#endif
