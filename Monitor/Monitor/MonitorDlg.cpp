
// MonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "MonitorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMonitorDlg dialog



CMonitorDlg::CMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MONITOR_DIALOG, pParent)
	//, m_DevPort(8000)
	//, m_UserName(_T("admin"))
	//, m_PassWord(_T("admin172"))
	//, m_lPlayHandle(0)
	//, m_bIsPlaying(false)
	, m_iCurChanIndex(0)
	, DeviceNum(0)
	//, CurrentDeviceNum(0)
	//, CurrentChannelNum(0)
	/*, m_PlayingWindNum(0)*/
	, m_CurrentWindNum(0)
	, m_AllWindNum(0)
	, m_iCurDevIndex(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  m_DevPort = 0;
}

void CMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT_PORT, m_DevPort);
	//  DDX_Text(pDX, IDC_EDIT_USER, m_UserName);
	//  DDX_Text(pDX, IDC_EDIT_PASSWORD, m_PassWord);
	//  DDX_Control(pDX, IDC_IPADDRESS_DEV, m_DevIP);
	DDX_Control(pDX, IDC_TREE_DEV, m_ctrlTreeDev);
	//  DDX_Control(pDX, IDC_STATIC_PLAYWINDOW1, m_PlayWind1);
	//  DDX_Control(pDX, IDC_STATIC_PLAYWINDOW2, m_PlayWind2);
	DDX_Control(pDX, IDC_TAB1, m_tab);
	DDX_Control(pDX, IDC_COMBO_WIND_NUM, m_ComboWindNum);
}

BEGIN_MESSAGE_MAP(CMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CMonitorDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CMonitorDlg::OnBnClickedButtonPlay)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_DEV, &CMonitorDlg::OnNMDblclkTreeDev)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CMonitorDlg::OnBnClickedButtonLogout)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, &CMonitorDlg::OnTcnSelchangeTabControl)
	ON_BN_CLICKED(IDC_BUTTON_GET, &CMonitorDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, &CMonitorDlg::OnBnClickedButtonConfig)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMonitorDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_CLOUDS_UP, &CMonitorDlg::OnBnClickedButtonCloudsUp)

	//
	ON_MESSAGE(WM_CURRENT_WIND_NUM, &CMonitorDlg::OnCurrentWindNumMsg)
	ON_CBN_SELENDCANCEL(IDC_COMBO_WIND_NUM, &CMonitorDlg::OnCbnSelendcancelComboWindNum)
	ON_CBN_SELCHANGE(IDC_COMBO_WIND_NUM, &CMonitorDlg::OnCbnSelchangeComboWindNum)
	ON_NOTIFY(NM_CLICK, IDC_TREE_DEV, &CMonitorDlg::OnNMClickTreeDev)
END_MESSAGE_MAP()


// CMonitorDlg message handlers

BOOL CMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CombInit();
	TabConfig();//
	
	ShowWindInit();
	m_ConfigWind.Init();
	//m_PreviewWind.DrawFrame();

	
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMonitorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//m_PreviewWind.DrawFrame();
		CDialogEx::OnPaint();
		//m_PreviewWind.DrawFrame();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMonitorDlg::OnBnClickedButtonLogin()
{




	//CDialog::OnOK();


	//UpdateData(TRUE);


	//CString DeviceIp;
	//char * ip;
	//char * user;
	//char * password;
	//m_DevIP.GetWindowTextW(DeviceIp);
	CString Sname;
	CString  Sip;
	CString Sport;
	CString Susername;
	CString Spassword;

	LoginWind dig;
	if (dig.DoModal() == IDOK)
	{
		 Sname = dig.m_name;
		  Sip = dig.m_IP;
		 Sport = dig.m_Port;
		 Susername = dig.m_Username;
		 Spassword = dig.m_Password;


		if (Login(Sip, Sport, Susername, Spassword))
		{
			//GetCompressioncfg();
			DoGetDeviceResoureCfg();  //��ȡ�豸��Դ��Ϣ	
			CreateDeviceTree(m_struDeviceInfo[DeviceNum].lLoginID);        //����ͨ����
																		   
			GetCompressioncfg();
			m_iCurDevIndex = DeviceNum;
			DeviceNum++;
			//GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText(_T("Logout"));
			//m_IsLogin = true;

		}
		//MessageBox(str);
	}









}

