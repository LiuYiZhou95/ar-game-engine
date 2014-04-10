/**
 *���ߣ�����ʢ
 *2011��10��30��
 */
#include "VideoCapture.h"

#define OBJ_MOVE_ID		1
#define OBJ_MOVE		0
#define OBJ_SKILL_ID	2
#define OBJ_SKILL		1


/** ��֡���ɨ�����**/
static int thresh;
/** �ӵ�ǰ����ͷ��ȡ��һ֡ͼƬ **/
static ARUint8 * m_pImgCaptureFromeCamera;
/** �ӵ�ǰ����ͷ��ȡ��һ֡ͼƬ **/
//static ARInt16 * m_pImgCaptureFromeCamera16;
/** Ŀ�꿨Ƭ���� **/
static OBJECT_T object[2];
/** ����ͷ�Ĳ��� **/
static ARParam         cparam, wparam;
/** ����ͷ���ڴ�С **/
static int	xsize, ysize;
/** �ٽ�ͬ���� **/
//static CCriticalSection  m_cCriticalSection ;
/** AR���е��� **/
static BOOL isRunning;
static BOOL isHeightSpeedCamera;

VideoCapture::VideoCapture(void)
{
}

VideoCapture::~VideoCapture(void)
{}

/** �������״̬ **/
BOOL VideoCapture::getRunState(){return isRunning;};


void VideoCapture::UpThresh()
{
	thresh+=10;
}

void VideoCapture::DownThresh()
{
	thresh-=10;
}

int VideoCapture::GetThresh()
{
	return thresh;
}

/**\brief
 *��ʼ������ͷ
 */
BOOL VideoCapture::LoadIni(char* _filename,char* _index)
{
	/** ����ͷ�����ļ� **/
	char * vconf, * cparam_name;

	EGCIniFile Ini(_filename);

	vconf = Ini.ReadText(_index,"vconf");
	cparam_name = Ini.ReadText(_index,"cparam_name");
	thresh = Ini.ReadInt(_index,"thresh");

	object[OBJ_MOVE].patt_name = Ini.ReadText(_index,"patt_move");
	object[OBJ_MOVE].patt_id = -1;
	object[OBJ_MOVE].visible = 0;
	object[OBJ_MOVE].model_id = OBJ_MOVE_ID;
	object[OBJ_MOVE].width = Ini.ReadInt(_index,"move_size");
	object[OBJ_MOVE].center[0] = 0.0;
	object[OBJ_MOVE].center[1] = 0.0;

	object[OBJ_SKILL].patt_name = Ini.ReadText(_index,"patt_skill");
	object[OBJ_SKILL].patt_id = -1;
	object[OBJ_SKILL].visible = 0;
	object[OBJ_SKILL].model_id = OBJ_SKILL_ID;
	object[OBJ_SKILL].width = Ini.ReadInt(_index,"skill_size");
	object[OBJ_SKILL].center[0] = 0.0;
	object[OBJ_SKILL].center[1] = 0.0;

	isRunning = FALSE;
	isHeightSpeedCamera = TRUE;
	/** �����ļ� */
    if( arVideoOpen( vconf ) < 0)
	{
		ShowMessage("�Ҳ�������ͷ�����ļ���");
        return FALSE;
	}
    
	/* �ҳ���Ƶ���ڵĴ�С */
    if( arVideoInqSize(&xsize, &ysize) < 0 )
	{
		ShowMessage("�޷���ȡ����ͷͼ��Ĵ�С��");
        return FALSE;
	}

    /* ��������ͷ��ʼ������ */
    if( arParamLoad(cparam_name, 1, &wparam) < 0 ) {
        printf("Camera parameter load error !!\n");
        return FALSE;
    }

    arParamChangeSize( &wparam, xsize, ysize, &cparam );
    arInitCparam( &cparam );

	/** װ��ƥ��ģ������ **/
    for(int i = 0; i < 2; i++ ) {
        if( (object[i].patt_id=arLoadPatt(object[i].patt_name)) < 0 ) {
			char * str = new char [126];
            sprintf(str,"pattern load error: %s\n", object[i].patt_name);
			ShowMessage(str);
            return FALSE;
        }
    }

	return TRUE;
}

void VideoCapture::run()
{
	isRunning = TRUE;
    /* ������ͷ��� */
    argInit( &cparam, 0, 0, 0, 0, 0 );
	/** ����Timer **/
	arUtilTimerReset();
    arVideoCapStart();
    while(1)
	{
		mainLoop();
	}
}

/**\brief
 *������ͷ��ȡһ֡ͼ��
 */
ARUint8 * VideoCapture::getImgFromCap()
{
	return m_pImgCaptureFromeCamera;
}


/**\brief
 *������Դ
 */
void VideoCapture::cleanup(void)
{
	isRunning = FALSE;
    arVideoCapStop();
    arVideoClose();
    argCleanup();
}

/**\brief
 *��ȡ��Ƶ�ļ��Ŀ�͸�
 */
int VideoCapture::getWidth()
{
	return xsize;
}
int VideoCapture::getHeight()
{
	return ysize;
}


void VideoCapture::mainLoop(void)
{
    ARMarkerInfo    *marker_info;
    int             marker_num;
    int             i, j, k;
	int lable_num;
	int *area,*clip, *label_ref;
	double *pos;

    /* ���Ի�ȡһ֡ͼ������ */
    if( (m_pImgCaptureFromeCamera = (ARUint8 *)arVideoGetImage()) == NULL ) {
        Sleep(1);
        return;
    }
	
	/** ��⿨Ƭλ������ **/
    if( arDetectMarker(m_pImgCaptureFromeCamera, thresh, &marker_info, &marker_num) < 0 ) {
        exit(0);
    }

    /* �����⵽��Ƭ��Ϣ���͸��¿�Ƭ�ṹ�����Ϣ */
    for( i = 0; i < 2; i++ ) {
        k = -1;
        for( j = 0; j < marker_num; j++ ) {
            if( object[i].patt_id == marker_info[j].id ) {
                if( k == -1 ) k = j;
                else if( marker_info[k].cf < marker_info[j].cf ) k = j;
            }
        }
        object[i].visible = k;

        if( k >= 0 ) {
            arGetTransMat(&marker_info[k],
                          object[i].center, object[i].width,
                          object[i].trans);
        }
    }

	/** ��������ͷÿ��15֡ **/
	if(isHeightSpeedCamera)
		Sleep(66);
	else
	/** Ϊ���ݵ�������ͷÿ��8֡ **/
		Sleep(118);
    arVideoCapNext();
    argSwapBuffers();
}

/** ��֡������ͷ **/
void VideoCapture::setLowSpeedCamera()
{
	isHeightSpeedCamera = FALSE;
}



/** ��ȡ��ǰ��Ƭ��Ϣ�ṹ **/
OBJECT_T * VideoCapture::getObjects()
{
	return object;
}