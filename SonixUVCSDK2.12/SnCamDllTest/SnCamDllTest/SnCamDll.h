
#pragma once
#define DT_API extern "C"

#ifdef SNCAMDLL_EXPORTS
#define SNCAMDLL_API __declspec(dllexport)
#else
#define SNCAMDLL_API __declspec(dllimport)
#endif

// ��������ֵ
typedef enum tagDS_CAMERA_STATUS
{
	STATUS_OK = 1,												// �����ɹ�
	STATUS_INTERNAL_ERROR = 0,							// �ڲ�����
	STATUS_NO_DEVICE_FIND = -1,							// û�з������
	STATUS_NOT_ENOUGH_SYSTEM_MEMORY = -2,		// û���㹻ϵͳ�ڴ�
	STATUS_HW_IO_ERROR = -3,								// Ӳ��IO����
	STATUS_PARAMETER_INVALID = -4,					// ������Ч
	STATUS_PARAMETER_OUT_OF_BOUND = -5,			// ����Խ��
	STATUS_FILE_CREATE_ERROR = -6,						// �����ļ�ʧ��
	STATUS_FILE_INVALID = -7,								// �ļ���ʽ��Ч
	STATUS_NO_RESOLUTION_FOUND=-8,					// ��֧�ִ˸�ʽ
	STATUS_NO_CAM_INIT=-9									// û�г�ʼ��
}DS_CAMERA_STATUS;

// ��ɫ�ռ�
typedef enum tagDS_COLORSPACE
{
	COLORSPACE_YUY2,											// YUV2
	COLORSPACE_MJPG,											// MJPEG
	COLORSPACE_RGB24,										// RGB24
	COLORSPACE_I420											// I420
}DS_COLORSPACE;

// ¼���ʽ
typedef enum tagDS_VIDEOFORMAT
{
	VIDEOFORMAT_avi,											// AVI
	VIDEOFORMAT_asf											// ASF
}DS_VIDEOFORMAT;

// ���ո�ʽ
typedef enum tagDS_PICTUREFOMAT
{
	PICTUREFORMAT_JPG,										// JPEG
	PICTUREFORMAT_BMP										// BMP
}DS_PICTUREFORMAT;

// ������
typedef enum tagDS_CAMERA_PROPERTY
{	
	PROPERTY_Brightness	= 0,								// ����
	PROPERTY_Contrast	= 1,									// �Աȶ�
	PROPERTY_Hue	= 2,										// ɫ��
	PROPERTY_Saturation	= 3,								// ���Ͷ�
	PROPERTY_Sharpness	= 4,								// ������
	PROPERTY_Gamma	= 5,									// ٤��
	PROPERTY_ColorEnable	= 6,								// �ڰ�
	PROPERTY_WhiteBalance	= 7,							// ��ƽ��
	PROPERTY_BacklightCompensation	= 8,				// ���Ա�
	PROPERTY_Gain	= 9										// ����
} DS_CAMERA_PROPERTY;

// ������
typedef enum tagDS_CAMERA_CONTROL
{
	CONTROL_Pan	= 0,											// ȫ��
	CONTROL_Tilt	= 1 ,											// ��б
	CONTROL_Roll	= 2 ,											// ����ת
	CONTROL_Zoom	= 3 ,										// ����
	CONTROL_Exposure	= 4 ,									// �ع�
	CONTROL_Iris	= 5 ,											// ��Ȧ
	CONTROL_Focus	= 6										// ����
} DS_CAMERA_CONTROL;

// �Ƿ��Զ�����
typedef enum tagDS_PROPERTY_FLAGS
{
	PROPERTY_FLAGS_Auto = 1,								// �Զ�
	PROPERTY_FLAGS_Manual = 2								// �ֶ�
} DS_PROPERTY_FLAGS, DS_CONTROL_FLAGS;

// ��ԴƵ��
typedef enum tagDS_POWER_LINE
{
	POWER_LINE_50Hz = 1,
	POWER_LINE_60Hz = 2
}DS_POWER_LINE;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	�ص�����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Function:		DS_SNAP_PROC
*	Description:		�ص����������붨�壩
*	Parameters:	ÿ֡Ԥ��ͼ�����ݣ����ݳ���
*	Return :			��������
*/
typedef int (CALLBACK* DS_SNAP_PROC)(BYTE *pImageBuffer, LONG BufferLength);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	�豸��Ϣ
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Function:		GetCameraCount
*	Description:		��ȡCamera������������ã�
*	Parameters:	Camera����
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS GetCameraCount(OUT LONG* CameraCout);

