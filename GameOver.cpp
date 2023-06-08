#include "main.h"
#include "renderer.h"
#include "input.h"
#include "manager.h"
#include "title.h"
#include "GameOver.h"
#include "TextureContainer.h"
#include "Draw2D.h"
#include "Padinput.h"

void GameOver::Init()
{
	TextureContainer::Load(TextureData::Tag::Result);

	GameObject* Polygon2D = new GameObject;
	Polygon2D->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Polygon2D->AddComponent<Draw2D>()->Init(D3DXVECTOR3(SCREEN_RESOLUTION_WIDTH, SCREEN_RESOLUTION_HEIGHT, 0.0f), 1);
	Polygon2D->SetTag("GameOver");
	AddGameObject(Polygon2D, UI_LAYER);
}

void GameOver::Uninit()
{

	Scene::Uninit();
	TextureContainer::Unload(TextureData::Tag::Result);

}

void GameOver::Update()
{
	Scene::Update();

	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonXinputTriggered(0,XINPUT_GAMEPAD_B))
	{
		Manager::SetScene<title>();
	}
}
