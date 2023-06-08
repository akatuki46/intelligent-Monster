#pragma once
#include "Component.h"
#include "main.h"
#include "manager.h"

class GameObject;

class MapComponent :
    public Component
{
private:
	GameObject* PlayerPos = nullptr;
	GameObject* EnemyPos = nullptr;

	bool m_flag = false;
	
public:
	void Init();
	void Uninit() override;
	void Draw() override;
	void Update()override;
};

