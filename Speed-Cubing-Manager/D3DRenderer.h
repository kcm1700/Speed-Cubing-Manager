#ifndef D3DRENDERER_H__
#define D3DRENDERER_H__
#include "FPSManage.h"

class CD3DRenderer : private Uncopyable
{
public:
	CD3DRenderer(HWND hWnd);
	virtual ~CD3DRenderer(void);
private:
	CD3DRenderer(void);

#pragma region members
	// DirectX 관련
	LPDIRECT3D9 m_pD3D9;
	LPDIRECT3D9EX m_pD3D9ex;
	LPDIRECT3DDEVICE9 m_pD3DDevice9;

	// 스레드 제어 관련
	HANDLE m_hStopEvent;
	HANDLE m_hThread;

	// 렌더러 동작 관련
	FPSManage m_fpsManage;
	struct UIState {
		enum type {
			MENU,
			PLAY,
			OPTION
		};
	};
	UIState::type m_UIState;
#pragma endregion end of members

#pragma region methods
	static unsigned int __stdcall threadProc(void *pParam);
	void WorkLoop();
	void DrawCube();
	void ProcessPlay();
	void ProcessMenu();
	void ProcessOption();
#pragma endregion end of methods

};

#endif
