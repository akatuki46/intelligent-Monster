#include "main.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "title.h"
#include "GameClear.h"
#include "TextureContainer.h"
#include "Draw2D.h"
#include "Padinput.h"

void GameClear::Init()
{
	TextureContainer::Load(TextureData::Tag::Result);

	GameObject* Polygon2D = new GameObject;
	Polygon2D->SetPosition(D3DXVECTOR3(0.0f,0.0f,0.0f));
	Polygon2D->AddComponent<Draw2D>()->Init(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH, SCREEN_RESOLUTION_HEIGHT, 0.0f), 1);
	Polygon2D->SetTag("GameClear");
	AddGameObject(Polygon2D, UI_LAYER);
}

void GameClear::Uninit()
{

	Scene::Uninit();
	TextureContainer::Unload(TextureData::Tag::Result);

}

void GameClear::Update()
{
	Scene::Update();

	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonXinputTriggered(0, XINPUT_GAMEPAD_B))
	{
		Manager::SetScene<title>();
	}
}
