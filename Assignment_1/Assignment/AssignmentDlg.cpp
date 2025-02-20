
// AssignmentDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Assignment.h"
#include "AssignmentDlg.h"
#include "afxdialogex.h"
#include "DlgImage.h"
#include "CProcess.h"
#include <iostream>
#include <thread>
#define WHITE_COLOR 0xff
#define BLACK_COLOR 0x00

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
//CPoint CAssignmentDlg::prePoint;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CAssignmentDlg 대화 상자



CAssignmentDlg::CAssignmentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ASSIGNMENT_DIALOG, pParent)
	, m_nRadius(0)
	, m_nBorder(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAssignmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_nRadius);
	DDX_Text(pDX, IDC_EDIT_BORDER, m_nBorder);
}

BEGIN_MESSAGE_MAP(CAssignmentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RADIUS, &CAssignmentDlg::OnBnClickedBtnRadius)
	ON_BN_CLICKED(IDC_BTN_BORDER, &CAssignmentDlg::OnBnClickedBtnBorder)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_RANDOM, &CAssignmentDlg::OnBnClickedBtnRandom)
	ON_BN_CLICKED(IDC_BTN_RESET, &CAssignmentDlg::OnBnClickedBtnReset)
	ON_MESSAGE(WM_UPDATE_POINT_PRINT, &CAssignmentDlg::OnUpdatePointPrint)
END_MESSAGE_MAP()


// CAssignmentDlg 메시지 처리기

BOOL CAssignmentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_pDlgImage = new CDlgImage(this);
	m_pDlgImage->Create(IDD_DLGIMAGE, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, 640, 510);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CAssignmentDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAssignmentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC pDC(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(pDC.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		pDC.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAssignmentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAssignmentDlg::OnBnClickedBtnRadius()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}

void CAssignmentDlg::OnBnClickedBtnBorder()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
}

void threadProcess(CWnd* pParent, CRect rect, int nPitch, int num, int delay)
{
	CAssignmentDlg* pWnd = (CAssignmentDlg*)pParent;
	pWnd->Process(rect, nPitch, num, delay);
}

void CAssignmentDlg::OnBnClickedBtnRandom()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_pDlgImage->m_clkPoint.size() == 3) {
		CRect rect(0, 0, m_pDlgImage->m_image.GetWidth(), m_pDlgImage->m_image.GetHeight());

		int nPitch = m_pDlgImage->m_image.GetPitch();
		thread _thread0(threadProcess, this, rect, nPitch, 10, 500);

		_thread0.join();
	}
}

void CAssignmentDlg::Process(CRect rect, int nPitch, int num, int delay)
{
	CClientDC dc(this);
	CProcess process;
	CPoint pt(0, 0);
	int cnt = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pt = CPoint(rand() % 640, rand() % 480);
			process.drawRandomCircle(m_pDlgImage->m_image, m_pDlgImage->m_clkPoint[j].x, m_pDlgImage->m_clkPoint[j].y, m_nRadius, WHITE_COLOR);
			m_pDlgImage->m_clkPoint[j] = pt;
			process.drawRandomCircle(m_pDlgImage->m_image, m_pDlgImage->m_clkPoint[j].x, m_pDlgImage->m_clkPoint[j].y, m_nRadius, BLACK_COLOR);
		}
		m_pDlgImage->pointPrint(m_pDlgImage->m_clkPoint, m_pDlgImage->dragState);
		m_pDlgImage->m_image.Draw(dc, 0, 0);
		process.drawCircle(&dc, m_pDlgImage->m_clkPoint, m_pDlgImage->m_image, m_nBorder);
		Sleep(delay);
	}
}

LRESULT CAssignmentDlg::OnUpdatePointPrint(WPARAM wParam, LPARAM lParam)
{
	// wParam는 CDlgImage의 포인터로 전달됩니다.
	CDlgImage* pDlgImage = (CDlgImage*)wParam;
	if (pDlgImage)
	{
		// UI 스레드에서 UpdateData(FALSE)를 호출하여 Edit Control들을 갱신합니다.
		pDlgImage->UpdateData(FALSE);
	}
	return 0;
}

void CAssignmentDlg::OnBnClickedBtnReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pDlgImage->m_clkPoint.clear();
	m_pDlgImage->pointPrint(m_pDlgImage->m_clkPoint, m_pDlgImage->dragState);
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	memset(fm, WHITE_COLOR, m_pDlgImage->m_image.GetWidth() * m_pDlgImage->m_image.GetHeight());
	m_pDlgImage->updateDisplay();
	UpdateData(FALSE);
}

void CAssignmentDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	delete m_pDlgImage;
}

