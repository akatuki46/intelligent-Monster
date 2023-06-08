#pragma once
#include "Component.h"

class Transition :
    public Component
{
private:

	bool m_In;
	bool m_OutFinish;
	bool m_InFinish;

	int m_Count = 0;
	int m_TransMax = 60;
public:

	void Init(int Max) { m_TransMax = Max; }
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void Start(bool in)
	{
		m_In = in;
		m_OutFinish = false;
		m_InFinish = false;

		if (m_In)
		{
			m_Count = m_TransMax;
		}
		else
		{
			m_Count = 0;
		}
	}
	int GetTransMax() { return m_TransMax; }

	bool GetStart() { return m_In; }
	int  GetCount() { return m_Count; }

	bool GetOutFinish() { return m_OutFinish; }
	bool GetInFinish() { return m_InFinish; }
};

