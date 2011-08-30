#include "StdAfx.h"
#include "D3DRenderer.h"


CD3DRenderer::CD3DRenderer(HWND hWnd)
{
	HRESULT hr;
	hr = Direct3DCreate9Ex(D3D_SDK_VERSION, &m_pD3D9ex);
	if ( FAILED(hr) ) return;

}

#define SAFE_RELEASE(pObj) \
	if(pObj != NULL) { \
		pObj->Release(); \
		pObj = NULL; \
	}

CD3DRenderer::~CD3DRenderer(void)
{
	SAFE_RELEASE(m_pD3D9ex);
}

#undef SAFE_RELEASE
