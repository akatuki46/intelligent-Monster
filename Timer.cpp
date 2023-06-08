#include "Timer.h"
#include "GameObject.h"

void Timer::Update()
{
	m_Cnt++;
	if (m_TimerCnt <= m_Cnt)
	{
		m_Cnt = 0;
		m_TimerCnt = 0;
		m_LeftTime = 0;
		m_TimerEnd = true;
	}
	else
	{
		m_LeftTime = m_TimerCnt - m_Cnt;
		m_TimerEnd = false;
	}
}
