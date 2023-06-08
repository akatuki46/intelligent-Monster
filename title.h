#pragma once
#include "Scene.h"
class title :
    public Scene
{
private:
	unsigned int m_Clicked;

	class GameObject* m_Transition = nullptr;
	bool m_TransitionMove = false;

public:
	void Init();
	void InitLoad(std::function<void(void)> function) {};

	void Uninit();
	void Update();


};

