#pragma once
#include "Situation.h"
class GameObject;

class NomalState :
    public Situation
{
public:
    NomalState(GameObject* enemy) :pEnemy(enemy) {};

    void Action()override;

    int GetStatus()override;

private:
    GameObject* pEnemy;

};