/*************************************************
Function:Login
Description:�豸ע��
Input:
Output:         
Return:         
Others:        

*************************************************/
bool CMonitorDlg::Login(CString  Sip,CString Sport,CString Susername,CString Spassword)
{
	for (auto i = ipstring.cbegin(); i != ipstring.cend(); i++)
	{
		int j = Sip.Compare(*i);
		if (0 == j)
		{
			MessageBox(_T("�豸��ע��"));
			return false;
		}

	}

	int n, len;

	//�ַ������� CStringתΪchar*       //ip
	n = Sip.GetLength(); //��ȡstr���ַ���    
	len = WideCharToMultiByte(CP_ACP, 0, Sip, n, NULL, 0, NULL, NULL); //��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����    
	char *ip = new char[len + 1]; //���ֽ�Ϊ��λ    
	WideCharToMultiByte(CP_ACP, 0, Sip, n, ip, len, NULL, NULL); //���ֽڱ���ת���ɶ��ֽڱ���    
	ip[len] = '\0'; //���ֽ��ַ���'\0'���� ԭ�Ĵ����д���Ŷ  

					//�ַ������� CStringתΪchar*     //username
	n = Susername.GetLength(); //��ȡstr���ַ���    
	len = WideCharToMultiByte(CP_ACP, 0, Susername, n, NULL, 0, NULL, NULL); //��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����    
	char *user = new char[len + 1]; //���ֽ�Ϊ��λ    
	WideCharToMultiByte(CP_ACP, 0, Susername, n, user, len, NULL, NULL); //���ֽڱ���ת���ɶ��ֽڱ���    
	user[len] = '\0'; //���ֽ��ַ���'\0'���� ԭ�Ĵ����д���Ŷ  

					  //�ַ������� CStringתΪchar*     //password
	n = Spassword.GetLength(); //��ȡstr���ַ���    
	len = WideCharToMultiByte(CP_ACP, 0, Spassword, n, NULL, 0, NULL, NULL); //��ȡ���ֽ��ַ��Ĵ�С����С�ǰ��ֽڼ����    
	char *password = new char[len + 1]; //���ֽ�Ϊ��λ    
	WideCharToMultiByte(CP_ACP, 0, Spassword, n, password, len, NULL, NULL); //���ֽڱ���ת���ɶ��ֽڱ���    
	password[len] = '\0'; //���ֽ��ַ���'\0'���� ԭ�Ĵ����д���Ŷ 

	int port = 8000;
	Sport.Format(_T("%d"), port);



	NET_DVR_DEVICEINFO_V40 struDeviceInfoV40={ 0 };
	LONG LoginID=hik.Login(ip, port,user, password, struDeviceInfoV40);


	if (-1==LoginID)
	{
		MessageBox(_T("Login to Device failed!"));
		CString str;
		str.Format(_T("%d", NET_DVR_GetLastError));
		MessageBox(str);
		return FALSE;
	}
	MessageBox(_T("success"));

	ipstring.push_back(Sip);//

	m_struDeviceInfo[DeviceNum].lLoginID = LoginID;// lLoginID;
	m_struDeviceInfo[DeviceNum].iDeviceChanNum = struDeviceInfoV40.struDeviceV30.byChanNum;//DeviceInfoTmp.byChanNum;
	m_struDeviceInfo[DeviceNum].iIPChanNum = struDeviceInfoV40.struDeviceV30.byIPChanNum;
	m_struDeviceInfo[DeviceNum].iStartChan = struDeviceInfoV40.struDeviceV30.byStartChan;
	m_struDeviceInfo[DeviceNum].iIPStartChan = struDeviceInfoV40.struDeviceV30.byStartDChan;
	//struDeviceInfoV40.struDeviceV30.

	return TRUE;
}
void CMonitorDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here

	StopPlay(IDChMatchWind[m_CurrentWindNum]);

	bool temp = false;//�����ж��Ƿ��д����ڲ���
	for (int i = 0; i < m_AllWindNum; i++)
	{
		if (IDChMatchWind[i].bIsPlaying)// = true;
		{
			temp = true;//�д������� ����
			break;
		}
		
	}
	if (!temp)//û�д��ڲ���
		m_ComboWindNum.EnableWindow(true);
}

