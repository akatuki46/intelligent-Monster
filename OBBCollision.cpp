#include "OBBCollision.h"
#include "Scene.h"
#include "manager.h"

void OBBCollision::Init(std::function<void(GameObject*,std::string)> function)
{
	m_CollisionAction = function;

}

void OBBCollision::Uninit()
{
}

void OBBCollision::Draw()
{
}

void OBBCollision::Update()
{
	Scene* scene = Manager::GetScene();

	std::vector<GameObject*> obj = scene->GetAllGameObjects(1);

	for (GameObject *object : obj)
	{
		if (m_ParentObject->GetCollsionNone())
		{
			int a = 0;

			if (m_ParentObject->GetTag() == "Attack")
			{
				a++;
			}
			D3DXVECTOR3 OBBPosition = object->GetPosition();
			D3DXVECTOR3 OBBScale = object->GetScale();
			D3DXVECTOR3 direction = (m_ParentObject->GetPosition()) -
				(OBBPosition);

			D3DXVECTOR3 obbX, obbZ, obbY;
			float obbLenx, obbLenz, obbLeny;

			obbX = object->GetObbX();
			obbLenx = D3DXVec3Length(&obbX);
			obbX /= obbLenx;

			//obbY = object->GetObbY();
			//obbLeny = D3DXVec3Length(&obbY);
			//obbY /= obbLenx;

			obbZ = object->GetObbZ();
			obbLenz = D3DXVec3Length(&obbZ);
			obbZ /= obbLenz;

			float lenX, lenY, lenZ;
			lenX = D3DXVec3Dot(&obbX, &direction);
			lenY = D3DXVec3Dot(&obbY, &direction);
			lenZ = D3DXVec3Dot(&obbZ, &direction);



			if (fabs(lenX) < obbLenx && fabs(lenZ) < obbLenz/* && fabs(lenY) < obbLeny*/)
			{

				m_CollisionAction(object,m_ParentObject->GetTag());
			}
		}
	}
}
