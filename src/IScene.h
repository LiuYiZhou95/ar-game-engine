/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __I_SCENE_H__
#define __I_SCENE_H__


/**\brief
 * ��Ϸ�еĳ���
 */
enum GAME_SCENE
{
	// �ճ���
	SCE_NULL=0,

	// ��Ƶ��������
	SCE_AVI,

	// ��ʼʱ����Ļ����
	SCE_TITLE,

	// �����ɫѡ�񳡾�
	SCE_SELCHAR,

	// ���ⳡ��
	SCE_OPENAIR,

	// ���ڳ���
	SCE_ROOM
};


/**\brief
 * ������Ļ���(����)
 */
class IScene
{
public:
	IScene(void);
	virtual ~IScene(void);


	/**\brief
	 * �����ĳ�ʼ��
	 */
	virtual BOOL Init(void)=0;


	/**\brief
	 * ��IIN�ļ���������
	 */
	virtual BOOL LoadIni(char* _filename,char* _index)=0;


	/**\brief
	 * ���ݵĸ���
	 */
	virtual void UpdateData(void)=0;


	/**\brief
	 * ��������Ⱦ
	 */
	virtual void Render(void)=0;

};


#endif
