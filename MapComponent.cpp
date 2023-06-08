#include "MapComponent.h"
#include "SizeDraw2D.h"
#include "Scene.h"
#include "manager.h"
#include "Player.h"
#include "Enemy.h"


void MapComponent::Init()
{
	Scene* scene = Manager::GetScene();



}

void MapComponent::Uninit()
{

}

void MapComponent::Draw()
{
}

void MapComponent::Update()
{

	Scene* scene = Manager::GetScene();

	if (!m_flag)
	{
		PlayerPos = new GameObject;
		PlayerPos->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		PlayerPos->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), 1);
		PlayerPos->SetTag("PlayerPos");
		scene->AddGameObject(PlayerPos, scene->UI_LAYER);

		EnemyPos = new GameObject;
		EnemyPos->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		EnemyPos->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), 1);
		EnemyPos->SetTag("EnemyPos");
		scene->AddGameObject(EnemyPos, scene->UI_LAYER);
		m_flag = true;
	}


	GameObject* pPlayer = scene->GetGameObject("Player", scene->PLAY_LAYER);
	GameObject* pEnemy = scene->GetGameObject("Enemy", scene->PLAY_LAYER);

	if (pPlayer != nullptr)
	{
		D3DXVECTOR3 PPos = D3DXVECTOR3((pPlayer->GetPosition().x / 25.0f) * m_ParentObject->GetComponent<SizeDraw2D>()->GetTexSize().x / 2
			, 0.0f, (pPlayer->GetPosition().z / 25.0f) * m_ParentObject->GetComponent<SizeDraw2D>()->GetTexSize().y / 2);
	
		PlayerPos->SetPosition(D3DXVECTOR3(m_ParentObject->GetPosition().x - PPos.x, m_ParentObject->GetPosition().y + PPos.z, 0.0f));
	}

	if (pEnemy != nullptr)
	{
		D3DXVECTOR3 EPos = D3DXVECTOR3((pEnemy->GetPosition().x / 25.0f) * m_ParentObject->GetComponent<SizeDraw2D>()->GetTexSize().x / 2
			, 0.0f, (pEnemy->GetPosition().z / 25.0f) * m_ParentObject->GetComponent<SizeDraw2D>()->GetTexSize().y / 2);

		EnemyPos->SetPosition(D3DXVECTOR3(m_ParentObject->GetPosition().x - EPos.x, m_ParentObject->GetPosition().y + EPos.z, 0.0f));

	}
}
