#include "RayCollision.h"
#include "Scene.h"
#include "manager.h"
#include "Ray.h"
#include "Enemy.h"

void RayCollision::Init(std::function<void(GameObject*)> function)
{
	m_CollisionAction = function;
}

void RayCollision::Update()
{
	if (m_ParentObject->GetComponent<Ray>())
	{
		Scene* scene = Manager::GetScene();

		std::vector<GameObject*> obj = scene->GetAllGameObjects(1);

		for (GameObject* object : obj)
		{	
				//Obbのポジション
				D3DXVECTOR3 ObbPos = object->GetPosition();

				//各辺の長さ/2
				D3DXVECTOR3 ObbX, ObbY, ObbZ;
				float LenObbX, LenObbY, LenObbZ;
				ObbX = object->GetObbX();
				ObbY = object->GetObbY();
				ObbZ = object->GetObbZ();

				LenObbX = D3DXVec3Length(&ObbX);
				LenObbY = D3DXVec3Length(&ObbY);
				LenObbZ = D3DXVec3Length(&ObbZ);
				D3DXVECTOR3 ObbLen = D3DXVECTOR3(LenObbX, LenObbY, LenObbZ);

				//Obbの向き
				ObbX /= LenObbX;
				ObbY /= LenObbY;
				ObbZ /= LenObbZ;
				//正規化
				D3DXVECTOR3 ObbDire = object->GetRotation();


				//Rayの始点座標
				D3DXVECTOR3 RayStartPos = m_ParentObject->GetComponent<Ray>()->GetRayStart();

				//Rayの向き
				D3DXVECTOR3 RayDire = m_ParentObject->GetComponent<Ray>()->GetRayDire();

				//OBB基準の座標系へ変換
				RayStartPos -= ObbPos;
				//OBBの角度分始点を回転
				RayStartPos = VRotate2D(RayStartPos, -ObbDire.y, ObbDire.x);
				//OBBの角度分線分の方向ベクトルを回転
				RayDire = VRotate2D(RayDire, -ObbDire.y, ObbDire.x);

				float tmin = 0.0f;
				float tmax = 100.0f;

				int LoopCnt = 0;
				do
				{
					//x方向の当たり判定
					if (LoopCnt == 0)
					{
						float t1 = (-LenObbX - RayStartPos.x) / RayDire.x;
						float t2 = (LenObbX - RayStartPos.x) / RayDire.x;

						if (t1 > t2)std::swap(t1, t2);
						if (t1 > tmin)tmin = t1;
						if (t2 < tmax)tmax = t2;
					}
					//if (LoopCnt == 1)
					//{
					//	float t1 = (-1 - RayStartPos.y) / RayDire.y;
					//	float t2 = (1 - RayStartPos.y) / RayDire.y;

					//	if (t1 > t2)std::swap(t1, t2);
					//	if (t1 > tmin)tmin = t1;
					//	if (t2 < tmax)break;
					//}
					
					//z方向の当たり判定
					if (LoopCnt == 1)
					{
						float t1 = (-LenObbZ - RayStartPos.z) / RayDire.z;
						float t2 = (LenObbZ - RayStartPos.z) / RayDire.z;

						if (t1 > t2)std::swap(t1, t2);
						if (t1 > tmin)tmin = t1;
						if (t2 < tmax)tmax = t2;
					}
					LoopCnt++;

				} while (LoopCnt < 2);

				//当たっているなら
				if (LoopCnt == 2 && tmin <= tmax)
				{
					//当たってはいるが、間にプレイヤーがいてプレイヤーが隠れていないか
					if (m_ParentObject->GetComponent<Enemy>()->FindPlayer())
					{
						D3DXVECTOR3 Direction = m_ParentObject->GetPosition() -
							m_ParentObject->GetComponent<Enemy>()->GetFindPlayer()->GetPosition();

						float Length;
						Length = D3DXVec3Length(&Direction);


						if (Length > tmin)
						{
							m_CollisionAction(object);
						}
					}
					else
					{
						m_CollisionAction(object);
					}
				}
			}

	}
}
