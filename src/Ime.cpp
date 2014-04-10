#include "stdafx.h" 
#include "ime.h"

EGIme* EGIme::m_pIme=NULL;


EGIme::EGIme():m_lpCandList(NULL),m_iImeCaret(-1),m_iWordCaret(-1),
			m_bReceive(true),m_iMaxLen(STR_MAX_LENGTH)
{
	m_pIme=this;
	m_chResultStr[0] =0 ;
	Disable(); 	//ͨ��Disable��ʼ��һЩ����
}


void EGIme::Release()
{
	Disable();
	if( m_lpCandList )
	{
		GlobalFree( (HANDLE)m_lpCandList );
		m_lpCandList = NULL;
	}
}



bool EGIme::OnWM_INPUTLANGCHANGE( HWND hWnd)
{
	//���뷨�ı�
	HKL hKL = GetKeyboardLayout( 0 );
	if( ImmIsIME( hKL ))
	{
		HIMC hIMC = ImmGetContext( hWnd );

		DWORD dwConversion;
		ImmGetConversionStatus( hIMC, &dwConversion,NULL );
		m_bSharp = ( dwConversion & IME_CMODE_FULLSHAPE )? true : false;//ȡ��ȫ�Ǳ�־
		m_bSymbol = ( dwConversion & IME_CMODE_SYMBOL )? true : false;//ȡ�����ı���־

		ImmEscape( hKL, hIMC, IME_ESC_IME_NAME, m_szName );//ȡ�������뷨����
		ImmReleaseContext( hWnd, hIMC );
	}
	else//Ӣ������
		//m_szImeName[ 0 ] = 0;
		strcpy(m_szName,"Ӣ��");
	return false;//���Ƿ���false����Ϊ��Ҫ���ں�������DefWindowProc��������
}


bool EGIme::OnWM_IME_NOTIFY( HWND hWnd, WPARAM wParam )
{
	HIMC hIMC;
	DWORD dwSize;
	DWORD dwConversion, dwSentence;
	switch( wParam )
	{
	case IMN_SETCONVERSIONMODE://ȫ��/��ǣ���/Ӣ�ı��ı�
		hIMC = ImmGetContext( hWnd );
		ImmGetConversionStatus( hIMC, &dwConversion, &dwSentence );
		m_bSharp = ( dwConversion & IME_CMODE_FULLSHAPE )? true : false;
		m_bSymbol = ( dwConversion & IME_CMODE_SYMBOL )? true : false;
		ImmReleaseContext( hWnd, hIMC );
		break;

		//case IMN_OPENCANDIDATE://����ѡ��״̬
	case IMN_CHANGECANDIDATE://ѡ�ֱ�ҳ
		hIMC = ImmGetContext( hWnd );
		if( m_lpCandList )
		{
			GlobalFree( (HANDLE)m_lpCandList );
			m_lpCandList = NULL;
		}//�ͷ���ǰ��ѡ�ֱ�
		if( dwSize = ImmGetCandidateList( hIMC, 0, NULL, 0 ))
		{
			m_lpCandList = (LPCANDIDATELIST)GlobalAlloc( GPTR, dwSize );
			if( m_lpCandList )
				ImmGetCandidateList( hIMC, 0, m_lpCandList, dwSize );
		}//�õ��µ�ѡ�ֱ�
		ImmReleaseContext( hWnd, hIMC );
		if( m_lpCandList )
			ConvertCandList( m_lpCandList, m_szCandList );//ѡ�ֱ�����ɴ�
		break;

	case IMN_CLOSECANDIDATE://�ر�ѡ�ֱ�
		if( m_lpCandList )
		{
			GlobalFree( (HANDLE)m_lpCandList );
			m_lpCandList = NULL;
		}//�ͷ�
		m_szCandList[ 0 ] = 0;
		break;
	}

	return true;//���Ƿ���true����ֹime���ڴ�
}


bool EGIme::OnWM_IME_COMPOSITION( HWND hWnd, LPARAM lParam )
{//����ı�
	HIMC hIMC;
	DWORD dwSize;
	hIMC = ImmGetContext( hWnd );
	//ȡ��szCompStr
	if( (DWORD)lParam & GCS_COMPSTR )
	{
		dwSize = ImmGetCompositionString( hIMC, GCS_COMPSTR, (void*)m_szCompStr, sizeof( m_szCompStr ));
		m_szCompStr[ dwSize ] = 0;
	}
	//ȡ��szCompReadStr
	if( (DWORD)lParam & GCS_COMPREADSTR )
	{
		dwSize = ImmGetCompositionString( hIMC, GCS_COMPREADSTR, (void*)m_szCompReadStr, sizeof( m_szCompReadStr ));
		m_szCompReadStr[ dwSize ] = 0;
	}
	//ȡ��nImeCursor
	if( lParam & GCS_CURSORPOS )
	{
		m_nCursor = 0xffff & ImmGetCompositionString( hIMC, GCS_CURSORPOS, NULL, 0 );
	}

	if( lParam & GCS_RESULTSTR )
	{
		char str[ MAX_PATH ];
		dwSize = ImmGetCompositionString( hIMC, GCS_RESULTSTR, (void*)str, sizeof( str ));//ȡ�ú������봮
		str[ dwSize ] = 0;
		ReceiveChar( str, dwSize );
	}

	ImmReleaseContext( hWnd, hIMC );
	return true;//���Ƿ���true����ֹime���ڴ�
}


