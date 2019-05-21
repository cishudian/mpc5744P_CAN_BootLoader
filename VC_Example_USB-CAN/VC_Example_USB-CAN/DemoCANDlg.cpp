// DemoCANDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DemoCAN.h"
#include "DemoCANDlg.h"
#include "ControlCAN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CString sFile;
unsigned long nextrow;
int StopFlag=0;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoCANDlg dialog

CDemoCANDlg::CDemoCANDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoCANDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoCANDlg)
	m_nSendFrameFormat = 0;
	m_nSendFrameType = 0;
	m_strSendData = _T("11 22 33 44 55 66 77 88");
	m_strSendID = _T("00 00 00 64");
	m_radioIDFormat = 1;
	m_bCanRxEn = FALSE;
	m_nCanIndex = 0;
	m_nBaudRateIdx = 6;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hSemaphore = NULL;
	m_bDeviceOpen = FALSE;
}

void CDemoCANDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoCANDlg)
	DDX_Control(pDX, IDC_SENDPROGRESS, m_progressBar);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_CBIndex(pDX, IDC_COMBO_SENDFRAMEFORMAT, m_nSendFrameFormat);
	DDX_CBIndex(pDX, IDC_COMBO_SENDFRAMETYPE, m_nSendFrameType);
	DDX_Text(pDX, IDC_EDIT_SEND_DATA, m_strSendData);
	DDX_Text(pDX, IDC_EDIT_SEND_ID, m_strSendID);
	DDX_Radio(pDX, IDC_RADIO_ID_FORMAT, m_radioIDFormat);
	DDX_Check(pDX, IDC_CHECK_CANRX_EN, m_bCanRxEn);
	DDX_CBIndex(pDX, IDC_COMBO_CAN_INDEX, m_nCanIndex);
	DDX_CBIndex(pDX, IDC_COMBO_BAUDRATE, m_nBaudRateIdx);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoCANDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoCANDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN_DEVICE, OnButtonOpenDevice)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_CHECK_CANRX_EN, OnCheckCanrxEn)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_DEVICE, OnButtonCloseDevice)
	ON_BN_CLICKED(IDC_BUTTON_SENDFILE, OnButtonSendfile)
	ON_BN_CLICKED(IDC_BUTTON_SENDCANCEL, OnButtonSendCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoCANDlg message handlers

BOOL CDemoCANDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
    //信息显示列表初始化
	m_list.InsertColumn(0,"Seq");
	m_list.SetColumnWidth(0,40);
	m_list.InsertColumn(1,"Time");
	m_list.SetColumnWidth(1,85);
	m_list.InsertColumn(2,"CANIndex");
	m_list.SetColumnWidth(2,60);
	m_list.InsertColumn(3,"Tx-Rx");
	m_list.SetColumnWidth(3,60);
	m_list.InsertColumn(4," ID ");
	m_list.SetColumnWidth(4,60);
	m_list.InsertColumn(5,"Frame");
	m_list.SetColumnWidth(5,50);
	m_list.InsertColumn(6,"Type");
	m_list.SetColumnWidth(6,70);
	m_list.InsertColumn(7,"DLC");
	m_list.SetColumnWidth(7,30);
	m_list.InsertColumn(8,"Data");
	m_list.SetColumnWidth(8,160);
	//信息显示列表初始化完毕

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoCANDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoCANDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoCANDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//一位十六进制转换为十进制
int HexChar(char c)
{
	if((c>='0') && (c<='9'))
		return c-0x30;
	else if((c>='A') && (c<='F'))
		return c-'A'+10;
	else if((c>='a') && (c<='f'))
		return c-'a'+10;
	else
		return 0x10;
}
//两位十六进制数转换为十进制
int Str2Hex(CString str)
{	
	int len = str.GetLength();
	if(len == 2)
	{
		int a= HexChar(str[0]);
		int b =HexChar(str[1]);
		if(a==16 || b==16 )
		{
			AfxMessageBox("Format error");
			return 256;
		}
		else
		{
			return a*16+b;
			
		}
		
	}
	else
	{
		AfxMessageBox("input length must be 2");
		return 256;
	}
}

BYTE timing0_tab[15] = {0xBF,0x31,0x18,0x87,0x09,0x83,0x04,0x03,0x81,
					  0x01,0x80,0x00,0x80,0x00,0x00}; 
BYTE timing1_tab[15] = {0xFF,0x1C,0x1C,0xFF,0x1C,0xFF,0x1C,0x1C,0xFA,
					  0x1C,0xFA,0x1C,0xB6,0x16,0x14}; 

//打开设备
void CDemoCANDlg::OnButtonOpenDevice() 
{

	UpdateData(TRUE);
	m_DevIndex=0;	
	m_DevType=DEV_USBCAN;
	DWORD Reserved=0;
	//打开设备
	if(VCI_OpenDevice(m_DevType,m_DevIndex,Reserved)!=1)
	{
		MessageBox("open failed");
		return;
	}
	VCI_INIT_CONFIG InitInfo[1];
	InitInfo->kCanBaud=m_nBaudRateIdx+1;
	InitInfo->Timing0=timing0_tab[m_nBaudRateIdx];
	InitInfo->Timing1=timing1_tab[m_nBaudRateIdx];
	InitInfo->Filter=0;
	InitInfo->AccCode=0x80000008;
	InitInfo->AccMask=0xFFFFFFFF;
	InitInfo->Mode=0;
	InitInfo->CanRx_IER=1;
    //初始化通道0
	if(VCI_InitCAN(m_DevType,m_DevIndex, 0,InitInfo)!=1)	//can-0
	{
		MessageBox("Init-CAN failed!");
		return;
	}
	Sleep(100);
    //初始化通道1
	if(VCI_StartCAN(m_DevType,m_DevIndex, 0)!=1)	//can-0
	{
		MessageBox("Start-CAN failed!");
		return;
	}

	m_bDeviceOpen = TRUE;
	MessageBox("Open successfule!\n Start CAN OK!");	

}
//关闭设备
void CDemoCANDlg::OnButtonCloseDevice() 
{
	if(VCI_CloseDevice(m_DevType,m_DevIndex)!=1)
	{
		MessageBox("Close failed！");
		return;
	}
	m_bDeviceOpen = FALSE;
	MessageBox("Close successful!");		
}
//发送信息
void CDemoCANDlg::OnButtonSend() 
{
   //从界面获取发送信息
	VCI_CAN_OBJ sendbuf[1];

	UpdateData(TRUE);
	CString str5[32];
	BYTE buf[50];
	BYTE SendID[10];
	CString strtemp,strtemp1;
	CString str1;
	int len,datanum=0,IDnum=0,newflag=1;

	len=m_strSendID.GetLength();	//from dialog
	for(int i=0; i<len;i++)
	{
		strtemp=m_strSendID.GetAt(i);
		if(strtemp==" ")
			newflag=1;
		else if(newflag==1)
		{
			newflag=0;
			strtemp=m_strSendID.GetAt(i);
			if(i==(len-1))
			{
				str5[IDnum]="0"+strtemp;

			}
			else
			{
				strtemp1=m_strSendID.GetAt(i+1);

				if(strtemp1 == " ")
					str5[IDnum]="0"+strtemp;
				else
					str5[IDnum]=strtemp+strtemp1;
			}

			SendID[IDnum]=Str2Hex(str5[IDnum]);
			IDnum++;
			if(IDnum>=4)	
				break;

		}

	}

	newflag=1;
	len=m_strSendData.GetLength();
	
	//test
	//for(i=0; i<len;i++)
	//	buf[i] = m_strSendData[i];
	//datanum = len;
	for(i=0; i<len;i++)
	{
		
		strtemp=m_strSendData.GetAt(i);
		if(strtemp==" ")
			newflag=1;
		else if(newflag==1)
		{	

			newflag=0;
			strtemp=m_strSendData.GetAt(i);		
			if(i==(len-1))
			{
				str5[datanum]="0"+strtemp;

			}
			else
			{
				strtemp1=m_strSendData.GetAt(i+1);

				if(strtemp1 == " ")
				{
					str5[datanum]="0"+strtemp;
				
				}
				else
					str5[datanum]=strtemp+strtemp1;
			
			}
			buf[datanum]=Str2Hex(str5[datanum]);
			datanum++;
			if(datanum>=8)
				break;
		}
	}
	sendbuf->ExternFlag=m_nSendFrameType;
	sendbuf->DataLen=datanum;
	sendbuf->RemoteFlag=m_nSendFrameFormat;
	if(m_nSendFrameFormat==1)//if remote frame, data area is invalid
		for(i=0;i<datanum;i++)
			buf[i]=0;
	BYTE SendID2[4];
	
	if((sendbuf->ExternFlag)==1)//
	{
		if(m_radioIDFormat)//direcet id to SJA1000 format
		{
			SendID[0] &= 0x1F;
			SendID2[0]=(SendID[0]<<3)|(SendID[1]>>5);
			SendID2[1]=(SendID[1]<<3)|(SendID[2]>>5);
			SendID2[2]=(SendID[2]<<3)|(SendID[3]>>5);
			SendID2[3]=(SendID[3]<<3);
			for(i=0;i<4;i++)
				sendbuf->ID[i]=SendID2[i];
		}
		else
		{
			SendID[3]=SendID[3] & 0xF8;//the last 3bit is invalid, clear to 0
			for(i=0;i<4;i++)
				sendbuf->ID[i]=SendID[i];
		}
	}
	else//basic frame ID
	{

		if(m_radioIDFormat)//
		{
			SendID[2] &= 0x07; 
			SendID2[0]=(SendID[2]<<5)|(SendID[3]>>3);
			SendID2[1]=SendID[3]<<5;
			for(i=0;i<2;i++)
				sendbuf->ID[i]=SendID2[i];
		}
		else
		{
			SendID[1]=SendID[1] & 0xE0;//the lower 5 bits is invalid,clear to 0
			for(i=0;i<2;i++)
				sendbuf->ID[i]=SendID[i];
		}
	}

	for(i=0;i<datanum;i++)
		sendbuf->Data[i]=buf[i];
/****************************************************************************/	
/******************************从界面获取发送信息完毕***********************/
/****************************************************************************/
	int flag;

	if((m_nCanIndex==1)&&(m_DevType!=DEV_USBCAN200))
	{
		MessageBox("the device only support CAN index 0");
		m_nCanIndex=0;
	}
    //调用动态链接库发送函数
	flag=VCI_Transmit(m_DevType,m_DevIndex,m_nCanIndex,sendbuf);//CAN message send
	if(flag<1)
	{
		//VCI_ERR_INFO info;
		//VCI_CAN_STATUS status;
		//VCI_ReadErrInfo(m_DevType,m_DevIndex,m_nCanIndex,&info);
		//VCI_ReadCANStatus(m_DevType,m_DevIndex,m_nCanIndex,&status);
		if(flag==-1)
			MessageBox("failed- device not open\n");
		else if(flag==0)
			MessageBox("send error\n");

		return;
	}

	CSize size;
	unsigned int JustnowItem;
	BYTE data;
    
    //发送信息列表显示
	CString strTime;
	SYSTEMTIME   systime;   
	GetLocalTime(&systime);   
	strTime.Format("%02d:%02d:%02d:%03d", systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds);   

	
	size.cx=0;
	size.cy=50;
	CString str;
	str.Format("%d",nextrow);
	m_list.ItemColorFlag[nextrow]=1;
	JustnowItem=m_list.InsertItem(nextrow,str);	

	nextrow++;	
	m_list.SetItemText(JustnowItem,1,strTime);		
	str.Format("%d",m_nCanIndex);	
	m_list.SetItemText(JustnowItem,2,str);		
	m_list.SetItemText(JustnowItem,3,"Send");		
	str="";

	if((sendbuf->RemoteFlag)==1)
	{
		m_list.SetItemText(JustnowItem,5,"Remote");	
	}
	else
	{
		m_list.SetItemText(JustnowItem,5,"Data");	
	
	}
	if((sendbuf->ExternFlag)==1)			
	{
			for(i=0;i<4;i++)
			{
				data=SendID[i];
				str1.Format("%02X",data);
				str+=str1;
			}
			m_list.SetItemText(JustnowItem,4,str);			
			m_list.SetItemText(JustnowItem,6,"Extended");		//	
	
	}
	else									
	{
			for(i=0;i<2;i++)
			{			
				if(m_radioIDFormat)//direct id to sja1000 format
					data=SendID[i+2];
				else
					data=SendID[i];
				str1.Format("%02X",data);
				str+=str1;
			}
			m_list.SetItemText(JustnowItem,4,str);		
		
			m_list.SetItemText(JustnowItem,6,"Standard");		//
		
		
	}
	str.Format("%d",sendbuf->DataLen);	
	m_list.SetItemText(JustnowItem,7,str);	
	
	str="";
	for(i=0;i<sendbuf->DataLen;i++)		
	{
		data=sendbuf->Data[i];
		str1.Format("%02X",data);
		str+=str1+" ";
	}
	m_list.SetItemText(JustnowItem,8,str);	
	m_list.Scroll(size); 
	//发送信息列表显示完毕
		
}


UINT CDemoCANDlg::ReceiveThread(LPVOID v)
{
	CDemoCANDlg *dlg=(CDemoCANDlg*) AfxGetApp()->GetMainWnd();	
	int k=0;
	while(1)
	{
		int NumValue;
		int i;
		VCI_CAN_OBJ pCanObj[200];

		CString strbuf[200],str1;
		int num=0;

		CSize size;
		unsigned int JustnowItem;
		BYTE ReceivedID[4];

		size.cx=0;
		size.cy=50;
		CString str;
		int Len=0;

        //调用动态链接看接收函数
		NumValue=VCI_Receive(dlg->m_DevType,dlg->m_DevIndex,0,pCanObj);
        //接收信息列表显示
		k++;
		CString strTime;
		SYSTEMTIME   systime;   
		GetLocalTime(&systime);   
		strTime.Format("%02d:%02d:%02d:%03d", systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds);   

		for(num=0;num<NumValue;num++)
		{
			if(nextrow==59999)
			{
					dlg->m_list.DeleteAllItems();
					nextrow=0;
			}


			dlg->m_list.ItemColorFlag[nextrow]=0;

			str.Format("%d",nextrow);
			JustnowItem=dlg->m_list.InsertItem(nextrow,str);	
			nextrow++;	
			
			dlg->m_list.SetItemText(JustnowItem,1,strTime);	
			
		//	str.Format("%d",nCanIndex);
			dlg->m_list.SetItemText(JustnowItem,2,"0");	
			
			dlg->m_list.SetItemText(JustnowItem,3,"Receive");	
			str="";

			if((pCanObj[num].RemoteFlag)==1)
			{
				dlg->m_list.SetItemText(JustnowItem,5,"Remote");	
			}
			else
			{
				dlg->m_list.SetItemText(JustnowItem,5,"Data");	
			
			}
			if((pCanObj[num].ExternFlag)==1)		
			{
				for(i=0;i<4;i++)
					ReceivedID[i]=pCanObj[num].ID[i];
				if(dlg->m_radioIDFormat)//from sja1000 format to direct id
				{

						ReceivedID[3]=(ReceivedID[2]<<5)|(ReceivedID[3]>>3);
						ReceivedID[2]=(ReceivedID[1]<<5)|(ReceivedID[2]>>3);
						ReceivedID[1]=(ReceivedID[0]<<5)|(ReceivedID[1]>>3);
						ReceivedID[0]=ReceivedID[0]>>3;
				}
				for(i=0;i<4;i++)
				{
						str1.Format("%02X",ReceivedID[i]);
						str+=str1;
				}
				dlg->m_list.SetItemText(JustnowItem,4,str);	//ID信息	
						
				dlg->m_list.SetItemText(JustnowItem,6,"Extended");		//	
					
			}
			else									//标准帧
			{
				for(i=0;i<2;i++)
						ReceivedID[i]=pCanObj[num].ID[i];
				if(dlg->m_radioIDFormat)//将CAN2.0B格式进行转换到直接ID值
				{

						ReceivedID[1]=(ReceivedID[1]>>5)|(ReceivedID[0]<<3);
						ReceivedID[0]=ReceivedID[0]>>5;
				}
				for(i=0;i<2;i++)
				{
					str1.Format("%02X",ReceivedID[i]);
					str+=str1;
				}
				dlg->m_list.SetItemText(JustnowItem,4,str);	//ID信息	
						
				dlg->m_list.SetItemText(JustnowItem,6,"Standard");		//
						
						
			}
			str.Format("%d",pCanObj[num].DataLen);	//长度信息
			dlg->m_list.SetItemText(JustnowItem,7,str);	
					
			str="";
			for(i=0;i<(pCanObj[num].DataLen);i++)			//数据信息
			{
						str1.Format("%02X ",pCanObj[num].Data[i]);
						str+=str1;
					
			}

			dlg->m_list.SetItemText(JustnowItem,8,str);	
			dlg->m_list.Scroll(size); 	
			 //接收信息列表显示完毕

      
		}
		Sleep(10);	


		if(StopFlag==1)
			return 0;	
	}

	return 1;
}

void CDemoCANDlg::OnCheckCanrxEn() 
{
	UpdateData(TRUE);
	if(m_bCanRxEn)
	{
		StopFlag=0;
		//开启接收线程
		AfxBeginThread(ReceiveThread,0);	
	}
	else
		StopFlag=1;

}
//清空信息显示列表
void CDemoCANDlg::OnButtonClear() 
{
	m_list.DeleteAllItems();	
}

/////////////////////////////////////////////////////////////////////////////

/****************************** CODE FOR CAN COMMUNICATION *************************************/
/* Values in ASCII table should be avoided 0~9, a~f, A~F, s, S                                 */
/* 0~9: 0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39                                      */
/* a~f: 0x61,0x62,0x63,0x64,0x65,0x66                                                          */
/* A~F: 0x41,0x42,0x43,0x44,0x45,0x46                                                          */
/* s:   0x73                                                                                   */
/* S:   0x53                                                                                   */
/***********************************************************************************************/

/******************* info code from host -> ECU ************************************************/
#define  DOWN_LINK                0xFF  
#define  DOWN_LINE_END            0xFE
#define  DOWN_FILE_END            0xFD

/******************* acknowledging from ECU -> HOST in first CAN byte **************************/
#define  UP_READY                 0xC3
#define  UP_BUSY                  0xC2
#define  UP_PRGEND                0xC1
#define  UP_ERR                   0x00                      

#define  STATUS_NOT_LINKED        0x00  
#define  STATUS_WAIT_READY        0x01
#define  STATUS_DOWNLOADING       0x02 
#define  STATUS_DOWNLOAD_END      0x03

unsigned char STATUS = STATUS_NOT_LINKED;  // indicates the overall states of downloading

BOOL CDemoCANDlg::SendDataAndDisplay(BYTE *dataPtr, int dataLen)
{
	int i;
	m_sendbuf->DataLen = dataLen;
	for (i = 0; i < dataLen; i++)
		m_sendbuf->Data[i] = dataPtr[i];

#if 1
	CSize size;
	unsigned int JustnowItem;
	BYTE data;
    CString str1;
    //发送信息列表显示
	CString strTime;
	SYSTEMTIME   systime;   
	GetLocalTime(&systime);   
	strTime.Format("%02d:%02d:%02d:%03d", systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds);   
	
	size.cx=0;
	size.cy=50;
	CString str;
	str.Format("%d",nextrow);
	m_list.ItemColorFlag[nextrow]=1;
	JustnowItem=m_list.InsertItem(nextrow,str);	

	nextrow++;	
	m_list.SetItemText(JustnowItem,1,strTime);		
	str.Format("%d",m_nCanIndex);	
	m_list.SetItemText(JustnowItem,2,str);		
	m_list.SetItemText(JustnowItem,3,"Send");		
	str="";

	m_list.SetItemText(JustnowItem,5,"Data");	

	for(i=0;i<2;i++)
	{			
		if(m_radioIDFormat)//direct id to sja1000 format
			data=m_SendID[i+2];
		else
			data=m_SendID[i];
		str1.Format("%02X",data);
		str+=str1;
	}
	
	m_list.SetItemText(JustnowItem,4,str);		
	m_list.SetItemText(JustnowItem,6,"Standard");		//
	
	str.Format("%d",m_sendbuf->DataLen);	
	m_list.SetItemText(JustnowItem,7,str);	
	
	str="";
	for(i=0;i<m_sendbuf->DataLen;i++)		
	{
		data=m_sendbuf->Data[i];
		str1.Format("%02X",data);
		//str1=data;
		str+=str1+" ";
	
	}
	m_list.SetItemText(JustnowItem,8,str);	
	m_list.Scroll(size);
#if 0
	m_testFile.WriteString(str+"\n");
#endif
	//发送信息列表显示完毕
#endif

	if (VCI_Transmit(m_DevType, m_DevIndex, m_nCanIndex, m_sendbuf) < 1)
		return TRUE; // send error

	return FALSE;
}		

void CDemoCANDlg::OnSendFileEnd(BOOL bErr)
{
	m_s19File.Close();
#if 0
	m_testFile.Close();
#endif	
	CloseHandle(m_hSemaphore);
	m_bSendFileErr = bErr;
	if (bErr)
		MessageBox("sending failed\n");
	else {
		if (m_cancelSend == FALSE) 
			MessageBox("sending succeeded!\n");
	}
	m_progressBar.SetPos(0);
	SetCursor(::LoadCursor(NULL,IDC_ARROW));
}

//static int t2 = 0;

UINT CDemoCANDlg::SendFileSendThread(void *param)
{
	CDemoCANDlg *dlg=(CDemoCANDlg*) AfxGetApp()->GetMainWnd();	
	BYTE frame_no, tail;
	BYTE line_len;        // inidcates the current line length (ASCII code)
	CString str;
	int i,j;
	BOOL bEnd = FALSE;
	BOOL bEof = FALSE;
	BOOL bErr = FALSE;
	BOOL bSendEnd = FALSE;
	BYTE Data[8];
	int DataLen;
	int line_no = 0;

	while(!bEnd && !bErr && !dlg->m_cancelSend) {
		switch (STATUS) {
			case STATUS_NOT_LINKED:
				DataLen = 1;
				Data[0] = DOWN_LINK; //ask for download_link 
				dlg->SendDataAndDisplay(Data,DataLen);
				//line_no = dlg->m_progressBar.GetPos();
				//if (line_no == 100)
				//	increment = -1;
				//if (line_no == 0)
				//	increment = 1;
				//dlg->m_progressBar.SetPos(line_no+increment);

				Sleep(50);
				break;
			case STATUS_DOWNLOADING:
				if (bSendEnd)
					Sleep(10);
				if (bEof && bSendEnd == FALSE) {
					DataLen = 1;
					Data[0] = DOWN_FILE_END; 
					WaitForSingleObject(dlg->m_hSemaphore, INFINITE); 
					bErr = dlg->SendDataAndDisplay(Data,DataLen); 
					//t2 ++;
					bSendEnd = TRUE;
					break;
				}
				if (dlg->m_s19File.ReadString(str) == NULL) { 
					bEof = TRUE;
					break;
				}
				// send a line of S-Record here
				line_len = str.GetLength();
				frame_no = line_len/8; //the length of first frame_no of CAN frames should be 8
				tail = line_len%8;     //the CAN length of last frame within a line
						
				for (i = 0; i < frame_no; i++) {            
					DataLen = 8;
					for (j = 0; j < 8; j++)
						Data[j] = str[i*8+j];  
					WaitForSingleObject(dlg->m_hSemaphore, INFINITE); 
					bErr = dlg->SendDataAndDisplay(Data,DataLen);
					//t2 ++;
				}
				DataLen = tail;
				for (j = 0; j < tail; j++)
					Data[j] = str[i*8+j];  
				WaitForSingleObject(dlg->m_hSemaphore, INFINITE); 
				bErr = dlg->SendDataAndDisplay(Data,DataLen);
				//t2 ++;

				DataLen = 1;
				Data[0] = DOWN_LINE_END;
				WaitForSingleObject(dlg->m_hSemaphore, INFINITE); 
				bErr = dlg->SendDataAndDisplay(Data,DataLen);
				//t2 ++;

				line_no ++;
				dlg->m_progressBar.SetPos(line_no);
				break;

			case STATUS_DOWNLOAD_END:
				bEnd = TRUE;
				break;
			case STATUS_WAIT_READY:
				//Sleep(5);
			default:
				break;    
		}
	}
	dlg->OnSendFileEnd(bErr);

	return 1;
}

//static int t1 = 0;
//static int t3 = 0;
UINT CDemoCANDlg::SendFileReceiveThread(void *param)
{
	CDemoCANDlg *dlg=(CDemoCANDlg*) AfxGetApp()->GetMainWnd();	
	int k=0;
	BOOL bEnd = FALSE;

	while(!bEnd && !dlg->m_bSendFileErr && !dlg->m_cancelSend)
	{
		int NumValue;
		int i;
		VCI_CAN_OBJ pCanObj[200];

		CString strbuf[200],str1;
		int num=0;

		CSize size;
		unsigned int JustnowItem;
		BYTE ReceivedID[4];

		size.cx=0;
		size.cy=50;
		CString str;
		int Len=0;

        //调用动态链接看接收函数
		NumValue=VCI_Receive(dlg->m_DevType,dlg->m_DevIndex,0,pCanObj);

		if (NumValue <= 0)
		{
			Sleep(10);
			continue;
		}
	
		switch (pCanObj[NumValue-1].Data[0]) {
			case UP_READY:
				STATUS = STATUS_DOWNLOADING;
				ReleaseSemaphore(dlg->m_hSemaphore, 1, 0); // release the semaphore. increase count by 1
				//t1 ++;
				break;
			case UP_BUSY:
				STATUS = STATUS_WAIT_READY;
				//t3 ++;
				break;
			case UP_PRGEND:
				STATUS = STATUS_DOWNLOAD_END;
				bEnd = TRUE;
				break;
			case UP_ERR:
				STATUS = STATUS_NOT_LINKED;
				break;
			default:
				break;
		}
#if 1	
		//接收信息列表显示
		k++;
		CString strTime;
		SYSTEMTIME   systime;   
		GetLocalTime(&systime);   
		strTime.Format("%02d:%02d:%02d:%03d", systime.wHour,systime.wMinute,systime.wSecond,systime.wMilliseconds);   

		for(num=NumValue-1;num<NumValue;num++)
		{
			if(nextrow==59999)
			{
				dlg->m_list.DeleteAllItems();
				nextrow=0;
			}
			dlg->m_list.ItemColorFlag[nextrow]=0;

			str.Format("%d",nextrow);
			JustnowItem=dlg->m_list.InsertItem(nextrow,str);	
			nextrow++;	
			
			dlg->m_list.SetItemText(JustnowItem,1,strTime);	
			
			dlg->m_list.SetItemText(JustnowItem,2,"0");	
			
			dlg->m_list.SetItemText(JustnowItem,3,"Receive");	
			str="";

			dlg->m_list.SetItemText(JustnowItem,5,"Data");	
			
		
			//标准帧
			for(i=0;i<2;i++)
				ReceivedID[i]=pCanObj[num].ID[i];
			if(dlg->m_radioIDFormat)//将CAN2.0B格式进行转换到直接ID值
			{
				ReceivedID[1]=(ReceivedID[1]>>5)|(ReceivedID[0]<<3);
				ReceivedID[0]=ReceivedID[0]>>5;
			}
			for(i=0;i<2;i++)
			{
				str1.Format("%02X",ReceivedID[i]);
				str+=str1;
			}
			dlg->m_list.SetItemText(JustnowItem,4,str);	//ID信息	
						
			dlg->m_list.SetItemText(JustnowItem,6,"Standard");		//
		
			str.Format("%d",pCanObj[num].DataLen);	//长度信息
			dlg->m_list.SetItemText(JustnowItem,7,str);	
					
			str="";
			for(i=0;i<(pCanObj[num].DataLen);i++)			//数据信息
			{
				str1.Format("%02X ",pCanObj[num].Data[i]);
				str+=str1;
			}

			dlg->m_list.SetItemText(JustnowItem,8,str);	
			dlg->m_list.Scroll(size); 	
			 //接收信息列表显示完毕
		}
#endif	
		Sleep(5);	
		//if(StopFlag==1)
		//	return 0;	
	}

	return 1;
}

void CDemoCANDlg::OnButtonSendfile() 
{
	// TODO: Add your control notification handler code here
	if (m_bDeviceOpen == FALSE)
	{
		MessageBox("device not open!\n");
		return;
	}
	
	//if (m_cancelSend == TRUE; 

	CFileDialog  FileDlg(TRUE,"*.s19",NULL,OFN_HIDEREADONLY,"S-Record files(*.s19)|*.s19|");   
    
	FileDlg.m_ofn.lpstrInitialDir="D:\\s-record";   

	if(FileDlg.DoModal()==IDOK)   
	{   
		CFileException fileException;

		if ( !m_s19File.Open( FileDlg.GetPathName(), CFile::typeText |   
             CFile::modeRead, &fileException ) )
		{
			TRACE( "Can't open file %s, error = %u\n",
				FileDlg.GetPathName(), fileException.m_cause );
			return;
		}

		CString str5[32];
		CString strtemp,strtemp1;
		int i,len,datanum=0,IDnum=0,newflag=1;
		BYTE SendID2[4];
	
		len = m_strSendID.GetLength();	//from dialog
		for(i = 0; i < len; i++)
		{
			strtemp = m_strSendID.GetAt(i);
			if(strtemp == " ")
				newflag = 1;
			else if(newflag == 1)
			{
				newflag = 0;
				strtemp = m_strSendID.GetAt(i);
				if(i == (len-1))
				{
					str5[IDnum] = "0" + strtemp;
				}
				else
				{
					strtemp1 = m_strSendID.GetAt(i+1);
					if(strtemp1 == " ")
						str5[IDnum] = "0"+strtemp;
					else
						str5[IDnum] = strtemp+strtemp1;
				}
				m_SendID[IDnum] = Str2Hex(str5[IDnum]);
				IDnum++;
				if(IDnum >= 4)	
					break;
			}
		}

		m_SendID[2] &= 0x07; 
		SendID2[0] = (m_SendID[2]<<5)|(m_SendID[3]>>3);
		SendID2[1] = m_SendID[3]<<5;

		m_sendbuf->ExternFlag = 0;
		m_sendbuf->RemoteFlag = 0;
		for(i = 0; i < 2; i++)
			m_sendbuf->ID[i] = SendID2[i];

		m_cancelSend = FALSE;
		
		CString str;
		m_linesInFile = 0;
		while(m_s19File.ReadString(str))
			m_linesInFile++;
		m_s19File.Seek(0, CFile::begin);
		m_progressBar.SetRange(0,m_linesInFile);
		m_progressBar.SetPos(0);
		m_progressBar.SetStep(1);
		/*
		 * Create the semaphore with desired concurrency.
		 * for the CreateSemaphore function the arguments are respectively:
		 *    0     - security attributes
		 *    semaphore_count  -initial count
		 *    semaphore_count - max count	
		 *    0     - name, if named semaphore
		 */
		m_hSemaphore = CreateSemaphore(0, 0, 1, 0);
		///StopFlag=0;
		STATUS = STATUS_NOT_LINKED;
		m_bSendFileErr = FALSE;
		AfxBeginThread(SendFileSendThread,0);
		AfxBeginThread(SendFileReceiveThread,0);
#if 0
		m_testFile.Open( "c:\\test.txt", CFile::modeCreate |   
             CFile::modeWrite, &fileException );
#endif
		SetCursor(::LoadCursor(NULL,IDC_WAIT));
	}
}

void CDemoCANDlg::OnButtonSendCancel() 
{
	// TODO: Add your control notification handler code here
	m_cancelSend = TRUE;
}
