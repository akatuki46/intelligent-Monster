#include "TestScene.h"
#include "Scene.h"
#include "manager.h"
#include "TextureContainer.h"
#include "ModelContainer.h"
#include "Motion.h"
#include "Draw2DVer3D.h"
#include "camera.h"
#include "TestComponent.h"
#include "Sky.h"
#include "Draw3D.h"
#include "input.h"
#include "Particle.h"
#include "title.h"

bool  TestScene::m_LoadFlag = false;

void TestScene::Load()
{
	ModelContainer::Instance().Load(ModelData::Tag::Game);
	TextureContainer::Load(TextureData::Tag::Game);

	m_LoadFlag = true;

}

void TestScene::Init()
{
	//Cameraのゲームオブジェクト生成
	GameObject* obj = new GameObject;
	obj->AddComponent<Camera>()->Init(false);
	obj->AddComponent<Camera>()->SetTestFlag(true);
	obj->SetTag("Camera");
	AddGameObject(obj, CAMERA_LAYER);

	GameObject* field = new GameObject;
	field->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	field->SetScale(D3DXVECTOR3(10.0f, 1.0f, 10.0f));
	field->AddComponent<Draw2DVer3D>()->Init(D3DXVECTOR3(1.0f, 0.0f, 1.0f), 10.0f,false);
	field->SetTag("Field");
	AddGameObject(field, PLAY_LAYER);

	GameObject* sky = new GameObject;
	sky->SetPosition(D3DXVECTOR3(0.0f, 40.0f, 0.0f));
	sky->SetScale(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	sky->AddComponent<Sky>()->Init();
	sky->AddComponent<Draw3D>()->Init();
	sky->SetTag("Sky");
	AddGameObject(sky, PLAY_LAYER);

	GameObject* zinouga = new GameObject;
	zinouga->SetPosition(D3DXVECTOR3(0.0f, 2.0f, 0.0f));
	zinouga->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	zinouga->AddComponent<Motion>()->Init();
	zinouga->AddComponent<TestComponent>()->Init();
	zinouga->SetTag("zinouga");
	AddGameObject(zinouga, PLAY_LAYER);

	GameObject* particle = new GameObject;
	particle->SetPosition(D3DXVECTOR3(0.0f,0.0f,0.0f));
	particle->AddComponent<Particle>()->Init(true);
	particle->GetComponent<Particle>()->SetInterval(0);
	particle->GetComponent<Particle>()->SetAmount(10);
	particle->GetComponent<Particle>()->SetLife(60);
	particle->GetComponent<Particle>()->SetLoop(false);
	particle->GetComponent<Particle>()->SetSize(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
	particle->GetComponent<Particle>()->SetColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
	particle->GetComponent<Particle>()->SetUse(true);
	particle->SetTag("Particle3D");
	AddGameObject(particle, PLAY_LAYER);


}

void TestScene::Uninit()
{
	Scene::Uninit();//継承元クラスのメソッド呼び出し

	TextureContainer::Unload(TextureData::Tag::Game);
	ModelContainer::Instance().Unload(ModelData::Tag::Game);

	m_LoadFlag = false;
}

void TestScene::Update()
{
	Scene* scene = Manager::GetScene();

	Scene::Update();//継承元クラスのメソッド呼び出し

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		Manager::SetScene<title>();
	}

}
