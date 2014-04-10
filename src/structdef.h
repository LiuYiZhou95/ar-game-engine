/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __STRUCT_DEF_H__
#define __STRUCT_DEF_H__
#include "general.h"

/**\brief
 * ������Ϣ�ṹ
 */
struct EGSWindowInfo
{
	// �Ƿ�ȫ����ʾ
	static BOOL			m_bFullScreen;

	// ���ڿ�
	static int			m_iWidth;

	// ���ڸ�
	static int			m_iHeight;
	
	// ��ɫλ��
	static int			m_iBits;

	// ������������
	static HINSTANCE	m_hInstance;

	// ���ھ��
	static HWND			m_hWnd;

	// ������
	static char*		m_strWinName;

	EGSWindowInfo()		{ m_pInfo = this; }
	~EGSWindowInfo()		{ _DELETE(m_strWinName);}

	/**\brief
	 * ��õ�ǰ������Ϣ��ָ��
	 */
	static EGSWindowInfo* GetSysWinInfo(){return m_pInfo;}

	/**\brief
	 * ��INI�ļ����봰����Ϣ
	 */
	static BOOL LoadIni(char* _filename,char* _index);

private:
	// ������Ϣָ��
	static EGSWindowInfo* m_pInfo;
};



/**\brief
 * 2D�ռ��еĵ�
 */
struct EGSPoint2
{
	union
	{
		struct{int x,y;};
		int point2[2];
	};

	EGSPoint2()									:x(0),y(0){}
	EGSPoint2(int _x,int _y)						:x(_x),y(_y){}
	const EGSPoint2 &operator=(const EGSPoint2 &p)	{x=p.x;y=p.y;return *this;}
};


/**\brief
 * 3D�ռ��еĵ�
 */
struct EGSPoint3
{
	union
	{
		struct {float x,y,z;};
		float point3[3];
	};

	EGSPoint3()									:x(0.0f),y(0.0f),z(0.0f){}
	EGSPoint3(float _x,float _y,float _z)			:x(_x),y(_y),z(_z){}
	const EGSPoint3 &operator=(const EGSPoint3 &p)	{x=p.x;y=p.y;z=p.z;return *this;}
};



/**\brief
 * ��ɫ�ṹ
 */
struct EGSColor
{
	union
	{
		struct {float r,g,b,a;};
		float color4[4];
	};

	EGSColor()									:r(0.0f),g(0.0f),b(0.0f),a(0.0f){}
	EGSColor(float _r,float _g,float _b,float _a)	:r(_r),g(_g),b(_b),a(_a){}
	const EGSColor &operator=(const EGSColor &c)	{r=c.r;g=c.g;b=c.b;a=c.a;return *this;}
	const EGSColor operator!(){EGSColor c;c.r=1.f-r;c.g=1.f-g;c.b=1.f-b;return c;}
};



/**\brief
 * ���νṹ
 */
struct EGSRect
{
	union
	{
		struct {int x,y,width,height;};
		int rect[4];
	};

	EGSRect():x(0),y(0),width(100),height(100){}
	EGSRect(int _x,int _y,int _w,int _h)		:x(_x),y(_y),width(_w),height(_h){};
	const EGSRect &operator=(const EGSRect &r)	{x=r.x;y=r.y;width=r.width;height=r.height;return *this;}
	BOOL PointIn(EGSPoint2 p){if(p.x>=x&&p.y>=y&&p.x<=x+width&&p.y<=y+height)return TRUE;else return FALSE;}
};


/**\brief
 *ƥ�䷽��Ķ�����Ϣ
 */
typedef struct {
  const char    *patt_name;
  int     patt_id;
  int     model_id;
  int     visible;
  double  width;
  double  center[2];
  double  trans[3][4];
} OBJECT_T;


#endif
