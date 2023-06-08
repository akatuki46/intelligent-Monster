#include "main.h"
#include "renderer.h"
#include "input.h"
#include "Player.h"
#include "Bullet.h"
#include "manager.h"
#include "Enemy.h"
#include "Item.h"
#include "Scene.h"
#include "title.h"
#include "ModelContainer.h"
#include "audio.h"
#include "Draw3D.h"
#include "Collision.h"
#include "MeshFieldDraw.h"
#include "Draw3DAnimetion.h"
#include "OBBCollision.h"
#include "AttaBoxComponent.h"
#include "camera.h"
#include "Padinput.h"
#include "Transform.h"

//コリジョンコンポ―ネントを作るとき
//①コリジョン必要なGameObjectにコリジョンコンポーネントをアタッチ
//②コリジョンコンポーネントには自分と何かが当たったか当たってないかを判定
//③当たったと判定したら、自分のGameObjectが”何か”と当たったときの処理を呼び出す
//↑例：プレイヤーと敵が当たった場合、
//コリジョンコンポーネントがプレイヤーの当たった処理を呼び出す


#define INVITIME 20
#define GRAVITE 0.5f

#define CIRCLE (3.14f)
#define CAMERA_SPEAD 100

static int CirclePoint = 0;

void Player::Init()
{
	m_Hp = 100;
	m_Stamina = 150;

	//Scene* scene = Manager::GetScene();
	//m_shotSE = scene->AddGameObject<Audio>(2);
	//m_shotSE->Load("asset\\Audio\\wan.wav");

	//影を付ける場合はここに影のインスタンスをセット
	m_Name = "Player";

}

void Player::Uninit()
{

}