void CMonitorDlg::OnBnClickedButtonPlay()
{

	if (!IDChMatchWind[m_CurrentWindNum].bIsPlaying)//��ǰ�����Ƿ��ڲ���
	{
		bool temp = true;
		for (int i = 0; i <m_AllWindNum; i++)
		{
					if (m_iCurDevIndex == IDChMatchWind[i].lLoginID
						&&m_iCurChanIndex == IDChMatchWind[i].iDeviceChan
						)//�ҵ���ǰ�豸
					{
						if (IDChMatchWind[i].bIsPlaying)//��ǰ�豸�Ƿ��ڲ���
						{
							temp = false;
							 break;

						}

					}
		}
		if (temp)//��ǰ�豸��ǰ���ڶ�û�ڲ���
		{
			StartPlay(m_iCurDevIndex, m_iCurChanIndex);//����  ע��id+ͨ��id 
			//m_AllWindNum
			m_ComboWindNum.EnableWindow(false);//���øı���ʾ���ڸ���

		}

	}


}


bool CMonitorDlg::StartPlay(int loginID,int ch)
{


	IDChMatchWind[m_CurrentWindNum].lLoginID = loginID;
	IDChMatchWind[m_CurrentWindNum].iDeviceChan = ch;
	IDChMatchWind[m_CurrentWindNum].iPlayWindID = m_CurrentWindNum;

	NET_DVR_CLIENTINFO ClientInfo;//�豸��Ϣ�ṹ��
	

	ClientInfo.hPlayWnd = m_PlayWnd[m_CurrentWindNum];
	ClientInfo.lChannel = ch +1;
	ClientInfo.lLinkMode = 0;
	ClientInfo.sMultiCastIP = NULL;

	TRACE("Channel number:%d\n", ClientInfo.lChannel);

	IDChMatchWind[m_CurrentWindNum].LPlayHandID = NET_DVR_RealPlay_V30(loginID, &ClientInfo, NULL, NULL, TRUE);

	if (-1 == IDChMatchWind[m_CurrentWindNum].LPlayHandID)
	{
		DWORD err = NET_DVR_GetLastError();
		CString m_csErr;
		m_csErr.Format(_T("���ų����������%d"), err);
		MessageBox(m_csErr);
		return false;
	}

	IDChMatchWind[m_CurrentWindNum].bIsPlaying = true;//���ڲ���

	return true;
}




bool CMonitorDlg::StopPlay(ID_CH_HAND_MATCH &hd)
{

	if (hd.LPlayHandID != -1)
	{

		NET_DVR_StopRealPlay(hd.LPlayHandID);

		hd.lLoginID = -1;
		hd.iDeviceChan = -1;
		hd.LPlayHandID = -1;

		hd.bIsPlaying = false;

		m_PreviewWind.Invalidate();
		return true;
	}
	return false;
}


