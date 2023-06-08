#include "main.h"
#include "renderer.h"
#include "model.h"
#include "Enemy.h"
#include "ModelContainer.h"
#include "Player.h"
#include "Scene.h"
#include "Draw3D.h"
#include "Timer.h"
#include "Bullet.h"
#include "input.h"
#include "MeshFieldDraw.h"
#include "Motion.h"
#include "NomalState.h"
#include "Particle.h"
#include "AttaBoxComponent.h"
#include "OBBCollision.h"

//ビヘイビアツリー用ヘッダ
#include "ActionBase.h"
#include "LongRangeAT.h"
#include "LongRangeJM.h"
#include "CloseRangeAT.h"
#include "CloseRangeJM.h"
#include "BehaviorData.h"
#include "NodeBase.h"
#include "NaviMeshAI.h"
#include "CloseDis.h"
#include "ApproachAction.h"
#include "WaitAction.h"
#include "WaitJudgment.h"
#include "BehaviorTree.h"
#include "AttackJudgment.h"
#include "AttackAction.h"
#include "DeffenceJudgment.h"
#include "DeffenceAction.h"	
#include "ChargeAction.h"
#include "ChargeJudgment.h"
#include "MediumRangeJM.h"
#include "DieAction.h"
#include "DieJudgment.h"
#include "DownAction.h"
#include "DownJudgment.h"
#include "TackleAction.h"
#include "RushAction.h"
#include "Transform.h"

int cnt = 0;

void Enemy::Init()
{
	m_AiTree = new BehaviorTree;

	//親のセレクトルールに準拠
	m_AiTree->AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);

	m_AiTree->AddNode("Root", "Die", 4, BehaviorTree::SELECT_RULE::NON, DieJudgment::GetInstance(), DieAction::GetInstance());
	m_AiTree->AddNode("Root", "Down", 3, BehaviorTree::SELECT_RULE::NON, DownJudgment::GetInstance(), DownAction::GetInstance());

	//Rootを親としてAttackのノードを生成(シーケンスで選択)
	m_AiTree->AddNode("Root", "Attack", 2, BehaviorTree::SELECT_RULE::ON_OFF, AttackJudgment::GetInstance(), NULL);
	//Rootを親としてDiffenceのノードを生成 (行動データ持ち)
	m_AiTree->AddNode("Root", "Deffence", 1, BehaviorTree::SELECT_RULE::NON, DeffenceJudgment::GetInstance(), DeffenceAction::GetInstance());

	m_AiTree->AddNode("Attack", "LongRange", 1, BehaviorTree::SELECT_RULE::RANDOM, LongRangeJM::GetInstance(), NULL);
	m_AiTree->AddNode("LongRange", "LongRangeAT", 1, BehaviorTree::SELECT_RULE::SEQUENCE, NULL, NULL);
	m_AiTree->AddNode("LongRangeAT", "Action", 1, BehaviorTree::SELECT_RULE::NON, NULL, LongRangeAT::GetInstance());
	m_AiTree->AddNode("LongRangeAT", "Wait", 2, BehaviorTree::SELECT_RULE::NON, NULL, WaitAction::GetInstance());

	m_AiTree->AddNode("Attack", "MediumRange", 2, BehaviorTree::SELECT_RULE::RANDOM, MediumRangeJM::GetInstance(), NULL);
	m_AiTree->AddNode("MediumRange", "MediumRangeAT", 2, BehaviorTree::SELECT_RULE::SEQUENCE, NULL, NULL);
	m_AiTree->AddNode("MediumRangeAT", "Aooroach", 1, BehaviorTree::SELECT_RULE::NON, NULL, ApproachAction::GetInstance());
	m_AiTree->AddNode("MediumRangeAT", "Wait", 2, BehaviorTree::SELECT_RULE::NON, NULL, WaitAction().GetInstance());
	m_AiTree->AddNode("MediumRange", "Charge", 2, BehaviorTree::SELECT_RULE::NON, ChargeJudgment::GetInstance(), ChargeAction::GetInstance());


	m_AiTree->AddNode("Attack", "CloseRange", 3, BehaviorTree::SELECT_RULE::RANDOM, CloseRangeJM::GetInstance(), NULL);
	m_AiTree->AddNode("CloseRange", "CloseRangeAT", 1, BehaviorTree::SELECT_RULE::SEQUENCE, NULL, NULL);
	m_AiTree->AddNode("CloseRangeAT", "Action", 1, BehaviorTree::SELECT_RULE::NON, NULL, CloseRangeAT::GetInstance());
	m_AiTree->AddNode("CloseRangeAT", "Wait", 2, BehaviorTree::SELECT_RULE::NON, NULL, WaitAction::GetInstance());
	m_AiTree->AddNode("CloseRange", "Tackle", 2, BehaviorTree::SELECT_RULE::NON, NULL, TackleAction::GetInstance());
	m_AiTree->AddNode("CloseRange", "Rush", 3, BehaviorTree::SELECT_RULE::NON, NULL, RushAction::GetInstance());


	m_AiTree->AddNode("LongRange", "Approach", 2, BehaviorTree::SELECT_RULE::SEQUENCE, NULL, NULL);
	m_AiTree->AddNode("Approach", "Action", 1, BehaviorTree::SELECT_RULE::NON, NULL, ApproachAction::GetInstance());
	m_AiTree->AddNode("Approach", "Wait", 2, BehaviorTree::SELECT_RULE::NON, NULL, WaitAction().GetInstance());

	m_AiTree->AddNode("LongRange", "CloseDis", 3, BehaviorTree::SELECT_RULE::SEQUENCE, NULL, NULL);
	m_AiTree->AddNode("CloseDis", "Action", 3, BehaviorTree::SELECT_RULE::NON, NULL, CloseDis::GetInstance());
	m_AiTree->AddNode("CloseDis", "Wait", 3, BehaviorTree::SELECT_RULE::NON, NULL, WaitAction().GetInstance());

	m_AiTree->AddNode("LongRange", "Charge", 3, BehaviorTree::SELECT_RULE::NON, ChargeJudgment::GetInstance(), ChargeAction::GetInstance());



	m_BehaviorData = new BehaviorData();

	m_Action = new NomalState(m_ParentObject);

	m_Name = "Enemy";
}

