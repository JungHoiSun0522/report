// DlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "Assignment.h"
#include "AssignmentDlg.h"
#include "DlgImage.h"
#include "afxdialogex.h"
#define WHITE_COLOR 0xff
#define BLACK_COLOR 0x00


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)
CPoint CDlgImage::prePoint;
CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLGIMAGE, pParent)
	, m_viewCircleX1(0)
	, m_viewCircleX2(0)
	, m_viewCircleX3(0)
	, m_viewCircleY1(0)
	, m_viewCircleY2(0)
	, m_viewCircleY3(0)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CIRCLE_X1, m_viewCircleX1);
	DDX_Text(pDX, IDC_EDIT_CIRCLE_X2, m_viewCircleX2);
	DDX_Text(pDX, IDC_EDIT_CIRCLE_X3, m_viewCircleX3);
	DDX_Text(pDX, IDC_EDIT_CIRCLE_Y1, m_viewCircleY1);
	DDX_Text(pDX, IDC_EDIT_CIRCLE_Y2, m_viewCircleY2);
	DDX_Text(pDX, IDC_EDIT_CIRCLE_Y3, m_viewCircleY3);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 640, 510);

	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, WHITE_COLOR, nWidth * nHeight);

	updateDisplay();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_image)
		m_image.Draw(dc, 0, 0);
}

void CDlgImage::updateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

void CDlgImage::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_clkPoint.size() == 3) {
		if (validImgPos(point.x, point.y)) {

			for (int i = 0; i < 3; i++) {
				if (isInCircle(point.x, point.y, m_clkPoint[i].x, m_clkPoint[i].y, m_nRadius)) {
					dragState = true;
					dragIndex = i;
					prePoint = point;
					break;
				}
			}
		}
	}
	else if (m_clkPoint.size() < 3) {
		if (validImgPos(point.x, point.y)) {
			m_clkPoint.emplace_back(point);
			CAssignmentDlg* m_pAssignment = (CAssignmentDlg*)m_pParent;
			int nPitch = m_image.GetPitch();
			unsigned char* fm = (unsigned char*)m_image.GetBits();
			m_nRadius = m_pAssignment->m_nRadius;
			drawClickToCircle(fm, point.x, point.y, nPitch, m_nRadius, BLACK_COLOR);
			pointPrint(m_clkPoint, dragState);
			updateDisplay();
		}
		if (m_clkPoint.size() == 3) {
			drawCircle(m_clkPoint);
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CDlgImage::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (dragState && dragIndex != -1) {
		nextPoint.x = point.x - prePoint.x;
		nextPoint.y = point.y - prePoint.y;

		int nPitch = m_image.GetPitch();
		unsigned char* fm = (unsigned char*)m_image.GetBits();

		drawClickToCircle(fm, m_clkPoint[dragIndex].x, m_clkPoint[dragIndex].y, nPitch, m_nRadius, WHITE_COLOR);
		drawClickToCircle(fm, m_clkPoint[dragIndex].x + nextPoint.x, m_clkPoint[dragIndex].y + nextPoint.y, nPitch, m_nRadius, BLACK_COLOR);
		m_clkPoint[dragIndex] += nextPoint;
		pointPrint(m_clkPoint, dragState);
		updateDisplay();
		prePoint = point;
		drawCircle(m_clkPoint);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CDlgImage::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	dragState = false;
	dragIndex = -1;
	prePoint = (-1, -1);
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CDlgImage::drawClickToCircle(unsigned char* fm, int nCesnterX, int nCesnterY, int nPitch, int m_nRadius, int colorRef)
{
	for (int j = nCesnterY - m_nRadius; j < nCesnterY + m_nRadius * 2; j++) {
		for (int i = nCesnterX - m_nRadius; i < nCesnterX + m_nRadius * 2; i++) {
			if (isInCircle(i, j, nCesnterX, nCesnterY, m_nRadius))
				if (validImgPos(i, j))
					fm[j * nPitch + i] = colorRef;
		}
	}
}

BOOL CDlgImage::isInCircle(int i, int j, int nCesnterX, int nCesnterY, int m_Radius)
{
	bool bRet = false;

	double dX = (double)i - nCesnterX;
	double dY = (double)j - nCesnterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < (int)m_Radius* m_Radius)
		bRet = true;

	return bRet;
}

BOOL CDlgImage::validImgPos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}

void CDlgImage::pointPrint(vector<CPoint> m_clkPoint, bool dragState)
{
	CAssignmentDlg* m_pAssignment = (CAssignmentDlg*)m_pParent;
	CString str_x[3], str_y[3];

	m_viewCircleX1 = m_clkPoint.size() > 0 ? m_clkPoint[0].x : 0;
	m_viewCircleY1 = m_clkPoint.size() > 0 ? m_clkPoint[0].y : 0;
	m_viewCircleX2 = m_clkPoint.size() > 1 ? m_clkPoint[1].x : 0;
	m_viewCircleY2 = m_clkPoint.size() > 1 ? m_clkPoint[1].y : 0;
	m_viewCircleX3 = m_clkPoint.size() > 2 ? m_clkPoint[2].x : 0;
	m_viewCircleY3 = m_clkPoint.size() > 2 ? m_clkPoint[2].y : 0;

	m_pAssignment->PostMessage(WM_UPDATE_POINT_PRINT, (WPARAM)this, 0);
}

void CDlgImage::drawCircle(vector<CPoint> m_clkPoint)
{
	if (m_clkPoint.size() == 3) {
		CAssignmentDlg* m_pAssignment = (CAssignmentDlg*)m_pParent;
		m_nBorder = m_pAssignment->m_nBorder;
		CClientDC dc(this);
		CPen pen;
		pen.CreatePen(PS_SOLID, m_nBorder, RGB(0, 0, 0));

		CPen* pOldPen = dc.SelectObject(&pen);
		CBrush* pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);

		CPoint A = m_clkPoint[0];
		CPoint B = m_clkPoint[1];
		CPoint C = m_clkPoint[2];

		CPoint center = CenterPoint(A, B, C);

		// 반지름 계산 (외심에서 한 점까지의 거리)
		int radius = (int)sqrt((A.x - center.x) * (A.x - center.x) +
			(A.y - center.y) * (A.y - center.y));

		CRect rect(0, 0, m_image.GetWidth(), m_image.GetHeight());
		dc.IntersectClipRect(&rect);
		dc.Ellipse(center.x - radius, center.y - radius, center.x + radius, center.y + radius);
		dc.SelectObject(pOldBrush);
		dc.SelectObject(pOldPen);
	}
}

CPoint CDlgImage::CenterPoint(CPoint A, CPoint B, CPoint C)
{
	double D = 2.0 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));

	double x = ((A.x * A.x + A.y * A.y) * (B.y - C.y) +
		(B.x * B.x + B.y * B.y) * (C.y - A.y) +
		(C.x * C.x + C.y * C.y) * (A.y - B.y)) / D;

	double y = ((A.x * A.x + A.y * A.y) * (C.x - B.x) +
		(B.x * B.x + B.y * B.y) * (A.x - C.x) +
		(C.x * C.x + C.y * C.y) * (B.x - A.x)) / D;
	return { (int)x, (int)y };
}
