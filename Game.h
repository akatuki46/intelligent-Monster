#pragma once
#include "Scene.h"

class BehaviorTree;

class Game : public Scene
{
private:
	BehaviorTree* behavior = nullptr;
	static bool  m_LoadFlag;

	class GameObject* m_Transition = nullptr;
	bool m_TransitionMove = false;

public:
	void Init();
	void InitLoad(std::function<void(void)> function) {};

	void Uninit();
	void Update();

	static void Load();

	static bool LoadClear() { return m_LoadFlag; }


};