void  EGIme::Disable()
{
	//while( ImmIsIME( GetKeyboardLayout( 0 )))
	//	ActivateKeyboardLayout(( HKL )HKL_NEXT, 0 );//���ime��ͨ��ѭ���л�����һ���ر�
	m_bIme = false;
	m_szName[ 0 ] = 0;

	m_szCompReadStr[ 0 ] = 0;
	m_szCandList[ 0 ] = 0;
	m_nCursor = 0;

	m_chResultStr[0] = 0;
	m_iImeCaret=-1;
	m_iWordCaret=-1;
	m_bReceive=true;
	m_bReturn=false;
}


void EGIme::ConvertCandList( CANDIDATELIST *pCandList, char *pszCandList )
{//ת��CandidateList��һ������\t�ָ�ÿһ��
	unsigned int i;
	if( pCandList->dwCount < pCandList->dwSelection )
	{
		pszCandList[ 0 ] = 0;
		return;
	}

	//��ѡ����ų���������΢��ƴ���ڶ��ε�ѡ�ֱ����һҳ���ٰ�PageDown�����������������һ��˳�ѡ��״̬����ʼһ���µ�����
	//��΢��ƴ���Լ���ime���ڿ��Խ��������⣬����΢��ƴ��ʵ���˸���Ľӿڣ�����ʹ�������ֲ�̫��׼������
	//�������޷����������⣬����ʵ��ʹ����Ҳ�������������£�����������׼���뷨������������bug
	//�Ǳ�׼���뷨����ʵ�ֵĽӿڱȽ��٣�����Ӧ��Ҳ������������bug
	for( i = 0; ( i < pCandList->dwCount - pCandList->dwSelection )&&( i < pCandList->dwPageSize ); ++i )
	{
		*pszCandList++ = ( i % 10 != 9 )? i % 10 + '1' : '0';//ÿ���Ӧ�����ּ�
		*pszCandList++ = '.';//��'.'�ָ�
		strcpy( pszCandList, (char*)pCandList
			+ pCandList->dwOffset[ pCandList->dwSelection + i ] );//ÿ��ʵ�ʵ�����
		pszCandList += strlen( pszCandList );
		*pszCandList++ = '\t';//��֮����'\t'�ָ�
	}
	*( pszCandList - 1 )= 0;//��β�����������һ��'\t'
}


void EGIme::ReceiveChar(TCHAR _iCharCode)
{
	if(!m_bIme)return;
	if(!m_bReceive&&_iCharCode!='\b')return;

	if( !_iCharCode )return;

	switch(_iCharCode) 
	{
	case '\b':
		BackspaceKey();
		break;
	case '\r':break;
	case '\t':break;
	case VK_ESCAPE:break;
	default:
		{
			int t_iLen = (int)strlen(m_chResultStr);

			if(t_iLen >= m_iMaxLen-1)
			{
				t_iLen = m_iMaxLen-1;
			}
			if( m_iImeCaret < m_iMaxLen-1 
				&& (int)strlen(m_chResultStr) < m_iMaxLen )
			{
				++m_iImeCaret;
				++m_iWordCaret;//////////////

				//������������ÿ���ַ�����ƶ�һλ
				for(int i = t_iLen; i>=m_iImeCaret; i--)
				{
					m_chResultStr[i+1] = m_chResultStr[i];
				}
				m_chResultStr[m_iImeCaret] = (char)_iCharCode;
			}
			break;
		}
	}
}

