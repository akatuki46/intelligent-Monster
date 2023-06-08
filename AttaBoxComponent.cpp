#include "AttaBoxComponent.h"
#include "Scene.h"
#include "manager.h"
#include "Player.h"
#include "Enemy.h"
#include "Particle.h"

void AttaBoxComponent::Init(GameObject* caller, int damage,std::string name)
{
	m_Caller = caller;
	m_Damage = damage;
	m_SubjectCollision = name;
}

void AttaBoxComponent::CollisionAction(GameObject* obj, std::string name)
{
	Scene* scene = Manager::GetScene();
	GameObject* Attabox = scene->GetGameObject(name, scene->PLAY_LAYER);

	if (obj->GetTag() == "Player" && obj->GetTag() == Attabox->GetComponent<AttaBoxComponent>()->GetSubjectName())
	{
		if (!obj->GetComponent<Player>()->GetHitFlag())
		{
			obj->SetPosition(obj->GetPosition() + obj->GetForward() * 3);
			obj->SetAnimetionName("Hit");
			obj->SetNextAnimetionName("Hit");

			obj->GetComponent<Player>()->LosHp(20);
			obj->GetComponent<Player>()->SetRedHp(10);

			obj->GetComponent<Player>()->SetHitFlag(true);
		}
	}

	if (obj->GetTag() == "Enemy" && obj->GetTag() == Attabox->GetComponent<AttaBoxComponent>()->GetSubjectName())
	{
		obj->GetComponent<Enemy>()->LastAttack(true);

		obj->GetComponent<Enemy>()->AddDamage(20);
		obj->GetComponent<Enemy>()->LosHp(20);

		GameObject* particle = new GameObject;
		particle->SetPosition(Attabox->GetPosition());
		particle->AddComponent<Particle>()->Init(true);
		particle->GetComponent<Particle>()->SetInterval(0);
		particle->GetComponent<Particle>()->SetAmount(20);
		particle->GetComponent<Particle>()->SetLife(60);
		particle->GetComponent<Particle>()->SetLoop(false);
		particle->GetComponent<Particle>()->SetSize(D3DXVECTOR3(2.0f, 2.0f, 0.0f));
		particle->GetComponent<Particle>()->SetColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
		particle->GetComponent<Particle>()->SetUse(true);
		particle->GetComponent<Particle>()->SetType(1);
		particle->GetComponent<Particle>()->SetAcc(D3DXVECTOR3(0.0f,-0.01,0.0f));
		particle->GetComponent<Particle>()->SetSpd(0.01f);

		particle->SetTag("Particle3D");
		scene->AddGameObject(particle, scene->PLAY_LAYER);
	}

}