void CMonitorDlg::DoGetDeviceResoureCfg()
{


	NET_DVR_IPPARACFG_V40 IpAccessCfg;
	memset(&IpAccessCfg, 0, sizeof(IpAccessCfg));
	DWORD  dwReturned;

	//m_struDeviceInfo.bIPRet = NET_DVR_GetDVRConfig(m_struDeviceInfo.lLoginID, NET_DVR_GET_IPPARACFG_V40, 0, &IpAccessCfg, sizeof(NET_DVR_IPPARACFG_V40), &dwReturned);
	m_struDeviceInfo[DeviceNum].bIPRet = NET_DVR_GetDVRConfig(m_struDeviceInfo[DeviceNum].lLoginID, NET_DVR_GET_IPPARACFG_V40, 0, &IpAccessCfg, sizeof(NET_DVR_IPPARACFG_V40), &dwReturned);

	int i;
	if (!m_struDeviceInfo[DeviceNum].bIPRet)   //��֧��ip����,9000�����豸��֧�ֽ���ģ��ͨ��
	{
		for (i = 0; i<MAX_ANALOG_CHANNUM; i++)
		{
			if (i < m_struDeviceInfo[DeviceNum].iDeviceChanNum)
			{
				sprintf_s(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName, "camera%d", i + m_struDeviceInfo[DeviceNum].iStartChan);
				m_struDeviceInfo[DeviceNum].struChanInfo[i].iChanIndex = i + m_struDeviceInfo[DeviceNum].iStartChan;  //ͨ����
				m_struDeviceInfo[DeviceNum].struChanInfo[i].bEnable = TRUE;

			}
			else
			{
				m_struDeviceInfo[DeviceNum].struChanInfo[i].iChanIndex = -1;
				m_struDeviceInfo[DeviceNum].struChanInfo[i].bEnable = FALSE;
				sprintf_s(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName, "");
			}
		}
	}
	else        //֧��IP���룬9000�豸
	{
		for (i = 0; i<MAX_ANALOG_CHANNUM; i++)  //ģ��ͨ��
		{
			if (i < m_struDeviceInfo[DeviceNum].iDeviceChanNum)
			{
				sprintf_s(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName, "camera%d", i + m_struDeviceInfo[DeviceNum].iStartChan);
				m_struDeviceInfo[DeviceNum].struChanInfo[i].iChanIndex = i + m_struDeviceInfo[DeviceNum].iStartChan;
				if (IpAccessCfg.byAnalogChanEnable[i])
				{
					m_struDeviceInfo[DeviceNum].struChanInfo[i].bEnable = TRUE;
				}
				else
				{
					m_struDeviceInfo[DeviceNum].struChanInfo[i].bEnable = FALSE;
				}

			}
			else//clear the state of other channel
			{
				m_struDeviceInfo[DeviceNum].struChanInfo[i].iChanIndex = -1;
				m_struDeviceInfo[DeviceNum].struChanInfo[i].bEnable = FALSE;
				sprintf_s(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName, "");
			}
		}

		//����ͨ��
		for (i = 0; i<MAX_IP_CHANNEL; i++)
		{
			if (IpAccessCfg.struStreamMode[i].uGetStream.struChanInfo.byEnable)  //ipͨ������
			{
				m_struDeviceInfo[DeviceNum].struChanInfo[i + MAX_ANALOG_CHANNUM].bEnable = TRUE;
				m_struDeviceInfo[DeviceNum].struChanInfo[i + MAX_ANALOG_CHANNUM].iChanIndex = i + IpAccessCfg.dwStartDChan;
				sprintf_s(m_struDeviceInfo[DeviceNum].struChanInfo[i + MAX_ANALOG_CHANNUM].chChanName, "IP Camera %d", i + 1);

			}
			else
			{
				m_struDeviceInfo[DeviceNum].struChanInfo[i + MAX_ANALOG_CHANNUM].bEnable = FALSE;
				m_struDeviceInfo[DeviceNum].struChanInfo[i + MAX_ANALOG_CHANNUM].iChanIndex = -1;
			}
		}


	}
}