void EGIme::ReceiveChar(char* _Char, DWORD _dwSize)
{
	if(!m_bIme)return;
	if(!m_bReceive&&_Char[0]!='\b')return;

	int t_iLen;
	int t_iLen2 = (int)strlen(_Char);

	while ( (int)strlen(m_chResultStr)+t_iLen2 > m_iMaxLen )
	{
		t_iLen2 -= 2;
	}
	
	m_iWordCaret+=(t_iLen2%2==1)?((t_iLen2+1)/2):(t_iLen2/2);/////////////

	for(int i=0; i<t_iLen2; ++i )
	{
		t_iLen = (int)strlen(m_chResultStr);

		if( t_iLen >= m_iMaxLen-1 )
		{
			t_iLen = m_iMaxLen-1;
		}
		if( m_iImeCaret < m_iMaxLen-1 )
		{
			++m_iImeCaret;
			//������������ÿ���ַ�����ƶ�һλ
			for(int j = t_iLen; j>=m_iImeCaret; j--)
			{
				m_chResultStr[j+1] = m_chResultStr[j];
			}
			if( m_iImeCaret < m_iMaxLen )
				m_chResultStr[m_iImeCaret] = _Char[i];
		}
	}

}


/** \brief
* "����"������Ĵ���
*/
void EGIme::RightKey( void )
{
	int t_iLen = (int)strlen(m_chResultStr);

	if( m_iImeCaret < t_iLen-2 )
	{
		// �ж��Ƿ��Ǻ���
		if( (BYTE)m_chResultStr[m_iImeCaret+1] > 160
			&& (BYTE)m_chResultStr[m_iImeCaret+2] > 160 )
			m_iImeCaret +=2;
		else
            ++m_iImeCaret;
		++m_iWordCaret;/////////////
	}
	else if( m_iImeCaret < t_iLen-1 )
	{
		++m_iImeCaret;
		++m_iWordCaret;/////////////
	}
}

/** \brief
* "����"������Ĵ���
*/
void EGIme::LeftKey( void )
{
	//�жϺ���
	if( m_iImeCaret-1 > -1 )
	{
		if( (BYTE)m_chResultStr[m_iImeCaret-1] > 160
			&& (BYTE)m_chResultStr[m_iImeCaret] > 160 )
		{
			m_iImeCaret -=2;
		}
		else
			m_iImeCaret--;
		m_iWordCaret--;////////////
	}
	else if( m_iImeCaret > -1 )
	{
		m_iImeCaret--;
		m_iWordCaret--;////////////
	}
}

/** \brief
* "����" ������
*/
void EGIme::BackspaceKey(void)
{
	int t_iLen = (int)strlen(m_chResultStr);
	//�жϺ���
	if( m_iImeCaret-1 > -1 )
	{
		//ɾ������
		if( (BYTE)m_chResultStr[m_iImeCaret-1] > 160
			&& (BYTE)m_chResultStr[m_iImeCaret] > 160 )
		{
			for(int i = m_iImeCaret; i<t_iLen; ++i)
			{
				m_chResultStr[i] = m_chResultStr[i+1];
			}
			m_iImeCaret--;
			for(int i = m_iImeCaret; i<t_iLen; ++i)
			{
				m_chResultStr[i] = m_chResultStr[i+1];
			}
			m_iImeCaret--;
		}
		else//ɾ��һ����ĸ
		{
			for(int i = m_iImeCaret; i<t_iLen; ++i)
			{
				m_chResultStr[i] = m_chResultStr[i+1];
			}
			m_iImeCaret--;
		}
		m_iWordCaret--;//////////////
	}
	else if( m_iImeCaret > -1 )
	{
		for(int i = m_iImeCaret; i<t_iLen; ++i)
		{
			m_chResultStr[i] = m_chResultStr[i+1];
		}
		m_iImeCaret--;
		m_iWordCaret--;////////////
	}
	if(m_iWordCaret<-1)m_iWordCaret=-1;///////////
}


/** \brief
* "DEL" ������
*/
void EGIme::DeleteKey(void)
{
	int t_iLen = (int)strlen(m_chResultStr);

	if( m_iImeCaret < t_iLen-2 )
	{
		// �ж��Ƿ��Ǻ���
		if( (BYTE)m_chResultStr[m_iImeCaret+1] > 160
			&& (BYTE)m_chResultStr[m_iImeCaret+2] > 160 )
		{
			//������������ÿ���ַ���ǰ�ƶ���λ
			for(int i = m_iImeCaret+1; i<t_iLen-1; ++i)
			{
				m_chResultStr[i] = m_chResultStr[i+2];
			}
		}
		else
		{
			//������������ÿ���ַ���ǰ�ƶ�һλ
			for(int i = m_iImeCaret+1; i<t_iLen; ++i)
			{
				m_chResultStr[i] = m_chResultStr[i+1];
			}
		}
	}
	else if( m_iImeCaret < t_iLen-1 )
	{
		//������������ÿ���ַ���ǰ�ƶ�һλ
		for(int i = m_iImeCaret+1; i<t_iLen; ++i)
		{
			m_chResultStr[i] = m_chResultStr[i+1];
		}
	}

	if(m_iWordCaret<-1)m_iWordCaret=-1;////////////
}


