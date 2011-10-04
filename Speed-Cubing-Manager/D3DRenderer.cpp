#include "StdAfx.h"
#include <exception>
#include <stdexcept>
#include <new>
#include "D3DRenderer.h"
#include "hres_error.h"

CD3DRenderer::CD3DRenderer(HWND hWnd) : m_pD3D9(nullptr), m_pD3D9ex(nullptr), m_pD3DDevice9(nullptr), m_hStopEvent(nullptr), m_hThread(nullptr)
{
	HRESULT hr;
	HMODULE hlib = ::LoadLibrary(TEXT("d3d9.dll"));
	if(hlib == nullptr) {
		this->~CD3DRenderer();
		throw std::runtime_error("d3d9.dll loadlibrary error");
	}

	HRESULT (WINAPI *pDirect3DCreate9Ex)(UINT, IDirect3D9Ex **) = 
		reinterpret_cast<HRESULT (WINAPI *)(UINT, IDirect3D9Ex **)>(::GetProcAddress(hlib, "Direct3DCreate9Ex"));

	if(pDirect3DCreate9Ex != nullptr)
	{
		hr = (*pDirect3DCreate9Ex)(D3D_SDK_VERSION, &m_pD3D9ex);
		if( FAILED(hr) ) {
			this->~CD3DRenderer();
			throw hres_error("Direct3DCreate9Ex Error", hr);
		}

		hr = m_pD3D9ex->QueryInterface(IID_IDirect3D9, reinterpret_cast<void **>(&m_pD3D9));
		if( FAILED(hr) ) {
			this->~CD3DRenderer();
			throw hres_error("Direct3DCreate9Ex::QueryInterface Error", hr);
		}
	}
	else
	{
		m_pD3D9 = ::Direct3DCreate9(D3D_SDK_VERSION);
		if(m_pD3D9 == nullptr) {
			this->~CD3DRenderer();
			throw std::runtime_error("Direct3DCreate9 error");
		}
	}

	D3DDEVTYPE devType = D3DDEVTYPE_HAL;
	if ( /* 옵션 */ false) { //TODO: 옵션에 들어간다.
		devType = D3DDEVTYPE_REF;
	}else if ( /* 옵션 */ false) {
		devType = D3DDEVTYPE_SW;
	}

	//FIXME: HARDWARE VERTEXPROCESSING 사용할 수 있는지 여부 체크하기
	DWORD createOption = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferWidth = 0;
	d3dpp.BackBufferHeight = 0;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	hr = m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, devType, NULL, 
		createOption, &d3dpp, &m_pD3DDevice9);

	if(FAILED(hr)) {
		this->~CD3DRenderer();
		throw hres_error("CreateDevice Error", hr);
	}

	m_hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if(m_hStopEvent == nullptr) {
		this->~CD3DRenderer();
		throw std::runtime_error("CreateEvent failed");
	}

	m_hThread = (HANDLE)::_beginthreadex(nullptr, 0, threadProc, this, 0, nullptr);
	if(m_hThread == nullptr) {
		this->~CD3DRenderer();
		throw std::runtime_error("_beginthreadex failed");
	}
}

#define SAFE_RELEASE(pObj) \
	if(pObj != nullptr) { \
		pObj->Release(); \
		pObj = nullptr; \
	}

CD3DRenderer::~CD3DRenderer(void)
{
	if(m_hThread != nullptr)
	{
		SetEvent(m_hStopEvent);
		if(WaitForSingleObject(m_hThread, 5000) != WAIT_TIMEOUT) {
			TerminateThread(m_hThread, 0x1);
		}
		CloseHandle(m_hThread);
		m_hThread = nullptr;
	}

	if(m_hStopEvent != nullptr)
	{
		CloseHandle(m_hStopEvent);
		m_hStopEvent = nullptr;
	}

	SAFE_RELEASE(m_pD3DDevice9);
	SAFE_RELEASE(m_pD3D9);
	SAFE_RELEASE(m_pD3D9ex);
}

unsigned int CD3DRenderer::threadProc(void *pParam)
{
	CD3DRenderer *ptr = reinterpret_cast<CD3DRenderer *>(pParam);
	ptr->WorkLoop();
	return 0u;
}

void CD3DRenderer::WorkLoop()
{
	while(::WaitForSingleObject(m_hStopEvent, 0) == WAIT_TIMEOUT)
	{
		HRESULT hr;
		hr = m_pD3DDevice9->Clear(0,nullptr,D3DCLEAR_TARGET,0x0,0,0);
		if(SUCCEEDED(m_pD3DDevice9->BeginScene()))
		{
			DrawCube();
			m_pD3DDevice9->EndScene();
		}
		hr = m_pD3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
		Sleep(33);
	}
}

void CD3DRenderer::DrawCube()
{
	// DRAW CUBE HERE
}

#undef SAFE_RELEASE
