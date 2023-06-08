#include "Collision.h"
#include "Scene.h"
#include "manager.h"


void Collision::Init(std::function<void(GameObject*)> function)
{
	m_CollisionAction = function;
}

void Collision::Uninit()
{
}

void Collision::Draw()
{
}

void Collision::Update()
{
	Scene* scene = Manager::GetScene();

	std::vector<GameObject*> obj = scene->GetAllGameObjects(1);

	for (GameObject* object : obj)
	{
		if (m_ParentObject != object && m_ParentObject->GetCollsionNone())
		{
			int a = 0;
			if (object->GetTag() == "attabox")
			{
				a++;
			}

			D3DXVECTOR3 objectPosition = object->GetPosition();

			D3DXVECTOR3 direction = m_ParentObject->GetPosition() - objectPosition;
			float length = D3DXVec3Length(&direction);

			if (length < 3.0f)
			{
				m_CollisionAction(object);

			}
			
		}
	}
}
