#include "Includes/PrecompileConfig.h"
#include "Timer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

#pragma comment(lib, "Winmm.lib")

CTimer::CTimer()
: m_nTimerID(0)
, m_nTimerResolution(0)
{
	TIMECAPS tc;
	if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR)
	{
		_ASSERT(0);
	}

	m_nTimerResolution = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
	timeBeginPeriod(m_nTimerResolution);
}

CTimer::~CTimer()
{
	if (m_nTimerResolution)
	{
		timeEndPeriod(m_nTimerResolution);
	}
}

void CTimer::TimerProc(unsigned int uID, unsigned int msg, unsigned long dwUser, unsigned long dw1, unsigned long dw2)
{
	CTimer* pTimer = (CTimer*)dwUser;
	if (!pTimer->OnTimer(uID))
	{
		pTimer->StopTimer(uID);
	}
}

unsigned int CTimer::StartTimer(bool bCustom, int nPeriod, int nResolution)
{
	unsigned int nTimerID = timeSetEvent(nPeriod, nResolution, &TimerProc, (unsigned long)this, TIME_PERIODIC);
	return nTimerID;
}

void CTimer::StopTimer(unsigned int& nTimeID)
{
	if (nTimeID != 0)
	{
		timeKillEvent(nTimeID);
		nTimeID = 0;
	}
}

#else

CTimer::CTimer()
{
	m_tTick.it_value.tv_sec = 0;
	m_tTick.it_value.tv_usec = 0;  
	m_tTick.it_interval.tv_sec = 0;
	m_tTick.it_interval.tv_usec = 0;
}

CTimer::~CTimer()
{
}

unsigned int CTimer::StartTimer(bool bCustom, int nPeriod, int nResolution)
{
	m_tTick.it_value.tv_sec = 1;
	m_tTick.it_value.tv_usec = 0;  
	m_tTick.it_interval.tv_sec = nPeriod; 
	m_tTick.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &m_tTick, NULL);

	return 0;
}

void CTimer::StopTimer(unsigned int& nTimeID)
{
	m_tTick.it_value.tv_sec = 0;
	m_tTick.it_value.tv_usec = 0;  
	m_tTick.it_interval.tv_sec = 0;
	m_tTick.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL, &m_tTick, NULL);
}

#endif
