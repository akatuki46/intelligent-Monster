#include "main.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"

#include "GameObject.h"
#include "camera.h"
#include "model.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "input.h"
#include "Item.h"
#include "Sky.h"
#include "Game.h"
#include "GameClear.h"
#include "GameOver.h"
#include "ModelContainer.h"
#include "TextureContainer.h"
#include "Draw3D.h"
#include "Collision.h"
#include "Draw2D.h"
#include "Draw2DVer3D.h"
#include "BehaviorTree.h"
#include "AttackJudgment.h"
#include "AttackAction.h"
#include "DeffenceJudgment.h"
#include "DeffenceAction.h"	
#include <time.h>
#include "NaviMeshAI.h"
#include "LongRangeAT.h"
#include "LongRangeJM.h"
#include "CloseRangeAT.h"
#include "CloseRangeJM.h"
#include "ApproachAction.h"
#include "Ray.h"
#include "RayCollision.h"
#include "OBBCollision.h"
#include "WaitAction.h"
#include "WaitJudgment.h"
#include "TestComponent.h"
#include "Wave3D.h"
#include "Draw3DAnimetion.h"
#include "Motion.h"
#include "MeshFieldDraw.h"
#include "ChargeAction.h"
#include "ChargeJudgment.h"
#include "SizeDraw2D.h"
#include "HpComponent.h"
#include "MultiComponent.h"
#include "Draw2DChangePivot.h"
#include "Timer.h"
#include "MapComponent.h"
#include "ItemManager.h"
#include "NumberDraw2D.h"
#include "Transform.h"
#include "CloseDis.h"
#include "Particle.h"
#include "FadeDraw2D.h"
#include "Transition.h"
#include "MultiComponent.h"
#include "BaseCamp.h"

bool  Game::m_LoadFlag = false;
void Game::Load()
{
	ModelContainer::Instance().Load(ModelData::Tag::Game);
	TextureContainer::Load(TextureData::Tag::Game);

	m_LoadFlag = true;
}

