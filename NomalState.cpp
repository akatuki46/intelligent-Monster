#include "NomalState.h"
#include "manager.h"
#include "Scene.h"
#include "Enemy.h"
#include "ChargeState.h"
#include "Motion.h"
#include "Particle.h"

void NomalState::Action()
{
	pEnemy->GetComponent<Motion>()->SetShaderCnt(0);
	//pEnemy->GetComponent<Particle>()->SetUse(false);

	//チャージ回数が3回になったら帯電状態へ移行
	if (pEnemy->GetComponent<Enemy>()->GetChargeCnt() == 3)
	{
		pEnemy->GetComponent<Enemy>()->NextSituation(new ChargeState(pEnemy));
	}
}

int NomalState::GetStatus()
{
	return 1;
}
