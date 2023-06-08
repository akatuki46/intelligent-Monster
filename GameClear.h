#pragma once
#include "Scene.h"
class GameClear : public Scene
{
public:
	void Init();
	void InitLoad(std::function<void(void)> function) {};

	void Uninit();
	void Update();


};

