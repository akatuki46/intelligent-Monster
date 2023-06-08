#pragma once
#include <functional>
#include "Scene.h"

class LodingScene : public Scene
{
public:
	void Init() {};
	void InitLoad(std::function<void(void)> function);
	void Uninit();
	void Update();


private:
	std::function<void(void)> m_LoadingScene;


};

