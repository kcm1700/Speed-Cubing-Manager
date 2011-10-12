#ifndef FPSManage_h__
#define FPSManage_h__

#include <concrt.h>

class FPSManage {
public:
	FPSManage();

	void SetTargetFPS(double fps);
	double GetTargetFPS();

	void InitTime();
	DWORD WaitTime();
private:
	double m_targetFPS;
	Concurrency::critical_section m_lock;

	typedef DWORD timetype;
	timetype m_lastFrameTime;
	double m_timeDiff;
};

#endif // FPSManage_h__