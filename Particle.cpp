#include "Particle.h"
#include "main.h"
#include "manager.h"
#include "Scene.h"
#include "Draw2DAction.h"
#include "input.h"
#include "Draw2DParticle.h"
#include "Draw2DParticleVer3D.h"
#include "input.h"

#define OFFSET_X			(SCREEN_WIDTH / 2)		// スクリーンの幅オフセット
#define OFFSET_Y			(SCREEN_HEIGHT / 2)		// スクリーンの高さオフセット

void Particle::Init(bool Is3D)
{
	m_3Dmode = Is3D;



	m_Name = "ParticleManager";
}

void Particle::Uninit()
{
}

void Particle::Update()
{
	Scene* scene = Manager::GetScene();
	
	if (!m_3Dmode)
	{
		// マウスクリック判定
		if (GetAsyncKeyState(VK_LBUTTON))
			g_uOnClick++;
		else
			g_uOnClick = 0;

		POINT p;
		GetCursorPos(&p);

		// スクリーン座標をクライアント座標に変換する
		ScreenToClient(GetWindow(), &p);

		int mx = p.x;
		int my = p.y;

		//----------------------------------------
		if (g_uOnClick == 1)
		{
			for (int i = 0; i < 50; i++)
			{
				int angle;
				float rad;
				float spd;

				angle = (int)Manager::randomfloat(0.0f, 10000.0f) % 360;
				rad = angle * 6.28 / 360;
				spd = ((int)Manager::randomfloat(0.0f, 10000.0f) % 50 + 100) / 100.0f;

				GameObject* Particle = new GameObject;
				Particle->SetPosition(D3DXVECTOR3((float)mx, (float)my, 0.0f));
				Particle->SetVelocity(D3DXVECTOR3(spd * cosf(rad), spd * sinf(rad), 0.0f));
				Particle->AddComponent<Draw2DParticle>()->Init(D3DXVECTOR3(20.0f, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.1f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), 100);
				Particle->SetTag("Particle");
				scene->AddGameObject(Particle, scene->UI_LAYER);
			}

		}
		for (int i = 0; i < 20; i++)
		{
			float rad = (int)Manager::randomfloat(0.0f, 10000.0f) % 360 * 6.28f / 360;
			int d = (int)Manager::randomfloat(0.0f, 10000.0f) % 10;
			float px = mx + cosf(rad) * d;
			float py = my + sinf(rad) * d;

			GameObject* Particle = new GameObject;
			Particle->SetPosition(D3DXVECTOR3(px, py, 0.0f));
			Particle->SetVelocity(D3DXVECTOR3((mx - px) / 10, (my - py) / 10, 0.0f));
			Particle->AddComponent<Draw2DParticle>()->Init(D3DXVECTOR3(10.0f, 10.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), 10);
			Particle->SetTag("Particle");
			scene->AddGameObject(Particle, scene->UI_LAYER);
		}
	}

	if (m_3Dmode)
	{
		if (!m_End && m_Use)
		{
			if (m_IntervalCnt > m_Interval)
			{
				for (int i = 0; i < m_Amount; i++)
				{
					int angle;
					float rad;
					float spd;
					int d = 0;
					angle = (int)Manager::randomfloat(0.0f, 10000.0f) % 360;
					rad = angle * 6.28 / 360;
					//spd = ((int)Manager::randomfloat(0.0f, 10000.0f) % 50 + 100) / m_spd;

					float px = 0.0f;
					float pz = 0.0f;

					GameObject* particle = nullptr;

					switch (m_Type)
					{
					case Hanabi:
						//花火
						d = ((int)Manager::randomfloat(0.0f, 10000.0f) % 10 / 2);
						px = m_ParentObject->GetPosition().x + cosf(rad) * d;
						//float py = m_ParentObject->m_Position.y + sinf(rad) * d;
						pz = m_ParentObject->GetPosition().z + sinf(rad) * d;

						particle = new GameObject;
						particle->SetPosition(D3DXVECTOR3(px, 2.0f, pz));
						particle->SetVelocity(D3DXVECTOR3(m_spd * cosf(rad), 0.001, m_spd * sinf(rad)));
						particle->SetScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
						particle->AddComponent<Draw2DParticleVer3D>()->Init(m_Size, m_Acc, m_Color, m_LifeTime);
						particle->SetTag("Particle");
						scene->AddGameObject(particle, scene->PLAY_LAYER);
						break;

					case Hunsui:
						//噴水？チックなもの
						d = ((int)Manager::randomfloat(0.0f, 10000.0f) % 10 / 2);
						px = m_ParentObject->GetPosition().x;
						//float py = m_ParentObject->m_Position.y + sinf(rad) * d;
						pz = m_ParentObject->GetPosition().z;

						particle = new GameObject;
						particle->SetPosition(D3DXVECTOR3(px, 2.0f, pz));
						particle->SetVelocity(D3DXVECTOR3(m_spd* cosf(rad), -0.001, m_spd* sinf(rad)));
						particle->SetScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
						particle->AddComponent<Draw2DParticleVer3D>()->Init(m_Size, m_Acc, m_Color, m_LifeTime);
						particle->SetTag("Particle");
						scene->AddGameObject(particle, scene->PLAY_LAYER);
						break;
					default:
						break;
					}



				}

				m_IntervalCnt = 0;

				if (!m_Loop)
					m_End = true;
			}
			m_IntervalCnt++;


		}
	}

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		if (!m_Use)
		{
			m_Use = true;
		}
		else
		{
			m_Use = false;
		}
	}


}

void Particle::Draw()
{
#ifdef _DEBUG

	if (!m_ImGuiDrawFlag)
		return;
	ImGui::Begin("Particle ImGui", &m_ImGuiDrawFlag);

	ImGui::InputInt("Interval", &m_Interval);
	ImGui::Separator();
	ImGui::InputInt("LifeTime", &m_LifeTime);
	ImGui::Separator();
	ImGui::InputInt("Amount", &m_Amount);
	ImGui::Separator();

	ImGui::InputInt("PosRot", &m_PosRot);
	ImGui::Separator();

	if (ImGui::TreeNode("Acceleration"))
	{
		ImGui::InputFloat("PositionX", &m_Acc.x);
		ImGui::InputFloat("PositionY", &m_Acc.y);
		ImGui::InputFloat("PositionZ", &m_Acc.z);

		ImGui::TreePop();
	}
	ImGui::Separator();
	ImGui::InputFloat("Speed", &m_spd);
	ImGui::Separator();

	ImGui::ColorPicker4("Color", m_Color);

	ImGui::Checkbox("Loop", &m_Loop);
	if (m_Loop)
	{
		m_End = false;
	}
	ImGui::Separator();

	ImGui::End();

#endif // !_DEBUG
}
