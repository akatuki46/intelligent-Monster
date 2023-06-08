#include "Transition.h"
#include "main.h"
#include "renderer.h"

void Transition::Uninit()
{
	m_Count = 0;
}

void Transition::Update()
{
	if (m_In)
	{
		if (m_Count > 0)
		{
			m_Count--;
		}
		else
		{
			m_InFinish = true;
		}
	}
	else
	{
		if (m_Count < m_TransMax)
		{
			m_Count++;
		}
		else
		{
			m_OutFinish = true;
		}
	}
}

void Transition::Draw()
{

}