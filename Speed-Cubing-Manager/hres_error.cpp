#include "stdafx.h"
#include "hres_error.h"

hres_error::hres_error( const char *message, HRESULT hr ) : std::exception(message), m_errorCode(hr) { }

HRESULT hres_error::GetErrorCode()
{
	return m_errorCode;
}