///
void CMonitorDlg::CreateDeviceTree(LONG loginID)
{
	CString str = _T("Dev");
	CString strnum;
	LONG a = loginID;
	strnum.Format(_T("%d"), a);
	str += strnum;
	//m_hDevItem = m_ctrlTreeDev.InsertItem(_T("Dev"));
	m_hDevItem = m_ctrlTreeDev.InsertItem(str);
	//m_ctrlTreeDev.InsertItem();
	m_ctrlTreeDev.SetItemData(m_hDevItem, DEVICETYPE * 1000);
	for (int i = 0; i<MAX_CHANNUM_V30; i++)
	{

		if (m_struDeviceInfo[DeviceNum].struChanInfo[i].bEnable)  //ͨ����Ч������ͨ����
		{

			if (i<MAX_ANALOG_CHANNUM)
			{
				CString str(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName);
				HTREEITEM ChanItem = m_ctrlTreeDev.InsertItem(str, m_hDevItem);
				m_iCurChanIndex = i;
				m_ctrlTreeDev.SetItemData(ChanItem, CHANNELTYPE * 1000 + 100 * loginID + i);   //Data��Ӧͨ���������е�����
				DevName.push_back(str);
			}
			else
			{
				CString str(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName);
				HTREEITEM ChanItem = m_ctrlTreeDev.InsertItem(str, m_hDevItem);
				m_iCurChanIndex = i- MAX_ANALOG_CHANNUM;
				m_ctrlTreeDev.SetItemData(ChanItem, CHANNELTYPE * 1000 + 100 * loginID + i);   //Data��Ӧͨ���������е�����
				DevName.push_back(str);
				//ipstring
			}
			////LPCTSTR buffer;
			////lstrcpy(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName, buffer);

			////wcstombs();
			//CString str(m_struDeviceInfo[DeviceNum].struChanInfo[i].chChanName);
			//HTREEITEM ChanItem = m_ctrlTreeDev.InsertItem(str, m_hDevItem);
			//m_iCurChanIndex = i;
			//m_ctrlTreeDev.SetItemData(ChanItem, CHANNELTYPE * 1000 + 100*loginID +i);   //Data��Ӧͨ���������е�����
		}
	}
	//m_ctrlTreeDev.setsel
	m_ctrlTreeDev.Expand(m_hDevItem, TVE_EXPAND);
}


void CMonitorDlg::OnNMClickTreeDev(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	HTREEITEM hSelected = m_ctrlTreeDev.GetSelectedItem();
	//δѡ��
	if (NULL == hSelected)
		return;
	DWORD itemData = m_ctrlTreeDev.GetItemData(hSelected);
	HTREEITEM hParent = NULL;
	int itype = itemData / 1000;    //

									/*int iIndex = itemData % 1000;*/
	int id = itemData / 100 % 10;

	int shiwei = itemData / 10 % 10;
	int gewei = itemData % 10;
	int iIndex = shiwei * 10 + gewei;


	if (iIndex >= MAX_ANALOG_CHANNUM)
		iIndex = iIndex - MAX_ANALOG_CHANNUM;



	switch (itype)
	{
	case DEVICETYPE:
		m_iCurChanIndex = -1;
		break;
	case CHANNELTYPE:
		m_iCurChanIndex = iIndex;
		TRACE("select chan: %d\n", iIndex);
		//CurrentDeviceNum = id;
		m_iCurDevIndex = id;
		//DbPlayChannel(m_struDeviceInfo[id].lLoginID,iIndex);
		//OnSelchangeComboPreset();
		break;
	default:
		break;

	}

	*pResult = 0;
}

void CMonitorDlg::OnNMDblclkTreeDev(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here

	GetCompressioncfg();

	*pResult = 0;
}


void CMonitorDlg::DbPlayChannel(int LongID,int index)
{
	if (!m_bIsPlaying[LongID])  //Play
	{
		StartPlay(LongID,index);
	}
	else                //Stop,play
	{
		StartPlay(LongID, index);
	}
		//StartPlay(LongID,index);

	
}


void CMonitorDlg::OnBnClickedButtonLogout()
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < DeviceNum; i++)
	{
		hik.Logout(m_struDeviceInfo[i].lLoginID);
		//GetDlgItem(IDC_BUTTON_LOGIN)->SetWindowText(_T("Login"));
	}
}