void Enemy::Run()
{
	//実行ノードがNULLだったら
	if (m_ActiveNode == NULL)
	{
		m_ActiveNode = m_AiTree->Inference(m_ParentObject, m_BehaviorData);
	}

	//実行ノードがあったら
	if (m_ActiveNode != NULL)
	{
		//一つの行動を完了したらNULLを入れる（ビヘイビアツリーの特徴）
		m_ActiveNode = m_AiTree->Run(m_ParentObject, m_ActiveNode, m_BehaviorData);
	}
}

void Enemy::Update()
{
	Scene* scene = Manager::GetScene();
	GameObject* pPlayer = scene->GetGameObject("Player", scene->PLAY_LAYER);
	GameObject* pField = scene->GetGameObject("Field", scene->PLAY_LAYER);


	m_ParentObject->SetOldPosition(m_ParentObject->GetPosition());

	//Updateでビヘイビアツリーの一番上から実行
	Run();
	
	//ステートマシン実行
	m_Action->Action();

	//ステートアップデート
	SituationUpdate();

	//プレイヤーのインスタンスがあるか
	if (pPlayer != nullptr)
	{

		//プレイヤーとの距離
		D3DXVECTOR3 direction = pPlayer->GetPosition() - m_ParentObject->GetPosition();
		m_Length = D3DXVec3Length(&direction);


		//プレイヤーをまだ見つけていないなら
		if (m_FindPlayer == NULL && !m_ActionFlag[Deffence_Judgment] && m_PlayerPos == D3DXVECTOR3(0.0f,0.0f,0.0f))
		{
			//内積計算
			float dot = 0.0f;
			D3DXVECTOR3 forward = m_ParentObject->GetForward();
			dot = D3DXVec3Dot(&forward, &direction);

			//内積計算で２以上、距離10以内でプレイヤーを発見
			if ((dot > 3.0f && m_Length < 15.0f) || m_LastAttack)
			{
				m_FindPlayer = pPlayer;
			}
		}
		else if(!m_ActionFlag[Deffence_Judgment] && !m_PlayMotion && m_PlayerPos == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
		{
			//プレイヤーのほうを向く処理
			float angle = atan2f(m_ParentObject->GetPosition().z - pPlayer->GetPosition().z,
				m_ParentObject->GetPosition().x - pPlayer->GetPosition().x);

			m_ParentObject->SetRotation(D3DXVECTOR3(0.0f, -angle - 1.5f,0.0f));
		}
	}


	//衝突後一秒経ったら見つけたプレイヤーをNULLに
	if (m_CollisionFlag)
	{
		cnt++;
		m_FindPlayer = nullptr;
		if (cnt >= 60)
		{
			m_CollisionFlag = false;
			cnt = 0;
		}
	}
	
	if (m_DamageCnt > 0)
	{
		if (m_DamageCnt > m_FearLimit)
		{
			m_DamageCnt = 0;
			m_FearFlag = true;
			m_FearLimit *= 1.2f;
		}

		m_FearCnt++;
		if (m_FearCnt > 90)
		{

			m_DamageCnt -= 40;
			m_LastAttack = false;
			m_FearCnt = 0;
		}
		if (m_LastAttack)
		{
			m_FearCnt = 0;
			m_LastAttack = false;
		}

	}

	m_ParentObject->SetPositionY(pField->GetComponent<MeshFieldDraw>()->GetHeight(m_ParentObject->GetPosition()) + 1.0f);

	m_NowStatus = m_Action->GetStatus();
}

void Enemy::Draw()
{
#ifdef _DEBUG

	if (!m_ImGuiDrawFlag)
		return;

	ImGui::Begin("Enemy ImGui", &m_ImGuiDrawFlag);
	if (ImGui::TreeNode("EnemyBehavior"))
	{
		ImGui::Checkbox("Attack_Judgment", &m_ActionFlag[Attack_Judgment]);
		ImGui::Checkbox("Charge_Judgment", &m_ActionFlag[Charge_Judgment]);
		ImGui::Checkbox("CloseRange_Judgment", &m_ActionFlag[CloseRange_Judgment]);
		ImGui::Checkbox("Deffence_Judgment", &m_ActionFlag[Deffence_Judgment]);
		ImGui::Checkbox("LongRange_Judgment", &m_ActionFlag[LongRange_Judgment]);
		ImGui::Separator();
		ImGui::TreePop();
	}

	if(ImGui::TreeNode("EnemyState"))
	{
		ImGui::RadioButton("Normal_State", &m_StateFlag[Normal_Status]);
		ImGui::RadioButton("Charge_State", &m_StateFlag[Charge_Status]);
		ImGui::RadioButton("SuperCharge_State", &m_StateFlag[SuperCharge_Status]);

		ImGui::Separator();
		ImGui::TreePop();

	}
	if (m_ActionFlag[Attack_Judgment])
	{
		ImGui::Text("Attack_Judgment");
	}
	if (m_ActionFlag[Charge_Judgment])
	{
		ImGui::Text("Charge_Judgment");
	}
	if (m_ActionFlag[CloseRange_Judgment])
	{
		ImGui::Text("CloseRange_Judgment");
	}
	if (m_ActionFlag[Deffence_Judgment])
	{
		ImGui::Text("Deffence_Judgment");
	}
	if (m_ActionFlag[LongRange_Judgment])
	{
		ImGui::Text("LongRange_Judgment");
	}

	ImGui::Text("m_DamageCnt : %d",m_DamageCnt);



	if (m_FindPlayer)
	{
		ImGui::Text("PlayerFind");
	}

	ImGui::Text("CurrentHP:%d", m_HP);

	ImGui::End();

#endif // !_DEBUG

}

//何かと衝突したときの処理
void Enemy::CollisionAction(GameObject* obj, std::string name)
{
	Scene* scene = Manager::GetScene();

	GameObject* enemy = scene->GetGameObject("Enemy", scene->PLAY_LAYER);

	//プレイヤーと衝突したら
	if (obj->GetTag() == "Player")
	{

		enemy->SetPosition(enemy->GetOldPosition());
		enemy->GetComponent<Enemy>()->m_CollisionFlag = true;
	}


	//if (obj->GetTag() == "Wall")
	//{
	//	enemy->m_Position = enemy->m_OldPosition;

	//	enemy->GetComponent<Enemy>()->m_WallCollision = true;

	//}
	//else
	//{
	//	enemy->GetComponent<Enemy>()->m_WallCollision = false;

	//}

}
//現状見失って直進するだけ
void Enemy::RayCollisionAction(GameObject* obj)
{
	Scene* scene = Manager::GetScene();

	GameObject* enemy = scene->GetGameObject("Enemy", scene->PLAY_LAYER);

	if (obj->GetTag() == "Wall")
	{

		if (enemy->GetComponent<Enemy>()->FindPlayer())
		{
			//プレイヤーが壁に隠れたときに最後に見た位置まで移動する
			enemy->GetComponent<Enemy>()->SetPlayerPos(enemy->GetComponent<Enemy>()->m_FindPlayer->GetPosition());

			enemy->GetComponent<Enemy>()->m_FindPlayer = nullptr;
		}
		enemy->GetComponent<Enemy>()->m_RayCollision = true;

		//MessageBox(NULL, TEXT("壁判定"),
		//	TEXT("メッセージボックス"), MB_APPLMODAL);
	
		//enemy->m_Position = enemy->m_OldPosition;
		//enemy->GetComponent<Enemy>()->m_CollisionFlag = true;

	}
	else
	{
		enemy->GetComponent<Enemy>()->m_RayCollision = false;

	}


}

//ステートが切り替わったときに実行
void Enemy::SituationUpdate()
{
	if (m_NextAction)
	{
		delete m_Action;
		m_Action = m_NextAction;
		m_NextAction = nullptr;
	}
}

void Enemy::Uninit()
{
	delete m_BehaviorData;
}

//攻撃行動
ActionBase::STATE Enemy::Attack()
{
	Scene* scene = Manager::GetScene();
	GameObject* Navi = scene->GetGameObject("NaviMesh", scene->PLAY_LAYER);
	m_ParentObject->GetComponent<Motion>()->SetMotion("Run");

	if (m_FindPlayer == NULL)
	{
		return ActionBase::STATE::COMPLETE;
	}

	m_ParentObject->AddPositionX(-(cosf(m_ParentObject->GetRotation().y + 1.5f) * 0.1f));
	m_ParentObject->AddPositionZ(sinf(m_ParentObject->GetRotation().y + 1.5f) * 0.1f);

	if (!Navi->GetComponent<NaviMeshAI>()->CollisionNavi(m_ParentObject))
	{
		m_ParentObject->SetPosition(m_ParentObject->GetOldPosition());
		m_FindPlayer = nullptr;
		return ActionBase::STATE::COMPLETE;
	}

	if (m_CollisionFlag)
	{
		m_FindPlayer = nullptr;
		return ActionBase::STATE::COMPLETE;
	}


	return ActionBase::STATE::RUN;
}

//防御行動
ActionBase::STATE Enemy::Deffence()
{

	Scene* scene = Manager::GetScene();
	m_ParentObject->GetComponent<Motion>()->SetMotion("Walk");

	if (m_FindPlayer != NULL)
	{
		FlagOff(DiffenceStart);
		return ActionBase::STATE::COMPLETE;
	}

	//Diffence行動開始だったら
	if (!FlagCheck(DiffenceStart))
	{
		GameObject* Navi = scene->GetGameObject("NaviMesh", scene->PLAY_LAYER);
		D3DXVECTOR3 aa = D3DXVECTOR3(Manager::randomint(-25, 25), 0.0f, Manager::randomint(-25, 25));

		//プレイヤーを見失ったら実行
		if (m_PlayerPos != D3DXVECTOR3(0.0f,0.0f,0.0f))
		{
			aa = m_PlayerPos;
		}

		m_AstarPosition = Navi->GetComponent<NaviMeshAI>()->AStar(m_ParentObject->GetPosition(),aa);

		FlagOn(DiffenceStart);
	}

	if (m_LastAttack && m_PlayerPos != D3DXVECTOR3(0.0f,0.0f,0.0f))
	{
		m_PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		FlagOff(DiffenceStart);
		m_AstarPosition.clear();
		return ActionBase::STATE::COMPLETE;
	}

	if (!m_AstarPosition.empty())
	{
		float angle = atan2f(m_ParentObject->GetPosition().z - m_AstarPosition.front().z, m_ParentObject->GetPosition().x - m_AstarPosition.front().x);

		m_ParentObject->SetRotationY(-angle - 1.5f);

		D3DXVECTOR3 PosDis = D3DXVECTOR3(m_AstarPosition.front().x - m_ParentObject->GetPosition().x, 0.0f, m_AstarPosition.front().z - m_ParentObject->GetPosition().z);

		float PosLen = D3DXVec3Length(&PosDis);

		//2点間の距離が0.1以下なら
		if (PosLen <= 0.1f)
		{
			m_ParentObject->SetPosition(D3DXVECTOR3(m_AstarPosition.front().x, m_ParentObject->GetPosition().y, m_AstarPosition.front().z));
			m_AstarPosition.pop_front();
		}
		else
		{
			D3DXVec3Normalize(&PosDis, &PosDis);

			//移動処理
			m_ParentObject->AddPositionX(PosDis.x * 0.05f);
			m_ParentObject->AddPositionZ(PosDis.z * 0.05f);
		}


	}
	else
	{
		m_PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		FlagOff(DiffenceStart);
		m_AstarPosition.clear();
		return ActionBase::STATE::COMPLETE;
	}

	return ActionBase::STATE::RUN;

}

//遠距離攻撃
ActionBase::STATE Enemy::LongRangeAT()
{
	//とりあえず玉発射
	Scene* scene = Manager::GetScene();
	if (!FlagCheck(LongRangeStart))
	{
		m_ParentObject->GetComponent<Motion>()->SetMotion("Shot");
		m_ParentObject->GetComponent<Motion>()->SetMotionEnd(false);
		DoOnce = false;

		FlagOn(LongRangeStart);
	}

	if (m_ParentObject->GetComponent<Motion>()->GetMotionEnd() && !DoOnce &&
		m_ParentObject->GetComponent<Motion>()->GetMotionName() == "Shot")
	{
		GameObject* obj = new GameObject;
		obj->SetPosition(m_ParentObject->GetPosition() + (m_ParentObject->GetRight() * 2));
		obj->SetRotation(m_ParentObject->GetRotation());
		obj->SetVelocity(m_ParentObject->GetForward() * 0.1f);
		obj->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		obj->AddComponent<Bullet>()->Init();
		obj->AddComponent<Draw3D>()->Init();
		obj->SetTag("Bullet");
		scene->AddGameObject(obj, Scene::PLAY_LAYER);

		if (m_Action->GetStatus() == Charge_Status || m_Action->GetStatus() == SuperCharge_Status)
		{
			GameObject* obj = new GameObject;
			obj->SetPosition(m_ParentObject->GetPosition() + (m_ParentObject->GetRight() * 3));
			obj->SetRotation(m_ParentObject->GetRotation());
			obj->SetVelocity(m_ParentObject->GetForward() * 0.2f);
			obj->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
			obj->AddComponent<Bullet>()->Init();
			obj->AddComponent<Draw3D>()->Init();
			obj->SetTag("Bullet");
			scene->AddGameObject(obj, Scene::PLAY_LAYER);
		}

		GameObject* time = new GameObject;
		time->AddComponent<Timer>()->Init(10);
		time->SetTag("LongTimer");
		scene->AddGameObject(time, scene->PLAY_LAYER);
		DoOnce = true;
	}

	GameObject* timer = scene->GetGameObject("LongTimer", scene->PLAY_LAYER);

	if (timer != nullptr && timer->GetComponent<Timer>()->EndTimer())
	{
		timer->SetDestroy();
		FlagOff(LongRangeStart);
		return ActionBase::STATE::COMPLETE;

	}

	return ActionBase::STATE::RUN;


}

//近距離攻撃
ActionBase::STATE Enemy::CloseRangeAT()
{
	Scene* scene = Manager::GetScene();

	if (!FlagCheck(CloseRangeATStart))
	{
		m_ParentObject->GetComponent<Motion>()->SetMotion("OTE");
		m_ParentObject->GetComponent<Motion>()->SetMotionEnd(false);

		GameObject* time = new GameObject;
		time->AddComponent<Timer>()->Init(70);
		time->SetTag("CloseTimer");
		scene->AddGameObject(time, scene->PLAY_LAYER);
		DoOnce = false;
		m_PlayMotion = true;
		FlagOn(CloseRangeATStart);
	}

	if (m_ParentObject->GetComponent<Motion>()->GetMotionEnd() && !DoOnce &&
		m_ParentObject->GetComponent<Motion>()->GetMotionName() == "OTE")
	{
		GameObject* attabox = new GameObject;
		attabox->SetRotation(m_ParentObject->GetRotation());
		attabox->SetPosition(m_ParentObject->GetPosition() + m_ParentObject->GetForward() * 4);
		attabox->SetScale(D3DXVECTOR3(2.0f, 1.0f, 5.5f));
		attabox->SetTag("attabox");
		scene->AddGameObject(attabox, scene->PLAY_LAYER);
		DoOnce = true;

		if (m_Action->GetStatus() == Charge_Status || m_Action->GetStatus() == SuperCharge_Status)
		{
			m_ParentObject->GetComponent<Motion>()->SetMotion("LeftOte");
			m_ParentObject->GetComponent<Motion>()->SetMotionEnd(false);

			GameObject* timer = scene->GetGameObject("CloseTimer", scene->PLAY_LAYER);
			timer->GetComponent<Timer>()->SetTime(100);
			DoOnce = false;
		}
	}

	if (m_ParentObject->GetComponent<Motion>()->GetMotionEnd() && !DoOnce &&
		m_ParentObject->GetComponent<Motion>()->GetMotionName() == "LeftOte")
	{
		GameObject* attabox = new GameObject;
		attabox->SetRotation(m_ParentObject->GetRotation());
		attabox->SetPosition(m_ParentObject->GetPosition() + m_ParentObject->GetForward() * 5);
		attabox->SetScale(D3DXVECTOR3(2.0f, 1.0f, 5.0f));
		attabox->SetTag("attabox");
		scene->AddGameObject(attabox, scene->PLAY_LAYER);
		DoOnce = true;
	}


	GameObject* timer = scene->GetGameObject("CloseTimer", scene->PLAY_LAYER);
	GameObject* attabox = scene->GetGameObject("attabox", scene->PLAY_LAYER);

	if(timer != nullptr && timer->GetComponent<Timer>()->EndTimer())
	{
		m_PlayMotion = false;
		if (attabox != nullptr)
		{
			attabox->SetDestroy();
		}
		m_ParentObject->SetRotationX(m_KeepRotX);
		FlagOff(CloseRangeATStart);
		if (timer != nullptr)
		{
			timer->SetDestroy();

		}
		DoOnce = false;

		return ActionBase::STATE::COMPLETE;

	}

	return ActionBase::STATE::RUN;
}

//距離詰め
ActionBase::STATE Enemy::ApproachAction()
{
	Scene* scene = Manager::GetScene();
	GameObject* Navi = scene->GetGameObject("NaviMesh", scene->PLAY_LAYER);
	GameObject* pPlayer = scene->GetGameObject("Player", scene->PLAY_LAYER);

	m_ParentObject->GetComponent<Motion>()->SetMotion("Run");

	if (m_FindPlayer == NULL)
	{
		return ActionBase::STATE::COMPLETE;
	}

	if (!FlagCheck(ApproachActionStart))
	{
		GameObject* time = new GameObject;
		time->AddComponent<Timer>()->Init(90);
		time->SetTag("ApproTimer");
		scene->AddGameObject(time, scene->PLAY_LAYER);

		FlagOn(ApproachActionStart);

	}

	GameObject* timer = scene->GetGameObject("ApproTimer", scene->PLAY_LAYER);

	D3DXVECTOR3 PosDis = D3DXVECTOR3(pPlayer->GetPosition().x - m_ParentObject->GetPosition().x, 0.0f, pPlayer->GetPosition().z - m_ParentObject->GetPosition().z);

	float PosLen = D3DXVec3Length(&PosDis);

	if (PosLen <= 4.5f || (timer != nullptr && timer->GetComponent<Timer>()->EndTimer()))
	{
		if (timer != nullptr)
		{
			timer->SetDestroy();
		}
		FlagOff(CloseDisStart);
		return ActionBase::STATE::COMPLETE;

	}
	else
	{
		D3DXVec3Normalize(&PosDis, &PosDis);

		//移動処理
		m_ParentObject->AddPositionX(PosDis.x * 0.1f);
		m_ParentObject->AddPositionZ(PosDis.z * 0.1f);

	}

	//ナビメッシュ内から出たら
	if (!Navi->GetComponent<NaviMeshAI>()->CollisionNavi(m_ParentObject) && timer!= nullptr)
	{
		m_ParentObject->SetPosition(m_ParentObject->GetOldPosition());
		m_FindPlayer = nullptr;
		timer->SetDestroy();
		FlagOff(ApproachActionStart);
		return ActionBase::STATE::COMPLETE;
	}
	else if(timer != nullptr) //いるならこっちの処理
	{
		//タイマー終わったら
		if (timer->GetComponent<Timer>()->EndTimer())
		{
			m_ParentObject->SetPosition(m_ParentObject->GetOldPosition());
			//m_FindPlayer = nullptr;
			timer->SetDestroy();
			FlagOff(ApproachActionStart);
			return ActionBase::STATE::COMPLETE;
		}
	}

	if (m_CollisionFlag)
	{
		m_FindPlayer = nullptr;
		return ActionBase::STATE::COMPLETE;
	}


	return ActionBase::STATE::RUN;
}

ActionBase::STATE Enemy::Wait()
{
	Scene* scene = Manager::GetScene();
	m_ParentObject->GetComponent<Motion>()->SetMotion("Idle");

	//if (m_WallCollision)
	//{
		if (!FlagCheck(WaitStart))
		{
			GameObject* time = new GameObject;
			time->AddComponent<Timer>()->Init(60);
			time->SetTag("WaitTimer");
			scene->AddGameObject(time, scene->PLAY_LAYER);

			FlagOn(WaitStart);

		}

		GameObject* timer = scene->GetGameObject("WaitTimer", scene->PLAY_LAYER);

		if (timer != nullptr && timer->GetComponent<Timer>()->EndTimer())
		{
			FlagOff(WaitStart);
			timer->SetDestroy();
			return ActionBase::STATE::COMPLETE;
		}
		else if (timer != nullptr)
		{
			m_ParentObject->SetPosition(m_ParentObject->GetOldPosition());

		}
	//}

	return ActionBase::STATE::RUN;
}

ActionBase::STATE Enemy::Charge()
{
	if (m_ChargeFlag == 0)
	{
		m_ParentObject->GetComponent<Motion>()->SetMotion("Charge");
		m_ParentObject->GetComponent<Motion>()->SetMotionEnd(false);

		m_ParentObject->GetComponent<Particle>()->SetUse(true);
		m_ChargeFlag++;
	}

	if (m_ParentObject->GetComponent<Motion>()->GetMotionEnd() && 
		m_ParentObject->GetComponent<Motion>()->GetMotionName() == "Charge")
	{
		m_ParentObject->GetComponent<Particle>()->SetUse(false);

		m_ChargeFlag = 0;
		m_ChargeCnt++;
		return ActionBase::STATE::COMPLETE;
	}


	return ActionBase::STATE::RUN;
}

ActionBase::STATE Enemy::CloseDis()
{
	Scene* scene = Manager::GetScene();
	GameObject* Navi = scene->GetGameObject("NaviMesh", scene->PLAY_LAYER);
	GameObject* pPlayer = scene->GetGameObject("Player", scene->PLAY_LAYER);

	if (!FlagCheck(CloseDisStart))
	{

		m_ParentObject->GetComponent<Motion>()->SetMotion("Jump");
		m_ParentObject->GetComponent<Motion>()->SetMotionEnd(false);
		DoOnce = false;
		DoOnce2 = false;
		FlagOn(CloseDisStart);
	}
	if (m_FindPlayer == NULL)
	{
		FlagOff(CloseDisStart);
		DoOnce = false;

		return ActionBase::STATE::COMPLETE;
	}

	if (!DoOnce)
	{
		GameObject* time = new GameObject;
		time->AddComponent<Timer>()->Init(90);
		time->SetTag("CloseDisTimer");
		scene->AddGameObject(time, scene->PLAY_LAYER);

		DoOnce = true;

	}

	GameObject* pTimer = scene->GetGameObject("CloseDisTimer", scene->PLAY_LAYER);

	D3DXVECTOR3 PosDis = D3DXVECTOR3(pPlayer->GetPosition().x - m_ParentObject->GetPosition().x, 0.0f, pPlayer->GetPosition().z - m_ParentObject->GetPosition().z);

	float PosLen = D3DXVec3Length(&PosDis);

	//2点間の距離が2以下なら
	//飛び掛かりモーションを実行中（End前）に距離が5以下になる可能性ある
	if (PosLen <= 5.0f || (pTimer != nullptr && pTimer->GetComponent<Timer>()->EndTimer()))
	{		
		if (m_ParentObject->GetComponent<Motion>()->GetMotionEnd() &&
			m_ParentObject->GetComponent<Motion>()->GetMotionName() == "Land")
		{
			if (!DoOnce2)
			{
				GameObject* attabox = new GameObject;
				attabox->SetRotation(m_ParentObject->GetRotation());
				attabox->SetPosition(m_ParentObject->GetPosition() + m_ParentObject->GetForward() * 4);
				attabox->SetScale(D3DXVECTOR3(2.0f, 1.0f, 2.5f));
				attabox->SetTag("attabox");
				scene->AddGameObject(attabox, scene->PLAY_LAYER);
				DoOnce2 = true;

			}
			else
			{
				GameObject* attabox = scene->GetGameObject("attabox", scene->PLAY_LAYER);

				if (pTimer != nullptr)
				{
					pTimer->SetDestroy();
				}

				attabox->SetDestroy();
				

				FlagOff(CloseDisStart);
				DoOnce = false;
				DoOnce2 = false;
				return ActionBase::STATE::COMPLETE;
			}
		}

		m_ParentObject->GetComponent<Motion>()->SetMotion("Land");

	}
	else if(m_ParentObject->GetComponent<Motion>()->GetMotionName() != "Land")
	{
		D3DXVec3Normalize(&PosDis, &PosDis);

		//移動処理
		m_ParentObject->AddPositionX(PosDis.x * 0.1f);
		m_ParentObject->AddPositionZ(PosDis.z * 0.1f);
	}



	return ActionBase::STATE::RUN;
}

ActionBase::STATE Enemy::Die()
{
	Scene* scene = Manager::GetScene();
	GameObject* pTargetText = scene->GetGameObject("TargetText", scene->UI_LAYER);
	GameObject* pClearText = scene->GetGameObject("ClearText", scene->UI_LAYER);

	if (!FlagCheck(DieActionStart))
	{
		m_ParentObject->GetComponent<Motion>()->SetMotion("Die");
		m_ParentObject->GetComponent<Motion>()->SetMotionEnd(false);
		FlagOn(DieActionStart);
		pTargetText->GetComponent<Transform>()->SetPlayFlag(true);
		m_MotionStartFlag = true;
		m_PlayMotion = true;
	}

	if (pTargetText->GetComponent<Transform>()->GetEndFlag())
	{
		pClearText->GetComponent<Transform>()->SetPlayFlag(true);

	}

	if (m_ParentObject->GetComponent<Motion>()->GetMotionEnd() &&
		m_ParentObject->GetComponent<Motion>()->GetMotionName() == "Die")
	{
		m_SceneFlag = true;
		m_PlayMotion = false;
		FlagOff(DieActionStart);
		return ActionBase::STATE::COMPLETE;

	}
	return ActionBase::STATE::RUN;
}

ActionBase::STATE Enemy::Down()
{
	if (!FlagCheck(DownActionStart))
	{
		m_ParentObject->GetComponent<Motion>()->SetMotion("Fear");
		m_ParentObject->GetComponent<Motion>()->SetMotionEnd(false);
		FlagOn(DownActionStart);
		m_PlayMotion = true;
	}
	if (m_ParentObject->GetComponent<Motion>()->GetMotionEnd() &&
		m_ParentObject->GetComponent<Motion>()->GetMotionName() == "Fear")
	{
		m_FearFlag = false;
		m_PlayMotion = false;
		FlagOff(DownActionStart);
		return ActionBase::STATE::COMPLETE;


	}
	return ActionBase::STATE::RUN;
}

ActionBase::STATE Enemy::Tackle()
{
	Scene* scene = Manager::GetScene();

	if (!FlagCheck(TackleActionStart))
	{
		m_ParentObject->GetComponent<Motion>()->SetMotion("Tackle");
		m_ParentObject->GetComponent<Motion>()->SetMotionEnd(false);
		FlagOn(TackleActionStart);
		m_PlayMotion = true;

	}
	
	if (m_ParentObject->GetComponent<Motion>()->GetMotionPoint() &&
		m_ParentObject->GetComponent<Motion>()->GetMotionName() == "Tackle")
	{
		GameObject* attabox = new GameObject;
		attabox->SetRotation(m_ParentObject->GetRotation());
		attabox->SetPosition(m_ParentObject->GetPosition() + m_ParentObject->GetForward() * 4);
		attabox->SetScale(D3DXVECTOR3(1.0f, 1.0f, 2.5f));
		attabox->SetTag("attabox");
		scene->AddGameObject(attabox, scene->PLAY_LAYER);

	}


	if (m_ParentObject->GetComponent<Motion>()->GetMotionEnd() &&
		m_ParentObject->GetComponent<Motion>()->GetMotionName() == "Tackle")
	{
		GameObject* attabox = scene->GetGameObject("attabox", scene->PLAY_LAYER);
		if (attabox != nullptr)
		{
			attabox->SetDestroy();
		}

		m_FearFlag = false;
		m_PlayMotion = false;
		FlagOff(TackleActionStart);
		return ActionBase::STATE::COMPLETE;


	}

	return ActionBase::STATE::RUN;
}

ActionBase::STATE Enemy::Rush()
{
	Scene* scene = Manager::GetScene();

	if (!FlagCheck(RushActionStart))
	{
		m_ParentObject->GetComponent<Motion>()->SetMotion("Run");

		m_MotionPos = m_ParentObject->GetPosition() + m_ParentObject->GetForward() * 15;
		m_PlayMotion = true;

		GameObject* attabox = new GameObject;
		attabox->SetRotation(m_ParentObject->GetRotation());
		attabox->SetPosition(m_ParentObject->GetPosition());
		attabox->SetScale(D3DXVECTOR3(2.0f, 1.0f, 2.5f));
		attabox->SetTag("attabox");
		scene->AddGameObject(attabox, scene->PLAY_LAYER);

		FlagOn(RushActionStart);
	}

	D3DXVECTOR3 PosDis = D3DXVECTOR3(m_MotionPos.x - m_ParentObject->GetPosition().x, 0.0f, m_MotionPos.z - m_ParentObject->GetPosition().z);

	float PosLen = D3DXVec3Length(&PosDis);

	GameObject* attabox = scene->GetGameObject("attabox", scene->PLAY_LAYER);
	if (attabox != nullptr)
	{
		attabox->SetPosition(m_ParentObject->GetPosition());
	}

	if (PosLen <= 0.1f)
	{
		attabox->SetDestroy();
		FlagOff(RushActionStart);
		m_PlayMotion = false;
		return ActionBase::STATE::COMPLETE;
	}
	else
	{
		D3DXVec3Normalize(&PosDis, &PosDis);

		//移動処理
		m_ParentObject->AddPositionX(PosDis.x * 0.15f);
		m_ParentObject->AddPositionZ(PosDis.z * 0.15f);
	}

	return ActionBase::STATE::RUN;
}
