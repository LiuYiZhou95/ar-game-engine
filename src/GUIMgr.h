/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __GUI_MGR_H__
#define __GUI_MGR_H__

#include "ListView.h"
#include "edit.h"
#include "dialog.h"
#include "animate.h"
#include "window.h"
#include "ListView.h"
#include "edit.h"
#include "mapview.h"
#include "progressbar.h"
#include "SceneMgr.h"
#include "VideoView.h"
#include "RecordSkillView.h"
#include "StoryDialog.h"
#include "TestPic.h"
#include "RecordSkill.h"

/**\brief
 * ���������
 */
class GUIMgr
{
public:
	GUIMgr(void);
	~GUIMgr(void);
	
	static GUIMgr* GetSysGUIMgr(){return m_pGUIMgr;}

	/**\brief
	 * ��INI�ļ�����������
	 */
	BOOL LoadCurIni(char* _filename,char* _index);


	/**\brief
	 * �������Ⱦ
	 */
	void Render(void);


	/**\brief
	 * ���뵭��
	 */
	void Fade(void);

	/**\brief
	 * ��ʼ���ֵ��뵭��Ч��
	 */
	void BeginFade(void){m_fFadeAlpha=1.f;}


private:
	static GUIMgr* m_pGUIMgr;
	EGAnimate m_cCursor;
	EGWindow bottom;

	ListView	m_cChatList;

	// ���������
	Edit		m_cChatEdit;

	// ���˵�
	Dialog		m_cMainMenu;
    Dialog      m_cVideoMenu;
	// С��ͼ
	MapView		m_cMapView;
	BOOL		m_bTopMenu;
	
	//��ͼ����
	VideoView	m_cVideoView;

	//�����趨��
	RecordSkillView m_cRecordSkillView;

	//���±���
	StoryDialog m_cStoryDialog;

	// �Ƿ񵯳����Ի���
	BOOL		m_bMainMenu;
    BOOL        m_bVideoMenu;
	// �����С�˵�
	Dialog		m_cTopMenu;
	
	// ʮ�ּ��ܲ˵�
	Dialog		m_cSkillMenu;

	// �������Ƶ��뵭���ı���
	float		m_fFadeAlpha;

	/////////////////////////////////////////
	// Ӣ�۵�Ѫ��
	EGProgressBar m_cRoleLife;

	// �����Ѫ��
	EGProgressBar m_cMonsterLife;

	// Ӣ�����Դ���
	Dialog		m_cPropertyWnd;
	/**\brief
	 * Ӣ�۵�����
	 */
	void Property(void);

	// Ӣ�۵���Ʒ������
	Dialog		m_cBagWnd;
	/**\brief
	 * Ӣ�۵���Ʒ��
	 */
	void Bag(void);

	/**\brief
	 * ����Ի���
	 */
	void Dialog(void);
	void MosDialog(void);

	/**\brief
	 * ����ͼ���ѡ��궨
	 */
	void MarkSkillMenu();

	BOOL m_bStop();
	///////////////////////////////////////////
	EGCTexture	m_cLifeTex;
	EGCTexture	m_cMagicTex;
	TestPic testPic;

	/**\brief
	 * �������ħ����Ļ���
	 */
	void Ball(EGCTexture tex,float x,float y,float pos);
};

#endif
