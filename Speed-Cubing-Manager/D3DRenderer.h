#ifndef D3DRENDERER_H__
#define D3DRENDERER_H__


#include <d3d9.h>
#include <d3dx9.h>
#include <dxdiag.h>


class CD3DRenderer
{
public:
	CD3DRenderer(HWND hWnd);
	virtual ~CD3DRenderer(void);
private:
	CD3DRenderer(void);
	LPDIRECT3D9EX m_pD3D9ex;
	LPDIRECT3D9 m_pD3D9;
	LPDIRECT3DDEVICE9EX m_pD3DDevice9ex;
	LPDIRECT3DDEVICE9 m_pD3DDevice9;
};

#endif
