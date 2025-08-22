
// SnCamDllTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SnCamDllTest.h"
#include "SnCamDllTestDlg.h"

#include "SnCamDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool m_bCaptureBuffer = false;
int iBufferCount = 0;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSnCamDllTestDlg dialog




CSnCamDllTestDlg::CSnCamDllTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSnCamDllTestDlg::IDD, pParent)
	, m_iPropertyAuto(0)
	, m_iControlAuto(0)
	, m_csOut(_T(""))
	, m_iPowerLine(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iPreviewFormat = 0;
	m_iStillFormat = 0;
	m_iProperty = 0;
	m_iControl = 0;
}

void CSnCamDllTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_iPreviewFormat);
	DDX_Text(pDX, IDC_EDIT3, m_iStillFormat);
	DDX_Text(pDX, IDC_EDIT4, m_iProperty);
	DDX_Text(pDX, IDC_EDIT5, m_iControl);
	DDX_Control(pDX, IDC_COMBO2, m_cProperty);
	DDX_Control(pDX, IDC_COMBO1, m_cControl);
	DDX_Check(pDX, IDC_CHECK1, m_iPropertyAuto);
	DDX_Check(pDX, IDC_CHECK2, m_iControlAuto);
	DDX_Text(pDX, IDC_EDIT1, m_csOut);
	DDX_Control(pDX, IDC_EDIT1, m_CEditOUT);
	DDX_Radio(pDX, IDC_RADIO1, m_iPowerLine);
}

BEGIN_MESSAGE_MAP(CSnCamDllTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CSnCamDllTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSnCamDllTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSnCamDllTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CSnCamDllTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CSnCamDllTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CSnCamDllTestDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CSnCamDllTestDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CSnCamDllTestDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CSnCamDllTestDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CSnCamDllTestDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CSnCamDllTestDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CSnCamDllTestDlg::OnBnClickedButton12)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CSnCamDllTestDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSnCamDllTestDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_RADIO1, &CSnCamDllTestDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSnCamDllTestDlg::OnBnClickedRadio2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

int CALLBACK pThread1(BYTE* pData, LONG BufferLength)
{
	TRACE("pThread1 %d\n", BufferLength);
	CString FileName;
	FileName.Format(L"%d.jpg", iBufferCount++);
	if (m_bCaptureBuffer)
	{
		m_bCaptureBuffer = false;
		CFile SaveFile;
		SaveFile.Open(FileName, CFile::modeWrite | CFile::modeCreate, NULL);
		SaveFile.Write(pData, BufferLength);
		SaveFile.Close();
	}
	return 0;
}

// CSnCamDllTestDlg message handlers

BOOL CSnCamDllTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	long iCount;
	int i = GetCameraCount(&iCount);
	char *pVID = NULL, *pPID = NULL, *pDeviceName = NULL;
	i = GetCameraInfo(0, & pVID, &pPID, &pDeviceName);
	CString tempStr;
	tempStr.Format(L"CameraCount: %d \r\n", iCount);
	m_csOut += tempStr;
	UpdateData(FALSE);

	i = CameraInit(0,
		pThread1,
		GetDlgItem(IDC_SHOW)->m_hWnd
		);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSnCamDllTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSnCamDllTestDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSnCamDllTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSnCamDllTestDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	int i = CameraPlay(0);
	if (i != 1)
	{
		i = CameraInit(0,
			pThread1,
			GetDlgItem(IDC_SHOW)->m_hWnd);
		i = CameraPlay(0);
	}
	if (i == 1)
		m_csOut += "Start Preview Success!\r\n";
	else
		m_csOut += "Start Preview Failed!\r\n";
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}

void CSnCamDllTestDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	int i = CameraStop(0);
	i = CameraUnInit(0);
	if (i == 1)
		m_csOut += "Stop Preview Success!\r\n";
	else
		m_csOut += "Stop Preview Failed!\r\n";
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}

void CSnCamDllTestDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	int i = CameraUnInit(0);
	CDialog::OnClose();
}

void CSnCamDllTestDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = CameraSetVideoFormat(0,m_iPreviewFormat);
	if (i == 1)
		m_csOut += "Set Video Format Success!\r\n";
	else
		m_csOut += "Set Video Format Failed!\r\n";
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}

void CSnCamDllTestDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = CameraSetStillFormat(0, m_iStillFormat);
	if (i == 1)
		m_csOut += "Set Still Format Success!\r\n";
	else
		m_csOut += "Set Still Format Failed!\r\n";
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}


void CSnCamDllTestDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	WCHAR FileName[] = { _T("1234.jpg") };
	int i = CameraSnapShot(0, PICTUREFORMAT_JPG, FileName);
	if (i == 1)
		m_csOut += "SnapShot Success!\r\n";
	else
		m_csOut += "SnapShot Failed!\r\n";
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}

void CSnCamDllTestDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	WCHAR FileName[] = {_T("1234.asf")};
	int i = CameraStartCapture(0,VIDEOFORMAT_asf, FileName);
	if (i == 1)
		m_csOut += "Start Capture!\r\n";
	else
		m_csOut += "Start Capture Failed!\r\n";
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}

void CSnCamDllTestDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	int i = CameraStopCapture(0);
	if (i == 1)
		m_csOut += "Stop Capture!\r\n";
	else
		m_csOut += "Stop Capture Failed!\r\n";
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}

void CSnCamDllTestDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	m_bCaptureBuffer = true;
	m_csOut += "Capture Buffer!\r\n";
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}



void CSnCamDllTestDlg::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iIndex = m_cProperty.GetCurSel();
	int temp;
	if (m_iPropertyAuto == 0)
		temp = 2;
	else
		temp = 1;
	int i = CameraPropertySet(0, (DS_CAMERA_PROPERTY)iIndex, m_iProperty, (DS_PROPERTY_FLAGS)temp);
	if (i == 1)
		m_csOut += "Set Property Success!\r\n";
	else
		m_csOut += "Set Property Failed!\r\n";
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}


void CSnCamDllTestDlg::OnBnClickedButton10()
{
	// TODO: Add your control notification handler code here
	long iCount = 0;
	DS_COLORSPACE iColor;
	long lWidth, lHeight = 0;
	CString tempStr;
	int i = GetPreviewResolutionCount(0, &iCount);
	for (int i = 0; i < iCount; i++)
	{
		GetPreviewResolutionInfo(0, i, &iColor, &lWidth, &lHeight);
		tempStr.Format(L"No.%d: Color:%d Solution:%d*%d \r\n", i, iColor, lWidth, lHeight);
		m_csOut += tempStr;
	}
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}

void CSnCamDllTestDlg::OnBnClickedButton11()
{
	// TODO: Add your control notification handler code here
	long iCount = 0;
	DS_COLORSPACE iColor;
	long lWidth, lHeight = 0;
	CString tempStr;
	int i = GetStillResolutionCount(0, &iCount);
	for (int i = 0; i < iCount; i++)
	{
		GetStillResolutionInfo(0, i, &iColor, &lWidth, &lHeight);
		tempStr.Format(L"No.%d: Color:%d Solution:%d*%d \r\n", i, iColor, lWidth, lHeight);
		m_csOut += tempStr;
	}
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}

void CSnCamDllTestDlg::OnBnClickedButton12()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iIndex = m_cControl.GetCurSel();
	int temp;
	if (m_iControlAuto == 0)
		temp = 2;
	else
		temp = 1;
	int i = CameraControlSet(0, (DS_CAMERA_CONTROL)iIndex, m_iControl, (DS_CONTROL_FLAGS)temp);
	if (i == 1)
		m_csOut += "Set Control Success!\r\n";
	else
		m_csOut += "Set Control Failed!\r\n";
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}


void CSnCamDllTestDlg::OnCbnSelchangeCombo2()
{
	// TODO:  在此添加控件通知处理程序代码
	LONG  iMin, iMax, iStep, iDefault, iFlag = 0;
	CString strTemp;
	int iIndex = m_cProperty.GetCurSel();
	int i = CameraPropertyGetRange(0, (DS_CAMERA_PROPERTY)iIndex, &iMin, &iMax, &iStep, &iDefault, (DS_PROPERTY_FLAGS*)&iFlag);
	if (i == 1)
		strTemp.Format(L"Property:%d: Min:%d Max:%d Step:%d Default:%d Flag:%d \r\n", iIndex, iMin, iMax, iStep, iDefault, iFlag);
	else
		m_csOut += "Negative!\r\n";
	i = CameraPropertyGet(0, (DS_CAMERA_PROPERTY)iIndex, (LONG*)&m_iProperty, (DS_PROPERTY_FLAGS*)&m_iPropertyAuto);
	if (2 == m_iPropertyAuto)
		m_iPropertyAuto = 0;
	else
		m_iPropertyAuto = 1;
	m_csOut += strTemp;
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}


void CSnCamDllTestDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	LONG  iMin, iMax, iStep, iDefault, iFlag = 0;
	CString strTemp;
	int iIndex = m_cControl.GetCurSel();
	int i = CameraControlGetRange(0, (DS_CAMERA_CONTROL)iIndex, &iMin, &iMax, &iStep, &iDefault, (DS_CONTROL_FLAGS*)&iFlag);
	if (i == 1)
		strTemp.Format(L"Control:%d: Min:%d Max:%d Step:%d Default:%d Flag:%d \r\n", iIndex, iMin, iMax, iStep, iDefault, iFlag);
	else
		m_csOut += "Negative!\r\n";
	i = CameraControlGet(0, (DS_CAMERA_CONTROL)iIndex, (LONG*)&m_iControl, (DS_CONTROL_FLAGS*)&m_iControlAuto);
	if (2 == m_iControlAuto)
		m_iControlAuto = 0;
	else
		m_iControlAuto = 1;
	m_csOut += strTemp;
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}


void CSnCamDllTestDlg::OnBnClickedRadio1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int i;
	i = CameraSetPowerLine(0, (DS_POWER_LINE)(m_iPowerLine + 1));
	if (i == 1)
		m_csOut += "Set PowerLine Success!\r\n";
	else
		m_csOut += "Set PowerLine Failed!\r\n";
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}


void CSnCamDllTestDlg::OnBnClickedRadio2()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int i;
	i = CameraSetPowerLine(0, (DS_POWER_LINE)(m_iPowerLine + 1));
	if (i == 1)
		m_csOut += "Set PowerLine Success!\r\n";
	else
		m_csOut += "Set PowerLine Failed!\r\n";
	UpdateData(FALSE);
	m_CEditOUT.LineScroll(m_CEditOUT.GetLineCount());
}
