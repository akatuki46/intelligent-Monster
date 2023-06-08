#pragma once
#include "Situation.h"
class GameObject;

class SuperChargeState :
    public Situation
{
public:
    SuperChargeState(GameObject* enemy) :pEnemy(enemy) {};

    void Action()override;

    int GetStatus()override;
private:
    GameObject* pEnemy;
    int m_AngerCnt = 0;

};

