#pragma once
#include <functional>
#include "Component.h"
#include "GameObject.h"

class OBBCollision :
    public Component
{
public:
	void Init(std::function<void(GameObject*, std::string)> function);
	void Uninit() override;
	void Draw() override;
	void Update()override;

private:
	std::function<void(GameObject*, std::string)> m_CollisionAction;
};

