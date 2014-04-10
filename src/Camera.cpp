/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "stdafx.h"
#include "Camera.h"
#include "mathlib.h"
#include "role.h"
#include "Terrain.h"

/** ������ͷ��б�Ƕȵ��ٶ� **/
static const float PITCHSPEED = 1.0f * 5;
/** ������ͷ������ת�Ƕȵ��ٶ� **/
static const float DIRECTIONSPEED = 1.0f;
/** ������ͷǰ�������ٶ� **/
static const float DIRECTIONTOHEROSPEED = 1.0f;

// ����ʹ�õ��������ָ��
EGCamera* EGCamera::m_pCamera = NULL;


EGCamera::EGCamera(void):direction(0.0f),pitch(21.f),
				dist_to_role(80.0f),role_pos(vector3d(2.0f,0.4f,-0.5f))
{
	m_pCamera = this;
}



/**\brief
 * ��������Ĳ����������ŵ���ѭ����
 */
void EGCamera::Update(void)
{
	if(EGInput::GetSysInput()->GetMouse()->GetWheelState()>0)
	{
		pitch += PITCHSPEED;
		if(pitch>100.0f)	pitch=100.0f;
	}
	if(EGInput::GetSysInput()->GetMouse()->GetWheelState()<0)
	{
		pitch -= PITCHSPEED;
		if(pitch<-3.f)	pitch=-3.f;
	}

	EGSPoint2 p=SYS_MOUSE->GetMousePos();
	if(p.x <=0)
	{
		if(EGRole::GetRolePointer()->IsArrive())direction+=DIRECTIONSPEED;
	}

	if(p.x >=SYS_WIDTH-1)
	{
		if (EGRole::GetRolePointer()->IsArrive())direction-=DIRECTIONSPEED;
	}
	if(p.y>SYS_HEIGHT-5)
	{
		dist_to_role += DIRECTIONTOHEROSPEED ;
		if(dist_to_role>160.0f)dist_to_role=160.0f;
	}
	if(p.y<5)
	{
		dist_to_role -= DIRECTIONTOHEROSPEED;
		if(dist_to_role<40.0f)dist_to_role=40.0f;
	}

	role_pos=EGRole::GetRolePointer()->GetPos();
	position = role_pos ;
	position.z += dist_to_role;
	position.y = role_pos.y+15.0f;
    

	FrameMove();
}


/**\brief
 * ���ñ�þ���
 */
void EGCamera::FrameMove(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f,0.0f,-dist_to_role);
	glRotatef(pitch,1.0f,0.0f,0.f);
	glRotatef(direction,0.0f,1.0f,0.0f);

    glTranslatef(0.0f,0.0f,dist_to_role);

	glTranslatef(-position.x,-position.y,-position.z);
}

