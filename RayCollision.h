#pragma once
#include <functional>
#include "Component.h"
#include "GameObject.h"

class RayCollision :
	public Component
{

public:
	void Init(std::function<void(GameObject*)> function);
	void Uninit() override {};
	void Draw() override {};
	void Update()override;

	D3DXVECTOR3 VRotate2D(const D3DXVECTOR3 &Vec, float Sin, float Cos) 
	{
		return D3DXVECTOR3(Vec.x * cosf(Cos) - Vec.z * sinf(Sin),0.0f, Vec.x * sinf(Sin) + Vec.z * cosf(Cos));
	}

private:
	std::function<void(GameObject*)> m_CollisionAction;

	bool m_CollisionFlag = false;

};

