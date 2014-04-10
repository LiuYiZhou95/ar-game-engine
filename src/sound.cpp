#include "stdafx.h"
#include "Sound.h"

#define WAV_HDR_SIZE  44
#define SND_GATE  0
#define SND_PING  1
#define SND_STATIC 2
#define SND_WALK 3


BOOL EGSound::bExist=FALSE;
BOOL EGSound::bEnable=FALSE;
LPDIRECTSOUND EGSound::lpDSound=NULL;
LPDIRECTSOUNDBUFFER EGSound::lpPrimarySoundBuffer=NULL;


EGSound::EGSound():DSSoundFX(NULL)
{
}

EGSound::~EGSound()
{
	if( lpDSound && DSSoundFX )
		_RELEASE( DSSoundFX );
}


/**\brief
 * ��ʼ�������豸
 *
 *\param	_hWnd	���ھ��
 *\return	BOOL	��ʼ���Ƿ�ɹ�
 */
BOOL EGSound::InitDirectSound(HWND _hWnd)	
{	
	if( bExist || bEnable ) return TRUE;
	
	if( DirectSoundCreate(NULL,&lpDSound,NULL)!=DS_OK )
	{
		MessageBox(_hWnd,"Create DirectSound Failed!\n��ʼ��DirectSound�����г���\
			�������Ƿ���ȷ�İ�װ��DirectX 5.0���ϰ汾�������������豸��ռ��������\
			�����㽫�޷�����������","error",MB_OK);

		bEnable=FALSE;
		return FALSE;
	}

	if( lpDSound->SetCooperativeLevel(_hWnd,DSSCL_NORMAL)!=DS_OK)
	{
		MessageBox(_hWnd,"error on set DirectSound CooperativeLevel\n��ʼ��DirectSound\
			�����г����������Ƿ���ȷ�İ�װ��DirectX 5.0���ϰ汾�������������豸��ռ\
			�������������㽫�޷�����������","error",MB_OK);

		bEnable=FALSE;
		return FALSE;
	}
	bEnable = TRUE;
	bExist=TRUE;
	return TRUE;  // ��ʼ���ɹ�
}



/**\brief
 * ����������������
 */
BOOL EGSound::CreatePrimarySoundBuffer()
{
	if( bExist || !bEnable ) 
		return TRUE;

    DSBUFFERDESC	dsbdesc;
	WAVEFORMATEX	pcmwf;

    // ����wave��ʽ�ṹ
    memset(&pcmwf, 0, sizeof(WAVEFORMATEX));
    pcmwf.wFormatTag = WAVE_FORMAT_PCM;
    pcmwf.nChannels = 1;
    pcmwf.nSamplesPerSec = 8000;
    pcmwf.nBlockAlign = 4;
    pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
    pcmwf.wBitsPerSample = 8;
	pcmwf.cbSize = 0;

    // ���� DSBUFFERDESC �ṹ
    memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); // Zero it out.
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    dsbdesc.dwFlags = DSBCAPS_PRIMARYBUFFER;

    // ��������������0
    dsbdesc.dwBufferBytes = 0; 
    dsbdesc.lpwfxFormat = NULL; // ��������������NULL

	if( (lpDSound->CreateSoundBuffer(&dsbdesc, &lpPrimarySoundBuffer, NULL)) == DS_OK)
	{
		if( (lpPrimarySoundBuffer->SetFormat(&pcmwf)) == DS_OK )
			return TRUE;
	}
	
	return FALSE;
}



/**\brief
 * �ͷ������豸
 */
void EGSound::ReleaseDirectSound(void)
{
	if( !bExist ) 
		return;
	bExist=FALSE;

	if( lpDSound != NULL )
	{
		_RELEASE( lpPrimarySoundBuffer );
		_RELEASE( lpDSound );
	}
}


/**\brief
 * װ������
 *
 *\param	filename	�����ļ���
 *\return	BOOL		�����Ƿ�ɹ�
 */
BOOL EGSound::LoadSoundFX(char *filename)
{
	if( !bEnable ) return TRUE;

	DSBUFFERDESC dsbd;	//�ṹ
	LPWAVEFORMATEX wav;	//������ʽ
	DWORD len; 			//�ļ�����
	BYTE *buf; 			//��ʱ������
	LPVOID ptr1;		//ָ��1
	LPVOID ptr2;		//ָ��2
	DWORD size1;		
	DWORD size2;
	DWORD BufferSize;	//DirectSoundBuffer ��С

	FILE *f;
	long WavLong;
	if( (f=fopen(filename,"rb"))==NULL )
	{
		MessageBox(NULL,"error open file",filename,MB_OK);
		return FALSE;
	}
	fseek(f,0x04,SEEK_SET);
	fread(&WavLong,sizeof(long),1,f);	//��ȡ�������ݳ���
	len=WavLong+WAV_HDR_SIZE;			//�ļ�����
	BufferSize=len-WAV_HDR_SIZE-800;	//���û�������С

	buf=(BYTE *)malloc(len);
	if( buf==NULL )

	{
		MessageBox(NULL,"error buf",filename,MB_OK);
		return FALSE;
	}

	//��ȡ�������ݵ���ʱ������
	fseek(f,0l,SEEK_SET);
	fread(buf,len,1,f);
	fclose(f);

	ptr1=buf+20;
	wav=(LPWAVEFORMATEX)(ptr1);
	
	memset(&dsbd,0,sizeof(dsbd));
	dsbd.dwSize=sizeof(dsbd);
	dsbd.dwFlags=DSBCAPS_STATIC;
	dsbd.dwBufferBytes=len-WAV_HDR_SIZE;
	dsbd.lpwfxFormat=wav;

	_RELEASE( DSSoundFX );

	if(lpDSound->CreateSoundBuffer(&dsbd,&DSSoundFX,NULL)!=DS_OK)
	{
		MessageBox(NULL,"error createsoundbuffer","error",MB_OK);
		return FALSE;
	}

	if( (DSSoundFX->Lock(0,BufferSize,&ptr1,&size1,&ptr2,&size2,0))!=DS_OK)
	{
		MessageBox(NULL,"error Lock","error",MB_OK);
		return FALSE;
	}
	memcpy(ptr1,buf+WAV_HDR_SIZE,size1); //�������ݵ�����������
	if(size2)
		memcpy(ptr2,buf+size1+WAV_HDR_SIZE,size2);//�������ݵ�����������
	if( DSSoundFX->Unlock(ptr1,size1,ptr2,size2)!=DS_OK)
	{
		MessageBox(NULL,"error UnLock","error",MB_OK);
		return FALSE;
	}
	
	_FREE(buf);

	
	return TRUE;
}



