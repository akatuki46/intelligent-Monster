#pragma once
#include "Component.h"
class Model;

class  Sky : public Component
{

public:

	void Init(){};
	void Uninit() override {};
	void Update() override ;
	void Draw() override {};
};

