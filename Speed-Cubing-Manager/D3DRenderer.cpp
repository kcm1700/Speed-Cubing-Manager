#include "StdAfx.h"
#include "D3DRenderer.h"


CD3DRenderer::CD3DRenderer(HWND hWnd)
{
	HRESULT hr;
	hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &m_pD3D9ex);
	if ( FAILED(hr) ) return;

	D3DDEVTYPE devType = D3DDEVTYPE_HAL;
	if ( /* 옵션 */ false) {
		devType = D3DDEVTYPE_REF;
	}else if ( /* 옵션 */ false) {
		devType = D3DDEVTYPE_SW;
	}
	//TODO: HARDWARE VERTEXPROCESSING 사용할 수 있는지 여부 체크하기
	DWORD createOption = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferWidth = 1; /* TODO: */
	d3dpp.BackBufferHeight = 1; /* TODO: */
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	hr = m_pD3D9ex->CreateDeviceEx(D3DADAPTER_DEFAULT, devType, hWnd, 
		createOption, &d3dpp, NULL, &m_pD3DDevice9);
}

#define SAFE_RELEASE(pObj) \
	if(pObj != NULL) { \
		pObj->Release(); \
		pObj = NULL; \
	}

CD3DRenderer::~CD3DRenderer(void)
{
	SAFE_RELEASE(m_pD3DDevice9);
	SAFE_RELEASE(m_pD3D9ex);
}

#undef SAFE_RELEASE
