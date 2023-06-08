#include "MultiComponent.h"
#include "Scene.h"
#include "Player.h"
#include "manager.h"
#include "SizeDraw2D.h"
#include "input.h"
#include "Timer.h"
#include "Transform.h"

void MultiComponent::Init()
{

}

void MultiComponent::Uninit()
{
	m_Flag = false;
}

void MultiComponent::Update()
{
	Scene* scene = Manager::GetScene();

	if (m_ParentObject->GetTag() == "Stamina")
	{
		GameObject* pPlayer = scene->GetGameObject("Player", scene->PLAY_LAYER);
		m_KeepInt = pPlayer->GetComponent<Player>()->GetStamina();
	
		m_ParentObject->GetComponent<SizeDraw2D>()->SetTexSize(D3DXVECTOR3(m_KeepInt * 10, 10.0f, 0.0f));
		m_ParentObject->GetComponent<SizeDraw2D>()->SetColor(D3DXVECTOR4(1.0f, 1.0f,0.0f, 1.0f));

	}

	if (m_ParentObject->GetTag() == "WorldTimer")
	{
		if (!m_Flag)
		{
			m_KeepInt = m_ParentObject->GetComponent<Timer>()->GetTime();
			m_Flag = true;
		}
		float rad = 0.0f;
		int elapsed = 0;  //Œ»Ý‚Ü‚Å‚ÌŒo‰ßŽžŠÔ
		int aa = 0;
		elapsed = m_KeepInt - m_ParentObject->GetComponent<Timer>()->GetLeftTime();
		aa = elapsed / 18000;
		rad = (aa * 30) * 6.28 / 360;
		m_ParentObject->SetRotationZ(rad);
	}

	if (m_ParentObject->GetTag() == "LoadLogo")
	{
		m_ParentObject->AddRotationZ(0.1f);
	}

	if (m_ParentObject->GetTag() == "Start")
	{
		if (m_Cnt > 60)
		{
			m_ParentObject->SetDestroy();
		}
		m_Cnt++;
	}

	if (m_ParentObject->GetTag() == "StartTimerUI")
	{
		if (m_Cnt > 60)
		{
			m_ParentObject->GetComponent<Transform>()->SetPlayFlag(true);
		}
		m_Cnt++;
	}

}

void MultiComponent::Draw()
{
}
