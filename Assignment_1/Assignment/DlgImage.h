#pragma once
#include<vector>

using namespace std;

// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)
private:
	static CPoint prePoint;
	CPoint nextPoint;
	bool m_rectInit = false;
	int dragIndex = -1;
	BOOL validImgPos(int x, int y);

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();
	int m_nRadius;
	int m_nBorder;
	bool dragState = false;
	CWnd* m_pParent;
	CImage m_image;
	vector<CPoint> m_clkPoint;

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGIMAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	BOOL isInCircle(int i, int j, int nCesnterX, int nCesnterY, int nRadius);
	CPoint CenterPoint(CPoint A, CPoint B, CPoint C);
	void updateDisplay();
	void drawCircle(vector<CPoint> m_clkPoint);
	void drawClickToCircle(unsigned char* fm, int nCesnterX, int nCesnterY, int nPitch, int m_nRadius, int colorRef);
	void pointPrint(vector<CPoint> m_clkPoint, bool dragState);
	int m_viewCircleX1;
	int m_viewCircleX2;
	int m_viewCircleX3;
	int m_viewCircleY1;
	int m_viewCircleY2;
	int m_viewCircleY3;
};
