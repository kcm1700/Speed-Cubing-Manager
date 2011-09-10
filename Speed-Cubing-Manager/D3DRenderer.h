#ifndef D3DRENDERER_H__
#define D3DRENDERER_H__

class CD3DRenderer
{
public:
	CD3DRenderer(HWND hWnd);
	virtual ~CD3DRenderer(void);
private:
	CD3DRenderer(void);
#pragma region members
	LPDIRECT3D9 m_pD3D9;
	LPDIRECT3D9EX m_pD3D9ex;
	LPDIRECT3DDEVICE9 m_pD3DDevice9;
	HANDLE m_hStopEvent;
	HANDLE m_hThread;
#pragma endregion end of members

#pragma region methods
	static unsigned int __stdcall threadProc(void *pParam);
	void WorkLoop();
	void DrawCube();
#pragma endregion end of methods

#endif

};