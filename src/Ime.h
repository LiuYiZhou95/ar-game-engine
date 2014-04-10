/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#pragma once
#ifndef __IME_H__
#define __IME_H__


#include <imm.h>

#pragma comment ( lib, "imm32.lib" )

// �����ַ�������󳤶�
#define STR_MAX_LENGTH 256



/** \brief
 *  ��װ��ime��صĴ��������࣬���뷨��ء�
 */
class EGIme
{
public:
	EGIme();
	~EGIme(){Release();}


	/**\brief
	 * �رղ���ֹ���뷨����ime�Ѿ�����رգ�
	 * �˺���Ҳ������ȼ�����ime
	 */
	void Disable();


	/**\brief
	 * �������뷨���˺���ҿ������ȼ�����ime
	 */
	void Enable(){Disable();m_bIme = true;}


	/**\brief
	 * �����Ƿ���������ַ�
	 */
	void SetReceiveChar(bool _b){m_bReceive=_b;}


	/**\brief
	 * �л�����һ�����뷨������EnableIme�����Ч
	 */
	void NextIme();


	/**\brief
	 * �л�ȫ��/���
	 */
	void SharpIme( HWND hWnd );


	/**\brief
	 * �л���/Ӣ�ı��
	 */
	void SymbolIme( HWND hWnd );


	/**\brief
	 * ״̬����
	 */
	char* GetImeName();

	/**\brief
	 * �Ƿ��˻س���
	 */
	BOOL GetReturnState(){return m_bReturn?TRUE:FALSE;}

	/**\brief
	 * �Ƿ�ȫ��
	 */
	bool IfImeSharp();


	/**\brief
	 * �Ƿ����ı��
	 */
	bool IfImeSymbol();


	char*   GetImeInputCompStr();
	char*   GetImeInputCompReadStr();
	int     GetImeInputCursor();
	char*   GetImeInputCandList();
	char*   GetImeInputResultStr();


	//@{
	// ��������Ϣ�е��õĺ��������������true��
	//  �򴰿ں���Ӧֱ�ӷ���0������Ӧ���ݸ�DefWindowProc

	/** \brief
	 *  �л����뷨��ʱ���յ�����Ϣ��
	 *
	 *  �����ֹime�򷵻�false����ʱ���ں���Ӧ����0������DefWindowProc������뷨
	 */
	virtual bool OnWM_INPUTLANGCHANGEREQUEST();
	virtual bool OnWM_INPUTLANGCHANGE( HWND hWnd);
	virtual bool OnWM_IME_SETCONTEXT(){ return true; }
	virtual bool OnWM_IME_STARTCOMPOSITION(){ return true; }
	virtual bool OnWM_IME_ENDCOMPOSITION(){ return true; }
	virtual bool OnWM_IME_NOTIFY( HWND hWnd, WPARAM wParam );
	virtual bool OnWM_IME_COMPOSITION( HWND hWnd, LPARAM lParam );
	//@} 

	void Release();

	void AddCharToResultStr(char* _Char);


	/** \brief
	*��������ַ� �ѵõ��������ַ������ַ����б���
	*/
	void ReceiveChar(TCHAR _iCharCode);


	/** \brief
	* �ڲ����λ�ò���һ���ַ���
	*
	* \param	_Char	������ַ���
	* \param	_dwSize	�ַ����ĳ���
	*/
	void ReceiveChar(char* _Char, DWORD _dwSize);


	/** \brief
	* ȡ�ò������λ��
	*/
	int GetCaret(void){return m_iImeCaret;}


	/**\brief
	 * ȡ�ò���������е�λ��
	 */
	int GetWordCaret(void){return m_iWordCaret;}


	/** \brief
	* "����" ������
	*/
	void BackspaceKey(void);


	/** \brief
	* "DEL" ������
	*/
	void DeleteKey(void);


	/** \brief
	* "����"������Ĵ���
	*/
	void RightKey(void);


	/** \brief
	* "����"������Ĵ���
	*/
	void LeftKey( void );


