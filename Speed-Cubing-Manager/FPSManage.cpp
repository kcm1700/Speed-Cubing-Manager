#include "stdafx.h"
#include <mmsystem.h>
#include "FPSManage.h"
#include "consts.h"

FPSManage::FPSManage() : m_targetFPS(60.0)
{
	InitTime();
}

void FPSManage::SetTargetFPS( double fps )
{
	Concurrency::critical_section::scoped_lock scopeLock(m_lock);
	m_targetFPS = fps;
}

double FPSManage::GetTargetFPS()
{
	Concurrency::critical_section::scoped_lock scopeLock(m_lock);
	return m_targetFPS;
}

void FPSManage::InitTime()
{
	m_lastFrameTime = ::timeGetTime();
	m_timeDiff = 0;
}

DWORD FPSManage::WaitTime()
{
	timetype now = ::timeGetTime();

	double targetFPS;
	{
		Concurrency::critical_section::scoped_lock scopeLock(m_lock);
		targetFPS = m_targetFPS;
	}

	double idealSleepLen = 1000.0/targetFPS - (now - m_lastFrameTime) + m_timeDiff;
	DWORD sleepLen((DWORD)idealSleepLen);

	if(sleepLen <= 0) {
		m_timeDiff = 0;
		m_lastFrameTime = now;
		return 0;
	} else {
		m_timeDiff = m_lastFrameTime + m_timeDiff + 1000.0/targetFPS - (now + sleepLen);
		m_lastFrameTime = now + sleepLen;
		return sleepLen;
	}
}
