//////////////////////////////////////////////////////////////////////////////////////////////////
//  テスト用　好きに使えるコンポーネント
/////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Component.h"
#include "main.h"
#include "manager.h"
#include "Scene.h"

class TestComponent :
    public Component
{
private:
	D3DXVECTOR3 m_ClothWind = D3DXVECTOR3(0.0f,0.0f,0.0f);

	int m_Cnt = 0;

	int m_TestFlag = -1;
public:
	void Init();
	void Uninit() override;
	void Draw() override;
	void Update()override;
};

