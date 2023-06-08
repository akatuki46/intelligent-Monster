#include "Transform.h"
#include "Scene.h"
#include "manager.h"
#include "SizeDraw2D.h"

void Transform::Init(D3DXVECTOR3 EndPos, int mode, int MoveFlame ,int Inteval)
{
	m_TransFlame = MoveFlame;
	m_Mode = (TransMode)mode;
	m_IntervalCnt = Inteval;

	m_ChangePos = (EndPos - m_ParentObject->GetPosition()) / MoveFlame;
}

void Transform::Init(D3DXVECTOR3 EndScale, int mode, int MoveFlame, int Inteval, int None)
{
	m_TransFlame = MoveFlame;
	m_Mode = (TransMode)mode;
	m_IntervalCnt = Inteval;

	m_ChangeScale = (EndScale - m_ParentObject->GetScale()) / MoveFlame;
}

void Transform::Init(D3DXVECTOR3 angle, int mode, int MoveFlame, int Inteval, float None)
{
	m_TransFlame = MoveFlame;
	m_Mode = (TransMode)mode;
	m_IntervalCnt = Inteval;

	m_Rad = (angle * 6.28 / 360) / MoveFlame;

}

void Transform::Init(D3DXVECTOR3 EndSize,D3DXVECTOR3 StartSize, int mode, int MoveFlame, int Inteval, float None)
{
	m_TransFlame = MoveFlame;
	m_Mode = (TransMode)mode;
	m_IntervalCnt = Inteval;

	m_ChangeSize = (EndSize - StartSize) / MoveFlame;

}
void Transform::Uninit()
{
}

void Transform::Update()
{
	Scene* scene = Manager::GetScene();

	if (!m_Playflag)
		return;

	switch (m_Mode)
	{
	case Not_Back:    //s‚Á‚½‚«‚è
		if (m_TransFlame > 0)
		{
			if (m_ChangePos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_ParentObject->AddPosition(m_ChangePos);
			}

			if (m_ChangeScale != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_ParentObject->AddScale(m_ChangeScale);
			}

			if (m_Rad != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_ParentObject->AddRotation(m_Rad);
			}

			if (m_ChangeSize != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				if (m_ParentObject->GetComponent<SizeDraw2D>())
				{
					m_ParentObject->GetComponent<SizeDraw2D>()->AddTexSize(m_ChangeSize);

				}
			}
			m_TransFlame--;
			
		}
		else
		{
			if (m_ChangeScale != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_ChangeScale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			m_EndFlag = true;
		}

		break;
	case Come_Back:   //s‚Á‚Ä–ß‚Á‚Ä‚­‚é
		if (m_ChangePos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_ParentObject->AddPosition(m_ChangePos * m_TransDire);
		}

		if (m_ChangeScale != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_ParentObject->AddScale(m_ChangeScale * m_TransDire);
		}

		if (m_Rad != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_ParentObject->AddRotation(m_Rad * m_TransDire);
		}

		if (m_ChangeScale != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_ChangeScale *= m_TransDire;
		}

		m_TransCnt++;
		if (m_TransCnt == m_TransFlame && !m_Once)
		{
			m_TransDire *= -1;
			m_TransCnt = 0;
			m_Once = true;
		}
		else if(m_TransCnt == m_TransFlame && m_Once)
		{
			if (m_ChangeScale != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_ChangeScale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			m_EndFlag = true;
		}
		break;
	case Move_Loop:    //‚¸‚Á‚Æ“®‚«‘±‚¯‚é
		if (m_ChangePos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_ParentObject->AddPosition(m_ChangePos * m_TransDire);
		}

		if (m_ChangeScale != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_ParentObject->AddScale(m_ChangeScale * m_TransDire);
		}

		if (m_Rad != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_ParentObject->AddRotation(m_Rad * m_TransDire);
		}

		if (m_ChangeScale != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			m_ChangeScale *= m_TransDire;
		}

		m_TransCnt++;
		if (m_TransCnt == m_TransFlame)
		{
			m_TransDire *= -1;
			m_TransCnt = 0;
		}
		break;

	case Interval_Loop:   //ˆê’èŠÔŠu‚Å“®‚­
		if (m_IntervalCnt < m_Cnt)
		{
			if (m_TransFlame >= m_TransCnt)
			{
				if (m_ChangePos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
				{
					m_ParentObject->AddPosition(m_ChangePos* m_TransDire);
				}

				if (m_ChangeScale != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
				{
					m_ParentObject->AddScale(m_ChangeScale* m_TransDire);
				}

				if (m_Rad != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
				{
					m_ParentObject->AddRotation(m_Rad* m_TransDire);
				}
				m_TransCnt++;

			}
			else
			{
				m_TransDire *= -1;
				m_Cnt = 0;
				m_TransCnt = 0;
			}

		}
		m_Cnt++;
		break;

	case Come_Back_Interval:
		if (!m_Intervalflag && m_EndFlag == false)
		{
			if (m_ChangePos != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_ParentObject->AddPosition(m_ChangePos * m_TransDire);
			}

			if (m_ChangeScale != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_ParentObject->AddScale(m_ChangeScale * m_TransDire);
			}

			if (m_Rad != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_ParentObject->AddRotation(m_Rad * m_TransDire);
			}

			if (m_ChangeScale != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_ChangeScale *= m_TransDire;
			}
			m_TransCnt++;

		}
		else if(m_Intervalflag && m_EndFlag == false)
		{
			if (m_Cnt > m_IntervalCnt)
			{
				m_Intervalflag = false;
				m_Cnt = 0;
			}
			m_Cnt++;

		}
		if (m_TransCnt == m_TransFlame && !m_Once)
		{
			m_TransDire *= -1;
			m_TransCnt = 0;
			m_Once = true;
			m_Intervalflag = true;
		}
		else if (m_TransCnt == m_TransFlame && m_Once)
		{
			if (m_ChangeScale != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
			{
				m_ChangeScale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			m_EndFlag = true;
		}
		break;
	default:
		break;
	}
}
