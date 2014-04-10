/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __INPUT_H__
#define __INPUT_H__

#define DIRECTINPUT_VERSION  0x0800
#include "stdafx.h"

#include <dinput.h>
#include "mathlib.h"

#define IS_USEKEYBOARD  1
#define IS_USEMOUSE     2
#define IS_USEJOYSTICK  4


/////////////////////////////////////////
/**\brief
 *  ������
 */
class CKeyboard
{
public:
	CKeyboard(LPDIRECTINPUT8 pDI, HWND hwnd);
	~CKeyboard();


	/**\brief
	 * key���Ƿ���
	 */
	BOOL KeyDown(int key);


	/**\brief
	 * ���¼������ݣ�������ѭ����
	 */
	BOOL Update();


	/**\brief
	 * �Լ�����������
	 */
	void Clear();


	/**\brief
	 * ȡ��������
	 */
	BOOL Acquire();


	/**\brief
	 * ֹͣȡ����
	 */
	BOOL Unacquire();


private:
	// �����豸
	LPDIRECTINPUTDEVICE8  m_pDIDev;

	// ����������
	char    m_keys[256];
};




////////////////////////////////////////
/**\brief
 *  �����
 */
class CMouse
{
public:
	CMouse(LPDIRECTINPUT8 pDI,HWND hwnd,BOOL isExclusive=TRUE);
	~CMouse();


	/**\brief
	 * ���ĳ���Ƿ��£�0-�����1-�Ҽ�
	 */
	BOOL	ButtonDown(int button);
	
	
	/**\brief
	 * ��ù������仯
	 */
	void	GetMovement(int &dx, int &dy);
	
	
	/**\brief
	 * ��ù��λ��
	 */
	EGSPoint2	GetMousePos();


	/**\brief
	 * ���������״̬,(<0,0,>0)
	 */
	int		GetWheelState();


	/**\brief
	 * ����������
	 */
	BOOL	Update();


	/**\beirf
	 * ȡ�������
	 */
	BOOL	Acquire();
	
	
	/**\brief
	 * ֹͣȡ����
	 */
	BOOL	Unacquire();


	// ���ڿ�
	int		m_iWidth;

	// ���ڸ�
	int		m_iHeight;


private:
	// ����豸
	LPDIRECTINPUTDEVICE8	m_pDIDev;

	// ���״̬
	DIMOUSESTATE			m_state;

	// ���λ��
	EGSPoint2					m_sMousePos;
};




/////////////////////////////////////////
/**\brief
 *  ��Ϸ�ֱ�
 */
class CJoystick
{
public:
	CJoystick(LPDIRECTINPUT8 pDI, HINSTANCE appInstance);
	~CJoystick();


	/**\brief
	 * �����ֱ�����
	 */
	BOOL Update(){ return TRUE;}


	/**\brief
	 * ȡ�ֱ�����
	 */
	BOOL Acquire();


	/**\brief
	 * ͣ��ȡ�ֱ�����
	 */
	BOOL Unacquire();


private:
	// �ֱ��豸
	LPDIRECTINPUTDEVICE8  m_pDIDev;
};




////////////////////////////////////////
/**\brief
 *  ����ϵͳ��
 */
class EGInput
{
public:
	EGInput():bClick(FALSE),bFirstMDownL(FALSE){m_pInput=this;}
	~EGInput(){Shutdown();}

	
	/**\brief
	 * ��ʼ�������豸
	 */
	BOOL  Init(HWND hwnd,HINSTANCE appInstance,BOOL isExclusive,DWORD flags=0);
	
	
	/**\brief
	 * �ͷ������豸��Դ
	 */
	BOOL  Shutdown();


	/**\brief
	 * ȡ�����豸������
	 */
	void  AcquireAll();
	
	
	/**\brief
	 * ͣ��ȡ�����豸������
	 */
	void  UnacquireAll();


	/**\brief
	 * ��ü���
	 */
	CKeyboard  *GetKeyboard(){return m_pKeyboard;}
	
	
	/**\brief
	 * ������
	 */
	CMouse     *GetMouse(){return m_pMouse;}
	
	
	/**\brief
	 * �����Ϸ�ֱ�
	 */
	CJoystick  *GetJoystick(){return m_pJoystick;}


	/**\brief
	 * ���������豸�Ĳ���
	 */
	void	Update();


