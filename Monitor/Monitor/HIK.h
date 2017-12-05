#pragma once
#include"head.h"
#include"GeneralDef.h"
//#include"hik\HCNetSDK.h"
#include"time.h"
using namespace std;


//typedef HWND(WINAPI *PROCGETCONSOLEWINDOW)();
//PROCGETCONSOLEWINDOW GetConsoleWindowAPI;

//HCNetSDK.lib
//PlayCtrl.lib


#pragma  comment(lib, "HCNetSDK.lib")
#pragma  comment(lib, "PlayCtrl.lib")

//void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
//{
//	char tempbuf[256] = { 0 };
//	switch (dwType)
//	{
//	case EXCEPTION_RECONNECT:    //Ԥ��ʱ����
//		printf("----------reconnect--------%d\n", time(NULL));
//		break;
//	default:
//		break;
//	}
//}


class HIK
{
public:
	HIK();
	~HIK();
	void Init(char * ip, int port, char * username, char * password);
	bool Logout(LONG ID);
	LONG Login(char * ip, int port, char * username, char * password, NET_DVR_DEVICEINFO_V40 &struDeviceInfoV40);
	//bool GetCompressionParameters();
	bool GetBasicParameters();
	bool StartPreview();
	bool EndPreview();
	/*��������*/
	bool GetDVRConfig(LONG lUserID,DWORD dwCommand,LONG lChannel,LPVOID lpOutBuffer,DWORD dwOutBufferSize);
	bool SetDVRConfig(LONG lUserID, DWORD dwCommand, LONG lChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize);
	bool GetDeviceConfig(LONG lUserID, DWORD dwCommand,DWORD dwCount,LPVOID lpInBuffer,DWORD dwInBufferSize,LPVOID lpStatusList,LPVOID lpOutBuffer, DWORD dwOutBufferSize);
	bool SetDeviceConfig(LONG lUserID, DWORD dwCommand, DWORD dwCount, LPVOID lpInBuffer, DWORD dwInBufferSize, LPVOID lpStatusList, LPVOID lpOutBuffer);
	bool GetSTDConfig(LONG lUserID, DWORD dwCommand,LPNET_DVR_STD_CONFIG lpConfigParam);
	bool SetSTDConfig(LONG lUserID, DWORD dwCommand, LPNET_DVR_STD_CONFIG lpConfigParam);
	bool STDXMLConfig(LONG lUserID, NET_DVR_XML_CONFIG_INPUT     *lpInputParam,NET_DVR_XML_CONFIG_OUTPUT    *lpOutputParam);
	bool RemoteControl(LONG lUserID, DWORD dwCommand,LPVOID    lpInBuffer,DWORD     dwInBufferSize);
	/*GetDVRConfig*/
	bool GetDeviceParameters(LONG lUserID, LONG lChannel, NET_DVR_DEVICECFG_V40&struParams);//�豸����(��չ)
	bool GetImageParameters(LONG lUserID, LONG lChannel, NET_DVR_PICCFG_V40 &struParams);//ͼ�����
	bool GetCompressionParameters(LONG lUserID, LONG lChannel, NET_DVR_COMPRESSIONCFG_V30 &struParams);//ѹ������
	bool SetCompressionParameters(LONG lUserID, LONG lChannel,  NET_DVR_COMPRESSIONCFG_V30 &struParams);//����ѹ������
	bool GetRecordingPlanParameters(LONG lUserID, LONG lChannel);//¼��ƻ�����
	//bool GetVideoInputImageParameters(LONG lChannel); //ͨ����Ƶ����ͼ�����(�豸��֧��)
	bool GetNetworkParameters(LONG lUserID);//�豸�������(�豸��֧��)
	bool GetHTTPSInformation(LONG lUserID);//HTTP��Ϣ
	bool GetIPAccessConfigurationParameters(LONG lUserID);//����IP���ò���(�豸��֧��)
	bool TestFunctiong(LONG lUserID,DWORD dwCommand);//������
	/*GetDeviceConfig*/


	/*��̨����*/
	bool PTZControl(LONG     lRealHandle,DWORD    dwPTZCommand,DWORD    dwStop);
	bool TiltUp(LONG     lRealHandle, DWORD    dwStop);//��
	bool TiltDown(LONG     lRealHandle, DWORD    dwStop);//��
	bool PanLeft(LONG     lRealHandle, DWORD    dwStop);//��
	bool PanRight(LONG     lRealHandle, DWORD    dwStop);//��

public:
	//LONG lUserID;
	//bool isLogin;
	
	
	//NET_DVR_USER_LOGIN_INFO struLoginInfo;
	
	
	//NET_DVR_DEVICEINFO_V40 struDeviceInfoV40;
	//vector<NET_DVR_COMPRESSIONCFG_V30> strCompressioncfg_V30//;
	//NET_DVR_DEVICEINFO_V40 struDeviceInfoV40;//����������ýṹ��
	//NET_DVR_DEVICECFG m_struDeviceCfg;//�豸�������ýṹ��
	//NET_DVR_GET_TIMECFG test;
	//NET_DVR_GET_DEVICECFG_V40 t;
	//LONG lRealPlayHandle;


	//LOCAL_DEVICE_INFO struDeviceInfo;
};