void CMonitorDlg::CodeMatching(NET_DVR_COMPRESSION_INFO_V30 info)
{
	BYTE     byStreamType= info.byStreamType;//��������  0-��Ƶ����1-������
	BYTE     byResolution= info.byResolution;//�ֱ���  16-VGA(640*480)��3-4CIF(704*576/704*480) 19-HD720P(1280*720)��20-XVGA(1280*960)��
	BYTE     byBitrateType= info.byBitrateType;//��������  0-�����ʣ�1-������ 

	BYTE     byPicQuality= info.byPicQuality;//ͼ������  0-��ã�1-�κã�2-�Ϻã�3-һ�㣬4-�ϲ5-��
	//DWORD    dwVideoBitrate;//��Ƶ����  0-������1-16K(����)��2-32K��3-48k��4-64K��5-80K��6-96K��7-128K��8-160k��9-192K��10-224K��11-256K��12-320K��13-384K��14-448K��15-512K��16-640K��17-768K��18-896K��19-1024K��20-1280K��21-1536K��22-1792K��23-2048K��24-3072K��25-4096K��26-8192K��27-16384K��
	DWORD    dwVideoFrameRate= info.dwVideoFrameRate;//��Ƶ֡�� 0-ȫ����1-1/16��2-1/8��3-1/4��4-1/2��5-1��6-2��7-4��8-6��9-8��10-10��11-12��12-16��13-20��14-15��15-18��16��22��17-25��18-30��19-35��20-40��21-45��22-50��23-55��24-60��25-3��26-5��27-7��28-9��29-100��30-120��31-24��32-48��
	BYTE     byFormatType= info.byFormatType;//��Ƶ�������� 0-˽��264��1-��׼h264��2-��׼mpeg4��7-M-JPEG��8-MPEG2��9-SVAC��10-��׼h265��0xfe- �Զ�����Դһ�£���0xff-��Ч 
	//����
	switch (byStreamType)
	{
	case '0':; break;
	case '1':; break;
	default:
		break;
	}

	//�ֱ���
	switch (byResolution)
	{
	case '3':; break;
	case '16':; break;
	case '19':; break;
	case '20':; break;
	default:
		break;
	}


	//��������
	switch (byBitrateType)
	{
	case '0':; break;
	case '1':; break;
	default:
		break;
	}

	//ͼ������
	switch (byPicQuality)
	{
	case '0':; break;
	case '1':; break;
	case '2':; break;
	case '3':; break;
	case '4':; break;
	case '5':; break;
	default:
		break;
	}

	////��Ƶ����
	//switch (dwVideoBitrate)
	//{
	//case '0':; break;
	//case '1':; break;
	//default:
	//	break;
	//}

	//��Ƶ֡��
	switch (dwVideoFrameRate)
	{
	case 0:; break;
	case 1:; break;
	case 2:; break;
	case 3:; break;
	case 4:; break;
	case 5:; break;
	case 6:; break;
	case 7:; break;
	case 8:; break;
	case 9:; break;
	case 10:; break;
	case 11:; break;
	case 12:; break;
	case 13:; break;
	case 14:; break;
	case 15:; break;
	case 16:; break;
	case 17:; break;
	default:
		break;
	}

	//��Ƶ��������
	switch (byFormatType)
	{
	case '0':; break;
	case '1':; break;
	case '2':; break;
	case '6':; break;
	case '7':; break;
	case '8':; break;
	case '9':; break;
	case '10':; break;
	default:
		break;
	}







}




