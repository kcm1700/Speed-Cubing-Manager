#ifndef SpeedCubingManager_h__
#define SpeedCubingManager_h__

#include "D3DRenderer.h"
#include "afxwin.h"

// CSpeedCubingManagerDlg ��ȭ ����
class CSpeedCubingManagerDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSpeedCubingManagerDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	virtual ~CSpeedCubingManagerDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SPEEDCUBINGMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;
	// D3D ����
	CD3DRenderer *m_renderer;

	// ������ �޽��� �� �Լ�
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
