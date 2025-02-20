
// AssignmentDlg.h: 헤더 파일
//

#pragma once
#include "DlgImage.h"
#include<vector>

using namespace std;

#define WM_UPDATE_POINT_PRINT (WM_USER + 1)

// CAssignmentDlg 대화 상자
class CAssignmentDlg : public CDialogEx
{
	// 생성입니다.
public:
	CAssignmentDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CDlgImage* m_pDlgImage;
	int m_nRadius;
	int m_nBorder;

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASSIGNMENT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnUpdatePointPrint(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRadius();
	afx_msg void OnBnClickedBtnBorder();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnRandom();
	afx_msg void OnBnClickedBtnReset();
	void Process(CRect rect, int nPitch, int num, int delay);
};