void Player::Update()
{
	Scene* scene = Manager::GetScene();
	GameObject* pField = scene->GetGameObject("Field", scene->PLAY_LAYER);
	GameObject* pCamera = scene->GetGameObject("Camera", scene->CAMERA_LAYER);

	m_ParentObject->SetOldPosition(m_ParentObject->GetPosition());

	//攻撃を食らった時は何もできなくなる
	if (!m_DamageFalg && !m_AttackFlag)
	{
		//三角関数での移動(前)
		if (GetKeyboardPress(DIK_W) || GetThumbLeftY(0) > 0)
		{
			
			m_ParentObject->AddPosition(-(pCamera->GetForward() * m_MoveValue));
			m_ParentObject->SetRotation(pCamera->GetRotation());

			if (m_DashFlag)
			{
				m_ParentObject->SetAnimetionName("Run");
				m_ParentObject->SetNextAnimetionName("Run");

				if (m_StaminaCnt > 3){
					m_Stamina--;
					m_StaminaCnt = 0;
				}
				else
				{
					m_StaminaCnt++;
				}
			}
			else
			{
				m_ParentObject->SetAnimetionName("Walk");
				m_ParentObject->SetNextAnimetionName("Walk");
			}
		}
		else
		{

			m_ParentObject->SetAnimetionName("Idle");
			m_ParentObject->SetNextAnimetionName("Idle");
		}
		//三角関数での移動(左)
		if (GetKeyboardPress(DIK_A) || GetThumbLeftX(0) < 0)
		{
			m_ParentObject->AddPosition(pCamera->GetRight() * m_MoveValue);
			D3DXVECTOR3 aa = pCamera->GetRight();
			m_ParentObject->SetRotationY(-atanf(D3DXVec3Length(&aa)) - 0.5f + pCamera->GetRotation().y);


			if (m_DashFlag)
			{
				m_ParentObject->SetAnimetionName("Run");
				m_ParentObject->SetNextAnimetionName("Run");
				if (m_StaminaCnt > 3) {
					m_Stamina--;
					m_StaminaCnt = 0;
				}
				else
				{
					m_StaminaCnt++;
				}

			}
			else
			{
				m_ParentObject->SetAnimetionName("Walk");
				m_ParentObject->SetNextAnimetionName("Walk");
			}
		}
		//三角関数での移動(右)
		if (GetKeyboardPress(DIK_D) || GetThumbLeftX(0) > 0)
		{
			m_ParentObject->AddPosition(-(pCamera->GetRight() * m_MoveValue));
			D3DXVECTOR3 aa = -(pCamera->GetRight());
			m_ParentObject->SetRotationY(atanf(D3DXVec3Length(&aa)) + 0.5f + pCamera->GetRotation().y);

			if (m_DashFlag)
			{
				m_ParentObject->SetAnimetionName("Run");
				m_ParentObject->SetNextAnimetionName("Run");
				if (m_StaminaCnt > 3) {
					m_Stamina--;
					m_StaminaCnt = 0;
				}
				else
				{
					m_StaminaCnt++;
				}

			}
			else
			{
				m_ParentObject->SetAnimetionName("Walk");
				m_ParentObject->SetNextAnimetionName("Walk");
			}
		}
		//三角関数での移動(後)
		if (GetKeyboardPress(DIK_S) || GetThumbLeftY(0) < 0)
		{
			m_ParentObject->AddPosition(pCamera->GetForward() * m_MoveValue);
			D3DXVECTOR3 aa = -(pCamera->GetForward());
			m_ParentObject->SetRotationY(atanf(D3DXVec3Length(&aa)) + 2.0f + pCamera->GetRotation().y);

			if (m_DashFlag)
			{
				m_ParentObject->SetAnimetionName("Run");
				m_ParentObject->SetNextAnimetionName("Run");
				if (m_StaminaCnt > 3) {
					m_Stamina--;
					m_StaminaCnt = 0;
				}
				else
				{
					m_StaminaCnt++;
				}

			}
			else
			{
				m_ParentObject->SetAnimetionName("Walk");
				m_ParentObject->SetNextAnimetionName("Walk");
			}
		}

		if (IsMouseLeftTriggered() || IsButtonXinputTriggered(0, XINPUT_GAMEPAD_Y))
		{
			GameObject* attabox = new GameObject;
			attabox->SetRotation(m_ParentObject->GetRotation());
			attabox->SetPosition(m_ParentObject->GetPosition() - m_ParentObject->GetForward());
			attabox->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

			attabox->AddComponent<AttaBoxComponent>()->Init(m_ParentObject,20,"Enemy");
			attabox->AddComponent<OBBCollision>()->Init(attabox->GetComponent<AttaBoxComponent>()->CollisionAction);
			attabox->SetTag("AttaBox");
			scene->AddGameObject(attabox, scene->PLAY_LAYER);
			m_AttackFlag = true;

		}


		if (GetKeyboardPress(DIK_LSHIFT) || IsButtonXinputPressed(0,XINPUT_GAMEPAD_RIGHT_SHOULDER))
		{
			if (m_Stamina <= 0)
			{
				m_Stamina = 0;
				m_DashFlag = false;
				m_MoveValue = 0.05f;
			}
			else
			{
				m_DashFlag = true;
				m_MoveValue = 0.1f;
			}

		}
		else if(!m_DodgeFlag)
		{
			m_DashFlag = false;
			m_MoveValue = 0.05f;
			m_Stamina++;
			if (m_Stamina > 150)
			{
				m_Stamina = 150;
			}
		}

		if (GetKeyboardTrigger(DIK_E) || IsButtonXinputTriggered(0, XINPUT_GAMEPAD_X))
		{
			if (m_HaveItem != nullptr && !m_UseItem && !m_HaveItem->GetComponent<ItemManager>()->GetListDraw())
			{
				m_HaveItem->GetComponent<ItemManager>()->UseItem();
				m_UseItem = true;
			}
		}

		if (GetKeyboardTrigger(DIK_SPACE) || IsButtonXinputTriggered(0, XINPUT_GAMEPAD_A))
		{
			if (m_Stamina > 20 && m_DodgeFlag == false)
			{
				m_DodgeFlag = true;
				m_ParentObject->GetComponent<Draw3DAnimetion>()->ResetFlame();

				m_Stamina -= 20;
				m_InvFlag = true;

			}
		}

	}
	else if(m_DamageFalg)
	{
		m_DamegeCnt++;
		if (m_DamegeCnt > 40 && m_Hp > 0)
		{
			m_DamageFalg = false;
			m_DamegeCnt = 0;
		}
		if (m_Hp <= 0)
		{
			GameObject* pDethText = scene->GetGameObject("DethText", scene->UI_LAYER);
			GameObject* pLosText = scene->GetGameObject("LosText", scene->UI_LAYER);
			GameObject* pBackText = scene->GetGameObject("BackText", scene->UI_LAYER);
			GameObject* pOverText = scene->GetGameObject("OverText", scene->UI_LAYER);

			pDethText->GetComponent<Transform>()->SetPlayFlag(true);

			if (pDethText->GetComponent<Transform>()->GetEndFlag())
			{
				m_ParentObject->GetComponent<Draw3DAnimetion>()->SetFlame(100);

				pLosText->GetComponent<Transform>()->SetPlayFlag(true);
			}

			if (pLosText->GetComponent<Transform>()->GetEndFlag())
			{
				if (Manager::GetDethCnt() == 2)
				{
					pOverText->GetComponent<Transform>()->SetPlayFlag(true);
				}
				else
				{
					pBackText->GetComponent<Transform>()->SetPlayFlag(true);
				}
			}

			m_ParentObject->SetAnimetionName("Die");
			m_ParentObject->SetNextAnimetionName("Die");
			m_DamageFalg = true;
			if (pBackText->GetComponent<Transform>()->GetEndFlag() || pOverText->GetComponent<Transform>()->GetEndFlag())
			{
				//死亡してからテキスト表示後シーン遷移
				m_SceneFlag = true;
			}

		}
	}

	if (m_UseItem)
	{
		m_UseItemCnt++;
		if (m_UseItemCnt > 30)
		{
			m_UseItemCnt = 0;
			m_UseItem = false;
		}
	}

	if (m_DodgeFlag)
	{
		m_ParentObject->SetAnimetionName("dodge");
		m_ParentObject->SetNextAnimetionName("dodge");
		if (m_InvCnt > 5)
		{
			m_InvFlag = false;
		}
		m_InvCnt++;
		if (m_ParentObject->SetPosTrans(-m_ParentObject->GetForward() * 3 + m_ParentObject->GetPosition(), m_ParentObject->GetPosition()))
		{
			m_DodgeFlag = false;
		}

	}

	if (m_AttackFlag)
	{
		m_ParentObject->SetAnimetionName("Attack");
		m_ParentObject->SetNextAnimetionName("Attack");

		if (m_AttackCnt == 1)
		{
			GameObject* attack = scene->GetGameObject("AttaBox", scene->PLAY_LAYER);
			attack->SetDestroy();
		}
		
		m_AttackCnt++;

		if(m_AttackCnt > 30)
		{

			m_AttackCnt = 0;
			m_AttackFlag = false;

		}
	}

	//赤ゲージがある場合
	if (m_RedHp > 0)
	{
		m_RecoveryCnt++;
		if (m_RecoveryCnt > 120)
		{
			m_RedHp--;
			m_Hp++;
			m_RecoveryCnt = 0;
		}
	}

	if (fabs(m_ParentObject->GetPosition().x) > 25 || fabs(m_ParentObject->GetPosition().z) > 25)
	{
		m_ParentObject->SetPosition(m_ParentObject->GetOldPosition());
	}

	m_ParentObject->SetPositionY(pField->GetComponent<MeshFieldDraw>()->GetHeight(m_ParentObject->GetPosition()));

	m_ParentObject->GetComponent<Draw3DAnimetion>()->SetBlendRate(m_BlendRate);
}