/*************************************************
Function:TabConfig
Description:TabControl�ؼ���ʼ����
Input:
Output:
Return:
Others:
*************************************************/
void CMonitorDlg::TabConfig()
{

	m_tab.InsertItem(0, _T("��ƵԤ��"));
	m_tab.InsertItem(1, _T("��������"));
	m_PreviewWind.Create(IDD_DIALOG_VIDEOSHOW, GetDlgItem(IDC_TAB_CONTROL));
	m_ConfigWind.Create(IDD_DIALOG_CONFIGURATION, GetDlgItem(IDC_TAB_CONTROL));

	m_tab.GetClientRect(&TabRect);

	TabRect.top += 23;
	TabRect.bottom -= 3;
	TabRect.left += 3;
	TabRect.right -= 3;
	
		
	m_PreviewWind.MoveWindow(&TabRect);
	m_ConfigWind.MoveWindow(&TabRect);

	m_PreviewWind.ShowWindow(true);
	m_ConfigWind.ShowWindow(false);

	m_tab.SetCurSel(0);
}

/*************************************************
Function:OnTcnSelchangeTabControl
Description:TabControl�ؼ���ǩҳ�л���Ӧ����
Input:
Output:
Return:
Others:
*************************************************/
void CMonitorDlg::OnTcnSelchangeTabControl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	int CurSel = m_tab.GetCurSel();
	switch (CurSel)
	{
	case 0:m_PreviewWind.ShowWindow(true);
		m_ConfigWind.ShowWindow(false);
		break;
	case 1: m_PreviewWind.ShowWindow(false);
		m_ConfigWind.ShowWindow(true);
		GetCompressioncfg();
		break;
	default:
		break;
	}
	*pResult = 0;
}


void CMonitorDlg::OnBnClickedButtonGet()
{
	// TODO: Add your control notification handler code here
	GetCompressioncfg();


	//hik.struDeviceInfoV40.struDeviceV30.
}

/*************************************************
Function:OnTcnSelchangeTabControl
Description:TabControl�ؼ���ǩҳ�л���Ӧ����
Input:
Output:
Return:
Others:
*************************************************/
void CMonitorDlg::OnBnClickedButtonConfig()
{
	// TODO: Add your control notification handler code here
	m_ConfigWind.UpdateData();


	//CString s;
	//m_ConfigWind.VideoFrameRate.GetWindowTextW(s);

	//m_ConfigWind.VideoFrameRate.GetCurSel();

	NET_DVR_COMPRESSIONCFG_V30 struParams;
	if (hik.GetCompressionParameters(m_struDeviceInfo[m_iCurDevIndex].lLoginID, 1, struParams))
	{
		
		struParams.struNormHighRecordPara.dwVideoFrameRate = m_ConfigWind.VideoFrameRate.GetCurSel();//��Ƶ֡��
		struParams.struNormHighRecordPara.byPicQuality = m_ConfigWind.PicQuality.GetCurSel();//ͼ������
		struParams.struNormHighRecordPara.byStreamType = m_ConfigWind.StreamType.GetCurSel();//��������
		struParams.struNormHighRecordPara.dwVideoBitrate = m_ConfigWind.BitrateType.GetCurSel();//��������

		struParams.struNormHighRecordPara.byResolution = ResolutionCodeMatch(m_ConfigWind.Resolution.GetCurSel());//��������
	}
		
	if (hik.SetCompressionParameters(m_struDeviceInfo[m_iCurDevIndex].lLoginID, 1, struParams))
	{
		CString str = m_ctrlTreeDev.GetItemText(m_ctrlTreeDev.GetSelectedItem());


		m_ConfigWind.UpdateConfieData(struParams.struNormHighRecordPara, str);//�豸��Ϣ����ˢ��

		//m_ConfigWind.UpdateConfieData(struParams.struNormHighRecordPara, str);
	//m_ConfigWind.UpdateData(false);
		AfxMessageBox(_T("OK"));
	}

	
}


/*************************************************
Function:ResolutionCodeMatch
Description:��Ƶ�ֱ��ʲ�������ƥ��
Input:int code	�����б��Ӧ˳��
Output:
Return:temp		��Ƶ�ֱ��ʶ�Ӧ����
Others:
*************************************************/
int CMonitorDlg::ResolutionCodeMatch(int code)
{
	int temp = -1;
	switch (code)
	{
	case 0:temp = 16; break;
	case 1:temp = 3; break;
	case 2:temp = 19; break;
	case 3:temp = 20; break;
	default:
		break;
	}
	return temp;
}


