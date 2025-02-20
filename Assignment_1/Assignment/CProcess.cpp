// CProcess.cpp: 구현 파일
//

#include "pch.h"
#include "Assignment.h"
#include "CProcess.h"


// CProcess

CProcess::CProcess()
{
}

CProcess::~CProcess()
{
}


// CProcess 멤버 함수

BOOL CProcess::validImgPos(CImage& m_image, int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}

BOOL CProcess::isInCircle(int i, int j, int nCesnterX, int nCesnterY, int m_Radius)
{
	bool bRet = false;

	double dX = (double)i - nCesnterX;
	double dY = (double)j - nCesnterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < (int)m_Radius * m_Radius)
		bRet = true;

	return bRet;
}

void CProcess::drawRandomCircle(CImage& m_image, int nCesnterX, int nCesnterY, int m_nRadius, int colorRef)
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	int nPitch = m_image.GetPitch();
	for (int j = nCesnterY - m_nRadius; j < nCesnterY + m_nRadius * 2; j++) {
		for (int i = nCesnterX - m_nRadius; i < nCesnterX + m_nRadius * 2; i++) {
			if (isInCircle(i, j, nCesnterX, nCesnterY, m_nRadius))
				if (validImgPos(m_image, i, j))
					fm[j * nPitch + i] = colorRef;
		}
	}
}

void CProcess::drawCircle(CDC* dc, vector<CPoint> m_clkPoint, CImage& m_image, int m_nBorder)
{
	if (m_clkPoint.size() == 3) {
		CPen pen;
		pen.CreatePen(PS_SOLID, m_nBorder, RGB(0, 0, 0));

		CPen* pOldPen = dc->SelectObject(&pen);
		CBrush* pOldBrush = (CBrush*)dc->SelectStockObject(NULL_BRUSH);

		CPoint A = m_clkPoint[0];
		CPoint B = m_clkPoint[1];
		CPoint C = m_clkPoint[2];

		CPoint center = CenterPoint(A, B, C);

		// 반지름 계산 (외심에서 한 점까지의 거리)
		int radius = (int)sqrt((A.x - center.x) * (A.x - center.x) +
			(A.y - center.y) * (A.y - center.y));

		CRect rect(0, 0, m_image.GetWidth(), m_image.GetHeight());
		dc->IntersectClipRect(&rect);
		dc->Ellipse(center.x - radius, center.y - radius, center.x + radius, center.y + radius);
		dc->SelectObject(pOldBrush);
		dc->SelectObject(pOldPen);
	}
}

CPoint CProcess::CenterPoint(CPoint A, CPoint B, CPoint C)
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
