#include "stdafx.h"
#include "music.h"


IDirectMusicPerformance* EGMusic::g_pPerf=NULL;
IDirectMusicLoader*	EGMusic::g_pLoader=NULL;
BOOL EGMusic::bMusic=TRUE;
BOOL EGMusic::bExist=FALSE;
BOOL EGMusic::bPlay=FALSE;
EGMusic* EGMusic::m_pMusic=NULL;

EGMusic::EGMusic():g_pMIDISeg(NULL)
{
	m_pMusic=this;
}

EGMusic::~EGMusic()
{
	if( bExist )
	{
		if (g_pMIDISeg)
		{
			g_pPerf->Stop(g_pMIDISeg, NULL, 0, 0);
			_RELEASE(g_pMIDISeg);
		}
	}
	bExist=false;
	bMusic=false;
}


/**\brief
 * �������ӿ�
 */
IDirectMusicPerformance* EGMusic::CreatePerformance(void)
{
    IDirectMusicPerformance* pPerf;
 
    if (FAILED(CoCreateInstance(
            CLSID_DirectMusicPerformance,
            NULL,
            CLSCTX_INPROC, 
            IID_IDirectMusicPerformance,
            (void**)&pPerf
        )))
    {
        pPerf = NULL;
    }
    return pPerf;
}


/**\brief
 * ����LOADER
 */
IDirectMusicLoader* EGMusic::CreateLoader(void)
{
    IDirectMusicLoader* pLoader;
 
    if (FAILED(CoCreateInstance(
            CLSID_DirectMusicLoader,
            NULL,
            CLSCTX_INPROC, 
            IID_IDirectMusicLoader,
            (void**)&pLoader
        )))
    {
        pLoader = NULL;
    }
    return pLoader;
}


/**\brief
 * ����һ������
 */
IDirectMusicSegment* EGMusic::LoadMIDISegment(IDirectMusicLoader* pLoader, WCHAR *wszMidiFileName )
{
	if( !bMusic )return NULL;		//û������

	//����ļ��Ƿ����
	FILE *fp;
	char* str = Char(wszMidiFileName);
	fp=fopen(str , "rb");
	_DELETE( str );
	if( fp==NULL )
	{
		ShowMessage("Midi file %s not found!",Char(wszMidiFileName));
		return NULL;
	}
	fclose(fp);

    DMUS_OBJECTDESC ObjDesc; 
    IDirectMusicSegment* pSegment = NULL;

    ObjDesc.guidClass = CLSID_DirectMusicSegment;
    ObjDesc.dwSize = sizeof(DMUS_OBJECTDESC);
    wcscpy(ObjDesc.wszFileName, wszMidiFileName );
    ObjDesc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;
 
    pLoader->GetObject(&ObjDesc,
            IID_IDirectMusicSegment, (void**) &pSegment);		//�õ�object
 
    pSegment->SetParam(GUID_StandardMIDIFile,
            -1, 0, 0, (void*)g_pPerf);							//�����ֶӵ�����
 
    pSegment->SetParam(GUID_Download, -1, 0, 0, (void*)g_pPerf);//�����Զ�����
 
    return pSegment;
}


/**\brief
 * ��ʼ��
 */
BOOL EGMusic::InitMusic()
{	
	if(bExist)return true;		//���������

    if (SUCCEEDED(CoInitialize(NULL)))		//��ʼ��COM
    {
		if( !bExist )						//�����岻����
		{
			bExist=true;					
			g_pPerf = CreatePerformance();	//�������ӿ�
			if (g_pPerf == NULL)
			{
				MessageBox(NULL,"CreatePerformance\n��ʼ��DirectMusic���̳���\
					�������Ƿ���ȷ�İ�װ��DirectX 7.0���ϰ汾������������������\
					ռ�������������㽫�޷������������֡�","ERROR",MB_OK);
				bMusic=false;
				return false;
			}	

			if (FAILED(g_pPerf->Init(NULL, NULL, NULL)))
			{
				MessageBox(NULL,"Init\nDirectMusic ��ʼ�������밲װDirectX 7.0��\
					�ϰ汾������������������ռ�������������㽫�޷������������֡�",
					"ERROR",MB_OK);
				bMusic=false;
				return false;
			}	
		
			if (FAILED(g_pPerf->AddPort(NULL)))		//���һ��port
			{	
				MessageBox(NULL,"AddPort\nDirectMusic ��ʼ�������밲װDirectX 7.0��\
					�ϰ汾������������������ռ�������������㽫�޷������������֡�",
					"ERROR",MB_OK);
				bMusic=false;
				return false;
			}

			g_pLoader = CreateLoader();				//����һ��loader
			if (g_pLoader == NULL)
			{
				MessageBox(NULL,"CreatLoader\nDirectMusic ��ʼ������\
					�밲װDirectX 7.0���ϰ汾������������������ռ�������������㽫�޷�\
					�����������֡�","ERROR",MB_OK);
				bMusic=false;
				return false;
			}
		}
		bMusic=true;
		return true;
	}
	bMusic=false;
	return false;
}


/**\brief
 * ����
 */
BOOL EGMusic::LoadMusic(WCHAR *filename)
{
	if( !bMusic )return true;		//û������

	wcscpy( MusicFile, filename );		
	if (g_pLoader)
	{
		_RELEASE(g_pMIDISeg);

		g_pMIDISeg = LoadMIDISegment(g_pLoader,filename);	//����һ����
		return true;
	}
	return false;
}

/**\brief
 * ����
 */
BOOL EGMusic::Play(int start)
{
	if( !bMusic )return true;

	IDirectMusicSegmentState* g_pSegState;		//��ǰ��״̬
	if (g_pMIDISeg)
	{
		//����һ���Σ�������״̬
		g_pPerf->PlaySegment(g_pMIDISeg, DMUS_SEGF_REFTIME , start, &g_pSegState);	
	}
	bPlay=true;
	return true;
}


/**\brief
 * �Ƿ����ڲ���
 */
BOOL EGMusic::IsPlay()
{
	if( !bMusic )return true;	//û������

	if (g_pMIDISeg)
	{
		if( (g_pPerf->IsPlaying(g_pMIDISeg,NULL))==S_OK )
			return true;
	}
	return false;
}


/**\brief
 * ֹͣ����
 */
BOOL EGMusic::Stop()
{
	if( !bMusic )return true;

	if (g_pMIDISeg)
	{
		if( (g_pPerf->Stop(g_pMIDISeg, NULL, 0, 0))==S_OK )
		{
			bPlay=false;
			return true;
		}
	}
	return false;
}


/**\brief
 * ��ͣ����
 */
BOOL EGMusic::Pause()
{
	if( !bMusic )return true;

	if (g_pMIDISeg)
	{
		g_pPerf->GetTime(NULL, &PauseTime);		//���ŵ���ʲôλ��

		if( (g_pPerf->Stop(g_pMIDISeg, NULL, 0, 0))==S_OK )	//ֹͣ
		{
			bPlay=false;
			return true;
		}
		return false;
	}
	return false;
}


/**\brief
 * ��ͣ��������������
 */
BOOL EGMusic::Resume()
{
	if( !bMusic ) return true;

	if (g_pMIDISeg)
	{
		g_pMIDISeg->SetStartPoint(PauseTime);	//��ʼ��λ��
		IDirectMusicSegmentState* g_pSegState;	//����
		g_pPerf->PlaySegment(g_pMIDISeg,DMUS_SEGF_REFTIME,0,&g_pSegState);
		g_pMIDISeg->SetStartPoint(0);					
		bPlay=true;
		return true;
	}
	return false;
}