void CMonitorDlg::GetCompressioncfg()
{

	//m_PreviewWind.updatec();
	NET_DVR_COMPRESSIONCFG_V30 struParams;
	//hik.GetCompressionParameters(m_struDeviceInfo[DeviceNum].lLoginID, m_struDeviceInfo[DeviceNum].struChanInfo, struParams);
	if (hik.GetCompressionParameters(m_struDeviceInfo[m_iCurDevIndex].lLoginID, 1, struParams))//��ȡ�豸��Ϣ
	{
		//m_ConfigWind.UpdateConfieData(struParams.struEventRecordPara.byResolution);


		//
		
		//char * ch = m_struDeviceInfo[m_iCurDevIndex].struChanInfo[m_iCurChanIndex].chChanName;


		CString str = m_ctrlTreeDev.GetItemText(m_ctrlTreeDev.GetSelectedItem());//��ȡ�豸����


		m_ConfigWind.UpdateConfieData(struParams.struNormHighRecordPara, str);//�豸��Ϣ����ˢ��

	}



}





void CMonitorDlg::OnBnClickedButtonCloudsUp()
{

}
/*************************************************
Function:OnCurrentWindNumMsg
Description:��ȡ��ǰѡ�еĴ�����Ϣ��Ӧ����
Input:
Output:
Return:
Others:

*************************************************/
LRESULT CMonitorDlg::OnCurrentWindNumMsg(WPARAM wParam, LPARAM)
{

	m_CurrentWindNum = (int)wParam;
	//CString str;
	//str.Format(_T("%d"), m_CurrentWindNum);
	//AfxMessageBox(str);
	return LRESULT();
}

/*************************************************
Function:CombInit
Description:����com�ؼ���ʼ����
Input:
Output:
Return:
Others:

*************************************************/
void CMonitorDlg::CombInit()
{
	m_ComboWindNum.InsertString(-1, _T("1"));
	m_ComboWindNum.InsertString(-1, _T("4"));
	m_ComboWindNum.InsertString(-1, _T("9"));
	m_ComboWindNum.InsertString(-1, _T("16"));
	m_ComboWindNum.InsertString(-1, _T("25"));
	m_ComboWindNum.InsertString(-1, _T("36"));
	m_ComboWindNum.SetCurSel(1);
	CString str;
	m_ComboWindNum.GetWindowTextW(str);
	m_AllWindNum = _ttoi(str);
}

/*************************************************
Function:ShowWindInit
Description:������ʼ����
Input:
Output:
Return:
Others:

*************************************************/
void CMonitorDlg::ShowWindInit()
{
	//�����ര��
	m_PreviewWind.CreateShowWind(TabRect, m_AllWindNum);
	//m_PreviewWind.DrawFrame();
	for (int i = 0; i<m_AllWindNum; i++)
		//m_PlayWnd[i] = m_PreviewWind.m_wndShow[i].m_hWnd;
	m_PlayWnd[i] = m_PreviewWind.m_wind[i].m_hWnd;

}


void CMonitorDlg::OnCbnSelendcancelComboWindNum()
{
	//// TODO: Add your control notification handler code here
}

/*************************************************
Function:OnCbnSelchangeComboWindNum
Description:�ؼ����ݸı���Ӧ
Input:
Output:
Return:
Others:

*************************************************/
void CMonitorDlg::OnCbnSelchangeComboWindNum()
{
	// TODO: Add your control notification handler code here

	CString str;
	//m_ComboWindNum.GetWindowTextW(str);
	m_ComboWindNum.GetLBText(m_ComboWindNum.GetCurSel(), str);//��ȡ��ǰ�ؼ�ֵ
	m_AllWindNum = _ttoi(str);//CStringתΪint
	ShowWindInit();

}



