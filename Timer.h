#pragma once
#include "Component.h"
class Timer :
    public Component
{
public:
	void Init(int time) { m_TimerCnt = time; };
	void Uninit() override {};
	void Update() override;
	void Draw() override {};

	void SetTime(int time) { m_TimerCnt = time; }
	int GetTime() { return m_TimerCnt; }
	int GetLeftTime() { return m_LeftTime; }

	bool EndTimer() { return m_TimerEnd; }


private:
	int m_TimerCnt = 0;
	int m_Cnt = 0;

	//Œo‰ßŠÔ•Û‘¶—p•Ï”
	int m_LeftTime = 0;

	bool m_TimerEnd = false;
};

