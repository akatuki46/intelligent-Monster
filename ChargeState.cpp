#include "ChargeState.h"
#include "manager.h"
#include "Scene.h"
#include "Enemy.h"
#include "SuperChargeState.h"
#include "Draw3D.h"
#include "Motion.h"
#include "Particle.h"
#include "NomalState.h"

void ChargeState::Action()
{
	pEnemy->GetComponent<Motion>()->SetShaderCnt(1);
	pEnemy->GetComponent<Particle>()->SetUse(true);

	//‘Ì—Í‚ª”¼•ªˆÈ‰º‚É‚È‚Á‚½‚ç‘JˆÚ
	if (pEnemy->GetComponent<Enemy>()->GetEnemyHp() <= 300)
	{
		pEnemy->GetComponent<Enemy>()->NextSituation(new SuperChargeState(pEnemy));

	}

	if (pEnemy->GetComponent<Enemy>()->GetFearFlag())
	{
		pEnemy->GetComponent<Enemy>()->ResetChargeCnt();
		pEnemy->GetComponent<Enemy>()->NextSituation(new NomalState(pEnemy));

	}
}

int ChargeState::GetStatus()
{
	return 2;
}