void Game::Init()
{


	//Cameraのゲームオブジェクト生成
	GameObject* obj = new GameObject;
	obj->AddComponent<Camera>()->Init(false);
	obj->GetComponent<Camera>()->SetTestFlag(false);
	obj->SetTag("Camera");
	AddGameObject(obj, CAMERA_LAYER);



	//Enemyのゲームオブジェクト生成
	GameObject* enemy = new GameObject;
	enemy->SetPosition(D3DXVECTOR3(-1.0f, 2.0f, -6.0f));
	enemy->SetScale(D3DXVECTOR3(6.0f, 6.0f, 10.0f));
	enemy->AddComponent<Enemy>()->Init();
	enemy->AddComponent<Motion>()->Init();
	enemy->AddComponent<Ray>()->Init();
	enemy->AddComponent<OBBCollision>()->Init(enemy->GetComponent<Enemy>()->CollisionAction);
	enemy->AddComponent<RayCollision>()->Init(enemy->GetComponent<Enemy>()->RayCollisionAction);
	enemy->AddComponent<Particle>()->Init(true);
	enemy->GetComponent<Particle>()->SetInterval(20);
	enemy->GetComponent<Particle>()->SetAmount(20);
	enemy->GetComponent<Particle>()->SetLife(120);
	enemy->GetComponent<Particle>()->SetLoop(true);
	enemy->GetComponent<Particle>()->SetSize(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	enemy->GetComponent<Particle>()->SetColor(D3DXVECTOR4(0.0f, 1.0f, 1.0f,1.0f));
	enemy->GetComponent<Particle>()->SetType(0);

	enemy->SetTag("Enemy");
	if (Manager::GetEneHp() != 0)
	{
		enemy->GetComponent<Enemy>()->SetEnemyHp(Manager::GetEneHp());
	}
	AddGameObject(enemy, PLAY_LAYER);



	GameObject* field = new GameObject;
	field->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	field->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	field->AddComponent<MeshFieldDraw>()->Init(5);
	field->SetTag("Field");
	AddGameObject(field, PLAY_LAYER);


	GameObject* player = new GameObject;
	player->SetPosition(D3DXVECTOR3(-1.0f, 1.0f, 10.0f));
	player->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	player->AddComponent<Player>()->Init();
	player->AddComponent<Draw3DAnimetion>()->Init();
	player->AddComponent<OBBCollision>()->Init(player->GetComponent<Player>()->CollisionAction);
	player->SetTag("Player");
	player->SetAnimetionName("Idle");
	player->SetNextAnimetionName("Run");
	AddGameObject(player, PLAY_LAYER);



	GameObject* sky = new GameObject;
	sky->SetPosition(D3DXVECTOR3(0.0f, 20.0f, 0.0f));
	sky->SetScale(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	sky->SetCollsionNone(false);
	sky->AddComponent<Sky>()->Init();
	sky->AddComponent<Draw3D>()->Init();
	sky->SetTag("Sky");
	AddGameObject(sky, PLAY_LAYER);

	GameObject* wall1 = new GameObject;
	wall1->SetPosition(D3DXVECTOR3(-10.0f, 1.0f, 20.0f));
	wall1->SetScale(D3DXVECTOR3(4.0f, 3.0f, 2.0f));
	wall1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	wall1->AddComponent<Draw3D>()->Init();
	wall1->SetTag("Wall");
	AddGameObject(wall1, PLAY_LAYER);

	GameObject* wall2 = new GameObject;
	wall2->SetPosition(D3DXVECTOR3(0.0f, 1.0f, 5.0f));
	wall2->SetScale(D3DXVECTOR3(4.0f, 3.0f, 2.0f));
	wall2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	wall2->AddComponent<Draw3D>()->Init();
	wall2->SetTag("Wall");
	AddGameObject(wall2, PLAY_LAYER);

	GameObject* HpUI = new GameObject;
	HpUI->SetPosition(D3DXVECTOR3(150.0f, 45.0f, 0.0f));
	HpUI->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(1550.0f, 15.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 2);
	HpUI->SetTag("HPOverRay");
	AddGameObject(HpUI, UI_LAYER);

	GameObject* Hp = new GameObject;
	Hp->SetPosition(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	Hp->AddComponent<HpComponent>()->Init();
	Hp->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(100.0f, 100.0f, 0.0f),D3DXVECTOR4(0.0f,1.0f,0.0f,1.0f),2);
	Hp->SetTag("HP");
	Hp->SetParent("HPOverRay");
	AddGameObject(Hp, UI_LAYER);

	GameObject* StaminaUI = new GameObject;
	StaminaUI->SetPosition(D3DXVECTOR3(150.0f, 95.0f, 0.0f));
	StaminaUI->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(1550.0f, 15.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 2);
	StaminaUI->SetTag("StaminaOverRay");
	AddGameObject(StaminaUI, UI_LAYER);

	GameObject* Stamina = new GameObject;
	Stamina->SetPosition(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	Stamina->AddComponent<MultiComponent>()->Init();
	Stamina->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), 2);
	Stamina->SetTag("Stamina");
	Stamina->SetParent("StaminaOverRay");
	AddGameObject(Stamina, UI_LAYER);

	GameObject* WorldClock = new GameObject;
	WorldClock->SetPosition(D3DXVECTOR3(70.0f, 95.0f, 0.0f));
	WorldClock->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(150.0f, 150.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	WorldClock->SetTag("WorldClock");
	AddGameObject(WorldClock, UI_LAYER);


	GameObject* WorldTimer = new GameObject;
	WorldTimer->SetPosition(D3DXVECTOR3(70.0f, 95.0f, 0.0f));
	WorldTimer->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	WorldTimer->AddComponent<Timer>()->Init(54000);
	WorldTimer->AddComponent<MultiComponent>()->Init();
	WorldTimer->AddComponent<Draw2DChangePivot>()->Init(D3DXVECTOR3(10.0f, 50.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), 3);
	WorldTimer->SetTag("WorldTimer");
	//WorldTimer->SetParent("WorldClock");
	AddGameObject(WorldTimer, UI_LAYER);

	GameObject* MiniMapOverRay = new GameObject;
	MiniMapOverRay->SetPosition(D3DXVECTOR3(300.0f, 800.0f, 0.0f));
	MiniMapOverRay->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(350.0f, 350.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), 1);
	MiniMapOverRay->SetTag("None");
	AddGameObject(MiniMapOverRay, UI_LAYER);

	GameObject* MiniMap = new GameObject;
	MiniMap->SetPosition(D3DXVECTOR3(300.0f, 800.0f, 0.0f));
	MiniMap->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(300.0f, 300.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	MiniMap->AddComponent<MapComponent>()->Init();
	MiniMap->SetTag("MiniMap");
	AddGameObject(MiniMap,UI_LAYER);

	GameObject* ItemOverRay = new GameObject;
	ItemOverRay->SetPosition(D3DXVECTOR3(1700.0f, 850.0f, 0.0f));
	ItemOverRay->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	ItemOverRay->SetTag("ItemOverRay");
	AddGameObject(ItemOverRay, UI_LAYER);


	GameObject* ItemList = new GameObject;
	ItemList->SetPosition(D3DXVECTOR3(1700.0f, 850.0f, 0.0f));
	ItemList->AddComponent<ItemManager>()->Init();
	ItemList->SetTag("ItemManager");
	AddGameObject(ItemList, UI_LAYER);

	player->GetComponent<Player>()->SetItemInstance(ItemList);

	//ナビメッシュはこの時点でのフィールド上にあるオブジェクトを判定するので、
	//基本最後に追加する
	GameObject* Navi = new GameObject;
	Navi->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Navi->SetScale(D3DXVECTOR3(25.0f, 0.0f, 25.0f));
	Navi->AddComponent<NaviMeshAI>()->Init(50.0f,50.0f);
	Navi->SetTag("NaviMesh");
	AddGameObject(Navi, PLAY_LAYER);

	GameObject* DethText = new GameObject;
	DethText->SetPosition(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, -300.0f, 0.0f));
	DethText->AddComponent<MultiComponent>()->Init();
	DethText->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(400.0f, 100.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	DethText->AddComponent<Transform>()->Init(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, SCREEN_RESOLUTION_HEIGHT / 2, 0.0f), 4, 20, 20);
	DethText->GetComponent<Transform>()->SetPlayFlag(false);
	DethText->GetComponent<Transform>()->SetTransDire(1);
	DethText->SetTag("DethText");
	AddGameObject(DethText, UI_LAYER);

	GameObject* LosText = new GameObject;
	LosText->SetPosition(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, -300.0f, 0.0f));
	LosText->AddComponent<MultiComponent>()->Init();
	LosText->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(400.0f, 100.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	LosText->AddComponent<Transform>()->Init(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, SCREEN_RESOLUTION_HEIGHT / 2, 0.0f), 4, 20, 20);
	LosText->GetComponent<Transform>()->SetPlayFlag(false);
	LosText->GetComponent<Transform>()->SetTransDire(1);
	LosText->SetTag("LosText");
	AddGameObject(LosText, UI_LAYER);

	GameObject* BackText = new GameObject;
	BackText->SetPosition(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, -300.0f, 0.0f));
	BackText->AddComponent<MultiComponent>()->Init();
	BackText->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(400.0f, 100.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	BackText->AddComponent<Transform>()->Init(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, SCREEN_RESOLUTION_HEIGHT / 2, 0.0f), 4, 20, 20);
	BackText->GetComponent<Transform>()->SetPlayFlag(false);
	BackText->GetComponent<Transform>()->SetTransDire(1);
	BackText->SetTag("BackText");
	AddGameObject(BackText, UI_LAYER);

	GameObject* OverText = new GameObject;
	OverText->SetPosition(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, -300.0f, 0.0f));
	OverText->AddComponent<MultiComponent>()->Init();
	OverText->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(400.0f, 100.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	OverText->AddComponent<Transform>()->Init(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, SCREEN_RESOLUTION_HEIGHT / 2, 0.0f), 4, 20, 20);
	OverText->GetComponent<Transform>()->SetPlayFlag(false);
	OverText->GetComponent<Transform>()->SetTransDire(1);
	OverText->SetTag("OverText");
	AddGameObject(OverText, UI_LAYER);

	GameObject* TargetText = new GameObject;
	TargetText->SetPosition(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, -300.0f, 0.0f));
	TargetText->AddComponent<MultiComponent>()->Init();
	TargetText->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(450.0f, 100.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	TargetText->AddComponent<Transform>()->Init(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, SCREEN_RESOLUTION_HEIGHT / 2, 0.0f), 4, 20, 20);
	TargetText->GetComponent<Transform>()->SetPlayFlag(false);
	TargetText->GetComponent<Transform>()->SetTransDire(1);
	TargetText->SetTag("TargetText");
	AddGameObject(TargetText, UI_LAYER);

	GameObject* ClearText = new GameObject;
	ClearText->SetPosition(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, -300.0f, 0.0f));
	ClearText->AddComponent<MultiComponent>()->Init();
	ClearText->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(400.0f, 100.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	ClearText->AddComponent<Transform>()->Init(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, SCREEN_RESOLUTION_HEIGHT / 2, 0.0f), 4, 20, 20);
	ClearText->GetComponent<Transform>()->SetPlayFlag(false);
	ClearText->GetComponent<Transform>()->SetTransDire(1);
	ClearText->SetTag("ClearText");
	AddGameObject(ClearText, UI_LAYER);
}

