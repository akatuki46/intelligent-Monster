///////////////////////////////////////////////////////
//      マルチに使う用　コンポーネント
///////////////////////////////////////////////////////
#pragma once
#include "Component.h"
class MultiComponent :
    public Component
{
private:
	int   m_KeepInt = 0;
	bool  m_Flag = false;
	int   m_Cnt = 0;
public:
	void Init();
	void Uninit() override;
	void Update() override;
	void Draw() override;
};