void Player::Draw()
{
#ifdef _DEBUG

	if (!m_ImGuiDrawFlag)
		return;

	ImGui::Begin("Player ImGui", &m_ImGuiDrawFlag);
	ImGui::Text("PlayerComplete");
	if (ImGui::TreeNode("PlayerPosition"))
	{
		ImGui::Text("X:%f Y:%f Z:%f",m_ParentObject->GetPosition().x,m_ParentObject->GetPosition().y,m_ParentObject->GetPosition().z);

		ImGui::TreePop();
		ImGui::Separator();
	}


	ImGui::End();

#endif // !_DEBUG

}


void Player::CollisionAction(GameObject* obj,std::string name)
{
	if (obj->GetTag() == "Wall")
	{
		Scene* scene = Manager::GetScene();

		GameObject* player = scene->GetGameObject("Player", scene->PLAY_LAYER);

		player->SetPosition(player->GetOldPosition());

		return;
	}

	if (obj->GetTag() == "Bullet")
	{
		Scene* scene = Manager::GetScene();

		GameObject* player = scene->GetGameObject("Player", scene->PLAY_LAYER);

		if (!player->GetComponent<Player>()->GetHitFlag())
		{
			player->AddPosition(obj->GetForward() * 3);
			if (fabs(player->GetPosition().x) > 25 || fabs(player->GetPosition().z) > 25)
			{
				player->SetPosition(player->GetOldPosition());
			}
			player->SetAnimetionName("Hit");
			player->SetNextAnimetionName("Hit");

			player->GetComponent<Player>()->LosHp(10);
			player->GetComponent<Player>()->SetRedHp(5);

			player->GetComponent<Player>()->SetHitFlag(true);
		}

		return;
	}

	if (obj->GetTag() == "Enemy")
	{
		Scene* scene = Manager::GetScene();

		GameObject* player = scene->GetGameObject("Player", scene->PLAY_LAYER);

		//player->m_Position = player->m_OldPosition;
	}

	if (obj->GetTag() == "attabox")
	{
		
		Scene* scene = Manager::GetScene();

		GameObject* player = scene->GetGameObject("Player", scene->PLAY_LAYER);
		GameObject* enemy = scene->GetGameObject("Enemy", scene->PLAY_LAYER);

		if (!player->GetComponent<Player>()->GetHitFlag() && !player->GetComponent<Player>()->GetInvFlag())
		{
			player->AddPosition(obj->GetForward() * 3);
			if (fabs(player->GetPosition().x) > 25 || fabs(player->GetPosition().z) > 25)
			{
				player->SetPosition(player->GetOldPosition());
			}
			player->SetAnimetionName("Hit");
			player->SetNextAnimetionName("Hit");

			if (enemy->GetComponent<Enemy>()->GetNowStatus() == 3)
			{
				player->GetComponent<Player>()->LosHp(30);
				player->GetComponent<Player>()->SetRedHp(15);

			}
			else
			{
				player->GetComponent<Player>()->LosHp(20);
				player->GetComponent<Player>()->SetRedHp(10);


			}

			player->GetComponent<Player>()->SetHitFlag(true);
		}
	}
}
