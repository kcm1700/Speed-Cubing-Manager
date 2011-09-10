#ifndef SpeedCubingManager_h__
#define SpeedCubingManager_h__

#include "D3DRenderer.h"
#include "afxwin.h"

// CSpeedCubingManagerDlg 대화 상자
class CSpeedCubingManagerDlg : public CDialogEx
{
// 생성입니다.
public:
	CSpeedCubingManagerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	virtual ~CSpeedCubingManagerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SPEEDCUBINGMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	// D3D 관련
	CD3DRenderer *m_renderer;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CButton m_buttonD3D;
//	afx_msg void OnNMCustomdrawButtonD3d(NMHDR *pNMHDR, LRESULT *pResult);
};

#endif
