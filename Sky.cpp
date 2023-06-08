#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "model.h"
#include "Sky.h"
#include "Enemy.h"
#include "camera.h"
#include "Scene.h"
#include "ModelContainer.h"


void Sky::Update()
{
	Scene* scene = Manager::GetScene();
	GameObject* pcamera = scene->GetGameObject("Camera",scene->CAMERA_LAYER);

	m_ParentObject->SetPosition(D3DXVECTOR3(pcamera->GetPosition().x, m_ParentObject->GetPosition().y, pcamera->GetPosition().z));
}

