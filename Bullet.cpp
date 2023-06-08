#include "main.h"
#include "renderer.h"
#include "model.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Scene.h"
#include "Player.h"
#include "manager.h"
#include "ModelContainer.h"
#include "Draw3D.h"
#include "AnimetionDraw2DVer3D.h"

void Bullet::Init()
{

	//m_ParentObject->m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//m_ParentObject->m_Rotation = D3DXVECTOR3(0.0f, 3.15f, 0.0f);
	//m_ParentObject->m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//m_ParentObject->m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


}


void Bullet::Uninit()
{


}


void Bullet::Update()
{
	//Œ»Ý‚ÌƒV[ƒ“‚ðŽæ“¾
	Scene* scene = Manager::GetScene();

	m_ParentObject->AddPosition(m_ParentObject->GetVelocity());
	
	if (fabs(m_ParentObject->GetPosition().z) > 25.0f ||
		fabs(m_ParentObject->GetPosition().x) > 25.0f)
	{
		m_ParentObject->SetDestroy();
		return;
	}

	m_ParentObject->AddVelocity(-(m_ParentObject->GetRight()) * m_Rot);

}


void Bullet::Draw()
{

}

void Bullet::CollisionAction(GameObject* obj)
{
	//if (obj->GetTag() == "Enemy")
	//{
	//	Scene* scene = Manager::GetScene();

	//	GameObject* bullet = scene->GetGameObject("Bullet", scene->PLAY_LAYER);

	//	GameObject* explosion = new GameObject;
	//	explosion->SetTag("Player");
	//	explosion->m_Position = bullet->m_Position;
	//	explosion->m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//	explosion->AddComponent<Draw3D>()->Init();
	//	scene->AddGameObject(explosion, Scene::PLAY_LAYER);

	//	obj->SetDestroy();
	//	bullet->SetDestroy();
	//}
}
