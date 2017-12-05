
// MonitorDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "HIK.h"
#include"PreviewWind.h"
#include"ConfigWind.h"
#include"LoginWind.h"
#include"ShowWind.h"
#include"Message.h"
#include "afxwin.h"



// CMonitorDlg dialog
class CMonitorDlg : public CDialogEx
{
// Construction
public:
	CMonitorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONITOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	unsigned int m_DevPort;
//	UINT m_DevPort;
//	CString m_UserName;
//	CString m_PassWord;
//	CIPAddressCtrl m_DevIP;
	afx_msg void OnBnClickedButtonLogin();
public:
	HIK hik;
	PreviewWind m_PreviewWind;
	ConfigWind m_ConfigWind;

	bool m_IsLogin;//�Ƿ��¼���
	long m_lPlayHandle[9];
	bool m_bIsPlaying[9];
	CTreeCtrl m_ctrlTreeDev;
	HTREEITEM m_hDevItem;

	HWND m_PlayWnd[WIND_MAX_NUM];//���ž��
	ID_CH_HAND_MATCH IDChMatchWind[WIND_MAX_NUM];
	LOCAL_DEVICE_INFO m_struDeviceInfo[10];//�豸��Ϣ�ṹ��

	CComboBox m_ComboWindNum;
	CTabCtrl m_tab;//�Ի���ؼ�
	CRect TabRect;//tab�ؼ���С

	vector<CString> ipstring;//�洢ע���˵�ip��ַ
	vector<CString> DevName;//�豸����

	int DeviceNum;//ע��������豸
	int m_iCurChanIndex;//ѡ��ͨ����
	int m_CurrentWindNum;//��ǰѡ�д���id��
	int m_iCurDevIndex;//ѡ���豸��

	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnNMDblclkTreeDev(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnTcnSelchangeTabControl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonConfig();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonCloudsUp();
	afx_msg LRESULT OnCurrentWindNumMsg(WPARAM, LPARAM);//��ǰѡ�д�����Ӧ����
	afx_msg void OnCbnSelendcancelComboWindNum();
	afx_msg void OnCbnSelchangeComboWindNum();
	afx_msg void OnNMClickTreeDev(NMHDR *pNMHDR, LRESULT *pResult);


	bool Login(CString, CString, CString, CString);//ע�ắ��
	bool StartPlay(int loginID,int ch);
	bool StopPlay(ID_CH_HAND_MATCH &hd);
	void DbPlayChannel(int,int index);
	void DoGetDeviceResoureCfg();
	void CreateDeviceTree(LONG longinID);
	void CodeMatching(NET_DVR_COMPRESSION_INFO_V30 info);	
	void TabConfig();
	int ResolutionCodeMatch(int code);
	void GetCompressioncfg();
	void CombInit();
	int m_AllWindNum;//��ǰ���д��ڸ���
	void ShowWindInit();//��ʾ���ڳ�ʼ��


};
