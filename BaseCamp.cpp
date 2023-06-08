#include "BaseCamp.h"
#include "TextureContainer.h"
#include "ModelContainer.h"
#include "Scene.h"
#include "manager.h"
#include "Player.h"
#include "HpComponent.h"
#include "SizeDraw2D.h"
#include "Timer.h"
#include "ItemManager.h"
#include "NumberDraw2D.h"
#include "Particle.h"
#include "MultiComponent.h"
#include "camera.h"
#include "Player.h"
#include "MeshFieldDraw.h"
#include "Draw3DAnimetion.h"
#include "OBBCollision.h"
#include "Sky.h"
#include "Draw3D.h"
#include "Transform.h"
#include "MapComponent.h"
#include "Draw2DChangePivot.h"
#include "Game.h"

bool  BaseCamp::m_LoadFlag = false;
void BaseCamp::Load()
{
	ModelContainer::Instance().Load(ModelData::Tag::Game);
	TextureContainer::Load(TextureData::Tag::Game);

	m_LoadFlag = true;
}

void BaseCamp::Init()
{

	//Cameraのゲームオブジェクト生成
	GameObject* obj = new GameObject;
	obj->AddComponent<Camera>()->Init(false);
	obj->GetComponent<Camera>()->SetTestFlag(false);
	obj->SetTag("Camera");
	AddGameObject(obj, CAMERA_LAYER);


	GameObject* field = new GameObject;
	field->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	field->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	field->AddComponent<MeshFieldDraw>()->Init(3);
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
	wall1->SetPosition(D3DXVECTOR3(-10.0f, 1.0f, -5.0f));
	wall1->SetScale(D3DXVECTOR3(10.0f, 10.0f, 20.0f));
	wall1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	wall1->AddComponent<Draw3D>()->Init();
	wall1->SetTag("Wall");
	AddGameObject(wall1, PLAY_LAYER);

	GameObject* wall2 = new GameObject;
	wall2->SetPosition(D3DXVECTOR3(10.0f, 1.0f, -5.0f));
	wall2->SetScale(D3DXVECTOR3(10.0f, 10.0f, 20.0f));
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
	Hp->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(100.0f, 100.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), 2);
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
	MiniMap->SetTag("BaseCampMap");
	AddGameObject(MiniMap, UI_LAYER);

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


	if (Manager::GetDethCnt() == 0)
	{
		GameObject* StartUI = new GameObject;
		StartUI->SetPosition(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, 300.0f, 0.0f));
		StartUI->AddComponent<MultiComponent>()->Init();
		StartUI->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(500.0f, 200.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
		StartUI->AddComponent<Transform>()->Init(D3DXVECTOR3(700.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 20, 0, 0.0f);
		StartUI->SetTag("Start");
		AddGameObject(StartUI, UI_LAYER);

		GameObject* StartTimerUI = new GameObject;
		StartTimerUI->SetPosition(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, -300.0f, 0.0f));
		StartTimerUI->AddComponent<MultiComponent>()->Init();
		StartTimerUI->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(400.0f, 100.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
		StartTimerUI->AddComponent<Transform>()->Init(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, SCREEN_RESOLUTION_HEIGHT/2, 0.0f), 4, 20, 20);
		StartTimerUI->GetComponent<Transform>()->SetPlayFlag(false);
		StartTimerUI->GetComponent<Transform>()->SetTransDire(1);
		StartTimerUI->SetTag("StartTimerUI");
		AddGameObject(StartTimerUI, UI_LAYER);
	}
	player->GetComponent<Player>()->SetItemInstance(ItemList);

}

void BaseCamp::Uninit()
{
	Scene::Uninit();//継承元クラスのメソッド呼び出し


	TextureContainer::Unload(TextureData::Tag::Game);
	ModelContainer::Instance().Unload(ModelData::Tag::Game);

	m_LoadFlag = false;

}

void BaseCamp::Update()
{
	Scene* scene = Manager::GetScene();

	Scene::Update();//継承元クラスのメソッド呼び出し

	GameObject* pPlayer = scene->GetGameObject("Player", scene->PLAY_LAYER);

	if (pPlayer->GetPosition().z < 0.0f)
	{
		Manager::SetSceneLoad(Game::Load);
	}

}


