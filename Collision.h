#pragma once
#include <functional>
#include "Component.h"
#include "GameObject.h"

class Collision :
    public Component
{

public:
	void Init(std::function<void(GameObject*)> function);
	void Uninit() override;
	void Draw() override;
	void Update()override;

private:
	std::function<void(GameObject*)> m_CollisionAction;
};

