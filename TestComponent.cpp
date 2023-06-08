//////////////////////////////////////////////////////////////////////////////////////////////////
//  テスト用　好きに使えるコンポーネント
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "TestComponent.h"
#include "GameObject.h"
#include "Draw2D.h"
#include "Enemy.h"
#include "Scene.h"
#include "manager.h"
#include "input.h"
#include "ClothDraw.h"
#include "Particle.h"

void TestComponent::Init()
{
	m_Name = "TestComponent";
}

void TestComponent::Uninit()
{
}

void TestComponent::Draw()
{
#ifdef _DEBUG

	if (!m_ImGuiDrawFlag)
		return;

	ImGui::Begin("Test ImGui", &m_ImGuiDrawFlag);
	ImGui::Text("TestrComplete");
	if (ImGui::TreeNode("TestPosition"))
	{
		ImGui::Text("X:%f Y:%f Z:%f", m_ParentObject->GetPosition().x, m_ParentObject->GetPosition().y, m_ParentObject->GetPosition().z);

		ImGui::TreePop();
		ImGui::Separator();
	}


	ImGui::End();

#endif // !_DEBUG

}

void TestComponent::Update()
{
	Scene* scene = Manager::GetScene();
	if (m_ParentObject->GetTag() == "Hakken")
	{

		GameObject* pEnemy = scene->GetGameObject("Enemy", scene->PLAY_LAYER);

		if (!pEnemy->GetComponent<Enemy>()->FindPlayer())
		{
			m_ParentObject->GetComponent<Draw2D>()->SetDrawFlag(false);

		}
		else
		{
			m_ParentObject->GetComponent<Draw2D>()->SetDrawFlag(true);

		}
	}

	if (m_ParentObject->GetTag() == "Particle3D")
	{
		if (GetKeyboardPress(DIK_W))
		{
			m_ParentObject->AddPositionY(-0.1f);
		}
		if (GetKeyboardPress(DIK_A))
		{
			m_ParentObject->AddPositionX(-0.1);
		}
		if (GetKeyboardPress(DIK_S))
		{
			m_ParentObject->AddPositionY(0.1f);
		}
		if (GetKeyboardPress(DIK_D))
		{
			m_ParentObject->AddPositionX(0.1f);
		}
	}

	if (m_ParentObject->GetTag() == "child2")
	{
		if (GetKeyboardPress(DIK_R))
		{
			m_ParentObject->AddRotationX(0.1f);
		}
		if (GetKeyboardPress(DIK_Q))
		{
			m_ParentObject->AddRotationX(-0.1f);
		}

		//m_ParentObject->m_Position.x += 0.01f;
	}

	if (m_ParentObject->GetTag() == "zinouga")
	{
		if (GetKeyboardPress(DIK_UP))
		{
			m_ParentObject->AddPositionZ(-0.1f);
		}
		if (GetKeyboardPress(DIK_LEFT))
		{
			m_ParentObject->AddPositionX(-0.1f);
		}
		if (GetKeyboardPress(DIK_DOWN))
		{
			m_ParentObject->AddPositionZ(0.1f);
		}
		if (GetKeyboardPress(DIK_RIGHT))
		{
			m_ParentObject->AddPositionX(0.1f);
		}

	}


	if (m_ParentObject->GetTag() == "Cloth")
	{
		GameObject* Cloth = scene->GetGameObject("Cloth", scene->UI_LAYER);
		
		m_ClothWind.y = 2.0f * m_TestFlag;
		m_Cnt++;
		if (m_Cnt > 30)
		{
			m_Cnt = 0;
			m_TestFlag *= -1;
		}

		Cloth->GetComponent<ClothDraw>()->AddWind(m_ClothWind);
	}
}
