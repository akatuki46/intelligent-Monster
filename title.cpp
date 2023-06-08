#include "main.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "title.h"
#include "Game.h"
#include "TextureContainer.h"
#include "audio.h"
#include "Draw2D.h"
#include "TestComponent.h"
#include "Draw2DAction.h"
#include "ClothDraw.h"
#include "Prism.h"
#include "camera.h"
#include "Wave3D.h"
#include "Particle.h"
#include "SizeDraw2D.h"
#include "input.h"
#include "Sky.h"
#include "Draw3D.h"
#include "ModelContainer.h"
#include "TestScene.h"
#include "LodingScene.h"
#include "FadeDraw2D.h"
#include "Transition.h"
#include "LoadingSceneMotionParticle.h"
#include "BaseCamp.h"

void title::Init()
{
	TextureContainer::Load(TextureData::Tag::Title);
	TextureContainer::Load(TextureData::Tag::Any);

	//Cameraのゲームオブジェクト生成
	GameObject* obj = new GameObject;
	obj->AddComponent<Camera>()->Init(false);
	obj->SetTag("Camera");
	AddGameObject(obj, CAMERA_LAYER);

	GameObject* titlelogo = new GameObject;
	titlelogo->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	titlelogo->AddComponent<Draw2D>()->Init(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH, SCREEN_RESOLUTION_HEIGHT, 0.0f), 1);
	titlelogo->SetTag("title");
	AddGameObject(titlelogo, UI_LAYER);

	GameObject* Cloth = new GameObject;
	Cloth->AddComponent<ClothDraw>()->Init(D3DXVECTOR3(200.0f,50.0f,0.0f),D3DXVECTOR3(60.0f,0.0f,30.0f));
	Cloth->AddComponent<TestComponent>()->Init();
	Cloth->SetTag("Cloth");
	AddGameObject(Cloth, UI_LAYER);


	GameObject* GameButton = new GameObject;
	GameButton->SetPosition(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, 750.0f, 0.0f));
	GameButton->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(600.0f,100.0f,0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f),1);
	GameButton->SetTag("GameButton");
	AddGameObject(GameButton, UI_LAYER);

	GameObject* MakeBotton = new GameObject;
	MakeBotton->SetPosition(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2, 850.0f, 0.0f));
	MakeBotton->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(600.0f, 100.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), 1);
	MakeBotton->SetTag("MakeButton");
	AddGameObject(MakeBotton, UI_LAYER);


	GameObject* particle = new GameObject;
	particle->AddComponent<Particle>()->Init(false);
	particle->SetTag("Particle2D");
	AddGameObject(particle, UI_LAYER);

	GameObject* Pore = new GameObject;
	Pore->SetPosition(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH / 2 - 400, 550.0f, 0.0f));
	Pore->AddComponent<SizeDraw2D>()->Init(D3DXVECTOR3(50.0f, 1000.0f, 0.0f), D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),1);
	Pore->SetTag("Pore");
	AddGameObject(Pore, UI_LAYER);



	
}

void title::Uninit()
{

	Scene::Uninit();
	TextureContainer::Unload(TextureData::Tag::Title);
	TextureContainer::Unload(TextureData::Tag::Any);

}

void title::Update()
{
	Scene::Update();

	// マウスクリック判定
	if (GetAsyncKeyState(VK_LBUTTON))
		m_Clicked++;
	else
		m_Clicked = 0;

	POINT p;
	GetCursorPos(&p);

	// スクリーン座標をクライアント座標に変換する
	ScreenToClient(GetWindow(), &p);

	Scene* scene = Manager::GetScene();
	GameObject* GameButton = scene->GetGameObject("GameButton", scene->UI_LAYER);

	if (GameButton != nullptr && m_Clicked == 1 &&
		(GameButton->GetPosition().x + GameButton->GetComponent<SizeDraw2D>()->GetTexSize().x / 2) > p.x &&
		(GameButton->GetPosition().x - GameButton->GetComponent<SizeDraw2D>()->GetTexSize().x / 2) < p.x &&
		(GameButton->GetPosition().y + GameButton->GetComponent<SizeDraw2D>()->GetTexSize().y / 2) > p.y &&
		(GameButton->GetPosition().y - GameButton->GetComponent<SizeDraw2D>()->GetTexSize().y / 2) < p.y)
	{
		Manager::SetSceneLoad(BaseCamp::Load);
		return;
	}

	GameObject* Make = scene->GetGameObject("MakeButton", scene->UI_LAYER);
	if (Make != nullptr && m_Clicked == 1 &&
		(Make->GetPosition().x + Make->GetComponent<SizeDraw2D>()->GetTexSize().x / 2) > p.x &&
		(Make->GetPosition().x - Make->GetComponent<SizeDraw2D>()->GetTexSize().x / 2) < p.x &&
		(Make->GetPosition().y + Make->GetComponent<SizeDraw2D>()->GetTexSize().y / 2) > p.y &&
		(Make->GetPosition().y - Make->GetComponent<SizeDraw2D>()->GetTexSize().y / 2) < p.y)
	{
		Manager::SetSceneLoad(TestScene::Load);
		return;

	}
}