	/**\brief
	 * ��ù���3D����
	 */
	vector3d GetMousePosition();


	/**\brief
	 * ����Ƿ��ǵ�һ�ΰ���
	 */
	BOOL	FirstMouseDownL(){return bFirstMDownL;}


	/**\brief
	 * �Ƿ񵥻������
	 */
	BOOL	Clicked(){return bClick;}
	

	/**\brief
	 * �õ���ǰ�������豸
	 */
	static EGInput* GetSysInput(){return m_pInput;}


	/**\brief
	 * �õ���ǰ�Ĵ��ھ��
	 */
	static HWND GetSysHWnd(){return m_hWnd;}


private:
	// ����ϵͳ
	static EGInput* m_pInput;

	// ���ھ��
	static HWND m_hWnd;

	// ����
	CKeyboard  *m_pKeyboard;

	// ���
	CMouse     *m_pMouse;

	// ��Ϸ�ֱ�
	CJoystick  *m_pJoystick;

	// �����豸
	LPDIRECTINPUT8 m_pDI;

	//���������º�̧��ʱΪTRUE
	BOOL		bClick;

	//��갴�»��и�ʱ��Σ��ǲ��Ǹտ�ʼ����
	BOOL		bFirstMDownL;
	
};







///////////////////////////////////////////////////
//------------CKeyboard inline����ʵ��-------------

/**\brief
 * key���Ƿ���
 */
inline BOOL CKeyboard::KeyDown(int key)
{
	return (m_keys[key]&0x80)?TRUE:FALSE;
}

/**\brief
 * �Լ�����������
 */
inline void CKeyboard::Clear()
{
	ZeroMemory(m_keys,256*sizeof(char));
}

/**\brief
 * ȡ��������
 */
inline BOOL CKeyboard::Acquire()
{
	Clear();
	return (!FAILED(m_pDIDev->Acquire()));
}

/**\brief
 * ֹͣȡ����
 */
inline BOOL CKeyboard::Unacquire()
{
	Clear();
	return (!FAILED(m_pDIDev->Unacquire()));
}



///////////////////////////////////////////////////
//------------CMouse inline����ʵ��----------------

/**\brief
 * ���ĳ���Ƿ��£�0-�����1-�Ҽ�
 */
inline BOOL CMouse::ButtonDown(int button)
{
	return (m_state.rgbButtons[button]&0x80)?TRUE:FALSE;
}

/**\brief
 * ��ù������仯
 */
inline void CMouse::GetMovement(int &dx, int &dy)
{
	dx = m_state.lX;
	dy = m_state.lY;
}

/**\brief
 * ��ù��λ��
 */
inline EGSPoint2 CMouse::GetMousePos()
{
	return m_sMousePos;
}

/**\brief
 * ���������״̬ (<0,0,>0)
 */
inline int	CMouse::GetWheelState()
{
	return m_state.lZ;
}

/**\beirf
 * ȡ�������
 */
inline BOOL CMouse::Acquire()
{
	return (!FAILED(m_pDIDev->Acquire()));
}

/**\brief
 * ֹͣȡ����
 */
inline BOOL CMouse::Unacquire()
{
	return (!FAILED(m_pDIDev->Unacquire()));
}



///////////////////////////////////////////////////
//-----------CJoystick inline����ʵ��--------------
/**\brief
 * ȡ�ֱ�����
 */
inline BOOL CJoystick::Acquire()
{
	return (!FAILED(m_pDIDev->Acquire()));
}

/**\brief
 * ֹͣȡ����
 */
inline BOOL CJoystick::Unacquire()
{
	return (!FAILED(m_pDIDev->Unacquire()));
}



///////////////////////////////////////////////////
//-------------EGInput inline����ʵ��---------------

/**\brief
 * ȡ�����豸������
 */
inline void EGInput::AcquireAll()
{
	if (m_pKeyboard)	m_pKeyboard->Acquire();
	if (m_pMouse)		m_pMouse->Acquire();
	if (m_pJoystick)	m_pJoystick->Acquire();
}

/**\brief
 * ֹͣȡ����
 */
inline void EGInput::UnacquireAll()
{
	if (m_pKeyboard)	m_pKeyboard->Unacquire();
	if (m_pMouse)		m_pMouse->Unacquire();
	if (m_pJoystick)	m_pJoystick->Unacquire();
}



#endif
