#pragma once
#include "Component.h"

class  Bullet : public Component
{
private:
	float m_Rot = 0.001f;

public:

	void Init();
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static void CollisionAction(GameObject* obj);
};