	/**\brief
	 * �س����Ĵ���
	 */
	void ReturnKey(void){m_bReturn=true;}


	/**\brief
	 * ȡ�õ�ǰ��IME����
	 */
	static EGIme* GetSysIme(){return m_pIme;}


private:
	// ime��ָ̬��
	static EGIme* m_pIme;

	// ime�����־
	bool	m_bIme;

	// �Ƿ�Ӽ��̽����ַ�<�����˼�>
	bool	m_bReceive;

	// �Ƿ��˻س�
	bool	m_bReturn;

	// �洢ת����Ĵ�
	char	m_szCompStr[ MAX_PATH ];

	// �洢����Ĵ�
	char	m_szCompReadStr[ MAX_PATH ];

	// �洢������ַ���ѡ�ֱ�
	char	m_szCandList[ MAX_PATH ];

	// �洢ת����Ĵ��еĹ��λ��
	int		m_nCursor;

	// �洢��׼��ѡ�ֱ�
	CANDIDATELIST *m_lpCandList;

	// ȫ�Ǳ�־
	bool	m_bSharp;

	// ���ı���־
	bool	m_bSymbol;

	/**\brief
	 *  ������洢����ʹ�����뷨��ʱ��������ִ���
	 *  �ϲ����ֻ��Ҫ�õ�����ִ��Ϳ����ˡ�
	 */
	char	m_chResultStr[STR_MAX_LENGTH];


	// �洢���뷨������
	char	m_szName[64];

	// ��ǰ�����ַ����ַ������Խ����ַ������̶�
	int		m_iMaxLen;

	//-------------------------------------------
	// �������λ�� ��������Ǹ��ַ��ĺ��
	int		m_iImeCaret;

	// ����������е�λ��
	int		m_iWordCaret;
	//--------------------------------------------

	/**\brief
	 * ��ѡ�ֱ�����ɴ�
	 */
	void ConvertCandList( CANDIDATELIST *pCandList,char *pszCandList );

};




///////////////////////////////////////////////
//--------------Inline����ʵ��-----------------

inline void EGIme::NextIme()
{
	if( m_bIme )ActivateKeyboardLayout((HKL)HKL_NEXT,0);
}

inline void EGIme::SharpIme( HWND hWnd )
{
	ImmSimulateHotKey( hWnd, IME_CHOTKEY_SHAPE_TOGGLE);
}

inline void EGIme::SymbolIme( HWND hWnd )
{
	ImmSimulateHotKey( hWnd, IME_CHOTKEY_SYMBOL_TOGGLE);
}


/**\brief
 * �л����뷨��ʱ���յ�����Ϣ��
 *
 * �����ֹime�򷵻�false����ʱ���ں���Ӧ����0������DefWindowProc������뷨
 */
inline bool EGIme::OnWM_INPUTLANGCHANGEREQUEST()
{
	return !m_bIme;
}


inline char* EGIme::GetImeName()
{
	return m_szName[0]?m_szName:NULL;
}

/**\brief
 * �Ƿ�ȫ��
 */
inline bool EGIme::IfImeSharp()
{
	return m_bSharp;
}

/**\brief
 * �Ƿ����ı��
 */
inline bool EGIme::IfImeSymbol()
{
	return m_bSymbol;
}

inline char* EGIme::GetImeInputCompStr()
{
	return  m_szCompStr[0] ? m_szCompStr : NULL;
}

inline char *EGIme::GetImeInputCompReadStr()
{
	return  m_szCompReadStr[0] ? m_szCompReadStr : NULL;
}

inline int EGIme::GetImeInputCursor()
{
	return  m_nCursor;
}

inline char* EGIme::GetImeInputCandList()
{
	return  m_szCandList[0] ? m_szCandList : NULL;
}

inline	char* EGIme::GetImeInputResultStr()
{
	return  m_chResultStr;
}

inline void EGIme::AddCharToResultStr(char* _Char)
{
	strcat(m_chResultStr,_Char);
}


#endif
