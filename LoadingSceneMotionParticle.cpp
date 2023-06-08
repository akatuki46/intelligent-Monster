#include "Draw2DChangePivot.h"
#include "Scene.h"
#include "manager.h"
#include "Game.h"
#include <thread>
#include "MultiComponent.h"
#include "TextureContainer.h"
#include "TestScene.h"
#include "Transform.h"
#include "Draw2D.h"
#include "LoadingSceneMotionParticle.h"

void LoadingSceneMotionParticle::Init()
{
	TextureContainer::Load(TextureData::Tag::Loading);
	TextureContainer::Load(TextureData::Tag::Title);


	std::thread th(TestScene::Load);

	th.detach();

	GameObject* titlelogo = new GameObject;
	titlelogo->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	titlelogo->AddComponent<Draw2D>()->Init(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH, SCREEN_RESOLUTION_HEIGHT, 0.0f), 1);
	titlelogo->SetTag("title");
	AddGameObject(titlelogo, UI_LAYER);

	GameObject* Loading_N = new GameObject;
	Loading_N->SetPosition(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	Loading_N->AddComponent<Draw2DChangePivot>()->Init(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	Loading_N->AddComponent<Transform>()->Init(D3DXVECTOR3(0.0f, 0.0f, 360.0f), 3, 30, 30, 0.0f);
	Loading_N->SetTag("Loading_N");
	AddGameObject(Loading_N, UI_LAYER);

	GameObject* Loading_O = new GameObject;
	Loading_O->SetPosition(D3DXVECTOR3(300.0f, 100.0f, 0.0f));
	Loading_O->AddComponent<Draw2DChangePivot>()->Init(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	Loading_O->AddComponent<Transform>()->Init(D3DXVECTOR3(0.0f, 0.0f, 360.0f), 3, 30, 30, 0.0f);
	Loading_O->SetTag("Loading_O");
	AddGameObject(Loading_O, UI_LAYER);

	GameObject* Loading_W = new GameObject;
	Loading_W->SetPosition(D3DXVECTOR3(500.0f, 100.0f, 0.0f));
	Loading_W->AddComponent<Draw2DChangePivot>()->Init(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	Loading_W->AddComponent<Transform>()->Init(D3DXVECTOR3(0.0f, 0.0f, 360.0f), 3, 30, 30, 0.0f);
	Loading_W->SetTag("Loading_W");
	AddGameObject(Loading_W, UI_LAYER);

	GameObject* Loading_L = new GameObject;
	Loading_L->SetPosition(D3DXVECTOR3(600.0f, 900.0f, 0.0f));
	Loading_L->AddComponent<Draw2DChangePivot>()->Init(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	Loading_L->AddComponent<Transform>()->Init(D3DXVECTOR3(0.0f, 0.0f, 360.0f), 3, 30, 30, 0.0f);
	Loading_L->SetTag("Loading_L");
	AddGameObject(Loading_L, UI_LAYER);

	GameObject* Loading_O_1 = new GameObject;
	Loading_O_1->SetPosition(D3DXVECTOR3(800.0f, 900.0f, 0.0f));
	Loading_O_1->AddComponent<Draw2DChangePivot>()->Init(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	Loading_O_1->AddComponent<Transform>()->Init(D3DXVECTOR3(0.0f, 0.0f, 360.0f), 3, 30, 30, 0.0f);
	Loading_O_1->SetTag("Loading_O");
	AddGameObject(Loading_O_1, UI_LAYER);

	GameObject* Loading_A = new GameObject;
	Loading_A->SetPosition(D3DXVECTOR3(1000.0f, 900.0f, 0.0f));
	Loading_A->AddComponent<Draw2DChangePivot>()->Init(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	Loading_A->AddComponent<Transform>()->Init(D3DXVECTOR3(0.0f, 0.0f, 360.0f), 3, 30, 30, 0.0f);
	Loading_A->SetTag("Loading_A");
	AddGameObject(Loading_A, UI_LAYER);

	GameObject* Loading_D = new GameObject;
	Loading_D->SetPosition(D3DXVECTOR3(1200.0f, 900.0f, 0.0f));
	Loading_D->AddComponent<Draw2DChangePivot>()->Init(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	Loading_D->AddComponent<Transform>()->Init(D3DXVECTOR3(0.0f, 0.0f, 360.0f), 3, 30, 30, 0.0f);
	Loading_D->SetTag("Loading_D");
	AddGameObject(Loading_D, UI_LAYER);

	GameObject* Loading_I = new GameObject;
	Loading_I->SetPosition(D3DXVECTOR3(1400.0f, 900.0f, 0.0f));
	Loading_I->AddComponent<Draw2DChangePivot>()->Init(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	Loading_I->AddComponent<Transform>()->Init(D3DXVECTOR3(0.0f, 0.0f, 360.0f), 3, 30, 30, 0.0f);
	Loading_I->SetTag("Loading_I");
	AddGameObject(Loading_I, UI_LAYER);

	GameObject* Loading_N_1 = new GameObject;
	Loading_N_1->SetPosition(D3DXVECTOR3(1600.0f, 900.0f, 0.0f));
	Loading_N_1->AddComponent<Draw2DChangePivot>()->Init(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	Loading_N_1->AddComponent<Transform>()->Init(D3DXVECTOR3(0.0f, 0.0f, 360.0f), 3, 30, 30, 0.0f);
	Loading_N_1->SetTag("Loading_N");
	AddGameObject(Loading_N_1, UI_LAYER);

	GameObject* Loading_G = new GameObject;
	Loading_G->SetPosition(D3DXVECTOR3(1800.0f, 900.0f, 0.0f));
	Loading_G->AddComponent<Draw2DChangePivot>()->Init(D3DXVECTOR3(200.0f, 200.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	Loading_G->AddComponent<Transform>()->Init(D3DXVECTOR3(0.0f, 0.0f, 360.0f), 3, 30, 30, 0.0f);
	Loading_G->SetTag("Loading_G");
	AddGameObject(Loading_G, UI_LAYER);
}

void LoadingSceneMotionParticle::Uninit()
{
	Scene::Uninit();
	TextureContainer::Unload(TextureData::Tag::Loading);
	TextureContainer::Unload(TextureData::Tag::Title);

}

void LoadingSceneMotionParticle::Update()
{
	Scene::Update();

	if (TestScene::LoadClear())
	{
		Manager::SetScene<TestScene>();
		return;
	}
}

