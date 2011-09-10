#include "stdafx.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <new>
#include <stdexcept>
#include "Speed-Cubing-Manager.h"
#include "Speed-Cubing-ManagerDlg.h"
#include "afxdialogex.h"
#include "hres_error.h"

/*#ifdef _DEBUG
#define new DEBUG_NEW
#endif*/

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD) {}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSpeedCubingManagerDlg 대화 상자


CSpeedCubingManagerDlg::CSpeedCubingManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSpeedCubingManagerDlg::IDD, pParent), m_renderer(nullptr)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSpeedCubingManagerDlg::~CSpeedCubingManagerDlg()
{
	if (m_renderer != nullptr) {
		delete m_renderer;
		m_renderer = nullptr;
	}
}

void CSpeedCubingManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_D3D, m_buttonD3D);
}

BEGIN_MESSAGE_MAP(CSpeedCubingManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_BUTTON_D3D, &CSpeedCubingManagerDlg::OnNMCustomdrawButtonD3d)
END_MESSAGE_MAP()


// CSpeedCubingManagerDlg 메시지 처리기

BOOL CSpeedCubingManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// D3D device 초기화
	try
	{
		m_renderer = new (std::nothrow) CD3DRenderer(m_buttonD3D.m_hWnd);
	}
	catch(hres_error &er)
	{
		char buff[256];
		sprintf(buff,"%s\nError Code: 0x%x", er.what(), er.GetErrorCode());
		MessageBoxA(NULL, buff, "CD3DRenderer creation failed", MB_OK);
	}
	catch(std::runtime_error &er)
	{
		MessageBoxA(NULL, er.what(), "CD3DRenderer creation failed", MB_OK);
	}
	catch(std::exception &er)
	{
		MessageBoxA(NULL, er.what(), "CD3DRenderer creation failed", MB_OK);
	}
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSpeedCubingManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSpeedCubingManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSpeedCubingManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

