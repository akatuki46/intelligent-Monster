#pragma once
#include "Scene.h"

class TestScene : public Scene
{
private:
	static bool m_LoadFlag;
public:
	void Init();
	void InitLoad(std::function<void(void)> function) {};

	void Uninit();
	void Update();

	static void Load();

	static bool LoadClear() { return m_LoadFlag; }


};

