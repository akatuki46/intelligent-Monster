#include "HpComponent.h"
#include "Player.h"
#include "Scene.h"
#include "manager.h"
#include "SizeDraw2D.h"

void HpComponent::Init()
{
	Scene* scene = Manager::GetScene();
	GameObject* pPlayer = scene->GetGameObject("Player", scene->PLAY_LAYER);

	if (pPlayer != nullptr)
	{
		m_keepHp = pPlayer->GetComponent<Player>()->getHp();
	}

	GameObject* RedHp = new GameObject;
	RedHp->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	RedHp->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f), 2);
	RedHp->SetTag("RedHP");
	scene->AddGameObject(RedHp, scene->UI_LAYER);
}

void HpComponent::Uninit()
{
	m_keepHp = 0;
}

void HpComponent::Update()
{
	Scene* scene = Manager::GetScene();
	GameObject* pPlayer = scene->GetGameObject("Player", scene->PLAY_LAYER);
	GameObject* pRedHP = scene->GetGameObject("RedHP", scene->UI_LAYER);

	if (pPlayer != nullptr)
	{
		m_keepHp = pPlayer->GetComponent<Player>()->getHp();
		m_keepRedHp = pPlayer->GetComponent<Player>()->GetRedHp();
	}

	m_ParentObject->GetComponent<SizeDraw2D>()->SetTexSize(D3DXVECTOR3(m_keepHp * 10, 10.0f, 0.0f));

	if (m_keepRedHp > 0)
	{
		pRedHP->SetPosition(m_ParentObject->GetPosition() + D3DXVECTOR3(m_keepHp * 10, 0.0f, 0.0f));

		pRedHP->GetComponent<SizeDraw2D>()->SetTexSize(D3DXVECTOR3(m_keepRedHp * 10, 10.0f, 0.0f));
		pRedHP->GetComponent<SizeDraw2D>()->SetColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));

	}
}

void HpComponent::Draw()
{
}
