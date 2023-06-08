#pragma once
#include "Component.h"
#include "manager.h"
#include "Scene.h"
#include "main.h"
class HpComponent :
    public Component
{
private:
	int m_keepHp = 0;
	int m_keepRedHp = 0;

	D3DXVECTOR4 m_KeepColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
public:
	void Init();
	void Uninit() override;
	void Update() override;
	void Draw() override;


};

