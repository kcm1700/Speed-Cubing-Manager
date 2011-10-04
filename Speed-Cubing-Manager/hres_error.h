#ifndef hres_error_h__
#define hres_error_h__

#include <exception>
#include <WinDef.h>

class hres_error : public std::exception {
public:
	hres_error(const char *message, HRESULT hr);
	HRESULT GetErrorCode();
private:
	HRESULT m_errorCode;
};

#endif // hres_error_h__