/**\brief
 * ��������
 *
 *\param	loop	Ϊ-1ʱ����ѭ������
 */
void EGSound::Play(DWORD loop)
{
	if( bEnable==FALSE || !DSSoundFX ) 
		return;
	
	DWORD *Status1=NULL;
	if( (DSSoundFX->GetStatus(Status1))!=DS_OK ) 
		goto _next;
	if( (*Status1 & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING  ) 
		return;

_next:
	DSSoundFX->SetCurrentPosition(0);
	if( loop==-1 ) 
		loop=DSBPLAY_LOOPING;	//ѭ������
	DSSoundFX->Play(0,0,loop);
}



/**\brief
 * ֹͣ����
 */
void EGSound::Stop()
{
	if( bEnable==FALSE || DSSoundFX==NULL ) 
		return;

	DSSoundFX->Stop();
}



/**\brief
 * �������Ƿ����ڲ���
 */
BOOL EGSound::IsPlaying()
{
	if( bEnable==FALSE || DSSoundFX==NULL )
		return TRUE;

	DWORD pos, wpos;
	DSBCAPS dsbc;
	
	memset(&dsbc,0,sizeof(DSBCAPS));
	dsbc.dwSize=sizeof(DSBCAPS);
	if( (DSSoundFX->GetCaps(&dsbc)) != DS_OK ) 
	{
		MessageBox(NULL, "DSSoundFX->GetCaps","error",MB_OK);
		return TRUE;
	}
	pos=dsbc.dwBufferBytes;
	
	if( (DSSoundFX->GetCurrentPosition(&wpos,NULL)) != DS_OK )
	{
		MessageBox(NULL, "DSSoundFX->GetCurrentPosition","error",MB_OK);
		return TRUE;
	}

	if( wpos >= pos/7.16 ) 
		return FALSE;
	return TRUE;
}



/**\brief
 * ���һ��WAV����������
 *
 *\param	lpSoundBuffer	����������
 *\param	filename		�����ļ���
 *\return	BOOL			����Ƿ�ɹ�
 */
BOOL EGSound::LoadSoundBuffer(LPDIRECTSOUNDBUFFER lpSoundBuffer, char *filename)
{
	if( bEnable==FALSE ) return FALSE;
	
	FILE *f;
	DSBUFFERDESC dsbd;		//�ṹ
	LPWAVEFORMATEX wav;  	//������ʽ
	DWORD FileLen; 			//�ļ�����
	BYTE *Buf;	 			//��ʱ������
	long BufLong;			//��������������

	if( (f=fopen(filename,"rb"))==NULL )
	{
		MessageBox(NULL,"Not found the sound file!", filename, MB_OK);
		return FALSE;
	}
	fseek(f,0x28,SEEK_SET);
	fread(&BufLong,sizeof(long),1,f);	//��ȡ�������ݳ���
	FileLen=BufLong+WAV_HDR_SIZE;		//�ļ�����

	Buf=(BYTE *)malloc(FileLen);
	if( Buf==NULL )
	{
		_ERROR("error alloc soundbuffer");
		return FALSE;
	}
	
	//��ȡ�������ݵ���ʱ������
	fseek(f,0x00,SEEK_SET);
	fread(Buf,FileLen,1,f);
	fclose(f);

	wav=(LPWAVEFORMATEX)(Buf+20);

	memset(&dsbd,0,sizeof(dsbd));
	dsbd.dwSize=sizeof(dsbd);
	dsbd.dwFlags=DSBCAPS_STATIC;
	dsbd.dwBufferBytes=BufLong;
	dsbd.lpwfxFormat=wav;
	
	//��������������ȡ����
	if(	lpDSound->CreateSoundBuffer(&dsbd, &lpSoundBuffer, NULL) )
	{		
		LPVOID ptr1;		//ָ��1
		LPVOID ptr2;		//ָ��2
		DWORD size1;		
		DWORD size2;

		if( ( lpSoundBuffer->Lock(0,BufLong,&ptr1,&size1,&ptr2,&size2,0))!=DS_OK)
		{
			_ERROR("error Lock DSoundBuffer");
			return FALSE;
		}
		
		//�������ݵ�����������
		memcpy(ptr1,Buf+WAV_HDR_SIZE,size1);
		if(size2) memcpy(ptr2,Buf+size1+WAV_HDR_SIZE,size2);
		
		if( lpSoundBuffer->Unlock(ptr1,size1,ptr2,size2)!=DS_OK)
		{
			_ERROR("error UnLock SoundBuffer");
			return FALSE;
		}
	}
	_FREE(Buf);
	return TRUE;//����
}