/*
*	Function:		GetCameraInfo
*	Description:		��ȡCamera��Ϣ
*	Parameters:	�����ţ�VID��PID���豸����
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS GetCameraInfo(IN BYTE CamNum, 
															OUT CHAR** VID, OUT CHAR** PID,
															OUT CHAR** DeviceName);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	�豸��ʼ�����ͷ�
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Function:		CameraInit
*	Description:		��ʼ��Camera��������ã�
*	Parameters:	�����ţ��ص�������Ԥ�����ھ��������Ԥ����NULL��
*	Return :			����״̬
*/

DT_API SNCAMDLL_API DS_CAMERA_STATUS  CameraInit(BYTE CamNum, 
															DS_SNAP_PROC pCallbackFunction,
															HWND hWndDisplay);
/*
*	Function:		CameraUnInit
*	Description:		�ͷ�Camera��������ã�
*	Parameters:	������
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraUnInit(BYTE CamNum);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Ԥ��
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Function:		GetPreviewResolutionCount
*	Description:		��ȡCamera֧�ֵ�Ԥ����ʽ����
*	Parameters:	�����ţ���ʽ����
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS GetPreviewResolutionCount(IN BYTE CamNum, 
															OUT LONG* ResolutionCount);

/*
*	Function:		GetPreviewResolutionInfo
*	Description:		��ȡ��ӦԤ����ʽ��Ϣ
*	Parameters:	�����ţ���ʽ��ţ�ɫ�ʿռ䣬����
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS GetPreviewResolutionInfo(IN BYTE CamNum, 
															IN BYTE ResolutionNum, 
															OUT DS_COLORSPACE* piColorspace,
															OUT LONG* plWidth, 
															OUT LONG* plHeight);

/*
*	Function:		CameraPlay
*	Description:		��ʼԤ��
*	Parameters:	������
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraPlay(BYTE CamNum);

/*
*	Function:		CameraStop
*	Description:		ֹͣԤ��
*	Parameters:	������
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraStop(BYTE CamNum);

/*
*	Function:		CameraSetVideoFormat
*	Description:		����Ԥ����ʽ
*	Parameters:	�����ţ���ʽ���
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraSetVideoFormat(BYTE CamNum, 
															BYTE ResolutionNum);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Function:		GetStillResolutionCount
*	Description:		��ȡCamera֧�ֵ����ո�ʽ����
*	Parameters:	�����ţ���ʽ����
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS GetStillResolutionCount(IN BYTE CamNum, 
															OUT LONG* ResolutionCount);
/*
*	Function:		GetStillResolutionInfo
*	Description:		��ȡ��Ӧ���ո�ʽ��Ϣ
*	Parameters:	�����ţ���ʽ��ţ���ɫ�ռ䣬����
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS GetStillResolutionInfo(IN BYTE CamNum, 
															IN BYTE ResolutionNum,
															OUT DS_COLORSPACE* piColorspace,
															OUT LONG* plWidth,
															OUT LONG* plHeight);
/*
*	Function:		CameraSetStillFormat
*	Description:		�������ո�ʽ
*	Parameters:	�����ţ���ʽ���
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraSetStillFormat(BYTE CamNum, 
															BYTE ResolutionNum);
/*
*	Function:		CameraSnapShot
*	Description:		����
*	Parameters:	�����ţ�BMPorJPEG��ͼƬ�ļ����ƣ�����ͼƬ·�����ļ�����
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraSnapShot(BYTE CamNum, 
															DS_PICTUREFORMAT uiformat,
															WCHAR* wszPictureFile
															);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	¼��
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Function:		CameraStartCapture
*	Description:		��ʼ¼��
*	Parameters:	�����ţ�AVIorASF��¼���ļ����ƣ�����ͼƬ·�����ļ�����
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraStartCapture(BYTE CamNum,
															DS_VIDEOFORMAT uiformat,
															WCHAR* wszCaptureFile);
/*
*	Function:		CameraStopCapture
*	Description:		ֹͣ¼��
*	Parameters:	������
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraStopCapture(BYTE CamNum);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	���Լ�����
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Function:		CameraPropertyGetRange
*	Description:		��ȡ����ҳ��Ŀ��Χ��������Ĭ��ֵ���Ƿ��Զ�
*	Parameters:	�����ţ�����ֵ����Сֵ�����ֵ���������Ƿ��Զ�
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraPropertyGetRange(IN BYTE CamNum, 
															IN DS_CAMERA_PROPERTY uiProperty,
															OUT LONG* pMin, OUT LONG* pMax,
															OUT LONG* pSteppingDelta, 
															OUT LONG* pDefault,
															OUT DS_PROPERTY_FLAGS* pCapsFlags
															);

/*
*	Function:		CameraPropertyGet
*	Description:		��ȡ����ҳ��Ŀ����ֵ
*	Parameters:	�����ţ�����ֵ������ֵ���Ƿ��Զ�
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraPropertyGet(BYTE CamNum, 
															DS_CAMERA_PROPERTY uiProperty,
															OUT LONG* lValue, 
															OUT DS_PROPERTY_FLAGS* Flags
															);

/*
*	Function:		CameraPropertySet
*	Description:		��������ҳ��Ŀ
*	Parameters:	�����ţ�����ֵ������ֵ���Ƿ��Զ�
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraPropertySet(BYTE CamNum, 
															DS_CAMERA_PROPERTY uiProperty,
															IN LONG lValue, 
															IN DS_PROPERTY_FLAGS Flags
															);

/*
*	Function:		CameraControlGetRange
*	Description:		��ȡ����ҳ��Ŀ��Χ��������Ĭ��ֵ���Ƿ��Զ�
*	Parameters:	�����ţ�����ֵ����Сֵ�����ֵ���������Ƿ��Զ�
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraControlGetRange(BYTE CamNum, 
															DS_CAMERA_CONTROL uiControl,
															OUT LONG* pMin, OUT LONG* pMax,
															OUT LONG* pSteppingDelta, 
															OUT LONG* pDefault,
															OUT DS_CONTROL_FLAGS* pCapsFlags
															);

/*
*	Function:		CameraControlGet
*	Description:		��ȡ����ҳ��Ŀ����ֵ
*	Parameters:	�����ţ�����ֵ������ֵ���Ƿ��Զ�
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraControlGet(BYTE CamNum, 
															DS_CAMERA_CONTROL uiControl,
															OUT LONG* lValue, 
															OUT DS_CONTROL_FLAGS* Flags
															);

/*
*	Function:		CameraControlSet
*	Description:		���ÿ���ҳ��Ŀ
*	Parameters:	�����ţ�����ֵ������ֵ���Ƿ��Զ�
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraControlSet(BYTE CamNum, 
															DS_CAMERA_CONTROL uiControl,
															IN LONG lValue, 
															IN DS_CONTROL_FLAGS Flags
															);

/*
*	Function:		CameraGetFrameSpeed
*	Description:		��ȡ��ǰ֡��
*	Parameters:	�����ţ�֡��
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraGetFrameSpeed(BYTE CamNum,
															OUT DOUBLE* dFramerate);

/*
*	Function:		CameraSetFrameSpeed
*	Description:		����֡��
*	Parameters:	�����ţ�֡��
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraSetFrameSpeed(BYTE CamNum,
															IN DOUBLE dFramerate);

/*
*	Function:		CameraSetPowerLine
*	Description:		���õ�ԴƵ��
*	Parameters:	�����ţ���ԴƵ��
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraSetPowerLine(BYTE CamNum, 
															IN DS_POWER_LINE PowerLine
															);


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	�Ĵ���
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*	Function:		CameraReadDSP
*	Description:		���Ĵ���
*	Parameters:	�����ţ��Ĵ�����ַ��ֵ
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraReadDSP(BYTE CamNum, 
															LONG laddress, OUT LONG* lData);

/*
*	Function:		CameraWriteDSP
*	Description:		д�Ĵ���
*	Parameters:	�����ţ��Ĵ�����ַ��ֵ
*	Return :			����״̬
*/
DT_API SNCAMDLL_API DS_CAMERA_STATUS CameraWriteDSP(BYTE CamNum, 
															LONG laddress, IN LONG* lData);