void Game::Uninit()
{

	Scene::Uninit();//継承元クラスのメソッド呼び出し

	TextureContainer::Unload(TextureData::Tag::Game);
	ModelContainer::Instance().Unload(ModelData::Tag::Game);

	m_LoadFlag = false;
}

void Game::Update()
{
	Scene* scene = Manager::GetScene();

	Scene::Update();//継承元クラスのメソッド呼び出し

	GameObject* pPlayer = scene->GetGameObject("Player", scene->PLAY_LAYER);
	GameObject* pEnemy = scene->GetGameObject("Enemy", scene->PLAY_LAYER);
	GameObject* pTimer = scene->GetGameObject("WorldTimer", scene->UI_LAYER);

	if (pPlayer->GetComponent<Player>()->GetSceneFlag())
	{
		Manager::SetEneHp(pEnemy->GetComponent<Enemy>()->GetEnemyHp());
		Manager::AddDethCnt();
		if (pTimer->GetComponent<Timer>()->EndTimer() || Manager::GetDethCnt() > 2)
		{
			Manager::SetScene<GameOver>();
			Manager::SetEneHp(0);
			Manager::ResetDethCnt();
		}
		else
		{
			Manager::SetSceneLoad(BaseCamp::Load);
		}
		return;
	}

	if (pEnemy->GetComponent<Enemy>()->GetSceneFlag())
	{
		Manager::SetScene<GameClear>();
		return;
	}
}
