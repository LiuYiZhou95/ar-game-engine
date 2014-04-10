/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef _MOTION_ANALYSIS_H_
#define _MOTION_ANALYSIS_H_
#include "stdAfx.h"
#include <AR/gsub.h>
#include <AR/param.h>
#include "Timer.h"
#include "mathlib.h"

struct SkillSelect
{
	char x,y,z;
};

typedef struct SkillSelect SkillSelect;

class MotionAnalysis
{
public:
	MotionAnalysis(void);
	~MotionAnalysis(void);


	/** ���·������� **/
	void update();

	/** ��ʼ���� **/
	void init(void);

	void getMovePos(vector3d & dis_pos);

	void getSkillSelect(SkillSelect & select);

	vector3d * getMoveMarkCenter(){return &debug;};
	
	BOOL getActiveMove(){return activeMove;};
	
	BOOL getSkillMove(){return skillMove;};
	
	double getMoveTime();

	double getSkillTime();

private:
	
	/** ��⶯������ **/
	BOOL activeMove;

	BOOL skillMove;
	
	vector3d moveMarkCenter,skillMarkCenter,debug;

	OBJECT_T * objs ;
};
#endif