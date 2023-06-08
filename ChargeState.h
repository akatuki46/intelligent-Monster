#pragma once
#include "Situation.h"
class GameObject;

class ChargeState :
    public Situation
{
public:
    ChargeState(GameObject* enemy) :pEnemy(enemy) {};

    void Action()override;

    int GetStatus()override;

private:
    GameObject* pEnemy;

};

