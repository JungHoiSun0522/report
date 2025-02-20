#pragma once
#include "DlgImage.h"
#include<vector>

using namespace std;

// CProcess 명령 대상

class CProcess : public CObject
{
public:
	CProcess();
	virtual ~CProcess();

	BOOL validImgPos(CImage& m_image, int x, int y);
	BOOL isInCircle(int i, int j, int nCesnterX, int nCesnterY, int m_Radius);
	void drawRandomCircle(CImage& m_image, int nCesnterX, int nCesnterY, int m_nRadius, int colorRef);
	void drawCircle(CDC* dc, vector<CPoint> m_clkPoint, CImage& m_image, int m_nBorder);
	CPoint CenterPoint(CPoint A, CPoint B, CPoint C);
};


