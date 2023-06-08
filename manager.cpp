#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "Scene.h"
#include "Game.h"
#include "title.h"
#include "ModelContainer.h"
#include "TextureContainer.h"
#include "audio.h"
#include "Draw3D.h"
#include <time.h>
#include "ImGuiManager.h"

Scene* Manager::m_Scene = NULL;
std::map<std::string,GameObject*> Manager::m_KeepObject;
int Manager::m_DethCnt = 0;
int Manager::m_EneHp = 0;

void Manager::Init()
{
	Renderer::Init();
	ModelContainer::Instance().Init();
	TextureContainer::Init();
	Audio::InitMaster();
	ImGuiManager::Init();

	SetScene<title>();

}


void Manager::Uninit()
{

	m_Scene->Uninit();
	delete m_Scene;

	ImGuiManager::Uninit();
	Audio::UninitMaster();
	ModelContainer::Instance().Uninit();
	TextureContainer::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{


	m_Scene->Update();


}

void Manager::Draw()
{
	Renderer::Begin();


	m_Scene->Draw();

#ifdef _DEBUG
	ImGuiManager::Draw();
#endif // _DEBUG

	Renderer::End();
}
